//=============================================================================
// Copyright Langis Pitre 1998
// You may do whatever you want with this code, as long as you include this
// copyright notice in your implementation files.
//=============================================================================
//=============================================================================
//                             CMixerFader
//
// Since this class is derived from CSliderCtrl, it allows the user to associate
// a slider resource with a mixer fader control. All messages are handled
// internally through nessage reflection.
// 
// How to use:
//
// 1) create a slider resource (either horizontal or vertical)
// 2) declare a variable of type CMixerFader in your CDialog-derived class
//    declaration
// 3) In your OnInitDialog, subclass the CMixerFader object to associate it
//    with the resource (or use DDE with a variable of type CMixerFader)
// 4) In your OnInitDialog, call the Init() member funcion.
//
// If the device has two channels, it is possible to either create one
// main volume and one balance slider, or to create sliders for the left
// and right channels.
//
//=============================================================================
//=============================================================================
//=============================================================================
#include "stdafx.h"
#include "MixerClasses.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// for fader control
const int FADER_SPAN = 65535;
const int FADER_STEP = 256;
const int SLIDER_SPAN = FADER_SPAN/FADER_STEP;
const int FADER_HALF  = FADER_SPAN/2;


//<=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=>
// Name   : CMixerFader
//          
// Descr. : 
//          
//------------------------------------------------------------------------------------------
CMixerFader::CMixerFader() : CMixerBase()
{
	m_Value = NULL;
	m_DeltaOverMax = 0;
}


//<=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=>
// Name   : ~CMixerFader
//          
// Descr. : 
//          
//------------------------------------------------------------------------------------------
CMixerFader::~CMixerFader()
{
	if( m_Value )
		delete[] m_Value;
}


BEGIN_MESSAGE_MAP( CMixerFader, CSliderCtrl )
	//{{AFX_MSG_MAP( CMixerFader )
	ON_MESSAGE( MM_MIXM_CONTROL_CHANGE, OnMixerControlChanged )
	ON_WM_HSCROLL_REFLECT( )
	ON_WM_VSCROLL_REFLECT( )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


//<=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=>
// Name   : Init
//          
// Descr. : Initializes the mixer control.
//          Init queries the mixer device for the specified mixer control type.
//          If such a control is found, its current value is queried, and used
//          to initialize the windows control.
//          
// Return : int
// Arg    : DWORD LineType    : see definition of MixerBase::Init() for a description
// Arg    : DWORD ControlType : type of desired fader.
//
//          These are valid arguments:
//
//              MIXERCONTROL_CONTROLTYPE_FADER 
//              MIXERCONTROL_CONTROLTYPE_VOLUME
//              MIXERCONTROL_CONTROLTYPE_BASS
//              MIXERCONTROL_CONTROLTYPE_TREBLE
//              MIXERCONTROL_CONTROLTYPE_EQUALIZER
//
// Arg    : int subType: If the mixer line has two channels, the subtype can be used to
//                       create a fader for the left or right channel, or as a balance
//                       between the channels, or as a main fader that controls both
//                       channels.
//                       If only one channel is available, only the MAIN subtype may be
//                       specified.
//                       These are valid arguments:
//                       
//                       CMixerFader::LEFT
//                       CMixerFader::RIGHT
//                       CMixerFader::MAIN
//                       CMixerFader::BALANCE
//                       
//------------------------------------------------------------------------------------------
int CMixerFader::Init( DWORD LineType, DWORD ControlType, int subType )
{	
	EnableWindow( FALSE );

	if( (ControlType & MIXERCONTROL_CT_CLASS_MASK) != MIXERCONTROL_CT_CLASS_FADER )
	{
		PopupErrorMsg( "Wrong control type for a fader control.", "CMixerFader::Init"  );
		return 0;
	}
	if( subType < LEFT || subType > BALANCE )
	{
		PopupErrorMsg( "Wrong sub-type for a fader control.", "CMixerFader::Init"  );
		return 0;
	}

	m_Type = subType;

	MIXERLINE mixerLine;
	if( CMixerBase::Init( LineType, m_hWnd, mixerLine ) == 0 )
		return 0;

	if( m_nChannels < 2 )
	{
		if( m_Type == LEFT || m_Type == RIGHT || m_Type == BALANCE )
		{
			PopupErrorMsg( "Only one channel available. Use type MAIN only.\r\nAssociated Windows control will be disabled.", 
				           "CMixerFader::Init"  );
			return 0;
		}
	}
	
	// ---------- We try and find a fader control for the mixer line ---------
    MIXERLINECONTROLS   mixerLineControl;
    MIXERCONTROL        mixerControl;

	mixerLineControl.cbStruct       = sizeof( mixerLineControl );
	mixerLineControl.dwLineID       = mixerLine.dwLineID;
	mixerLineControl.dwControlType  = ControlType;
	mixerLineControl.cControls      = 1;
	mixerLineControl.cbmxctrl       = sizeof( mixerControl );
	mixerLineControl.pamxctrl       = &mixerControl;
	
	if( mixerGetLineControls( ( HMIXEROBJ )m_HMixer, &mixerLineControl, 
		MIXER_GETLINECONTROLSF_ONEBYTYPE ) != MMSYSERR_NOERROR )
	{
		TRACE( "mixerGetLineControls failed\n" );
		PopupErrorMsg( "Could not find specified mixer control.\r\nAssociated Windows slider control will be disabled.", 
				       "CMixerFader::Init"  );
		return 0;
	}
	
	m_Value = new MIXERCONTROLDETAILS_UNSIGNED[m_nChannels];
	if( m_Value == NULL )
	{
		PopupErrorMsg( "Memory allocation error.", "CMixerFader::Init"  );
		return 0;
	}

	// ---------- We get the fader control's current value ----------------
	m_Control.cbStruct       = sizeof( m_Control );
    m_Control.dwControlID    = mixerControl.dwControlID;
    m_Control.cChannels      = mixerLine.cChannels;
    m_Control.cMultipleItems = 0;
    m_Control.cbDetails      = sizeof( MIXERCONTROLDETAILS_UNSIGNED );
    m_Control.paDetails      = m_Value;

    if( mixerGetControlDetails( ( HMIXEROBJ )m_HMixer, &m_Control, 
		MIXER_GETCONTROLDETAILSF_VALUE ) != MMSYSERR_NOERROR )
    {
		PopupErrorMsg( "mixerGetControlDetails failed", "CMixerFader::Init"  );
		return 0;
    }

	EnableWindow( TRUE );
	SetRange( 0, SLIDER_SPAN );

	SetHVSliderPos();

	return 1;
}


//<=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=>
// Name   : SetHVSliderPos
//          
// Descr. : Updates the slider position according to the subtype of fader used.
//          Since a fader can be used as a balance between the two channels, this function
//          and SetFaderValue() had to work in conjunction to ensure proper behavior of all
//          sliders. For example, if the balance slider is shifted to one side, the right
//          and left channels sliders must react accordingly. And if the main fader slider
//          is moved, the relative position of the right and left channels must be kept
//          constant.
//          You don't have to read the rest of this description. It was not written to
//          impress anybody; I just wanted to keep it logged somewhere!
//
//            For the BALANCE slider position P, the maximum value must be obtained at mid-course,
//          the value decreasing linearly to 0 at both ends.
//            Defining D (Delta) as R - L, the difference in value between the Right and
//          Left channel, and M the greatest value between the the Right and Left channel,
//          D / M is a function that is defined in the range [-1, 1], with a maximum at 0.
//            So, SLIDER_SPAN / 2 * ( D/M + 1) will have the range [0, SLIDER_SPAN] with a
//          maximum at half the slider range.
//
//          -> P = S / 2 * ( DOM + 1), where DOM = D/M (Delta-Over-Max),and S = SLIDER_SPAN
//          
//          Whenever a new set of values are sent to the mixer device, it sends back a
//          notification message to all the mixer controls. The CMixerFader handler
//          for this message (see below) calls SetHVSliderPos() to reposition the affected
//          sliders. This was a headache because the current value of DOM had to be
//          protected from unwanted changes. I used a member variable (m_DeltaOverMax) that
//          could be used by both this function and SetFaderValue(). This looked simple on
//          paper, but it took me a lot of debugging to find the right way to do this.
//
// Return : void
//------------------------------------------------------------------------------------------
void CMixerFader::SetHVSliderPos()
{
	float MaxVal;

	if( m_nChannels > 1 )
	{
		MaxVal = ( float )max( m_Value[RIGHT].dwValue, m_Value[LEFT].dwValue );
		if( MaxVal > 0 )
		{
			m_DeltaOverMax = ( (float)m_Value[RIGHT].dwValue - (float)m_Value[LEFT].dwValue )/MaxVal;
		}
	}
	else
	{
		MaxVal = ( float )m_Value->dwValue;
	}
		
	switch ( m_Type )
	{
		case MAIN: // set the main fader to the maximum value
			SetSliderPos( int( MaxVal/FADER_STEP ) );
			break;

		case BALANCE: // pos = SLIDER_SPAN/2 * ( delta/ max + 1 )
			if( MaxVal > 0 )
			{
				SetSliderPos( int( SLIDER_SPAN*( m_DeltaOverMax + 1.0 )/2.0 ) );
			}
			break;

		case LEFT: // only set the left channel slider
			SetSliderPos( int( ( float )m_Value[RIGHT].dwValue/FADER_STEP ) );
			break;

		case RIGHT: // only set the right channel slider
			SetSliderPos( int( ( float )m_Value[LEFT].dwValue/FADER_STEP ) );
			break;

		default:
			PopupErrorMsg( "Wrong sub-type for a fader control.", "CMixerFader::SetHVSliderPos" );
	}
}


//<=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=>
// Name   : SetFaderValue
//          
// Descr. : the slider position changed, update the values and send to mixer device.
//
//          To determine the values to send to the mixer device, this algorithm is used:
//
//          - If the MAIN slider is moved:
//          The idea is to keep D = R - L constant. In other words, D1/M1 = D2/M2 where
//          D2 and M2 are the new values.
//          Now, if D1 > 0, this means that R1 = M1. This, in the abvove equality, gives:
//          -> L2 = R2( 1 - D1/R1) =  R2( 1 - DOM1 )
//          If D1 < 0,  L1 = M1, which leads to:
//          ->  R2 = L2( 1 + DOM1 )
//
//          - If the BALANCE slider is moved:
//          This will change D. Starting from the equation P = S / 2 * ( D/M + 1)
//          and rearranging the terms, we obtain respectively for the rigth and left channels:
//
//          -> R = M ( 2P/S - 1 ) + L
//          -> L = R - M ( 2P/S - 1 )
//
//          If D > 0, R = M. This gives: L = 2R ( 1 - P/S )
//          If D < 0, L = M. This gives: R = 2LP/S
//
// Return : void
//------------------------------------------------------------------------------------------
void CMixerFader::SetFaderValue()
{
	DWORD newVal = GetSliderValue();
	
	float MaxVal;

	if( m_nChannels > 1 )
	{
		MaxVal = ( float )max( m_Value[RIGHT].dwValue, m_Value[LEFT].dwValue );
	}
	else
	{
		MaxVal = ( float )m_Value->dwValue;
	}

	switch ( m_Type )
	{
		case MAIN:
			if( m_nChannels > 1 )
			{
				if( m_DeltaOverMax > 0 )
				{
					m_Value[RIGHT].dwValue = newVal;
					m_Value[LEFT].dwValue = DWORD( newVal*( 1.0f - m_DeltaOverMax ) );
				}
				else
				{
					m_Value[LEFT].dwValue = newVal;
					m_Value[RIGHT].dwValue = DWORD( newVal*( 1.0f + m_DeltaOverMax ) );
				}
			}
			else
			{
				m_Value->dwValue = newVal;
			}
			break;

		case BALANCE:
			if( newVal > FADER_HALF )
			{
				m_Value[RIGHT].dwValue = DWORD(MaxVal);
				m_Value[LEFT].dwValue = DWORD( 2*MaxVal*( 1.0 - ( float )newVal/FADER_SPAN ) );
			}
			else
			{
				m_Value[RIGHT].dwValue = DWORD( 2*MaxVal*( float )newVal/FADER_SPAN );
				m_Value[LEFT].dwValue = DWORD(MaxVal);
			}
			break;

		case LEFT:
			m_Value[RIGHT].dwValue = newVal;
			break;

		case RIGHT:
			m_Value[LEFT].dwValue = newVal;
			break;

		default:
			PopupErrorMsg( "Wrong sub-type for a fader control.", "CMixerFader::SetFaderValue" );
			return;
	}
	
	if( mixerSetControlDetails( ( HMIXEROBJ )m_HMixer, &m_Control, 
		MIXER_SETCONTROLDETAILSF_VALUE ) != MMSYSERR_NOERROR )
	{
		TRACE("mixerGetControlDetails error");
	}
}


//<=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=>
// Name   : GetSliderValue
//          
// Descr. : gets the current slider position. The value returned depends on the orientation
//          of the slider.
//          
// Return : DWORD value corresponding to slider position
//------------------------------------------------------------------------------------------
DWORD CMixerFader::GetSliderValue()
{
	if( ( GetStyle( ) & TBS_VERT ) == TBS_VERT )
	{
		return ( ( SLIDER_SPAN - GetPos() ) * FADER_STEP );
	}
	else
	{
		return ( GetPos() * FADER_STEP );
	}
}


//=============================================================================
// Name   : OnMixerControlChanged
//          
// Descr. : Message handler called whenever the MCI device sends the MM_MIXM_CONTROL_CHANGE
//          message. The MCI mixer device will send this message for any changing
//          setting, so we need to check that the MCI control that sent the message
//          corresponds to the current fader control.
//          
// Return : LONG
// Arg    : UINT         : 
// Arg    : LONG message : 
//=============================================================================
LONG CMixerFader::OnMixerControlChanged( UINT hMix, LONG message )
{
	UINT id = ( UINT )message;

	if( id == m_Control.dwControlID && m_HMixer == (HMIXER)hMix )
	{
		if( mixerGetControlDetails( ( HMIXEROBJ )m_HMixer, &m_Control, 
			MIXER_GETCONTROLDETAILSF_VALUE ) != MMSYSERR_NOERROR )
		{
			TRACE( "CMixerFader::OnMixerControlChanged mixerGetControlDetails error" );
			return 0L;
		}

		SetHVSliderPos();
	}

	return 0L;
}


//=============================================================================
//
// Descr. : Handler for scrolling event message sent whenever the slider is used. 
//          Called by a horizontal slider
//
//=============================================================================
void CMixerFader::HScroll ( UINT nSBCode, UINT /*nPos*/ )
{
	TRACE("HScroll\n");

	if( m_Value == NULL )
	{
		PopupErrorMsg( "Error: m_Value = NULL. Did you call Init() first?", "CMixerFader::VScroll"  );
		return;
	}
	if( nSBCode == TB_THUMBTRACK || nSBCode == TB_ENDTRACK || nSBCode == TB_PAGEDOWN || nSBCode == TB_PAGEUP )
	{
		SetFaderValue();
	}
}

//=============================================================================
//
// Descr. : Handler for scrolling event message sent whenever the slider is used. 
//          Called by a vertical slider
//
//=============================================================================
void CMixerFader::VScroll ( UINT nSBCode, UINT /*nPos*/ )
{
	TRACE("VScroll\n");
	
	if( m_Value == NULL )
	{
		PopupErrorMsg( "Error: m_Value = NULL. Did you call Init() first?", "CMixerFader::VScroll"  );
		return;
	}

	if( nSBCode == TB_THUMBTRACK || nSBCode == TB_ENDTRACK || nSBCode == TB_PAGEDOWN || nSBCode == TB_PAGEUP )
	{
		SetFaderValue();
	}
}


//<=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=>
// Name   : SetSliderPos
//          
// Descr. : we need to reverse the value for a vertical scrollbar
//          
// Return : void
// Arg    : int value : 
//------------------------------------------------------------------------------------------
void CMixerFader::SetSliderPos( int value )
{
	if( ( GetStyle( ) & TBS_VERT ) == TBS_VERT )
	{
		SetPos( SLIDER_SPAN - value );
	}
	else
	{
		SetPos( value );
	}
}

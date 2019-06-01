//=============================================================================
// Copyright Langis Pitre 1998
// You may do whatever you want with this code, as long as you include this
// copyright notice in your implementation files.
//=============================================================================
//=============================================================================
//                             CMixerSwitch
//
// Since this class is derived from CButton, it allows the user to associate
// a check box or radio button with a mixer switch control. All messages are
// handled internally through nessage reflection.
//
// How to use:
//
// 1) create a checkbox or radio button resource.
// 2) declare a variable of type CMixerSwitch in your CDialog-derived class
//    declaration
// 3) In your OnInitDialog, subclass the CMixerSwitch object to associate it
//    with the resource (or use DDE with a variable of type CMixerSwitch)
// 4) In your OnInitDialog, call the Init() member funcion.
//
// These switches work on both channels simutaneously.
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


CMixerSwitch::CMixerSwitch() : CMixerBase()
{
}

CMixerSwitch::~CMixerSwitch()
{
}


BEGIN_MESSAGE_MAP( CMixerSwitch, CButton )
	//{{AFX_MSG_MAP( CMixerSwitch )
	ON_CONTROL_REFLECT( BN_CLICKED, OnClicked )
	ON_MESSAGE( MM_MIXM_CONTROL_CHANGE, OnMixerControlChanged )
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
// Arg    : DWORD ControlType : type of desired switch.
//          These are valid arguments:
//
//              MIXERCONTROL_CONTROLTYPE_BOOLEAN 
//              MIXERCONTROL_CONTROLTYPE_ONOFF
//              MIXERCONTROL_CONTROLTYPE_MUTE
//              MIXERCONTROL_CONTROLTYPE_MONO
//              MIXERCONTROL_CONTROLTYPE_LOUDNESS
//              MIXERCONTROL_CONTROLTYPE_STEREOENH
//
//------------------------------------------------------------------------------------------
int CMixerSwitch::Init(  DWORD LineType, DWORD ControlType )
{	
	EnableWindow( FALSE );
	m_HasOnOff   = FALSE;

	if( (ControlType & MIXERCONTROL_CT_CLASS_MASK) != MIXERCONTROL_CT_CLASS_SWITCH )
	{
		PopupErrorMsg( "Wrong control type for an on-off control.", 
		            "CMixerSwitch::Init" );
		return 0;
	}

	MIXERLINE mixerLine;
	if( CMixerBase::Init( LineType, m_hWnd, mixerLine ) == 0 )
		return 0;
	
    MIXERLINECONTROLS   mixerLineControl;
    MIXERCONTROL        mixerControl;

	mixerLineControl.cbStruct       = sizeof( mixerLineControl );
	mixerLineControl.dwLineID       = mixerLine.dwLineID;
	mixerLineControl.dwControlType  = ControlType;
	mixerLineControl.cControls      = 1;
	mixerLineControl.cbmxctrl       = sizeof( mixerControl );
	mixerLineControl.pamxctrl       = &mixerControl;
	

	// ---------- We try and find a switch control for the mixer line -----------
	
	if( mixerGetLineControls( ( HMIXEROBJ )m_HMixer, &mixerLineControl, 
		                      MIXER_GETLINECONTROLSF_ONEBYTYPE ) 
							  != MMSYSERR_NOERROR )
	{
		PopupErrorMsg( "Could not find specified control.\r\nButton control will be disabled.", 
			        "CMixerSwitch::Init" );
		return 0;
	}

	// ---------- We get the switch control current value ----------------
	m_Control.cbStruct       = sizeof( m_Control );
    m_Control.dwControlID    = mixerControl.dwControlID;
    m_Control.cChannels      = 1; // for uniform controls
    m_Control.cMultipleItems = 0;
    m_Control.cbDetails      = sizeof( MIXERCONTROLDETAILS_BOOLEAN );
    m_Control.paDetails      = &m_Value;

    if( mixerGetControlDetails( ( HMIXEROBJ )m_HMixer, &m_Control, 
	                            MIXER_GETCONTROLDETAILSF_VALUE ) 
								!= MMSYSERR_NOERROR )
    {
		PopupErrorMsg( "mixerGetControlDetails failed.", 
			        "CMixerSwitch::Init" );
		return 0;
    }

	m_HasOnOff = TRUE;

	EnableWindow( TRUE );
	SetCheck( m_Value.fValue );

	return 1;
}


//=============================================================================
// Name   : OnMixerControlChanged
//          
// Descr. : Message handler called whenever the MCI device sends the MM_MIXM_CONTROL_CHANGE
//          message. The MCI mixer device will send this message for any changing
//          setting, so we need to check that the MCI control that sent the message
//          corresponds to the current mixer control.
//          
// Return : LONG
// Arg    : UINT         : 
// Arg    : LONG message : 
//=============================================================================
LONG CMixerSwitch::OnMixerControlChanged( UINT, LONG message )
{
	UINT id = ( UINT )message;

	if( id == m_Control.dwControlID )
	{
		if( mixerGetControlDetails( ( HMIXEROBJ )m_HMixer, &m_Control, 
			                          MIXER_GETCONTROLDETAILSF_VALUE ) 
									  != MMSYSERR_NOERROR )
		{
			TRACE( "CMixerSwitch::OnMixerControlChanged mixerGetControlDetails failed." );
			return 0L;
		}
		SetCheck( m_Value.fValue );
	}

	return 0L;
}

//=============================================================================
// Name   : OnClicked
//          
// Descr. : button callback reflected message. Switches the mixer control off/on
//          
// Return : void
//=============================================================================
void CMixerSwitch::OnClicked()
{
	if( m_HasOnOff == TRUE )
	{
		m_Value.fValue = !m_Value.fValue;
		SetCheck( m_Value.fValue );

		mixerSetControlDetails( ( HMIXEROBJ )m_HMixer, &m_Control, 
			                    MIXER_SETCONTROLDETAILSF_VALUE );
	}
	else
	{
		PopupErrorMsg( "No Sound card present, or no mixer switch capability\r\n"
		               "Did you call Init() first?", 
		            "CMixerSwitch::OnClicked" );
	}
}
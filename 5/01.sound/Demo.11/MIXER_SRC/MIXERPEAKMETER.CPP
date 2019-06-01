//=============================================================================
// Copyright Langis Pitre 1998
// You may do whatever you want with this code, as long as you include this
// copyright notice in your implementation files.
//=============================================================================
//=============================================================================
//                             CMixerPeakMeter
//
// Since this class is derived from CStatic, it allows the user to associate
// a static resource with a mixer peak meter control. All messages are handled
// internally through nessage reflection.
//
// How to use:
//
// 1) create a static resource (specify a resource ID other than IDC_STATIC)
//    You can give it the Sunken style if you wish.
// 2) declare a variable of type CMixerPeakMeter in your CDialog-derived
//    class declaration
// 3) In your OnInitDialog, subclass the CMixerPeakMeter object to associate it
//    with the resource (or use DDE with a variable of type CMixerPeakMeter)
// 4) In your OnInitDialog, call the Init() member funcion.
//
// The peak meter works like the CProgressCtrl, except that it is vertical.
// It displays the audio level of the line it is associated with.
//
//=============================================================================
//=============================================================================
//=============================================================================
#include "stdafx.h"
#include "MixerClasses.h"
#include "MemDC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMixerPeakMeter

CMixerPeakMeter::CMixerPeakMeter(COLORREF background ) : CMixerBase()
{
    m_Bkgnd = background;
	m_Value.lValue = 0;
}

CMixerPeakMeter::~CMixerPeakMeter()
{
}


BEGIN_MESSAGE_MAP( CMixerPeakMeter, CStatic )
	//{{AFX_MSG_MAP(CMixerPeakMeter)
	ON_WM_PAINT()
	ON_MESSAGE( MM_MIXM_LINE_CHANGE, OnMixerLineChanged )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


//<=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=>
// Name   : Init
//          
// Descr. : Initializes the mixer control.
//          Init queries the mixer device for the specified mixer control type,
//          which is always MIXERCONTROL_CONTROLTYPE_PEAKMETER in this case.
//          If such a control is found, its current value is queried, and used
//          to initialize the windows control.
//          
// Return : int
// Arg    : DWORD LineType    : see definition of MixerBase::Init() for a description
//          
//------------------------------------------------------------------------------------------
int CMixerPeakMeter::Init( DWORD LineType )
{		
	EnableWindow( FALSE );

	MIXERLINE mixerLine;
	if( CMixerBase::Init( LineType, GetSafeHwnd(), mixerLine ) == 0 )
		return 0;

    MIXERLINECONTROLS   mixerLineControl;
    MIXERCONTROL        mixerControl;

	mixerLineControl.cbStruct       = sizeof( MIXERLINECONTROLS );
	mixerLineControl.dwLineID       = mixerLine.dwLineID;
	mixerLineControl.dwControlType  = MIXERCONTROL_CONTROLTYPE_PEAKMETER;
	mixerLineControl.cControls      = 1;
	mixerLineControl.cbmxctrl       = sizeof( MIXERCONTROL );
	mixerLineControl.pamxctrl       = &mixerControl;
	

	// ---------- We try and find a peak meter control for the mixer line -----------
	
	if( mixerGetLineControls( ( HMIXEROBJ )m_HMixer, &mixerLineControl,
	                          MIXER_GETLINECONTROLSF_ONEBYTYPE ) != MMSYSERR_NOERROR )
	{
		PopupErrorMsg( "Get peak meter failed", "CMixerPeakMeter::Init" );
		return 0;
	}


	// ---------- We get the control current value ----------------
	m_Control.cbStruct       = sizeof( m_Control );
    m_Control.dwControlID    = mixerControl.dwControlID;
    m_Control.cChannels      = 1;
    m_Control.cMultipleItems = 0;
    m_Control.cbDetails      = sizeof( MIXERCONTROLDETAILS_SIGNED );
    m_Control.paDetails      = &m_Value;

    if( mixerGetControlDetails( ( HMIXEROBJ )m_HMixer, &m_Control, 
	                            MIXER_GETCONTROLDETAILSF_VALUE ) != MMSYSERR_NOERROR )
    {
		PopupErrorMsg( "Peak meter query failed", "CMixerPeakMeter::Init" );
		return 0;
    }

	m_LineID = mixerLine.dwLineID;
	
	return 1;
}

//=============================================================================
// Name   : OnMixerLineChanged
//          
// Descr. : Message handler called whenever the MCI device sends the MM_MIXM_LINE_CHANGE
//          message. If the line is active, it calls DrawMeter() to redraw the
//          windows control.
//          
// Return : LONG
// Arg    : UINT   mix  : handle of mixer device that sent the message
// Arg    : LONG LineID : id of the active line
//=============================================================================
LONG CMixerPeakMeter::OnMixerLineChanged( UINT hMix, LONG LineID )
{
	CClientDC dc(this);
	
	TRACE( "OnMixerLineChanged called.\n" );

	MSG msg;

	MIXERLINE line;
	line.cbStruct = sizeof( MIXERLINE );
	line.dwLineID = m_LineID;

	// check if the line is the one associated with the wave out audio
	if( m_LineID == (DWORD)LineID)
	{
		do // while the line is active, get the peak meter value
		{
			// get the current peak meter value
			if( mixerGetControlDetails( ( HMIXEROBJ )hMix, &m_Control, 
			                              MIXER_GETCONTROLDETAILSF_VALUE ) 
										  != MMSYSERR_NOERROR )
			{
				TRACE("CMixerPeakMeter::OnMixerLineChanged returned an error.\n");
				return 0;
			}
			
			// the loop could be long, process messages ao avoid freezing
			while( ::PeekMessage(&msg, NULL, 0,0, PM_REMOVE) )
			{
				::TranslateMessage(&msg); 
				::DispatchMessage( &msg);
			}
			DrawMeter(&dc);
			
			// get the line info to see if the line is still active
			if( mixerGetLineInfo( ( HMIXEROBJ )hMix, &line, 
				                  MIXER_GETLINEINFOF_LINEID ) != MMSYSERR_NOERROR )
			{
				TRACE( "OnMixerLineChanged: Error querying audio line." );
				return 0;
			}
		}
		while( (line.fdwLine & MIXERLINE_LINEF_ACTIVE) /*&& m_Value.lValue != 0*/ );
	}
	
	return 1L;
}



//<=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=>
// Name   : OnPaint
//          
// Descr. : 
//          
// Return : void
//------------------------------------------------------------------------------------------
void CMixerPeakMeter::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	DrawMeter( &dc );
}


//<=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=>
// Name   : DrawMeter
//          
// Descr. : Draws the windows control (static control). Draws a series of rectangles, up
//          to the current value. Since the value of the peak meter mixer control ranges from
//          -32,768 to 32,767, only the positive values are used, and these values are mapped
//          to fall between 0 and NSTEPS. Thus, a maximum of NSTEPS-1 rectangles will be drawn.
//          
// Return : void
// Arg    : CDC *pDC : 
//------------------------------------------------------------------------------------------
void CMixerPeakMeter::DrawMeter( CDC *pDC )
{
	const int NSTEPS = 10;
	CRect r;
	GetClientRect( &r );

	int rHeight = r.Height() / NSTEPS;
	int rWidth  = r.Width();
	
	// the peak meter range is -32,768 to 32,767
	if( m_Value.lValue >= 0 )
	{
		CMemDC mdc( pDC, r );
		
		mdc.FillSolidRect( r, m_Bkgnd );
		
		int value = int( m_Value.lValue * NSTEPS / 32768 );

		TRACE("DrawMeter - value: %lu\n", value);

		// draw a series of rectangles from green to red
		for( int i = 0; i < value; i++ )
		{
			mdc.FillSolidRect( 0, (NSTEPS - i) * rHeight, r.Width(), rHeight-1,
							   RGB( i*255/NSTEPS, 255 - i*255/NSTEPS, 0 ) );
		}	
	}
}

//=============================================================================
// Copyright Langis Pitre 1998
// You may do whatever you want with this code, as long as you include this
// copyright notice in your implementation files.
//=============================================================================
//=============================================================================
//                             CMixerSelector
//
// This class allows the user to associate one or more CheckBoxes with a mixer
// selector control. Selectors are used to select one or more input audio line
// associated with a given output line. For example, my SoundBlaster enables
// the selection of the CD audio, microphone, and line-in input lines associated
// with the speakers' output line.
//
// Selectors are multiple mixer controls. Each item of the control is a boolean
// value. For each item in the CMixerSelector object, you shoud have a BOOL
// variable (associated with a CheckBox or radio button for example) in your program.
//
// Since several checkboxes (even just boolean variables for that matter)
// can be used to interface with the selector, the CMixerSelector works differently
// than the other CMixerBase-derived classes.
// It is not subclassed from a window's control. Instead, it sends the
// MIXER_SELECTOR_CHANGED message to its parent window, which must handle the
// message to update its ckeckboxes (or variables).
//
// How to use:
//
// 1) Declare a variable of type CMixerSelector in your CDialog-derived class
//    declaration
// 2) call the Init() member funcion.
// 3) Your window class must also have a message map entry and a handler
//    for the MIXER_SELECTOR_CHANGED message:
//
//      ON_MESSAGE( MIXER_SELECTOR_CHANGED, <Callback_Function> )
//
//	    afx_msg LONG Callback_Function( UINT, LONG );
//
//    In the callback function, update your checkboxes or variables by using
//    CMixerSelector::GetItemValue()
//
// 4) When one of your BOOL variables changes, call CMixerSelector::SetItemValue()
//    to update the selector.
//    If you use checkboxes or radio buttons, provide one or several callback
//    functions to tell the CMixerSelector object that your controls have
//    changed state.
//    In the callbacks, use CMixerSelector::SetItemValue() to update the selector.
//
// These controls work on both channels simutaneously.
//
//=============================================================================
//=============================================================================
//=============================================================================

#include "stdafx.h"
#include "MixerClasses.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMixerSelector::CMixerSelector() : CMixerBase()
{
	m_Value = NULL;
}

CMixerSelector::~CMixerSelector()
{
	DestroyWindow();

	if(m_Value)
		delete[] m_Value;
}


BEGIN_MESSAGE_MAP(CMixerSelector, CWnd)
	//{{AFX_MSG_MAP(CMixerSelector)
	ON_MESSAGE( MM_MIXM_CONTROL_CHANGE, OnMixerControlChanged )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


//<=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=>
// Name   : Init
//          
// Descr. : Initializes the mixer control.
//          Init queries the mixer device for the specified mixer control type.
//          If such a control is found, its current value is queried, and the
//          MIXER_SELECTOR_CHANGED message is sent to the parent window.
//          
// Return : int
// Arg    : DWORD LineType    : see definition of MixerBase::Init() for a description
// Arg    : DWORD ControlType : type of desired selector.
//                              These are valid arguments:
//
//              MIXERCONTROL_CONTROLTYPE_SINGLESELECT 
//              MIXERCONTROL_CONTROLTYPE_MUX
//              MIXERCONTROL_CONTROLTYPE_MULTIPLESELECT
//              MIXERCONTROL_CONTROLTYPE_MIXER
//
// Arg    : CWnd* parent      : pointer to the parent CWnd object. This argument must not
//                              be NULL
//------------------------------------------------------------------------------------------
int CMixerSelector::Init( DWORD LineType, DWORD ControlType, CWnd* parent)
{	
	if( parent == NULL )
	{
		PopupErrorMsg(  "Selectors must have a parent window.", 
		                       "CMixerSelector::Init"  );
		return 0;
	}

	if( (ControlType & MIXERCONTROL_CT_CLASS_MASK) != MIXERCONTROL_CT_CLASS_LIST )
	{
		PopupErrorMsg(  "Wrong control type for multiple-selection control.", 
		                       "CMixerSwitch::Init"  );
		return 0;
	}

	// create an invisible window for handling mixer messages
	if( Create( NULL, "", NULL, CRect(0,0,0,0), parent, 0 ) == FALSE )
	{
		PopupErrorMsg(  "Error creating invisible window for selector.", 
		                       "CMixerSelector::Init"  );
		return 0;
	}
	
	MIXERLINE mixerLine;
	if ( CMixerBase::Init( LineType, GetSafeHwnd(), mixerLine ) == 0 )
		return 0;

    MIXERLINECONTROLS   mixerLineControl;
    MIXERCONTROL        mixerControl;

	mixerLineControl.cbStruct       = sizeof( mixerLineControl );
	mixerLineControl.dwLineID       = mixerLine.dwLineID;
	mixerLineControl.dwControlType  = ControlType;
	mixerLineControl.cControls      = 1;
	mixerLineControl.cbmxctrl       = sizeof( mixerControl );
	mixerLineControl.pamxctrl       = &mixerControl;
	
	// ---------- We try and find a mixer (multiple) control for the mixer line -----------
	
	if( mixerGetLineControls( ( HMIXEROBJ )m_HMixer, &mixerLineControl, 
	                          MIXER_GETLINECONTROLSF_ONEBYTYPE ) 
							  != MMSYSERR_NOERROR )
	{
		PopupErrorMsg(  "Get selector failed", "CMixerSelector::Init"  );
		return 0;
	}

	if( mixerControl.fdwControl & MIXERCONTROL_CONTROLF_UNIFORM )
	{
		m_Control.cChannels = 1;
		nItems = mixerControl.cMultipleItems;
	}
	else
	{
		m_Control.cChannels = mixerLine.cChannels;
		nItems = mixerControl.cMultipleItems*m_nChannels;
	}

	m_Value = new MIXERCONTROLDETAILS_BOOLEAN[nItems];
	if( m_Value == NULL )
	{
		PopupErrorMsg( "Memory allocation error.", "CMixerSelector::Init"  );
		return 0;
	}

	// ---------- We get the selector control current value ----------------
	m_Control.cbStruct       = sizeof( m_Control );
    m_Control.dwControlID    = mixerControl.dwControlID;
    m_Control.cMultipleItems = mixerControl.cMultipleItems;
    m_Control.cbDetails      = sizeof( MIXERCONTROLDETAILS_BOOLEAN );
    m_Control.paDetails      = m_Value;

    if( mixerGetControlDetails( ( HMIXEROBJ )m_HMixer, &m_Control, 
	                            MIXER_GETCONTROLDETAILSF_VALUE ) 
								!= MMSYSERR_NOERROR )
    {
		PopupErrorMsg(  "Selector Details failed.", "CMixerSelector::Init"  );
		return 0;
    }
	::PostMessage( GetParent()->GetSafeHwnd(), MIXER_SELECTOR_CHANGED, 0, 0 );

	return 1;
}

//=============================================================================
// Name   : OnMixerControlChanged
//          
// Descr. : Message handler called whenever the MCI device sends the MM_MIXM_CONTROL_CHANGE
//          message. The MCI mixer device will send this message for any changing
//          setting, so we need to check that the MCI control that sent the message
//          corresponds to the current selector control.
//          
// Return : LONG
// Arg    : UINT         : 
// Arg    : LONG message : 
//=============================================================================
LONG CMixerSelector::OnMixerControlChanged( UINT, LONG message )
{
	UINT id = ( UINT )message;

	if( id == m_Control.dwControlID ) // query the new value
	{
		if( mixerGetControlDetails( ( HMIXEROBJ )m_HMixer, &m_Control, 
		                            MIXER_GETCONTROLDETAILSF_VALUE ) 
									!= MMSYSERR_NOERROR )
		{
			return 0;
		}
		::PostMessage( GetParent()->GetSafeHwnd(), MIXER_SELECTOR_CHANGED, 0, 0 );
	}

	return 0L;
}


//<=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=>
// Name   : SetItemValue
//          
// Descr. : Call this function to update one of the items in the selector.
//          
// Return : int
// Arg    : int index  : index of the item to update.
// Arg    : BOOL value : new value desired for item
//------------------------------------------------------------------------------------------
int CMixerSelector::SetItemValue( int index, BOOL value )
{
	if( m_Value == NULL )
	{
		PopupErrorMsg(  "Value is NULL. Make sure Init() is called first.", "CMixerSelector::SetItemValue" );
		return 0;
	}

	if( ( index >= nItems ) || index < 0  )
	{
		PopupErrorMsg(  "Invalid index passed.", "CMixerSelector::SetItemValue" );
		return 0;
	}

	m_Value[index].fValue = value;

	if( mixerSetControlDetails( ( HMIXEROBJ )m_HMixer, &m_Control,
	                            MIXER_SETCONTROLDETAILSF_VALUE ) 
								!= MMSYSERR_NOERROR )
	{
		return 0;
	}

	return 1;
}


//<=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=>
// Name   : GetItemValue
//          
// Descr. : Use this function to query the current state of a selector item.
//          
// Return : BOOL : current value of selector item
// Arg    : int index : index of item to query
//------------------------------------------------------------------------------------------
BOOL CMixerSelector::GetItemValue( int index )
{
	if( m_Value == NULL )
	{
		PopupErrorMsg(  "Value is NULL. Make sure Init() is called first.", "CMixerSelector::GetItemValue" );
		return FALSE;
	}
	if( ( index >= nItems ) || index < 0  )
	{
		PopupErrorMsg(  "Invalid index passed.", "CMixerSelector::GetItemValue" );
		return FALSE;
	}
	return (m_Value[index].fValue);
}


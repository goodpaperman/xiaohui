//=============================================================================
// Copyright Langis Pitre 1998
// You may do whatever you want with this code, as long as you include this
// copyright notice in your implementation files.
//=============================================================================
//=============================================================================
//                         CMixerBase Class
//
// Base class of all the mixer classes
// Takes care of opening the mixer device to get a valid handler.
// This handle, along with the number of channels are stored in
// member variables.
//
//=============================================================================
//=============================================================================
#include "stdafx.h"
#include "MixerClasses.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CMixerBase::CMixerBase()
{
	m_HMixer = 0;
}

CMixerBase::~CMixerBase()
{
	if ( m_HMixer )
		mixerClose( m_HMixer );
}


//<=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=>
// Name   : Init
//          
// Descr. : Opens the mixer device and retrieves its handle. Queries the mixer device for
//          the desired component (Mixer Line) type. This component type corresponds to the
//          type of audio line to access. Called by the derived classes (protected).
//          
// Return : int 1 if successful, 0 otherwise
// Arg    : DWORD LineType           : component type
//          
//          These are valid arguments (if available):
//
//            Destination lines:
//
//              MIXERLINE_COMPONENTTYPE_DST_DIGITAL 
//              MIXERLINE_COMPONENTTYPE_DST_LINE
//              MIXERLINE_COMPONENTTYPE_DST_MONITOR
//              MIXERLINE_COMPONENTTYPE_DST_SPEAKERS
//              MIXERLINE_COMPONENTTYPE_DST_HEADPHONES
//              MIXERLINE_COMPONENTTYPE_DST_TELEPHONE 
//              MIXERLINE_COMPONENTTYPE_DST_WAVEIN
//              MIXERLINE_COMPONENTTYPE_DST_MONITOR
//              MIXERLINE_COMPONENTTYPE_DST_VOICEIN
//
//            Source lines:
//
//              MIXERLINE_COMPONENTTYPE_SRC_DIGITAL 
//              MIXERLINE_COMPONENTTYPE_SRC_LINE
//              MIXERLINE_COMPONENTTYPE_SRC_MICROPHONE
//              MIXERLINE_COMPONENTTYPE_SRC_SYNTHESIZER
//              MIXERLINE_COMPONENTTYPE_SRC_COMPACTDISC
//              MIXERLINE_COMPONENTTYPE_SRC_TELEPHONE 
//              MIXERLINE_COMPONENTTYPE_SRC_PCSPEAKER
//              MIXERLINE_COMPONENTTYPE_SRC_WAVEOUT
//              MIXERLINE_COMPONENTTYPE_SRC_AUXILIARY
//              MIXERLINE_COMPONENTTYPE_SRC_ANALOG

// Arg    : HWND hwnd            : handle of window that will handle mixer specific messages
//                                 this handle is supplied by the derived classes.
// Arg    : MIXERLINE &mixerLine : reference to MIXERLINE structure that will receive the
//                                 queried information.
//------------------------------------------------------------------------------------------
int CMixerBase::Init( DWORD LineType, HWND hwnd, MIXERLINE &mixerLine )
{	
	UINT nbMixers = mixerGetNumDevs();
	if( nbMixers < 1 )
	{
		PopupErrorMsg(  "No mixer device present", "CMixerBase::Init" );
		return 0;
	}
	//TRACE( "nbMixers = %d\n", nbMixers );

	if( mixerOpen( &m_HMixer, 0, ( DWORD )hwnd, 0, CALLBACK_WINDOW ) != MMSYSERR_NOERROR )
	{
		PopupErrorMsg(  "Could not open mixer device", "CMixerBase::Init" );
		return 0;
	}
	TRACE( "m_HMixer = %d\n", m_HMixer );

	// ----- We try and find an audio mixer line of the specified type, get its ID,
	// ----- and check if there are controls associated with this line
	
	mixerLine.cbStruct = sizeof( MIXERLINE );
	mixerLine.dwComponentType = LineType;

	if( mixerGetLineInfo( ( HMIXEROBJ )m_HMixer, &mixerLine, 
	                      MIXER_GETLINEINFOF_COMPONENTTYPE ) != MMSYSERR_NOERROR )
	{
		PopupErrorMsg(  "Error querying audio line for the specified component type.", 
			                   "CMixerBase::Init" );
		return 0;
	}
	m_nChannels = mixerLine.cChannels;

	if( mixerLine.cControls == 0 )
	{
		PopupErrorMsg(  "No controls available for this audio line.", 
			                   "CMixerBase::Init" );
		return 0;
	}
	//TRACE( "Nunber of controls available: %d\n", mixerLine.cControls );

	return 1;
}

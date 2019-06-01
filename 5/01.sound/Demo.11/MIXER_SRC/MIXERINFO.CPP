//=============================================================================
// Copyright Langis Pitre 1998
// You may do whatever you want with this code, as long as you include this
// copyright notice in your implementation files.
//=============================================================================
//  MixerInfo.cpp
//
// Utility function to list all available options of your mixer device interface
//
//=============================================================================
#include "stdafx.h"
#include "MixerInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Helper functions used by GetDevicesInfo
static void PrintLineComponentType( int nIndent, MIXERLINE &line, FILE *file );
static void PrintControl( HMIXEROBJ mixer, MIXERLINE &line, MIXERCONTROL &control, FILE *file );

//=============================================================================
// Name   : GetDevicesInfo
//          
// Descr. : Finds all the input and output lines, and all mixer controls
//          available through the audio mixer device.
//
//          Use GetDevicesInfo() to find out the capabilities of your sound card.
//          Check the the file and note the type and number of destination (output)
//          lines, as well as the source (input) lines associated with every
//          destination line. Note also the type of the controls available.
//          You will need these to create your windows controls.
//          
// Return : void
// Arg    : LPCSTR filename : 
//=============================================================================
void GetDevicesInfo( LPCSTR filename )
{
	FILE *file;
	
	UINT nbMixers = mixerGetNumDevs();
	if( nbMixers < 1 )
	{
		AfxMessageBox( "No mixer device present" );
		return;
	}

	HMIXER hMixer;
	if( mixerOpen( &hMixer, 0, 0, 0, 0 ) != MMSYSERR_NOERROR )
	{
		AfxMessageBox( "Could not open mixer device" );
		return;
	}

	file = fopen( filename, "w" );
	if( file == NULL )
	{
		AfxMessageBox("Could not open file.");
		return;
	}

	MIXERCAPS caps;
	if( mixerGetDevCaps( ( UINT )hMixer, &caps, sizeof( MIXERCAPS ) ) != MMSYSERR_NOERROR )
	{
		fclose( file );
		return;
	}
	fprintf( file, "Name of device: %s\n", caps.szPname );
	fprintf( file, "Number of destination lines: %d\n\n", caps.cDestinations );
	fprintf( file, "\nPay particular attention to the \"Component type\" and \"Control type\" lines.\n"
	               "You will pass these to the Init() functions of the various CMixerBase-derived classes\n"
				   "to specify which type of control you want to use.\n");

	MIXERLINE line;
    MIXERLINECONTROLS   mixerLineControl;
    MIXERCONTROL        *pMixerControl;


	int nDest = caps.cDestinations;
	for( int i = 0; i < nDest; i++ )
	{

		line.cbStruct = sizeof( MIXERLINE );
		line.dwSource = 0;
		line.dwDestination = i;
		mixerGetLineInfo( ( HMIXEROBJ )hMixer, &line, MIXER_GETLINEINFOF_DESTINATION );
		
		fprintf( file, "\n***************************************************************************************************\n");
		fprintf( file, "** Destination line. Index = %d  *******************************************************************\n", i );
		fprintf( file, "***************************************************************************************************\n");
		PrintLineComponentType( 0, line, file );

		pMixerControl = new MIXERCONTROL[line.cControls];
		ASSERT( pMixerControl != NULL );
		mixerLineControl.cbStruct  = sizeof( MIXERLINECONTROLS );
		mixerLineControl.dwLineID  = line.dwLineID;
		mixerLineControl.cControls = line.cControls;
		mixerLineControl.cbmxctrl  = sizeof( MIXERCONTROL );
		mixerLineControl.pamxctrl  = pMixerControl;
		
		mixerGetLineControls( ( HMIXEROBJ )hMixer, &mixerLineControl, MIXER_GETLINECONTROLSF_ALL );
		
		UINT ncontrols = line.cControls;
		for( UINT k = 0; k < ncontrols; k++ )
		{
			PrintControl( ( HMIXEROBJ )hMixer, line, pMixerControl[k], file );
		}
		
		delete[] pMixerControl;
		
		
		// for each destination line, list the source lines and their controls
		UINT nconn = line.cConnections;
		for( UINT j = 0; j < nconn; j++ )
		{
			line.cbStruct = sizeof( MIXERLINE );
			line.dwSource = j;
			line.dwDestination = i;
			mixerGetLineInfo( ( HMIXEROBJ )hMixer, &line, MIXER_GETLINEINFOF_SOURCE );
			
			fprintf( file,  "\n\t======================================================================================\n");
			fprintf( file,  "\t== Source line. Index = %d ===========================================================\n", j );
			fprintf( file,  "\t======================================================================================\n");
			PrintLineComponentType( 1, line, file );
		
			pMixerControl = new MIXERCONTROL[line.cControls];
			ASSERT( pMixerControl != NULL );
			mixerLineControl.cbStruct  = sizeof( MIXERLINECONTROLS );
			mixerLineControl.dwLineID  = line.dwLineID;
			mixerLineControl.cControls = line.cControls;
			mixerLineControl.cbmxctrl  = sizeof( MIXERCONTROL );
			mixerLineControl.pamxctrl  = pMixerControl;
			
			mixerGetLineControls( ( HMIXEROBJ )hMixer, &mixerLineControl, MIXER_GETLINECONTROLSF_ALL );
			
			UINT ncontrols = line.cControls;
			for( UINT k = 0; k < ncontrols; k++ )
			{
				PrintControl( ( HMIXEROBJ )hMixer, line, pMixerControl[k], file );
			}

			delete[] pMixerControl;
		}
	}
	fclose( file );
}


//<=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=>
// Name   : PrintLineComponentType
//          
// Descr. : 
//          
// Return : void
// Arg    : MIXERLINE &line : 
// Arg    : FILE *file      : 
//------------------------------------------------------------------------------------------
void PrintLineComponentType( int nIndent, MIXERLINE &line, FILE *file )
{
	char *tabs;
	if( nIndent == 0 )
		tabs = "";
	else
		tabs = "\t";

	fprintf( file, "%s -----------------------------------------------------------------------\n", tabs );
	fprintf( file, "%s Component type :", tabs );

	switch( line.dwComponentType )
	{
		case MIXERLINE_COMPONENTTYPE_DST_DIGITAL:
			fprintf( file, "%s MIXERLINE_COMPONENTTYPE_DST_DIGITAL\n", tabs );
			fprintf( file, "%s -----------------------------------------------------------------------\n", tabs );
			fprintf( file, "%s Audio line is a digital destination (for example, digital input to a DAT or CD audio device).\n", tabs );
			break;
		case MIXERLINE_COMPONENTTYPE_DST_UNDEFINED:
			fprintf( file, "%s MIXERLINE_COMPONENTTYPE_DST_UNDEFINED\n", tabs );
			fprintf( file, "%s -----------------------------------------------------------------------\n", tabs );
			fprintf( file,  "%s Audio line is a destination that cannot be defined by one of the standard component types.\n", tabs );
			break;
		case MIXERLINE_COMPONENTTYPE_DST_LINE:
			fprintf( file, "%s MIXERLINE_COMPONENTTYPE_DST_LINE\n", tabs);
			fprintf( file, "%s -----------------------------------------------------------------------\n", tabs );
			fprintf( file,  "%s Audio line is a line level destination that will be the final recording source for the analog-to-digital converter (ADC).\n", tabs );
			break;
		case MIXERLINE_COMPONENTTYPE_DST_MONITOR:
			fprintf( file, "%s MIXERLINE_COMPONENTTYPE_DST_MONITOR\n", tabs);
			fprintf( file, "%s -----------------------------------------------------------------------\n", tabs );
			fprintf( file,  "%s Audio line is a destination used for a monitor.\n", tabs );
			break;
		case MIXERLINE_COMPONENTTYPE_DST_SPEAKERS:
			fprintf( file, "%s MIXERLINE_COMPONENTTYPE_DST_SPEAKERS\n", tabs);
			fprintf( file, "%s -----------------------------------------------------------------------\n", tabs );
			fprintf( file,  "%s Audio line is an adjustable (gain and/or attenuation) destination intended to drive speakers.\n", tabs );
			break;
		case MIXERLINE_COMPONENTTYPE_DST_HEADPHONES:
			fprintf( file, "%s MIXERLINE_COMPONENTTYPE_DST_HEADPHONES\n", tabs);
			fprintf( file, "%s -----------------------------------------------------------------------\n", tabs );
			fprintf( file,  "%s Audio line is an adjustable (gain and/or attenuation) destination intended to drive headphones.\n", tabs );
			break;
		case MIXERLINE_COMPONENTTYPE_DST_TELEPHONE:
			fprintf( file, "%s MIXERLINE_COMPONENTTYPE_DST_TELEPHONE\n", tabs);
			fprintf( file, "%s -----------------------------------------------------------------------\n", tabs );
			fprintf( file,  "%s Audio line is a destination that will be routed to a telephone line.\n", tabs );
			break;
		case MIXERLINE_COMPONENTTYPE_DST_WAVEIN:
			fprintf( file, "%s MIXERLINE_COMPONENTTYPE_DST_WAVEIN\n", tabs);
			fprintf( file, "%s -----------------------------------------------------------------------\n", tabs );
			fprintf( file,  "%s Audio line is a destination that will be the final recording source for the waveform-audio input (ADC).\n", tabs );
			break;
		case MIXERLINE_COMPONENTTYPE_DST_VOICEIN:
			fprintf( file, "%s MIXERLINE_COMPONENTTYPE_DST_VOICEIN\n", tabs);
			fprintf( file, "%s -----------------------------------------------------------------------\n", tabs );
			fprintf( file,  "%s Audio line is a destination that will be the final recording source for voice input.\n", tabs );
			break;
		case MIXERLINE_COMPONENTTYPE_SRC_ANALOG:
			fprintf( file, "%s MIXERLINE_COMPONENTTYPE_SRC_ANALOG\n", tabs);
			fprintf( file, "%s -----------------------------------------------------------------------\n", tabs );
			fprintf( file,  "%s Audio line is an analog source (for example, analog output from a video-cassette tape).\n", tabs );
			break;
		case MIXERLINE_COMPONENTTYPE_SRC_AUXILIARY:
			fprintf( file, "%s MIXERLINE_COMPONENTTYPE_SRC_AUXILIARY\n", tabs);
			fprintf( file, "%s -----------------------------------------------------------------------\n", tabs );
			fprintf( file,  "%s Audio line is a source originating from the auxiliary audio line.\n", tabs );
			break;
		case MIXERLINE_COMPONENTTYPE_SRC_COMPACTDISC:
			fprintf( file, "%s MIXERLINE_COMPONENTTYPE_SRC_COMPACTDISC\n", tabs);
			fprintf( file, "%s -----------------------------------------------------------------------\n", tabs );
			fprintf( file,  "%s Audio line is a source originating from the output of an internal audio CD.\n", tabs );
			break;
		case MIXERLINE_COMPONENTTYPE_SRC_DIGITAL:
			fprintf( file, "%s MIXERLINE_COMPONENTTYPE_SRC_DIGITAL\n", tabs);
			fprintf( file, "%s -----------------------------------------------------------------------\n", tabs );
			fprintf( file,  "%s Audio line is a digital source (for example, digital output from a DAT or audio CD).\n", tabs );
			break;
		case MIXERLINE_COMPONENTTYPE_SRC_LINE:
			fprintf( file, "%s MIXERLINE_COMPONENTTYPE_SRC_LINE\n", tabs);
			fprintf( file, "%s -----------------------------------------------------------------------\n", tabs );
			fprintf( file,  "%s Audio line is a line-level source (for example, line-level input from an external stereo).\n", tabs );
			break;
		case MIXERLINE_COMPONENTTYPE_SRC_MICROPHONE:
			fprintf( file, "%s MIXERLINE_COMPONENTTYPE_SRC_MICROPHONE\n", tabs);
			fprintf( file, "%s -----------------------------------------------------------------------\n", tabs );
			fprintf( file,  "%s Audio line is a microphone recording source.\n", tabs );
			break;
		case MIXERLINE_COMPONENTTYPE_SRC_PCSPEAKER:
			fprintf( file, "%s MIXERLINE_COMPONENTTYPE_SRC_PCSPEAKER\n", tabs);
			fprintf( file, "%s -----------------------------------------------------------------------\n", tabs );
			fprintf( file,  "%s Audio line is a source originating from personal computer speaker.\n", tabs );
			break;
		case MIXERLINE_COMPONENTTYPE_SRC_SYNTHESIZER:
			fprintf( file, "%s MIXERLINE_COMPONENTTYPE_SRC_SYNTHESIZER\n", tabs);
			fprintf( file, "%s -----------------------------------------------------------------------\n", tabs );
			fprintf( file,  "%s Audio line is a source originating from the output of an internal synthesizer.\n", tabs );
			break;
		case MIXERLINE_COMPONENTTYPE_SRC_TELEPHONE:
			fprintf( file, "%s MIXERLINE_COMPONENTTYPE_SRC_TELEPHONE\n", tabs);
			fprintf( file, "%s -----------------------------------------------------------------------\n", tabs );
			fprintf( file,  "%s Audio line is a source originating from an incoming telephone line.\n", tabs );
			break;
		case MIXERLINE_COMPONENTTYPE_SRC_UNDEFINED:
			fprintf( file, "%s MIXERLINE_COMPONENTTYPE_SRC_UNDEFINED\n", tabs);
			fprintf( file, "%s -----------------------------------------------------------------------\n", tabs );
			fprintf( file,  "%s Audio line is a source that cannot be defined by one of the standard component types.\n", tabs );
			break;
		case MIXERLINE_COMPONENTTYPE_SRC_WAVEOUT:
			fprintf( file, "%s MIXERLINE_COMPONENTTYPE_SRC_WAVEOUT\n", tabs);
			fprintf( file, "%s -----------------------------------------------------------------------\n", tabs );
			fprintf( file,  "%s Audio line is a source originating from the waveform-audio output digital-to-analog converter (DAC).\n", tabs );
			break;
		default:
			fprintf( file, "\n" );
	}
	
	fprintf( file,  "%s Name: %s\n", tabs, line.szName );
	fprintf( file,  "%s Short Name: %s\n\n", tabs, line.szShortName );

	switch( line.fdwLine )
	{
		case MIXERLINE_LINEF_ACTIVE:
			fprintf( file,  "%s Audio line is active.  signal is probably passing through the line.\n", tabs );
			break;
		case MIXERLINE_LINEF_DISCONNECTED:
			fprintf( file,  "%s Audio line is disconnected.\n", tabs );
			break;
		case MIXERLINE_LINEF_SOURCE:
			fprintf( file,  "%s Audio line is an audio source line associated with a single audio destination line.\n", tabs );
			break;
	}


	if( line.Target.dwType != MIXERLINE_TARGETTYPE_UNDEFINED )
	{
		fprintf( file,  "%s     Target type: %lu --    ", tabs, line.Target.dwType );
		switch( line.Target.dwType )
		{
			case MIXERLINE_TARGETTYPE_WAVEOUT:
				fprintf( file, "MIXERLINE_TARGETTYPE_WAVEOUT\n" );
				break;
			case MIXERLINE_TARGETTYPE_WAVEIN:
				fprintf( file, "MIXERLINE_TARGETTYPE_WAVEIN\n" );
				break;
			case MIXERLINE_TARGETTYPE_MIDIOUT:
				fprintf( file, "MIXERLINE_TARGETTYPE_MIDIOUT\n" );
				break;
			case MIXERLINE_TARGETTYPE_MIDIIN:
				fprintf( file, "MIXERLINE_TARGETTYPE_MIDIIN\n" );
				break;
			case MIXERLINE_TARGETTYPE_AUX:
				fprintf( file, "MIXERLINE_TARGETTYPE_AUX\n" );
				break;
			default:
				fprintf( file, "\n" );
				break;
		}

		fprintf( file,  "%s     Target name: %s\n", tabs, line.Target.szPname );
		fprintf( file,  "%s     Manufacturer and product IDs: %u -- %u (see mmreg.h or help subject: \"Manufacturer and Product Identifiers\")\n\n", tabs, line.Target.wMid , line.Target.wPid );
	}

	if( line.dwComponentType > MIXERLINE_COMPONENTTYPE_DST_FIRST && line.dwComponentType <= MIXERLINE_COMPONENTTYPE_DST_LAST )
	{
		fprintf( file,  "%s Number of source lines associated with destination line: %lu\n", tabs, line.cConnections );
	}
	fprintf( file,  "%s Number of channels: %lu\n", tabs, line.cChannels );
	fprintf( file,  "%s Number of controls: %lu\n", tabs, line.cControls );
	
	if( line.cControls > 0 )
		fprintf( file,  "%s List of controls follows:\n", tabs );
}



//<=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=>
// Name   : PrintControl
//          
// Descr. : 
//          
// Return : void
// Arg    : MIXERCONTROL &control : 
// Arg    : FILE *file            : 
//------------------------------------------------------------------------------------------
void PrintControl( HMIXEROBJ mixer, MIXERLINE &line, MIXERCONTROL &control, FILE *file )
{
	char *tabs = "\t\t";

	fprintf( file,  "\n%s   ---------------------------- Control ----------------------------\n", tabs );
	fprintf( file,  "%s     Control type:\t", tabs );
	
	switch( control.dwControlType )
	{
	case MIXERCONTROL_CONTROLTYPE_CUSTOM:
		fprintf( file,  "MIXERCONTROL_CONTROLTYPE_CUSTOM\n" );
		break;
	case MIXERCONTROL_CONTROLTYPE_BOOLEANMETER:
		fprintf( file,  "MIXERCONTROL_CONTROLTYPE_BOOLEANMETER\n" );
		break;
	case MIXERCONTROL_CONTROLTYPE_SIGNEDMETER:
		fprintf( file,  "MIXERCONTROL_CONTROLTYPE_SIGNEDMETER\n" );
		break;
	case MIXERCONTROL_CONTROLTYPE_UNSIGNEDMETER:
		fprintf( file,  "MIXERCONTROL_CONTROLTYPE_UNSIGNEDMETER\n" );
		break;
	case MIXERCONTROL_CONTROLTYPE_PEAKMETER:
		fprintf( file,  "MIXERCONTROL_CONTROLTYPE_PEAKMETER\n" );
		break;
	case MIXERCONTROL_CONTROLTYPE_BOOLEAN:
		fprintf( file,  "MIXERCONTROL_CONTROLTYPE_BOOLEAN\n" );
		break;
	case MIXERCONTROL_CONTROLTYPE_ONOFF:
		fprintf( file,  "MIXERCONTROL_CONTROLTYPE_ONOFF\n" );
		break;
	case MIXERCONTROL_CONTROLTYPE_MUTE:
		fprintf( file,  "MIXERCONTROL_CONTROLTYPE_MUTE\n" );
		break;
	case MIXERCONTROL_CONTROLTYPE_MONO:
		fprintf( file,  "MIXERCONTROL_CONTROLTYPE_MONO\n" );
		break;
	case MIXERCONTROL_CONTROLTYPE_LOUDNESS:
		fprintf( file,  "MIXERCONTROL_CONTROLTYPE_LOUDNESS\n" );
		break;
	case MIXERCONTROL_CONTROLTYPE_STEREOENH:
		fprintf( file,  "MIXERCONTROL_CONTROLTYPE_STEREOENH\n" );
		break;
	case MIXERCONTROL_CONTROLTYPE_BUTTON:
		fprintf( file,  "MIXERCONTROL_CONTROLTYPE_BUTTON\n" );
		break;
	case MIXERCONTROL_CONTROLTYPE_DECIBELS:
		fprintf( file,  "MIXERCONTROL_CONTROLTYPE_DECIBELS\n" );
		break;
	case MIXERCONTROL_CONTROLTYPE_SIGNED:
		fprintf( file,  "MIXERCONTROL_CONTROLTYPE_SIGNED\n" );
		break;
	case MIXERCONTROL_CONTROLTYPE_UNSIGNED:
		fprintf( file,  "MIXERCONTROL_CONTROLTYPE_UNSIGNED\n" );
		break;
	case MIXERCONTROL_CONTROLTYPE_PERCENT:
		fprintf( file,  "MIXERCONTROL_CONTROLTYPE_PERCENT\n" );
		break;
	case MIXERCONTROL_CONTROLTYPE_SLIDER:
		fprintf( file,  "MIXERCONTROL_CONTROLTYPE_SLIDER\n" );
		break;
	case MIXERCONTROL_CONTROLTYPE_PAN:
		fprintf( file,  "MIXERCONTROL_CONTROLTYPE_PAN\n" );
		break;
	case MIXERCONTROL_CONTROLTYPE_QSOUNDPAN:
		fprintf( file,  "MIXERCONTROL_CONTROLTYPE_QSOUNDPAN\n" );
		break;
	case MIXERCONTROL_CONTROLTYPE_FADER:
		fprintf( file,  "MIXERCONTROL_CONTROLTYPE_FADER\n" );
		break;
	case MIXERCONTROL_CONTROLTYPE_VOLUME:
		fprintf( file,  "MIXERCONTROL_CONTROLTYPE_VOLUME\n" );
		break;
	case MIXERCONTROL_CONTROLTYPE_BASS:
		fprintf( file,  "MIXERCONTROL_CONTROLTYPE_BASS\n" );
		break;
	case MIXERCONTROL_CONTROLTYPE_TREBLE:
		fprintf( file,  "MIXERCONTROL_CONTROLTYPE_TREBLE\n" );
		break;
	case MIXERCONTROL_CONTROLTYPE_EQUALIZER:
		fprintf( file,  "MIXERCONTROL_CONTROLTYPE_EQUALIZER\n" );
		break;
	case MIXERCONTROL_CONTROLTYPE_SINGLESELECT:
		fprintf( file,  "MIXERCONTROL_CONTROLTYPE_SINGLESELECT\n" );
		break;
	case MIXERCONTROL_CONTROLTYPE_MUX:
		fprintf( file,  "MIXERCONTROL_CONTROLTYPE_MUX\n" );
		break;
	case MIXERCONTROL_CONTROLTYPE_MULTIPLESELECT:
		fprintf( file,  "MIXERCONTROL_CONTROLTYPE_MULTIPLESELECT\n" );
		break;
	case MIXERCONTROL_CONTROLTYPE_MIXER:
		fprintf( file,  "MIXERCONTROL_CONTROLTYPE_MIXER\n" );
		break;
	case MIXERCONTROL_CONTROLTYPE_MICROTIME:
		fprintf( file,  "MIXERCONTROL_CONTROLTYPE_MICROTIME\n" );
		break;
	case MIXERCONTROL_CONTROLTYPE_MILLITIME:
		fprintf( file,  "MIXERCONTROL_CONTROLTYPE_MILLITIME\n" );
		break;
	default:
		fprintf( file,  "---- UNKNOWN CONTROL TYPE ----\n" );
	}
	fprintf( file,  "%s   -----------------------------------------------------------------\n", tabs );

	fprintf( file,  "%s     Short Name: %s\n", tabs, control.szShortName );
	fprintf( file,  "%s     Name: %s\n", tabs, control.szName );

	switch( control.dwControlType & MIXERCONTROL_CT_UNITS_MASK )
	{
		case MIXERCONTROL_CT_UNITS_UNSIGNED:
		case MIXERCONTROL_CT_UNITS_DECIBELS:
			fprintf( file,  "%s     - Min: %lu\n", tabs, control.Bounds.dwMinimum );
			fprintf( file,  "%s     - Max: %lu\n", tabs, control.Bounds.dwMaximum );
			break;
		case MIXERCONTROL_CT_UNITS_PERCENT:
		case MIXERCONTROL_CT_UNITS_SIGNED:
		case MIXERCONTROL_CT_UNITS_BOOLEAN:
			fprintf( file,  "%s     - Min: %ld\n", tabs, control.Bounds.lMinimum );
			fprintf( file,  "%s     - Max: %ld\n", tabs, control.Bounds.lMaximum );
			break;
		case MIXERCONTROL_CT_UNITS_CUSTOM:
			fprintf( file,  "%s     Custom control\n", tabs );
			break;
	}

	fprintf( file,  "%s     - Steps: %lu\n", tabs, control.Metrics.cSteps );

	fprintf( file,  "%s     Status and support flags:\n", tabs);

	if( control.fdwControl & MIXERCONTROL_CONTROLF_UNIFORM )
		fprintf( file,  "%s         - Uniform control\n", tabs );
	
	if( control.fdwControl & MIXERCONTROL_CONTROLF_DISABLED )
		fprintf( file,  "%s         - Control is disabled\n", tabs );

	if( control.fdwControl & MIXERCONTROL_CONTROLF_MULTIPLE )
		fprintf( file,  "%s         - Multiple control. The control has two or more possible settings.\n", tabs );

	if( control.cMultipleItems > 0 )
	{
		fprintf( file,  "%s             Number of items per channel: %d\n", tabs, control.cMultipleItems );

		MIXERCONTROLDETAILS details;
		details.cbStruct       = sizeof( MIXERCONTROLDETAILS );
		details.dwControlID    = control.dwControlID;
		details.cMultipleItems = control.cMultipleItems;
		details.cbDetails      = sizeof( MIXERCONTROLDETAILS_LISTTEXT );

		int listSize;
		if( control.fdwControl & MIXERCONTROL_CONTROLF_UNIFORM )
		{
			details.cChannels = 1;
			listSize = control.cMultipleItems;
		}
		else
		{
			details.cChannels = line.cChannels;
			listSize = control.cMultipleItems*line.cChannels;
		}

		MIXERCONTROLDETAILS_LISTTEXT *list = new MIXERCONTROLDETAILS_LISTTEXT[listSize];

		details.paDetails = list;
		
		if( mixerGetControlDetails( mixer, &details, 
			MIXER_GETCONTROLDETAILSF_LISTTEXT ) != MMSYSERR_NOERROR )
		{
			TRACE( "mixerGetControlDetails failed\n" );
			delete[] list;
			return;
		}
		for ( int i = 0; i < listSize; i++ )
		{
			fprintf( file,  "%s              -------------- Item %d -------------\n", tabs, i );
			fprintf( file,  "%s              Name: %s\n", tabs, list[i].szName );

		}
		
		delete[] list;
	}

}
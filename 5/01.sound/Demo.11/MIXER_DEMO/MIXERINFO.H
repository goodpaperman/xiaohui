//=============================================================================
// Copyright Langis Pitre 1998
// You may do whatever you want with this code, as long as you include this
// copyright notice in your implementation files.
//
// Comments and bug reports: lpitre@sympatico.ca
//
//## Header file for the GetDevicesInfo helper function.
//=============================================================================
#ifndef _LANGIS_PITRE_MIXER_INFO_H_
#define _LANGIS_PITRE_MIXER_INFO_H_

#include <mmsystem.h>

extern    void GetDevicesInfo( LPCSTR filename );
extern LPCTSTR GetControlTypeString( DWORD type );
extern LPCTSTR GetLineTypeString( DWORD type );

//===========================================================================
// Function   : GetDevicesInfo
//          
// Utility function that will print to the specified file all audio lines
// and all mixer controls available on your system. You might want to use
// this function before doing anything else to determine the capabilities
// of your sound card, and of the mixer drivers installed.
//
// It will list all destination lines (ouput lines) and all
// source (input) lines available with every destination line. It will
// also list the available mixer controls for each audio line. Use that
// information to determine what type of windows controls you would
// be allowed to create.
//
// Check the output file and note the type and number of destination (output)
// lines, as well as the source (input) lines associated with every destination
// line. These are labled "Line type".
// Note also the available control types, labeled "Control types"
// You will need these to create your windows controls.
//
// The output may be quite long, but its structure is as follows: for
// every destination line, the controls that work on the output are listed first.
// Then the source lines available for the given output line are listed, as well
// as the controls they contain. Below is an example for the speakers output
// line only, where all the extra information has been removed.
//
//**************************************************************************************
//** Destination line. Index = 0 *******************************************************
//  ------
//  Line type :  ---------  MIXERLINE_COMPONENTTYPE_DST_SPEAKERS
//  ------
//
//      Control type:      MIXERCONTROL_CONTROLTYPE_VOLUME
//
//      Control type:      MIXERCONTROL_CONTROLTYPE_MUTE
//
//      Control type:      MIXERCONTROL_CONTROLTYPE_MIXER
//    
//      Control type:      MIXERCONTROL_CONTROLTYPE_BASS
//    
//      Control type:      MIXERCONTROL_CONTROLTYPE_TREBLE
//    
//      Control type:      ---- UNKNOWN CONTROL TYPE ----
//    
//    =====================================================================================
//    == Source line. Index = 0 ===========================================================
//    ------
//    Line type :  ---------  MIXERLINE_COMPONENTTYPE_SRC_AUXILIARY
//    ------
//    Audio line is a source originating from the auxiliary audio line.
//
//        Control type:      MIXERCONTROL_CONTROLTYPE_VOLUME
//      
//        Control type:      MIXERCONTROL_CONTROLTYPE_MUTE
//      
//    ======================================================================================
//    == Source line. Index = 1 ===========================================================
//    ------
//    Line type :  ---------  MIXERLINE_COMPONENTTYPE_SRC_SYNTHESIZER
//    ------
//    Audio line is a source originating from the output of an internal synthesizer.
//
//        Control type:      MIXERCONTROL_CONTROLTYPE_VOLUME
//      
//        Control type:      MIXERCONTROL_CONTROLTYPE_MUTE
//      
//    ======================================================================================
//    == Source line. Index = 2 ===========================================================
//    ------
//    Line type :  ---------  MIXERLINE_COMPONENTTYPE_SRC_MICROPHONE
//    ------
//    Audio line is a microphone recording source.
//
//        Control type:      MIXERCONTROL_CONTROLTYPE_VOLUME
//      
//        Control type:      MIXERCONTROL_CONTROLTYPE_MUTE
//      
//        Control type:      MIXERCONTROL_CONTROLTYPE_ONOFF
//
//    ======================================================================================
//    == Source line. Index = 3 ===========================================================
//    ------
//    Line type :  ---------  MIXERLINE_COMPONENTTYPE_SRC_COMPACTDISC
//    ------
//    Audio line is a source originating from the output of an internal audio CD.
//
//        Control type:      MIXERCONTROL_CONTROLTYPE_VOLUME
//      
//        Control type:      MIXERCONTROL_CONTROLTYPE_MUTE
//      
//    ======================================================================================
//    == Source line. Index = 4 ===========================================================
//    ------
//    Line type :  ---------  MIXERLINE_COMPONENTTYPE_SRC_WAVEOUT
//    ------
//    Audio line is a source originating from the waveform-audio output digital-to-analog converter (DAC).
//
//        Control type:      MIXERCONTROL_CONTROLTYPE_VOLUME
//      
//        Control type:      MIXERCONTROL_CONTROLTYPE_MUTE
//      
//        Control type:      MIXERCONTROL_CONTROLTYPE_PEAKMETER
//    
//
// Implemented in MixerInfo.cpp
//          
// Return :	void
// Arg    : LPCSTR filename : name of output file
//===========================================================================


#endif // _LANGIS_PITRE_MIXER_INFO_H_

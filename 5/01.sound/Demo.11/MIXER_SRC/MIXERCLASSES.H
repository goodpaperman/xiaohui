//=============================================================================
// Copyright Langis Pitre 1998
// You may do whatever you want with this code, as long as you include this
// copyright notice in your implementation files.
//
// If you wish to add new classes to this collection, feel free to do so.
// But please send me your code so that I can update the collection.
//
// Comments and bug reports: lpitre@sympatico.ca
//
//=============================================================================
//=============================================================================
//                         CMixerBase
//                         CMixerFader
//                         CMixerSwitch
//                         CMixerSelector
//                         CMixerPeakMeter
//
// This collection of classes encapsulates part of the audio mixer services
// which control the routing of audio lines to a destination device for playing
// or recording, or to control volume and other audio effects.
//
// For more information on each of these classes, see their respective
// implementation file.
//
// It takes quite a bit of work just to get a simple volume control to work
// in an application. With these classes, all it takes is a few lines of code
// to get a control up and running.
// For example: the CMixerFader class is derived from CSliderCtrl, so it takes
// a slider control resource, and 3 lines of code (plus the include directive!)
// to have a fully functional volume control in a dialog box.
//
// Also supplied is a utility function you can use to determine the capabilities
// of your sound card and the available audio services (see prototype below).
//
// To use these classes, add this file and the source files to your project,
// include this file where necessary, and link with winmm.lib
//                                        -------------------
//=============================================================================
#ifndef _LANGIS_PITRE_MIXER_CONTROLS_H_
#define _LANGIS_PITRE_MIXER_CONTROLS_H_

#include <mmsystem.h>

#define MIXER_SELECTOR_CHANGED (WM_USER+1)

// Comment-out the next line to prevent warnings to popup. If there was a problem
// initiating a mixer control, your program won't crash since the classes check
// the validity of values. It does help to find out where the problem is though.
#define DO_MIXER_WARNING

//=============================================================================
//                         CMixerBase Class
//
// Base class of all the mixer classes
// Takes care of opening the mixer device to get a valid handler.
// This handle, along with the number of channels are stored in
// member variables.
//
// You don't use this class directly, unless you want to derive new classes
// from it.
//
//===========================================================================
class CMixerBase  
//===========================================================================
{
public:

	CMixerBase();
	virtual ~CMixerBase();
	
	void PopupErrorMsg( LPCSTR mess, LPCSTR origin );

protected:
	int Init( DWORD LineType, HWND hwnd, MIXERLINE &mixerLine );

	int m_nChannels;
	HMIXER m_HMixer;
};

	
inline void CMixerBase::PopupErrorMsg( LPCSTR mess, LPCSTR origin )
{
#ifdef DO_MIXER_WARNING
	::MessageBox(NULL, mess, origin, MB_OK|MB_ICONEXCLAMATION);
#else
	mess; origin;
#endif

}


//=============================================================================
//                             CMixerFader Class
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
// For example:  say you want a main volume slider and a cd audio
// volume slider, the call to Init() for the main and CD volumes would be:
//
//	m_mainVolume.Init( MIXERLINE_COMPONENTTYPE_DST_SPEAKERS,   // destination line
//	                   MIXERCONTROL_CONTROLTYPE_VOLUME,	       // control type
//					   CMixerFader::MAIN );
//
//	m_cdVolume.Init( MIXERLINE_COMPONENTTYPE_SRC_COMPACTDISC,  // source line
//	                 MIXERCONTROL_CONTROLTYPE_VOLUME,          // control type
//					 CMixerFader::MAIN );
//
//=============================================================================
class CMixerFader : public CSliderCtrl, public CMixerBase
//===========================================================================
{
public:
	CMixerFader();
	virtual ~CMixerFader();
	
	enum { LEFT, RIGHT, MAIN, BALANCE };

	int Init( DWORD LineType, DWORD ControlType, int subType );

	//{{AFX_VIRTUAL(CMixerFader)
	//}}AFX_VIRTUAL

protected:

	DWORD GetSliderValue();
	void SetFaderValue();

	void SetSliderPos( int value );
	void SetHVSliderPos();

	int m_Type;
	float m_DeltaOverMax;

    MIXERCONTROLDETAILS m_Control;
	MIXERCONTROLDETAILS_UNSIGNED *m_Value;

	//{{AFX_MSG(CMixerFader)
	afx_msg LONG OnMixerControlChanged( UINT, LONG );
	afx_msg void HScroll ( UINT nSBCode, UINT nPos );
	afx_msg void VScroll ( UINT nSBCode, UINT nPos );
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};


//=============================================================================
//                             CMixerSwitch Class
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
class CMixerSwitch : public CButton, public CMixerBase
//===========================================================================
{
public:
	CMixerSwitch();
	virtual ~CMixerSwitch();

	int   Init( DWORD LineType, DWORD ControlType );

	//{{AFX_VIRTUAL(CMixerSwitch)
	//}}AFX_VIRTUAL

protected:

	BOOL  m_HasOnOff;

    MIXERCONTROLDETAILS          m_Control;
	MIXERCONTROLDETAILS_BOOLEAN  m_Value;

	//{{AFX_MSG(CMixerSwitch)
	afx_msg LONG OnMixerControlChanged( UINT, LONG );
	afx_msg void OnClicked();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};


//=============================================================================
//                             CMixerSelector Class
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
// 1) Declare a variable of type CMixerSelector in your dialog or window class
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
//===========================================================================
class CMixerSelector : public CWnd, public CMixerBase
//===========================================================================
{
// Construction
public:
	CMixerSelector();
	virtual ~CMixerSelector();

	int Init( DWORD LineType, DWORD ControlType, CWnd* parent);

	int  SetItemValue( int index, BOOL value );
	BOOL GetItemValue( int index );

	//{{AFX_VIRTUAL(CMixerSelector)
	//}}AFX_VIRTUAL

protected:

	int nItems;
    MIXERCONTROLDETAILS          m_Control;
	MIXERCONTROLDETAILS_BOOLEAN  *m_Value;

	//{{AFX_MSG(CMixerSelector)
	afx_msg LONG OnMixerControlChanged( UINT, LONG );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//=============================================================================
//                             CMixerPeakMeter Class
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
class CMixerPeakMeter : public CStatic, public CMixerBase
//===========================================================================
{
public:
	CMixerPeakMeter( COLORREF background = RGB( 192, 192, 192 ) );
	virtual ~CMixerPeakMeter();

	int  Init( DWORD LineType );

	//{{AFX_VIRTUAL(CMixerPeakMeter)
	//}}AFX_VIRTUAL

protected:

    COLORREF m_Bkgnd;
	DWORD m_LineID;

    MIXERCONTROLDETAILS         m_Control;
	MIXERCONTROLDETAILS_SIGNED  m_Value;

	void DrawMeter( CDC *pDC = NULL );

	//{{AFX_MSG(CMixerPeakMeter)
	afx_msg void OnPaint();
	afx_msg LONG OnMixerLineChanged( UINT, LONG );
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

//===========================================================================
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // _LANGIS_PITRE_MIXER_CONTROLS_H_

//===========================================================================

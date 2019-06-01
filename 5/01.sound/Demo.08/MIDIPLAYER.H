// MidiPlayer.h : main header file for the MIDIPLAYER application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "SingleInstanceApp.h"

/////////////////////////////////////////////////////////////////////////////
// CMidiPlayerApp:
// See MidiPlayer.cpp for the implementation of this class
//

class CMidiPlayerApp : public CSingleInstanceApp
{
public:
	CMidiPlayerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMidiPlayerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMidiPlayerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

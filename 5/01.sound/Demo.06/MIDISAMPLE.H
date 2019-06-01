// MidiSample.h : main header file for the MIDISAMPLE application
//

#if !defined(AFX_MIDISAMPLE_H__AD8DF4A3_587E_11D2_A78C_000000000000__INCLUDED_)
#define AFX_MIDISAMPLE_H__AD8DF4A3_587E_11D2_A78C_000000000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMidiSampleApp:
// See MidiSample.cpp for the implementation of this class
//

class CMidiSampleApp : public CWinApp
{
public:
	CMidiSampleApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMidiSampleApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMidiSampleApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MIDISAMPLE_H__AD8DF4A3_587E_11D2_A78C_000000000000__INCLUDED_)

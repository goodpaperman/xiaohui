// StackUp.h : main header file for the STACKUP application
//

#if !defined(AFX_STACKUP_H__DF9698A5_CCC4_11D1_82C0_444553540000__INCLUDED_)
#define AFX_STACKUP_H__DF9698A5_CCC4_11D1_82C0_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

class CStackUp;

/////////////////////////////////////////////////////////////////////////////
// CStackUpApp:
// See StackUp.cpp for the implementation of this class
//

class CStackUpApp : public CWinApp
{
public:
	CStackUpApp();

  CStackUp* m_pStackUp;
  BOOL  m_bIsActive;    
  BOOL  m_bRedrawScreen;
  BOOL  m_bShutDown;
  void  SetActive(BOOL bActive) { m_bIsActive = bActive; m_bRedrawScreen = bActive; };
  void  ShutDown() { m_bShutDown = TRUE; };

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStackUpApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual int Run();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CStackUpApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STACKUP_H__DF9698A5_CCC4_11D1_82C0_444553540000__INCLUDED_)

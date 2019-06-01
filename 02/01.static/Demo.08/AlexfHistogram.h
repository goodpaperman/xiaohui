// AlexfHistogram.h : main header file for the ALEXFHISTOGRAM application
//

#if !defined(AFX_ALEXFHISTOGRAM_H__EE1F7AC9_2661_11D3_9865_868E4C4284CA__INCLUDED_)
#define AFX_ALEXFHISTOGRAM_H__EE1F7AC9_2661_11D3_9865_868E4C4284CA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CAlexfHistogramApp:
// See AlexfHistogram.cpp for the implementation of this class
//

class CAlexfHistogramApp : public CWinApp
{
public:
	CAlexfHistogramApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAlexfHistogramApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CAlexfHistogramApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALEXFHISTOGRAM_H__EE1F7AC9_2661_11D3_9865_868E4C4284CA__INCLUDED_)

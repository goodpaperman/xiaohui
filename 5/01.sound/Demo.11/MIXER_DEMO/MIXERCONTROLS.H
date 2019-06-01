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
// MixerControls.h : main header file for the MixerControls application
//

#if !defined(AFX_MIXERCONTROLS_H__B000D3C5_0897_11D2_A16F_000000000000__INCLUDED_)
#define AFX_MIXERCONTROLS_H__B000D3C5_0897_11D2_A16F_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
class CMixerControlsApp : public CWinApp
//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
{
public:
	CMixerControlsApp();

	//{{AFX_VIRTUAL(CMixerControlsApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL
	
	//{{AFX_MSG(CMixerControlsApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MIXERCONTROLS_H__B000D3C5_0897_11D2_A16F_000000000000__INCLUDED_)

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
// MixerControls.cpp : Defines the class behaviors for the application.
//
#include "stdafx.h"
#include "MixerControls.h"
#include "MainDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


BEGIN_MESSAGE_MAP(CMixerControlsApp, CWinApp)
	//{{AFX_MSG_MAP(CMixerControlsApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
// Name   : CMixerControlsApp
//          
// Descr. : 
//          
//-----------------------------------------------------------------------------
CMixerControlsApp::CMixerControlsApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
//
// The one and only CMixerControlsApp object
//
//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
CMixerControlsApp theApp;
//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm



//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
// Name   : InitInstance
//          
// Descr. : CMixerControlsApp initialization
//          
// Return : BOOL
//-----------------------------------------------------------------------------
BOOL CMixerControlsApp::InitInstance()
{

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
	
	CMainDlg dlg;

	m_pMainWnd = &dlg;
	dlg.DoModal();

	return FALSE;
}


//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
// Name   : OnAppAbout
//          
// Descr. : 
//          
// Return : void
//-----------------------------------------------------------------------------
void CMixerControlsApp::OnAppAbout() 
{
	CDialog dlg( IDD_ABOUT_DIALOG );

	dlg.DoModal();
}

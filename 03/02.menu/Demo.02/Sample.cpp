// A flat popup menu for controls
// Copyright (c) 1999 Andy Brown <andy@mirage.dabsol.co.uk>
// You may do whatever you like with this file, I just don't care.


#include "stdafx.h"
#include "Sample.h"
#include "MainFrm.h"
#include "SampleDoc.h"
#include "SampleView.h"


// The one and only CSampleApp object

CSampleApp theApp;


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/***************/
/* Message map */
/***************/

BEGIN_MESSAGE_MAP(CSampleApp, CWinApp)
	//{{AFX_MSG_MAP(CSampleApp)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
END_MESSAGE_MAP()


/***************/
/* Constructor */
/***************/

CSampleApp::CSampleApp()
{
}


/****************/
/* InitInstance */
/****************/

BOOL CSampleApp::InitInstance()
{
	Enable3dControls();

// Register document template
	
	AddDocTemplate(new CSingleDocTemplate(IDR_MAINFRAME,RUNTIME_CLASS(CSampleDoc),RUNTIME_CLASS(CMainFrame),RUNTIME_CLASS(CSampleView)));

// create new document

	OnFileNew();

// show the main window

	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}

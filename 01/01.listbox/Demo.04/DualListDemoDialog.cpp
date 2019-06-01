///////////////////////////////////////////////////////////////////////////////
//
//  Filename:       DualListDemoDialog.cpp
//  Description:    Demo dialog box that uses the DualListManager class.
//
//  AUTHOR     :    Copyright (C) Steve Aube, February 2000
//                  SteveAube@yahoo.com
//
//                  You can reuse and redistribute this code, provided this 
//                  header is kept as is.
//
////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DualListDemo.h"
#include "DualListDemoDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDualListDemoDialog dialog


CDualListDemoDialog::CDualListDemoDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CDualListDemoDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDualListDemoDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CDualListDemoDialog::~CDualListDemoDialog(void)
{
}

void CDualListDemoDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDualListDemoDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDualListDemoDialog, CDialog)
	//{{AFX_MSG_MAP(CDualListDemoDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDualListDemoDialog message handlers

BOOL CDualListDemoDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();

    // ADDED TO DEFAULT THE LISTS.
    // This code will need to be replaced with your application specific 
    // code that knows what belongs in each list.
    m_DualListManager.AddItemToAvailableList(_T("Red"), 0);
    m_DualListManager.AddItemToAvailableList(_T("Green"), 1);
    m_DualListManager.AddItemToAvailableList(_T("Blue"), 2);
    m_DualListManager.AddItemToChoosenList(_T("Yellow"), 3);
    m_DualListManager.AddItemToChoosenList(_T("Purple"), 4);
    m_DualListManager.AddItemToChoosenList(_T("Orange"), 5);

    // ADDED TO INITIALIZE THE MANAGER CLASS
    m_DualListManager.InitializeControls(this, 
                                         IDC_DLG_LIST_AVAILABLE,
                                         IDC_DLG_LIST_CHOOSEN, 
                                         IDC_DLG_ADD,
                                         IDC_DLG_ADD_ALL,
                                         IDC_DLG_REMOVE,
                                         IDC_DLG_REMOVE_ALL,
                                         IDC_DLG_MOVE_UP,
                                         IDC_DLG_MOVE_DOWN);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDualListDemoDialog::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
    // ADDED TO INTERCEPT MESSAGE THAT THE DUAL LIST MANAGER NEEDS
    m_DualListManager.ProcessCmdMsg(nID, nCode);

    // NOW CALL THE BASE CLASS
	return CDialog::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

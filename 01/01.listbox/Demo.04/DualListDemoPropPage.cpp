///////////////////////////////////////////////////////////////////////////////
//
//  Filename:       DualListPropPage.cpp
//  Description:    Demo property page that uses the DualListManager class.
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
#include "DualListDemoPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDualListDemoPropPage property page

IMPLEMENT_DYNCREATE(CDualListDemoPropPage, CPropertyPage)

CDualListDemoPropPage::CDualListDemoPropPage() : CPropertyPage(CDualListDemoPropPage::IDD)
{
	//{{AFX_DATA_INIT(CDualListDemoPropPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CDualListDemoPropPage::~CDualListDemoPropPage()
{
}

void CDualListDemoPropPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDualListDemoPropPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDualListDemoPropPage, CPropertyPage)
	//{{AFX_MSG_MAP(CDualListDemoPropPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDualListDemoPropPage message handlers

BOOL CDualListDemoPropPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
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
                                         IDC_PP_LIST_AVAILABLE,
                                         IDC_PP_LIST_CHOOSEN, 
                                         IDC_PP_ADD,
                                         IDC_PP_ADD_ALL,
                                         IDC_PP_REMOVE,
                                         IDC_PP_REMOVE_ALL,
                                         IDC_PP_MOVE_UP,
                                         IDC_PP_MOVE_DOWN);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDualListDemoPropPage::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
    // ADDED TO INTERCEPT MESSAGE THAT THE DUAL LIST MANAGER NEEDS
    m_DualListManager.ProcessCmdMsg(nID, nCode);

    // NOW CALL THE BASE CLASS
	return CPropertyPage::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

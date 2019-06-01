///////////////////////////////////////////////////////////////////////////////
//
//  Filename:       DualListDemoPropSheet.cpp
//  Description:    Demo Property Sheet that uses a property page that uses 
//                  the DualListManager class.
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
#include "DualListDemoPropSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDualListDemoPropSheet

IMPLEMENT_DYNAMIC(CDualListDemoPropSheet, CPropertySheet)

CDualListDemoPropSheet::CDualListDemoPropSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
    AddPage(&m_DualListPP);
}

CDualListDemoPropSheet::CDualListDemoPropSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
    AddPage(&m_DualListPP);
}

CDualListDemoPropSheet::~CDualListDemoPropSheet()
{
}


BEGIN_MESSAGE_MAP(CDualListDemoPropSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CDualListDemoPropSheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDualListDemoPropSheet message handlers

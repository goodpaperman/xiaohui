#include "stdafx.h"
#include "resource.h"
#include "MyPropertySheet.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CMyPropertySheet, CPropertySheet)

CMyPropertySheet::CMyPropertySheet(CWnd* pWndParent)
	 : CPropertySheet(IDS_PROPSHT_CAPTION, pWndParent)
{
	AddPage(&m_Page1);
	AddPage(&m_Page2);
}

CMyPropertySheet::~CMyPropertySheet()
{
}


BEGIN_MESSAGE_MAP(CMyPropertySheet, CPropertySheet)
	//{{AFX_MSG_MAP(CMyPropertySheet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CMyPropertySheet::PostNcDestroy()
{
	CPropertySheet::PostNcDestroy();
	delete this;
}



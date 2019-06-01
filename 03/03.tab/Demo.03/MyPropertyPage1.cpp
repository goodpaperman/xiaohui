#include "stdafx.h"
#include "resource.h"
#include "MyPropertyPage1.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CMyPropertyPage1, CPropertyPage)
IMPLEMENT_DYNCREATE(CMyPropertyPage2, CPropertyPage)


CMyPropertyPage1::CMyPropertyPage1() : CPropertyPage(CMyPropertyPage1::IDD)
{
	//{{AFX_DATA_INIT(CMyPropertyPage1)
	//}}AFX_DATA_INIT
}

CMyPropertyPage1::~CMyPropertyPage1()
{
}

void CMyPropertyPage1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyPropertyPage1)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyPropertyPage1, CPropertyPage)
	//{{AFX_MSG_MAP(CMyPropertyPage1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CMyPropertyPage2::CMyPropertyPage2() : CPropertyPage(CMyPropertyPage2::IDD)
{
	//{{AFX_DATA_INIT(CMyPropertyPage2)
	//}}AFX_DATA_INIT
}

CMyPropertyPage2::~CMyPropertyPage2()
{
}

void CMyPropertyPage2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyPropertyPage2)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyPropertyPage2, CPropertyPage)
	//{{AFX_MSG_MAP(CMyPropertyPage2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



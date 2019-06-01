// PropTest.cpp : implementation file
//

#include "stdafx.h"
#include "lbtabdemo.h"
#include "PropTest.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropTest property page

IMPLEMENT_DYNCREATE(CPropTest, CPropertyPage)

CPropTest::CPropTest() : CPropertyPage(CPropTest::IDD)
{
	//{{AFX_DATA_INIT(CPropTest)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPropTest::~CPropTest()
{
}

void CPropTest::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropTest)
    DDX_Control(pDX, IDC_SPIN_TEST, m_spin); 
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPropTest, CPropertyPage)
	//{{AFX_MSG_MAP(CPropTest)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropTest message handlers

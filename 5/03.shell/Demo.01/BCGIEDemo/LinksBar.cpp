// LinksBar.cpp : implementation file
//

#include "stdafx.h"
#include "BCGIEDemo.h"
#include "LinksBar.h"
#include "LinkButton.h"
#include "BCGIEDemoDoc.h"
#include "BCGIEDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SERIAL(CLinksBar, CBCGToolBar, 1)

/////////////////////////////////////////////////////////////////////////////
// CLinksBar

CLinksBar::CLinksBar()
{
}

CLinksBar::~CLinksBar()
{
}


BEGIN_MESSAGE_MAP(CLinksBar, CBCGToolBar)
	//{{AFX_MSG_MAP(CLinksBar)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CLinksBar message handlers

int CLinksBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGToolBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	InsertButton (CLinkButton (_T("Best Company"), _T("http://www.iet-w6.com")));
	InsertButton (CLinkButton (_T("Best Programmers Site"), _T("http://www.codeguru.com")));
	InsertButton (CLinkButton (_T("Best Car"), _T("http://www.skoda-auto.com")));
	InsertButton (CLinkButton (_T("Best Rock-Band"), _T("http://www.planetaquarium.com/eng")));
	InsertButton (CLinkButton (_T("Best City"), _T("http://www.spb.ru")));

	return 0;
}

BOOL CLinksBar::OnSendCommand (const CBCGToolbarButton* pButton)
{
	CLinkButton* pLinkButton = DYNAMIC_DOWNCAST (CLinkButton, pButton);
	if (pLinkButton == NULL)
	{
		// Defauult processing
		return FALSE;
	}

	CString strURL = pLinkButton->GetURL ();

	((CBCGIEDemoView*)GetParentFrame ()->GetActiveView())->Navigate2 (strURL, 0, NULL);
	return TRUE;
}


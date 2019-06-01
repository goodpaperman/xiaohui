// WndFileBrowse.cpp : implementation file
//

#include "stdafx.h"
#include <dlgs.h>
#include "twopanes.h"
#include "WndFileBrowse.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWndFileBrowse

IMPLEMENT_DYNAMIC(CWndFileBrowse, CWnd)

CWndFileBrowse::CWndFileBrowse()
{
}

CWndFileBrowse::~CWndFileBrowse()
{
}


BEGIN_MESSAGE_MAP(CWndFileBrowse, CWnd)
	//{{AFX_MSG_MAP(CWndFileBrowse)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CWndFileBrowse message handlers

void CWndFileBrowse::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	SetListSize();
}

void CWndFileBrowse::SetListSize()
{
	CWnd* pWnd = GetDlgItem(lst2);
	if(pWnd)
	{
		if(!g_bIsWindows98orLater)
		{
			CRect rectClient, rectList;
			GetClientRect(&rectClient);
			pWnd->GetWindowRect(&rectList);
			ScreenToClient(&rectList);
			int nMarginX = rectList.left - rectClient.left;
			ASSERT(nMarginX > 0);
			int nMarginY = rectList.top - rectClient.top;
			ASSERT(nMarginY > 0);
			rectClient.DeflateRect(nMarginX, nMarginY);
			int nWidth = rectClient.Width();
			int nHeight = rectClient.Height();
			if(nWidth > 0 && nHeight > 0)
				pWnd->SetWindowPos(NULL, 0, 0, nWidth, nHeight,
					SWP_NOMOVE|SWP_NOZORDER|SWP_NOACTIVATE);
		}
//		CWnd* pList = pWnd->ChildWindowFromPoint(CPoint(1, 1));
//		if(pList)
//			pList->Invalidate();
	}	
}

// EditBar.cpp : implementation file
//

#include "stdafx.h"
#include "EditBar.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditBar

IMPLEMENT_DYNAMIC( CEditBar, CControlBar )

CEditBar::CEditBar()
 : m_szMRU(400, 64)
{	
}

CEditBar::~CEditBar()
{
}


BEGIN_MESSAGE_MAP(CEditBar, CControlBar)
	//{{AFX_MSG_MAP(CEditBar)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_MESSAGE(WM_GETTEXT, OnGetText)
	ON_MESSAGE(WM_GETTEXTLENGTH, OnGetTextLength)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CEditBar message handlers

BOOL CEditBar::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.dwExStyle |= WS_EX_CLIENTEDGE;

	return CControlBar::PreCreateWindow(cs);
}

BOOL CEditBar::Create(CWnd* pParentWnd)
{
	ASSERT_VALID(pParentWnd);   // must have a parent
	DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_BORDER | WS_HSCROLL | WS_VSCROLL 
		| ES_AUTOHSCROLL | ES_AUTOVSCROLL |ES_MULTILINE | ES_NOHIDESEL | ES_WANTRETURN;
	// create the HWND
	CRect rect; 
	rect.SetRectEmpty();

	if (!CWnd::Create(_T("EDIT"), NULL, dwStyle, rect, pParentWnd, (UINT)-1))
	{
		ASSERT(0);
		return FALSE;
	}
	// Note: Parent must resize itself for control bar to be resized

	return TRUE;
	
}

void CEditBar::OnUpdateCmdUI(CFrameWnd*, BOOL)
{
}

CSize CEditBar::CalcDynamicLayout(int nLength, DWORD dwMode)
{
	if(0 < nLength)
		if(dwMode & LM_LENGTHY)
			m_szMRU.cy = nLength;
		else
			m_szMRU.cx = nLength;
	CSize size = m_szMRU;
	CFrameWnd* pFrame = GetParentFrame();
	ASSERT(pFrame);
	if(pFrame->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	{
		CRect rect;
		pFrame->GetClientRect(&rect);
		size.cx = rect.Width();
	}
	return size;
}

BOOL CEditBar::PreTranslateMessage(MSG* pMsg)
{
	return CWnd::PreTranslateMessage(pMsg);
}

void CEditBar::OnPaint() 
{
	Default();
}

void CEditBar::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CWnd::OnLButtonDown(nFlags, point);
}

static const TCHAR szCaption[] = _T("Command Input");
#define CaptionLength (sizeof(szCaption) / sizeof(TCHAR) - 1)

LRESULT CEditBar::OnGetText(WPARAM wParam, LPARAM lParam)
{
	lstrcpyn((LPTSTR)lParam, szCaption, wParam);
	if ((int)wParam > CaptionLength)
		wParam = CaptionLength;
	return wParam;
}

LRESULT CEditBar::OnGetTextLength(WPARAM, LPARAM)
{
	return CaptionLength;
}

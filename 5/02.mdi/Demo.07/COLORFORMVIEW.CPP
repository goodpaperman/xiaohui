/////////////////////////////////////////////////////////////////////////////
//
// Author:	if (it works)
//				Author = _T("Patty You");
//			else
//				Author = _T("IUnknown");
// Date:	08/26/98
/////////////////////////////////////////////////////////////////////////////
//
// ColorFormView.cpp : implementation file
//

#include "stdafx.h"
#include "MyFormView.h"
#include "ColorFormView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorFormView

IMPLEMENT_DYNAMIC(CColorFormView, CFormView)

CColorFormView::CColorFormView(LPCTSTR lpszTemplateName)
:CFormView(lpszTemplateName)
{
	m_crBackground = GetSysColor(COLOR_3DFACE);
	m_wndbkBrush.CreateSolidBrush(m_crBackground); 
}

CColorFormView::CColorFormView(UINT nIDTemplate)
:CFormView(nIDTemplate)
{
	m_crBackground = GetSysColor(COLOR_3DFACE);
	m_wndbkBrush.CreateSolidBrush(m_crBackground); 
}

CColorFormView::~CColorFormView()
{
	if(m_wndbkBrush.GetSafeHandle())
		m_wndbkBrush.DeleteObject();
}


BEGIN_MESSAGE_MAP(CColorFormView, CFormView)
	//{{AFX_MSG_MAP(CColorFormView)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorFormView drawing

void CColorFormView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
}

void CColorFormView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CColorFormView diagnostics

#ifdef _DEBUG
void CColorFormView::AssertValid() const
{
	CFormView::AssertValid();
}

void CColorFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CColorFormView message handlers
void CColorFormView::SetBackgroundColor(COLORREF crBackground)
{
	m_crBackground = crBackground;
	
	if(m_wndbkBrush.GetSafeHandle())
		m_wndbkBrush.DeleteObject();

	m_wndbkBrush.CreateSolidBrush(m_crBackground); 
}

BOOL CColorFormView::OnEraseBkgnd(CDC* pDC) 
{
	CFormView::OnEraseBkgnd(pDC);

	CRect rect;
	GetClientRect(rect);

	pDC->FillRect(&rect, &m_wndbkBrush);

	return TRUE;
}

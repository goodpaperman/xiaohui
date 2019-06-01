// FrameGrabberTestView.cpp : implementation of the CFrameGrabberTestView class
//
// (c) Vadim Gorbatenko, 1999 
// gvv@mail.tomsknet.ru
// All rights reserved
//

#include "stdafx.h"
#include "FrameGrabberTest.h"

#include "FrameGrabberTestDoc.h"
#include "FrameGrabberTestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define	DEFAULT_PERIOD	100
/////////////////////////////////////////////////////////////////////////////
// CFrameGrabberTestView

IMPLEMENT_DYNCREATE(CFrameGrabberTestView, CView)

BEGIN_MESSAGE_MAP(CFrameGrabberTestView, CView)
	//{{AFX_MSG_MAP(CFrameGrabberTestView)
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_UPDATE_COMMAND_UI(ID_FILE_FORMAT, OnUpdateFileFormat)
	ON_UPDATE_COMMAND_UI(ID_FILE_SOURCE, OnUpdateFileSource)
	ON_COMMAND(ID_FILE_SOURCE, OnFileSource)
	ON_COMMAND(ID_FILE_FORMAT, OnFileFormat)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFrameGrabberTestView construction/destruction

CFrameGrabberTestView::CFrameGrabberTestView()
{
	// TODO: add construction code here

}

CFrameGrabberTestView::~CFrameGrabberTestView()
{
}

BOOL CFrameGrabberTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CFrameGrabberTestView drawing

void CFrameGrabberTestView::OnDraw(CDC* pDC)
{
	CFrameGrabberTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(!m_FrameGrabber.GetSafeHwnd())
	{
		CRect rc;
		GetClientRect(rc);
        
        CFont wFont;
        wFont.CreateFont(24, 0, 0, 0, 0,
            0, 0, 0,
            0, 0, 0, 0,
            VARIABLE_PITCH | FF_SWISS, "MS Sans Serif");
        CFont *of=pDC->SelectObject(&wFont);
        
        CString s="Capture device not ready or not found";
        pDC->SetBkMode(TRANSPARENT);
        pDC->SetTextColor(GetSysColor(COLOR_BTNSHADOW));
        pDC->DrawText(s,&rc,
            DT_CENTER|DT_SINGLELINE|DT_VCENTER);
        pDC->SelectObject(of);
	
	}

	if(pDoc->m_ImageBitmap.GetSafeHandle())
	{
		pDoc->m_ImageBitmap.BitBlt(pDC,CPoint(0,0));
	}
}

/////////////////////////////////////////////////////////////////////////////
// CFrameGrabberTestView diagnostics

#ifdef _DEBUG
void CFrameGrabberTestView::AssertValid() const
{
	CView::AssertValid();
}

void CFrameGrabberTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFrameGrabberTestDoc* CFrameGrabberTestView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFrameGrabberTestDoc)));
	return (CFrameGrabberTestDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFrameGrabberTestView message handlers

void CFrameGrabberTestView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	if(!m_FrameGrabber.GetSafeHwnd())
	{
		m_FrameGrabber.Create(0,9,this);
		SetTimer(0x1, DEFAULT_PERIOD, NULL);
	}	
}

void CFrameGrabberTestView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{	
	if(m_FrameGrabber.GetSafeHwnd())
	{
		CSize sz = m_FrameGrabber.GetImageSize();
		CRect rcc;
		CRect rcw;
		GetClientRect(&rcc);
		GetWindowRect(&rcw);
		int dx = rcw.Width()-rcc.Width();
		int dy = rcw.Height()-rcc.Height();

		if(sz.cx && (rcc.Width()!=sz.cx || rcc.Height()!=sz.cy))
		{
			SetWindowPos(NULL,0,0,
						 sz.cx+dx, sz.cy+dy, SWP_NOMOVE|SWP_NOZORDER);
            
            GetParentFrame()->GetClientRect(&rcc);
            GetParentFrame()->GetWindowRect(&rcw);
            dx+= rcw.Width()-rcc.Width();
            dy+= rcw.Height()-rcc.Height();

			GetParentFrame()->SetWindowPos(NULL,0,0,
						sz.cx+dx, sz.cy+dy, SWP_NOMOVE|SWP_NOZORDER);
		}
		InvalidateRect(NULL);
	}	
}

void CFrameGrabberTestView::OnTimer(UINT nIDEvent) 
{
	if(!m_FrameGrabber.GetSafeHwnd())	return;

	CFrameGrabberTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	//get the first frame
	if(!pDoc->m_ImageBitmap.GetSafeHandle())
	{
		LPBITMAPINFO lpBi = m_FrameGrabber.GetDIB();
		pDoc->m_ImageBitmap.CreateFromDib(lpBi);
		InvalidateRect(NULL);	
	}
	else//only pass DIB to processor
	{	
		LPBITMAPINFO lpBi = m_FrameGrabber.GetDIB();
		pDoc->ProcessImage(lpBi);
	}
}

BOOL CFrameGrabberTestView::OnEraseBkgnd(CDC* pDC) 
{
	if(m_FrameGrabber.GetSafeHwnd())	
        return TRUE;	
	
	return CView::OnEraseBkgnd(pDC);
}

void CFrameGrabberTestView::OnUpdateFileFormat(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable((BOOL)m_FrameGrabber.GetSafeHwnd());	
}

void CFrameGrabberTestView::OnUpdateFileSource(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable((BOOL)m_FrameGrabber.GetSafeHwnd());	
}

void CFrameGrabberTestView::OnFileSource() 
{
	if(m_FrameGrabber.GetSafeHwnd())
	{
		m_FrameGrabber.VideoSourceDialog();
		OnUpdate(NULL, 0, NULL); 
	}	
}

void CFrameGrabberTestView::OnFileFormat() 
{
	if(m_FrameGrabber.GetSafeHwnd())
	{
		m_FrameGrabber.VideoFormatDialog();
		OnUpdate(NULL, 0, NULL); 
	}	
}

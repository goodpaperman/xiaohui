// PicStatic.cpp : implementation file
//

#include "stdafx.h"
#include "AVI.h"
#include "PicStatic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPicStatic

CPicStatic::CPicStatic() : m_avi("Desktop.avi")
{
}

CPicStatic::~CPicStatic()
{
    if(m_dc.m_hDC)
    {
        m_dc.SelectObject((CBitmap*)NULL); 
        m_bmp.DeleteObject(); 
    }
}


BEGIN_MESSAGE_MAP(CPicStatic, CStatic)
	//{{AFX_MSG_MAP(CPicStatic)
	ON_WM_PAINT()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPicStatic message handlers

void CPicStatic::OnPaint() 
{
    CRect rect; 
    GetClientRect(&rect); 
	CPaintDC dc(this); // device context for painting
	if(m_dc.m_hDC == NULL)
    {
        m_dc.CreateCompatibleDC(&dc); 
        m_bmp.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height()); 
        m_dc.SelectObject(&m_bmp); 
        //m_dc.FillSolidRect(&rect, ::GetSysColor(COLOR_WINDOW)); 
        SetTimer(1, 100, NULL); 
    }

    CWnd* pDesk = GetDesktopWindow(); 
    CDC* pDC = pDesk->GetDC(); 
    m_dc.BitBlt(0, 0, rect.Width(), rect.Height(), pDC, 0, 0, SRCCOPY); 
    ReleaseDC(pDC); 
    dc.BitBlt(0, 0, rect.Width(), rect.Height(), &m_dc, 0, 0, SRCCOPY); 
    m_avi.AddFrame(m_bmp); 
}

void CPicStatic::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
    if(nIDEvent == 1)
        Invalidate(); 

	CStatic::OnTimer(nIDEvent);
}

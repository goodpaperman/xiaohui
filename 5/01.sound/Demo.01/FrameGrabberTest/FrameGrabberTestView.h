// FrameGrabberTestView.h : interface of the CFrameGrabberTestView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FRAMEGRABBERTESTVIEW_H__7E92FA34_976C_11D3_B4B8_8E815E0D4B38__INCLUDED_)
#define AFX_FRAMEGRABBERTESTVIEW_H__7E92FA34_976C_11D3_B4B8_8E815E0D4B38__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FrameGrabber.h"
#include "CBitmapEx.h"

class CFrameGrabberTestView : public CView
{
protected: // create from serialization only
	CFrameGrabberTestView();
	DECLARE_DYNCREATE(CFrameGrabberTestView)

// Attributes
public:
	CFrameGrabberTestDoc* GetDocument();

	CFrameGrabber	m_FrameGrabber;
	// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFrameGrabberTestView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFrameGrabberTestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// Generated message map functions
protected:
	//{{AFX_MSG(CFrameGrabberTestView)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnUpdateFileFormat(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSource(CCmdUI* pCmdUI);
	afx_msg void OnFileSource();
	afx_msg void OnFileFormat();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in FrameGrabberTestView.cpp
inline CFrameGrabberTestDoc* CFrameGrabberTestView::GetDocument()
   { return (CFrameGrabberTestDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FRAMEGRABBERTESTVIEW_H__7E92FA34_976C_11D3_B4B8_8E815E0D4B38__INCLUDED_)

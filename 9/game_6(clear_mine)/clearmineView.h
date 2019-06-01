// clearmineView.h : interface of the CClearmineView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLEARMINEVIEW_H__BB20D5DC_19E6_11D5_86D8_0000F74D8D41__INCLUDED_)
#define AFX_CLEARMINEVIEW_H__BB20D5DC_19E6_11D5_86D8_0000F74D8D41__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CClearmineView : public CView
{
protected: // create from serialization only
	CClearmineView();
	DECLARE_DYNCREATE(CClearmineView)

// Attributes
public:
	CClearmineDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClearmineView)
	public:
	virtual void OnDraw(CDC* pDC); 
	
    // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	int HowManyMine(int a,int b);
	void TestIsMine(int a,int b);

	virtual ~CClearmineView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	int IsBegin;//开始记时
	CString time;
	int seconds;
	int second;
    int hour;
	int minute;
	int clearmines;
	int y;
	int x;
	int IsDown;
	int RectLeftTopX[10][10];
	int RectLeftTopY[10][10];
	int RectRightDownX[10][10];
	int RectRightDownY[10][10];
	int IsMine[10][10];
	//{{AFX_MSG(CClearmineView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent,CDC *pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in clearmineView.cpp
inline CClearmineDoc* CClearmineView::GetDocument()
   { return (CClearmineDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLEARMINEVIEW_H__BB20D5DC_19E6_11D5_86D8_0000F74D8D41__INCLUDED_)

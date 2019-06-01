#if !defined(AFX_BCGDOCKBAR_H__9440A463_E272_11D1_A089_00A0C9B05590__INCLUDED_)
#define AFX_BCGDOCKBAR_H__9440A463_E272_11D1_A089_00A0C9B05590__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// BCGDockBar.h : header file
//

#include "bcgcontrolbar.h"

/////////////////////////////////////////////////////////////////////////////
// CBCGDockBar window

class BCGCONTROLBARDLLEXPORT CBCGDockBar : public CControlBar
{
	DECLARE_DYNAMIC(CBCGDockBar)

// Construction / destruction
public:
    CBCGDockBar();

// Attributes
public:
    BOOL IsHorz() const;
	const CSize& GetDockedSize () const
	{
		return IsHorz() ? m_sizeHorz : m_sizeVert;
	}

// Operations
public:

// Overridables
    virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);

// Overrides
public:
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CBCGDockBar)
	public:
    virtual BOOL Create(CWnd* pParentWnd, CSize sizeDefault, UINT nID, DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_TOP);
    virtual CSize CalcFixedLayout( BOOL bStretch, BOOL bHorz );
    virtual CSize CalcDynamicLayout( int nLength, DWORD dwMode );
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL
	virtual void DoPaint(CDC* pDC);

// Implementation
public:
    virtual ~CBCGDockBar();
    void StartTracking();
    void StopTracking(BOOL bAccept);
    void OnInvertTracker(const CRect& rect);
    
    // implementation helpers
    CPoint& ClientToWnd(CPoint& point);

protected:
    CSize       m_sizeMin;
    CSize       m_sizeHorz;
    CSize       m_sizeVert;
    CSize       m_sizeFloat;
    CRect       m_rectBorder;
	CRect		m_rectGripper;
	CRect		m_rectClose;
    CRect       m_rectTracker;
    UINT        m_nDockBarID;
    CPoint      m_ptOld;
    BOOL        m_bTracking;
    BOOL        m_bInRecalcNC;
	HCURSOR		m_hcurHorzSize;
	HCURSOR		m_hcurVertSize;
	BOOL		m_bClosePressed;
	BOOL		m_bCloseFocused;

// Generated message map functions
protected:
    //{{AFX_MSG(CBCGDockBar)
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
    afx_msg void OnWindowPosChanged(WINDOWPOS FAR* lpwndpos);
    afx_msg void OnNcPaint();
    afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
    afx_msg UINT OnNcHitTest(CPoint point);
    afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnCaptureChanged(CWnd *pWnd);
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnCancelMode();
	afx_msg void OnNcLButtonUp(UINT nHitTest, CPoint point);
	//}}AFX_MSG

    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGDOCKBAR_H__9440A463_E272_11D1_A089_00A0C9B05590__INCLUDED_)

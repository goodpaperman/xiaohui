// EditBar.h : header file
//

#ifndef __EditBar_h__
#define __EditBar_h__

/////////////////////////////////////////////////////////////////////////////
// CEditBar window

class CEditBar : public CControlBar
{
	DECLARE_DYNAMIC(CEditBar)
// Construction
public:
	CEditBar();

// Attributes
public:
	virtual CSize CalcDynamicLayout(int nLength, DWORD dwMode);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditBar)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL
	void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);

// Implementation
public:
	virtual ~CEditBar();
	BOOL Create(CWnd* pParentWnd);

	// Generated message map functions
protected:
	//{{AFX_MSG(CEditBar)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg LRESULT OnGetText(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGetTextLength(WPARAM, LPARAM);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CSize m_szMRU;
};

/////////////////////////////////////////////////////////////////////////////

#endif// __EditBar_h__

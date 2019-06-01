// RealDlg.h : header file
//

#if !defined(AFX_REALDLG_H__EA410356_4D9F_4E58_8764_EB17D4D4C31D__INCLUDED_)
#define AFX_REALDLG_H__EA410356_4D9F_4E58_8764_EB17D4D4C31D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// HitTest Constants
#define DHT_CLOSE		0x01
#define DHT_CAPTION		0x02

#define LIGHT_COLOR		250
#define DARK_COLOR		100

/////////////////////////////////////////////////////////////////////////////
// CRealDlg dialog

class CRealDlg : public CDialog
{
// Construction
public:
	CRealDlg(CWnd* pParent = NULL);	// standard constructor
     
// Dialog Data
	//{{AFX_DATA(CRealDlg)
	enum { IDD = IDD_REAL_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRealDlg)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CRealDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnDestroy();
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnNcPaint();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnNcLButtonUp(UINT nHitTest, CPoint point);
	afx_msg void OnNcLButtonDblClk(UINT nHitTest, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnInitMenu(CMenu* pMenu);
	afx_msg BOOL OnNcActivate(BOOL bActive);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	void DrawLogo();
	HBITMAP m_hBmp;		
	HBITMAP m_hSys;		
	CRect	m_rectLogo, m_rectSys;
	BOOL	m_bClose;
	LONG gwl;
	CString m_strTitle;	
	int m_nKeyUp;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REALDLG_H__EA410356_4D9F_4E58_8764_EB17D4D4C31D__INCLUDED_)

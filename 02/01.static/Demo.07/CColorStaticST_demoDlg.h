// CColorStaticST_demoDlg.h : header file
//

#if !defined(AFX_CCOLORSTATICST_DEMODLG_H__D2E6DD14_7FCF_11D2_A1E0_00805F8593B2__INCLUDED_)
#define AFX_CCOLORSTATICST_DEMODLG_H__D2E6DD14_7FCF_11D2_A1E0_00805F8593B2__INCLUDED_

#include "ColorStaticST.h"	// Added by ClassView
#include "AboutDlg.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CCColorStaticST_demoDlg dialog

class CCColorStaticST_demoDlg : public CDialog
{
// Construction
public:
	CCColorStaticST_demoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCColorStaticST_demoDlg)
	enum { IDD = IDD_CCOLORSTATICST_DEMO_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCColorStaticST_demoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	LRESULT OnDangerBlink(WPARAM wParam, LPARAM lParam);
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCColorStaticST_demoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	UINT m_nDangerCount;
	CFont m_Font;
	CColorStaticST m_stcCalling;
	CColorStaticST m_stcDanger;
	CColorStaticST m_stcSTSign;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CCOLORSTATICST_DEMODLG_H__D2E6DD14_7FCF_11D2_A1E0_00805F8593B2__INCLUDED_)

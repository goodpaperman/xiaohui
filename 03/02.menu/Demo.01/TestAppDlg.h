// TestAppDlg.h : header file
//

#if !defined(AFX_TESTAPPDLG_H__3C61FD66_645C_11D3_9DDA_0004AC25CC15__INCLUDED_)
#define AFX_TESTAPPDLG_H__3C61FD66_645C_11D3_9DDA_0004AC25CC15__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTestAppDlg dialog

class CTestAppDlg : public CDialog
{
// Construction
public:
	CTestAppDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestAppDlg)
	enum { IDD = IDD_TESTAPP_DIALOG };
	CString	m_csWidth;
	int		m_nStretch;
	BOOL	m_bShowBmp;
	BOOL	m_bShow4All;
	BOOL	m_bShowSlider;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestAppDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestAppDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnPopupmenu();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CSliderCtrl m_Slider;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTAPPDLG_H__3C61FD66_645C_11D3_9DDA_0004AC25CC15__INCLUDED_)

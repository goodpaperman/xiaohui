// MixerDlg.h : header file
//

#if !defined(AFX_MIXERDLG_H__6060A299_0470_4F93_9EDB_2CC01C4EE244__INCLUDED_)
#define AFX_MIXERDLG_H__6060A299_0470_4F93_9EDB_2CC01C4EE244__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMixerDlg dialog

class CMixerDlg : public CDialog
{
// Construction
public:
	CMixerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMixerDlg)
	enum { IDD = IDD_MIXER_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMixerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

    void GetControlForLine(HMIXER hMixer, MIXERLINE& mxl); 
// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMixerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MIXERDLG_H__6060A299_0470_4F93_9EDB_2CC01C4EE244__INCLUDED_)

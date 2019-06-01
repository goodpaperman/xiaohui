// MuteDlg.h : header file
//

#if !defined(AFX_MUTEDLG_H__39694507_F4A0_11D1_9F80_006008984DF6__INCLUDED_)
#define AFX_MUTEDLG_H__39694507_F4A0_11D1_9F80_006008984DF6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CMuteDlg dialog

class CMuteDlg : public CDialog
{
// Construction
public:
	CMuteDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMuteDlg)
	enum { IDD = IDD_MUTE_DIALOG };
	BOOL	m_bMute;
	CString	m_strStat1;
	CString	m_strStat2;
	CString	m_strStat3;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMuteDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMuteDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnMute();
	afx_msg LONG OnMixerCtrlChange(UINT wParam, LONG lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	UINT m_nNumMixers;
	HMIXER m_hMixer;
	MIXERCAPS m_mxcaps;

	CString m_strDstLineName, m_strMuteControlName;
	DWORD m_dwMuteControlID;

	BOOL amdUninitialize();
	BOOL amdInitialize();
	BOOL amdGetMasterMuteControl();
	BOOL amdGetMasterMuteValue(LONG &lVal) const;
	BOOL amdSetMasterMuteValue(LONG lVal) const;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MUTEDLG_H__39694507_F4A0_11D1_9F80_006008984DF6__INCLUDED_)

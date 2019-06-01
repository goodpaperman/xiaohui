// MeterDlg.h : header file
//

#if !defined(AFX_METERDLG_H__3A48D837_F4B7_11D1_9F80_006008984DF6__INCLUDED_)
#define AFX_METERDLG_H__3A48D837_F4B7_11D1_9F80_006008984DF6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CMeterDlg dialog

class CMeterDlg : public CDialog
{
// Construction
public:
	CMeterDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMeterDlg)
	enum { IDD = IDD_METER_DIALOG };
	CProgressCtrl	m_ctrlProgress;
	CString	m_strStat1;
	CString	m_strStat2;
	CString	m_strStat3;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMeterDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMeterDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	enum { TIMER_ID = 1, TIMER_ELAPSE = 200 };

	UINT m_nTimerID;

	UINT m_nNumMixers;
	HMIXER m_hMixer;
	MIXERCAPS m_mxcaps;

	CString m_strWaveLineName, m_strMeterControlName;
	LONG m_lMinimum, m_lMaximum;
	DWORD m_dwMeterControlID;

	BOOL amdUninitialize();
	BOOL amdInitialize();
	BOOL amdGetWaveMeterControl();
	BOOL amdGetWaveMeterValue(LONG &lVal) const;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_METERDLG_H__3A48D837_F4B7_11D1_9F80_006008984DF6__INCLUDED_)

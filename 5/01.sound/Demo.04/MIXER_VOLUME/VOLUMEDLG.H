// VolumeDlg.h : header file
//

#if !defined(AFX_VOLUMEDLG_H__3A48D827_F4B7_11D1_9F80_006008984DF6__INCLUDED_)
#define AFX_VOLUMEDLG_H__3A48D827_F4B7_11D1_9F80_006008984DF6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CVolumeDlg dialog

class CVolumeDlg : public CDialog
{
// Construction
public:
	CVolumeDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CVolumeDlg)
	enum { IDD = IDD_VOLUME_DIALOG };
	CSliderCtrl	m_ctrlSlider;
	CString	m_strStat1;
	CString	m_strStat2;
	CString	m_strStat3;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVolumeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CVolumeDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg LONG OnMixerCtrlChange(UINT wParam, LONG lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	UINT m_nNumMixers;
	HMIXER m_hMixer;
	MIXERCAPS m_mxcaps;

	CString m_strDstLineName, m_strVolumeControlName;
	DWORD m_dwMinimum, m_dwMaximum;
	DWORD m_dwVolumeControlID;

	BOOL amdUninitialize();
	BOOL amdInitialize();
	BOOL amdGetMasterVolumeControl();
	BOOL amdGetMasterVolumeValue(DWORD &dwVal) const;
	BOOL amdSetMasterVolumeValue(DWORD dwVal) const;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VOLUMEDLG_H__3A48D827_F4B7_11D1_9F80_006008984DF6__INCLUDED_)

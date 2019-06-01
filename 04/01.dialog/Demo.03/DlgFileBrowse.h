#if !defined(AFX_DLGFILEBROWSE_H__942D1242_B4AD_11D3_9CE3_E7C9978DB001__INCLUDED_)
#define AFX_DLGFILEBROWSE_H__942D1242_B4AD_11D3_9CE3_E7C9978DB001__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgFileBrowse.h : header file
//

class CThreadRunningDlg;

/////////////////////////////////////////////////////////////////////////////
// CDlgFileBrowse dialog

class CDlgFileBrowse : public CFileDialog
{
	DECLARE_DYNAMIC(CDlgFileBrowse)

public:
	CDlgFileBrowse(
		CThreadRunningDlg& rThreadRunningDlg
		);

protected:
	//{{AFX_MSG(CDlgFileBrowse)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	afx_msg LPARAM OnInitFinished(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

protected:
	void OnInitDone();
	BOOL OnFileNameOK();
	void OnFolderChange();

private:
	CThreadRunningDlg& m_rThreadRunningDlg;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGFILEBROWSE_H__942D1242_B4AD_11D3_9CE3_E7C9978DB001__INCLUDED_)

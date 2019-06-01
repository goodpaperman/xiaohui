// AVCDemoDlg.h : header file
//

#if !defined(AFX_AVCDEMODLG_H__5E9B7CF6_5997_11D3_AE18_000000000000__INCLUDED_)
#define AFX_AVCDEMODLG_H__5E9B7CF6_5997_11D3_AE18_000000000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BitmapDialog.h"
#include "AVICtrl.h"	// Added by ClassView

/////////////////////////////////////////////////////////////////////////////
// CAVCDemoDlg dialog

class CAVCDemoDlg : public CBitmapDialog
{
// Construction
public:
	CAVCDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CAVCDemoDlg)
	enum { IDD = IDD_AVCDEMO_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAVCDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CAVCDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnApply();
	afx_msg void OnWindowPosChanging(WINDOWPOS FAR* lpwndpos);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CRect m_crOrigAVIWnd;
	CAVICtrl m_AviCtrl;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AVCDEMODLG_H__5E9B7CF6_5997_11D3_AE18_000000000000__INCLUDED_)

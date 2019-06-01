// dragdroptreeDlg.h : header file
//

#if !defined(AFX_DRAGDROPTREEDLG_H__29F88947_897C_11D3_A59E_00A02411D21E__INCLUDED_)
#define AFX_DRAGDROPTREEDLG_H__29F88947_897C_11D3_A59E_00A02411D21E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "dragdroptreectrl.h"
/////////////////////////////////////////////////////////////////////////////
// CDragdroptreeDlg dialog

class CDragdroptreeDlg : public CDialog
{
// Construction
public:
	CDragdroptreeDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDragdroptreeDlg)
	enum { IDD = IDD_DRAGDROPTREE_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDragdroptreeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDragdroptreeDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void PopulateTree(CDragDropTreeCtrl &treeCtrl);
	CDragDropTreeCtrl m_treeCtrl1;
	CImageList m_cImageList;
	CDragDropTreeCtrl m_treeCtrl2;
	CDragDropTreeCtrl m_treeCtrl3;
	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAGDROPTREEDLG_H__29F88947_897C_11D3_A59E_00A02411D21E__INCLUDED_)

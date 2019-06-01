#if !defined(AFX_DLGBITMAP_H__A69F7E15_69CD_11D3_9AB9_0008C7728E19__INCLUDED_)
#define AFX_DLGBITMAP_H__A69F7E15_69CD_11D3_9AB9_0008C7728E19__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgBitmap.h : header file
//

#include "DIBStatic.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgBitmap dialog

class CDlgBitmap : public CDialog
{
// Construction
public:
	CDlgBitmap(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgBitmap)
	enum { IDD = IDD_DLG_BITMAP };
	CDIBStatic	m_ActualBMP;
	int		m_Option;
	//}}AFX_DATA

	


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgBitmap)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgBitmap)
	afx_msg void OnBMP1();
	afx_msg void OnBMP2();
	afx_msg void OnBMP3();
	afx_msg void OnBMP4();
	afx_msg void OnBMP5();
	afx_msg void OnBMP6();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGBITMAP_H__A69F7E15_69CD_11D3_9AB9_0008C7728E19__INCLUDED_)

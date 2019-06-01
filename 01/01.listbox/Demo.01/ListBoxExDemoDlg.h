// ListBoxExDemoDlg.h : header file
//

#if !defined(AFX_LISTBOXEXDEMODLG_H__BF92D786_D35C_11D3_B5AC_A965B72AE035__INCLUDED_)
#define AFX_LISTBOXEXDEMODLG_H__BF92D786_D35C_11D3_B5AC_A965B72AE035__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CListBoxExDemoDlg dialog
#include "ListBoxEx.h"
#include "SHBrowseDlg.h"

class CMyListBoxEx: public CListBoxEx
{
public:

   CMyListBoxEx()
   {
      SetEditStyle( LBEX_EDITBUTTON );
      //SetEditStyle(0); 
   };

   virtual void OnBrowseButton( int iItem )
   {
       CString strDir; 
       GetText(iItem, strDir); 
      CSHBrowseDlg dlgBrowse(m_hWnd, "请选择一个目录");
      if ( dlgBrowse.DoModal((LPTSTR)(LPCTSTR)strDir) ) SetEditText( dlgBrowse.GetFullPath() );
   };

   //virtual BOOL OnBeginEditing(int nIndex)
   //{
   //    return nIndex / 2 == 0; 
   //}

   //virtual BOOL OnEndEditing( int iItem, BOOL fCanceled )
   //{
   //    return iItem % 2 == 1; 
   //}
};

class CListBoxExDemoDlg : public CDialog
{
// Construction
public:
	CListBoxExDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CListBoxExDemoDlg)
	enum { IDD = IDD_LISTBOXEXDEMO_DIALOG };
	CMyListBoxEx	m_ListBoxEx;
	//}}AFX_DATA

        CListBoxExBuddy m_ListBoxExBuddy;
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListBoxExDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CListBoxExDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//afx_msg void OnEditbutton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTBOXEXDEMODLG_H__BF92D786_D35C_11D3_B5AC_A965B72AE035__INCLUDED_)

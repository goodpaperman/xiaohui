/************************************
  REVISION LOG ENTRY
  Revision By: Mihai Filimon
  Revised on 7/21/98 10:13:49 AM
  Comments: SheetListCtrl.h : header file
 ************************************/

#if !defined(AFX_SHEETLISTCTRL_H__91E4A9F7_1FA5_11D2_864F_0040055C08D9__INCLUDED_)
#define AFX_SHEETLISTCTRL_H__91E4A9F7_1FA5_11D2_864F_0040055C08D9__INCLUDED_

#include "SheetAlpha.h"	// Added by ClassView
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CSheetListCtrl window

#include <afxtempl.h>

class CSheetListCtrl : public CListCtrl
{
// Construction
public:
	CSheetListCtrl();
	virtual BOOL SubclassWindow( HWND hWnd );
	virtual CSheetAlpha& GetSheetControl() {return m_wndSheet;};
	virtual ~CSheetListCtrl();

// Attributes
public:

// Operations
public:
	int SumWidthColumns();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSheetListCtrl)
	protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

	// Generated message map functions
protected:
	//{{AFX_MSG(CSheetListCtrl)
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	CSheetAlpha m_wndSheet;
private:
	void ActivateScrollBar();
	virtual BOOL NeedScroll();
	int m_nInsideCalc;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHEETLISTCTRL_H__91E4A9F7_1FA5_11D2_864F_0040055C08D9__INCLUDED_)

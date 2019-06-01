/************************************
  REVISION LOG ENTRY
  Revision By: Mihai Filimon
  Revised on 7/22/98 6:01:36 PM
  Comments: FilterListCtrl.h: interface for the CFilterListCtrl class.
 ************************************/

#if !defined(AFX_FILTERLISTCTRL_H__261E8541_2174_11D2_8651_0040055C08D9__INCLUDED_)
#define AFX_FILTERLISTCTRL_H__261E8541_2174_11D2_8651_0040055C08D9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "SheetListCtrl.h"

#define IDLCALL 0x1971

class CFilterListCtrl : public CSheetListCtrl  
{
public:
	void Refresh();
	CFilterListCtrl(int nFilterColumn = 0);
	virtual ~CFilterListCtrl();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFilterListCtrl)
	protected:
	virtual void PreSubclassWindow();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

	// Generated message map functions
protected:
	virtual BOOL IsEqual(LPCTSTR lpszSource, LPCTSTR lspzDestination);
	virtual void Fill(LPCTSTR lpszFilter);
	//{{AFX_MSG(CFilterListCtrl)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	int m_nFilterColumn;
	int m_nOutsideListCtrl;
	CListCtrl m_lcAll;
};

#endif // !defined(AFX_FILTERLISTCTRL_H__261E8541_2174_11D2_8651_0040055C08D9__INCLUDED_)

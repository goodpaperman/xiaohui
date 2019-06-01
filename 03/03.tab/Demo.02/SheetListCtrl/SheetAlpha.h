/************************************
  REVISION LOG ENTRY
  Revision By: Mihai Filimon
  Revised on 7/21/98 10:13:59 AM
  Comments: SheetAlpha.h: interface for the CSheetAlpha class.
 ************************************/

#if !defined(AFX_SHEETALPHA_H__91E4A9F5_1FA5_11D2_864F_0040055C08D9__INCLUDED_)
#define AFX_SHEETALPHA_H__91E4A9F5_1FA5_11D2_864F_0040055C08D9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "SheetsWnd.h"
#include "DragPage.h"

class CSheetAlpha : public CSheetsWnd  
{
public:
	static CString& TranslateMessage(DWORD dw);
	virtual void RemovePage(int nPage);
	virtual void RemovePage(LPCTSTR lpszTitle);
	virtual void ShowScrollBar(BOOL bShow = TRUE);
	virtual int AddPage(LPCTSTR lpszTitle);
	virtual CScrollBar& GetScrollBar();
	virtual void SetActiveView(CWnd* pView);
	virtual CString GetViewTitle(CWnd* pView);
	virtual CWnd* GetActiveView();
	CSheetAlpha();
	virtual ~CSheetAlpha();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSheetAlpha)
	//}}AFX_VIRTUAL
protected:
	virtual CRect EraseExclude();
	virtual void Draw(CDC* pDC);
	virtual CRect GetSplitterRect();
	virtual CWnd* GetNextView();
	virtual CWnd* GetFirstView();
	virtual int GetPageIndex(LPCTSTR lpszTitle);
	virtual void Resize(HWND hWndParent);
	virtual void EndDrag(CPoint ptn);
	virtual void TrackDrag(CPoint ptn);
	virtual void BeginDrag(CPoint ptn);
		//{{AFX_MSG(CSheetAlpha)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CDragPage m_sPageDrag;
	BOOL bSplitter();
	void RecalcDrawRect();
	int m_nDXSplitter;
	double m_fDXScrollBar;
	CScrollBar m_sbHorz;
	CStringArray m_strTitles;
	int m_nActive, m_nFind;
	CPoint m_bPointCaptured;
	BOOL m_bCaptured;
};


#endif // !defined(AFX_SHEETALPHA_H__91E4A9F5_1FA5_11D2_864F_0040055C08D9__INCLUDED_)

#if !defined(AFX_BCGPOPUPMENUBAR_H__A6E1AD76_D511_11D1_A64D_00A0C93A70EC__INCLUDED_)
#define AFX_BCGPOPUPMENUBAR_H__A6E1AD76_D511_11D1_A64D_00A0C93A70EC__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// BCGPopupMenuBar.h : header file
//

#include "bcgcontrolbar.h"
#include "BCGToolBar.h"

class CBCGToolbarMenuButton;

/////////////////////////////////////////////////////////////////////////////
// CBCGPopupMenuBar command target

class BCGCONTROLBARDLLEXPORT CBCGPopupMenuBar : public CBCGToolBar
{
	friend class CBCGPopupMenu;

	DECLARE_SERIAL(CBCGPopupMenuBar)

public:
	CBCGPopupMenuBar();
	virtual ~CBCGPopupMenuBar();

// Attributes
public:
	UINT GetDefaultMenuId () const
	{
		return m_uiDefaultMenuCmdId;
	}

	int GetOffset () const
	{
		return m_iOffset;
	}

	void SetOffset (int iOffset)
	{
		m_iOffset = iOffset;
		if (m_iOffset != iOffset)
		{
			AdjustLocations ();
		}
	}

protected:
	UINT					m_uiDefaultMenuCmdId;
	CBCGToolbarMenuButton*	m_pDelayedPopupMenuButton;
	BOOL					m_bFirstClick;
	int						m_iOffset;	// rows

// Operations
public:
	BOOL ImportFromMenu (HMENU hMenu);
	HMENU ExportToMenu () const;

	void StartPopupMenuTimer (CBCGToolbarMenuButton* pMenuButton);
	CBCGToolBar* FindDestBar (CPoint point);

protected:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGPopupMenuBar)
	//}}AFX_VIRTUAL

	virtual BOOL OnSendCommand (const CBCGToolbarButton* pButton);
	virtual void AdjustLocations ();
	virtual int GetRowHeight () const;
	virtual void DrawSeparator (CDC* pDC, const CRect& rect, BOOL bHorz);
	virtual CSize CalcSize ();
	virtual BOOL AllowSelectDisabled () const	{	return TRUE;	}
	virtual int FindDropIndex (const CPoint p, CRect& rectDrag) const;
	virtual void DrawDragMarker (CDC* pDC);
	virtual CBCGToolbarButton* CreateDroppedButton (COleDataObject* pDataObject);
	virtual void OnChangeHot (int iHot);
	virtual BOOL OnKey (UINT nChar);
	virtual BOOL OnSetDefaultButtonText (CBCGToolbarButton* pButton);
	virtual BOOL EnableContextMenuItems (CBCGToolbarButton* pButton, CMenu* pPopup);

	virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBCGPopupMenuBar)
	afx_msg void OnNcPaint();
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGPOPUPMENUBAR_H__A6E1AD76_D511_11D1_A64D_00A0C93A70EC__INCLUDED_)

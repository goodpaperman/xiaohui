/////////////////////////////////////////////////////////////////////////////
// This is an extension to the MFC C++ library.
// Copyright (C) 1997-1998 ACPSoft
// All rights reserved.
//
// This source code is only intended as a building
// tool to aid your own development.  This code is
// under the license agreement provided with the
// software. By using this code in your own project(s)
// you agree to the terms in that license.
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRIPDIALOGBAR_H__E3F8F9A2_CBC9_11D1_9783_726AA5000000__INCLUDED_)
#define AFX_GRIPDIALOGBAR_H__E3F8F9A2_CBC9_11D1_9783_726AA5000000__INCLUDED_

#ifndef NGTB_PROJECT
#define NGTB_EXPORT __declspec(dllimport)
#else
#define NGTB_EXPORT __declspec(dllexport)
#endif


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <afxpriv.h>

/////////////////////////////////////////////////////////////////////////////
// Classes declared in this file

//CObject
	//CmdTarget
		//CWnd
			//CControlbar
				//CDialogBar
					class CInitDialogBar;
						class CGripDialogBar;
		//CEdit
			class CGripControl;

//CDockContext
	class CExDockContext;

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// InitDialogBar.h: interface for the CInitDialogBar class.
/////////////////////////////////////////////////////////////////////////////

class NGTB_EXPORT CInitDialogBar : public CDialogBar
{
	DECLARE_DYNAMIC(CInitDialogBar)

// Construction / Destruction
public:
	CInitDialogBar();
	virtual ~CInitDialogBar();

// Attributes
public:

// Operations
public:
	BOOL Create(CWnd * pParentWnd, UINT nIDTemplate, UINT nStyle, UINT nID);
	BOOL Create(CWnd * pParentWnd, LPCTSTR lpszTemplateName, UINT nStyle, UINT nID);


// Overrides
public:
	virtual BOOL OnInitDialogBar();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInitDialogBar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

// Implementation
public:

// Generated message map functions
protected:
	//{{AFX_MSG(CInitDialogBar)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// class CGripDialogBar: interface for the CGripDialogBar class.
/////////////////////////////////////////////////////////////////////////////

// GBS_STYLE Constants See constructor
// for use of these styles
#define GBS_DOCKAPPST	0x01
#define GBS_DOCKBUTTON	0x02
#define GBS_DOCKCLOSE	0x04
#define GBS_DOCKTITLE	0x08
#define GBS_NOGRADIENT	0x10
#define GBS_NOGRIPBARS	0x20
#define GBS_USECOLOR	0x40


class NGTB_EXPORT CGripDialogBar : public CInitDialogBar  
{
	friend CGripControl;

	DECLARE_DYNAMIC(CGripDialogBar)

// Construction / Destruction
public:

	CGripDialogBar();
	CGripDialogBar(UINT n_ID, DWORD Style = GBS_DOCKCLOSE | GBS_USECOLOR, COLORREF clr = RGB(192,192,192));
	virtual ~CGripDialogBar();

// Attributes
public:
protected:

	BOOL m_bActive;
	CGripControl* m_GripBar;
	
// Operations
public:

	void GetCaptionRect(CRect* rect);
	DWORD GetGripStyle();
	void ModifyGripStyle(DWORD remove, DWORD add);
	void SetActiveState(UINT nState);
	void StartDrag(CPoint point);
	void ToggleDocking();
	void View(CFrameWnd* fWnd, BOOL state);
		
// Overrides
public:
protected:

	virtual BOOL OnInitDialogBar();
	
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInitDialogBar)
	//}}AFX_VIRTUAL

// Implementation
public:
protected:

	void ExcludeCaption(CDC* pDC);
	void PaintRect(CDC* dc, int x, int y, int w, int h, COLORREF color);
	void RecalcLayout();
			
// Generated message map functions
public:
protected:

	//{{AFX_MSG(CInitDialogBar)
	afx_msg void OnClose();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg BOOL OnNcActivate(BOOL bActive);
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// class CGripControl: interface for the CGripControl class.
/////////////////////////////////////////////////////////////////////////////

// Hit Test Constants
#define GHT_CLOSE		0x01
#define GHT_DOCKBUT		0x02
#define GHT_CAPTION		0x03

class NGTB_EXPORT CGripControl : public CEdit
{
	friend CGripDialogBar;

	DECLARE_DYNCREATE(CGripControl)

// Construction
public:
	CGripControl();
	CGripControl(UINT nID, DWORD Style, COLORREF clr);
	virtual ~CGripControl();

// Attributes
public:
protected:

	CBitmap m_bmpCap[2];
	CFont m_fontCap;
	CFont m_fontTitle;
	CGripDialogBar* m_pControlBar;
	CRect m_rcCap;
	CRect m_rcIcon;
	CRect m_rcClose;
	CString m_appString;
	COLORREF m_ColorCap;
	DWORD m_GBStyle;
	DWORD m_prevHitTest;
	UINT m_nID;

// Operations
public:

	void Abolish();
	void Fasten(CGripDialogBar* pControlBar);
	CString GetBarTitle();
	void GetCaptionRect(CRect* rect);

// Overrides
public:
protected:

	virtual void CreateFonts();
	virtual void OnNcDraw(CDC* pDC);

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGripControl)
	//}}AFX_VIRTUAL

// Implementation
public:
protected:

	void DrawOnBitmap(BOOL bActive, CDC* pMemDC, CRect* pRC);
	DWORD HitTest(CPoint pt);
	void PaintRect(CDC* dc, int x, int y, int w, int h, COLORREF color);
	void UpdateBitmap(BOOL bActive, CDC* pMemDC, CDC* pWinDC);

// Generated message map functions
public:
protected:
	//{{AFX_MSG(CGripControl)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	afx_msg void OnSysColorChange();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// class CExDockContext: interface for the CExDockContext class.
/////////////////////////////////////////////////////////////////////////////

class NGTB_EXPORT CExDockContext : public CDockContext  
{

// Construction / Destruction
public:

	CExDockContext(CControlBar* pBar);
	virtual ~CExDockContext();

// Overrides
public:

	virtual void StartDrag(CPoint pt);

protected:

	virtual void AdjustWindowForFloat(CRect& rect);
	virtual BOOL Tracking();
};

//////////////////////////////////////////////

#endif // !defined(AFX_GRIPDIALOGBAR_H__E3F8F9A2_CBC9_11D1_9783_726AA5000000__INCLUDED_)
//////////////////////////////////////////////
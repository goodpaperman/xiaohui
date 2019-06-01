#if !defined(AFX_HOTBUTTON_H__7DB403D1_46D1_11D4_AB66_005004CF7A2A__INCLUDED_)
#define AFX_HOTBUTTON_H__7DB403D1_46D1_11D4_AB66_005004CF7A2A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// HotButton.h : header file
//

// notification sent when the hot part of the button is clicked
#define BN_HOT_CLICKED          0x101

/////////////////////////////////////////////////////////////////////////////
// CHotButton window

class CHotButton : public CButton
{
// Construction
public:
	CHotButton();

// Attributes
private:
	CImageList	m_ImageList;	// internal image list
	CImageList	*m_pAppImageList;	// app defined image list, set via SetAppBmp()
	CImageList	*m_pCurImageList;	// the current image list, either internal or app defined
	CRect	m_rectBMP;					// size of the bitmap
	CRect	m_rectX;						// where image area in the button client rect
	CRect	m_rectHotX;					// the hot area of the button
	CRect	m_rectFocus;				// text drawing area and focus rect
	BOOL	m_bHotAreaActive;		// if the image area is hot
	BOOL	m_bIsHot;						// if image area is hot
	BOOL	m_bShowBitmap;			// if to paint the bitmap
	UINT	m_iBitmap;					// index of current bitmap

// Operations
public:
	void	EnableHotSpot(BOOL bEnable = TRUE);	// enable/disable the hot spot
	void	ShowBitmap(BOOL bShow = TRUE);
	void	UseXBitmap()					{ m_pCurImageList = &m_ImageList; UseInternalBitmap(0); }
	void	UseCheckBitmap()			{ m_pCurImageList = &m_ImageList; UseInternalBitmap(1); }
	void	UseFolderBitmap()			{ m_pCurImageList = &m_ImageList; UseInternalBitmap(2); }
	void	UsePaperBitmap()			{ m_pCurImageList = &m_ImageList; UseInternalBitmap(3); }
	void	UsePrinterBitmap()		{ m_pCurImageList = &m_ImageList; UseInternalBitmap(4); }
	void	UseRightArrowBitmap()	{ m_pCurImageList = &m_ImageList; UseInternalBitmap(5); }
	void	UseLeftArrowBitmap()	{ m_pCurImageList = &m_ImageList; UseInternalBitmap(6); }
	void	UseLEDBitmap()				{ m_pCurImageList = &m_ImageList; UseInternalBitmap(7); }
	void	UseEllipseBitmap()		{ m_pCurImageList = &m_ImageList; UseInternalBitmap(8); }
	void	UseBinocularBitmap()	{ m_pCurImageList = &m_ImageList; UseInternalBitmap(9); }
	void	UseClockBitmap()			{ m_pCurImageList = &m_ImageList; UseInternalBitmap(10); }
	void	UseRedFlagBitmap()		{ m_pCurImageList = &m_ImageList; UseInternalBitmap(11); }
	void	UseBannedBitmap()			{ m_pCurImageList = &m_ImageList; UseInternalBitmap(12); }
	void	UseInternalBitmap(int iBitmap);		// use given bitmap in internal image list
	void	UseBitmap(int iBitmap);						// use given bitmap in the current image list
	void	UseAppBitmap(int iBitmap);				// use given bitmap in the app defined image list
	void	SetAppBmp(UINT nBitmapID, int cx, COLORREF crMask);

	// tooltip
public:
	CToolTipCtrl m_ToolTip;
	void SetTooltipText(LPCSTR szText, BOOL bActivate = TRUE);
	void ActivateTooltip(BOOL bEnable = TRUE);
private:
	void InitToolTip();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHotButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CHotButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CHotButton)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnCaptureChanged(CWnd *pWnd);
	afx_msg UINT OnGetDlgCode();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HOTBUTTON_H__7DB403D1_46D1_11D4_AB66_005004CF7A2A__INCLUDED_)

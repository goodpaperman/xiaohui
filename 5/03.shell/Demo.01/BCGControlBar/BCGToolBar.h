//
// bcgtoolbar.h : definition of CBCGToolBar
//
// This code is based on the Microsoft Visual C++ sample file
// TOOLBAR.C from the OLDBARS example
//

#ifndef _TOOLBAR_H_
#define _TOOLBAR_H_

#ifndef __AFXTEMPL_H__
	#include "afxtempl.h"
#endif

#include "bcgcontrolbar.h"
#include "BCGToolbarDropTarget.h"
#include "BCGToolbarDropSource.h"
#include "BCGToolBarImages.h"
#include "BCGToolbarButton.h"

class CBCGToolbarMenuButton;

//----------------------------------
// BCGToolbar notification messages:
//----------------------------------
BCGCONTROLBARDLLEXPORT extern UINT BCGM_TOOLBARMENU;
BCGCONTROLBARDLLEXPORT extern UINT BCGM_CUSTOMIZETOOLBAR;
BCGCONTROLBARDLLEXPORT extern UINT BCGM_CREATETOOLBAR;
BCGCONTROLBARDLLEXPORT extern UINT BCGM_DELETETOOLBAR;
BCGCONTROLBARDLLEXPORT extern UINT BCGM_CUSTOMIZEHELP;
BCGCONTROLBARDLLEXPORT extern UINT BCGM_RESETTOOLBAR;

static const int dwDefaultToolbarStyle = (WS_CHILD | WS_VISIBLE | CBRS_TOP | 
										  CBRS_GRIPPER | CBRS_HIDE_INPLACE);

class BCGCONTROLBARDLLEXPORT CBCGToolBar : public CControlBar
{
	friend class CBCGToolbarDropTarget;
	friend class CToolbarsPage;
	friend class CButtonsTextList;

	DECLARE_SERIAL(CBCGToolBar)

	//--------------
	// Construction:
	//--------------
public:
	CBCGToolBar();
	virtual BOOL Create(CWnd* pParentWnd,
			DWORD dwStyle = dwDefaultToolbarStyle,
			UINT nID = AFX_IDW_TOOLBAR);
	virtual BOOL CreateEx(CWnd* pParentWnd, DWORD dwCtrlStyle = TBSTYLE_FLAT,
		DWORD dwStyle = dwDefaultToolbarStyle,
		CRect rcBorders = CRect(1, 1, 1, 1),
		UINT nID = AFX_IDW_TOOLBAR);

	//----------------------------------------------------------------
	// Set toolbar buttons image resources.
	// You should use SINGLE CBCGToolBarImages for ALL your toolbars!
	//----------------------------------------------------------------
	static BOOL SetUserImages (CBCGToolBarImages* pUserImages);

	//--------------------------------
	// Dimension manipulation methods:
	//--------------------------------
	static void SetSizes (SIZE sizeButton, SIZE sizeImage);
	static void SetMenuSizes (SIZE sizeButton, SIZE sizeImage);
	static CSize GetMenuImageSize ();
	static CSize GetMenuButtonSize ();

	void SetHeight (int cyHeight);

	//-----------------
	// Toolbar context:
	//-----------------
	BOOL LoadBitmap (UINT uiResID, UINT uiColdResID = 0, UINT uiMenuResID = 0, BOOL bLocked = FALSE);
	BOOL LoadToolBar (UINT uiResID, UINT uiColdResID = 0, UINT uiMenuResID = 0, BOOL bLocked = FALSE);

	//----------------------------
	// Toolbar buttons add/remove:
	//----------------------------
	BOOL SetButtons(const UINT* lpIDArray, int nIDCount);

	int InsertButton (const CBCGToolbarButton& button, int iInsertAt = -1);
	int InsertSeparator (int iInsertAt = -1);
	
	BOOL RemoveButton (int iIndex);
	void RemoveAllButtons ();

	static BOOL IsLastCommandFromButton (CBCGToolbarButton* pButton);
	static BOOL AddToolBarForImageCollection (UINT uiResID);

	static void SetNonPermittedCommands (CList<UINT, UINT>& lstCommands);
	static BOOL IsCommandPermitted (UINT uiCmd)
	{
		return m_lstUnpermittedCommands.Find (uiCmd) == NULL;
	}

	virtual int GetRowHeight () const
	{
		return m_bMenuMode && m_sizeMenuButton.cy > 0 ? 
			m_sizeMenuButton.cy :
			m_sizeButton.cy;
	}

	virtual int GetColumnWidth () const
	{
		return m_bMenuMode && m_sizeMenuButton.cx > 0 ? 
			m_sizeMenuButton.cx :
			m_sizeButton.cx;
	}

	static void SetHelpMode (BOOL bOn = TRUE);
	void Deactivate ();
	void RestoreFocus ();

	//------------
	// Attributes:
	//------------
public: 

	// standard control bar things
	int CommandToIndex(UINT nIDFind) const;
	UINT GetItemID(int nIndex) const;
	virtual void GetItemRect(int nIndex, LPRECT lpRect) const;
	UINT GetButtonStyle(int nIndex) const;
	void SetButtonStyle(int nIndex, UINT nStyle);

	int GetCount () const;
	int ButtonToIndex(const CBCGToolbarButton* pButton) const;
	CBCGToolbarButton* GetButton (int iIndex) const;

	// Find all buttons specified by the given command ID from the all
	// toolbars:
	static int GetCommandButtons (UINT uiCmd, CObList& listButtons);
	
	static BOOL SetCustomizeMode (BOOL bSet = TRUE);
	static BOOL IsCustomizeMode ()
	{
		return m_bCustomizeMode;
	}

	static CBCGToolBar* FromHandlePermanent (HWND hwnd);
	static CBCGToolBarImages* GetImages ()
	{
		return &m_Images;
	}
	static CBCGToolBarImages* GetUserImages ()
	{
		return m_pUserImages;
	}

	static int GetDefaultImage (UINT uiID)
	{
		int iImage;
		if (m_DefaultImages.Lookup (uiID, iImage))
		{
			return iImage;
		}

		return -1;
	}

	int GetImagesOffset () const
	{
		return m_iImagesOffset;
	}

	CBCGToolbarButton* GetHighlightedButton () const;

	static void SetHotTextColor (COLORREF clrText);
	static COLORREF GetHotTextColor ();

	void SetHotBorder (BOOL bShowHotBorder)
	{
		m_bShowHotBorder = bShowHotBorder;
	}

	BOOL GetHotBorder () const
	{
		return m_bShowHotBorder;
	}

	void SetGrayDisabledButtons (BOOL bGrayDisabledButtons)
	{
		m_bGrayDisabledButtons = bGrayDisabledButtons;
	}

	BOOL GetGrayDisabledButtons () const
	{
		return m_bGrayDisabledButtons;
	}

	//------------------------------------------------------
	// Enable/disable quick customization mode ("Alt+drag"):
	//------------------------------------------------------
	static void EnableQuickCustomization (BOOL bEnable = TRUE)
	{
		m_bAltCustomization = bEnable;
	}

public:
	// for changing button info
	void GetButtonInfo(int nIndex, UINT& nID, UINT& nStyle, int& iImage) const;
	void SetButtonInfo(int nIndex, UINT nID, UINT nStyle, int iImage);

	BOOL SetButtonText(int nIndex, LPCTSTR lpszText);
	CString GetButtonText( int nIndex ) const;
	void GetButtonText( int nIndex, CString& rString ) const;

	// Save/load toobar state + buttons:
	void Serialize (CArchive& ar);
	virtual BOOL LoadState (LPCTSTR lpszProfileName, int nIndex = -1, UINT uiID = (UINT) -1);
	virtual BOOL SaveState (LPCTSTR lpszProfileName, int nIndex = -1, UINT uiID = (UINT) -1);
	virtual BOOL RemoveStateFromRegistry (LPCTSTR lpszProfileName, int nIndex = -1, UINT uiID = (UINT) -1);
	static BOOL LoadParameters (LPCTSTR lpszProfileName);
	static BOOL SaveParameters (LPCTSTR lpszProfileName);

	virtual BOOL CanBeRestored () const;
	virtual BOOL CanBeClosed () const
	{
		return TRUE;
	}

	virtual BOOL RestoreOriginalstate ();
	virtual void OnReset () {}

	virtual void AdjustLayout ();

	virtual BOOL PrevMenu ();
	virtual BOOL NextMenu ();
	CBCGToolbarMenuButton* GetDroppedDownMenu (int* pIndex = NULL) const;

	BOOL SetHot (CBCGToolbarButton *pMenuButton);
	virtual void OnChangeHot (int iHot);

	virtual BOOL OnSetDefaultButtonText (CBCGToolbarButton* pButton);

	BOOL IsDragButton (const CBCGToolbarButton* pButton) const
	{
		return pButton == m_pDragButton;
	}

// Implementation
public:
	virtual ~CBCGToolBar();

	virtual CSize CalcFixedLayout(BOOL bStretch, BOOL bHorz);
	virtual CSize CalcDynamicLayout (int nLength, DWORD dwMode);

	virtual CSize CalcSize (BOOL bVertDock);
	int WrapToolBar (int nWidth);

protected:
	virtual CSize CalcLayout (DWORD dwMode, int nLength = -1);
	void  SizeToolBar (int nLength, BOOL bVert = FALSE);

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	int  InsertButton (CBCGToolbarButton* pButton, int iInsertAt = -1);
	void InvalidateButton(int nIndex);
	void UpdateButton(int nIndex);

	virtual BOOL DrawButton (CDC* pDC, CBCGToolbarButton* pButton, 
		CBCGToolBarImages* pImages, BOOL bHighlighted);
	void DrawGripper (CDC* pDC);
	void DrawBorders(CDC* pDC, CRect& rect);
	virtual void DrawDragMarker (CDC* pDC);

	void RebuildAccelerationKeys ();

protected:
	static CBCGToolBarImages	m_Images;			// Shared toolbar images
	static CBCGToolBarImages	m_ColdImages;		// Shared toolbar "cold" images
	static CBCGToolBarImages	m_MenuImages;		// Shared menu images
	static CBCGToolBarImages*	m_pUserImages;		// Shared user-defined images

	CBCGToolBarImages	m_ImagesLocked;				// "Locked" toolbar images
	CBCGToolBarImages	m_ColdImagesLocked;			// "Locked" toolbar "cold" images
	CBCGToolBarImages	m_MenuImagesLocked;			// "Locked" toolbar menu images
	BOOL				m_bLocked;

	static CMap<UINT, UINT, int, int>	m_DefaultImages;

	static CSize m_sizeButton;			// size of button
	static CSize m_sizeImage;			// size of glyph
	static CSize m_sizeMenuButton;		// size of button on the menu
	static CSize m_sizeMenuImage;		// size of image on the menu

	int m_iButtonCapture;       // index of button with capture (-1 => none)
	int m_iHighlighted;			// highlighted button index
	int m_iSelected;			// selected button index
	int	m_iHot;

	CObList	m_Buttons;
	CBCGToolbarDropTarget	m_DropTarget;
	
	static CBCGToolbarDropSource m_DropSource;
	static BOOL m_bCustomizeMode;

	DROPEFFECT	m_prevDropEffect;
	int			m_iDragIndex;
	CRect		m_rectDrag;
	CPen		m_penDrag;
	CBCGToolbarButton* m_pDragButton;
	CPoint		m_ptStartDrag;
	BOOL		m_bIsDragCopy;

	BOOL		m_bStretchButton;
	CRect		m_rectTrack;

	int			m_iImagesOffset;
	UINT		m_uiOriginalResID;	// Toolbar resource ID

	BOOL		m_bTracked;
	CPoint		m_ptLastMouse;

	BOOL		m_bMenuMode;

	CWnd*		m_pWndLastCapture;
	HWND		m_hwndLastFocus;

	static COLORREF	m_clrTextHot;
	
	static HHOOK m_hookMouseHelp;	// Mouse hook for the help mode
	static CBCGToolBar* m_pLastHookedToolbar;

	CMap<UINT, UINT&, CBCGToolbarButton*, CBCGToolbarButton*&>	m_AcellKeys;	// Keyborad acceleration keys

	static BOOL m_bShowTooltips;
	static BOOL m_bShowShortcutKeys;

	static CList<UINT, UINT> m_lstUnpermittedCommands;

	BOOL		m_bShowHotBorder;
	BOOL		m_bGrayDisabledButtons;

	static BOOL	m_bAltCustomization;

	virtual BOOL OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point);
	virtual DROPEFFECT OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	virtual void OnDragLeave();
	virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);

	virtual void DoPaint(CDC* pDC);
	virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);
	virtual int HitTest(CPoint point);
	virtual int OnToolHitTest(CPoint point, TOOLINFO* pTI) const;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual DWORD RecalcDelayShow(AFX_SIZEPARENTPARAMS* lpLayout);

	virtual int FindDropIndex (const CPoint point, CRect& rectDrag) const;
	virtual void AdjustLocations ();

	virtual BOOL OnSendCommand (const CBCGToolbarButton* /*pButton*/)	{	return FALSE;	}

	virtual BOOL AllowSelectDisabled () const	{	return FALSE;	}

	virtual void DrawSeparator (CDC* pDC, const CRect& rect, BOOL bHorz);
	virtual CBCGToolbarButton* CreateDroppedButton (COleDataObject* pDataObject);
	virtual BOOL OnKey (UINT /*nChar*/)				{	return FALSE;	}
	virtual void OnCustomizeMode (BOOL bSet);

	virtual BOOL EnableContextMenuItems (CBCGToolbarButton* pButton, CMenu* pPopup);

	void AddRemoveSeparator (const CBCGToolbarButton* pButton,
						const CPoint& ptStart, const CPoint& ptDrop);
	void ShowCommandMessageString (UINT uiCmdId);

	static LRESULT CALLBACK BCGToolBarMouseProc (int nCode, WPARAM wParam, LPARAM lParam);

	BOOL DropDownMenu (CBCGToolbarButton* pButton);
	
	//{{AFX_MSG(CBCGToolBar)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnCancelMode();
	afx_msg void OnSysColorChange();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnToolbarAppearance();
	afx_msg void OnToolbarDelete();
	afx_msg void OnToolbarImage();
	afx_msg void OnToolbarImageAndText();
	afx_msg void OnToolbarStartGroup();
	afx_msg void OnToolbarText();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnWindowPosChanged(WINDOWPOS FAR* lpwndpos);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnBcgbarresToolbarReset();
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
	afx_msg void OnNcPaint();
	afx_msg UINT OnNcHitTest(CPoint point);
	afx_msg void OnBcgbarresCopyImage();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	afx_msg void OnContextMenu(CWnd*, CPoint point);
	afx_msg LRESULT OnMouseLeave(WPARAM,LPARAM);
	afx_msg LRESULT OnHelpHitTest(WPARAM,LPARAM);
	DECLARE_MESSAGE_MAP()
};

#endif //!_TOOLBAR_H_

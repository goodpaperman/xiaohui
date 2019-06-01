#ifndef __WINDOWMANAGER_H__
#define __WINDOWMANAGER_H__

#ifndef __AFXTEMPL_H__
#pragma message("Include <afxtempl.h> in your stdafx.h to avoid this message")
#include <afxtempl.h>
#endif

////////////////////////////////////////////////////////////////////////////////
// Forward declaration

class CViewManager;
#define  CMyMainFrameClass CMainFrame	//TODO: Please change the CMainFrame to your main frame
class CMyMainFrameClass;

///////////////////////////////////////////////////////////
// CDocumentList declaration

class CDocumentList : public CList<CDocument*, CDocument*>
{
public:
// Constuction
	CDocumentList();  // To automatically enumerates the documents in a given application
// Destruction
	~CDocumentList(); // To empty and destroy the list when out of scope
	
// Operations
	CDocument* GetNextDocument();  // Gets next document object
	
// Prevent any copying and assignment of CDocumentList objects
private:
	CDocumentList(const CDocumentList&);
	const CDocumentList& operator=(const CDocumentList&);
	
// Implementation
private:
// Keep the current position in the document list
	POSITION m_CurPosInDocList;
};


/////////////////////////////////////////////////////////////////////////////
// CWindowDlg dialog

class CWindowDlg : public CDialog
{
// Construction
public:
	CWindowDlg(CMDIFrameWnd *pMDIFrame);   

// Dialog Data
	//{{AFX_DATA(CWindowDlg)
	enum { IDD = IDD_WINDOW_MANAGE };
	CListBox	m_wndList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWindowDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void  MDIMessage(UINT uMsg,WPARAM flag);
	void  FillWindowList(void);
	void  SelActive(void);
	void  UpdateButtons(void);

	CMDIFrameWnd  *m_pMDIFrame;

	// Generated message map functions
	//{{AFX_MSG(CWindowDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnSelChange();
	afx_msg void OnSave();
	afx_msg void OnActivate();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnUpdateUI(CCmdUI * pCmdUI);
	afx_msg void OnTileHorz();
	afx_msg void OnMinimize();
	afx_msg void OnTileVert();
	afx_msg void OnCascade();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CMDIClient window

class CMDIClient : public CWnd
{
// Construction
public:
	CMDIClient();

// Attributes
public:

protected:
	CString       m_strWindows;
	HMENU	      m_hMenuWindow;
	CMyMainFrameClass*   m_pMDIFrame;

	// Full Screen mode support
	BOOL          m_bToolBarVisible;
	BOOL          m_bStatusBarVisible;
	CRect         m_rcMainFrame;
	BOOL          m_bMaxChild;
	CToolBar*     m_pwndFullScrnToolBar;

private:
	void FullScreenOff();
	void FullScreenOn();
	CSize         m_sizeClient;
	CViewManager* m_pViewManager;
	BOOL          m_bFullScreen;        // TRUE for "On" mode, FALSE for "Off"
	BOOL          m_bFirstTime;

// Operations
public:
	void ManageWindows(CMDIFrameWnd *pMDIFrame);
    BOOL SubclassMDIClient(CMDIFrameWnd* pMDIFrameWnd, 
		CViewManager* pViewManager, UINT uID = ID_VIEW_VIEWTAB);

	BOOL IsFullScreen() { return m_bFullScreen; }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMDIClient)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	void RestoreMainFrameState(UINT nCmdShow);
	void SaveMainFrameState();
	virtual ~CMDIClient();
	
protected:
	COLORREF m_crBkColor;

	// Generated message map functions
protected:
	//{{AFX_MSG(CMDIClient)
	afx_msg LRESULT OnRefreshMenu(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnSetMenu(WPARAM wParam,LPARAM lParam);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnWindowManage();
	afx_msg void OnWindowNext();
	afx_msg void OnWindowPrevious();
	afx_msg void OnWindowSaveAll();
	afx_msg void OnWindowCloseAll();
	afx_msg void OnViewFullscreen();
	afx_msg void OnUpdateViewFullscreen(CCmdUI* pCmdUI);
	afx_msg void OnTabView();
	afx_msg void OnUpdateTabView(CCmdUI* pCmdUI);
	afx_msg void OnUpdateWindowManage(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg LRESULT OnMDICreate(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMDIDestroy(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

#endif

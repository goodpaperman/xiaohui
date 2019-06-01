// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include <wininet.h>
#include "BCGIEDemo.h"
#include "BCGIEDemoDoc.h"
#include "BCGIEDemoView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define FIRST_FAVORITE_COMMAND	0xe00
#define LAST_FAVORITE_COMMAND	0xfff

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

#define CONTROL_BARS	_T("Control Bars")

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_COMMAND(ID_LINK_1, OnLink1)
	ON_COMMAND(ID_VIEW_ADDRESS_BAR, OnViewAddressBar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ADDRESS_BAR, OnUpdateViewAddressBar)
	ON_COMMAND(ID_VIEW_LINKS_BAR, OnViewLinksBar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_LINKS_BAR, OnUpdateViewLinksBar)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_VIEW_CUSTOMIZE, OnViewCustomize)
	ON_REGISTERED_MESSAGE(BCGM_RESETTOOLBAR, OnToolbarReset)
	ON_REGISTERED_MESSAGE(BCGM_TOOLBARMENU, OnToolbarContextMenu)
	ON_REGISTERED_MESSAGE(BCGM_CUSTOMIZEHELP, OnHelpCustomizeToolbars)
	ON_CBN_SELENDOK(AFX_IDW_TOOLBAR + 1,OnNewAddress)
	ON_COMMAND_RANGE(FIRST_FAVORITE_COMMAND, LAST_FAVORITE_COMMAND, OnFavorite)
	ON_COMMAND_RANGE(FIRST_HISTORY_COMMAND, FIRST_HISTORY_COMMAND + HISTORY_LEN - 1, OnHistory)
	ON_COMMAND(IDOK, OnNewAddressEnter)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	CBCGToolBar::EnableQuickCustomization ();

	//---------------------------------
	// Set toolbar and menu image size:
	//---------------------------------
	CBCGToolBar::SetSizes (CSize (36, 28), CSize (22, 20));
	CBCGToolBar::SetMenuSizes (CSize (22, 21), CSize (16, 15));

	CBCGToolBar::SetHotTextColor (::GetSysColor (COLOR_HIGHLIGHT)); //RGB(0, 0, 255));

	//--------------------
	// Create the menubar:
	//--------------------
	if (!m_wndMenuBar.Create (this))
	{
		TRACE0("Failed to create menubar\n");
		return -1;      // fail to create
	}

	m_wndMenuBar.SetBarStyle(m_wndMenuBar.GetBarStyle() | CBRS_SIZE_DYNAMIC);

	//------------------------------------
	// Remove menubar gripper and borders:
	//------------------------------------
    m_wndMenuBar.SetBarStyle (m_wndMenuBar.GetBarStyle() &
        ~(CBRS_GRIPPER | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

	//------------------------------
	// Create the animation control:
	//------------------------------
	if (!m_wndAnimate.Create(WS_CHILD | WS_VISIBLE, CRect(0, 0, 10, 10), this, AFX_IDW_TOOLBAR + 2) ||
		!m_wndAnimate.Open(IDR_MFCAVI))
	{
		TRACE0("Failed to create aimation\n");
		return -1;      // fail to create
	}

	if (!m_wndToolBar.CreateEx(this) ||
		!m_wndToolBar.LoadBitmap (IDB_HOTTOOLBAR, IDB_COLDTOOLBAR, IDB_MENU_IMAGES) ||
		!m_wndToolBar.RestoreOriginalstate ())
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	//------------------------------------
	// Remove toolbar gripper and borders:
	//------------------------------------
	m_wndToolBar.SetBarStyle (m_wndToolBar.GetBarStyle() &
		~(CBRS_GRIPPER | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

	//----------------------------------------
	// Create a combo box for the address bar:
	//----------------------------------------
	CString strAddressLabel;
	strAddressLabel.LoadString(IDS_ADDRESS);

	if (!m_wndAddress.Create(CBS_DROPDOWN | WS_CHILD, CRect(0, 0, 200, 120), this, AFX_IDW_TOOLBAR + 1))
	{
		TRACE0("Failed to create combobox\n");
		return -1;      // fail to create
	}

	//------------------
	// Create links bar:
	//------------------
	CString strLinksLabel;
	strLinksLabel.LoadString (IDS_LINKS);

	if (!m_wndLinksBar.Create (this, dwDefaultToolbarStyle, AFX_IDW_TOOLBAR + 3))
	{
		TRACE0("Failed to create links bar\n");
	}

	m_wndLinksBar.SetWindowText (strLinksLabel);
	m_wndLinksBar.SetBarStyle (m_wndLinksBar.GetBarStyle() &
		~(CBRS_GRIPPER | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

	//--------------
	// Create rebar:
	//--------------
	if (!m_wndReBar.Create(this) ||
		!m_wndReBar.AddBar(&m_wndMenuBar) ||
		!m_wndReBar.AddBar(&m_wndToolBar, NULL, NULL,
				RBBS_GRIPPERALWAYS | RBBS_FIXEDBMP | RBBS_BREAK) ||
		!m_wndReBar.AddBar(&m_wndAnimate, NULL, NULL, RBBS_FIXEDSIZE | RBBS_FIXEDBMP) ||
		!m_wndReBar.AddBar(&m_wndAddress, strAddressLabel, NULL,
				RBBS_GRIPPERALWAYS | RBBS_FIXEDBMP | RBBS_BREAK) ||
		!m_wndReBar.AddBar(&m_wndLinksBar, strLinksLabel, NULL,
				RBBS_GRIPPERALWAYS | RBBS_FIXEDBMP | RBBS_BREAK))
	{
		TRACE0("Failed to create rebar\n");
		return -1;      // fail to create
	}

	//--------------------------------------------------------------
	// Set up min/max sizes and ideal sizes for pieces of the rebar:
	//--------------------------------------------------------------
	REBARBANDINFO rbbi;

	CRect rectToolBar;
	m_wndToolBar.GetItemRect(0, &rectToolBar);

	rbbi.cbSize = sizeof(rbbi);
	rbbi.fMask = RBBIM_CHILDSIZE | RBBIM_IDEALSIZE | RBBIM_SIZE;
	rbbi.cxMinChild = rectToolBar.Width();
	rbbi.cyMinChild = rectToolBar.Height();
	rbbi.cx = rbbi.cxIdeal = rectToolBar.Width() * m_wndToolBar.GetCount ();
	m_wndReBar.GetReBarCtrl().SetBandInfo (1, &rbbi);
	rbbi.cxMinChild = 0;

	CRect rectAddress;
	m_wndAddress.GetEditCtrl()->GetWindowRect(&rectAddress);

	rbbi.fMask = RBBIM_CHILDSIZE | RBBIM_IDEALSIZE;
	rbbi.cyMinChild = rectAddress.Height() + 10;
	rbbi.cxIdeal = 200;
	m_wndReBar.GetReBarCtrl().SetBandInfo (3, &rbbi);

	//-------------------
	// Create status bar:
	//-------------------
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	CString strMainToolbarTitle;
	strMainToolbarTitle.LoadString (IDS_MAIN_TOOLBAR);
	m_wndToolBar.SetWindowText (strMainToolbarTitle);
	m_wndMenuBar.SetBarStyle(m_wndMenuBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY);

	CString strControlBarRegEntry = REGISTRY_ROOT;
	strControlBarRegEntry += CONTROL_BARS;

	//------------------------
	// Load standard toolbars:
	//------------------------
	m_wndToolBar.LoadState (strControlBarRegEntry);
	m_wndMenuBar.LoadState (strControlBarRegEntry);
	m_wndLinksBar.LoadState (strControlBarRegEntry);

	CBCGToolBar::LoadParameters (strControlBarRegEntry);

	//-------------------------------------
	// Load control bar states and context:
	//-------------------------------------
	CDockState dockState;
	dockState.LoadState (CONTROL_BARS); 

	if (IsDockStateValid (dockState))
	{
		SetDockState (dockState);
	}

	//-----------------------
	// Set up Favorites menu:
	//-----------------------
	m_menuFavotites.CreatePopupMenu ();

	TCHAR           sz[MAX_PATH];
	TCHAR           szPath[MAX_PATH];
	HKEY            hKey;
	DWORD           dwSize;

	// find out from the registry where the favorites are located.
	if(RegOpenKey(HKEY_CURRENT_USER, _T("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\User Shell Folders"), &hKey) != ERROR_SUCCESS)
	{
		TRACE0("Favorites folder not found\n");
		return 0;
	}
	dwSize = sizeof(sz);
	RegQueryValueEx(hKey, _T("Favorites"), NULL, NULL, (LPBYTE)sz, &dwSize);
	ExpandEnvironmentStrings(sz, szPath, MAX_PATH);
	RegCloseKey(hKey);

	BuildFavoritesMenu(szPath, 0, &m_menuFavotites);

	SHFILEINFO sfi;
	m_himSystem = (HIMAGELIST)SHGetFileInfo( TEXT("C:\\"), 
                                       0,
                                       &sfi, 
                                       sizeof(SHFILEINFO), 
                                       SHGFI_SYSICONINDEX | SHGFI_SMALLICON);
	if (m_himSystem != NULL)
	{
		int cx, cy;

		::ImageList_GetIconSize (m_himSystem, &cx, &cy);
		m_SysImageSize = CSize (cx, cy);
	}

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnViewCustomize()
{
	//------------------------------------
	// Create a customize toolbars dialog:
	//------------------------------------
	CBCGToolbarCustomize* pDlgCust = new CBCGToolbarCustomize (this,
		TRUE /* Automatic menus scaning */);

	pDlgCust->Create ();
}

void CMainFrame::OnClose() 
{
	CString strControlBarRegEntry = REGISTRY_ROOT;
	strControlBarRegEntry += CONTROL_BARS;

	CBCGToolBar::SaveParameters (strControlBarRegEntry);

	CDockState dockState;
	GetDockState (dockState);
	dockState.SaveState (CONTROL_BARS);

	//------------------------
	// Save standard toolbars:
	//------------------------
	m_wndToolBar.SaveState (strControlBarRegEntry);
	m_wndMenuBar.SaveState (strControlBarRegEntry);
	m_wndLinksBar.SaveState (strControlBarRegEntry);

	theApp.SaveCustomState ();

	CFrameWnd::OnClose();
}


LRESULT CMainFrame::OnToolbarContextMenu(WPARAM,LPARAM lp)
{
	CPoint point (LOWORD (lp), HIWORD(lp));

	CMenu menu;
	VERIFY(menu.LoadMenu (IDR_POPUP_TOOLBAR));

	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);


	CBCGPopupMenu* pPopupMenu = new CBCGPopupMenu;
	pPopupMenu->Create (this, point.x, point.y, pPopup->Detach ());

	return 0;
}

afx_msg LRESULT CMainFrame::OnToolbarReset(WPARAM /*wp*/,LPARAM)
{
	// TODO: reset toolbar with id = (UINT) wp to its initial state:
	//
	// UINT uiToolBarId = (UINT) wp;
	// if (uiToolBarId == IDR_MAINFRAME)
	// {
	//		do something with m_wndToolBar
	// }

	return 0;
}

LRESULT CMainFrame::OnHelpCustomizeToolbars(WPARAM wp, LPARAM lp)
{
	int iPageNum = (int) wp;

	CBCGToolbarCustomize* pDlg = (CBCGToolbarCustomize*) lp;
	ASSERT_VALID (pDlg);

	// TODO: show help about page number iPageNum

    MessageBox("Dont ask me next time, I'm busy", "I don't know."); 
	return 0;
}

int CMainFrame::BuildFavoritesMenu(LPCTSTR pszPath, int nStartPos, CMenu* pMenu)
{
	CString         strPath(pszPath);
	CString         strPath2;
	CString         str;
	WIN32_FIND_DATA wfd;
	HANDLE          h;
	int             nPos;
	int             nEndPos;
	int             nNewEndPos;
	int             nLastDir;
	TCHAR           buf[INTERNET_MAX_PATH_LENGTH];
	CStringArray    astrFavorites;
	CStringArray    astrDirs;
	CMenu*          pSubMenu;

	// make sure there's a trailing backslash
	if(strPath[strPath.GetLength() - 1] != _T('\\'))
		strPath += _T('\\');
	strPath2 = strPath;
	strPath += "*.*";

	// now scan the directory, first for .URL files and then for subdirectories
	// that may also contain .URL files
	h = FindFirstFile(strPath, &wfd);
	if(h != INVALID_HANDLE_VALUE)
	{
		nEndPos = nStartPos;
		do
		{
			if((wfd.dwFileAttributes & (FILE_ATTRIBUTE_DIRECTORY|FILE_ATTRIBUTE_HIDDEN|FILE_ATTRIBUTE_SYSTEM))==0)
			{
				str = wfd.cFileName;
				if(str.Right(4) == _T(".url"))
				{
					// an .URL file is formatted just like an .INI file, so we can
					// use GetPrivateProfileString() to get the information we want
					::GetPrivateProfileString(_T("InternetShortcut"), _T("URL"),
											  _T(""), buf, INTERNET_MAX_PATH_LENGTH,
											  strPath2 + str);
					str = str.Left(str.GetLength() - 4);

					// scan through the array and perform an insertion sort
					// to make sure the menu ends up in alphabetic order
					for(nPos = nStartPos ; nPos < nEndPos ; ++nPos)
					{
						if(str.CompareNoCase(astrFavorites[nPos]) < 0)
							break;
					}
					astrFavorites.InsertAt(nPos, str);
					m_astrFavoriteURLs.InsertAt(nPos, buf);

					TCHAR ext[_MAX_EXT];
					_tsplitpath (buf, NULL, NULL, NULL, ext);

					int iIcon;
					if (!m_URLIcons.Lookup (ext, iIcon))
					{
						// Retrieve icon file
						SHFILEINFO sfi;
						if (::SHGetFileInfo (strPath2 + wfd.cFileName, 0, &sfi, sizeof(SHFILEINFO), 
							SHGFI_SMALLICON | SHGFI_SYSICONINDEX) &&
							sfi.iIcon >= 0)
						{
							m_URLIcons.SetAt (ext, sfi.iIcon);
						}
					}

					++nEndPos;
				}
			}
		} while(FindNextFile(h, &wfd));
		FindClose(h);
		// Now add these items to the menu
		for(nPos = nStartPos ; nPos < nEndPos ; ++nPos)
		{
			pMenu->AppendMenu(MF_STRING | MF_ENABLED, FIRST_FAVORITE_COMMAND + nPos, astrFavorites[nPos]);
		}


		// now that we've got all the .URL files, check the subdirectories for more
		nLastDir = 0;
		h = FindFirstFile(strPath, &wfd);
		ASSERT(h != INVALID_HANDLE_VALUE);
		do
		{
			if(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				// ignore the current and parent directory entries
				if(lstrcmp(wfd.cFileName, _T(".")) == 0 || lstrcmp(wfd.cFileName, _T("..")) == 0)
					continue;

				for(nPos = 0 ; nPos < nLastDir ; ++nPos)
				{
					if(astrDirs[nPos].CompareNoCase(wfd.cFileName) > 0)
						break;
				}
				pSubMenu = new CMenu;
				pSubMenu->CreatePopupMenu();

				// call this function recursively.
				nNewEndPos = BuildFavoritesMenu(strPath2 + wfd.cFileName, nEndPos, pSubMenu);
				if(nNewEndPos != nEndPos)
				{
					// only intert a submenu if there are in fact .URL files in the subdirectory
					nEndPos = nNewEndPos;
					pMenu->InsertMenu(nPos, MF_BYPOSITION | MF_POPUP | MF_STRING, (UINT)pSubMenu->m_hMenu, wfd.cFileName);
					pSubMenu->Detach();
					astrDirs.InsertAt(nPos, wfd.cFileName);
					++nLastDir;
				}
				delete pSubMenu;
			}
		} while(FindNextFile(h, &wfd));
		FindClose(h);
	}
	return nEndPos;
}

void CMainFrame::OnShowPopupMenu (CBCGPopupMenu* pMenuPopup)
{
    CBCGFrameWnd::OnShowPopupMenu (pMenuPopup);

	if (pMenuPopup == NULL || CBCGToolBar::IsCustomizeMode ())
	{
        return;
    }

	CBCGPopupMenuBar* pMenuBar = pMenuPopup->GetMenuBar ();
	ASSERT_VALID (pMenuBar);

	for (int i = 0; i < pMenuBar->GetCount (); i ++)
	{
		CBCGToolbarButton* pButton = pMenuBar->GetButton (i);
		ASSERT_VALID (pButton);

		if (pButton->m_nID == ID_FAVORITS_DUMMY)
		{
			pMenuBar->ImportFromMenu (m_menuFavotites);
			//pMenuPopup->EnableScrolling ();

			return;
		}
	}

	CBCGToolbarMenuButton* pParentButton = pMenuPopup->GetParentButton ();
	if (pParentButton == NULL)
	{
		return;
	}

	switch (pParentButton->m_nID)
	{
	case ID_GO_BACK:
	case ID_GO_FORWARD:
		{
			CBCGIEDemoView* pView = ((CBCGIEDemoView*)GetActiveView());
			ASSERT_VALID (pView);

			CBCGIEDemoDoc* pDoc = pView->GetDocument();
			ASSERT_VALID(pDoc);

			_T_HistotyList lst;

			if (pParentButton->m_nID == ID_GO_BACK)
			{
				pDoc->GetBackList (lst);
			}
			else
			{
				pDoc->GetFrwdList (lst);
			}
			
			if (!lst.IsEmpty ())
			{
				pMenuPopup->RemoveAllItems ();

				for (POSITION pos = lst.GetHeadPosition (); pos != NULL;)
				{
					CHistoryObj* pObj = lst.GetNext (pos);
					ASSERT (pObj != NULL);

					pMenuPopup->InsertItem (
						CBCGToolbarMenuButton (pObj->GetCommand (), NULL, -1, 
												pObj->GetTitle ()));
				}
			}
		}
	}
}

BOOL CMainFrame::OnDrawMenuImage (CDC* pDC,
								const CBCGToolbarMenuButton* pMenuButton,
								const CRect& rectImage)
{
	if (m_himSystem == NULL)
	{
		return FALSE;
	}

	ASSERT_VALID (pDC);
	ASSERT_VALID (pMenuButton);

	int iIcon = -1;

	switch (pMenuButton->m_nID)
	{
	case ID_HELP_MICROSOFT_ON_THE_WEB_FREE_STUFF:
	case ID_HELP_MICROSOFT_ON_THE_WEB_GET_FASTER_INTERNET_ACCESS:
	case ID_HELP_MICROSOFT_ON_THE_WEB_FREQUENTLY_ASKED_QUESTIONS:
	case ID_HELP_MICROSOFT_ON_THE_WEB_INTERNET_START_PAGE:
	case ID_HELP_MICROSOFT_ON_THE_WEB_SEND_FEEDBACK:
	case ID_HELP_MICROSOFT_ON_THE_WEB_BEST_OF_THE_WEB:
	case ID_HELP_MICROSOFT_ON_THE_WEB_SEARCH_THE_WEB:
	case ID_HELP_MICROSOFT_ON_THE_WEB_MICROSOFT_HOME_PAGE:
		iIcon = 2;
		break;

	default:
		if (pMenuButton->m_nID >= FIRST_FAVORITE_COMMAND &&
			pMenuButton->m_nID <= LAST_FAVORITE_COMMAND)
		{
			TCHAR ext[_MAX_EXT];
			_tsplitpath (m_astrFavoriteURLs [pMenuButton->m_nID - FIRST_FAVORITE_COMMAND], NULL, NULL, NULL, ext);

			m_URLIcons.Lookup (ext, iIcon);
		}
		else if (IsFavoritesMenu (pMenuButton))	// Maybe, favorits folder?
		{
			iIcon = 0;
		}
	}

	if (iIcon == -1)
	{
		return FALSE;	// Don't draw it!
	}

	::ImageList_Draw (m_himSystem, iIcon, pDC->GetSafeHdc (), 
		rectImage.left + (rectImage.Width () - m_SysImageSize.cx) / 2, 
		rectImage.top + (rectImage.Height () - m_SysImageSize.cy) / 2, ILD_TRANSPARENT);

	return TRUE;
}

BOOL CMainFrame::IsFavoritesMenu (const CBCGToolbarMenuButton* pMenuButton)
{
	if (pMenuButton == NULL || pMenuButton->m_nID != (UINT) -1)
	{
		return FALSE;
	}

	ASSERT_VALID (pMenuButton);
	const CObList& lstCommands = pMenuButton->GetCommands ();
	
	for (POSITION pos = lstCommands.GetHeadPosition (); pos != NULL;)
	{
		CBCGToolbarButton* pCmd = (CBCGToolbarButton*) lstCommands.GetNext (pos);
		ASSERT_VALID (pCmd);

		if ((pCmd->m_nID >= FIRST_FAVORITE_COMMAND &&
			pCmd->m_nID <= LAST_FAVORITE_COMMAND) ||
			IsFavoritesMenu (DYNAMIC_DOWNCAST (CBCGToolbarMenuButton, pCmd)))
		{
			return TRUE;
		}
	}

	return FALSE;
}

void CMainFrame::OnFavorite(UINT nID)
{
	((CBCGIEDemoView*)GetActiveView())->Navigate2(m_astrFavoriteURLs[nID-FIRST_FAVORITE_COMMAND], 0, NULL);
}

void CMainFrame::OnHistory(UINT nID)
{
	CBCGIEDemoView* pView = ((CBCGIEDemoView*)GetActiveView());
	ASSERT_VALID (pView);

	CBCGIEDemoDoc* pDoc = pView->GetDocument();
	ASSERT_VALID(pDoc);

	CHistoryObj* pObj = pDoc->Go (nID);
	ASSERT (pObj != NULL);

	pView->Navigate2 (pObj->GetURL (), 0, NULL);
}

void CMainFrame::SetAddress(LPCTSTR lpszUrl)
{
	// This is called when the browser has completely loaded the new location,
	// so make sure the text in the address bar is up to date and stop the
	// animation.
	m_wndAddress.SetWindowText(lpszUrl);
	m_wndAnimate.Stop();
	m_wndAnimate.Seek(0);
}

void CMainFrame::StartAnimation()
{
	// Start the animation.  This is called when the browser begins to
	// navigate to a new location
	m_wndAnimate.Play(0, -1, -1);
}

void CMainFrame::OnNewAddress()
{
	// gets called when an item in the Address combo box is selected
	// just navigate to the newly selected location.
	CString str;

	m_wndAddress.GetLBText(m_wndAddress.GetCurSel(), str);
	((CBCGIEDemoView*)GetActiveView())->Navigate2(str, 0, NULL);
}

void CMainFrame::OnNewAddressEnter()
{
	// gets called when an item is entered manually into the edit box portion
	// of the Address combo box.
	// navigate to the newly selected location and also add this address to the
	// list of addresses in the combo box.
	CString str;

	m_wndAddress.GetEditCtrl()->GetWindowText(str);
	((CBCGIEDemoView*)GetActiveView())->Navigate2(str, 0, NULL);

	COMBOBOXEXITEM item;

	item.mask = CBEIF_TEXT;
	item.iItem = -1;
	item.pszText = (LPTSTR)(LPCTSTR)str;
	m_wndAddress.InsertItem(&item);
}

// empty handler for link buttons enabled.
void CMainFrame::OnLink1() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnViewAddressBar() 
{
	m_wndReBar.GetReBarCtrl().ShowBand (3, !m_wndAddress.IsWindowVisible ());
}

void CMainFrame::OnUpdateViewAddressBar(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck (m_wndAddress.IsWindowVisible ());
}

void CMainFrame::OnViewLinksBar() 
{
	ShowControlBar (&m_wndLinksBar, (m_wndLinksBar.GetStyle () & WS_VISIBLE) == 0, FALSE);
}

void CMainFrame::OnUpdateViewLinksBar(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck (m_wndLinksBar.IsWindowVisible ());
}

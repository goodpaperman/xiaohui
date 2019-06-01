// BCGToolbarSystemMenuButton.cpp: implementation of the CBCGToolbarSystemMenuButton class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <afxpriv.h>
#include "BCGToolBar.h"
#include "BCGToolbarSystemMenuButton.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(CBCGToolbarSystemMenuButton, CBCGToolbarMenuButton, VERSIONABLE_SCHEMA | 1)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBCGToolbarSystemMenuButton::CBCGToolbarSystemMenuButton()
{
	m_hSysMenuIcon = NULL;
	m_hSystemMenu = NULL;
}
//****************************************************************************************
CBCGToolbarSystemMenuButton::CBCGToolbarSystemMenuButton (HMENU hSystemMenu, HICON hSystemIcon) :
	CBCGToolbarMenuButton (0, hSystemMenu, -1)
{
	m_hSysMenuIcon = hSystemIcon;
	m_hSystemMenu = hSystemMenu;
}
//****************************************************************************************
CBCGToolbarSystemMenuButton::~CBCGToolbarSystemMenuButton()
{
}
//****************************************************************************************
void CBCGToolbarSystemMenuButton::CopyFrom (const CBCGToolbarButton& s)
{
	CBCGToolbarMenuButton::CopyFrom (s);

	const CBCGToolbarSystemMenuButton& src = (const CBCGToolbarSystemMenuButton&) s;

	m_hSysMenuIcon = src.m_hSysMenuIcon;
	m_hSystemMenu = src.m_hSystemMenu;
}
//****************************************************************************************
SIZE CBCGToolbarSystemMenuButton::OnCalculateSize (CDC* /*pDC*/, const CSize& sizeDefault, 
													BOOL /*bHorz*/)
{
	return CSize (	::GetSystemMetrics (SM_CXSMICON),
					sizeDefault.cy);
}
//****************************************************************************************
void CBCGToolbarSystemMenuButton::OnDraw (CDC* pDC, const CRect& rect, 
					CBCGToolBarImages* /*pImages*/,
					BOOL /*bHorz*/, BOOL /*bCustomizeMode*/,
					BOOL /*bHighlight*/,
					BOOL /*bDrawBorder*/, BOOL /*bGrayDisabledButtons*/)
{
	if (m_hSysMenuIcon != NULL)
	{
		int iHeight = GetSystemMetrics (SM_CYSMICON);
		int iOffset = (rect.Height () - iHeight) / 2;

		::DrawIconEx (*pDC, rect.left, rect.top + iOffset, m_hSysMenuIcon,
			GetSystemMetrics (SM_CXSMICON), iHeight,
			0, NULL, DI_NORMAL);
	}
}
//****************************************************************************************
void CBCGToolbarSystemMenuButton::OnDblClick (CWnd* pWnd)
{
	if (CBCGToolBar::IsCustomizeMode ())
	{
		return;
	}

	ASSERT (pWnd != NULL);

	CMDIFrameWnd* pParentFrame = 
		DYNAMIC_DOWNCAST (CMDIFrameWnd, pWnd->GetParentFrame ());

	if (pParentFrame != NULL)
	{
		CMDIChildWnd* pChild = pParentFrame->MDIGetActive ();
		ASSERT_VALID (pChild);

		pChild->SendMessage (WM_SYSCOMMAND, SC_CLOSE);
	}
}
//****************************************************************************************
void CBCGToolbarSystemMenuButton::CreateFromMenu (HMENU hMenu)
{
	m_hSystemMenu = hMenu;
}
//****************************************************************************************
HMENU CBCGToolbarSystemMenuButton::CreateMenu () const
{
	ASSERT (m_hSystemMenu != NULL);

	HMENU hMenu = CBCGToolbarMenuButton::CreateMenu ();
	if (hMenu == NULL)
	{
		return NULL;
	}

	//---------------------------------------------------------------------
	// System menu don't produce updating command statuses via the
	// standard MFC idle command targeting. So, we should enable/disable
	// system menu items according to the standard system menu status:
	//---------------------------------------------------------------------
	CMenu* pMenu = CMenu::FromHandle (hMenu);
	ASSERT_VALID (pMenu);

	CMenu* pSysMenu = CMenu::FromHandle (m_hSystemMenu);
	ASSERT_VALID (pSysMenu);

	int iCount = (int) pSysMenu->GetMenuItemCount ();
	for (int i = 0; i < iCount; i ++)
	{
		UINT uiState = pSysMenu->GetMenuState (i, MF_BYPOSITION);
		UINT uiCmd = pSysMenu->GetMenuItemID (i);

		if (uiState & MF_CHECKED)
		{
			pMenu->CheckMenuItem (uiCmd, MF_CHECKED);
		}

		if (uiState & MF_DISABLED)
		{
			pMenu->EnableMenuItem (uiCmd, MF_DISABLED);
		}

		if (uiState & MF_GRAYED)
		{
			pMenu->EnableMenuItem (uiCmd, MF_GRAYED);
		}
	}

	return hMenu;
}

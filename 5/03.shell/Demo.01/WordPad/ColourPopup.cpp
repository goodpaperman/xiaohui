#include "stdafx.h"
#include <math.h>
#include "ColourPopup.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColourPopup

IMPLEMENT_SERIAL(CColourPopup, CBCGPopupMenu, 1)

CColourPopup::CColourPopup(COLORREF color, BOOL bAutomatic) :
	m_wndColorBar (color, bAutomatic)
{
}

CColourPopup::~CColourPopup()
{
}

BEGIN_MESSAGE_MAP(CColourPopup, CBCGPopupMenu)
    //{{AFX_MSG_MAP(CColourPopup)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColourPopup message handlers

int CColourPopup::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGToolBar::IsCustomizeMode ())
	{
		return -1;
	}

	if (CMiniFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndColorBar.Create (this))
	{
		TRACE(_T("Can't create popup menu bar\n"));
		return -1;
	}

	m_wndColorBar.SetOwner (GetParent ());
	m_wndColorBar.SetBarStyle(m_wndColorBar.GetBarStyle() | CBRS_TOOLTIPS);

	//-----------------------------------------------------------------------------
	// Maybe, main application frame should update the popup menu context before it
	// displayed (example - windows list):
	//-----------------------------------------------------------------------------
	ActivatePopupMenu (this);
	RecalcLayout ();
	return 0;
}

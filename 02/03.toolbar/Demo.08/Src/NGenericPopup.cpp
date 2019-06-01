// NGenericPopup.cpp : implementation file
//
/*
Copyright (C) 1998 Tony Hoyle (tmh@netfusion.co.uk)

This program is free software; you can redistribute it and/or modify it under the terms
of the GNU General Public License as published by the Free Software Foundation; either
version 2 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program;
if not, write to the Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#include "stdafx.h"
#include "NGenericPopup.h"
#include "NGenericToolBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNGenericPopup

CNGenericPopup::CNGenericPopup()
{
	m_pMenu=new CMenu;
	m_bIsAttached = FALSE;
}

CNGenericPopup::~CNGenericPopup()
{
	m_pMenu->m_hMenu=NULL;
	delete m_pMenu;
}


IMPLEMENT_DYNAMIC(CNGenericPopup, CWnd)

BEGIN_MESSAGE_MAP(CNGenericPopup, CWnd)
	//{{AFX_MSG_MAP(CNGenericPopup)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CNGenericPopup message handlers

BOOL CNGenericPopup::ShowMenu(/*int nOrient, */BOOL bFromKey, /*CNGenericToolBar* pToolbar, */int x, int y, CWnd* pParent, HMENU hMenu)
{
	ASSERT(hMenu);

	HideMenu();
	m_pMenu->m_hMenu=hMenu;
	m_pParent=pParent;

	if ((FALSE == m_bIsAttached) && (TRUE == m_cSubMenu.Attach (m_pMenu->m_hMenu)))
	{
		m_cSubMenu.TrackPopupMenu (TPM_LEFTALIGN , x , y , m_pParent , NULL);
		m_pParent->SendMessage(WM_ENTERMENULOOP,FALSE);
		m_bIsAttached = TRUE;
	}

	if(bFromKey)
	{
		m_pParent->SendMessage (WM_MENUSELECT , 0 , (LPARAM)hMenu);
	}

	return TRUE;
}
BOOL CNGenericPopup::HideMenu()
{
	if (m_bIsAttached == TRUE)
	{
		m_cSubMenu.Detach ();
		m_pParent->SendMessage(WM_EXITMENULOOP,(WPARAM)FALSE,0);
		m_bIsAttached = FALSE;
	}
	return TRUE;
}

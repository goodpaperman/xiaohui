/****************************************************************************************
//	Copyright (c) 1999, Huang Shansong (╩фи╫ки)
//	Department of Automation, Tsinghua University, Beijing, P.R.China
//	hsssp@263.net or pingersoft@263.net
//	You may freely use or modify this code provided this 
//	copyright is included in all derived versions.
//	If you enhance it, please mail one copy to me. Thanks.
****************************************************************************************/

// COptionsTreeCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "OptionsTreeCtrl.h"
#include "options.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptionsTreeCtrl

/****************************************************************************************
* Function	:	COptionsTreeCtrl::COptionsTreeCtrl
* Description		:	
* Return Value	:	
****************************************************************************************/
COptionsTreeCtrl::COptionsTreeCtrl()
{
}

/****************************************************************************************
* Function	:	COptionsTreeCtrl::~COptionsTreeCtrl
* Description		:	
* Return Value	:	
****************************************************************************************/
COptionsTreeCtrl::~COptionsTreeCtrl()
{
}


BEGIN_MESSAGE_MAP(COptionsTreeCtrl, CTreeCtrl)
	//{{AFX_MSG_MAP(COptionsTreeCtrl)
	ON_NOTIFY_REFLECT(TVN_GETDISPINFO, OnGetdispinfo)
	ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionsTreeCtrl message handlers
/****************************************************************************************
* Function	:	COptionsTreeCtrl::Initialize
* Description		:	
* Return Value	:	void
* Parameter		:	char* str	-	
****************************************************************************************/
void COptionsTreeCtrl::Initialize(char* str)
{
	int level = 0;
	HTREEITEM hItem, hExpandItem = NULL;
	TVINSERTSTRUCT tvi;
	hItem = GetRootItem();
	int indent;
	OPTIONITEM* p;

	SetImageList(&(m_pOptions->m_Img), TVSIL_NORMAL);

	for (POSITION pos = m_pOptions->m_Items.GetHeadPosition() ; pos != NULL ; )
	{
		p = m_pOptions->m_Items.GetNext(pos);
		for (indent = 0 ; p->szText[indent] == '\t' ; indent ++);

		tvi.itemex.mask = TVIF_TEXT | TVIF_PARAM | TVIF_IMAGE | TVIF_SELECTEDIMAGE;

		tvi.itemex.pszText = LPSTR_TEXTCALLBACK;//&(p->szText[indent]);
		tvi.itemex.cchTextMax = 50;
		tvi.itemex.iImage = I_IMAGECALLBACK;
		tvi.itemex.iSelectedImage = I_IMAGECALLBACK;
		tvi.itemex.lParam = (LPARAM)p;
		
		if (indent == level)
			tvi.hParent = GetParentItem(hItem);
		else if (indent > level)
		{
			tvi.hParent = hItem;
			level ++;
		}
		else if (indent < level)
		{
			tvi.hParent = GetParentItem(hItem);
			while( level != indent)
			{
				tvi.hParent = GetParentItem(tvi.hParent);
				level --;
			}
		}
		
		tvi.hInsertAfter = TVI_LAST;
		hItem = InsertItem(&tvi);

		if (str != NULL && _stricmp(p->szText, str) == 0)
			hExpandItem = hItem;
	}

	if (hExpandItem != NULL)
	{
		ExpandItem(hExpandItem);
		SelectSetFirstVisible(hExpandItem);
	}
	else
	{
		for (hItem = GetRootItem() ; hItem != NULL ; )
		{
			if (ItemHasChildren(hItem))
				ExpandItem(hItem);
			hItem = GetNextSiblingItem(hItem);
		}
		SelectSetFirstVisible(GetRootItem());
	}

	for (hItem = GetRootItem() ; hItem != NULL ; )
	{
		if (ItemHasChildren(hItem))
			EnableItem(hItem, COptions::Enable, true);
		hItem = GetNextSiblingItem(hItem);
	}
}

/////////////////////////////

/****************************************************************************************
* Function	:	COptionsTreeCtrl::OnGetdispinfo
* Description		:	
* Return Value	:	void
* Parameter		:	NMHDR* pNMHDR   	-	
* Parameter		:	LRESULT* pResult	-	
****************************************************************************************/
void COptionsTreeCtrl::OnGetdispinfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TV_DISPINFO* pTVDispInfo = (TV_DISPINFO*)pNMHDR;
	OPTIONITEM* p = (OPTIONITEM*)GetItemData(pTVDispInfo->item.hItem);
	pTVDispInfo->item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	if (strlen(p->szName) != 0)
	{
		pTVDispInfo->item.iImage = (m_pOptions->GetOption((CString)(p->szName)) == p->iTrueValue ? 
			p->iTrueImage : p->iFalseImage);
		pTVDispInfo->item.iSelectedImage = pTVDispInfo->item.iImage;
	}
	else
	{
		pTVDispInfo->item.iImage = p->iImage;
		pTVDispInfo->item.iSelectedImage = p->iSelectedImage;
	}

	if (p->fEnable == COptions::Disable || p->fEnable == COptions::StaticDisable)
	{
		pTVDispInfo->item.mask |= TVIF_STATE;
		pTVDispInfo->item.stateMask = TVIS_CUT;
		pTVDispInfo->item.state = TVIS_CUT;
	}

	int indent;
	for (indent = 0 ; p->szText[indent] == '\t' ; indent ++);
	pTVDispInfo->item.pszText = &(p->szText[indent]);
	*pResult = 0;
}


/****************************************************************************************
* Function	:	COptionsTreeCtrl::OnClick
* Description		:	
* Return Value	:	void
* Parameter		:	NMHDR* pNMHDR   	-	
* Parameter		:	LRESULT* pResult	-	
****************************************************************************************/
void COptionsTreeCtrl::OnClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	CPoint pt;
	CRect rt;
	GetCursorPos(&pt);
	ScreenToClient(&pt);
	UINT flag;
	HTREEITEM hItem = HitTest(pt, &flag);
	if ((flag & TVHT_ONITEMICON) != TVHT_ONITEMICON)
		return;
	OPTIONITEM* p = (OPTIONITEM*)GetItemData(/*pNMTreeView->itemNew.*/hItem);
	if (strlen(p->szName) != 0)
	{
		if (p->fEnable == COptions::Enable || p->fEnable == COptions::StaticEnable)
		{
			if (p->iTrueValue == COptions::CheckTrue)
			{//Check button
				BOOL flag = (m_pOptions->GetOption((CString)p->szName) == p->iTrueValue);
				m_pOptions->SetOption((CString)p->szName, flag ? COptions::CheckFalse : p->iTrueValue);
				EnableItem(hItem, (!flag) ? COptions::Enable : COptions::Disable, false);
				InvalidateItem(hItem, true);
			}
			else
			{//Radio button
				m_pOptions->SetOption((CString)p->szName, p->iTrueValue);
				hItem = GetParentItem(hItem);
				for( hItem = GetChildItem(hItem) ; hItem != NULL ; )
				{
					p = (OPTIONITEM*)GetItemData(hItem);
					EnableItem(hItem, m_pOptions->GetOption((CString)p->szName) == p->iTrueValue ? COptions::Enable : COptions::Disable, false);
					InvalidateItem(hItem, true);
					hItem = GetNextSiblingItem(hItem);
				}
			}
		}
	}
	*pResult = 0;
}

/****************************************************************************************
* Function	:	COptionsTreeCtrl::ExpandItem
* Description		:	
* Return Value	:	void
* Parameter		:	HTREEITEM hItem	-	
****************************************************************************************/
void COptionsTreeCtrl::ExpandItem(HTREEITEM hItem)
{
	CTreeCtrl::Expand(hItem, TVE_EXPAND);
	for (hItem = GetChildItem(hItem) ; hItem != NULL ; )
	{
		if (ItemHasChildren(hItem))
			ExpandItem(hItem);
		hItem = GetNextSiblingItem(hItem);
	}
}

/****************************************************************************************
* Function	:	COptionsTreeCtrl::EnableItem
* Description		:	
* Return Value	:	void
* Parameter		:	HTREEITEM hItem	-	
* Parameter		:	BOOL enable    	-	
* Parameter		:	BOOL self      	-	
****************************************************************************************/
void COptionsTreeCtrl::EnableItem(HTREEITEM hItem, BOOL enable, BOOL self)
{
	OPTIONITEM* p = (OPTIONITEM*)GetItemData(hItem);
	BOOL flag;

	ASSERT(enable != COptions::StaticEnable);
	ASSERT(enable != COptions::StaticDisable);

	if (self && p->fEnable != COptions::StaticEnable && p->fEnable != COptions::StaticDisable)
	{
		p->fEnable = enable;
	}

	if (strlen(p->szName) != 0)
	{
		if (p->fEnable == COptions::Enable || p->fEnable == COptions::StaticEnable)
		{
			flag = (m_pOptions->GetOption((CString)p->szName) == p->iTrueValue) ? COptions::Enable : COptions::Disable;
		}
		else
		{
			ASSERT(p->fEnable == COptions::Disable || p->fEnable == COptions::StaticDisable);
			flag = COptions::Disable;
		}
	}
	else
	{
		if (p->fEnable == COptions::StaticEnable || p->fEnable == COptions::Enable)
		{
			flag = COptions::Enable;
		}
		else
		{
			ASSERT(p->fEnable == COptions::Disable || p->fEnable == COptions::StaticDisable);
			flag = COptions::Disable;
		}
	}

	for (hItem = GetChildItem(hItem) ; hItem != NULL ; )
	{
		if (ItemHasChildren(hItem))
		{
			EnableItem(hItem, flag, true);
		}
		else
		{
			p = (OPTIONITEM*)GetItemData(hItem);
			if (p->fEnable != COptions::StaticEnable && p->fEnable != COptions::StaticDisable)
				p->fEnable = flag;
		}
		hItem = GetNextSiblingItem(hItem);
	}
}

/****************************************************************************************
* Function	:	COptionsTreeCtrl::InvalidateItem
* Description		:	
* Return Value	:	void
* Parameter		:	HTREEITEM hItem	-	
* Parameter		:	BOOL self      	-	
****************************************************************************************/
void COptionsTreeCtrl::InvalidateItem(HTREEITEM hItem, BOOL self)
{
	CRect rt;
	if (self)
	{
		GetItemRect(hItem, &rt, false);
		InvalidateRect(&rt, true);
	}
	for (hItem = GetChildItem(hItem) ; hItem != NULL ; )
	{
		if (ItemHasChildren(hItem) && GetItemState(hItem, TVIS_EXPANDED))
			InvalidateItem(hItem, true);
		else
		{
			GetItemRect(hItem, &rt, false);
			InvalidateRect(&rt, true);
		}
		hItem = GetNextSiblingItem(hItem);
	}
}

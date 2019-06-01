// BCGToolbarMenuButtonsButton.cpp: implementation of the CBCGToolbarMenuButtonsButton class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BCGToolbarMenuButtonsButton.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CBCGToolbarMenuButtonsButton, CBCGToolbarButton)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBCGToolbarMenuButtonsButton::CBCGToolbarMenuButtonsButton()
{
	m_uiSystemCommand = 0;
}
//****************************************************************************************
CBCGToolbarMenuButtonsButton::CBCGToolbarMenuButtonsButton(UINT uiCmdId)
{
	if (uiCmdId != SC_CLOSE &&
		uiCmdId != SC_MINIMIZE &&
		uiCmdId != SC_RESTORE)
	{
		ASSERT (FALSE);
	}

	m_uiSystemCommand = uiCmdId;
}
//****************************************************************************************
CBCGToolbarMenuButtonsButton::~CBCGToolbarMenuButtonsButton()
{
}
//****************************************************************************************
void CBCGToolbarMenuButtonsButton::OnDraw (CDC* pDC, const CRect& rect, 
					CBCGToolBarImages* /*pImages*/,
					BOOL /*bHorz*/, BOOL /*bCustomizeMode*/,
					BOOL /*bHighlight*/,
					BOOL /*bDrawBorder*/, BOOL /*bGrayDisabledButtons*/)
{
	UINT uiState = 0;

	switch (m_uiSystemCommand)
	{
	case SC_CLOSE:
		uiState |= DFCS_CAPTIONCLOSE;
		break;

	case SC_MINIMIZE:
		uiState |= DFCS_CAPTIONMIN;
		break;

	case SC_RESTORE:
		uiState |= DFCS_CAPTIONRESTORE;
		break;

	default:
		return;
	}

	if (m_nStyle & TBBS_PRESSED)
	{
		uiState |= DFCS_PUSHED;
	}

	CRect r = rect;
	pDC->DrawFrameControl (r, DFC_CAPTION, uiState);
}
//****************************************************************************************
SIZE CBCGToolbarMenuButtonsButton::OnCalculateSize (CDC* /*pDC*/, const CSize& /*sizeDefault*/,
													BOOL /*bHorz*/)
{
	return CSize (	::GetSystemMetrics (SM_CXSIZE),
					::GetSystemMetrics (SM_CYSIZE));
}
//****************************************************************************************
void CBCGToolbarMenuButtonsButton::CopyFrom (const CBCGToolbarButton& s)
{
	CBCGToolbarButton::CopyFrom (s);

	const CBCGToolbarMenuButtonsButton& src = (const CBCGToolbarMenuButtonsButton&) s;
	m_uiSystemCommand = src.m_uiSystemCommand;
}

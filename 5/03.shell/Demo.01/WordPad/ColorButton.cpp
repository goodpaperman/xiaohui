// ColorButton.cpp: implementation of the CColorButton class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <..\\src\\afximpl.h>
#include <BCGToolBarImages.h>
#include "wordpad.h"
#include "ColorButton.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(CColorButton, CBCGToolbarButton, 1)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CColorButton::CColorButton (COLORREF color, LPCTSTR lpszColorName/* = NULL*/,
							BOOL bHighlight/* = FALSE*/) :
	m_Color (color),
	m_bHighlight (bHighlight)
{
	m_strText = (lpszColorName == NULL) ? _T("") : lpszColorName;
}
//***************************************************************************************
CColorButton::~CColorButton()
{
}
//***************************************************************************************
void CColorButton::OnDraw (CDC* pDC, const CRect& rect, CBCGToolBarImages* pImages,
								BOOL bHorz, BOOL bCustomizeMode, BOOL bHighlight,
								BOOL bDrawBorder, BOOL bGrayDisabledButtons)
{
	ASSERT (!bCustomizeMode);

	ASSERT_VALID (pDC);
	ASSERT_VALID (this);

	//---------------
	// Interior grey:
	//---------------
	pDC->FillSolidRect (&rect, ::GetSysColor (COLOR_3DFACE));

	if (!bHighlight &&
		((m_nStyle & (TBBS_CHECKED | TBBS_INDETERMINATE) || m_bHighlight)))
	{
		CRect rectDither = rect;
		rectDither.InflateRect (-afxData.cxBorder2, -afxData.cyBorder2);

		CBCGToolBarImages::FillDitheredRect (pDC, rectDither);
	}

	if (m_nStyle & TBBS_DISABLED)
	{
		return;
	}

	//--------------------
	// Draw button border:
	//--------------------
	if (bDrawBorder)
	{
		if (m_nStyle & (TBBS_PRESSED | TBBS_CHECKED) || m_bHighlight)
		{
			//-----------------------
			// Pressed in or checked:
			//-----------------------
			pDC->Draw3dRect (&rect,
				afxData.clrBtnShadow,
				afxData.clrBtnHilite);
		}
		else if (bHighlight && !(m_nStyle & TBBS_DISABLED) &&
			!(m_nStyle & (TBBS_CHECKED | TBBS_INDETERMINATE)))
		{
			pDC->Draw3dRect (&rect, afxData.clrBtnHilite,
									afxData.clrBtnShadow);
		}
	}

	CRect rectColor = rect;
	rectColor.DeflateRect (afxData.cxBorder2 * 2, afxData.cyBorder2 * 2);

	pDC->FillSolidRect (rectColor, m_Color);
	pDC->Draw3dRect (rectColor, afxData.clrBtnShadow,
								afxData.clrBtnShadow);
}

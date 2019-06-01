// ColorAutoButton.cpp: implementation of the CColorAutoButton class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <..\\src\\afximpl.h>
#include "wordpad.h"
#include "BCGToolBarImages.h"
#include "ColorAutoButton.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(CColorAutoButton, CBCGToolbarButton, 1)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CColorAutoButton::CColorAutoButton (int nIndex/* = COLOR_TEXT*/, 
									LPCTSTR lpszLabel/* = NULL*/, 
									BOOL bHighlight/* = FALSE*/) :
	m_nIndex (nIndex),
	m_bHighlight (bHighlight)
{
	if (lpszLabel != NULL)
	{
		m_strLabel = lpszLabel;
	}
}
//***************************************************************************************
CColorAutoButton::~CColorAutoButton()
{
}
//***************************************************************************************
void CColorAutoButton::OnDraw (CDC* pDC, const CRect& rect, CBCGToolBarImages* pImages,
								BOOL bHorz, BOOL bCustomizeMode, BOOL bHighlight,
								BOOL bDrawBorder, BOOL bGrayDisabledButtons)
{
	ASSERT (!bCustomizeMode);
	ASSERT (bHorz);

	ASSERT_VALID (pDC);
	ASSERT_VALID (this);

	//---------------
	// Interior grey:
	//---------------
	pDC->FillSolidRect (&rect, ::GetSysColor (COLOR_3DFACE));

	if (!bCustomizeMode && !bHighlight &&
		((m_nStyle & (TBBS_CHECKED | TBBS_INDETERMINATE)) || m_bHighlight))
	{
		CRect rectDither = rect;
		rectDither.InflateRect (-afxData.cxBorder2, -afxData.cyBorder2);

		CBCGToolBarImages::FillDitheredRect (pDC, rectDither);
	}

	//--------------------
	// Draw button border:
	//--------------------
	if (HaveHotBorder () && bDrawBorder)
	{
		if ((m_nStyle & (TBBS_PRESSED | TBBS_CHECKED)) || m_bHighlight)
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

	//----------------
	// Draw color box:
	//----------------
	CRect rectColor = rect;
	rectColor.right = rectColor.left + rectColor.Height ();
	rectColor.DeflateRect (afxData.cxBorder2 * 4, afxData.cyBorder2 * 4);

	pDC->FillSolidRect (rectColor, ::GetSysColor (m_nIndex));
	pDC->Draw3dRect (rectColor, afxData.clrBtnShadow,
								afxData.clrBtnShadow);

	//------------
	// Draw label:
	//------------
	CRect rectText = rect;
	rectText.left += rectText.Height () + 1;
	rectText.DeflateRect (afxData.cxBorder2 * 4, afxData.cyBorder2 * 4);

	pDC->SetTextColor (m_nStyle & TBBS_DISABLED ? 
		::GetSysColor (COLOR_GRAYTEXT) :
		::GetSysColor(COLOR_BTNTEXT));
	pDC->DrawText (m_strLabel, &rectText, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

	//------------
	// Draw frame:
	//------------
	CRect rectFrame = rect;
	rectFrame.DeflateRect (afxData.cxBorder2 * 2, afxData.cyBorder2 * 2);

	pDC->Draw3dRect (rectFrame, afxData.clrBtnShadow,
								afxData.clrBtnShadow);
}

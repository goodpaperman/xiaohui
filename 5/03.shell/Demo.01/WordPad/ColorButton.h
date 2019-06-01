// ColorButton.h: interface for the CColorButton class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COLORBUTTON_H__664F5586_F6F4_11D2_A713_0090274409AC__INCLUDED_)
#define AFX_COLORBUTTON_H__664F5586_F6F4_11D2_A713_0090274409AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BCGToolbarButton.h"

class CColorButton : public CBCGToolbarButton  
{
	DECLARE_SERIAL(CColorButton)

public:
	CColorButton(COLORREF color = RGB (0, 0, 0), 
				LPCTSTR lpszColorName = NULL, BOOL bHighlight = FALSE);
	virtual ~CColorButton();

	COLORREF GetColor () const
	{
		return m_Color;
	}

protected:
	virtual void OnDraw (CDC* pDC, const CRect& rect, CBCGToolBarImages* pImages,
						BOOL bHorz = TRUE, BOOL bCustomizeMode = FALSE,
						BOOL bHighlight = FALSE,
						BOOL bDrawBorder = TRUE,
						BOOL bGrayDisabledButtons = TRUE);

	COLORREF	m_Color;
	BOOL		m_bHighlight;
};

#endif // !defined(AFX_COLORBUTTON_H__664F5586_F6F4_11D2_A713_0090274409AC__INCLUDED_)

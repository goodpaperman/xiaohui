// ColorAutoButton.h: interface for the CColorAutoButton class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COLORAUTOBUTTON_H__651CE25D_F892_11D2_A713_0090274409AC__INCLUDED_)
#define AFX_COLORAUTOBUTTON_H__651CE25D_F892_11D2_A713_0090274409AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BCGToolbarButton.h"

class CColorAutoButton : public CBCGToolbarButton
{
	DECLARE_SERIAL(CColorAutoButton)

public:
	CColorAutoButton(int nIndex = COLOR_WINDOWTEXT,
					LPCTSTR lpszLabel = NULL,
					BOOL bHighlight = FALSE);
	virtual ~CColorAutoButton();

protected:
	virtual void OnDraw (CDC* pDC, const CRect& rect, CBCGToolBarImages* pImages,
						BOOL bHorz = TRUE, BOOL bCustomizeMode = FALSE,
						BOOL bHighlight = FALSE,
						BOOL bDrawBorder = TRUE,
						BOOL bGrayDisabledButtons = TRUE);

	int		m_nIndex;
	CString	m_strLabel;
	BOOL	m_bHighlight;
};

#endif // !defined(AFX_COLORAUTOBUTTON_H__651CE25D_F892_11D2_A713_0090274409AC__INCLUDED_)

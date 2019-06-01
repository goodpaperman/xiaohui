// colorlis.h : header file
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "BCGToolbarMenuButton.h"
#include "ColourPopup.h"

class CColorMenuButton : public CBCGToolbarMenuButton  
{
	DECLARE_SERIAL(CColorMenuButton)

public:
	CColorMenuButton();
	virtual ~CColorMenuButton();

	virtual void OnDraw (CDC* pDC, const CRect& rect, CBCGToolBarImages* pImages,
						BOOL bHorz = TRUE, BOOL bCustomizeMode = FALSE,
						BOOL bHighlight = FALSE,
						BOOL bDrawBorder = TRUE,
						BOOL bGrayDisabledButtons = TRUE);
	virtual CBCGPopupMenu* CreatePopupMenu ()
	{
		return new CColourPopup (m_Color, COLOR_WINDOWTEXT);
	}

	virtual BOOL IsEmptyMenuAllowed () const
	{
		return TRUE;
	}

	virtual void OnChangeParentWnd (CWnd* pWndParent);

	void SetColor (COLORREF clr, BOOL bNotify = TRUE);

protected:
	COLORREF	m_Color;
};


/////////////////////////////////////////////////////////////////////////////

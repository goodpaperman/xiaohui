#if !defined(AFX_COLOURPOPUP_H__D0B75902_9830_11D1_9C0F_00A0243D1382__INCLUDED_)
#define AFX_COLOURPOPUP_H__D0B75902_9830_11D1_9C0F_00A0243D1382__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "BCGPopupMenu.h"
#include "ColorPopupBar.h"

/////////////////////////////////////////////////////////////////////////////
// CColourPopup window

class CColorMenuButton;

class CColourPopup : public CBCGPopupMenu
{
	DECLARE_SERIAL(CColourPopup)

// Construction
public:
    CColourPopup(COLORREF color = (COLORREF) -1, int nAutoColorIndex = -1);

// Attributes
protected:
	CColorPopupBar	m_wndColorBar;

// Operations
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CColourPopup)
	//}}AFX_VIRTUAL

	virtual CBCGPopupMenuBar* GetMenuBar ()
	{
		return &m_wndColorBar;
	}

// Implementation
public:
    virtual ~CColourPopup();

    // Generated message map functions
protected:
    //{{AFX_MSG(CColourPopup)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLOURPOPUP_H__D0B75902_9830_11D1_9C0F_00A0243D1382__INCLUDED_)

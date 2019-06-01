#if !defined(AFX_COLORPOPUPBAR_H__664F5585_F6F4_11D2_A713_0090274409AC__INCLUDED_)
#define AFX_COLORPOPUPBAR_H__664F5585_F6F4_11D2_A713_0090274409AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColorPopupBar.h : header file
//

#include "BCGPopupMenuBar.h"

// To hold the colours and their names
typedef struct {
    COLORREF crColour;
    TCHAR    *szName;
} ColourTableEntry;

extern UINT CPN_SELCHANGE;			// Colour Picker Selection change

/////////////////////////////////////////////////////////////////////////////
// CColorPopupBar window

class CColorPopupBar : public CBCGPopupMenuBar
{
	DECLARE_SERIAL(CColorPopupBar)

// Construction
public:
	CColorPopupBar(COLORREF color = (COLORREF) -1, int nAutoColorIndex = -1);

// Attributes
public:

protected:
    static ColourTableEntry m_crColours[];
    int				m_nNumColumns;
    int				m_nNumRows;
	int				m_nNumColours;
	CPalette		m_Palette;
	CSize			m_BoxSize;
	int				m_nAutoBoxHeight;
	const COLORREF	m_Color;
	const int		m_nAutoColorIndex;

// Operations
public:

// Overrides
	virtual BOOL OnSendCommand (const CBCGToolbarButton* pButton);
	virtual int OnToolHitTest(CPoint point, TOOLINFO* pTI) const;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorPopupBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CColorPopupBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CColorPopupBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnQueryNewPalette();
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	virtual void AdjustLocations ();
	virtual CSize CalcSize ();
	virtual void DoPaint(CDC* pDC);

    void Initialise();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORPOPUPBAR_H__664F5585_F6F4_11D2_A713_0090274409AC__INCLUDED_)

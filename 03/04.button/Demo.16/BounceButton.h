#if !defined(AFX_BOUNCEBUTTON_H__E38C830E_B929_11D2_A3C4_F74379B0725C__INCLUDED_)
#define AFX_BOUNCEBUTTON_H__E38C830E_B929_11D2_A3C4_F74379B0725C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// BounceButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBounceButton window

#define Rad2Deg	180.0/3.1415 
#define LIGHT_SOURCE_ANGLE	-2.356		// -2.356 radians = -135 degrees, i.e. From top left
#include <math.h>

class CBounceButton : public CButton
{
// Construction
public:
	CBounceButton( bool bDepressed=false, bool bCenterAlign=true );

// Attributes
public:
	bool MouseOverItem();

// Operations
public:
protected:
	COLORREF GetColor( double dAngle, COLORREF crBright, COLORREF crDark);
	void DrawCircle( CDC* pDC, CPoint p, LONG lRadius, COLORREF crColour, BOOL bDashed = FALSE);
	void DrawCircle( CDC* pDC, CPoint p, LONG lRadius, COLORREF crBright, COLORREF crDark);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBounceButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	int m_nMargin;
	int m_nRadius;

public:
	bool Depress( bool Down );
	bool IsDepressed();
	void Set_Check( int nCheck );
	virtual ~CBounceButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CBounceButton)
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	void OnMouseEnter(void);
	void OnMouseLeave(void);

	DECLARE_MESSAGE_MAP()

private:
	CRgn   m_btnRgn;
	CPoint m_ptCenter;
	CRect  m_textRect;
	CFont m_BoldFont;
	bool m_bMouseOver;
	bool m_bDepressed;
	bool m_bMouseTracking;
	bool m_bLMouseButtonDown;
	bool m_bDrawFocusRect;
	bool m_bCenterAlign;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BOUNCEBUTTON_H__E38C830E_B929_11D2_A3C4_F74379B0725C__INCLUDED_)

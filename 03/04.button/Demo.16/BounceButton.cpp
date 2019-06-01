// BounceButton.cpp : implementation file
//

#include "stdafx.h"
#include "BounceButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



#define DEFAULT_MARGIN	20



/////////////////////////////////////////////////////////////////////////////
// CBounceButton

CBounceButton::CBounceButton( bool bDepressed, bool bCenterAlign )
{
	m_bDepressed = bDepressed;
	m_bCenterAlign = bCenterAlign;
	m_bDrawFocusRect = false;
	m_bMouseTracking = false;
	m_bLMouseButtonDown = false;
	m_nMargin = DEFAULT_MARGIN;
}

CBounceButton::~CBounceButton()
{
	// ensure the GDI member objects are deleted
	m_btnRgn.DeleteObject();
	m_BoldFont.DeleteObject();
}


BEGIN_MESSAGE_MAP(CBounceButton, CButton)
	//{{AFX_MSG_MAP(CBounceButton)
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()	
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBounceButton message handlers
void CBounceButton::PreSubclassWindow() 
{
	CButton::PreSubclassWindow();

	// make sure we are an owner draw button
	ModifyStyle(0, BS_OWNERDRAW);

	CRect rect;
	GetClientRect(rect);

	// setup the button metrics
    LOGFONT lf;
    GetFont()->GetLogFont(&lf);
    m_nRadius = lf.lfHeight;
    if( m_nRadius == 0 )
        m_nRadius = 15;
    if( m_nRadius < 0 )
        m_nRadius = (-1)*m_nRadius;
	//m_nRadius  = (int)(rect.bottom*0.5)-5;

	// don't let the button get above this maximum radius
	// user can reset m_nRadius later, if desired
	if( m_nRadius > 6 )
		m_nRadius = 6;

	m_ptCenter.x = rect.left+m_nRadius+1;
	if( m_bCenterAlign )
	{
		m_ptCenter.y = rect.top+(int)(rect.Height()*0.5);
	}
	else
	{
		m_ptCenter.y = rect.top+m_nRadius+1;		
	}

	m_btnRgn.CreateEllipticRgn( rect.left, m_ptCenter.y-m_nRadius-1, rect.left+(2*m_nRadius)+4, m_ptCenter.y+m_nRadius+3 );

	// get the current window font info and use it to create a bold font
	LOGFONT logfont;
	CFont* pWndFont = GetFont();	
	pWndFont->GetLogFont( &logfont );
	logfont.lfWeight = 700;	// set the weight to a bold value
	m_BoldFont.CreateFontIndirect( &logfont );

}

// draw the button and text
void CBounceButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	ASSERT(lpDrawItemStruct != NULL);
	
	CDC* pDC   = CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect rect = lpDrawItemStruct->rcItem;
	UINT state = lpDrawItemStruct->itemState;
	UINT nStyle = GetStyle();
	int nRadius = m_nRadius;

	int nSavedDC = pDC->SaveDC();

	pDC->SelectStockObject(NULL_BRUSH);
	pDC->FillSolidRect(rect, ::GetSysColor(COLOR_BTNFACE));

	// draw the border circle if disabled
	if( lpDrawItemStruct->itemState & ODS_DISABLED )
	{
		DrawCircle(pDC, m_ptCenter, nRadius+1, ::GetSysColor(COLOR_BTNHIGHLIGHT));
		nRadius-=4;
	}
	else
	{
		DrawCircle(pDC, m_ptCenter, nRadius+1, ::GetSysColor(COLOR_WINDOWFRAME));

		// Draw the raised/sunken edges of the button (unless flat)
		if (nStyle & BS_FLAT)
		{
			DrawCircle(pDC, m_ptCenter, nRadius--, RGB(0,0,0));
			DrawCircle(pDC, m_ptCenter, nRadius--, ::GetSysColor(COLOR_3DHIGHLIGHT));
		}
		else
		{
			if (m_bDepressed)
			{	// button down
				DrawCircle(pDC, m_ptCenter, nRadius--, 
						   ::GetSysColor(COLOR_3DDKSHADOW), ::GetSysColor(COLOR_3DHIGHLIGHT));
				DrawCircle(pDC, m_ptCenter, nRadius--, 
						   ::GetSysColor(COLOR_3DDKSHADOW), ::GetSysColor(COLOR_3DHIGHLIGHT));
				DrawCircle(pDC, m_ptCenter, nRadius--, 
						   ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DLIGHT));
				DrawCircle(pDC, m_ptCenter, nRadius--, 
						   ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DLIGHT));
				pDC->SelectObject( m_BoldFont );
			}
			else	
			{	// button up
				DrawCircle(pDC, m_ptCenter, nRadius--, 
						   ::GetSysColor(COLOR_3DHIGHLIGHT), ::GetSysColor(COLOR_3DDKSHADOW));
				DrawCircle(pDC, m_ptCenter, nRadius--, 
						   ::GetSysColor(COLOR_3DHIGHLIGHT), ::GetSysColor(COLOR_3DDKSHADOW));
				DrawCircle(pDC, m_ptCenter, nRadius--, 
						   ::GetSysColor(COLOR_3DLIGHT), ::GetSysColor(COLOR_3DSHADOW));
				DrawCircle(pDC, m_ptCenter, nRadius--, 
						   ::GetSysColor(COLOR_3DLIGHT), ::GetSysColor(COLOR_3DSHADOW));
			}
		}
	}

	// draw the text if there is any
	CString strText;
	GetWindowText(strText);
	CSize Extent;
	CPoint pt;

	CRect textRect, clientRect;
	GetClientRect( clientRect );
	textRect = clientRect;
	textRect.left += (2*(m_nRadius+5));
	textRect.right -= 2;
	if (!strText.IsEmpty())
	{
		Extent = pDC->GetTextExtent(strText);
		pt.x = rect.left + (2*nRadius) + m_nMargin;
		pt.y = (int)((rect.Height() - Extent.cy)*0.5);

		pDC->SetBkMode(TRANSPARENT);

		if (state & ODS_DISABLED)
			pDC->DrawState(pt, Extent, strText, DSS_DISABLED, TRUE, 0, (HBRUSH)NULL);
		else
		{
			pDC->DrawText( strText, textRect, DT_LEFT|DT_NOPREFIX|/*DT_WORDBREAK|*/DT_CALCRECT );
			int h = textRect.Height();
			textRect.top = clientRect.top+(int)((clientRect.Height()-textRect.Height())*0.5);
			textRect.bottom = textRect.top + h;
			pDC->DrawText( strText, textRect, DT_LEFT|DT_NOPREFIX|DT_WORDBREAK );
			m_textRect = textRect;
		}
	}
	textRect.right += 2;

	// draw the focus rectangle around the control
    //POINT point;
    //GetCursorPos( &point );
	if (/*state & ODS_FOCUS*/m_bDrawFocusRect )
	{
		textRect.InflateRect(1,1);
		textRect.right++;
		pDC->DrawFocusRect( textRect );
		m_textRect = textRect;
	}

	pDC->RestoreDC(nSavedDC);
}

// remove the focus rect if we lose focus
void CBounceButton::OnKillFocus(CWnd*) 
{
	// remove focus from ourself and redraw
	if( m_bDrawFocusRect )
	{
		m_bDrawFocusRect = false;
		Invalidate();
	}
}

// handle double click as rapid single click
void CBounceButton::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	POINT pt;

	if( m_bDrawFocusRect )
	{
		::GetCursorPos(&pt);
		::MapWindowPoints(NULL,(HWND)(m_hWnd),&pt,1);
		::SendMessage((HWND)(m_hWnd),WM_LBUTTONDOWN,0,MAKELPARAM(pt.x,pt.y));	

		CButton::OnLButtonDblClk(nFlags, point);
	}
}

// handle left mouse button up
void CBounceButton::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if( m_bDrawFocusRect )
	{
		if( m_bLMouseButtonDown )
			m_bLMouseButtonDown = false;

		CButton::OnLButtonUp(nFlags, point);
	}
}

// handle Left Mouse Button down.
void CBounceButton::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// make sure the mouse button is in the correct area
	POINT pt;
	pt.x = point.x;
	pt.y = point.y;

	if( m_bDrawFocusRect )
	{
		m_bLMouseButtonDown = true;
		m_bDepressed = !m_bDepressed;
		SetFocus();
		Invalidate();

		CButton::OnLButtonDown(nFlags, point);
	}
}

// hack for quick conversion of Checkboxes to bounce buttons
void CBounceButton::Set_Check(int nCheck)
{
	switch( nCheck )
	{
	case 0	:	{	if( m_bDepressed )
					{
						m_bDepressed = false;
						Invalidate();
					}
					break;
				}
	case 1	:	{	if( !m_bDepressed )
					{
						m_bDepressed = true;
						Invalidate();
					}
					break;
				}
	case 2	:	{
					EnableWindow(false);
					break;
				}
	default:	break;
	}
}

// handle MouseMove notifications. Set the FocusRect state accordingly.
void CBounceButton::OnMouseMove(UINT, CPoint) 
{
	// 1. Mouse has moved and we are not tracking this button, or 
	// 2. mouse has moved and the cursor was not above this window
	// == Is equivalent to WM_MOUSEENTER (for which there is no message)
	if( !m_bMouseTracking || GetCapture()!=this )
	{
		OnMouseEnter();
	}
	else 
	{
		if( !MouseOverItem() )
			OnMouseLeave();
	}

	if( MouseOverItem() && !m_bDrawFocusRect )
	{
		m_bDrawFocusRect = true;
		Invalidate();
		UpdateWindow();
	}

	if( !MouseOverItem() && m_bDrawFocusRect )
	{
		m_bDrawFocusRect = false;
		Invalidate();
		UpdateWindow();
	}

}

// test for MouseOver
// return true if the mouse is over the button or the text,
// return false if the mouse is over whitespace
bool CBounceButton::MouseOverItem() 
{
	// get the current mouse position
	POINT mouse;
	GetCursorPos( &mouse );
	ScreenToClient( &mouse );

	return( (m_textRect.PtInRect( mouse )) || (m_btnRgn.PtInRegion( mouse )) );
}

// receive a MouseEnter notification
void CBounceButton::OnMouseEnter(void)
{
	// We are now tracking the mouse, OVER this button
	m_bMouseTracking = TRUE;
	m_bLMouseButtonDown = false;

	// take the focus
	GetFocus();

	// Ensure that mouse input is sent to the button
	SetCapture();
}

// receive MouseLeave notification
void CBounceButton::OnMouseLeave(void)
{
	// We are not tracking the mouse, this button is OFF.
	m_bMouseTracking = false;
	bool RedrawNeeded = false;

	// Release mouse capture from the button and restore normal mouse input
	ReleaseCapture();

	// if the left button is down, the user didn't complete a mouse click
	// so we need to unclick the button
	if( m_bLMouseButtonDown )
	{
		m_bDepressed = !m_bDepressed;
		m_bLMouseButtonDown = false;
		RedrawNeeded = true;
	}

	if( m_bDrawFocusRect )
	{
		m_bDrawFocusRect = false;
		RedrawNeeded = true;
	}

	if( RedrawNeeded )
	{
		Invalidate();
		UpdateWindow();
	}
}


// return the button's depression state
bool CBounceButton::IsDepressed()
{
	return m_bDepressed;
}


// set the button's depression state
bool CBounceButton::Depress(bool bDown)
{
	if( bDown != m_bDepressed )
	{
		m_bDepressed = bDown;
		Invalidate();
		return !m_bDepressed;
	}
	
	return m_bDepressed;
}




// GetColor and DrawCircle routines written by Chris Maunder
// (chrismaunder@codeguru.com)
// Copyright (c) 1997,1998.
// This code may be used in compiled form in any way you desire. This
// file may be redistributed unmodified by any means PROVIDING it is 
// not sold for profit without the authors written consent, and 
// providing that this notice and the authors name is included. If 
// the source code in this file is used in any commercial application 
// then a simple email would be nice.
// Calculate colour for a point at the given angle by performing a linear
// interpolation between the colours crBright and crDark based on the cosine
// of the angle between the light source and the point.
//
// Angles are measured from the +ve x-axis (i.e. (1,0) = 0 degrees, (0,1) = 90 degrees )
// But remember: +y points down!

// Thanks, Chris! You do good work.
// -Jim

COLORREF CBounceButton::GetColor(double dAngle, COLORREF crBright, COLORREF crDark)
{
	ASSERT(dAngle > -3.1416 && dAngle < 3.1416);
	double dAngleDifference = LIGHT_SOURCE_ANGLE - dAngle;

	if (dAngleDifference < -3.1415) dAngleDifference = 6.293 + dAngleDifference;
	else if (dAngleDifference > 3.1415) dAngleDifference = 6.293 - dAngleDifference;

	double Weight = 0.5*(cos(dAngleDifference)+1.0);

	BYTE Red   = (BYTE) (Weight*GetRValue(crBright) + (1.0-Weight)*GetRValue(crDark));
	BYTE Green = (BYTE) (Weight*GetGValue(crBright) + (1.0-Weight)*GetGValue(crDark));
	BYTE Blue  = (BYTE) (Weight*GetBValue(crBright) + (1.0-Weight)*GetBValue(crDark));

	return RGB(Red, Green, Blue);
}

void CBounceButton::DrawCircle(CDC* pDC, CPoint p, LONG lRadius, COLORREF crColour, BOOL bDashed)
{
	const int nDashLength = 1;
	LONG lError, lXoffset, lYoffset;
	int  nDash = 0;
	BOOL bDashOn = TRUE;

	//Check to see that the coordinates are valid
	ASSERT( (p.x + lRadius <= LONG_MAX) && (p.y + lRadius <= LONG_MAX) );
	ASSERT( (p.x - lRadius >= LONG_MIN) && (p.y - lRadius >= LONG_MIN) );

	//Set starting values
	lXoffset = lRadius;
	lYoffset = 0;
	lError   = -lRadius;

	do {
		if (bDashOn) {
			pDC->SetPixelV(p.x + lXoffset, p.y + lYoffset, crColour);
			pDC->SetPixelV(p.x + lXoffset, p.y - lYoffset, crColour);
			pDC->SetPixelV(p.x + lYoffset, p.y + lXoffset, crColour);
			pDC->SetPixelV(p.x + lYoffset, p.y - lXoffset, crColour);
			pDC->SetPixelV(p.x - lYoffset, p.y + lXoffset, crColour);
			pDC->SetPixelV(p.x - lYoffset, p.y - lXoffset, crColour);
			pDC->SetPixelV(p.x - lXoffset, p.y + lYoffset, crColour);
			pDC->SetPixelV(p.x - lXoffset, p.y - lYoffset, crColour);
		}

		//Advance the error term and the constant X axis step
		lError += lYoffset++;

		//Check to see if error term has overflowed
		if ((lError += lYoffset) >= 0)
			lError -= --lXoffset * 2;

		if (bDashed && (++nDash == nDashLength)) {
			nDash = 0;
			bDashOn = !bDashOn;
		}

	} while (lYoffset <= lXoffset);	//Continue until halfway point
} 

void CBounceButton::DrawCircle(CDC* pDC, CPoint p, LONG lRadius, COLORREF crBright, COLORREF crDark)
{
	LONG lError, lXoffset, lYoffset;

	//Check to see that the coordinates are valid
	ASSERT( (p.x + lRadius <= LONG_MAX) && (p.y + lRadius <= LONG_MAX) );
	ASSERT( (p.x - lRadius >= LONG_MIN) && (p.y - lRadius >= LONG_MIN) );

	//Set starting values
	lXoffset = lRadius;
	lYoffset = 0;
	lError   = -lRadius;

	do {
		const double Pi = 3.141592654, 
					 Pi_on_2 = Pi * 0.5,
					 Three_Pi_on_2 = Pi * 1.5;
		COLORREF crColour;
		double   dAngle = atan2(lYoffset, lXoffset);

		//Draw the current pixel, reflected across all eight arcs
		crColour = GetColor(dAngle, crBright, crDark);
		pDC->SetPixelV(p.x + lXoffset, p.y + lYoffset, crColour);

		crColour = GetColor(Pi_on_2 - dAngle, crBright, crDark);
		pDC->SetPixelV(p.x + lYoffset, p.y + lXoffset, crColour);

		crColour = GetColor(Pi_on_2 + dAngle, crBright, crDark);
		pDC->SetPixelV(p.x - lYoffset, p.y + lXoffset, crColour);

		crColour = GetColor(Pi - dAngle, crBright, crDark);
		pDC->SetPixelV(p.x - lXoffset, p.y + lYoffset, crColour);

		crColour = GetColor(-Pi + dAngle, crBright, crDark);
		pDC->SetPixelV(p.x - lXoffset, p.y - lYoffset, crColour);

		crColour = GetColor(-Pi_on_2 - dAngle, crBright, crDark);
		pDC->SetPixelV(p.x - lYoffset, p.y - lXoffset, crColour);

		crColour = GetColor(-Pi_on_2 + dAngle, crBright, crDark);
		pDC->SetPixelV(p.x + lYoffset, p.y - lXoffset, crColour);

		crColour = GetColor(-dAngle, crBright, crDark);
		pDC->SetPixelV(p.x + lXoffset, p.y - lYoffset, crColour);

		//Advance the error term and the constant X axis step
		lError += lYoffset++;

		//Check to see if error term has overflowed
		if ((lError += lYoffset) >= 0)
			lError -= --lXoffset * 2;

	} while (lYoffset <= lXoffset);	//Continue until halfway point
} 
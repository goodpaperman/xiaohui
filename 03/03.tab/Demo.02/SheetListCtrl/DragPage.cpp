/************************************
  REVISION LOG ENTRY
  Revision By: Mihai Filimon
  Revised on 7/22/98 9:22:22 AM
  Comments: DragPage.cpp implementation for CDragPage
 ************************************/

#include "stdafx.h"
#include "DragPage.h"
#include "SheetAlpha.h"
#include <math.h>

// Function name	: CDragPage::CDragPage
// Description	    : Default constructor for this object
// Return type		: 
CDragPage::CDragPage()
{
	Reset();
	m_pRectSave = new SRectSave();
}

// Function name	: CDragPage::CDragPage
// Description	    : Copy constructor
// Return type		: 
// Argument         : CDragPage& dragSource
CDragPage::CDragPage(CDragPage& dragSource)
{
	m_bDragging = dragSource.m_bDragging;
	m_pViewStartDrag = dragSource.m_pViewStartDrag;
	m_pViewTrackDrag = dragSource.m_pViewTrackDrag;
	m_pRectSave = NULL;
}

// Function name	: CDragPage::~CDragPage
// Description	    : virtual Destructor of this object
// Return type		: 
CDragPage::~CDragPage()
{
	if (m_pRectSave)
		delete m_pRectSave;
	m_pRectSave = NULL;
}

// Function name	: CDragPage::Set
// Description	    : Set the m_bDragging, m_pViewStartDrag to new values, and reset m_pViewTrackDrag
// Return type		: void 
// Argument         : BOOL bDragging
// Argument         : CWnd* pViewStartDrag
void CDragPage::Set(BOOL bDragging , CWnd* pViewStartDrag )
{
	m_bDragging = bDragging;
	m_pViewStartDrag = pViewStartDrag;
	SetTrackDrag(m_pViewStartDrag);
}

// Function name	: CDragPage::SetTrackDrag
// Description	    : Set the m_pViewTrackDrag mamber to new value pWnd
// Return type		: void 
// Argument         : CWnd * pWnd
void CDragPage::SetTrackDrag(CWnd * pWnd)
{
	m_pViewTrackDrag = pWnd;
}

// Function name	: CDragPage::Reset
// Description	    : Reset all member variables
// Return type		: void 
void CDragPage::Reset()
{
	Set(FALSE,NULL);
}

// Function name	: CDragPage::IsDragging
// Description	    : True if dragging
// Return type		: BOOL 
BOOL CDragPage::IsDragging()
{
	return m_bDragging;
}

// Function name	: CDragPage::Draw
// Description	    : Draw drag object
// Return type		: void 
// Argument         : CSheetAlpha* pSheet
void CDragPage::Draw(CSheetAlpha* pSheet)
{
	static const int arDX = 0, arDY = -5, a = 7;
	if (!m_pViewTrackDrag)
		m_pRectSave->Restore();
	else
	{
		CRect rt = pSheet->GetPageRect(m_pViewTrackDrag);
		CRect rDraw = pSheet->GetDrawRect();
		rt.left = min(max(rt.left, rDraw.left),rt.right);
		pSheet->ClientToScreen(rt);
		rt.top = rt.top + arDY; rt.left = rt.left + arDX;
		int ar3p3p2 = (int)((double)a * sqrt(3)/6);
		CPoint points[3];
		 points[0] = rt.TopLeft() + CPoint(-a / 2,-ar3p3p2);
		 points[1] = rt.TopLeft() + CPoint(+a / 2,-ar3p3p2);
		 points[2] = rt.TopLeft() + CPoint(   0   ,ar3p3p2 * 2);
		if (m_pRectSave->IsChanged(points[0]))
		{
			CRgn rgn;
			if (rgn.CreatePolygonRgn(points, 3, WINDING))
			{
				m_pRectSave->Restore();
				m_pRectSave->Save(CRect(points[0], CSize(a,a)));

				CDC* pDC = CDC::FromHandle(::GetDC(NULL));
				
				// Draw the putirin
				pDC->FillRgn(&rgn, &CBrush(RGB(0,0,0)));
				// End draw putirin
				::ReleaseDC(NULL, pDC->m_hDC);
			}
		}
	}
}


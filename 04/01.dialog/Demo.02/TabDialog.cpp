// TabDialog.cpp : implementation file
//
// Written by Christophe Mestrallet 
// Copyright (c) 2000.
//
//
// This code may be used in compiled form in any way you desire. This
// file may be redistributed unmodified by any means PROVIDING it is 
// not sold for profit without the authors written consent, and 
// providing that this notice and the authors name is included. If 
// the source code in  this file is used in any commercial application 
// then acknowledgement must be made to the author of this file 
// (in whatever form you wish).
//
// This file is provided "as is" with no expressed or implied warranty.
// The author accepts no liability for any damage/loss of business that
// this product may cause.
//
// Expect bugs!
// 
// Please use and enjoy. Please let me know of any bugs/mods/improvements 
// that you have found/implemented and I will fix/incorporate them into this
// file. 
//
// 03 Jan 2000 - First release

#include "stdafx.h"
#include "TabDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define APPBAR_CALLBACK     WM_USER + 1010
#define IDT_AUTOHIDE 	1

#define SIZE_ICON_X 16
#define SIZE_ICON_Y 16

#define SIZE_CLOSE_X 15
#define SIZE_CLOSE_Y 15


//////////////////////////////////////////////////////////////////////
// CPolygon Class
// this class is used to Draw the polygon that
// represents the shape of the Window
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/*
 * CPolygon() constuctor
 */

CPolygon::CPolygon()
{
	m_nPoints = 0;
	m_pPoints = NULL;
}

/*
 * CPolygon() destructor
 * Free all the polygon points
 */
CPolygon::~CPolygon()
{
	Free();
}

/*
 * AddPoint() 
 * Add a point in the polygon
 */
void CPolygon::AddPoint(POINT &point)
{
	m_nPoints = m_nPoints+1;

	m_pPoints = (LPPOINT) realloc(m_pPoints, m_nPoints * sizeof(POINT));

	m_pPoints[m_nPoints-1].x = point.x;
	m_pPoints[m_nPoints-1].y = point.y;
}

/*
 * AddPoint() 
 * Add a point in the polygon
 */
void CPolygon::AddPoint(int x, int y)
{
    POINT point;

	point.x = x;
	point.y = y;
	AddPoint(point);

}

/*
 * Free() 
 * Free polygon points
 */
void CPolygon::Free()
{
	m_nPoints = 0;
	if (m_pPoints != NULL)
		free(m_pPoints);

	m_pPoints = NULL;
}


/////////////////////////////////////////////////////////////////////////////
// CTabDialog dialog

/*
 * CTabDialog() constuctor
 */

CTabDialog::CTabDialog( UINT nIDTemplate, CWnd* pParent /*=NULL*/)
	: CDialog(nIDTemplate, pParent)
{
	//{{AFX_DATA_INIT(CTabDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	// init private data
	m_bMoving = FALSE;
	m_nTabRound  = 2;
	m_nXIcon = 0;
	m_nYIcon = 0;
	m_nXControlsMoved = 0;
	m_nYControlsMoved = 0;
	m_bHiddenStatus  = FALSE;
	// init poublic data

	// original Window pos
	m_nXpos = 0;
	m_nYpos = 0;

	// original Window border
	m_nBorderPos = TAB_BORDER_LEFT;

	// Tab default height and width
	m_nTabHeight = 20;
	m_nTabWidth = 50;

	// Auto tab Width computation
	m_bAutoTabSize = TRUE;

	// TopMost Attribute
	m_bTopMost = TRUE;

	// AutoHide Attribute
	m_bAutoHide = TRUE;
	m_bCloseBox = TRUE;
	m_hTitleIcon = NULL;
	m_sTitle = _T("");
}

BEGIN_MESSAGE_MAP(CTabDialog, CDialog)
	//{{AFX_MSG_MAP(CTabDialog)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabDialog message handlers

/*
 * OnCreate
 *
 * Create Message Handler
 * Modify the Window Style to remove Caption , borders...
 */
int CTabDialog::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// we make sure the Window has no Border,Title 
	ModifyStyle( WS_CAPTION | WS_BORDER,0);
	
	// remove the dialog from the taskbar
	ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW);
	return 0;
}

/*
 * PositionWindowOnBorder
 *
 * Position the Window on a border of the desktop
 * point : the mouse position
 */
void CTabDialog::PositionWindowOnBorder( CPoint point)
{
    POINT ptCursor = {point.x, point.y};
    LONG cxScreen, cyScreen;
    RECT rFrame;
    RECT rNewFrame;
    int frameWidth;
    int frameHeight;
    BOOL bMove;
    int oldBorderPos;

	// Convert the mouse position to screen coordinates
	ClientToScreen(&ptCursor);
	GetWindowRect(&rFrame);

	// get the old Border position
	oldBorderPos = m_nBorderPos;
    CRect rect; 
    ::SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0); 
    //cxScreen = GetSystemMetrics(SM_CXSCREEN);
    //cyScreen = GetSystemMetrics(SM_CYSCREEN);
    cxScreen = rect.Width(); 
    cyScreen = rect.Height(); 
	frameWidth =  rFrame.right - rFrame.left;
	frameHeight =  rFrame.bottom - rFrame.top;

	// compute new frame position
	rNewFrame.left = ptCursor.x - m_dx;
	rNewFrame.top = ptCursor.y - m_dy ;

	// attach new frame position to a window border
	if (ptCursor.x < frameWidth)
	{
		rNewFrame.left = 0;
		bMove = TRUE;
		m_nBorderPos = TAB_BORDER_LEFT;
	}
	else
	if (ptCursor.x > cxScreen - frameWidth)
	{
		rNewFrame.left = cxScreen - frameWidth;
		bMove = TRUE;
		m_nBorderPos = TAB_BORDER_RIGHT;
	}
	else
		bMove = FALSE;

	if (ptCursor.y < frameHeight)
	{
		rNewFrame.top = 0;
		bMove = TRUE;
		m_nBorderPos = TAB_BORDER_TOP;
	}
	else if (ptCursor.y > cyScreen - frameHeight)
	{
		rNewFrame.top = cyScreen - frameHeight;
		bMove = TRUE;
		m_nBorderPos = TAB_BORDER_BOTTOM;
	}

	// if the mouse position is correct, we move the window
	if (bMove) 
	{
		m_nXpos = rNewFrame.left;
		m_nYpos = rNewFrame.top;

		// if the border has changed we compute the new polygon region
		if (oldBorderPos != m_nBorderPos)
		{
			CreateTabPolygon();
		}

		// move the window to a new position
		SetWindowPos(NULL, rNewFrame.left, rNewFrame.top, NULL, NULL, SWP_NOSIZE |  SWP_NOZORDER );
	}
}

/*
 * OnLButtonDown
 *
 * Button Down Message handler
 * Used for dragging the window on the desktop corners.
 */
void CTabDialog::OnLButtonDown(UINT nFlags, CPoint point) 
{
    POINT ptCursor = {point.x, point.y};
    RECT rFrame;

	ClientToScreen(&ptCursor);

	if (m_closeRect.PtInRect(point))
		SendMessage(WM_CLOSE,0,0);
	else
	{
		// Stop the Timer
		KillTimer (IDT_AUTOHIDE);
		m_bMoving = TRUE;
		GetWindowRect(&rFrame);
        
		// get the original pointer position
		m_dx = ptCursor.x - rFrame.left;
		m_dy = ptCursor.y - rFrame.top;

		// Capture the Window
		// Begin dragging the window
		SetCapture();	
	}
	
	CDialog::OnLButtonDown(nFlags, point);
}

/*
 * OnMouseMove
 *
 * Mouse Move Message handler
 * Used for dragging the window on the desktop corners.
 */
void CTabDialog::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (!m_bMoving)
    {
		return;
    }

	// move the window to the border
	PositionWindowOnBorder(point);
	CDialog::OnMouseMove(nFlags, point);
}

/*
 * OnLButtonUp
 *
 * Mouse Button Up Message handler
 * Release the Window on the corner we chose.
 */
void CTabDialog::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (!m_bMoving)
    {
		return;
    }

	// move the window to the border
	PositionWindowOnBorder(point);

	// stop dragging the window
	ReleaseCapture();				
	m_bMoving = FALSE;

	// restart the AutoHide Timer
	SetTimer(IDT_AUTOHIDE,500,NULL);	
    CDialog::OnLButtonUp(nFlags, point);
}

/*
 * SetAutoHide
 *
 * Update the AutoHide status of the Window
 * Start the AutoHide Timer
 */
void CTabDialog::SetAutoHide(BOOL bAutoHide)
{
	m_bAutoHide = bAutoHide;
	OnAutoHide();
}


/*
 * SetAutoHide
 *
 * Hide/show the Window
 * Start the AutoHide Timer
 */
void CTabDialog::OnAutoHide()
{
	if (m_bAutoHide == TRUE)
	{
		HideTabWindow();
		SetTimer(IDT_AUTOHIDE,500,NULL);
	}
	else
	{
		ShowTabWindow();
		KillTimer(IDT_AUTOHIDE);
	}
}

/*
 * SetTopMost
 *
 * Update the TopMost status of the Window
 */
void CTabDialog::SetTopMost(BOOL bTopMost)
{
	m_bTopMost = bTopMost;
	OnTopMost();
}

/*
 * SetTopMost
 *
 * Make th Window being TopMost / NoTopMost
 */
void CTabDialog::OnTopMost()
{

	if (m_bTopMost == TRUE)
	    SetWindowPos(&wndTopMost,
		             0, 0, 0, 0, 
			         SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
	else
	    SetWindowPos(&wndNoTopMost,
		             0, 0, 0, 0, 
			         SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);

}

/*
 * OnTimer
 *
 * Message handler for the AutoHide Timer.
 * Verify if the window needs to be shown or hide depending of the mouse position
 */
void CTabDialog::OnTimer(UINT nIDEvent) 
{
    CPoint pt;
    HWND hwndActive;
    CPoint ptCursor;
    CRect rc;

	if (nIDEvent = IDT_AUTOHIDE)
	{
		KillTimer (nIDEvent);
	 	GetCursorPos(&pt);
		ptCursor = pt;		
        hwndActive = (HWND) GetForegroundWindow();

		// offset the point for the hitTest
		ScreenToClient(&ptCursor);
		if (!m_closeRect.PtInRect(ptCursor))
		{
			// If the mouse is outside of our Region,
			// or we are not active,
			// or at least one window is active, or we are not the parent
			// of an active window, the hide the window.
			if (m_testRgn.PtInRegion(ptCursor))
				ShowTabWindow();
			else
				HideTabWindow();

		}

		SetTimer(IDT_AUTOHIDE,500,NULL);
	}
	CDialog::OnTimer(nIDEvent);
}


/*
 * HideTabWindow
 *
 * Hide the Tab Window
 * To hide the window, I move it in order to view only the Tab
 * To show the window, I move it back to its original position
 */
void CTabDialog::HideTabWindow()
{
    CRect rect;
    int width,height;
    int nX, nY;

	if (m_bHiddenStatus == TRUE) return;

	GetWindowRect(&rect);

	width = rect.right - rect.left;
	height = rect.bottom - rect.top;

	if (m_nBorderPos == TAB_BORDER_LEFT)
	{
		nX = m_nXpos - (width -m_nTabHeight);
		nY = m_nYpos;
	}
	else
	if (m_nBorderPos == TAB_BORDER_RIGHT)
	{
		nX = m_nXpos + (width - m_nTabHeight);
		nY = m_nYpos;
	}
	else
	if (m_nBorderPos == TAB_BORDER_TOP)
	{
		nX = m_nXpos;
		nY = m_nYpos  - (height  - m_nTabHeight);
	}
	else
	if (m_nBorderPos == TAB_BORDER_BOTTOM)
	{
		nX = m_nXpos;
		nY = m_nYpos  + (height  - m_nTabHeight);
	}

	SetWindowPos(NULL, nX, nY, NULL, NULL, SWP_NOSIZE |  SWP_NOZORDER );
	m_bHiddenStatus = TRUE;
}

/*
 * ShowTabWindow
 *
 * show the Tab Window
 * To show the window, I move it back to its original position
 */
void CTabDialog::ShowTabWindow()
{
	if (m_bHiddenStatus == FALSE) return;

	SetWindowPos(NULL, m_nXpos, m_nYpos, NULL, NULL, SWP_NOSIZE |  SWP_NOZORDER );

	m_bHiddenStatus = FALSE;

}

/*
 * EnumChildProc
 *
 * Callback used to move Child Windows
 * HWND : Child's handle
 * lParam :  pointer to a RECT structure containing :
 *	left : Father Left corner
 *	top : father top corner
 *  right : number of pixels to move the Child Window in the X direction
 *  bottom : number of pixels to move the Child Window in the Y direction
 */
BOOL CALLBACK EnumChildProc( HWND hwnd, 
							LPARAM lParam)
{
    RECT rect;
    CRect *pRect;
    POINT pt2;

	pRect = (CRect *)(lParam);
	GetWindowRect(hwnd,&rect);
	pt2.x = rect.left - pRect->left + pRect->right;
	pt2.y = rect.top  - pRect->top + pRect->bottom;
	SetWindowPos(hwnd,NULL, pt2.x , pt2.y , NULL, NULL, SWP_NOSIZE |  SWP_NOZORDER );

	return(TRUE);
}

/*
 * MoveDialogControls
 *
 * Move all the child controls in the Dialog
 * nX : number of pixels to move the controls in the X Direction
 * nY : number of pixels to move the controls in the Y Direction
 */
void CTabDialog::MoveDialogControls(int nX,int nY)
{
    CRect *pRect;
	pRect = new CRect;
	GetWindowRect(pRect);
	pRect->right  = nX - m_nXControlsMoved;
	pRect->bottom = nY - m_nYControlsMoved;
	m_nXControlsMoved = nX;
	m_nYControlsMoved = nY;
	EnumChildWindows( this->m_hWnd, 
						&EnumChildProc, 
					 (LPARAM)	pRect);
 
    delete (pRect);	
}

/*
 * CreateTabPolygon
 *
 * Create a polygon designing the borders of the Window
 * Create a region based on this polygon
 * Apply the region to the Window
 */
void CTabDialog::CreateTabPolygon()
{
    int x;
    int y;
    CRect rect;
    int tabDec;
    int nXClose, nYClose;


	if ( (m_nBorderPos  == TAB_BORDER_TOP) || (m_nBorderPos == TAB_BORDER_BOTTOM))
	{
		// update Window Height in order to create the Tab
		SetWindowPos(NULL, m_nXpos, m_nYpos, m_nInitialWidth, m_nInitialHeight + m_nTabHeight, SWP_NOZORDER );
		tabDec = m_nInitialWidth - m_nTabWidth;

		// move all controls in the Window

		if (m_nBorderPos == TAB_BORDER_BOTTOM)
			MoveDialogControls(0,m_nTabHeight);
		else
			MoveDialogControls(0,0);
	}
	else
	{
		// update Window Width in order to create the Tab
		SetWindowPos(NULL, m_nXpos, m_nYpos, m_nInitialWidth + m_nTabHeight, m_nInitialHeight, SWP_NOZORDER );
		tabDec = m_nInitialHeight - m_nTabWidth;

		// move all controls in the Window
		if (m_nBorderPos == TAB_BORDER_RIGHT)
			MoveDialogControls(m_nTabHeight,0);
		else
			MoveDialogControls(0,0);

	}
	// free the old polygon 
	m_polygon.Free();

	// get window size
	GetWindowRect(&rect);

	// create a polygon used for Region and Drawing
	if (m_nBorderPos == TAB_BORDER_LEFT) 
	{
		x = 0;
		y = 0;
		m_polygon.AddPoint(x,y);
		x = rect.Width() -  m_nTabHeight -m_nTabRound;
		m_polygon.AddPoint(x,y);
		x = rect.Width() - m_nTabHeight ;
		y = m_nTabRound;
		m_polygon.AddPoint(x,y);
		y = tabDec -m_nTabRound;
		m_polygon.AddPoint(x,y);
		x = rect.Width() - m_nTabHeight +m_nTabRound;
		y = tabDec;
		m_polygon.AddPoint(x,y);
		x = rect.Width() - m_nTabRound;
		m_polygon.AddPoint(x,y);
		x = rect.Width();
		y = tabDec + m_nTabRound;
		m_polygon.AddPoint(x,y);
		y = rect.Height()  -m_nTabRound-1;
		m_polygon.AddPoint(x,y);
		x = rect.Width() -m_nTabRound-1;
		y = rect.Height();
		m_polygon.AddPoint(x,y);
		x = 0;
		m_polygon.AddPoint(x,y);
		y = 0;
		m_polygon.AddPoint(x,y);

		m_nXIcon = rect.Width()  - m_nTabHeight + m_nTabRound;
		m_nYIcon = rect.Height() - m_nTabRound;
	}
	else
	if (m_nBorderPos == TAB_BORDER_RIGHT) 
	{
		x = m_nTabRound;
		y = tabDec;
		m_polygon.AddPoint(x,y);
		x = 0;
		y = tabDec + m_nTabRound;
		m_polygon.AddPoint(x,y);
		y = rect.Height() - m_nTabRound;
		m_polygon.AddPoint(x,y);
		x = m_nTabRound;
		y = rect.Height();
		m_polygon.AddPoint(x,y);
		x = rect.Width();
		m_polygon.AddPoint(x,y);
		y = 0;
		m_polygon.AddPoint(x,y);
		x = m_nTabHeight +  m_nTabRound;
		m_polygon.AddPoint(x,y);
		x = m_nTabHeight;
		y = m_nTabRound;
		m_polygon.AddPoint(x,y);
		y = tabDec - m_nTabRound;
		m_polygon.AddPoint(x,y);
		x = m_nTabHeight -m_nTabRound;
		y = tabDec;
		m_polygon.AddPoint(x,y);
		x = m_nTabRound;
		y = tabDec;
		m_polygon.AddPoint(x,y);

		m_nXIcon = m_nTabRound;
		m_nYIcon = rect.Height() - m_nTabRound;
	}
	else
	if (m_nBorderPos == TAB_BORDER_TOP) 
	{
		x = 0;
		y = 0;
		m_polygon.AddPoint(x,y);
		x = rect.Width();
		y = 0;
		m_polygon.AddPoint(x,y);
		y = rect.Height() - m_nTabHeight - m_nTabRound;
		m_polygon.AddPoint(x,y);
		x = rect.Width() - m_nTabRound;
		y = rect.Height() - m_nTabHeight;
		m_polygon.AddPoint(x,y);
		x = rect.Width() - tabDec + m_nTabRound;
		m_polygon.AddPoint(x,y);
		x = rect.Width() - tabDec ;
		y = rect.Height() - m_nTabHeight + m_nTabRound;
		m_polygon.AddPoint(x,y);			
		y = rect.Height() - m_nTabRound;
		m_polygon.AddPoint(x,y);
		x = rect.Width() - tabDec  - m_nTabRound;
		y = rect.Height();
		m_polygon.AddPoint(x,y);				
		x = m_nTabRound;
		m_polygon.AddPoint(x,y);
		x = 0;
		y = rect.Height() - m_nTabRound;
		m_polygon.AddPoint(x,y);
		y = 0;
		m_polygon.AddPoint(x,y);
		
		m_nXIcon = m_nTabRound;
		m_nYIcon = rect.Height() - (m_nTabHeight  -m_nTabRound);
	}
	else
	if (m_nBorderPos == TAB_BORDER_BOTTOM) 
	{
		x = 0;
		y = m_nTabRound;
		m_polygon.AddPoint(x,y);
		x = m_nTabRound;
		y = 0;
		m_polygon.AddPoint(x,y);
		x = rect.Width() - tabDec - m_nTabRound;
		m_polygon.AddPoint(x,y);
		x = rect.Width() - tabDec;
		y = m_nTabRound;
		m_polygon.AddPoint(x,y);
		y = m_nTabHeight - m_nTabRound;
		m_polygon.AddPoint(x,y);
		x = rect.Width() - tabDec + m_nTabRound;
		y = m_nTabHeight;
		m_polygon.AddPoint(x,y);
		x = rect.Width() - m_nTabRound;
		m_polygon.AddPoint(x,y);
		x = rect.Width();
		y = m_nTabHeight + m_nTabRound;
		m_polygon.AddPoint(x,y);
		y = rect.Height();
		m_polygon.AddPoint(x,y);
		x = 0;
		m_polygon.AddPoint(x,y);
		y = m_nTabRound;
		m_polygon.AddPoint(x,y);
		
		m_nXIcon = m_nTabRound;
		m_nYIcon = m_nTabRound;

	}

	m_nXDC = nXClose = m_nXIcon ;
	m_nYDC = nYClose = m_nYIcon;

	// compute new position for memory DC and for the Close Rectangle
	if ((m_nBorderPos == TAB_BORDER_BOTTOM) || (m_nBorderPos == TAB_BORDER_TOP))
	{
		// if there is an icon, increase X position of the memory HDC
		if (m_hTitleIcon != NULL)
			m_nXDC += SIZE_ICON_X + m_nTabRound;

		nXClose  = m_nXDC +  m_DCRect.Width() +  2*m_nTabRound;

		m_closeRect.left	= nXClose;
		m_closeRect.right	= m_closeRect.left + SIZE_CLOSE_X;
		m_closeRect.top		= m_nYDC + (m_nTabHeight -SIZE_CLOSE_Y)  / 2 - m_nTabRound;
		m_closeRect.bottom	= m_closeRect.top + SIZE_CLOSE_Y;
	}
	else
	{
		// if there is an icon, increase Y position of the memory HDC
		if (m_hTitleIcon != NULL)
			m_nYDC -=  (SIZE_ICON_Y +m_nTabRound);

		nYClose = m_nYDC -(m_DCRect.Width()+ 2*m_nTabRound);
		
		m_closeRect.left	= m_nXDC + (m_nTabHeight -SIZE_CLOSE_X)  / 2 - m_nTabRound;
		m_closeRect.right	= m_closeRect.left + SIZE_CLOSE_X;
		m_closeRect.bottom	= nYClose;
		m_closeRect.top 	= m_closeRect.bottom - SIZE_CLOSE_Y;
	}

	// delete old region if necessary
	if (m_Rgn.m_hObject != NULL)
		m_Rgn.DeleteObject();

	if (m_testRgn.m_hObject != NULL)
		m_testRgn.DeleteObject();

	// create a new Region based on the PolyGon
	m_Rgn.CreatePolygonRgn (m_polygon.m_pPoints,m_polygon.m_nPoints,WINDING);
	

	// region used for hit Test
	// we need another region for the HitTest because SetWindowRgn handle m_Rgn
	m_testRgn.CreatePolygonRgn(m_polygon.m_pPoints,m_polygon.m_nPoints,WINDING);

	// appy the region to the Window
	SetWindowRgn(m_Rgn, TRUE);

	// force the Window to be drawn
	Invalidate();
}

/*
 * ComputeTabSize
 *
 * Compute the Tab size if m_bAutoTabSize member  is TRUE
 * the tab Size depends of : 
 * - the Window Title
 * - the Window Icon if not NULL
 */
void CTabDialog::ComputeTabSize()
{
	if (m_bAutoTabSize == TRUE)
	{
        CSize size;
        CDC *pDc = GetDC();
        CFont *pOldFont;
		pOldFont = pDc->SelectObject(GetFont());

		m_nTabWidth = 0;
		if (m_hTitleIcon != NULL)
			m_nTabWidth += SIZE_ICON_X;
	
		if (m_bCloseBox == TRUE)
			m_nTabWidth += SIZE_CLOSE_X + 2*m_nTabRound;

	    size = pDc->GetTextExtent(m_sTitle);
		
		m_nTabWidth += (size.cx  + 3*m_nTabRound);

		if (pOldFont != NULL)
			pDc->SelectObject(pOldFont);

		// verify the tab With is not bigger tha the Window's borders
		if ( (m_nTabWidth > m_nInitialWidth) || ( m_nTabWidth > m_nInitialHeight) )
		{
			m_nTabWidth = __min(m_nInitialWidth,m_nInitialHeight);	
		}
	}
}

/*
 * InitTitleDC
 *
 * Create a new device context for the title
 * tis device context is usefull if we want vertical title.
 */
void CTabDialog::InitTitleDC()
{
    CDC *pDc = GetDC();
    CRect textRect;

	m_DCRect.left = 0;
	m_DCRect.right = m_nTabWidth - 3*m_nTabRound;
	m_DCRect.top = 0;
	m_DCRect.bottom = m_nTabHeight - 2 * m_nTabRound;

	if (m_hTitleIcon != NULL)
		m_DCRect.right -= SIZE_ICON_X;

	if (m_bCloseBox == TRUE)
		m_DCRect.right -= (SIZE_CLOSE_X + 2*m_nTabRound);


	m_pDC.CreateCompatibleDC(pDc);
	m_bitmap.CreateCompatibleBitmap(pDc, m_DCRect.Width(), m_DCRect.Height());
	m_pDC.SelectObject(&m_bitmap);

	m_pDC.SetWindowOrg(0,0);

	m_pDC.SetBkColor(GetSysColor(COLOR_3DFACE));
	m_pDC.SetBkMode(TRANSPARENT);
	m_pDC.SelectObject(GetFont());
	m_pDC.SetTextColor(GetSysColor(COLOR_BTNTEXT));

	CBrush brush(GetSysColor(COLOR_3DFACE));

	m_pDC.FillRect( &m_DCRect, &brush);

	m_pDC.DrawText(m_sTitle,&m_DCRect, DT_LEFT | DT_VCENTER |DT_NOPREFIX |DT_END_ELLIPSIS);
}



/*
 * OnInitDialog
 *
 * Initialize the TabDialog
 */
BOOL CTabDialog::OnInitDialog() 
{
    CRect rect;
	GetWindowRect(&rect);
	m_nInitialWidth  = rect.Width() ;
	m_nInitialHeight = rect.Height() ;

	// make sure X and Y positions are correct depending on the window position
	if ((m_nBorderPos == TAB_BORDER_BOTTOM) || (m_nBorderPos == TAB_BORDER_TOP))
		m_nYpos  = 0;
	else
		m_nXpos = 0;

	CDialog::OnInitDialog();

	ComputeTabSize();	
	InitTitleDC();
	CreateTabPolygon();
	
	OnAutoHide();
	OnTopMost();
	
	return TRUE;  
}


/*
 * OnEraseBkgnd
 *
 * Draw the Window Border and the Window Title
 */
BOOL CTabDialog::OnEraseBkgnd(CDC *pDC)
{
    CPen PenBorder(PS_SOLID,2,GetSysColor(COLOR_3DDKSHADOW ));
    CPen PenLightBorder(PS_SOLID,2,GetSysColor(COLOR_3DHIGHLIGHT));
    BOOL bRet;

	// calls the bas Dialog Method
	bRet = CDialog::OnEraseBkgnd(pDC);

	// if there are no points in the polygon, we return.....

	if (m_polygon.m_nPoints == 0) return(bRet);

	// draw the light border all around the window
	pDC->SelectObject(&PenLightBorder);
	pDC->Polyline(m_polygon.m_pPoints,m_polygon.m_nPoints);

	// draw the dark border depending of the window position
	pDC->SelectObject(&PenBorder);
	if (m_nBorderPos == TAB_BORDER_LEFT)
	{
		pDC->MoveTo (m_polygon.m_pPoints[2]);
		pDC->LineTo (m_polygon.m_pPoints[3]);
		pDC->MoveTo (m_polygon.m_pPoints[6]);
		pDC->LineTo (m_polygon.m_pPoints[7]);
		pDC->LineTo (m_polygon.m_pPoints[8]);
		pDC->LineTo (m_polygon.m_pPoints[9]);
	}
	else
	if (m_nBorderPos == TAB_BORDER_RIGHT)
	{
		pDC->MoveTo (m_polygon.m_pPoints[3]);
		pDC->LineTo (m_polygon.m_pPoints[4]);
		pDC->LineTo (m_polygon.m_pPoints[5]);
	}
	else
	if (m_nBorderPos == TAB_BORDER_TOP)
	{
		pDC->MoveTo (m_polygon.m_pPoints[1]);
		pDC->LineTo (m_polygon.m_pPoints[2]);
		pDC->LineTo (m_polygon.m_pPoints[3]);
		pDC->LineTo (m_polygon.m_pPoints[4]);
		pDC->LineTo (m_polygon.m_pPoints[5]);
		pDC->LineTo (m_polygon.m_pPoints[6]);
		pDC->LineTo (m_polygon.m_pPoints[7]);
		pDC->LineTo (m_polygon.m_pPoints[8]);
	}
	else
	if (m_nBorderPos == TAB_BORDER_BOTTOM)
	{
		pDC->MoveTo (m_polygon.m_pPoints[3]);
		pDC->LineTo (m_polygon.m_pPoints[4]);
		pDC->MoveTo (m_polygon.m_pPoints[7]);
		pDC->LineTo (m_polygon.m_pPoints[8]);
		pDC->LineTo (m_polygon.m_pPoints[9]);
	}

	// if we need an icon, draw it
	if (m_hTitleIcon != NULL)
	{
		if ((m_nBorderPos == TAB_BORDER_BOTTOM) || (m_nBorderPos == TAB_BORDER_TOP))
		{
			DrawIconEx(pDC->m_hDC,m_nXIcon,m_nYIcon,m_hTitleIcon, SIZE_ICON_X,SIZE_ICON_Y,NULL,NULL, DI_NORMAL);
		}
		else
		{
			DrawIconEx(pDC->m_hDC,m_nXIcon,m_nYIcon - SIZE_ICON_X,m_hTitleIcon, SIZE_ICON_X,SIZE_ICON_Y,NULL,NULL, DI_NORMAL);
		}
	}
   
	// if the title hdc is OK we draw it back to the Window
	if (m_pDC.m_hDC != NULL)
	{
		if ((m_nBorderPos == TAB_BORDER_BOTTOM) || (m_nBorderPos == TAB_BORDER_TOP))
		{
			// on the top and bottom border the title is hrizontal
			pDC->BitBlt( m_nXDC,m_nYDC, m_DCRect.Width(),  m_DCRect.Height(), &m_pDC, 0, 0, SRCCOPY );
		}
		else
		{
			// on the left and right border the title is vertical, so we need to rotate the DC
			POINT	pnts[3];
			CBitmap bitmap;
			pnts[0].x	=	m_nXDC;
			pnts[0].y	=	m_nYDC;
			pnts[1].x	=	m_nXDC;
			pnts[1].y	=	m_nYDC - m_DCRect.Width() ;
			pnts[2].x	=	m_nXDC + m_DCRect.Height();
			pnts[2].y	=	m_nYDC;
			pDC->PlgBlt(pnts,
						&m_pDC,
						0,
						0,
						m_DCRect.Width(),
						m_DCRect.Height(),
						CBitmap(),
						0,
						0);
		}
	}

	// if we need the CloseBox , Draw it
	if (m_bCloseBox == TRUE)
	{
		CPen PenBorder2(PS_SOLID,1,GetSysColor(COLOR_3DDKSHADOW ));
		CPen PenLightBorder2(PS_SOLID,1,GetSysColor(COLOR_3DSHADOW ));
		CPen PenHighlightBorder2(PS_SOLID,1,GetSysColor(COLOR_3DHIGHLIGHT));

		m_closeRect.InflateRect(-1,-1);

		pDC->SelectObject(&PenHighlightBorder2);
		pDC->MoveTo(m_closeRect.left, m_closeRect.top);
		pDC->LineTo(m_closeRect.right, m_closeRect.top);
		pDC->MoveTo(m_closeRect.left, m_closeRect.top);		
		pDC->LineTo(m_closeRect.left, m_closeRect.bottom);

		pDC->SelectObject(&PenBorder2);
		pDC->MoveTo(m_closeRect.right, m_closeRect.top);
		pDC->LineTo(m_closeRect.right, m_closeRect.bottom);
		pDC->LineTo(m_closeRect.left-1, m_closeRect.bottom);

		pDC->MoveTo(m_closeRect.left+4, m_closeRect.top+4);
		pDC->LineTo(m_closeRect.right-4, m_closeRect.bottom-3);
		pDC->MoveTo(m_closeRect.left+4, m_closeRect.bottom-4);
		pDC->LineTo(m_closeRect.right-4, m_closeRect.top+3);

		pDC->SelectObject(&PenLightBorder2);
		pDC->MoveTo(m_closeRect.left + 1, m_closeRect.bottom - 1);
		pDC->LineTo(m_closeRect.right-1, m_closeRect.bottom-1);
		pDC->LineTo(m_closeRect.right-1, m_closeRect.top);

		m_closeRect.InflateRect(1,1);
	}

	return(bRet);
}

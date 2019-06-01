/////////////////////////////////////////////////////////////////////////////
// This is an extension to the MFC C++ library.
// Copyright (C) 1997-1998 ACPSoft
// All rights reserved.
//
// This source code is only intended as a building
// tool to aid your own development.  This code is
// under the license agreement provided with the
// software. By using this code in your own project(s)
// you agree to the terms in that license.
/////////////////////////////////////////////////////////////////////////////

// MFC includes
#include "stdafx.h"
#include <afxpriv.h> 
#include <..\src\afximpl.h> 

// Local includes
#include "GripDialogBar.h" 

#ifdef _DEBUG 
#undef THIS_FILE 
static char THIS_FILE[]=__FILE__; 
#define new DEBUG_NEW 
#endif

/////////////////////////////////////////////////////////////////// 
// Class CInitDialogBar 
// 
// Class provides new behavior for OnInitDialogBar() 
// and DDX support for common CDialogBar
//  
/////////////////////////////////////////////////////////////////// 

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CInitDialogBar, CDialogBar)

CInitDialogBar::CInitDialogBar()
{
	// In derived classes set intial
	// state of control(s) in the derived
	// constructor
}

CInitDialogBar::~CInitDialogBar()
{
}

BEGIN_MESSAGE_MAP(CInitDialogBar, CDialogBar)
	//{{AFX_MSG_MAP(CInitDialogBar)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CInitDialogBar::Create(CWnd * pParentWnd, UINT nIDTemplate, UINT nStyle, UINT nID)
{
	ASSERT(pParentWnd);

	m_dwStyle = nStyle;

	//Let MFC Create the control
	if(!CDialogBar::Create(pParentWnd,
		nIDTemplate,
		nStyle,
		nID))
		return FALSE;

	// Since there is no WM_INITDIALOG message we have to call
	// our own InitDialog function ourselves after m_hWnd is valid
	if(!OnInitDialogBar())
		return FALSE;
	return TRUE;
}

BOOL CInitDialogBar::Create(CWnd * pParentWnd, LPCTSTR lpszTemplateName, UINT nStyle, UINT nID)
{
	ASSERT(pParentWnd);

	m_dwStyle = nStyle;

	//Let MFC Create the control
	if(!CDialogBar::Create(pParentWnd,
		lpszTemplateName,
		nStyle,
		nID))
		return 0;

	// Since there is no WM_INITDIALOG message we have to call
	// our own InitDialog function ourselves after m_hWnd is valid
	if(!OnInitDialogBar())
		return FALSE;
	return TRUE;
}

BOOL CInitDialogBar::OnInitDialogBar()
{
	// Support for the MFC DDX model
	// If you do not want this do not 
	// call the base class from derived 
	// classes
	UpdateData(FALSE);
	return TRUE;
}

void CInitDialogBar::DoDataExchange(CDataExchange* pDX) 
{
	//Derived Classes Overide this function
	ASSERT(pDX);

	// In derived class call the DDX_???
	// functions to set retrieve values
	// of your controls
	// See example derived class for how
	// to do this.
	CDialogBar::DoDataExchange(pDX);
}

//////////////////////////////////////////////////////////////////////
// Class CGripDialogBar 
// 
// Class provides new behavior for drawing the 
// CDialog Bar make it like a DevStudio workspace
//  
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction 
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CGripDialogBar, CInitDialogBar) 

CGripDialogBar::CGripDialogBar()
{
	
	// Default style Gripper bars and
	// close button only to add text
	// dockbutton or title use the
	// GBS_??? flags
	m_GripBar = new CGripControl();
	m_bActive = -1;
}

CGripDialogBar::CGripDialogBar(UINT nID, DWORD Style, COLORREF clr)
{

	// To use color be sure to
	// Set the GBS_USECOLOR bit

	// GBS_DOCKAPPST - Display App String
	// GBS_DOCKBUTTON - Display the dock button
	// GBS_DOCKCLOSE - Display the close button
	// GBS_DOCKTITLE - Displays window title
	// GBS_NOGRADIENT - Use solid color
	// GBS_NOGRIPBARS - Do not display grip bars
	// GBS_USECOLOR - Use user defined color
	
	m_GripBar = new CGripControl(nID, Style, clr);
	m_bActive = -1;
}

CGripDialogBar::~CGripDialogBar() 
{ 

	// Cleanup
	if(m_GripBar)
		delete m_GripBar;
}

BEGIN_MESSAGE_MAP(CGripDialogBar, CInitDialogBar) 
	//{{AFX_MSG_MAP(CInitDialogBar)
	ON_WM_CLOSE()
	ON_WM_ERASEBKGND()
	ON_WM_NCACTIVATE()
	ON_WM_NCPAINT() 
	ON_WM_PAINT()
	//}}AFX_MSG_MAP 
END_MESSAGE_MAP()

void CGripDialogBar::GetCaptionRect(CRect* rect)
{

	// Get the frame size
	DWORD style = GetStyle();

	CSize frame;
	if(style & WS_BORDER)
		frame = CSize(GetSystemMetrics(SM_CXFIXEDFRAME),
				GetSystemMetrics(SM_CXFIXEDFRAME));
	else
		frame = CSize(GetSystemMetrics(SM_CXFIXEDFRAME),
				GetSystemMetrics(SM_CYFIXEDFRAME));

	// Compute caption area
	GetWindowRect(rect);
	CPoint pt(rect->left, rect->top);

	// Our DC has 0,0 as it origin
	*rect -= pt;	

	// Adjust for window frame
	rect->left  += frame.cx;			
	rect->right -= frame.cx;
	rect->top   += frame.cy;
	rect->bottom = rect->top + GetSystemMetrics(SM_CYCAPTION)
		- GetSystemMetrics(SM_CYBORDER);
	return;
}

inline
DWORD CGripDialogBar::GetGripStyle()
{
	return m_GripBar->m_GBStyle;
}

void CGripDialogBar::ModifyGripStyle(DWORD remove, DWORD add)
{
	m_GripBar->m_GBStyle = m_GripBar->m_GBStyle | add;
	m_GripBar->m_GBStyle = m_GripBar->m_GBStyle & ~remove;
	m_GripBar->Abolish();
}

void CGripDialogBar::SetActiveState(UINT nState)
{
	if(!IsWindow(m_hWnd))
		return;

	WPARAM state;

	// Call this function from your main frame
	// OnActivate Handler. Example:
	// void CMainFrame::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
	// {
	//      m_YourObject.SetActiveState(nState); <-- Add this line
	//      CMDIFrameWnd::OnActivate(nState, pWndOther, bMinimized);
	//      return;
	// }

	if(nState == WA_INACTIVE)
		state = FALSE;
	else
		state = TRUE;

	SendMessage(WM_NCACTIVATE, state, 0);
	return;
}

void CGripDialogBar::StartDrag(CPoint point)
{
	ASSERT(m_pDockContext != NULL);

	m_pDockContext->StartDrag(point);
	Invalidate(TRUE);
}

void CGripDialogBar::ToggleDocking()
{
	 ASSERT(m_pDockContext != NULL); 

     m_pDockContext->ToggleDocking(); 
}

void CGripDialogBar::View(CFrameWnd* fWnd, BOOL state)
{
	ASSERT(fWnd);

	// Put this function in your handler
	// which toggles the view of the control
	fWnd->ShowControlBar(this, state, FALSE);
}

BOOL CGripDialogBar::OnInitDialogBar() 
{ 

	// To display a title modify your resource
	// select the title checkbox, the grip bar will
	// take the title of the window. Set your
	// margin at 16 or more dialog units. See below.
	m_GripBar->Fasten(this);

	// To avoid MFC bugs with edit controls we need
	// to turn off the caption style and provide our
	// own caption. This means in your resource you
	// need to leave a little space at the top for
	// the caption. Set the top margin at 16 DLG Units
	// This works well.
	ModifyStyle(WS_CAPTION, 0);
	
	// Setup the overidden context for Docking.
	// We will use this context to provide our own 
	// docking functionality.  By doing this ourselves
	// now instead of during Enable docking we are
	// able to replace the original member variable
	// with our new class. All changes MUST occur
	// in virtual functions. 
     if (m_pDockContext == NULL) 
          m_pDockContext = new CExDockContext(this); 
     ASSERT(m_pDockContext); 

     // Call Base Class. You must do this
     CInitDialogBar::OnInitDialogBar(); 
     return TRUE; 
}

void CGripDialogBar::ExcludeCaption(CDC* pDC) 
{ 

	// Compute caption area
	CRect capRect;
	CRect rcWin;
	GetWindowRect(rcWin);
	GetCaptionRect(&capRect);

	// There is no need to paint the caption
	// area twice so only our provided caption
	// paint it. The parent need not paint
	// the same area. This helps to prevent
	// flicker in drawing.
	pDC->ExcludeClipRect(&capRect);
} 

void CGripDialogBar::PaintRect(CDC* pDC, int x, int y, int w, int h, COLORREF color)
{
	CBrush brush(color);
	CBrush* pOldBrush = pDC->SelectObject(&brush);
	pDC->PatBlt(x, y, w, h, PATCOPY);
	pDC->SelectObject(pOldBrush);
}

void CGripDialogBar::RecalcLayout() 
{ 
	// If we are floating we do not want 
	// our new caption to be visible, 
	// so we move our window up so our 
	// caption is underneath the CMiniFrameWnd 
	// caption 
	if(IsFloating()) 
	{
		CRect rect; 

		GetWindowRect(rect); 

		SetWindowPos(NULL, 
			0, 
			-(GetSystemMetrics(SM_CYCAPTION) 
			+ GetSystemMetrics(SM_CYFRAME)), 
			rect.Width(), 
			rect.Height(), 
			NULL); 
	} 
} 

void CGripDialogBar::OnClose() 
{
	CFrameWnd* wnd;

	wnd = (CFrameWnd*) AfxGetMainWnd();
	ASSERT(wnd);

	// Make sure your main Wnd is really a 
	// Frame Wnd Object else we do nothing
	// This protects us from apps which do not
	// use CFrameWnd for their main window.
	// Those apps will need to override to
	// provide their own support for close.
	if(wnd->IsKindOf(RUNTIME_CLASS(CFrameWnd)))
	{

		// Close (really hide) our control bar
		wnd->ShowControlBar(this, FALSE, FALSE);
	}
	return;
}

BOOL CGripDialogBar::OnEraseBkgnd(CDC* pDC)
{
	ExcludeCaption(pDC);
	CInitDialogBar::OnEraseBkgnd(pDC);
	return TRUE;
}

BOOL CGripDialogBar::OnNcActivate(BOOL bActive) 
{ 

	// Tell the control which of our two
	// caption bitmaps to paint
	m_bActive = bActive;

	m_GripBar->Invalidate(TRUE);
	return TRUE;
}

void CGripDialogBar::OnPaint() 
{ 
	// Notice here we break the do not call 
	// the base class OnPaint Rule. This is 
	// because we do not set up our own DC 
	// here so calling the base is OK and
	// also required otherwise we need to
	// redo what the base already does for us 
	RecalcLayout(); 
	CDialogBar::OnPaint(); 
} 


/////////////////////////////////////////////////////////////////// 
// Class CGripControl 
// 
// Class provides new behavior for drawing the 
// CDialog Bar make it like a DevStudio workspace
//  
/////////////////////////////////////////////////////////////////// 

// Local defines
#define WHITE RGB(255,255,255)
#define BLACK RGB(0,0,0)
#define GRADBOXWIDTH 80
#define HLSMAX 240	
#define RGBMAX 255

// Local functions
// The following function is
/////////////////////////////////////////////////
// Copyright (1997) Microsoft Systems Journal
/////////////////////////////////////////////////
static int GetLuminosity(COLORREF color)
{
	int r = GetRValue(color);
	int g = GetGValue(color);
	int b = GetBValue(color);
	int rgbMax = max( max(r,g), b);
	int rgbMin = min( min(r,g), b);
	return (((rgbMax+rgbMin) * HLSMAX) + RGBMAX ) / (2*RGBMAX);
}
/////////////////////////////////////////////////
// End MSJ code
/////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////// 
// Construction/Destruction 
////////////////////////////////////////////////////////////////////// 
IMPLEMENT_DYNCREATE(CGripControl, CEdit)

CGripControl::CGripControl()
{
	// Default style
	// Gripper bars and close
	// button only to add text
	// dockbutton or title use
	// the GBS flags
	m_nID = 0;
	m_GBStyle = GBS_DOCKCLOSE;
	m_prevHitTest = -1;

	// DevStudio Generated String
	// for application title
	UINT id = AFX_IDS_APP_TITLE;
	m_appString.LoadString(id);
}

CGripControl::CGripControl(UINT nID, DWORD Style, COLORREF clr)
{
	m_ColorCap = clr;
	m_GBStyle = Style;
	m_prevHitTest = -1;
	m_nID = nID;

	// DevStudio Generated String
	// for application title
	UINT id = AFX_IDS_APP_TITLE;
	m_appString.LoadString(id);
}

CGripControl::~CGripControl()
{
}


BEGIN_MESSAGE_MAP(CGripControl, CEdit)
	//{{AFX_MSG_MAP(CGripControl)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SETTINGCHANGE()
	ON_WM_SYSCOLORCHANGE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGripControl message handlers

void CGripControl::Abolish()
{
	// Next time we paint use the newly
	// seleted settings.
	m_fontCap.DeleteObject();
	m_fontTitle.DeleteObject();
	m_rcCap.SetRectEmpty();	
}

void CGripControl::Fasten(CGripDialogBar* pControlBar)
{
	ASSERT(pControlBar);
	ASSERT(pControlBar->IsKindOf(RUNTIME_CLASS(CGripDialogBar)));
	
	m_pControlBar = pControlBar;

	// Setup the Grip Bar Control
	// using the parms from the control
	// Get the text and rect from control
	CString str;
	m_pControlBar->GetWindowText(str);

	// Dummy Rect for Creation purposes
	// The window is moved to the proper
	// location during erase background
	CRect rc(0,0,10,50);
	Create(WS_VISIBLE,
		rc,
		m_pControlBar,
		m_nID);
	ASSERT(IsWindow(m_hWnd));

	SetWindowText(str);
}

inline
CString CGripControl::GetBarTitle()
{
	CString str;

	GetWindowText(str);
	return str;
}

inline 
void CGripControl::GetCaptionRect(CRect* rect)
{
	GetClientRect(rect);
	return;
}

void CGripControl::CreateFonts()
{
	NONCLIENTMETRICS ncm;
	ncm.cbSize = sizeof(ncm);
	VERIFY(SystemParametersInfo(SPI_GETNONCLIENTMETRICS,
		0,
		&ncm,
		0));

	// Derived classes can esily override to provide
	// their own font support
	m_fontCap.CreateFontIndirect(&ncm.lfCaptionFont);
	m_fontTitle.CreateFontIndirect(&ncm.lfCaptionFont);
} 

void CGripControl::OnNcDraw(CDC* pDC)
{

	// We will draw on a MemDC then BitBlt
	// the bmp to the window DC
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);

	// See if we need a new bitmap
	UpdateBitmap(m_pControlBar->m_bActive,
		&memDC,
		pDC);

	// Get paint area 
	// It's set by update bitmap
	CRect& rc = m_rcCap;

	// OK Paint
	pDC->BitBlt(rc.left,
		rc.top,
		rc.Width(),
		rc.Height(),
		&memDC,
		0,
		0,
		SRCCOPY);
	return;
}

void CGripControl::DrawOnBitmap(BOOL bActive, CDC* pMemDC, CRect* pRC)
{
	int w = pRC->Width();
	int cxIcon = GetSystemMetrics(SM_CXSIZE);
	int cyIcon = GetSystemMetrics(SM_CYSIZE);

	// Paint our inactive bmp
	if (!bActive)
	{

		// Let's not get fancy; when we are inactive
		// The window is probably out of view anyway.
		// Don't waste CPU cycles on something no one
		// may ever see. So we will just fill the caption
		// Rect with the default inactive color
		PaintRect(pMemDC,
			0,
			0,
			pRC->Width(),
			pRC->Height(),
			GetSysColor(COLOR_INACTIVECAPTION));
	}
	else
	{
		// Active : We paint according to
		// which flags are set
		COLORREF clr;

		// Do we use windows default
		// or user supplied color
		if(m_GBStyle & GBS_USECOLOR)
		{

			// user supplied
			clr = m_ColorCap;
		}
		else
		{

			// widnows default
			clr = GetSysColor(COLOR_ACTIVECAPTION); 
		}

		// Do we use quadratic gradient
		// or solid Fill
		if(m_GBStyle & GBS_NOGRADIENT)
		{
			// If you prefer not to have a color gradient
			// use this flag
			PaintRect(pMemDC,
				0,
				0,
				pRC->Width(),
				pRC->Height(),
				clr);
		}
		else
		{

			// Use the quadratic gradient
			// The following gradient:
/////////////////////////////////////////////////
			// Copyright (1997) Microsoft Systems Journal
/////////////////////////////////////////////////
			// Note: future version of this code will replace
			// this gradient with a new one.
			int r = GetRValue(clr);
			int g = GetGValue(clr);
			int b = GetBValue(clr);
			int x = 7 * pRC->right / 8;
			int w = x - pRC->left;					
			int xDelta= max((w / GRADBOXWIDTH),1);
			int h = pRC->Height();

			PaintRect(pMemDC,
				x,
				0,
				pRC->right - x,
				h,
				clr);
	
			int w2  = w*w;

			while (x > xDelta)
			{						
				x -= xDelta;
				int wmx2 = (w-x)*(w-x);
					
				PaintRect(pMemDC,
					x,
					0,
					xDelta,
					h,	
					RGB(r-(r*wmx2)/w2,
						g-(g*wmx2)/w2,
						b-(b*wmx2)/w2));
			}

			// Remainder paint black
			PaintRect(pMemDC,0,0,x,h,BLACK);

/////////////////////////////////////////////////
			// End MSJ code
/////////////////////////////////////////////////
		}
	}

	// Draw icon and caption buttons.
	// Note if you do not want these
	// buttons use the GBS_??? flags
	// to turn on/off. See constructor
	// comments for more details
	CRect rcButn(0,0,cxIcon,cyIcon);
	rcButn.DeflateRect(0,2);
	rcButn.left += 2;

	// Do we want the dock button?
	if(m_GBStyle & GBS_DOCKBUTTON)
	{
		m_rcIcon = rcButn;
		pMemDC->DrawFrameControl(&rcButn,
				DFC_CAPTION,
				DFCS_CAPTIONRESTORE);
	}
	else
		m_rcIcon.SetRect(-1,-1,-1,-1);

	rcButn += CPoint(w-cxIcon-2,0);

	// Do we want the close button?
	if(m_GBStyle & GBS_DOCKCLOSE)
	{
		m_rcClose = rcButn;
		pMemDC->DrawFrameControl(&rcButn,
			DFC_CAPTION,
			DFCS_CAPTIONCLOSE);
	}
	else
		m_rcClose.SetRect(-1,-1,-1,-1);

	CString str;

	// Do we want the application string?
	if((m_GBStyle & GBS_DOCKAPPST))
	{
		str = m_appString;
		if(m_GBStyle & GBS_DOCKTITLE)
		{
			str += _T(" - ");
		}
	}
	else
		str = _T(" ");

	CRect rcText = CRect(pRC->TopLeft(),
			pMemDC->GetTextExtent(str));

	// Use old fonts or create new if user
	// has changed system settings
	if (!m_fontCap.m_hObject)
			CreateFonts();

	CFont* pOldFont = pMemDC->SelectObject(&m_fontTitle);

	if(!(m_GBStyle & GBS_DOCKBUTTON))
	{
		rcText.left += 2;				 
		rcText.right += 2;
	}
	else
	{
		rcText.left += cxIcon+2;				 
		rcText.right += cxIcon+2;
	}

	// Set our text color
	COLORREF clrText;

    if (bActive)
    {
        clrText = GetSysColor(COLOR_CAPTIONTEXT);
        
        if(m_GBStyle & GBS_NOGRADIENT)
        {
            
            // If the current color will not show
            // up in the window let's brighten it
            // until it will
            while(GetLuminosity(clrText) < 90)
            {
                int r = GetRValue(clrText);
                int g = GetGValue(clrText);
                int b = GetBValue(clrText);
                
                r+= 20;
                g+= 20;
                b+= 20;
                clrText = RGB(r,
                    g,
                    b);
            }
        }
    } else
        clrText = GetSysColor(COLOR_INACTIVECAPTIONTEXT);

	pMemDC->SetBkMode(TRANSPARENT);
	pMemDC->SetTextColor(clrText);
	pMemDC->DrawText(str,
		&rcText,
		DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS);

	if(m_GBStyle & GBS_DOCKTITLE)
	{
		pMemDC->SelectObject(&m_fontCap);
		rcText.left += pMemDC->GetTextExtent(str).cx;
		str = GetBarTitle();
		rcText.right += pMemDC->GetTextExtent(str).cx + 4;

		if (rcText.right > rcText.left)
		{
			pMemDC->DrawText(GetBarTitle(),
				&rcText,
				DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS);
		} 
	}

	if(!(m_GBStyle & GBS_NOGRIPBARS))
	{
		// Draw the docking grippers
		CRect rect(5, 6, (5+w) - 30, 9);

		if((m_GBStyle & GBS_DOCKTITLE) ||
			(m_GBStyle & GBS_DOCKAPPST))
		{
			rect.left += rcText.right;
		}
		else
		{
			if(m_GBStyle & GBS_DOCKBUTTON)
			{
				rect.left = m_rcIcon.right + 2;
			}
			else
			{
				rect.left = 2;
			}
			
		}
		if(m_GBStyle & GBS_DOCKCLOSE)
		{
			rect.right = m_rcClose.left - 2;
		}
		else
		{
			rect.right = rcButn.right;
		}
		if (rect.right > rect.left)
		{
			pMemDC->Draw3dRect(rect,
				RGB(255,255,255),
				RGB(128,128,128));

			rect += CPoint(0, 4);
			pMemDC->Draw3dRect(rect,
				RGB(255,255,255),
				RGB(128,128,128));
		}
	}

	// Restore DC
	pMemDC->SelectObject(pOldFont);
	return;
}

DWORD CGripControl::HitTest(CPoint pt)
{
	if(m_rcClose.PtInRect(pt))
		return (DWORD) GHT_CLOSE;
	else if(m_rcIcon.PtInRect(pt))
		return (DWORD) GHT_DOCKBUT;
	else
		return (DWORD) GHT_CAPTION;
}

void CGripControl::PaintRect(CDC* pDC, int x, int y, int w, int h, COLORREF color)
{
	CBrush brush(color);
	CBrush* pOldBrush = pDC->SelectObject(&brush);
	pDC->PatBlt(x, y, w, h, PATCOPY);
	pDC->SelectObject(pOldBrush);
}

void CGripControl::UpdateBitmap(BOOL bActive, CDC * pMemDC, CDC * pWinDC)
{

	// Get our Active or inactive bmp
	CBitmap& bmp = m_bmpCap[bActive != 0];

	// Get our draw region
	CRect rcCap;
	GetCaptionRect(&rcCap);

	// If we have a new Rect redraw
	// bmp otherwise use the old one
	if (rcCap != m_rcCap) {				
		m_bmpCap[0].DeleteObject();
		m_bmpCap[1].DeleteObject();
		m_rcCap = rcCap;
	}

	// Make sure there is a valid bmp
	if (bmp.m_hObject)
	{
		pMemDC->SelectObject(&bmp);
		return;
	}

	// Erase old bmp
	bmp.DeleteObject();

	// Create new bmp
	bmp.CreateCompatibleBitmap(pWinDC,
		m_rcCap.Width(),
		m_rcCap.Height());
	pMemDC->SelectObject(&bmp);

	DrawOnBitmap(bActive, pMemDC, &m_rcCap);
	return;
}

BOOL CGripControl::OnEraseBkgnd(CDC* pDC)
{
	CRect rect;
	
	m_pControlBar->GetCaptionRect(&rect);
	MoveWindow(rect, TRUE);
	return TRUE;
}

void CGripControl::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	DWORD hitTest = HitTest(point);
	
	switch(hitTest)
	{
	case GHT_CAPTION:
	{
		m_pControlBar->ToggleDocking();
	}
	default:
	break;
	}
}

void CGripControl::OnLButtonDown(UINT nFlags, CPoint point) 
{

	// Make sure if parent is app
	// when we click on ControlBar
	CWnd* Wnd = GetActiveWindow();
	CWnd* frm = AfxGetMainWnd();

	if(Wnd != frm)
		frm->SetActiveWindow();

	DWORD hitTest = HitTest(point);

	switch(hitTest)
	{
	case GHT_CAPTION:
	{
		CPoint pt = point;

		ClientToScreen(&point);
		m_pControlBar->StartDrag(point);
		return;
	}
	break;
	case GHT_CLOSE:
	{
		CClientDC dc(this);

		DrawFrameControl(dc.m_hDC,
			m_rcClose,
			DFC_CAPTION,
			DFCS_CAPTIONCLOSE | DFCS_PUSHED);
	}
	break;
	case GHT_DOCKBUT:
	{
		CClientDC dc(this);

		DrawFrameControl(dc.m_hDC,
			m_rcIcon,
			DFC_CAPTION,
			DFCS_CAPTIONRESTORE | DFCS_PUSHED);
	}
	break;
	default:
	break;
	}
	SetCapture();
}

void CGripControl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if(this != GetCapture())
		return;

	DWORD hitTest = HitTest(point);
	
	switch(hitTest)
	{
	case GHT_CAPTION:
	{
	}
	break;
	case GHT_CLOSE:
	{
		CClientDC dc(this);

		DrawFrameControl(dc.m_hDC,
			m_rcClose,
			DFC_CAPTION,
			DFCS_CAPTIONCLOSE);
		ReleaseCapture();
		m_pControlBar->SendMessage(WM_CLOSE, 0,0);
	}
	break;
	case GHT_DOCKBUT:
	{
		CClientDC dc(this);

		DrawFrameControl(dc.m_hDC,
			m_rcIcon,
			DFC_CAPTION,
			DFCS_CAPTIONRESTORE);
		ReleaseCapture();
		m_pControlBar->ToggleDocking();
		return;
	}
	default:
	break;
	}
	ReleaseCapture();
}

void CGripControl::OnMouseMove(UINT nFlags, CPoint point) 
{
	if(this != GetCapture())
		return;

	DWORD hitTest = HitTest(point);
	if(hitTest == m_prevHitTest)
		return;

	m_prevHitTest = hitTest;

	CClientDC dc(this);

	switch(hitTest)
	{
	case GHT_CAPTION:
	{
		DrawFrameControl(dc.m_hDC,
			m_rcClose,
			DFC_CAPTION,
			DFCS_CAPTIONCLOSE);
		DrawFrameControl(dc.m_hDC,
			m_rcIcon,
			DFC_CAPTION,
			DFCS_CAPTIONRESTORE);
	}
	break;
	case GHT_CLOSE:
	{
		DrawFrameControl(dc.m_hDC,
			m_rcClose,
			DFC_CAPTION,
			DFCS_CAPTIONCLOSE | DFCS_PUSHED);
	}
	break;
	case GHT_DOCKBUT:
	{
		CClientDC dc(this);

		DrawFrameControl(dc.m_hDC,
			m_rcIcon,
			DFC_CAPTION,
			DFCS_CAPTIONRESTORE | DFCS_PUSHED);
	}
	default:
	break;
	}
}

void CGripControl::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	OnNcDraw(&dc);
}

BOOL CGripControl::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	::SetCursor((HCURSOR) ::LoadCursor(NULL, IDC_ARROW));	
	return TRUE;
}

void CGripControl::OnSettingChange(UINT uFlags, LPCTSTR lpszSection) 
{
	OnSysColorChange();
	return;
}

void CGripControl::OnSysColorChange() 
{
	Abolish();
}


/////////////////////////////////////////////////////////////////// 
// Class CExDocContext 
// 
// Class provides new behaviour for drawing the 
// track frame when floating 
// Rem out the code inside AdjustWindowForFloat() 
// to see original behaviour 
/////////////////////////////////////////////////////////////////// 

// Local defines
// Gain Access to MFC private DATA 
// Could change without warning 
#undef AFX_DATA 
#define AFX_DATA AFX_CORE_DATA 

extern AFX_DATA AUX_DATA afxData; 

// Macros from orginal DockCont.cpp 
#define HORZF(dw) (dw & CBRS_ORIENT_HORZ) 
#define VERTF(dw) (dw & CBRS_ORIENT_VERT) 

// Local functions
// Function from original DockCont.cpp 
static void AdjustRectangle(CRect& rect, CPoint pt) 
{ 
 int nXOffset = (pt.x < rect.left) ? (pt.x - rect.left) : 
     (pt.x > rect.right) ? (pt.x - rect.right) : 0; 
 int nYOffset = (pt.y < rect.top) ? (pt.y - rect.top) : 
     (pt.y > rect.bottom) ? (pt.y - rect.bottom) : 0; 
 rect.OffsetRect(nXOffset, nYOffset); 
} 

////////////////////////////////////////////////////////////////////// 
// Construction/Destruction 
////////////////////////////////////////////////////////////////////// 

CExDockContext::CExDockContext(CControlBar* pBar) : CDockContext(pBar) 
{ 
     // Default constructor passes control object 
     // to base class 
} 

CExDockContext::~CExDockContext() 
{ 
} 

void CExDockContext::StartDrag(CPoint pt) 
{ 
     ASSERT_VALID(m_pBar); 

	 m_bDragging = TRUE; 
     InitLoop(); 

     if (m_pBar->m_dwStyle & CBRS_SIZE_DYNAMIC) 
     { 
          // get true bar size (including borders) 
          CRect rect; 
          m_pBar->GetWindowRect(rect); 

          // This is our added funtionality 
          // This overridable allows you 
          // to adjust the window rect so that 
          // you can hide controls like a caption 
          // bar from view 
          AdjustWindowForFloat(rect); 

          m_ptLast = pt; 
          CSize sizeHorz = m_pBar->CalcDynamicLayout(0, LM_HORZ | LM_HORZDOCK); 
          CSize sizeVert = m_pBar->CalcDynamicLayout(0, LM_VERTDOCK); 
          CSize sizeFloat = m_pBar->CalcDynamicLayout(0, LM_HORZ | LM_MRUWIDTH); 

          m_rectDragHorz = CRect(rect.TopLeft(), sizeHorz); 
          m_rectDragVert = CRect(rect.TopLeft(), sizeVert); 

          // calculate frame dragging rectangle 
          m_rectFrameDragHorz = CRect(rect.TopLeft(), sizeFloat); 
          m_rectFrameDragVert = CRect(rect.TopLeft(), sizeFloat); 

#ifdef _MAC 
          CMiniFrameWnd::CalcBorders(&m_rectFrameDragHorz, 
               WS_THICKFRAME | WS_CAPTION, WS_EX_FORCESIZEBOX); 
          CMiniFrameWnd::CalcBorders(&m_rectFrameDragVert, 
               WS_THICKFRAME | WS_CAPTION, WS_EX_FORCESIZEBOX); 
#else 
          CMiniFrameWnd::CalcBorders(&m_rectFrameDragHorz); 
          CMiniFrameWnd::CalcBorders(&m_rectFrameDragVert); 
#endif 
          m_rectFrameDragHorz.InflateRect(-afxData.cxBorder2, -afxData.cyBorder2); 
          m_rectFrameDragVert.InflateRect(-afxData.cxBorder2, -afxData.cyBorder2); 
     } 
     else if (m_pBar->m_dwStyle & CBRS_SIZE_FIXED) 
     { 
          // get true bar size (including borders) 
          CRect rect; 
          m_pBar->GetWindowRect(rect); 

          // This is our added funtionality 
          // This overridable allows you 
          // to adjust the window rect so that 
          // you can hide controls like a caption 
          // bar from view 
          AdjustWindowForFloat(rect); 

          m_ptLast = pt; 
          CSize sizeHorz = m_pBar->CalcDynamicLayout(-1, LM_HORZ | LM_HORZDOCK); 
          CSize sizeVert = m_pBar->CalcDynamicLayout(-1, LM_VERTDOCK); 

          // calculate frame dragging rectangle 
          m_rectFrameDragHorz = m_rectDragHorz = CRect(rect.TopLeft(), sizeHorz); 
          m_rectFrameDragVert = m_rectDragVert = CRect(rect.TopLeft(), sizeVert); 

          CMiniFrameWnd::CalcBorders(&m_rectFrameDragHorz); 
          CMiniFrameWnd::CalcBorders(&m_rectFrameDragVert); 
          m_rectFrameDragHorz.InflateRect(-afxData.cxBorder2, -afxData.cyBorder2); 
          m_rectFrameDragVert.InflateRect(-afxData.cxBorder2, -afxData.cyBorder2); 
     } 
     else 
     { 
          // get true bar size (including borders) 
          CRect rect; 
          m_pBar->GetWindowRect(rect); 

          // This is our added funtionality 
          // This overridable allows you 
          // to adjust the window rect so that 
          // you can hide controls like a caption 
          // bar from view 
          AdjustWindowForFloat(rect); 

          m_ptLast = pt; 
          BOOL bHorz = HORZF(m_dwStyle); 
          DWORD dwMode = !bHorz ? (LM_HORZ | LM_HORZDOCK) : LM_VERTDOCK; 
          CSize size = m_pBar->CalcDynamicLayout(-1, dwMode); 

          // calculate inverted dragging rect 
          if (bHorz) 
          { 
               m_rectDragHorz = rect; 
               m_rectDragVert = CRect(CPoint(pt.x - rect.Height()/2, rect.top), size); 
          } 
          else // vertical orientation 
          { 
               m_rectDragVert = rect; 
               m_rectDragHorz = CRect(CPoint(rect.left, pt.y - rect.Width()/2), size); 
          } 

          // calculate frame dragging rectangle 
          m_rectFrameDragHorz = m_rectDragHorz; 
          m_rectFrameDragVert = m_rectDragVert; 

          CMiniFrameWnd::CalcBorders(&m_rectFrameDragHorz); 
          CMiniFrameWnd::CalcBorders(&m_rectFrameDragVert); 
          m_rectFrameDragHorz.InflateRect(-afxData.cxBorder2, -afxData.cyBorder2); 
          m_rectFrameDragVert.InflateRect(-afxData.cxBorder2, -afxData.cyBorder2); 
     } 

     // adjust rectangles so that point is inside 
     AdjustRectangle(m_rectDragHorz, pt); 
     AdjustRectangle(m_rectDragVert, pt); 
     AdjustRectangle(m_rectFrameDragHorz, pt); 
     AdjustRectangle(m_rectFrameDragVert, pt); 

     // initialize tracking state and enter tracking loop 
     m_dwOverDockStyle = CanDock(); 
     Move(pt);   // call it here to handle special keys 

	 // Here we call our new function Tracking
     Tracking(); 
} 
  

void CExDockContext::AdjustWindowForFloat(CRect& rect) 
{ 

     // Overridable to adjust floating frame 
     // size for added controls you do not 
     // want to see in the floating state 
     // Default behavior is to move window 
     // up enough to hide the caption bar 
     if(m_pBar->IsFloating()) 
           rect.top += (GetSystemMetrics(SM_CYCAPTION) 
               + GetSystemMetrics(SM_CYFRAME)); 
} 

BOOL CExDockContext::Tracking()
{

	// don't handle if capture already set
	if (::GetCapture() != NULL)
		return FALSE;

	// set capture to the window which received this message
	m_pBar->SetCapture();
	ASSERT(m_pBar == CWnd::GetCapture());

#ifndef _MAC
	// get messages until capture lost or cancelled/accepted
	while (CWnd::GetCapture() == m_pBar)
	{
		MSG msg;
		if (!::GetMessage(&msg, NULL, 0, 0))
		{
			AfxPostQuitMessage(msg.wParam);
			break;
		}

		switch (msg.message)
		{
		case WM_NCLBUTTONUP:
			m_pBar->SendMessage(WM_NCLBUTTONUP,
				msg.wParam,
				msg.lParam);
			return TRUE;
		case WM_LBUTTONUP:
			if (m_bDragging)
				EndDrag();
			else
				EndResize();
			return TRUE;
		case WM_MOUSEMOVE:
			if (m_bDragging)
				Move(msg.pt);
			else
				Stretch(msg.pt);
			break;
		case WM_KEYUP:
			if (m_bDragging)
				OnKey((int)msg.wParam, FALSE);
			break;
		case WM_KEYDOWN:
			if (m_bDragging)
				OnKey((int)msg.wParam, TRUE);
			if (msg.wParam == VK_ESCAPE)
			{
				CancelLoop();
				return FALSE;
			}
			break;
		case WM_RBUTTONDOWN:
			CancelLoop();
			return FALSE;

		// just dispatch rest of the messages
		default:
			DispatchMessage(&msg);
			break;
		}
	}
#else
	Point   ptCur = {0};

	// get messages until capture lost or cancelled/accepted
	while (CWnd::GetCapture() == m_pBar)
	{
		EventRecord     er;

		if (OSEventAvail(everyEvent, &er))
		{
			GetNextEvent(everyEvent, &er);
			switch (er.what)
			{
			case mouseUp:
				if (m_bDragging)
					EndDrag();
				else
					EndResize();
				return TRUE;

			case keyDown:
			case keyUp:
			case autoKey:
			case app2Evt:
			{
				MSG     msg;

				if (WrapEvent(&er, &msg, PM_REMOVE))
				{
					if (m_bDragging)
						OnKey((int)msg.wParam, msg.message == WM_KEYDOWN);
					if (msg.message == WM_KEYUP && msg.wParam == VK_ESCAPE)
					{
						CancelLoop();
						return FALSE;
					}
				}
				break;
			}

			default:
				break;
			}
		}
		else
		{
			if (!EqualPt(er.where, ptCur))
			{
				POINT pt = {er.where.h, er.where.v};
				if (m_bDragging)
					Move(pt);
				else
					Stretch(pt);
			}
		}
	}
#endif
	CancelLoop();
	return FALSE;
}

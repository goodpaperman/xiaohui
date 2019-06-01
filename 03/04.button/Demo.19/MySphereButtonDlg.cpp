// MySphereButtonDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MySphereButton.h"
#include "MySphereButtonDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMySphereButtonDlg dialog

CMySphereButtonDlg::CMySphereButtonDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMySphereButtonDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMySphereButtonDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMySphereButtonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMySphereButtonDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMySphereButtonDlg, CDialog)
	//{{AFX_MSG_MAP(CMySphereButtonDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(MY_BTN1, OnButton)
	ON_BN_CLICKED(MY_BTN2, OnButton)
	ON_BN_CLICKED(MY_BTN3, OnButton)
	ON_BN_CLICKED(MY_BTN4, OnButton)
	ON_BN_CLICKED(MY_BTN5, OnButton)
	ON_BN_CLICKED(MY_BTN6, OnButton)
	ON_BN_CLICKED(MY_BTN7, OnButton)
	ON_BN_CLICKED(MY_BTN8, OnButton)
	ON_BN_CLICKED(MY_BTN9, OnButton)
	ON_BN_CLICKED(MY_BTN10, OnButton)
	ON_BN_CLICKED(MY_BTN11, OnButton)
	ON_BN_CLICKED(MY_BTN12, OnButton)
	ON_BN_CLICKED(MY_BTN13, OnButton)
	ON_BN_CLICKED(MY_BTN14, OnButton)
	ON_BN_CLICKED(MY_BTN15, OnButton)
	ON_BN_CLICKED(MY_BTN16, OnButton)
	ON_BN_CLICKED(MY_BTN17, OnButton)
	ON_BN_CLICKED(MY_BTN18, OnButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMySphereButtonDlg message handlers

BOOL CMySphereButtonDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// create shapes for button
	// make sure that region is in button client coordinates

	HRGN r; 

	// RECTANGULAR BUTTONS
	r = CreateRectRgn(0, 0, 63, 31);
	m_Btn1.Create("Btn 1", WS_CHILD | WS_VISIBLE, CPoint(15, 15), r, this, MY_BTN1, RGB(255, 255, 0));
	DeleteObject(r);

	// ELLIPTIC BUTTON
	r = CreateEllipticRgn(0, 0, 63, 31);
	m_Btn2.Create("Btn 2", WS_CHILD | WS_VISIBLE, CPoint(95, 15), r, this, MY_BTN2, 2, GetSysColor(COLOR_BTNFACE), RGB(0, 255, 0), RGB(0, 255, 0), GetSysColor(COLOR_BTNFACE)); 
	DeleteObject(r);

	// HELF_ELLIPSE: create left and right buttons splitting ellipse in half
	HRGN rgnR = CreateRectRgn(0, 0, 127, 31);
	HRGN rgnE = CreateEllipticRgn(0, 0, 127, 31);
	OffsetRgn(rgnR, 63, 0);
	CombineRgn(rgnE, rgnE, rgnR, RGN_DIFF);
	m_Btn3.Create("  Btn 3", WS_CHILD | WS_VISIBLE, CPoint(175, 15), rgnE, this, MY_BTN3, 2, GetSysColor(COLOR_BTNFACE), RGB(156, 175, 194), RGB(237, 175, 71), GetSysColor(COLOR_BTNFACE)); 

	DeleteObject(rgnE);
	DeleteObject(rgnR);

	rgnR = CreateRectRgn(0, 0, 127, 31);
	rgnE = CreateEllipticRgn(0, 0, 127, 31);
	OffsetRgn(rgnR, -63, 0);
	CombineRgn(rgnE, rgnE, rgnR, RGN_DIFF);
	OffsetRgn(rgnE, -64, 0);
	m_Btn4.Create("Btn 4  ", WS_CHILD | WS_VISIBLE | WS_DISABLED, CPoint(175 + 64, 15), rgnE, this, MY_BTN4, 2, GetSysColor(COLOR_BTNFACE), RGB(156, 175, 194), RGB(237, 175, 71), GetSysColor(COLOR_BTNFACE)); 

	DeleteObject(rgnE);
	DeleteObject(rgnR);

	// BUTTONS from text regions
	HDC hDC = CreateCompatibleDC(GetDC() -> GetSafeHdc());
	HRGN c;
	LOGFONT lf;
	GetFont() -> GetLogFont(&lf);
	lf.lfHeight = -128;
	lf.lfWeight = 1000;
	HFONT hFont = CreateFontIndirect(&lf);
	HFONT hOldFont = (HFONT) SelectObject(hDC, hFont);
	c = CreateRectRgn(0, 0, 0, 0);

	int mode = SetBkMode(hDC, TRANSPARENT);
	BeginPath(hDC);
	TextOut(hDC, 0, 0, "$", 1);
	EndPath(hDC);
	c = PathToRegion(hDC);
	SetBkMode(hDC, mode);

	m_Btn5.Create("", WS_CHILD | WS_VISIBLE, CPoint(15, 63), c, this, MY_BTN5, RGB(255, 255, 0)); 

	mode = SetBkMode(hDC, TRANSPARENT);
	BeginPath(hDC);
	TextOut(hDC, 0, 0, "@", 1);
	EndPath(hDC);
	c = PathToRegion(hDC);
	SetBkMode(hDC, mode);
	m_Btn6.Create("", WS_CHILD | WS_VISIBLE, CPoint(15 + 64, 63), c, this, MY_BTN6, RGB(255, 0, 255)); 

	SelectObject(hDC, hOldFont);
	DeleteObject(hFont);
	DeleteObject(c);

	HRGN cr; 

	BeginPath(hDC);
	MoveToEx(hDC, 0, 0, NULL);
	LineTo(hDC, 64, 0);
	LineTo(hDC, 64, 16);
	LineTo(hDC, 48, 32);
	LineTo(hDC, 0, 32);
	LineTo(hDC, 0, 0);
	EndPath(hDC);
	cr = CreateRectRgn(0, 0, 63, 63);
	cr = PathToRegion(hDC);
	m_Btn7.Create("Save  ", WS_CHILD | WS_VISIBLE, CPoint(15 + 64 + 128, 63), cr, this, MY_BTN7, 1, RGB(254, 247, 211), RGB(211, 247, 254), RGB(211, 247, 254), GetSysColor(COLOR_BTNFACE)); 

	BeginPath(hDC);
	MoveToEx(hDC, 64, 16, NULL);
	LineTo(hDC, 64, 32);
	LineTo(hDC, 48, 32);
	LineTo(hDC, 64, 16);
	EndPath(hDC);
	cr = PathToRegion(hDC);
	m_Btn8.Create("", WS_CHILD | WS_VISIBLE, CPoint(15 + 64 + 128 + 48 + 1, 63 + 16 + 1), cr, this, MY_BTN8, 1, RGB(247, 211, 254), RGB(211, 247, 254), RGB(211, 247, 254), GetSysColor(COLOR_BTNFACE)); 

	
	DeleteObject(cr);


	// SIMPLE POLYLINE REGION button
	HRGN r1;
	HRGN r2;
	BeginPath(hDC);
	MoveToEx(hDC, 0, 32, NULL);
	LineTo(hDC, 48, 32);
	LineTo(hDC, 48, 16);
	LineTo(hDC, 96, 48);
	LineTo(hDC, 48, 80);
	LineTo(hDC, 48, 64);
	LineTo(hDC, 0, 64);
	LineTo(hDC, 0, 32);
	EndPath(hDC);
	cr = CreateRectRgn(0, 0, 63, 63);
	cr = PathToRegion(hDC);
	m_Btn9.Create("Btn 9", WS_CHILD | WS_VISIBLE, CPoint(32 + 64 + 96, 63 + 16 + 128), cr, this, MY_BTN9, 2, RGB(250, 207, 194), RGB(255, 0, 0), RGB(255, 0, 0), GetSysColor(COLOR_BTNFACE)); 

	DeleteObject(cr);
	DeleteObject(hDC);

	// COMPLEX region
	hDC = CreateCompatibleDC(GetDC() -> GetSafeHdc());
	BeginPath(hDC);
	MoveToEx(hDC, 31, 15, NULL);
	CPoint p[7];
	p[ 0] = CPoint(5, 0);
	p[ 1] = CPoint(0, 55);
	p[ 2] = CPoint(0, 28);
	p[ 3] = CPoint(31, 64);
	p[ 4] = CPoint(59, 55);
	p[ 5] = CPoint(59, 0);
	p[ 6] = CPoint(31, 15);

	PolyBezier(hDC, &p[0], 7);
	EndPath(hDC);
	cr = CreateRectRgn(0, 0, 63, 63);
	cr = PathToRegion(hDC);
	m_Btn10.Create("Btn 10", WS_CHILD | WS_VISIBLE, CPoint(15, 63 + 16 + 64 + 64), cr, this, MY_BTN10, 2, RGB(151, 244, 219), RGB(211, 247, 254), RGB(211, 247, 254), GetSysColor(COLOR_BTNFACE)); 

	DeleteObject(cr);
	DeleteObject(hDC);

	// STRECHED BUTTON
	c = CreateRectRgn(16, 0, 80, 31);
	r1 = CreateEllipticRgn(0, 0, 32, 32);
	r2 = CreateEllipticRgn(64, 0, 96, 32);
	CombineRgn(c, c, r1, RGN_OR);
	CombineRgn(c, c, r2, RGN_OR);
	m_Btn11.Create("Btn 11", WS_CHILD | WS_VISIBLE, CPoint(15 + 64, 63 + 32 + 64 + 64), c, this, MY_BTN11, 2, GetSysColor(COLOR_BTNFACE), RGB(211, 247, 254), RGB(211, 247, 254), GetSysColor(COLOR_BTNFACE)); 
	DeleteObject(c);
	DeleteObject(r1);
	DeleteObject(r2);

	// MERGED BUTTONS
	c = CreateRectRgn(8, 0, 55, 31);
	r1 = CreateEllipticRgn(48, 8, 15 + 48, 15 + 8);
	CombineRgn(c, c, r1, RGN_OR);
	m_Btn12.Create("File", WS_CHILD | WS_VISIBLE, CPoint(16, 63 + 32 + 64 + 128), c, this, MY_BTN12, 1, RGB(151, 219, 244), RGB(211, 247, 254), RGB(211, 247, 254), GetSysColor(COLOR_BTNFACE)); 
	r1 = CreateEllipticRgn(0, 8, 15, 15 + 8);
	CombineRgn(c, c, r1, RGN_DIFF);
	m_Btn13.Create("Edit", WS_CHILD | WS_VISIBLE, CPoint(16 + 48, 63 + 32 + 64 + 128), c, this, MY_BTN13, 1, RGB(151, 219, 244), RGB(211, 247, 254), RGB(211, 247, 254), GetSysColor(COLOR_BTNFACE));
	m_Btn14.Create("View", WS_CHILD | WS_VISIBLE, CPoint(16 + 48 + 48, 63 + 32 + 64 + 128), c, this, MY_BTN14, 1, RGB(151, 219, 244), RGB(211, 247, 254), RGB(211, 247, 254), GetSysColor(COLOR_BTNFACE));
	m_Btn15.Create("Insert",WS_CHILD |WS_VISIBLE, CPoint(16 + 48 + 48 + 48, 63 + 32 + 64 + 128), c, this, MY_BTN15, 1, RGB(151, 219, 244), RGB(211, 247, 254), RGB(211, 247, 254), GetSysColor(COLOR_BTNFACE));
	m_Btn16.Create("Tools", WS_CHILD |WS_VISIBLE, CPoint(16 + 48 + 48 + 48 + 48, 63 + 32 + 64 + 128), c, this, MY_BTN16, 1, RGB(151, 219, 244), RGB(211, 247, 254), RGB(211, 247, 254), GetSysColor(COLOR_BTNFACE));
	m_Btn17.Create("Help",  WS_CHILD |WS_VISIBLE, CPoint(16 + 48 + 48 + 48 + 48 + 48, 63 + 32 + 64 + 128), c, this, MY_BTN17, 1, RGB(151, 244, 219), RGB(211, 247, 254), RGB(211, 247, 254), GetSysColor(COLOR_BTNFACE));
	c = CreateRectRgn(8, 0, 63, 31);
	r1 = CreateEllipticRgn(0, 8, 15, 15 + 8);
	CombineRgn(c, c, r1, RGN_DIFF);
	m_Btn18.Create("Exit",  WS_CHILD |WS_VISIBLE, CPoint(16 + 48 + 48 + 48 + 48 + 48 + 48, 63 + 32 + 64 + 128), c, this, MY_BTN18, 1, RGB(244, 151, 219), RGB(211, 247, 254), RGB(211, 247, 254), GetSysColor(COLOR_BTNFACE));

	DeleteObject(c);
	DeleteObject(r1);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMySphereButtonDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CMySphereButtonDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMySphereButtonDlg::OnButton() 
{
	MessageBeep(0xFFFFFFFF);
}

// A flat popup menu for controls
// Copyright (c) 1999 Andy Brown <andy@mirage.dabsol.co.uk>
// You may do whatever you like with this file, I just don't care.


#include "stdafx.h"
#include "SampleView.h"
#include "FlatPopupMenu.h"
#include "resource.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CSampleView, CView)


/***************/
/* Message map */
/***************/

BEGIN_MESSAGE_MAP(CSampleView, CView)
	//{{AFX_MSG_MAP(CSampleView)
	ON_WM_CONTEXTMENU()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/***************/
/* Constructor */
/***************/

CSampleView::CSampleView()
{
	m_pFont=NULL;
	m_pBrush=NULL;

	m_crBack=PALETTERGB(192,192,192);
	m_crText=PALETTERGB(0,0,0);

	m_bCheck1=true;
	m_bCheck2=false;
}


/**************/
/* Destructor */
/**************/

CSampleView::~CSampleView()
{
	if(m_pFont)
		delete m_pFont;

	if(m_pBrush)
		delete m_pBrush;
}


/***********/
/* Draw it */
/***********/

void CSampleView::OnDraw(CDC *pDC)
{
	int				 x,y,nDC,width1,width2;
	TEXTMETRIC tm;
	CRect			 rect;

	if(m_pFont==NULL)
	{
		m_pFont=new CFont;
		m_pFont->CreatePointFont(10,"MS Sans Serif");

		GetTextMetrics(*pDC,&tm);
		m_Height=tm.tmHeight;
	}

	if(m_pBrush==NULL)
	{
		m_pBrush=new CBrush;
		m_pBrush->CreateSolidBrush(m_crBack);
	}

	nDC=pDC->SaveDC();

	x=10;
	y=10;

	pDC->SelectObject(m_pFont);
	pDC->SelectObject(m_pBrush);
	pDC->SelectStockObject(BLACK_PEN);
	pDC->SetTextColor(m_crText);
	pDC->SetBkMode(TRANSPARENT);

	m_rcControl.left=10;
	m_rcControl.top=10;
	m_rcControl.right=200;
	m_rcControl.bottom=100;

	pDC->Rectangle(m_rcControl);

	width1=pDC->GetTextExtent("File").cx;
	pDC->Rectangle(x,y,x+width1+9,y+m_Height);
	pDC->TextOut(x+4,y+1,"File");

	x+=width1+8;
	width2=pDC->GetTextExtent("Edit").cx;
	pDC->Rectangle(x,y,x+width2+8,y+m_Height);
	pDC->TextOut(x+4,y+1,"Edit");

	rect.left=10;
	rect.right=200;
	rect.top=10+m_Height+10;
	rect.bottom=100;

	m_rcFile.left=10;
	m_rcFile.top=10;
	m_rcFile.right=10+width1+8;
	m_rcFile.bottom=10+m_Height;

	m_rcEdit.left=m_rcFile.right;
	m_rcEdit.right=m_rcEdit.left+width2+8;
	m_rcEdit.top=10;
	m_rcEdit.bottom=10+m_Height;

	pDC->DrawText("select a menu title or right-click here to test the flat popup menu",rect,DT_CENTER | DT_WORDBREAK);
	pDC->RestoreDC(nDC);
}


/***************************/
/* CSampleView diagnostics */
/***************************/

#ifdef _DEBUG
void CSampleView::AssertValid() const
{
	CView::AssertValid();
}

void CSampleView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif


/******************/
/* WM_CONTEXTMENU */
/******************/

void CSampleView::OnContextMenu(CWnd *pWnd,CPoint point)
{
	ScreenToClient(&point);

	if(m_rcControl.PtInRect(point))
		ControlMenu(point);
}


/******************/
/* Left button up */
/******************/

void CSampleView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if(m_rcFile.PtInRect(point))
		FileMenu();
	else if(m_rcEdit.PtInRect(point))
		EditMenu();
}


/*************/
/* File menu */
/*************/

void CSampleView::FileMenu(void)
{
	CFlatPopupMenu menu;
	CPoint				 p;
	int						 id;
	TCHAR					 szBuffer[100];

// set some of the colors

	menu.SetColor(CFlatPopupMenu::colorBorder,m_crText);
	menu.SetColor(CFlatPopupMenu::colorText,m_crText);
	menu.SetColor(CFlatPopupMenu::colorBackground,m_crBack);

// create it

	menu.Create(AfxGetInstanceHandle(),IDB_FILE);

// add some items

	menu.AppendItem(0,"&New...",1,0);
	menu.AppendItem(0,"&Open...",2,1);
	menu.AppendItem(0,"Close",3);
	menu.AppendItem(CFlatPopupMenu::itemSeparator,NULL,0);
	menu.AppendItem(0,"&Save",4,2);
	menu.AppendItem(0,"Save &As...",5);
	menu.AppendItem(0,"Save A&ll",6,3);
	menu.AppendItem(CFlatPopupMenu::itemSeparator,NULL,0);
	menu.AppendItem(0,"Page Set&up",7);
	menu.AppendItem(0,"&Print...",8,4);

// track it

	p.x=m_rcFile.left;
	p.y=m_rcFile.bottom-1;
	ClientToScreen(&p);

	id=menu.Track(p.x,p.y,NULL,true);

	if(id>0)
	{
		wsprintf(szBuffer,"selected id #%d",id);
		AfxMessageBox(szBuffer);
	}
}


/*************/
/* Edit menu */
/*************/

void CSampleView::EditMenu(void)
{
	CFlatPopupMenu menu;
	CPoint				 p;
	int						 id;
	TCHAR					 szBuffer[100];

// set some of the colors

	menu.SetColor(CFlatPopupMenu::colorBorder,m_crText);
	menu.SetColor(CFlatPopupMenu::colorText,m_crText);
	menu.SetColor(CFlatPopupMenu::colorBackground,m_crBack);

// create it

	menu.Create(AfxGetInstanceHandle(),IDB_EDIT);

// add some items

	menu.AppendItem(0,"&Undo",1,0);
	menu.AppendItem(0,"&Redo",2,1);
	menu.AppendItem(CFlatPopupMenu::itemSeparator,NULL,0);
	menu.AppendItem(0,"Cu&t",3,2);
	menu.AppendItem(0,"&Copy",4,3);
	menu.AppendItem(0,"&Paste",5,4);
	menu.AppendItem(0,"&Delete",6,5);
	menu.AppendItem(CFlatPopupMenu::itemSeparator,NULL,0);
	menu.AppendItem(0,"Select A&ll",7);

// track it

	p.x=m_rcEdit.left;
	p.y=m_rcEdit.bottom-1;
	ClientToScreen(&p);

	id=menu.Track(p.x,p.y,NULL,true);

	if(id>0)
	{
		wsprintf(szBuffer,"selected id #%d",id);
		AfxMessageBox(szBuffer);
	}
}


/****************/
/* control menu */
/****************/

void CSampleView::ControlMenu(CPoint point)
{
	CFlatPopupMenu menu,submenu;
	CPoint				 p;

// set some of the colors

	menu.SetColor(CFlatPopupMenu::colorBorder,m_crText);
	menu.SetColor(CFlatPopupMenu::colorText,m_crText);
	menu.SetColor(CFlatPopupMenu::colorBackground,m_crBack);

	submenu.SetColor(CFlatPopupMenu::colorBorder,m_crText);
	submenu.SetColor(CFlatPopupMenu::colorText,m_crText);
	submenu.SetColor(CFlatPopupMenu::colorBackground,m_crBack);

// create it

	menu.Create(AfxGetInstanceHandle(),IDB_CONTROL);
	submenu.Create(AfxGetInstanceHandle(),IDB_CONTROL);

// add some items

    menu.AppendItem(CFlatPopupMenu::itemBold | CFlatPopupMenu::itemNotSelectable | CFlatPopupMenu::itemGrayed,"A Title",0);
	menu.AppendItem(CFlatPopupMenu::itemSeparator,NULL,0);
	menu.AppendItem(0,"Checkable item &1",1,m_bCheck1 ? 1 : 0);
	menu.AppendItem(0,"Checkable item &2",2,m_bCheck2 ? 1 : 0);
	menu.AppendItem(CFlatPopupMenu::itemSeparator,NULL,0);
	menu.AppendPopup(0,"Colors",submenu);

	submenu.AppendItem(0,"&Background",3);
	submenu.AppendItem(0,"&Text",4);

// track it

	ClientToScreen(&point);

	switch(menu.Track(point.x,point.y,NULL,true))
	{
		case 1:
			m_bCheck1^=true;
			break;

		case 2:
			m_bCheck2^=true;
			break;

		case 3:
			EditColor(m_crBack);
			break;

		case 4:
			EditColor(m_crText);
			break;
	}
}


/****************/
/* Edit a color */
/****************/

void CSampleView::EditColor(COLORREF& cr)
{
	CColorDialog dlg;

	dlg.m_cc.rgbResult=cr;
	if(dlg.DoModal()==IDOK)
	{
		cr=dlg.GetColor();
		
		delete m_pBrush;
		m_pBrush=NULL;

		Invalidate();
	}
}

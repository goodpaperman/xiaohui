// sndView.cpp : implementation of the CSndView class
//

#include "stdafx.h"
#include "snd.h"

#include "sndDoc.h"
#include "sndView.h"

#include "soundin.h"
extern CSoundIn SoundIn;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSndView

IMPLEMENT_DYNCREATE(CSndView, CView)

BEGIN_MESSAGE_MAP(CSndView, CView)
	//{{AFX_MSG_MAP(CSndView)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSndView construction/destruction

CSndView::CSndView()
{
	// TODO: add construction code here

}

CSndView::~CSndView()
{
}

BOOL CSndView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSndView drawing

void CSndView::OnDraw(CDC* pDC)
{
	CSndDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CSndView printing

BOOL CSndView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSndView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSndView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CSndView diagnostics

#ifdef _DEBUG
void CSndView::AssertValid() const
{
	CView::AssertValid();
}

void CSndView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSndDoc* CSndView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSndDoc)));
	return (CSndDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSndView message handlers

void CSndView::OnTimer(UINT nIDEvent) 
{
    
    CRect rcClient;
    GetClientRect(rcClient);
    
    CClientDC dc(this);
    
    CBitmap Bitmap;
    CBitmap* pbmOld = NULL;
    
    CDC dcMem;
    dcMem.CreateCompatibleDC(&dc);
    
    Bitmap.CreateCompatibleBitmap(&dc,rcClient.right,rcClient.bottom);
    //pbmOld = dcMem.SelectObject(&m_bmBall);
    pbmOld = dcMem.SelectObject(&Bitmap);
    
    dcMem.PatBlt(0, 0,rcClient.right, rcClient.bottom, WHITENESS);
    
    dcMem.MoveTo(0,rcClient.bottom/2);
    
    // trace un graph correspondant a une fft (sinx/x)
    //
    int x,y;
    dcMem.MoveTo(0,rcClient.bottom/2);
    
    // display incomming signal
    for  (x =0 ; x < (rcClient.right); x++)  // display Input
    {
        //y 	= rcClient.bottom/2 + 50 - SoundIn.InputBuffer[x]/8 ;
        y = rcClient.bottom/2 - SoundIn.InputBuffer[x]; 
        dcMem.LineTo(x,y);
        //yMoy[x] = (yMoy[x]+y)/2;
    }
    dc.BitBlt(0,0,rcClient.right,rcClient.bottom, &dcMem, 0, 0, SRCCOPY);
    
    
    dcMem.SelectObject(pbmOld);
    dcMem.DeleteDC();
    
    //	CView::OnTimer(nIDEvent);
}


void CSndView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	if (!SetTimer(1, 200 /*start slow*/, NULL))
	{
		MessageBox(_T("Not enough timers available for this window."),
				_T("Sound Test "), MB_ICONEXCLAMATION | MB_OK);

		// signal creation failure...
		return;
	}
	
}

// PrintView.cpp : implementation of the CPrintView class
//

#include "stdafx.h"
#include "Print.h"

#include "PrintDoc.h"
#include "PrintView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrintView

IMPLEMENT_DYNCREATE(CPrintView, CFormView)

BEGIN_MESSAGE_MAP(CPrintView, CFormView)
	//{{AFX_MSG_MAP(CPrintView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrintView construction/destruction

CPrintView::CPrintView()
	: CFormView(CPrintView::IDD)
{	
	m_pMemDC = new CDC ;
	m_pBm = new CBitmap;
	
	//{{AFX_DATA_INIT(CPrintView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CPrintView::~CPrintView()
{
	delete m_pMemDC; //CLEAN UP OUR VARIABLES
	delete	m_pBm;
}

void CPrintView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPrintView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BOOL CPrintView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPrintView printing

BOOL CPrintView::OnPreparePrinting(CPrintInfo* pInfo)
{

	return DoPreparePrinting(pInfo);
}

void CPrintView::OnBeginPrinting(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
	if (m_pMemDC->GetSafeHdc()) m_pMemDC->DeleteDC();
	m_pMemDC->CreateCompatibleDC(pDC);

	CClientDC dc(this);
	CRect rect;
	GetClientRect(rect);
	m_pMemDC->SetMapMode(MM_ANISOTROPIC);
	m_pMemDC->SetWindowExt(dc.GetDeviceCaps(LOGPIXELSX),dc.GetDeviceCaps(LOGPIXELSY));
	m_pMemDC->SetViewportExt(m_pMemDC->GetDeviceCaps(LOGPIXELSX),m_pMemDC->GetDeviceCaps(LOGPIXELSY));

	if (m_pBm->GetSafeHandle()) m_pBm->DeleteObject();
	m_pBm->CreateCompatibleBitmap(&dc,rect.Width(),rect.Height());
	m_pMemDC->SelectObject(m_pBm);
	dc.DPtoLP(rect); //Convert to Logical Coordinates
	m_rect = rect; //Save Logical Coordinates
	m_pMemDC->BitBlt(0,0,rect.Width(),rect.Height(),&dc,0,0,SRCCOPY);
	
	//This will prevent creation of the Memory device context 
	//and our Bitmap object a second time.
}

void CPrintView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CPrintView::OnPrint(CDC* pDC, CPrintInfo*)
{
	// TODO: add code to print the controls
//The Following code scales the image based on printer resolution.
	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetWindowExt(m_pMemDC->GetDeviceCaps(LOGPIXELSX),m_pMemDC->GetDeviceCaps(LOGPIXELSY));
	pDC->SetViewportExt(pDC->GetDeviceCaps(LOGPIXELSX),pDC->GetDeviceCaps(LOGPIXELSY));
	pDC->StretchBlt(0,0,m_rect.Width(),m_rect.Height(),m_pMemDC,0,0,m_rect.Width(),m_rect.Height(),SRCCOPY);

}

/////////////////////////////////////////////////////////////////////////////
// CPrintView diagnostics

#ifdef _DEBUG
void CPrintView::AssertValid() const
{
	CFormView::AssertValid();
}

void CPrintView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CPrintDoc* CPrintView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPrintDoc)));
	return (CPrintDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPrintView message handlers

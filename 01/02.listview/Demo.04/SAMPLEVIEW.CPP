// SampleView.cpp : implementation of the CSampleView class
//

#include "stdafx.h"
#include "Sample.h"
#include "SampleDoc.h"
#include "SampleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define NUM_COLUMNS	2

static _TCHAR* g_szColumnLabel[NUM_COLUMNS]=
{
	"First Name",
	"Last Name"
};

static int g_nColumnWidth[NUM_COLUMNS]=
{
	15,
	20
};

static int g_nColumnFmt[NUM_COLUMNS]=
{
	LVCFMT_LEFT,
	LVCFMT_LEFT
};

#define NUM_ITEMS	2

static _TCHAR* g_szData[NUM_ITEMS][NUM_COLUMNS]=
{
	{ "John","Smith" },
	{ "Betsy","Winslow" }
};

/////////////////////////////////////////////////////////////////////////////
// CSampleView

IMPLEMENT_DYNCREATE(CSampleView, CListEditView)

BEGIN_MESSAGE_MAP(CSampleView, CListEditView)
	//{{AFX_MSG_MAP(CSampleView)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CListEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CListEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CListEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSampleView construction/destruction

CSampleView::CSampleView()
{
}

CSampleView::~CSampleView()
{
}

BOOL CSampleView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CListEditView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSampleView drawing

void CSampleView::OnDraw(CDC* pDC)
{
	CSampleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

void CSampleView::OnInitialUpdate()
{
	CListEditView::OnInitialUpdate();

	GetListCtrl().DeleteAllItems();
	
	while(GetListCtrl().DeleteColumn(0));

	TEXTMETRIC tm;
	CClientDC dc(this);

	CFont* pOldFont=dc.SelectObject(GetFont());
	dc.GetTextMetrics(&tm);
	dc.SelectObject(pOldFont);

	LV_COLUMN lvc;
	lvc.mask=LVCF_FMT|LVCF_WIDTH|LVCF_TEXT|LVCF_SUBITEM;

	int n;
	for(n=0; n<NUM_COLUMNS; n++)
	{
		lvc.iSubItem=n;
		lvc.pszText=g_szColumnLabel[n];
		lvc.cx=tm.tmAveCharWidth*(2+g_nColumnWidth[n]);
		lvc.fmt=g_nColumnFmt[n];
		GetListCtrl().InsertColumn(n,&lvc);
	}

	LV_ITEM lvi;
	ZeroMemory(&lvi,sizeof(LV_ITEM));
	lvi.mask=LVIF_TEXT;

	for(n=0; n<NUM_ITEMS; n++)
	{
		lvi.iItem=n;
		lvi.iSubItem=0;
		(LPCTSTR&)lvi.pszText=g_szData[n][0];
		lvi.cchTextMax=strlen(lvi.pszText);
		GetListCtrl().InsertItem(&lvi);
		
		lvi.iSubItem=1;
		(LPCTSTR&)lvi.pszText=g_szData[n][1];
		lvi.cchTextMax=strlen(lvi.pszText);
		GetListCtrl().SetItem(&lvi);
	}	
}

/////////////////////////////////////////////////////////////////////////////
// CSampleView printing

BOOL CSampleView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSampleView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSampleView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CSampleView diagnostics

#ifdef _DEBUG
void CSampleView::AssertValid() const
{
	CListEditView::AssertValid();
}

void CSampleView::Dump(CDumpContext& dc) const
{
	CListEditView::Dump(dc);
}

CSampleDoc* CSampleView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSampleDoc)));
	return (CSampleDoc*)m_pDocument;
}
#endif //_DEBUG



#include "stdafx.h"
#include "Family.h"

/////////////////////////////////////////////////////////////////////////////
// CPaul

IMPLEMENT_DYNCREATE(CPaul, CView)

CPaul::CPaul()
{
}

CPaul::~CPaul()
{
}


BEGIN_MESSAGE_MAP(CPaul, CView)
	//{{AFX_MSG_MAP(CPaul)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPaul drawing

void CPaul::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
	pDC->TextOut(0,0,"son Paul");
}

/////////////////////////////////////////////////////////////////////////////
// CPaul diagnostics

#ifdef _DEBUG
void CPaul::AssertValid() const
{
	CView::AssertValid();
}

void CPaul::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPaul message handlers
/////////////////////////////////////////////////////////////////////////////
// CJames

IMPLEMENT_DYNCREATE(CJames, CView)

CJames::CJames()
{
}

CJames::~CJames()
{
}


BEGIN_MESSAGE_MAP(CJames, CView)
	//{{AFX_MSG_MAP(CJames)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJames drawing

void CJames::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
	pDC->TextOut(0,0,"son James");
}

/////////////////////////////////////////////////////////////////////////////
// CJames diagnostics

#ifdef _DEBUG
void CJames::AssertValid() const
{
	CView::AssertValid();
}

void CJames::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CJames message handlers
/////////////////////////////////////////////////////////////////////////////
// CBill

IMPLEMENT_DYNCREATE(CBill, CView)

CBill::CBill()
{
}

CBill::~CBill()
{
}


BEGIN_MESSAGE_MAP(CBill, CView)
	//{{AFX_MSG_MAP(CBill)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBill drawing

void CBill::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
	pDC->TextOut(0,0,"son Bill");
}

/////////////////////////////////////////////////////////////////////////////
// CBill diagnostics

#ifdef _DEBUG
void CBill::AssertValid() const
{
	CView::AssertValid();
}

void CBill::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBill message handlers
/////////////////////////////////////////////////////////////////////////////
// CAlex

IMPLEMENT_DYNCREATE(CAlex, CView)

CAlex::CAlex()
{
}

CAlex::~CAlex()
{
}


BEGIN_MESSAGE_MAP(CAlex, CView)
	//{{AFX_MSG_MAP(CAlex)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAlex drawing

void CAlex::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
	pDC->TextOut(0,0,"son Alex");
}

/////////////////////////////////////////////////////////////////////////////
// CAlex diagnostics

#ifdef _DEBUG
void CAlex::AssertValid() const
{
	CView::AssertValid();
}

void CAlex::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAlex message handlers
/////////////////////////////////////////////////////////////////////////////
// CDaddy

IMPLEMENT_DYNCREATE(CDaddy, CView)

CDaddy::CDaddy()
{
}

CDaddy::~CDaddy()
{
}


BEGIN_MESSAGE_MAP(CDaddy, CView)
	//{{AFX_MSG_MAP(CDaddy)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDaddy drawing

void CDaddy::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
	pDC->TextOut(0,0,"Daddy");
}

/////////////////////////////////////////////////////////////////////////////
// CDaddy diagnostics

#ifdef _DEBUG
void CDaddy::AssertValid() const
{
	CView::AssertValid();
}

void CDaddy::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDaddy message handlers

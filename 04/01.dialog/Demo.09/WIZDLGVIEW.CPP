// WizDlgView.cpp : implementation of the CWizDlgView class
//

#include "stdafx.h"
#include "WizDlg.h"

#include "WizDlgDoc.h"
#include "WizDlgView.h"

#include "WizardDlg.h"
#include "Testpage1.h"
#include "Testpage2.h"
#include "Testpage3.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWizDlgView

IMPLEMENT_DYNCREATE(CWizDlgView, CView)

BEGIN_MESSAGE_MAP(CWizDlgView, CView)
	//{{AFX_MSG_MAP(CWizDlgView)
	ON_COMMAND(ID_TEST_WIZARD, OnTestWizard)
	ON_COMMAND(ID_CUSTOM_WIZARD, OnCustomWizard)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWizDlgView construction/destruction

CWizDlgView::CWizDlgView()
{
	// TODO: add construction code here

}

CWizDlgView::~CWizDlgView()
{
}

BOOL CWizDlgView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CWizDlgView drawing

void CWizDlgView::OnDraw(CDC* pDC)
{
	CWizDlgDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CWizDlgView printing

BOOL CWizDlgView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CWizDlgView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CWizDlgView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CWizDlgView diagnostics

#ifdef _DEBUG
void CWizDlgView::AssertValid() const
{
	CView::AssertValid();
}

void CWizDlgView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWizDlgDoc* CWizDlgView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWizDlgDoc)));
	return (CWizDlgDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWizDlgView message handlers

void CWizDlgView::OnTestWizard() 
{
	CWizardDlg dlg;

	dlg.csTitle = "This is a test wizard";

	CTestPage1 page1;
	CTestPage2 page2;
	page2.iTestInt = 10;

	CTestPage3 page3;

	dlg.AddPage("Page 1\tsmall description of step 1", &page1, CTestPage1::IDD);
	dlg.AddPage("Page 2\tsmall description of step 2", &page2, CTestPage2::IDD);
	dlg.AddPage("Page 3\tsmall description of step 3", &page3, CTestPage3::IDD);

	dlg.DoModal();	
}






class CCustomWizardDlg : public CWizardDlg
{
public:
	virtual void SetCurSel(const int idx);
};

void CCustomWizardDlg::SetCurSel(const int idx)
{
	CWizardDlg::SetCurSel(idx);
	if (idx == 2)
	{
		CTestPage2 * p2 = (CTestPage2 *) GetDialog(1);
		CTestPage3 * p3 = (CTestPage3 *) GetDialog(2);
		p3->iTestInt = p2->iTestInt * 2;
		p3->UpdateData(false);
	}
}


void CWizDlgView::OnCustomWizard() 
{
	CCustomWizardDlg dlg;

	dlg.csTitle = "This is a custom test wizard";

	CTestPage1 page1;
	CTestPage2 page2;
	page2.iTestInt = 10;

	CTestPage3 page3;

	dlg.AddPage("Page 1\tsmall description of step 1", &page1, CTestPage1::IDD);
	dlg.AddPage("Page 2\tsmall description of step 2", &page2, CTestPage2::IDD);
	dlg.AddPage("Page 3\tsmall description of step 3", &page3, CTestPage3::IDD);

	dlg.DoModal();	

}

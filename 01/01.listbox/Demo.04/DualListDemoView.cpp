// DualListDemoView.cpp : implementation of the CDualListDemoView class
//

#include "stdafx.h"
#include "DualListDemo.h"

#include "DualListDemoDoc.h"
#include "DualListDemoView.h"
#include "DualListDemoDialog.h"
#include "DualListDemoPropSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDualListDemoView

IMPLEMENT_DYNCREATE(CDualListDemoView, CFormView)

BEGIN_MESSAGE_MAP(CDualListDemoView, CFormView)
	//{{AFX_MSG_MAP(CDualListDemoView)
	ON_COMMAND(ID_DUALLISTTESTS_DUALLISTDIALOG, OnDuallisttestsDuallistdialog)
	ON_COMMAND(ID_DUALLISTTESTS_DUALLISTPROPERTYPAGE, OnDuallisttestsDuallistpropertypage)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDualListDemoView construction/destruction

CDualListDemoView::CDualListDemoView()
	: CFormView(CDualListDemoView::IDD)
{
	//{{AFX_DATA_INIT(CDualListDemoView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CDualListDemoView::~CDualListDemoView()
{
}

void CDualListDemoView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDualListDemoView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BOOL CDualListDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CDualListDemoView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

    // ADDED TO DEFAULT THE LISTS.
    // This code will need to be replaced with your application specific 
    // code that knows what belongs in each list.
    m_DualListManager.AddItemToAvailableList(_T("Red"), 0);
    m_DualListManager.AddItemToAvailableList(_T("Green"), 1);
    m_DualListManager.AddItemToAvailableList(_T("Blue"), 2);
    m_DualListManager.AddItemToChoosenList(_T("Yellow"), 3);
    m_DualListManager.AddItemToChoosenList(_T("Purple"), 4);
    m_DualListManager.AddItemToChoosenList(_T("Orange"), 5);

    // ADDED TO INITIALIZE THE MANAGER CLASS
    m_DualListManager.InitializeControls(this, 
                                         IDC_FV_LIST_AVAILABLE,
                                         IDC_FV_LIST_CHOOSEN, 
                                         IDC_FV_ADD,
                                         IDC_FV_ADD_ALL,
                                         IDC_FV_REMOVE,
                                         IDC_FV_REMOVE_ALL,
                                         IDC_FV_MOVE_UP,
                                         IDC_FV_MOVE_DOWN);
}

/////////////////////////////////////////////////////////////////////////////
// CDualListDemoView printing

BOOL CDualListDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDualListDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDualListDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CDualListDemoView::OnPrint(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

/////////////////////////////////////////////////////////////////////////////
// CDualListDemoView diagnostics

#ifdef _DEBUG
void CDualListDemoView::AssertValid() const
{
	CFormView::AssertValid();
}

void CDualListDemoView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CDualListDemoDoc* CDualListDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDualListDemoDoc)));
	return (CDualListDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDualListDemoView message handlers

void CDualListDemoView::OnDuallisttestsDuallistdialog() 
{
    CDualListDemoDialog dlg;
    dlg.DoModal();
}

void CDualListDemoView::OnDuallisttestsDuallistpropertypage() 
{
    CDualListDemoPropSheet  ps(_T("Dual List Demo"));
    ps.DoModal();
}

BOOL CDualListDemoView::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
    // ADDED TO INTERCEPT MESSAGE THAT THE DUAL LIST MANAGER NEEDS
    m_DualListManager.ProcessCmdMsg(nID, nCode);

    // NOW CALL THE BASE CLASS
    return CFormView::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
#include "Test.h"

#include "TestDoc.h"
#include "TestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestView

IMPLEMENT_DYNCREATE(CTestView, CTreeView)

BEGIN_MESSAGE_MAP(CTestView, CTreeView)
	//{{AFX_MSG_MAP(CTestView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CTreeView::OnFilePrintPreview)
	ON_MESSAGE(WM_DATAAVAILABLE, OnDataAvailable)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestView construction/destruction

CTestView::CTestView()
{
	// TODO: add construction code here

}

CTestView::~CTestView()
{
}

BOOL CTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CTreeView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTestView drawing

void CTestView::OnDraw(CDC* pDC)
{
	CTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

void CTestView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();
	CTreeViewExt<int>::OnInitialUpdate();

	// TODO: You may populate your TreeView with items by directly accessing
	//  its tree control through a call to GetTreeCtrl().
}

/////////////////////////////////////////////////////////////////////////////
// CTestView printing

BOOL CTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CTestView diagnostics

#ifdef _DEBUG
void CTestView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CTestView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CTestDoc* CTestView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestDoc)));
	return (CTestDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTestView message handlers

// THIS function is required for MFC message maps to work correctly. 
//We could just have added entry like this
//	ON_MESSAGE(WM_DATAAVAILABLE, CTreeViewExt::OnDataAvailable).
//, but unfortunately that doesn't work correctly due to problems with 
// multiple inheritance. The "this" pointer passed in this case points to
// CTestView portion of the object and NOT the CTreeViewExt part.
// Any ideas for solving this problem are welcome.

LONG CTestView::OnDataAvailable(WPARAM wParam, LPARAM lParam)
{
	return CTreeViewExt<int>::OnDataAvailable(wParam, lParam);
}

/////////////////////////////////////////////////////////////////////////////
// CTreeViewExt overrides

// provide the list of root level items to be added
void CTestView::GetRootItems(list<TreeData>& List)
{
	TreeData Data;
	Data.m_hHandle = NULL;
	Data.m_Data = 0;
	Data.m_nImage = 0;
	Data.m_strText = "Level 0";
	List.push_back(Data);
}

// itParent points to the parent item. We provide "children" for this item
// in the List reference passed
void CTestView::GetChildItems(list<TreeData>::iterator itParent, list<TreeData>& List)
{
	if(itParent->m_nImage==2) // only two levels of data
		return; 

    //static int nTimes = 0; 
    //if(nTimes++ > 100)
    //    return; 

	switch(itParent->m_nImage)
	{
	case 0:
		{
			CString strText;
			for(int i=0 ; i<4; i++)
			{
				// no need to provide handle value
				TreeData Data;
				Data.m_Data = 1;
				Data.m_nImage = 1;
				strText.Format("Level 1 : Item %d", i);
				Data.m_strText = strText;
				List.push_back(Data);
			}
		}
		break;

	case 1:
		{
			CString strText;
			for(int i=0 ; i<4; i++)
			{
				// no need to provide handle value
				TreeData Data;
				Data.m_Data = 2;
				Data.m_nImage = 2;
				strText.Format("Level 2 : Item %d", i);
				Data.m_strText = strText;
				List.push_back(Data);
			}
		}
		break;
	default:
		break;

	}
}

/////////////////////////////////////////////////////////////////////////////
//

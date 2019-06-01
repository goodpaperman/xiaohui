// ListViewDemoDoc.cpp : implementation of the CListViewDemoDoc class
//

#include "stdafx.h"
#include "ListViewDemo.h"

#include "ListViewDemoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListViewDemoDoc

IMPLEMENT_DYNCREATE(CListViewDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CListViewDemoDoc, CDocument)
	//{{AFX_MSG_MAP(CListViewDemoDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListViewDemoDoc construction/destruction

CListViewDemoDoc::CListViewDemoDoc()
{
}

CListViewDemoDoc::~CListViewDemoDoc()
{
}

BOOL CListViewDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CListViewDemoDoc serialization

void CListViewDemoDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}

/////////////////////////////////////////////////////////////////////////////
// CListViewDemoDoc diagnostics

#ifdef _DEBUG
void CListViewDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CListViewDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CListViewDemoDoc commands

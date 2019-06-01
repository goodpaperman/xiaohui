// CGfxListViewDoc.cpp : implementation of the CCGfxListViewDoc class
//

#include "stdafx.h"
#include "CGfxListView.h"

#include "CGfxListViewDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCGfxListViewDoc

IMPLEMENT_DYNCREATE(CCGfxListViewDoc, CDocument)

BEGIN_MESSAGE_MAP(CCGfxListViewDoc, CDocument)
	//{{AFX_MSG_MAP(CCGfxListViewDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCGfxListViewDoc construction/destruction

CCGfxListViewDoc::CCGfxListViewDoc()
{
	// TODO: add one-time construction code here

}

CCGfxListViewDoc::~CCGfxListViewDoc()
{
}

BOOL CCGfxListViewDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CCGfxListViewDoc serialization

void CCGfxListViewDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CCGfxListViewDoc diagnostics

#ifdef _DEBUG
void CCGfxListViewDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCGfxListViewDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCGfxListViewDoc commands

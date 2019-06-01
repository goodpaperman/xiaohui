// GlobalDoc.cpp : implementation of the CGlobalDoc class
//

#include "stdafx.h"
#include "OutBarDemo.h"

#include "GlobalDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGlobalDoc

IMPLEMENT_DYNCREATE(CGlobalDoc, CDocument)

BEGIN_MESSAGE_MAP(CGlobalDoc, CDocument)
	//{{AFX_MSG_MAP(CGlobalDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGlobalDoc construction/destruction

CGlobalDoc::CGlobalDoc()
{
	// TODO: add one-time construction code here

}

CGlobalDoc::~CGlobalDoc()
{
}

BOOL CGlobalDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CGlobalDoc serialization

void CGlobalDoc::Serialize(CArchive& ar)
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
// CGlobalDoc diagnostics

#ifdef _DEBUG
void CGlobalDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGlobalDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGlobalDoc commands

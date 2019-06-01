// ExampleDIBDoc.cpp : implementation of the CExampleDIBDoc class
//

#include "stdafx.h"
#include "ExampleDIB.h"

#include "ExampleDIBDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExampleDIBDoc

IMPLEMENT_DYNCREATE(CExampleDIBDoc, CDocument)

BEGIN_MESSAGE_MAP(CExampleDIBDoc, CDocument)
	//{{AFX_MSG_MAP(CExampleDIBDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExampleDIBDoc construction/destruction

CExampleDIBDoc::CExampleDIBDoc()
{
	// TODO: add one-time construction code here

}

CExampleDIBDoc::~CExampleDIBDoc()
{
}

BOOL CExampleDIBDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CExampleDIBDoc serialization

void CExampleDIBDoc::Serialize(CArchive& ar)
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
// CExampleDIBDoc diagnostics

#ifdef _DEBUG
void CExampleDIBDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CExampleDIBDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CExampleDIBDoc commands

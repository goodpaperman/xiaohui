// MyFormViewDoc.cpp : implementation of the CMyFormViewDoc class
//

#include "stdafx.h"
#include "MyFormView.h"

#include "MyFormViewDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyFormViewDoc

IMPLEMENT_DYNCREATE(CMyFormViewDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyFormViewDoc, CDocument)
	//{{AFX_MSG_MAP(CMyFormViewDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyFormViewDoc construction/destruction

CMyFormViewDoc::CMyFormViewDoc()
{
	// TODO: add one-time construction code here

}

CMyFormViewDoc::~CMyFormViewDoc()
{
}

BOOL CMyFormViewDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMyFormViewDoc serialization

void CMyFormViewDoc::Serialize(CArchive& ar)
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
// CMyFormViewDoc diagnostics

#ifdef _DEBUG
void CMyFormViewDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyFormViewDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyFormViewDoc commands

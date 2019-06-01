// TestViewDoc.cpp : implementation of the CTestViewDoc class
//

#include "stdafx.h"
#include "TestView.h"

#include "TestViewDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestViewDoc

IMPLEMENT_DYNCREATE(CTestViewDoc, CDocument)

BEGIN_MESSAGE_MAP(CTestViewDoc, CDocument)
	//{{AFX_MSG_MAP(CTestViewDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestViewDoc construction/destruction

CTestViewDoc::CTestViewDoc()
{
	// TODO: add one-time construction code here

}

CTestViewDoc::~CTestViewDoc()
{
}

BOOL CTestViewDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTestViewDoc serialization

void CTestViewDoc::Serialize(CArchive& ar)
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
// CTestViewDoc diagnostics

#ifdef _DEBUG
void CTestViewDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTestViewDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTestViewDoc commands

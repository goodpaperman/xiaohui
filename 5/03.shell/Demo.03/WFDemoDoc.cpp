// WFDemoDoc.cpp : implementation of the CWFDemoDoc class
//

#include "stdafx.h"
#include "WFDemo.h"

#include "WFDemoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWFDemoDoc

IMPLEMENT_DYNCREATE(CWFDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CWFDemoDoc, CDocument)
	//{{AFX_MSG_MAP(CWFDemoDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWFDemoDoc construction/destruction

CWFDemoDoc::CWFDemoDoc()
{
	// TODO: add one-time construction code here

}

CWFDemoDoc::~CWFDemoDoc()
{
}

BOOL CWFDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CWFDemoDoc serialization

void CWFDemoDoc::Serialize(CArchive& ar)
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
// CWFDemoDoc diagnostics

#ifdef _DEBUG
void CWFDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CWFDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWFDemoDoc commands

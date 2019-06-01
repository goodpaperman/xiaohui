// GHCustomDrawDoc.cpp : implementation of the CGHCustomDrawDoc class
//

#include "stdafx.h"
#include "GHCustomDraw.h"

#include "GHCustomDrawDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGHCustomDrawDoc

IMPLEMENT_DYNCREATE(CGHCustomDrawDoc, CDocument)

BEGIN_MESSAGE_MAP(CGHCustomDrawDoc, CDocument)
	//{{AFX_MSG_MAP(CGHCustomDrawDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGHCustomDrawDoc construction/destruction

CGHCustomDrawDoc::CGHCustomDrawDoc()
{
	// TODO: add one-time construction code here

}

CGHCustomDrawDoc::~CGHCustomDrawDoc()
{
}

BOOL CGHCustomDrawDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CGHCustomDrawDoc serialization

void CGHCustomDrawDoc::Serialize(CArchive& ar)
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
// CGHCustomDrawDoc diagnostics

#ifdef _DEBUG
void CGHCustomDrawDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGHCustomDrawDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGHCustomDrawDoc commands

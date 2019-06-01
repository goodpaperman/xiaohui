// TLViewDoc.cpp : implementation of the CTLViewDoc class
//

#include "stdafx.h"
#include "TLView.h"

#include "TLViewDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTLViewDoc

IMPLEMENT_DYNCREATE(CTLViewDoc, CDocument)

BEGIN_MESSAGE_MAP(CTLViewDoc, CDocument)
	//{{AFX_MSG_MAP(CTLViewDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTLViewDoc construction/destruction

CTLViewDoc::CTLViewDoc()
{
	// TODO: add one-time construction code here

}

CTLViewDoc::~CTLViewDoc()
{
}

BOOL CTLViewDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTLViewDoc serialization

void CTLViewDoc::Serialize(CArchive& ar)
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
// CTLViewDoc diagnostics

#ifdef _DEBUG
void CTLViewDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTLViewDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTLViewDoc commands

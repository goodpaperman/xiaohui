// SuperGrid1Doc.cpp : implementation of the CSuperGrid1Doc class
//

#include "stdafx.h"
#include "GfxList.h"

#include "SuperGrid1Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSuperGrid1Doc

IMPLEMENT_DYNCREATE(CSuperGrid1Doc, CDocument)

BEGIN_MESSAGE_MAP(CSuperGrid1Doc, CDocument)
	//{{AFX_MSG_MAP(CSuperGrid1Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSuperGrid1Doc construction/destruction

CSuperGrid1Doc::CSuperGrid1Doc()
{
	// TODO: add one-time construction code here

}

CSuperGrid1Doc::~CSuperGrid1Doc()
{
}

BOOL CSuperGrid1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSuperGrid1Doc serialization

void CSuperGrid1Doc::Serialize(CArchive& ar)
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
// CSuperGrid1Doc diagnostics

#ifdef _DEBUG
void CSuperGrid1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSuperGrid1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSuperGrid1Doc commands

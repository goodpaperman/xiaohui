// DemoTBarDDoc.cpp : implementation of the CDemoTBarDDoc class
//

#include "stdafx.h"
#include "DemoTBarD.h"

#include "DemoTBarDDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDemoTBarDDoc

IMPLEMENT_DYNCREATE(CDemoTBarDDoc, CDocument)

BEGIN_MESSAGE_MAP(CDemoTBarDDoc, CDocument)
	//{{AFX_MSG_MAP(CDemoTBarDDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemoTBarDDoc construction/destruction

CDemoTBarDDoc::CDemoTBarDDoc()
{
	// TODO: add one-time construction code here

}

CDemoTBarDDoc::~CDemoTBarDDoc()
{
}

BOOL CDemoTBarDDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDemoTBarDDoc serialization

void CDemoTBarDDoc::Serialize(CArchive& ar)
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
// CDemoTBarDDoc diagnostics

#ifdef _DEBUG
void CDemoTBarDDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDemoTBarDDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDemoTBarDDoc commands

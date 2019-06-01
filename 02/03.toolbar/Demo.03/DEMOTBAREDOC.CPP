// DemoTBarEDoc.cpp : implementation of the CDemoTBarEDoc class
//

#include "stdafx.h"
#include "DemoTBarE.h"

#include "DemoTBarEDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDemoTBarEDoc

IMPLEMENT_DYNCREATE(CDemoTBarEDoc, CDocument)

BEGIN_MESSAGE_MAP(CDemoTBarEDoc, CDocument)
	//{{AFX_MSG_MAP(CDemoTBarEDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemoTBarEDoc construction/destruction

CDemoTBarEDoc::CDemoTBarEDoc()
{
	// TODO: add one-time construction code here

}

CDemoTBarEDoc::~CDemoTBarEDoc()
{
}

BOOL CDemoTBarEDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDemoTBarEDoc serialization

void CDemoTBarEDoc::Serialize(CArchive& ar)
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
// CDemoTBarEDoc diagnostics

#ifdef _DEBUG
void CDemoTBarEDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDemoTBarEDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDemoTBarEDoc commands

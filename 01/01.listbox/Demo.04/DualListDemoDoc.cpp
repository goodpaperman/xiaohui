// DualListDemoDoc.cpp : implementation of the CDualListDemoDoc class
//
// MFC generated code: no changes necessary

#include "stdafx.h"
#include "DualListDemo.h"

#include "DualListDemoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDualListDemoDoc

IMPLEMENT_DYNCREATE(CDualListDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CDualListDemoDoc, CDocument)
	//{{AFX_MSG_MAP(CDualListDemoDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDualListDemoDoc construction/destruction

CDualListDemoDoc::CDualListDemoDoc()
{
	// TODO: add one-time construction code here

}

CDualListDemoDoc::~CDualListDemoDoc()
{
}

BOOL CDualListDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDualListDemoDoc serialization

void CDualListDemoDoc::Serialize(CArchive& ar)
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
// CDualListDemoDoc diagnostics

#ifdef _DEBUG
void CDualListDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDualListDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDualListDemoDoc commands

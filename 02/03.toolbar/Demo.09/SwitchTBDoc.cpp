// SwitchTBDoc.cpp : implementation of the CSwitchTBDoc class
//

#include "stdafx.h"
#include "SwitchTB.h"

#include "SwitchTBDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSwitchTBDoc

IMPLEMENT_DYNCREATE(CSwitchTBDoc, CDocument)

BEGIN_MESSAGE_MAP(CSwitchTBDoc, CDocument)
	//{{AFX_MSG_MAP(CSwitchTBDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSwitchTBDoc construction/destruction

CSwitchTBDoc::CSwitchTBDoc()
{
	// TODO: add one-time construction code here

}

CSwitchTBDoc::~CSwitchTBDoc()
{
}

BOOL CSwitchTBDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSwitchTBDoc serialization

void CSwitchTBDoc::Serialize(CArchive& ar)
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
// CSwitchTBDoc diagnostics

#ifdef _DEBUG
void CSwitchTBDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSwitchTBDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSwitchTBDoc commands

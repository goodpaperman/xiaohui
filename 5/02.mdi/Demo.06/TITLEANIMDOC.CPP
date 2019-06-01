// titleAnimDoc.cpp : implementation of the CTitleAnimDoc class
//

#include "stdafx.h"
#include "titleAnim.h"

#include "titleAnimDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTitleAnimDoc

IMPLEMENT_DYNCREATE(CTitleAnimDoc, CDocument)

BEGIN_MESSAGE_MAP(CTitleAnimDoc, CDocument)
	//{{AFX_MSG_MAP(CTitleAnimDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTitleAnimDoc construction/destruction

CTitleAnimDoc::CTitleAnimDoc()
{
	// TODO: add one-time construction code here

}

CTitleAnimDoc::~CTitleAnimDoc()
{
}

BOOL CTitleAnimDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CTitleAnimDoc serialization

void CTitleAnimDoc::Serialize(CArchive& ar)
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
// CTitleAnimDoc diagnostics

#ifdef _DEBUG
void CTitleAnimDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTitleAnimDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTitleAnimDoc commands

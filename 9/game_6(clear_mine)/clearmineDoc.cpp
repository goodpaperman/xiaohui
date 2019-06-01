// clearmineDoc.cpp : implementation of the CClearmineDoc class
//

#include "stdafx.h"
#include "clearmine.h"

#include "clearmineDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClearmineDoc

IMPLEMENT_DYNCREATE(CClearmineDoc, CDocument)

BEGIN_MESSAGE_MAP(CClearmineDoc, CDocument)
	//{{AFX_MSG_MAP(CClearmineDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClearmineDoc construction/destruction

CClearmineDoc::CClearmineDoc()
{
	// TODO: add one-time construction code here

}

CClearmineDoc::~CClearmineDoc()
{
}

BOOL CClearmineDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CClearmineDoc serialization

void CClearmineDoc::Serialize(CArchive& ar)
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
// CClearmineDoc diagnostics

#ifdef _DEBUG
void CClearmineDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CClearmineDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CClearmineDoc commands

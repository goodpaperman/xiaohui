// DocumentBarDoc.cpp : implementation of the CDocumentBarDoc class
//

#include "stdafx.h"
#include "DocumentBar.h"

#include "DocumentBarDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDocumentBarDoc

IMPLEMENT_DYNCREATE(CDocumentBarDoc, CDocument)

BEGIN_MESSAGE_MAP(CDocumentBarDoc, CDocument)
	//{{AFX_MSG_MAP(CDocumentBarDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDocumentBarDoc construction/destruction

CDocumentBarDoc::CDocumentBarDoc()
{
	// TODO: add one-time construction code here

}

CDocumentBarDoc::~CDocumentBarDoc()
{
}

BOOL CDocumentBarDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDocumentBarDoc serialization

void CDocumentBarDoc::Serialize(CArchive& ar)
{
	// CEditView contains an edit control which handles all serialization
	((CEditView*)m_viewList.GetHead())->SerializeRaw(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CDocumentBarDoc diagnostics

#ifdef _DEBUG
void CDocumentBarDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDocumentBarDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDocumentBarDoc commands

// ToolBarExampleDoc.cpp : implementation of the CToolBarExampleDoc class
//

#include "stdafx.h"
#include "ToolBarExample.h"

#include "ToolBarExampleDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CToolBarExampleDoc

IMPLEMENT_DYNCREATE(CToolBarExampleDoc, CDocument)

BEGIN_MESSAGE_MAP(CToolBarExampleDoc, CDocument)
	//{{AFX_MSG_MAP(CToolBarExampleDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolBarExampleDoc construction/destruction

CToolBarExampleDoc::CToolBarExampleDoc()
{
	// TODO: add one-time construction code here

}

CToolBarExampleDoc::~CToolBarExampleDoc()
{
}

BOOL CToolBarExampleDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CToolBarExampleDoc serialization

void CToolBarExampleDoc::Serialize(CArchive& ar)
{
	// CEditView contains an edit control which handles all serialization
	((CEditView*)m_viewList.GetHead())->SerializeRaw(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CToolBarExampleDoc diagnostics

#ifdef _DEBUG
void CToolBarExampleDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CToolBarExampleDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CToolBarExampleDoc commands

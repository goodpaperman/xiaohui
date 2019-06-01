// TabProjDoc.cpp : implementation of the CTabProjDoc class
//

#include "stdafx.h"
#include "TabProj.h"

#include "TabProjDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabProjDoc

IMPLEMENT_DYNCREATE(CTabProjDoc, CDocument)

BEGIN_MESSAGE_MAP(CTabProjDoc, CDocument)
	//{{AFX_MSG_MAP(CTabProjDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabProjDoc construction/destruction

CTabProjDoc::CTabProjDoc()
{
	// TODO: add one-time construction code here

}

CTabProjDoc::~CTabProjDoc()
{
}

BOOL CTabProjDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTabProjDoc serialization

void CTabProjDoc::Serialize(CArchive& ar)
{
	// CEditView contains an edit control which handles all serialization
	((CEditView*)m_viewList.GetHead())->SerializeRaw(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CTabProjDoc diagnostics

#ifdef _DEBUG
void CTabProjDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTabProjDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTabProjDoc commands

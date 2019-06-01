// CustomMoreWindowsDoc.cpp : implementation of the CCustomMoreWindowsDoc class
//

#include "stdafx.h"
#include "CustomMoreWindows.h"

#include "CustomMoreWindowsDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustomMoreWindowsDoc

IMPLEMENT_DYNCREATE(CCustomMoreWindowsDoc, CDocument)

BEGIN_MESSAGE_MAP(CCustomMoreWindowsDoc, CDocument)
	//{{AFX_MSG_MAP(CCustomMoreWindowsDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustomMoreWindowsDoc construction/destruction

CCustomMoreWindowsDoc::CCustomMoreWindowsDoc()
{
	// TODO: add one-time construction code here

}

CCustomMoreWindowsDoc::~CCustomMoreWindowsDoc()
{
}

BOOL CCustomMoreWindowsDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CCustomMoreWindowsDoc serialization

void CCustomMoreWindowsDoc::Serialize(CArchive& ar)
{
	// CEditView contains an edit control which handles all serialization
	((CEditView*)m_viewList.GetHead())->SerializeRaw(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CCustomMoreWindowsDoc diagnostics

#ifdef _DEBUG
void CCustomMoreWindowsDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCustomMoreWindowsDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCustomMoreWindowsDoc commands

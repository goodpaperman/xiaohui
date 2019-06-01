// ColorSpaceDoc.cpp : implementation of the CColorSpaceDoc class
//

#include "stdafx.h"
#include "ColorSpace.h"

#include "ColorSpaceDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorSpaceDoc

IMPLEMENT_DYNCREATE(CColorSpaceDoc, CDocument)

BEGIN_MESSAGE_MAP(CColorSpaceDoc, CDocument)
	//{{AFX_MSG_MAP(CColorSpaceDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorSpaceDoc construction/destruction

CColorSpaceDoc::CColorSpaceDoc()
{
	// TODO: add one-time construction code here

}

CColorSpaceDoc::~CColorSpaceDoc()
{
}

BOOL CColorSpaceDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CColorSpaceDoc serialization

void CColorSpaceDoc::Serialize(CArchive& ar)
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
// CColorSpaceDoc diagnostics

#ifdef _DEBUG
void CColorSpaceDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CColorSpaceDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CColorSpaceDoc commands

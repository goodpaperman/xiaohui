// ReStartDoc.cpp : implementation of the CReStartDoc class
//

#include "stdafx.h"
#include "ReStart.h"

#include "ReStartDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReStartDoc

IMPLEMENT_DYNCREATE(CReStartDoc, CDocument)

BEGIN_MESSAGE_MAP(CReStartDoc, CDocument)
	//{{AFX_MSG_MAP(CReStartDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReStartDoc construction/destruction

CReStartDoc::CReStartDoc()
{
}

CReStartDoc::~CReStartDoc()
{
	
}

BOOL CReStartDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CReStartDoc serialization

void CReStartDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}

/////////////////////////////////////////////////////////////////////////////
// CReStartDoc diagnostics

#ifdef _DEBUG
void CReStartDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CReStartDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CReStartDoc commands

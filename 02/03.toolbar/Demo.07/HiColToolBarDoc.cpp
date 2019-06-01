// HiColToolBarDoc.cpp : implementation of the CHiColToolBarDoc class
//

#include "stdafx.h"
#include "HiColToolBar.h"

#include "HiColToolBarDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHiColToolBarDoc

IMPLEMENT_DYNCREATE(CHiColToolBarDoc, CDocument)

BEGIN_MESSAGE_MAP(CHiColToolBarDoc, CDocument)
	//{{AFX_MSG_MAP(CHiColToolBarDoc)
	ON_COMMAND(ID_TEST, OnTest)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHiColToolBarDoc construction/destruction

CHiColToolBarDoc::CHiColToolBarDoc()
{
}

CHiColToolBarDoc::~CHiColToolBarDoc()
{
}

BOOL CHiColToolBarDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CHiColToolBarDoc serialization

void CHiColToolBarDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}

/////////////////////////////////////////////////////////////////////////////
// CHiColToolBarDoc diagnostics

#ifdef _DEBUG
void CHiColToolBarDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CHiColToolBarDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHiColToolBarDoc commands

void CHiColToolBarDoc::OnTest() 
{
}

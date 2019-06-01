// TestTipDayDoc.cpp : implementation of the CTestTipDayDoc class
//

#include "stdafx.h"
#include "TestTipDay.h"

#include "TestTipDayDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestTipDayDoc

IMPLEMENT_DYNCREATE(CTestTipDayDoc, CDocument)

BEGIN_MESSAGE_MAP(CTestTipDayDoc, CDocument)
	//{{AFX_MSG_MAP(CTestTipDayDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestTipDayDoc construction/destruction

CTestTipDayDoc::CTestTipDayDoc()
{
	// TODO: add one-time construction code here

}

CTestTipDayDoc::~CTestTipDayDoc()
{
}

BOOL CTestTipDayDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CTestTipDayDoc serialization

void CTestTipDayDoc::Serialize(CArchive& ar)
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
// CTestTipDayDoc diagnostics

#ifdef _DEBUG
void CTestTipDayDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTestTipDayDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTestTipDayDoc commands

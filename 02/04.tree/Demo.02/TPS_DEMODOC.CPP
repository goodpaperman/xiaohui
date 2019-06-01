// TPS_DemoDoc.cpp : implementation of the CTPS_DemoDoc class
//

#include "stdafx.h"
#include "TPS_Demo.h"

#include "TPS_DemoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTPS_DemoDoc

IMPLEMENT_DYNCREATE(CTPS_DemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CTPS_DemoDoc, CDocument)
	//{{AFX_MSG_MAP(CTPS_DemoDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTPS_DemoDoc construction/destruction

CTPS_DemoDoc::CTPS_DemoDoc()
{
	// TODO: add one-time construction code here

}

CTPS_DemoDoc::~CTPS_DemoDoc()
{
}

BOOL CTPS_DemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CTPS_DemoDoc serialization

void CTPS_DemoDoc::Serialize(CArchive& ar)
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
// CTPS_DemoDoc diagnostics

#ifdef _DEBUG
void CTPS_DemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTPS_DemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTPS_DemoDoc commands

// WizDlgDoc.cpp : implementation of the CWizDlgDoc class
//

#include "stdafx.h"
#include "WizDlg.h"

#include "WizDlgDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWizDlgDoc

IMPLEMENT_DYNCREATE(CWizDlgDoc, CDocument)

BEGIN_MESSAGE_MAP(CWizDlgDoc, CDocument)
	//{{AFX_MSG_MAP(CWizDlgDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWizDlgDoc construction/destruction

CWizDlgDoc::CWizDlgDoc()
{
	// TODO: add one-time construction code here

}

CWizDlgDoc::~CWizDlgDoc()
{
}

BOOL CWizDlgDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CWizDlgDoc serialization

void CWizDlgDoc::Serialize(CArchive& ar)
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
// CWizDlgDoc diagnostics

#ifdef _DEBUG
void CWizDlgDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CWizDlgDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWizDlgDoc commands

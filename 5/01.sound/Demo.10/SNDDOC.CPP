// sndDoc.cpp : implementation of the CSndDoc class
//

#include "stdafx.h"
#include "snd.h"

#include "sndDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSndDoc

IMPLEMENT_DYNCREATE(CSndDoc, CDocument)

BEGIN_MESSAGE_MAP(CSndDoc, CDocument)
	//{{AFX_MSG_MAP(CSndDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSndDoc construction/destruction

CSndDoc::CSndDoc()
{
	// TODO: add one-time construction code here

}

CSndDoc::~CSndDoc()
{
}

BOOL CSndDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSndDoc serialization

void CSndDoc::Serialize(CArchive& ar)
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
// CSndDoc diagnostics

#ifdef _DEBUG
void CSndDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSndDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSndDoc commands

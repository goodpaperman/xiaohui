// DVMDoc.cpp : implementation of the CDVMDoc class
//

#include "stdafx.h"
#include "DualViewMDI.h"

#include "DVMDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDVMDoc

IMPLEMENT_DYNCREATE(CDVMDoc, CDocument)

BEGIN_MESSAGE_MAP(CDVMDoc, CDocument)
	//{{AFX_MSG_MAP(CDVMDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDVMDoc construction/destruction

CDVMDoc::CDVMDoc()
{
	// TODO: add one-time construction code here

}

CDVMDoc::~CDVMDoc()
{
}

BOOL CDVMDoc::OnNewDocument()
{
	CFrameWnd			*pWndSecondChild ;
	CMultiDocTemplate	*pDocTemplate ;

	if (!CDocument::OnNewDocument())
		return FALSE;

	m_strTestText = "This window will self-destruct in 5 seconds. Just kidding!";

// Create secondary child frame with view and document. 'theApp' is defined at 
// the bottom of the app's class' header file, so that we can easily refer to 
// the application object.
	pDocTemplate = theApp.GetDocTemplate(DOCTEMPLATE_SECONDVIEW);
	if (pDocTemplate != NULL)
	{
// Note: First child frame does not exist at this point, so we cannot refer to 
// it.
		pWndSecondChild = pDocTemplate->CreateNewFrame(this, NULL);	
		ASSERT(pWndSecondChild != NULL);
// Third parameter (make window visible) defaults to TRUE.
		pDocTemplate->InitialUpdateFrame(pWndSecondChild, this);
	}

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CDVMDoc serialization

void CDVMDoc::Serialize(CArchive& ar)
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
// CDVMDoc diagnostics

#ifdef _DEBUG
void CDVMDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDVMDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDVMDoc commands

CString CDVMDoc::GetTestText(void)
{
	return m_strTestText ;
}

// TestPreviewDoc.cpp : implementation of the CTestPreviewDoc class
//

#include "stdafx.h"
#include "TestPreview.h"
#include "TestPreviewDoc.h"
#include "CPreviewFileDialog.h"
#include "CDib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestPreviewDoc

IMPLEMENT_DYNCREATE(CTestPreviewDoc, CDocument)

BEGIN_MESSAGE_MAP(CTestPreviewDoc, CDocument)
	//{{AFX_MSG_MAP(CTestPreviewDoc)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


class CPreviewDIB : public CAbstractPreview
{
public:
	virtual void SetPreviewFile(const CString& csFileName);
	virtual void DrawPreview(CDC *pDC,int x,int y,int width,int height);


	CDIB dib;
};

/////////////////////////////////////////////////////////////////////////////
// CTestPreviewDoc construction/destruction

CTestPreviewDoc::CTestPreviewDoc()
{

}

CTestPreviewDoc::~CTestPreviewDoc()
{
}

BOOL CTestPreviewDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTestPreviewDoc serialization

void CTestPreviewDoc::Serialize(CArchive& ar)
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
// CTestPreviewDoc diagnostics

#ifdef _DEBUG
void CTestPreviewDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTestPreviewDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTestPreviewDoc commands

void CTestPreviewDoc::OnFileOpen() 
{
CPreviewDIB preview;
CPreviewFileDialog dlg(&preview,TRUE,"bmp","*.bmp",OFN_HIDEREADONLY | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR |OFN_PATHMUSTEXIST,
								"Bitmap Files (*.bmp)|*.bmp|"
								"All Files (*.*)|*.*||",
								AfxGetMainWnd());
	if(dlg.DoModal() == IDOK)
	{
		AfxGetApp()->OpenDocumentFile(dlg.GetPathName());
	}
}


void CPreviewDIB::SetPreviewFile(const CString& csFileName)
{
	if(!dib.OpenDIB(csFileName)) dib.DestroyDIB();
}

void CPreviewDIB::DrawPreview(CDC *pDC,int X,int Y,int width,int height)
{
	if(!dib.IsValid()) return;
	CRect cr;
	cr = Calc(dib.Width(),dib.Height(),width,height);
	dib.StretchBlt(pDC->m_hDC,cr.left+X,cr.top+Y,cr.Width(),cr.Height(),0,0,dib.Width(),dib.Height());
}

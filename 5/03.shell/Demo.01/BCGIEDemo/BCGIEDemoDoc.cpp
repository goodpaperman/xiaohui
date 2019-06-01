// BCGIEDemoDoc.cpp : implementation of the CBCGIEDemoDoc class
//

#include "stdafx.h"
#include "BCGIEDemo.h"

#include "BCGIEDemoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBCGIEDemoDoc

IMPLEMENT_DYNCREATE(CBCGIEDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CBCGIEDemoDoc, CDocument)
	//{{AFX_MSG_MAP(CBCGIEDemoDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBCGIEDemoDoc construction/destruction

CBCGIEDemoDoc::CBCGIEDemoDoc()
{
	m_iHistoryOffset = 0;
	m_arHistory.SetSize (0, 1);
}

CBCGIEDemoDoc::~CBCGIEDemoDoc()
{
	for (int i = 0; i < m_arHistory.GetSize (); i ++)
	{
		ASSERT (m_arHistory [i] != NULL);
		delete m_arHistory [i];
	}
}

BOOL CBCGIEDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CBCGIEDemoDoc serialization

void CBCGIEDemoDoc::Serialize(CArchive& ar)
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
// CBCGIEDemoDoc diagnostics

#ifdef _DEBUG
void CBCGIEDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBCGIEDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBCGIEDemoDoc commands

CHistoryObj* CBCGIEDemoDoc::AddURLToHistory (const CString& strTitle, const CString& strURL)
{
	ASSERT (m_arHistory.GetSize () <= HISTORY_LEN);

	for (int i = 0; i < m_arHistory.GetSize (); i ++)
	{
		CHistoryObj* pObj = m_arHistory [i];
		ASSERT (pObj != NULL);

		if (pObj->GetTitle () == strTitle &&
			pObj->GetURL () == strURL)
		{
			return pObj;
		}
	}

    int n = m_arHistory.GetSize(); 
	if (n == HISTORY_LEN)
	{
        delete m_arHistory.GetAt(n-1); 
		m_arHistory.RemoveAt (n-1);
	}

    static int m = 0; 
    m = (m+1)%HISTORY_LEN; 
	CHistoryObj* pObj = new CHistoryObj (strTitle, strURL, 
		FIRST_HISTORY_COMMAND + m);
	m_arHistory.InsertAt (0, pObj);

	m_iHistoryOffset = 0;
	return pObj;
}
//****************************************************************************************
void CBCGIEDemoDoc::GetBackList (_T_HistotyList& lst) const
{
	lst.RemoveAll ();
	for (int i = m_iHistoryOffset + 1; i < m_arHistory.GetSize () ; i ++)
	{
		lst.AddTail (m_arHistory [i]);
	}
}
//****************************************************************************************
void CBCGIEDemoDoc::GetFrwdList (_T_HistotyList& lst) const
{
	lst.RemoveAll ();
	for (int i = m_iHistoryOffset - 1; i >= 0; i --)
	{
		ASSERT (i < m_arHistory.GetSize ());
		lst.AddTail (m_arHistory [i]);
	}
}
//****************************************************************************************
CHistoryObj* CBCGIEDemoDoc::Go (UINT uiCmd)
{
	for (int i = 0; i < m_arHistory.GetSize (); i ++)
	{
		CHistoryObj* pObj = m_arHistory [i];
		ASSERT (pObj != NULL);

		if (pObj->GetCommand () == uiCmd)
		{
            //m_arHistory.RemoveAt (i);
            //m_arHistory.Add (pObj);

			m_iHistoryOffset = i;
			return pObj;
		}
	}

	return NULL;
}

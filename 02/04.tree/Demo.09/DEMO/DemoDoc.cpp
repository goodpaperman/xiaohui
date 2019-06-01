// DemoDoc.cpp : implementation of the CDemoDoc class
//

#include "stdafx.h"
#include "Demo.h"

#include "DemoDoc.h"
#include "OptionsDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDemoDoc

IMPLEMENT_DYNCREATE(CDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CDemoDoc, CDocument)
	//{{AFX_MSG_MAP(CDemoDoc)
	ON_COMMAND(IDM_SETTINGS, OnSettings)
	ON_COMMAND(IDM_SELECT, OnSelect)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemoDoc construction/destruction

CDemoDoc::CDemoDoc()
{
	m_Options.SetOption("RadioOption1", 2);
	m_Options.SetOption("RadioOption2", 1);
	m_Options.SetOptionItem("Radio Options", IDB_ITEMS, IDB_ITEMS);
	m_Options.SetOptionItem("RadioOption1", "\tSelection 0", 0, IDB_RADIOON, IDB_RADIOOFF);
	m_Options.SetOptionItem("RadioOption1", "\tSelection 1", 1, IDB_RADIOON, IDB_RADIOOFF);
	m_Options.SetOptionItem("RadioOption1", "\tSelection 2", 2, IDB_RADIOON, IDB_RADIOOFF);
		m_Options.SetOptionItem("RadioOption2", "\t\tSelection 0", 0, IDB_RADIOON, IDB_RADIOOFF);
		m_Options.SetOptionItem("RadioOption2", "\t\tSelection 1", 1, IDB_RADIOON, IDB_RADIOOFF);
	m_Options.SetOptionItem("RadioOption1", "\tSelection 3", 3, IDB_RADIOON, IDB_RADIOOFF);

	m_Options.SetOptionItem("Check Options", IDB_ITEMS, IDB_ITEMS);
	m_Options.SetOption("CheckOption1", COptions::CheckFalse);
	m_Options.SetOptionItem("CheckOption1", "\tCheck 1", COptions::CheckTrue, IDB_CHECKON, IDB_CHECKOFF);
		m_Options.SetOption("RadioOption3", 1);
		m_Options.SetOptionItem("RadioOption3", "\t\tSelection 0", 0, IDB_RADIOON, IDB_RADIOOFF);
		m_Options.SetOptionItem("RadioOption3", "\t\tSelection 1", 1, IDB_RADIOON, IDB_RADIOOFF);
	m_Options.SetOption("CheckOption2", COptions::CheckTrue);
	m_Options.SetOptionItem("CheckOption2", "\tCheck 2", COptions::CheckTrue, IDB_CHECKON, IDB_CHECKOFF);
}

CDemoDoc::~CDemoDoc()
{
}

BOOL CDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDemoDoc serialization

void CDemoDoc::Serialize(CArchive& ar)
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
// CDemoDoc diagnostics

#ifdef _DEBUG
void CDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDemoDoc commands

void CDemoDoc::OnSettings() 
{
	COptionsDlg dlg;
	dlg.m_OptionsTreeCtrl.m_pOptions = &m_Options;
	m_Options.BeginTrans();

	if (dlg.DoModal() != IDOK)
	{
		m_Options.RollbackTrans();
	}
	else
	{
		m_Options.CommitTrans();
	}
}

void CDemoDoc::OnSelect() 
{
	// TODO: Add your command handler code here
	
}

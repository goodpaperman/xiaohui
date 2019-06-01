// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "SwitchTB.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
}

CMainFrame::~CMainFrame()
{
	CToolBar *pTB;
	int n;

	for (n=0 ; n < m_vToolbars.GetSize () ; n++) {
		pTB = m_vToolbars.GetAt (n);
		if (pTB)
			delete pTB;
	}
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_wndClient.SubclassWindow (m_hWndMDIClient);
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

#include "DocTemplateEx.h"

void CMainFrame::SwitchToolbar ()
{
/***************************************************************\
| This function retrive the resource ID from the current view.	|
| Then it calls 'SetToolbar' to activate the specified toolbar	|
| and to disactivets all the others.							|
| If no view is open the resource ID, 'idResource', is set to 0	|
| and all toolbars are disactivated.							|
| External functions used:										|
| IsWindow (CWnd *pWnd)											|
\***************************************************************/

	CView *pView;
	CDocTemplateEx *pTmpl;
	CMDIChildWnd *pKid;
	int idResource = 0; // initialize incase no resource is found

	pKid = MDIGetActive ();
	if (::IsWindow (pKid)) {
		pView = pKid->GetActiveView ();
		if (::IsWindow (pView)) {
			pTmpl = (CDocTemplateEx *) pView->GetDocument ()->GetDocTemplate ();
			idResource = pTmpl->GetResourceID ();
		}
	}
	SetToolbar (idResource);
}

void CMainFrame::SetToolbar (int nIdr)
/***************************************************************\
| This function gets the toolbar index to the toolbars array,	|
| 'm_vToolbars'. The it loops over all the toolbars. If the		|
| toolbar the one to be displayed it is closed.					|
| External functions used:										|
| ShowControlBar												|
| RecalcLayout													|
\***************************************************************/
{
	static int nToolbars;
	int n, nIdx;
	CString str;
	CToolBar *pTB;

	str.Format ("Toolbar #%d", ++nToolbars);
	nIdx = AddToolbar (nIdr, str);
	for (n=0 ; n < m_vToolbars.GetSize () ; n++) {
		pTB = m_vToolbars.GetAt (n);
		if (n != nIdx) {
			ShowControlBar (pTB, 0, 0);
		}
		else
			ShowControlBar (pTB, 1, 1);
	}
	m_wndToolBar.GetParentFrame()->RecalcLayout();
}

int CMainFrame::AddToolbar (int nIDR, CString strWndTxt)
/***************************************************************\
| This function returns the index of the toolbar, that have the	|
| ID of 'nIDR', in the toolbar array, 'm_vToolbars'.			|
| If the ID does not exist in the loaded ID array, 'm_idrLoaded'|
| the function creates a new toolbar, ads the toolbar pointer	|
| to the toolbar array and the ID to the loaded toolbar IDs		|
| array.														|
| The function also docks the toolbar left to the mainframe		|
| toolbar.														|
| External functions used:										|
| ShowControlBar												|
| FindInArray													|
\***************************************************************/
{
	CToolBar *pTB;
	BOOL f;
	CRect rc;
	int nIdx;

	if (nIDR == 0)
		return (-1);
	if ((nIdx = ::FindInArray (m_idrLoaded, nIDR)) < 0) {
		pTB = new CToolBar;
		pTB->Create (this);
		f = pTB->LoadToolBar (nIDR);
		if (f == 0) {
			pTB->DestroyWindow ();
			delete pTB;
			return (-1);
		}
		pTB->SetBarStyle(m_wndToolBar.GetBarStyle() |
							CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
		pTB->EnableDocking(CBRS_ALIGN_TOP);
		m_wndToolBar.GetWindowRect (&rc);
		rc.OffsetRect(1,0);
		DockControlBar(pTB, AFX_IDW_DOCKBAR_TOP, &rc);
		pTB->SetWindowText (strWndTxt);
		pTB->ShowWindow (SW_RESTORE);
		ShowControlBar (pTB, 1, 1);
		nIdx = m_vToolbars.Add (pTB);
		m_idrLoaded.Add (nIDR);
	}
	return (nIdx);
}


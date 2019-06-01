// DlgFileBrowse.cpp : implementation file
//

#include "stdafx.h"
#include <dlgs.h>
#include "TwoPanes.h"
#include "DlgFileBrowse.h"
#include "ThreadRunningDlg.h"
#include "WndFileBrowse.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define WM_USR_INIT_FINISHED (WM_USER + 101)

/////////////////////////////////////////////////////////////////////////////
// CDlgFileBrowse

IMPLEMENT_DYNAMIC(CDlgFileBrowse, CFileDialog)

CDlgFileBrowse::CDlgFileBrowse(
		CThreadRunningDlg& rThreadRunningDlg
			)
: m_rThreadRunningDlg(rThreadRunningDlg)
, CFileDialog(TRUE, NULL, _T("*.*"), 
			  OFN_ALLOWMULTISELECT | OFN_ENABLEHOOK | OFN_HIDEREADONLY, 
			  _T("All Files (*.*)|*.*||"), 
				NULL
				)
{
}


BEGIN_MESSAGE_MAP(CDlgFileBrowse, CFileDialog)
	//{{AFX_MSG_MAP(CDlgFileBrowse)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_USR_INIT_FINISHED, OnInitFinished)
END_MESSAGE_MAP()

void CDlgFileBrowse::OnInitDone()
{
	ASSERT_VALID(this);
	ASSERT(!GetParent()->IsWindowVisible());
	PostMessage(WM_USR_INIT_FINISHED);
}

BOOL CDlgFileBrowse::OnInitDialog() 
{
	CWnd* pParent = GetParent();

	VERIFY(::SetWindowLong(*pParent, GWL_STYLE, WS_CHILD | WS_CLIPCHILDREN));
	VERIFY(::SetParent(*pParent,  m_rThreadRunningDlg.m_hWndParent));
	VERIFY(::SetWindowPos(*pParent, NULL, 0, 0, 0, 0,
		SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_FRAMECHANGED ));
	if(pParent)
		pParent->SetDlgCtrlID(m_rThreadRunningDlg.m_nID);

	CFileDialog::OnInitDialog();
	
	HideControl(IDOK);
	HideControl(IDCANCEL);
	HideControl(stc2);
	if(g_bIsWindows98orLater)
	{
		SetControlText(stc3, "");
		HWND hwndSB = FindWindowEx(*pParent, NULL, _T("ScrollBar"), NULL);
		if(hwndSB)
			::ShowWindow(hwndSB, SW_HIDE);
	}
	else
		HideControl(stc3);
	HideControl(cmb1);
	HideControl(edt1);
	return TRUE;  // return TRUE unless you set the focus to a control
}

BOOL CDlgFileBrowse::OnFileNameOK()
{
	return TRUE;
}

LPARAM CDlgFileBrowse::OnInitFinished(WPARAM, LPARAM)
{
	m_rThreadRunningDlg.m_wndFileBrowse.SubclassWindow(*GetParent());
//	m_rThreadRunningDlg.m_wndFileBrowse.Invalidate();
	ASSERT(NULL == m_rThreadRunningDlg.m_pMainWnd);
	m_rThreadRunningDlg.m_pMainWnd = &m_rThreadRunningDlg.m_wndFileBrowse;//GetParent();
	VERIFY(SetEvent(m_rThreadRunningDlg.m_hEventCreated));
	return 1;
}

void CDlgFileBrowse::OnFolderChange()
{
	CFileDialog::OnFolderChange();
	if(!g_bIsWindows98orLater)
	{
		CWndFileBrowse* pParent = DYNAMIC_DOWNCAST(CWndFileBrowse, GetParent());
		if(pParent)
			pParent->SetListSize();
	}
}
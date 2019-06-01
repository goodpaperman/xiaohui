// ThreadRunningDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TwoPanes.h"
#include "ThreadRunningDlg.h"
#include "DlgFileBrowse.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

__declspec(thread) HHOOK g_hHook=NULL;

static long lThreads = 0;

HANDLE g_hEventClosed = CreateEvent(NULL, TRUE, FALSE, NULL);

UINT CALLBACK KeybProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode >= 0 && wParam==VK_ESCAPE)
	// Do not call CallNextHookEx to prevent the system to delete
		return 1;
	return CallNextHookEx(g_hHook, nCode, wParam, lParam);
}

/////////////////////////////////////////////////////////////////////////////
// CThreadRunningDlg

IMPLEMENT_DYNCREATE(CThreadRunningDlg, CWinThread)

CThreadRunningDlg::CThreadRunningDlg()
{
	m_msgCur.wParam = 0;
	m_hWndParent = NULL;
	m_pAttachedView = NULL;
	m_nID = 0;
	InterlockedIncrement(&lThreads);
	m_hEventCreated = CreateEvent(NULL, TRUE, FALSE, NULL);
}

CThreadRunningDlg::~CThreadRunningDlg()
{
	CloseHandle(m_hEventCreated);
	if(m_pAttachedView)
		delete m_pAttachedView;
	if(0 == InterlockedDecrement(&lThreads))
		VERIFY(SetEvent(g_hEventClosed));
}

BOOL CThreadRunningDlg::InitInstance()
{
	g_hHook = SetWindowsHookEx(WH_KEYBOARD, 
						 reinterpret_cast<HOOKPROC>(KeybProc), 
						 NULL, GetCurrentThreadId());	
	CDlgFileBrowse dlg(*this);
	dlg.DoModal();
	m_pMainWnd = NULL;
	return FALSE;
}


BEGIN_MESSAGE_MAP(CThreadRunningDlg, CWinThread)
	//{{AFX_MSG_MAP(CThreadRunningDlg)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CThreadRunningDlg message handlers


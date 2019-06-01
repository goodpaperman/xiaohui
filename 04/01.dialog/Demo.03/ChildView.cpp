// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "TwoPanes.h"
#include "ChildView.h"
#include "ThreadRunningDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildView

IMPLEMENT_DYNCREATE(CChildView, CWnd)

CChildView::CChildView()
{
	m_pDialogThread = NULL;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView,CWnd )
	//{{AFX_MSG_MAP(CChildView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CChildView message handlers


BOOL CChildView::Create(LPCTSTR, LPCTSTR, DWORD, const RECT&, CWnd* pParentWnd, UINT nID, CCreateContext* ) 
{
	m_pDialogThread = (CThreadRunningDlg*)
		AfxBeginThread(RUNTIME_CLASS(CThreadRunningDlg), 
			THREAD_PRIORITY_NORMAL, /*nPriority*/
			0, /*nStackSize*/ 
			CREATE_SUSPENDED /*dwCreateFlags*/);
	ASSERT_VALID(m_pDialogThread);
	m_pDialogThread->m_hWndParent = *pParentWnd;
	m_pDialogThread->m_pMainWnd = NULL;
	m_pDialogThread->m_pAttachedView = this;
	m_pDialogThread->m_nID = nID;
	VERIFY(m_pDialogThread->ResumeThread());

	MSG msg;
	while(WAIT_OBJECT_0 + 1 == MsgWaitForMultipleObjects( 
			1,					// number of handles in the object handle array 
			&m_pDialogThread->m_hEventCreated,	// pointer to the object-handle array 
			FALSE,			// wait for all or wait for one 
			5000,				// time-out interval in milliseconds 
			QS_ALLINPUT		// type of input events to wait for 
			))
	{
		::PeekMessage( &msg, NULL, 0, 0, PM_REMOVE);
//		if(WM_PAINT == msg.message)
//			::DispatchMessage(&msg);
//		else
			TRACE("Mesage bypassed: HWND %X ID %X WPARAM %X LPARAM %X\n",
					msg.hwnd, msg.message, msg.wParam, msg.lParam);
		if(NULL != m_pDialogThread->m_pMainWnd)
			break;
	}
	BOOL bResult = FALSE;
	CWnd* pWnd = m_pDialogThread->m_pMainWnd;
	if(NULL != pWnd)
	{
		HWND hWnd = *pWnd;
		if(NULL != hWnd && Attach(hWnd))
		{
//			SetDlgCtrlID(nID);
//			ASSERT(GetDlgCtrlID() == (int)nID);
			bResult = TRUE;
		}
	}
	return bResult;
}


BOOL CChildView::DestroyWindow() 
{
//	if(!IsWindow(m_hWnd))
//	{
//		Detach();
//		return TRUE;
//	}
//	::SetWindowPos(m_hWnd, NULL, 0, 0, 0, 0,
//		SWP_NOZORDER|SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE|
//		SWP_HIDEWINDOW);
//	VERIFY(SetParent(NULL));
//	if(::EndDialog(m_hWnd, IDCANCEL))
	Detach();
	return m_pDialogThread->PostThreadMessage(WM_QUIT, 0, 0);
}

// BCGIEDemoView.cpp : implementation of the CBCGIEDemoView class
//

#include "stdafx.h"
#include "BCGIEDemo.h"

#include "BCGIEDemoDoc.h"
#include "BCGIEDemoView.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBCGIEDemoView

IMPLEMENT_DYNCREATE(CBCGIEDemoView, CHtmlView)

BEGIN_MESSAGE_MAP(CBCGIEDemoView, CHtmlView)
	//{{AFX_MSG_MAP(CBCGIEDemoView)
	ON_COMMAND(ID_GO_BACK, OnGoBack)
	ON_COMMAND(ID_GO_FORWARD, OnGoForward)
	ON_COMMAND(ID_GO_SEARCH_THE_WEB, OnGoSearchTheWeb)
	ON_COMMAND(ID_GO_START_PAGE, OnGoStartPage)
	ON_COMMAND(ID_VIEW_STOP, OnViewStop)
	ON_COMMAND(ID_VIEW_REFRESH, OnViewRefresh)
	ON_COMMAND(ID_HELP_WEB_TUTORIAL, OnHelpWebTutorial)
	ON_COMMAND(ID_HELP_ONLINE_SUPPORT, OnHelpOnlineSupport)
	ON_COMMAND(ID_HELP_MICROSOFT_ON_THE_WEB_FREE_STUFF, OnHelpMicrosoftOnTheWebFreeStuff)
	ON_COMMAND(ID_HELP_MICROSOFT_ON_THE_WEB_FREQUENTLY_ASKED_QUESTIONS, OnHelpMicrosoftOnTheWebFrequentlyAskedQuestions)
	ON_COMMAND(ID_HELP_MICROSOFT_ON_THE_WEB_GET_FASTER_INTERNET_ACCESS, OnHelpMicrosoftOnTheWebGetFasterInternetAccess)
	ON_COMMAND(ID_HELP_MICROSOFT_ON_THE_WEB_MICROSOFT_HOME_PAGE, OnHelpMicrosoftOnTheWebMicrosoftHomePage)
	ON_COMMAND(ID_HELP_MICROSOFT_ON_THE_WEB_SEARCH_THE_WEB, OnHelpMicrosoftOnTheWebSearchTheWeb)
	ON_COMMAND(ID_HELP_MICROSOFT_ON_THE_WEB_SEND_FEEDBACK, OnHelpMicrosoftOnTheWebSendFeedback)
	ON_COMMAND(ID_HELP_MICROSOFT_ON_THE_WEB_INTERNET_START_PAGE, OnHelpMicrosoftOnTheWebInternetStartPage)
	ON_COMMAND(ID_HELP_MICROSOFT_ON_THE_WEB_BEST_OF_THE_WEB, OnHelpMicrosoftOnTheWebBestOfTheWeb)
	ON_COMMAND(ID_VIEW_FONTS_LARGEST, OnViewFontsLargest)
	ON_COMMAND(ID_VIEW_FONTS_LARGE, OnViewFontsLarge)
	ON_COMMAND(ID_VIEW_FONTS_MEDIUM, OnViewFontsMedium)
	ON_COMMAND(ID_VIEW_FONTS_SMALL, OnViewFontsSmall)
	ON_COMMAND(ID_VIEW_FONTS_SMALLEST, OnViewFontsSmallest)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_UPDATE_COMMAND_UI(ID_GO_FORWARD, OnUpdateGoForward)
	ON_UPDATE_COMMAND_UI(ID_GO_BACK, OnUpdateGoBack)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CHtmlView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CHtmlView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CHtmlView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBCGIEDemoView construction/destruction

CBCGIEDemoView::CBCGIEDemoView()
{
	// TODO: add construction code here

}

CBCGIEDemoView::~CBCGIEDemoView()
{
}

BOOL CBCGIEDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CHtmlView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CBCGIEDemoView drawing

void CBCGIEDemoView::OnDraw(CDC* pDC)
{
	CBCGIEDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CBCGIEDemoView printing

BOOL CBCGIEDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CBCGIEDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CBCGIEDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CBCGIEDemoView diagnostics

#ifdef _DEBUG
void CBCGIEDemoView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CBCGIEDemoView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}

CBCGIEDemoDoc* CBCGIEDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBCGIEDemoDoc)));
	return (CBCGIEDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBCGIEDemoView message handlers
// these are all simple one-liners to do simple controlling of the browser
void CBCGIEDemoView::OnGoBack()
{
	CBCGIEDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CHistoryObj* pHistoryObj = pDoc->GoBack ();
	if (pHistoryObj != NULL)
	{
		Navigate2 (pHistoryObj->GetURL (), 0, NULL);
	}
}

void CBCGIEDemoView::OnGoForward()
{
//	GoForward();
	CBCGIEDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CHistoryObj* pHistoryObj = pDoc->GoForward ();
	if (pHistoryObj != NULL)
	{
		Navigate2 (pHistoryObj->GetURL (), 0, NULL);
	}
}

void CBCGIEDemoView::OnGoSearchTheWeb()
{
	GoSearch();
}

void CBCGIEDemoView::OnGoStartPage()
{
	GoHome();
}

void CBCGIEDemoView::OnViewStop()
{
	Stop();
}

void CBCGIEDemoView::OnViewRefresh()
{
	Refresh();
}

// these all go to specific web pages, just like Internet Explorer's help menu
void CBCGIEDemoView::OnHelpWebTutorial()
{
	CString str;

	str.LoadString(IDS_WEB_TUTORIAL);
	Navigate2(str, 0, NULL);
}

void CBCGIEDemoView::OnHelpOnlineSupport()
{
	CString str;

	str.LoadString(IDS_ONLINE_SUPPORT);
	Navigate2(str, 0, NULL);
}

void CBCGIEDemoView::OnHelpMicrosoftOnTheWebBestOfTheWeb()
{
	CString str;

	str.LoadString(IDS_BEST_OF_THE_WEB);
	Navigate2(str, 0, NULL);
}

void CBCGIEDemoView::OnHelpMicrosoftOnTheWebFreeStuff()
{
	CString str;

	str.LoadString(IDS_FREE_STUFF);
	Navigate2(str, 0, NULL);
}

void CBCGIEDemoView::OnHelpMicrosoftOnTheWebFrequentlyAskedQuestions()
{
	CString str;

	str.LoadString(IDS_FREQUENTLY_ASKED_QUESTIONS);
	Navigate2(str, 0, NULL);
}

void CBCGIEDemoView::OnHelpMicrosoftOnTheWebGetFasterInternetAccess()
{
	CString str;

	str.LoadString(IDS_GET_FASTER_INTERNET_ACCESS);
	Navigate2(str, 0, NULL);
}

void CBCGIEDemoView::OnHelpMicrosoftOnTheWebMicrosoftHomePage()
{
	CString str;

	str.LoadString(IDS_MICROSOFT_HOME_PAGE);
	Navigate2(str, 0, NULL);
}

void CBCGIEDemoView::OnHelpMicrosoftOnTheWebSearchTheWeb()
{
	CString str;

	str.LoadString(IDS_SEARCH_THE_WEB);
	Navigate2(str, 0, NULL);
}

void CBCGIEDemoView::OnHelpMicrosoftOnTheWebSendFeedback()
{
	CString str;

	str.LoadString(IDS_SEND_FEEDBACK);
	Navigate2(str, 0, NULL);
}

void CBCGIEDemoView::OnHelpMicrosoftOnTheWebInternetStartPage()
{
	CString str;

	str.LoadString(IDS_INTERNET_START_PAGE);
	Navigate2(str, 0, NULL);
}

// these functions control the font size.  There is no explicit command in the
// CHtmlView class to do this, but we can do it by using the ExecWB() function.
void CBCGIEDemoView::OnViewFontsLargest()
{
	COleVariant vaZoomFactor(4l);

	ExecWB(OLECMDID_ZOOM, OLECMDEXECOPT_DONTPROMPTUSER,
		   &vaZoomFactor, NULL);
}

void CBCGIEDemoView::OnViewFontsLarge()
{
	COleVariant vaZoomFactor(3l);

	ExecWB(OLECMDID_ZOOM, OLECMDEXECOPT_DONTPROMPTUSER,
		   &vaZoomFactor, NULL);
}

void CBCGIEDemoView::OnViewFontsMedium()
{
	COleVariant vaZoomFactor(2l);

	ExecWB(OLECMDID_ZOOM, OLECMDEXECOPT_DONTPROMPTUSER,
		   &vaZoomFactor, NULL);
}

void CBCGIEDemoView::OnViewFontsSmall()
{
	COleVariant vaZoomFactor(1l);

	ExecWB(OLECMDID_ZOOM, OLECMDEXECOPT_DONTPROMPTUSER,
		   &vaZoomFactor, NULL);
}

void CBCGIEDemoView::OnViewFontsSmallest()
{
	COleVariant vaZoomFactor(0l);

	ExecWB(OLECMDID_ZOOM, OLECMDEXECOPT_DONTPROMPTUSER,
		   &vaZoomFactor, NULL);
}

// This demonstrates how we can use the Navigate2() function to load local files
// including local HTML pages, GIFs, AIFF files, etc.
void CBCGIEDemoView::OnFileOpen()
{
	CString str;

	str.LoadString(IDS_FILETYPES);

	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, str);

	if(fileDlg.DoModal() == IDOK)
		Navigate2(fileDlg.GetPathName(), 0, NULL);
}

void CBCGIEDemoView::OnUpdateGoForward(CCmdUI* pCmdUI) 
{
	CBCGIEDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pCmdUI->Enable (pDoc->IsFrwdAvailable ());
}

void CBCGIEDemoView::OnUpdateGoBack(CCmdUI* pCmdUI) 
{
	CBCGIEDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pCmdUI->Enable (pDoc->IsBackAvailable ());
}

void CBCGIEDemoView::OnDocumentComplete(LPCTSTR lpszURL) 
{
	// make sure the main frame has the new URL.  This call also stops the animation
	((CMainFrame*)GetParentFrame())->SetAddress(lpszURL);

	CBCGIEDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->AddURLToHistory (GetLocationName (), lpszURL);
}

void CBCGIEDemoView::OnTitleChange(LPCTSTR lpszText) 
{
	// this will change the main frame's title bar
	if (m_pDocument != NULL)
		m_pDocument->SetTitle(lpszText);
}

void CBCGIEDemoView::OnBeforeNavigate2(LPCTSTR lpszURL, DWORD nFlags, LPCTSTR lpszTargetFrameName, CByteArray& baPostedData, LPCTSTR lpszHeaders, BOOL* pbCancel) 
{
	// start the animation so that is plays while the new page is being loaded
	((CMainFrame*)GetParentFrame())->StartAnimation();
}

void CBCGIEDemoView::OnInitialUpdate() 
{
	GoHome();
}

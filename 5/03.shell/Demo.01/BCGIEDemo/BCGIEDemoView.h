// BCGIEDemoView.h : interface of the CBCGIEDemoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BCGIEDEMOVIEW_H__F83C8E13_F33E_11D2_A713_0090274409AC__INCLUDED_)
#define AFX_BCGIEDEMOVIEW_H__F83C8E13_F33E_11D2_A713_0090274409AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CBCGIEDemoView : public CHtmlView
{
protected: // create from serialization only
	CBCGIEDemoView();
	DECLARE_DYNCREATE(CBCGIEDemoView)

// Attributes
public:
	CBCGIEDemoDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGIEDemoView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnDocumentComplete(LPCTSTR lpszURL);
	virtual void OnTitleChange(LPCTSTR lpszText);
	virtual void OnBeforeNavigate2(LPCTSTR lpszURL, DWORD nFlags, LPCTSTR lpszTargetFrameName, CByteArray& baPostedData, LPCTSTR lpszHeaders, BOOL* pbCancel);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBCGIEDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBCGIEDemoView)
	afx_msg void OnGoBack();
	afx_msg void OnGoForward();
	afx_msg void OnGoSearchTheWeb();
	afx_msg void OnGoStartPage();
	afx_msg void OnViewStop();
	afx_msg void OnViewRefresh();
	afx_msg void OnHelpWebTutorial();
	afx_msg void OnHelpOnlineSupport();
	afx_msg void OnHelpMicrosoftOnTheWebFreeStuff();
	afx_msg void OnHelpMicrosoftOnTheWebFrequentlyAskedQuestions();
	afx_msg void OnHelpMicrosoftOnTheWebGetFasterInternetAccess();
	afx_msg void OnHelpMicrosoftOnTheWebMicrosoftHomePage();
	afx_msg void OnHelpMicrosoftOnTheWebSearchTheWeb();
	afx_msg void OnHelpMicrosoftOnTheWebSendFeedback();
	afx_msg void OnHelpMicrosoftOnTheWebInternetStartPage();
	afx_msg void OnHelpMicrosoftOnTheWebBestOfTheWeb();
	afx_msg void OnViewFontsLargest();
	afx_msg void OnViewFontsLarge();
	afx_msg void OnViewFontsMedium();
	afx_msg void OnViewFontsSmall();
	afx_msg void OnViewFontsSmallest();
	afx_msg void OnFileOpen();
	afx_msg void OnUpdateGoForward(CCmdUI* pCmdUI);
	afx_msg void OnUpdateGoBack(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in BCGIEDemoView.cpp
inline CBCGIEDemoDoc* CBCGIEDemoView::GetDocument()
   { return (CBCGIEDemoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGIEDEMOVIEW_H__F83C8E13_F33E_11D2_A713_0090274409AC__INCLUDED_)

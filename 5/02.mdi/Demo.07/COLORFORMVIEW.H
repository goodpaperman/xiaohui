#if !defined(AFX_COLORFORMVIEW_H__F9BB0CD5_3D20_11D2_BC46_0060970A2B51__INCLUDED_)
#define AFX_COLORFORMVIEW_H__F9BB0CD5_3D20_11D2_BC46_0060970A2B51__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
/////////////////////////////////////////////////////////////////////////////
//
// Author:	if (it works)
//				Author = _T("Patty You");
//			else
//				Author = _T("IUnknown");
// Date:	08/26/98
/////////////////////////////////////////////////////////////////////////////
// ColorFormView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CColorFormView view

class CColorFormView : public CFormView
{
protected:      // must derive your own class
	CColorFormView(LPCTSTR lpszTemplateName);
	CColorFormView(UINT nIDTemplate);
	DECLARE_DYNAMIC(CColorFormView)

// Attributes
public:

protected:
	COLORREF m_crBackground;
	CBrush m_wndbkBrush;	// background brush

// Operations
public:
	void SetBackgroundColor(COLORREF crBackground);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorFormView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CColorFormView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CColorFormView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORFORMVIEW_H__F9BB0CD5_3D20_11D2_BC46_0060970A2B51__INCLUDED_)

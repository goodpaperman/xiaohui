#if !defined(AFX_SWITCHTBVIEW1_H__0ED95745_DBDF_11D2_9146_0060082BE95D__INCLUDED_)
#define AFX_SWITCHTBVIEW1_H__0ED95745_DBDF_11D2_9146_0060082BE95D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SwitchTBView1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSwitchTBView1 view

class CSwitchTBView1 : public CView
{
protected:
	CSwitchTBView1();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CSwitchTBView1)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSwitchTBView1)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CSwitchTBView1();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CSwitchTBView1)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SWITCHTBVIEW1_H__0ED95745_DBDF_11D2_9146_0060082BE95D__INCLUDED_)

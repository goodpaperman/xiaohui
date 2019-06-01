// TestPreviewDoc.h : interface of the CTestPreviewDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTPREVIEWDOC_H__D9C030CC_12DD_11D3_915F_FDE9AD318528__INCLUDED_)
#define AFX_TESTPREVIEWDOC_H__D9C030CC_12DD_11D3_915F_FDE9AD318528__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTestPreviewDoc : public CDocument
{
protected: // create from serialization only
	CTestPreviewDoc();
	DECLARE_DYNCREATE(CTestPreviewDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestPreviewDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTestPreviewDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTestPreviewDoc)
	afx_msg void OnFileOpen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTPREVIEWDOC_H__D9C030CC_12DD_11D3_915F_FDE9AD318528__INCLUDED_)

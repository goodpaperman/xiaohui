// ListViewDemoDoc.h : interface of the CListViewDemoDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LISTVIEWDEMODOC_H__6AB8B06B_0F98_11D2_8560_00A024068C2F__INCLUDED_)
#define AFX_LISTVIEWDEMODOC_H__6AB8B06B_0F98_11D2_8560_00A024068C2F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CListViewDemoDoc : public CDocument
{
protected: // create from serialization only
	CListViewDemoDoc();
	DECLARE_DYNCREATE(CListViewDemoDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListViewDemoDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CListViewDemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CListViewDemoDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTVIEWDEMODOC_H__6AB8B06B_0F98_11D2_8560_00A024068C2F__INCLUDED_)

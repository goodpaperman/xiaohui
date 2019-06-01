// DualListDemoDoc.h : interface of the CDualListDemoDoc class
//
// MFC generated code: no changes necessary
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DUALLISTDEMODOC_H__E6FFDCDA_DF3B_11D3_8664_0050DA15E05C__INCLUDED_)
#define AFX_DUALLISTDEMODOC_H__E6FFDCDA_DF3B_11D3_8664_0050DA15E05C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDualListDemoDoc : public CDocument
{
protected: // create from serialization only
	CDualListDemoDoc();
	DECLARE_DYNCREATE(CDualListDemoDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDualListDemoDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDualListDemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDualListDemoDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DUALLISTDEMODOC_H__E6FFDCDA_DF3B_11D3_8664_0050DA15E05C__INCLUDED_)

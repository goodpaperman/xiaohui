// MyFormViewDoc.h : interface of the CMyFormViewDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYFORMVIEWDOC_H__F9BB0CCA_3D20_11D2_BC46_0060970A2B51__INCLUDED_)
#define AFX_MYFORMVIEWDOC_H__F9BB0CCA_3D20_11D2_BC46_0060970A2B51__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CMyFormViewDoc : public CDocument
{
protected: // create from serialization only
	CMyFormViewDoc();
	DECLARE_DYNCREATE(CMyFormViewDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyFormViewDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyFormViewDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyFormViewDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYFORMVIEWDOC_H__F9BB0CCA_3D20_11D2_BC46_0060970A2B51__INCLUDED_)

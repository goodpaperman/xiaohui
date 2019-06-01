// ExampleDIBDoc.h : interface of the CExampleDIBDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXAMPLEDIBDOC_H__A69F7E0A_69CD_11D3_9AB9_0008C7728E19__INCLUDED_)
#define AFX_EXAMPLEDIBDOC_H__A69F7E0A_69CD_11D3_9AB9_0008C7728E19__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CExampleDIBDoc : public CDocument
{
protected: // create from serialization only
	CExampleDIBDoc();
	DECLARE_DYNCREATE(CExampleDIBDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExampleDIBDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CExampleDIBDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CExampleDIBDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXAMPLEDIBDOC_H__A69F7E0A_69CD_11D3_9AB9_0008C7728E19__INCLUDED_)

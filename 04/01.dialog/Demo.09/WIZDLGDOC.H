// WizDlgDoc.h : interface of the CWizDlgDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WIZDLGDOC_H__5C87DCCA_0E81_11D2_8427_0000B43382FE__INCLUDED_)
#define AFX_WIZDLGDOC_H__5C87DCCA_0E81_11D2_8427_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CWizDlgDoc : public CDocument
{
protected: // create from serialization only
	CWizDlgDoc();
	DECLARE_DYNCREATE(CWizDlgDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWizDlgDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWizDlgDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CWizDlgDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WIZDLGDOC_H__5C87DCCA_0E81_11D2_8427_0000B43382FE__INCLUDED_)

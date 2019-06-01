// WFDemoDoc.h : interface of the CWFDemoDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WFDEMODOC_H__284419AB_4050_11D4_AE95_00A024E8EE6B__INCLUDED_)
#define AFX_WFDEMODOC_H__284419AB_4050_11D4_AE95_00A024E8EE6B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CWFDemoDoc : public CDocument
{
protected: // create from serialization only
	CWFDemoDoc();
	DECLARE_DYNCREATE(CWFDemoDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWFDemoDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWFDemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CWFDemoDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WFDEMODOC_H__284419AB_4050_11D4_AE95_00A024E8EE6B__INCLUDED_)

// TabProjDoc.h : interface of the CTabProjDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TABPROJDOC_H__DE90A1AD_3680_11D2_A494_0008C77CF953__INCLUDED_)
#define AFX_TABPROJDOC_H__DE90A1AD_3680_11D2_A494_0008C77CF953__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTabProjDoc : public CDocument
{
protected: // create from serialization only
	CTabProjDoc();
	DECLARE_DYNCREATE(CTabProjDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabProjDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTabProjDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTabProjDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABPROJDOC_H__DE90A1AD_3680_11D2_A494_0008C77CF953__INCLUDED_)

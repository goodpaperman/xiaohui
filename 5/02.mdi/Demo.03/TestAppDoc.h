// TestAppDoc.h : interface of the CTestAppDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTAPPDOC_H__9FD1E40F_D97C_11D2_989A_204C4F4F5020__INCLUDED_)
#define AFX_TESTAPPDOC_H__9FD1E40F_D97C_11D2_989A_204C4F4F5020__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTestAppDoc : public CDocument
{
protected: // create from serialization only
	CTestAppDoc();
	DECLARE_DYNCREATE(CTestAppDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestAppDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTestAppDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTestAppDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTAPPDOC_H__9FD1E40F_D97C_11D2_989A_204C4F4F5020__INCLUDED_)

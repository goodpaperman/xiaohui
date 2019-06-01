// TestViewDoc.h : interface of the CTestViewDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTVIEWDOC_H__CCAACD8E_1F93_11D2_864F_0040055C08D9__INCLUDED_)
#define AFX_TESTVIEWDOC_H__CCAACD8E_1F93_11D2_864F_0040055C08D9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CTestViewDoc : public CDocument
{
protected: // create from serialization only
	CTestViewDoc();
	DECLARE_DYNCREATE(CTestViewDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestViewDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTestViewDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTestViewDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTVIEWDOC_H__CCAACD8E_1F93_11D2_864F_0040055C08D9__INCLUDED_)

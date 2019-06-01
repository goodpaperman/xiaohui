// clearmineDoc.h : interface of the CClearmineDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLEARMINEDOC_H__BB20D5DA_19E6_11D5_86D8_0000F74D8D41__INCLUDED_)
#define AFX_CLEARMINEDOC_H__BB20D5DA_19E6_11D5_86D8_0000F74D8D41__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CClearmineDoc : public CDocument
{
protected: // create from serialization only
	CClearmineDoc();
	DECLARE_DYNCREATE(CClearmineDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClearmineDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CClearmineDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CClearmineDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLEARMINEDOC_H__BB20D5DA_19E6_11D5_86D8_0000F74D8D41__INCLUDED_)

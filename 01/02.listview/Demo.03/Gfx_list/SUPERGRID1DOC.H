// SuperGrid1Doc.h : interface of the CSuperGrid1Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SUPERGRID1DOC_H__C8BADFCA_051E_11D2_83EF_0000B43382FE__INCLUDED_)
#define AFX_SUPERGRID1DOC_H__C8BADFCA_051E_11D2_83EF_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CSuperGrid1Doc : public CDocument
{
protected: // create from serialization only
	CSuperGrid1Doc();
	DECLARE_DYNCREATE(CSuperGrid1Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSuperGrid1Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSuperGrid1Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSuperGrid1Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUPERGRID1DOC_H__C8BADFCA_051E_11D2_83EF_0000B43382FE__INCLUDED_)

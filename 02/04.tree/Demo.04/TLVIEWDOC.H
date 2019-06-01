// TLViewDoc.h : interface of the CTLViewDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TLVIEWDOC_H__3C29E70F_4823_11D2_980D_004095E0DEFA__INCLUDED_)
#define AFX_TLVIEWDOC_H__3C29E70F_4823_11D2_980D_004095E0DEFA__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CTLViewDoc : public CDocument
{
protected: // create from serialization only
	CTLViewDoc();
	DECLARE_DYNCREATE(CTLViewDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTLViewDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTLViewDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTLViewDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TLVIEWDOC_H__3C29E70F_4823_11D2_980D_004095E0DEFA__INCLUDED_)

// GHCustomDrawDoc.h : interface of the CGHCustomDrawDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GHCUSTOMDRAWDOC_H__B510B4AB_CA7C_11D2_80FF_00104B346232__INCLUDED_)
#define AFX_GHCUSTOMDRAWDOC_H__B510B4AB_CA7C_11D2_80FF_00104B346232__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CGHCustomDrawDoc : public CDocument
{
protected: // create from serialization only
	CGHCustomDrawDoc();
	DECLARE_DYNCREATE(CGHCustomDrawDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGHCustomDrawDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGHCustomDrawDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGHCustomDrawDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GHCUSTOMDRAWDOC_H__B510B4AB_CA7C_11D2_80FF_00104B346232__INCLUDED_)

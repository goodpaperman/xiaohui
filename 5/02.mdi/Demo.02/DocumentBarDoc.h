// DocumentBarDoc.h : interface of the CDocumentBarDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DOCUMENTBARDOC_H__822331B0_F2C5_11D3_91A0_303D4FC10000__INCLUDED_)
#define AFX_DOCUMENTBARDOC_H__822331B0_F2C5_11D3_91A0_303D4FC10000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDocumentBarDoc : public CDocument
{
protected: // create from serialization only
	CDocumentBarDoc();
	DECLARE_DYNCREATE(CDocumentBarDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDocumentBarDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDocumentBarDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDocumentBarDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOCUMENTBARDOC_H__822331B0_F2C5_11D3_91A0_303D4FC10000__INCLUDED_)

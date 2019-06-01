// ReStartDoc.h : interface of the CReStartDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_RESTARTDOC_H__4A734420_EB5C_11D3_B07D_0050DAB826FF__INCLUDED_)
#define AFX_RESTARTDOC_H__4A734420_EB5C_11D3_B07D_0050DAB826FF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CReStartDoc : public CDocument
{
protected: // create from serialization only
	CReStartDoc();
	DECLARE_DYNCREATE(CReStartDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReStartDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CReStartDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CReStartDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RESTARTDOC_H__4A734420_EB5C_11D3_B07D_0050DAB826FF__INCLUDED_)

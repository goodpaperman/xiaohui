// DemoTBarDDoc.h : interface of the CDemoTBarDDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEMOTBARDDOC_H__DA7A8A0C_9921_11D2_ABA4_B4FFFFC00000__INCLUDED_)
#define AFX_DEMOTBARDDOC_H__DA7A8A0C_9921_11D2_ABA4_B4FFFFC00000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDemoTBarDDoc : public CDocument
{
protected: // create from serialization only
	CDemoTBarDDoc();
	DECLARE_DYNCREATE(CDemoTBarDDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemoTBarDDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDemoTBarDDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDemoTBarDDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMOTBARDDOC_H__DA7A8A0C_9921_11D2_ABA4_B4FFFFC00000__INCLUDED_)

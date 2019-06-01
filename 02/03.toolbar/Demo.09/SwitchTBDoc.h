// SwitchTBDoc.h : interface of the CSwitchTBDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SWITCHTBDOC_H__22E8407F_DBB1_11D2_9145_0060082BE95D__INCLUDED_)
#define AFX_SWITCHTBDOC_H__22E8407F_DBB1_11D2_9145_0060082BE95D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSwitchTBDoc : public CDocument
{
protected: // create from serialization only
	CSwitchTBDoc();
	DECLARE_DYNCREATE(CSwitchTBDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSwitchTBDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSwitchTBDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSwitchTBDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SWITCHTBDOC_H__22E8407F_DBB1_11D2_9145_0060082BE95D__INCLUDED_)

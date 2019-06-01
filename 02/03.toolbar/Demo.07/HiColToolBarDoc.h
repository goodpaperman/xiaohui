// HiColToolBarDoc.h : interface of the CHiColToolBarDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HICOLTOOLBARDOC_H__16F54469_1B11_11D2_BD39_00A0C945A10E__INCLUDED_)
#define AFX_HICOLTOOLBARDOC_H__16F54469_1B11_11D2_BD39_00A0C945A10E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CHiColToolBarDoc : public CDocument
{
protected: // create from serialization only
	CHiColToolBarDoc();
	DECLARE_DYNCREATE(CHiColToolBarDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHiColToolBarDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CHiColToolBarDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CHiColToolBarDoc)
	afx_msg void OnTest();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HICOLTOOLBARDOC_H__16F54469_1B11_11D2_BD39_00A0C945A10E__INCLUDED_)

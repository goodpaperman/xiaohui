// CustomMoreWindowsDoc.h : interface of the CCustomMoreWindowsDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CUSTOMMOREWINDOWSDOC_H__1E39FFF0_EC51_11D3_91A0_20314FC10000__INCLUDED_)
#define AFX_CUSTOMMOREWINDOWSDOC_H__1E39FFF0_EC51_11D3_91A0_20314FC10000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCustomMoreWindowsDoc : public CDocument
{
protected: // create from serialization only
	CCustomMoreWindowsDoc();
	DECLARE_DYNCREATE(CCustomMoreWindowsDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomMoreWindowsDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCustomMoreWindowsDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCustomMoreWindowsDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTOMMOREWINDOWSDOC_H__1E39FFF0_EC51_11D3_91A0_20314FC10000__INCLUDED_)

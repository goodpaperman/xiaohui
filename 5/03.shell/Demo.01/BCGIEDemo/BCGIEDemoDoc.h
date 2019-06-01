// BCGIEDemoDoc.h : interface of the CBCGIEDemoDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BCGIEDEMODOC_H__F83C8E11_F33E_11D2_A713_0090274409AC__INCLUDED_)
#define AFX_BCGIEDEMODOC_H__F83C8E11_F33E_11D2_A713_0090274409AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define FIRST_HISTORY_COMMAND	0x1000
#define HISTORY_LEN	10

#include "HistoryObj.h"

typedef CList<CHistoryObj*, CHistoryObj*> _T_HistotyList;

class CBCGIEDemoDoc : public CDocument
{
protected: // create from serialization only
	CBCGIEDemoDoc();
	DECLARE_DYNCREATE(CBCGIEDemoDoc)

// Attributes
public:
	CArray<CHistoryObj*, CHistoryObj*>	m_arHistory;
	int	m_iHistoryOffset;

// Operations
public:
	void GetBackList (_T_HistotyList& lst) const;
	void GetFrwdList (_T_HistotyList& lst) const;

	BOOL IsBackAvailable () const
	{
		return m_iHistoryOffset < m_arHistory.GetSize () - 1;
	}

	BOOL IsFrwdAvailable ()
	{
		return m_iHistoryOffset > 0;
	}

	CHistoryObj* GoBack ()
	{
		if (m_iHistoryOffset >= m_arHistory.GetSize ())
		{
			ASSERT (FALSE);
			return NULL;
		}

		return m_arHistory [++ m_iHistoryOffset];
	}

	CHistoryObj* GoForward ()
	{
		if (m_iHistoryOffset < 1)
		{
			ASSERT (FALSE);
			return NULL;
		}

		return m_arHistory [--m_iHistoryOffset];
	}

	CHistoryObj* Go (UINT uiCmd);
	CHistoryObj* AddURLToHistory (const CString& strTitle, const CString& strURL);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGIEDemoDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBCGIEDemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBCGIEDemoDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGIEDEMODOC_H__F83C8E11_F33E_11D2_A713_0090274409AC__INCLUDED_)

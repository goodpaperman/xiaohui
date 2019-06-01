//	AutoFillEdit Class
//
//  Copyright 2000 Softhor
//
//  Via Adige, 31 - 81100 CASERTA - Italy
//
//  Anybody can use this code or a part of it in every program,
//  commercial or not, without fee or royalty to pay.
//
//  Please don't modify this notice.

#if !defined(AFX_AFEDIT_H__0B514390_CADB_11D3_BD1E_0060520365FB__INCLUDED_)
#define AFX_AFEDIT_H__0B514390_CADB_11D3_BD1E_0060520365FB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// AFEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAFEdit window

class CAFEdit : public CEdit
{
// Construction
public:
	CAFEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAFEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	bool AddString( CString sString );
	virtual ~CAFEdit();

	// Generated message map functions
protected:
	CStringList m_strList;
	//{{AFX_MSG(CAFEdit)
	afx_msg void OnKillfocus();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AFEDIT_H__0B514390_CADB_11D3_BD1E_0060520365FB__INCLUDED_)

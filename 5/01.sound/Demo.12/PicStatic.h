#if !defined(AFX_PICSTATIC_H__8AAB83BF_274C_4503_BECB_6958ACA0CB5C__INCLUDED_)
#define AFX_PICSTATIC_H__8AAB83BF_274C_4503_BECB_6958ACA0CB5C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PicStatic.h : header file
//

#include "WriteAVI.h" 

/////////////////////////////////////////////////////////////////////////////
// CPicStatic window

class CPicStatic : public CStatic
{
// Construction
public:
	CPicStatic();

// Attributes
public:
    CDC m_dc; 
    CBitmap m_bmp; 
    CAVIFile m_avi; 

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPicStatic)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPicStatic();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPicStatic)
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PICSTATIC_H__8AAB83BF_274C_4503_BECB_6958ACA0CB5C__INCLUDED_)

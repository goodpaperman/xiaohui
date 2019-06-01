#if !defined(AFX_PROPTEST_H__12FBAFC3_996F_47B6_BCF6_45BCD8522AD6__INCLUDED_)
#define AFX_PROPTEST_H__12FBAFC3_996F_47B6_BCF6_45BCD8522AD6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PropTest.h : header file
//

#include "LBSpinButtonCtrl.h" 

/////////////////////////////////////////////////////////////////////////////
// CPropTest dialog

class CPropTest : public CPropertyPage
{
	DECLARE_DYNCREATE(CPropTest)

// Construction
public:
	CPropTest();
	~CPropTest();

// Dialog Data
	//{{AFX_DATA(CPropTest)
	enum { IDD = IDD_PROPPAGE1 };
    CLBSpinButtonCtrl m_spin; 
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPropTest)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPropTest)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPTEST_H__12FBAFC3_996F_47B6_BCF6_45BCD8522AD6__INCLUDED_)

// Demo2.h : header file

#if !defined(AFX_DEMO2_H__FB847020_6E52_11D2_B9A8_00104B138C8C__INCLUDED_)
#define AFX_DEMO2_H__FB847020_6E52_11D2_B9A8_00104B138C8C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "chhctrl\hhctrl.h"

/////////////////////////////////////////////////////////////////////////////
// Demo2 dialog

class Demo2 : public CDialog
{
public:
    Demo2(CWnd* pParent = NULL);   

    //{{AFX_DATA(Demo2)
    enum { IDD = IDD_DIALOG_DEMO2 };
    //}}AFX_DATA

    //{{AFX_VIRTUAL(Demo2)
	protected:
    virtual void DoDataExchange(CDataExchange* pDX);  
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

protected:
    CHHCtrl m_hhctrl;   // embedded help window control

    //{{AFX_MSG(Demo2)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMO2_H__FB847020_6E52_11D2_B9A8_00104B138C8C__INCLUDED_)

// KHDemoDlg.h : header file

#if !defined(AFX_KHDEMODLG_H__546F2505_6E43_11D2_B9A8_00104B138C8C__INCLUDED_)
#define AFX_KHDEMODLG_H__546F2505_6E43_11D2_B9A8_00104B138C8C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "chhctrl\hhctrl.h"

/////////////////////////////////////////////////////////////////////////////
// CKHDemoDlg dialog

#define HOVER_DELAY 500 // milliseconds before embedded help window changes

class CKHDemoDlg : public CDialog
{
public:
    CKHDemoDlg(CWnd* pParent = NULL);  
    ~CKHDemoDlg();

    //{{AFX_DATA(CKHDemoDlg)
    enum { IDD = IDD_KHDEMO_DIALOG };
    //}}AFX_DATA

    //{{AFX_VIRTUAL(CKHDemoDlg)
protected:
    virtual void DoDataExchange(CDataExchange* pDX);   
    //}}AFX_VIRTUAL

protected:
    HICON m_hIcon;
    CHHCtrl m_hhctrl;   // embedded help window control
    int  m_curHelpId;   // keep track of current mouse-over help id
    UINT m_timerHelpId; // current timer id

    //{{AFX_MSG(CKHDemoDlg)
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    afx_msg void OnCheck1();
    afx_msg void OnSetfocusEdit1();
    afx_msg void OnIntro();
    afx_msg void OnRadio1();
    afx_msg void OnRadio2();
    afx_msg void OnTimer(UINT nIDEvent);
    afx_msg void OnDestroy();
    afx_msg void OnButton1();
    //}}AFX_MSG
    LRESULT OnRelayEvent(WPARAM wParam, LPARAM lParam);

    DECLARE_MESSAGE_MAP()
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KHDEMODLG_H__546F2505_6E43_11D2_B9A8_00104B138C8C__INCLUDED_)

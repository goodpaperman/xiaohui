// Demo2.cpp : implementation file

#include "stdafx.h"
#include "khdemo.h"
#include "Demo2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static const char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Demo2 dialog

BEGIN_MESSAGE_MAP(Demo2, CDialog)
    //{{AFX_MSG_MAP(Demo2)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

Demo2::Demo2(CWnd* pParent /*=NULL*/) : CDialog(Demo2::IDD, pParent)
{
    //{{AFX_DATA_INIT(Demo2)
    //}}AFX_DATA_INIT
}

void Demo2::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(Demo2)
    //}}AFX_DATA_MAP
    if (!pDX->m_bSaveAndValidate) {
        if (m_hhctrl.SetChmFile("KhDemo.chm")) {
            m_hhctrl.ReplaceControl(this, 
                IDC_HHCTRL,                // the control we are replacing
                HHCTRL_BTN_HOME | HHCTRL_BTN_BACK | HHCTRL_BTN_FORWARD | HHCTRL_BTN_PRINT,
                (LPCTSTR) IDD_DIALOG_DEMO2,     // where the home button should go
                TRUE);                         // don't display button labels
            m_hhctrl.NavigateChm(IDD_DIALOG_DEMO2);
        }
    }
}

BOOL Demo2::OnCommand(WPARAM wParam, LPARAM lParam) 
{
    // We give m_hhctrl first crack at any WM_COMMAND messages in case they are
    // navigation bar commands

    m_hhctrl.OnCommand(LOWORD(wParam));
    
    return CDialog::OnCommand(wParam, lParam);
}

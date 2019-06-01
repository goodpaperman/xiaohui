/************************************ 

REVISION LOG ENTRY 

Revision By: Mihai Filimon 

Revised on 7/3/98 11:10:00 AM 

HiButton.cpp : implementation file 

************************************/ 


#include "stdafx.h" 

#include "btntest.h" 

#include "HiButton.h" 


#ifdef _DEBUG 

#define new DEBUG_NEW 

#undef THIS_FILE 

static char THIS_FILE[] = __FILE__; 

#endif 


///////////////////////////////////////////////////////////////////////////// 


// CHiButton 


// Function name : CHiButton::CHiButton 

// Description : Contructor 

// Return type : 

CHiButton::CHiButton() 

{ 
    
    m_bInsideButton = FALSE; 
    
} 


// Function name : CHiButton::~CHiButton 

// Description : Destructor 

// Return type : 

CHiButton::~CHiButton() 

{ 
    
} 



BEGIN_MESSAGE_MAP(CHiButton, CButton) 

//{{AFX_MSG_MAP(CHiButton) 

// NOTE - the ClassWizard will add and remove mapping macros here. 

//}}AFX_MSG_MAP 

END_MESSAGE_MAP() 


///////////////////////////////////////////////////////////////////////////// 


// CHiButton message handlers 


// Function name : CHiButton::PreSubclassWindow 

// Description : Subclass control 

// Return type : void 

void CHiButton::PreSubclassWindow() 

{ 
    
    CString caption; 
    
    GetWindowText(caption); 
    
    SetWindowText(_T("")); 
    
    CRect client; GetClientRect(client); 
    
    int dx = (int)((double)client.Width() * 0.8), dy = 
        
        (int)((double)client.Height() * 0.7); 
    
    m_wndButtonInside.Create(caption, WS_CHILD | WS_VISIBLE | GetStyle(), 
        
        CRect(CPoint((client.Width() - dx) / 2, (client.Height() - dy) / 
        
        2),CSize( dx, dy)), this, 0); 
    
    m_wndButtonInside.SetWindowPos(&CWnd::wndNoTopMost,0,0,0,0, SWP_NOMOVE 
        
        | SWP_NOSIZE); 
    
    ModifyStyle(0,WS_CLIPSIBLINGS | WS_CLIPCHILDREN); 
    
    m_wndButtonInside.SetFont(GetFont()); 
    
    CButton::PreSubclassWindow(); 
    
} 



// Function name : CHiButton::OnCommand 

// Description : Send WM_COMMAND to parent of button. 

// Return type : BOOL 

// Argument : WPARAM wParam 

// Argument : LPARAM lParam 

BOOL CHiButton::OnCommand(WPARAM wParam, LPARAM lParam) 

{ 
    
    m_bInsideButton = TRUE; 
    
    GetParent()->SendMessage(WM_COMMAND, 
        
        MAKEWPARAM(GetDlgCtrlID(),HIWORD(wParam)), lParam); 
    
    m_bInsideButton = FALSE; 
    
    
    return CButton::OnCommand(wParam, lParam); 
    
} 


// Function name : CHiButton::SetBitmap 

// Description : Call to set the bitmap image of inside button 

// Return type : HBITMAP 

// Argument : HBITMAP hBitmap 

HBITMAP CHiButton::SetBitmap( HBITMAP hBitmap ) 

{ 
    
    ASSERT(m_wndButtonInside.GetSafeHwnd()); 
    
    return m_wndButtonInside.SetBitmap(hBitmap); 
    
} 


// Function name : CHiButton::SetIcon 

// Description : Call to set the icon image of inside button 

// Return type : HICON 

// Argument : HICON hIcon 

HICON CHiButton::SetIcon( HICON hIcon ) 

{ 
    
    ASSERT(m_wndButtonInside.GetSafeHwnd()); 
    
    return m_wndButtonInside.SetIcon(hIcon); 
    
} 


// Function name : CHiButton::SetCursor 

// Description : 

// Return type : HICON 

// Argument : HCURSOR hCursor 

HCURSOR CHiButton::SetCursor( HCURSOR hCursor ) 

{ 
    
    ASSERT(m_wndButtonInside.GetSafeHwnd()); 
    
    return m_wndButtonInside.SetCursor(hCursor); 
    
} 

// KHDemoDlg.cpp : implementation file

// This module is used for installing and removing the mouse hook that is used
// in dialogs for hooking a mouse hover and click so that it will change the
// embedded help window content.

#include "stdafx.h"
#include "KHDemo.h"

//////////////////////////////////// Mouse Message Hook //////////////////////////////////////////////////

static LRESULT CALLBACK RelayMouseMsgHook(int nCode, WPARAM wParam, LPARAM lParam);

static HHOOK s_hkMouseMsg;
static HWND  s_hwndMouseMsgDlg;

bool SetMouseMsgHook(HWND hwndDlg)
{
    ASSERT(!s_hkMouseMsg);  // we only one hook at a time

    s_hkMouseMsg = SetWindowsHookEx(WH_GETMESSAGE, RelayMouseMsgHook, 
        (HINSTANCE) NULL, GetCurrentThreadId());
    if (s_hkMouseMsg) {
        s_hwndMouseMsgDlg = hwndDlg;
        return true;
    }
    else
        return false;
}

void RemoveMouseMsgHook()
{
    if (s_hkMouseMsg) {
        UnhookWindowsHookEx(s_hkMouseMsg);
        s_hkMouseMsg = NULL;
    }
}

static LRESULT CALLBACK RelayMouseMsgHook(int nCode, WPARAM wParam, LPARAM lParam) 
{ 
    MSG* pmsg = (MSG*) lParam; 
 
    if (nCode < 0 || !(IsChild(s_hwndMouseMsgDlg, pmsg->hwnd))) 
        return CallNextHookEx(s_hkMouseMsg, nCode, wParam, lParam); 
 
    switch (pmsg->message) { 
        case WM_MOUSEMOVE: 
        case WM_LBUTTONDOWN: 
        case WM_LBUTTONUP: 
        case WM_RBUTTONDOWN: 
        case WM_RBUTTONUP: 
            { 
                SendMessage(s_hwndMouseMsgDlg, TTM_RELAYEVENT, 0, (LPARAM) pmsg);
            } 
            break; 

        default: 
            break; 
    } 
    return CallNextHookEx(s_hkMouseMsg, nCode, wParam, lParam); 
} 

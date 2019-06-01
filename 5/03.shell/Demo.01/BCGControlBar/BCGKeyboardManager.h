// BCGKeyboardManager.h: interface for the CBCGKeyboardManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BCGKEYBOARDMANAGER_H__916B7A45_556A_11D2_B110_FD3F2C81B152__INCLUDED_)
#define AFX_BCGKEYBOARDMANAGER_H__916B7A45_556A_11D2_B110_FD3F2C81B152__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "bcgcontrolbar.h"

class BCGCONTROLBARDLLEXPORT CBCGKeyboardManager
{
// Constructor/Destructor:
public:
	CBCGKeyboardManager();
	virtual ~CBCGKeyboardManager();

// Operattion:
public:
	BOOL LoadState (LPCTSTR lpszProfileName);
	BOOL SaveState (LPCTSTR lpszProfileName);

	BOOL UpdateAcellTable (CMultiDocTemplate* pTemplate, LPACCEL lpAccel, int nSize);
	BOOL UpdateAcellTable (CMultiDocTemplate* pTemplate, HACCEL hAccelNew);

	void ResetAll ();

	static BOOL FindDefaultAccelerator (UINT uiCmd, CString& str, CFrameWnd* pWndFrame);

protected:
	BOOL SaveAccelaratorState (LPCTSTR lpszProfileName,
		UINT uiResId, HACCEL hAccelTable);
	BOOL LoadAccelaratorState (LPCTSTR lpszProfileName, 
		UINT uiResId, HACCEL& hAccelTable);
};

extern CBCGKeyboardManager*	g_pKeyboardManager;

#endif // !defined(AFX_BCGKEYBOARDMANAGER_H__916B7A45_556A_11D2_B110_FD3F2C81B152__INCLUDED_)

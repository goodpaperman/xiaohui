/////////////////////////////////////////////////////////////////////////////
// Copyright (C) 1999 by Jens Schacherl (16.09.1999)
// All rights reserved.
//
// This is free source code and you are allowed to use it even in your
// billion-dollar-application as long as you leave this copyright notice
// unchanged.
//
// No warranty of any kind, expressed or implied, is included with this
// software. Any responsibility for damages, loss of money or hair etc. rests
// entirely with the prospective user.
// Have fun but use it at your own risk.
//
// Mail me your thoughts to:	schacherl@spiess.com (preferred) or
//								jschacherl@csi.com		
//		
/////////////////////////////////////////////////////////////////////////////

// AVICtrl.h : header file
//

#if !defined(AFX_AVICTRL_H__5EC9E0F0_52F0_11D3_AE13_000000000000__INCLUDED_)
#define AFX_AVICTRL_H__5EC9E0F0_52F0_11D3_AE13_000000000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


// load flags
#define AVC_HALFSPEED			0x0000001 // plays video with half speed
#define AVC_DOUBLESPEED			0x0000002 // plays video with double speed

#define AVC_CENTERAVI			0x0000004 // centers video inside the window
#define AVC_STRETCHAVI			0x0000008 // stretches video to fit inside of the window
#define AVC_CENTERRECT			0x0000010 // resizes window, center point stays the same

#define AVC_AUTOPLAY			0x0000020 // starts playing automatically after Load()

#define AVC_MAPWINDOWCOLOR		0x0000040 // background is COLOR_WINDOW instead of transparent (like CAnimateCtrl's AVS_"TRANSPARENT")
#define AVC_FIRSTPIXTRANSPRNT	0x0000080 // ignore clrTransparent parameter and use color of firstframes first pixel for transparency

// colors
#define BLACK				RGB(0, 0, 0)
#define WHITE				RGB(255, 255, 255)
#define LTGREEN				RGB(0, 255, 0)

// timer
#define ID_TIMER			111

// identifier for avi resources
#define RT_AVIVIDEO			_T("AVI")

#include "vfw.h"

/////////////////////////////////////////////////////////////////////////////
// CAVICtrl window

class CAVICtrl : public CWnd
{
// Construction
public:
	CAVICtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAVICtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	HRESULT Load(UINT nIDResource, DWORD dwFlags = 0L, COLORREF clrTransparent = LTGREEN);
	HRESULT Load(LPCTSTR lpszFile, DWORD dwFlags = 0L, COLORREF clrTransparent = LTGREEN);

	void ReinitBackground() { m_bInitBkg = TRUE; };

	BOOL Play(BOOL bOnce = FALSE);
	BOOL Stop(BOOL bResetToFirst = FALSE);
	void Seek(UINT nTo);	
	BOOL IsPlaying() { return m_bPlaying; };

	virtual ~CAVICtrl();

	// Generated message map functions
protected:
	CString GetTempAVIFileName();
	COLORREF GetFirstPixelColor();
	void InitBackground();
	void DrawTransparent(int x, int y, int nWidth, int nHeight, CDC* pSrcDC, CDC* pDstDC);
	void DrawCurrentFrame(CDC* pDC);
	static void CALLBACK PlayTimer(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);
	//{{AFX_MSG(CAVICtrl)
	afx_msg void OnWindowPosChanging(WINDOWPOS FAR* lpwndpos);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSysColorChange();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void CtrlDestroy();
	void CtrlInit();

	DWORD m_dwFlags;
	CString m_csTempFile;
	int m_nRealHeight;
	int m_nRealWidth;
	int m_nAVIOffsetY;
	int m_nAVIOffsetX;
	BOOL m_bOnce;
	BOOL m_bInitBkg;
	CBitmap* m_pbmpBkgOld;
	CBitmap m_bmpBkg;
	CDC m_dcBkg;
	COLORREF m_clrTransp;
	HDRAWDIB m_hDrawDib;
	UINT m_nTimerTime;
	LONG m_lFrames;
	UINT m_nCurrentFrame;
	PGETFRAME m_pGF;
	BOOL m_bPlaying;
	PAVISTREAM m_pAS;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AVICTRL_H__5EC9E0F0_52F0_11D3_AE13_000000000000__INCLUDED_)

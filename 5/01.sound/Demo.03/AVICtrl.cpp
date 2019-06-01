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

// AVICtrl.cpp : implementation file
//

#include "stdafx.h"
#include "AVICtrl.h"

#include <io.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// pointer to use in static member
//CAVICtrl* pThis = NULL;

/////////////////////////////////////////////////////////////////////////////
// CAVICtrl

CAVICtrl::CAVICtrl()
{
	// initialize members
	CtrlInit();

	// open avi library
	AVIFileInit();

	// open draw lib
	m_hDrawDib = DrawDibOpen();
	_ASSERTE(m_hDrawDib);

	// pointer used in static memberfunc PlayTimer
	//pThis = this;
}

CAVICtrl::~CAVICtrl()
{
	CtrlDestroy();
	
	// close drawing library
	if (m_hDrawDib)
	{
		DrawDibClose(m_hDrawDib);
	}

	// close avi library
	AVIFileExit();
}


BEGIN_MESSAGE_MAP(CAVICtrl, CWnd)
	//{{AFX_MSG_MAP(CAVICtrl)
	ON_WM_WINDOWPOSCHANGING()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_SYSCOLORCHANGE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CAVICtrl public members
HRESULT CAVICtrl::Load(UINT nIDResource, DWORD dwFlags, COLORREF clrTransparent)
{
	HRSRC hRes;
	HGLOBAL hMem;
	DWORD dwSizeRes;
	LPVOID lpData;

	// pls subclass *before* loading
	if (!::IsWindow(m_hWnd))
	{
		return E_FAIL;
	}

	if (m_pAS)
	{
		// control has been used before: reinitialize everything
		CtrlDestroy();
		CtrlInit();
	}

	// find & load our avi resource
	hRes = ::FindResource(AfxGetResourceHandle(), MAKEINTRESOURCE(nIDResource), RT_AVIVIDEO);
	if (!hRes)
	{
		TRACE("FindRes error=%lu\n", GetLastError());
		return E_FAIL;
	}

	hMem = ::LoadResource(AfxGetResourceHandle(), hRes);
	_ASSERTE(hMem);
	dwSizeRes = ::SizeofResource(AfxGetResourceHandle(), hRes);
	_ASSERTE(dwSizeRes > 0L);
	
	lpData = ::LockResource(hMem);
	_ASSERTE(lpData);

	// create temp file
	_ASSERTE(m_csTempFile.IsEmpty());

	//VERIFY(GetTempPath(_MAX_PATH, szTempDir));
	//VERIFY(GetTempFileName(szTempDir, _T("AVC"), 0, m_csTempFile.GetBuffer(_MAX_PATH)));
	//m_csTempFile.ReleaseBuffer();
	m_csTempFile = GetTempAVIFileName();
	_ASSERTE(!m_csTempFile.IsEmpty());

	// for NT it's ok, but stupid Win98 cannot open the file if the extension is not AVI
	/*CString sNewName(m_csTempFile);
	sNewName.Replace(".TMP", ".AVI");
	_trename(m_csTempFile, sNewName);
	m_csTempFile = sNewName;*/

	// open temp file and write avi data to it
	CFile tmpFile;

	if (!tmpFile.Open(m_csTempFile, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyWrite))
	{
		TRACE("Failed opening temp file\n");
		return E_FAIL;
	}
	
	TRY
	{
		tmpFile.Write(lpData, dwSizeRes);
	}
	CATCH(CFileException, e)
	{
		TRACE("Failed writing temp file: %d\n", e->m_cause);
		tmpFile.Close();

		return E_FAIL;
	}
	END_CATCH

	tmpFile.Close();

	// OLH to Unlock-/FreeResource says that they are obsolete, but most of the
	// Win32 samples still use them...so what?
	// Anyway they are redefined as dummies in AFXV_W32.H so it makes no sense calling them.
	//::UnlockResource(hMem);
	//::FreeResource(hMem);

	return Load(m_csTempFile, dwFlags, clrTransparent);
}


HRESULT CAVICtrl::Load(LPCTSTR lpszFile, DWORD dwFlags, COLORREF clrTransparent)
{
	// pls subclass *before* loading
	if (!::IsWindow(m_hWnd))
	{
		return E_FAIL;
	}

	if (m_pAS)
	{
		// control has been used before: reinitialize everything
		CtrlDestroy();
		CtrlInit();
	}

	HRESULT hr;

	// open AVI
	hr = AVIStreamOpenFromFile(&m_pAS, lpszFile, streamtypeVIDEO,
								 0, OF_READ|OF_SHARE_EXCLUSIVE, NULL);
	if (FAILED(hr))
	{
		m_pAS = NULL;
        //USHORT sc = (USHORT)hr; 
		return hr;
	}

	//set flags and color
	m_dwFlags = dwFlags;
	m_clrTransp = clrTransparent;

	// open frames
	_ASSERTE(m_pAS);
	m_pGF = AVIStreamGetFrameOpen(m_pAS, NULL);
	_ASSERTE(m_pGF);

	// get number of frames
	m_lFrames = AVIStreamLength(m_pAS);
	_ASSERTE(m_lFrames > 0);

	// calculate timer delay
	LONG lLTime = AVIStreamEndTime(m_pAS);
	_ASSERTE(lLTime > 0);
	m_nTimerTime = (UINT)(lLTime / m_lFrames);
	if (m_dwFlags & AVC_HALFSPEED)
	{
		m_nTimerTime *= 2;
	}
	else if (m_dwFlags & AVC_DOUBLESPEED)
	{
		m_nTimerTime /= 2;
	}

	// get size of control
	CRect rcCtrl;
	GetClientRect(&rcCtrl);

	// get size of avi
	AVISTREAMINFO si;
	AVIStreamInfo(m_pAS, &si, sizeof(si));

	// precalculate some often needed values in case we need them later
	int nWidth = si.rcFrame.right-si.rcFrame.left;
	int nHeight = si.rcFrame.bottom - si.rcFrame.top;
	int nOfsX = ((rcCtrl.Width() > nWidth) ? ((rcCtrl.Width() - nWidth) / 2) : 0);
	int nOfsY = ((rcCtrl.Height() > nHeight) ? ((rcCtrl.Height() - nHeight)) / 2 : 0);
	
	// this is true if we stretch the avi or resize the control window
	m_nRealWidth = rcCtrl.Width();
	m_nRealHeight = rcCtrl.Height();

	if (m_dwFlags & AVC_CENTERAVI)
	{
		m_nAVIOffsetX = nOfsX;
		m_nAVIOffsetY = nOfsY;

		//special case: different size of ctrl and avi
		m_nRealWidth = nWidth;
		m_nRealHeight = nHeight;
	}
	else if (!(m_dwFlags & AVC_STRETCHAVI))
	{
		VERIFY(SetWindowPos(NULL, -1, -1, nWidth, nHeight, SWP_NOMOVE|SWP_NOZORDER|SWP_NOREDRAW|SWP_NOACTIVATE));
		m_nRealWidth = nWidth;
		m_nRealHeight = nHeight;

		if (m_dwFlags & AVC_CENTERRECT)
		{
			// calculate ctrl postion relative to parent and move it
			CRect rcWnd;
			GetWindowRect(&rcWnd);

			CWnd* pParent = GetParent();
			_ASSERTE(pParent);
			if (pParent)
			{
				pParent->ScreenToClient(&rcWnd);
				rcWnd.OffsetRect(nOfsX, nOfsY);
				MoveWindow(rcWnd, FALSE);
			}
		}
	}

	// not transparent
	if (m_dwFlags & AVC_MAPWINDOWCOLOR)
	{
		CClientDC dcCtrl(this);

		m_dcBkg.CreateCompatibleDC(&dcCtrl);
		m_bmpBkg.CreateCompatibleBitmap(&dcCtrl, rcCtrl.Width(), rcCtrl.Height());
		m_pbmpBkgOld = m_dcBkg.SelectObject(&m_bmpBkg);
		m_dcBkg.FillSolidRect(&rcCtrl, ::GetSysColor(COLOR_WINDOW));
	}
	else if (m_dwFlags & AVC_FIRSTPIXTRANSPRNT)
	{
		m_clrTransp = GetFirstPixelColor();
	}

	// autoplay?
	if (m_dwFlags & AVC_AUTOPLAY)
	{
		VERIFY(Play());
	}

	return hr;
}

BOOL CAVICtrl::Play(BOOL bOnce)
{
	if (!m_pAS)
	{
		return FALSE;
	}

	// set flag
	m_bOnce = bOnce;

	if (m_bPlaying)
	{
		// reset frame to first and exit
		m_nCurrentFrame = 0;
		return FALSE;
	}

	// draw current (first) frame
	Invalidate();

	// set timer
	VERIFY(::SetTimer(GetSafeHwnd(), ID_TIMER, m_nTimerTime, (TIMERPROC)PlayTimer));

	// flags
	m_bPlaying = TRUE;

	return TRUE;
}


BOOL CAVICtrl::Stop(BOOL bResetToFirst)
{
	// reset even if not playing
	if (bResetToFirst)
	{
		m_nCurrentFrame = 0;
		if (::IsWindow(m_hWnd))
		{
			Invalidate();
		}
	}

	if (!m_bPlaying)
	{
		return TRUE;
	}

	// stop playing
	VERIFY(::KillTimer(GetSafeHwnd(), ID_TIMER));

	m_bPlaying = FALSE;

	return TRUE;
}


void CAVICtrl::Seek(UINT nTo)
{
	if (m_bPlaying)
	{
		Stop();
	}

	m_nCurrentFrame = __max(nTo, (UINT)m_lFrames);
	Invalidate();
}


/////////////////////////////////////////////////////////////////////////////
// CAVICtrl message handlers

void CAVICtrl::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	if (m_pAS)
	{
		DrawCurrentFrame(&dc);	
	}
}


BOOL CAVICtrl::OnEraseBkgnd(CDC*) 
{
	// if needed, get new background
	if (m_bInitBkg)
	{
		m_bInitBkg = FALSE;
		InitBackground();
	}

	// do nothing else here
	// it would cause too much flicker if we'd restore the background here
	return TRUE;
}


void CAVICtrl::OnWindowPosChanging(WINDOWPOS FAR* lpwndpos) 
{
	if (!(lpwndpos->flags & (SWP_HIDEWINDOW | SWP_SHOWWINDOW)))
	{
		m_bInitBkg = TRUE;
	}
	
	CWnd::OnWindowPosChanging(lpwndpos);
}


void CAVICtrl::OnSysColorChange() 
{
	CWnd::OnSysColorChange();
	
	if (m_dcBkg.m_hDC && (m_dwFlags & AVC_MAPWINDOWCOLOR))
	{
		CRect rcCtrl;

		GetClientRect(&rcCtrl);
		m_dcBkg.FillSolidRect(&rcCtrl, ::GetSysColor(COLOR_WINDOW));
	}
}


void CAVICtrl::OnDestroy()
{
	Stop();
}


void CALLBACK CAVICtrl::PlayTimer(HWND hWnd, UINT, UINT, DWORD)
{
	CAVICtrl* pThis = (CAVICtrl*)CWnd::FromHandle(hWnd);
	_ASSERTE(pThis);
	if (pThis == NULL)
	{
		return;
	}

	if (++pThis->m_nCurrentFrame >= (UINT)pThis->m_lFrames)
	{
		pThis->m_nCurrentFrame = 0;

		if (pThis->m_bOnce)
		{
			pThis->Stop(TRUE);
			return;
		}
	}

	pThis->Invalidate();
}

/////////////////////////////////////////////////////////////////////////////
// CAVICtrl protected members

void CAVICtrl::DrawCurrentFrame(CDC *pDC)
{
	LPBITMAPINFOHEADER lpBi;
	CRect rcClip;

	GetClientRect(&rcClip);

	lpBi = (LPBITMAPINFOHEADER)AVIStreamGetFrame(m_pGF, (LONG)m_nCurrentFrame);
	_ASSERTE(lpBi);
	if (lpBi)
	{
		// create compatible dc & bitmap
		CDC dcComp;
		CBitmap bmp, *bmpOld;

		dcComp.CreateCompatibleDC(pDC);
		bmp.CreateCompatibleBitmap(pDC, rcClip.Width(), rcClip.Height());
		bmpOld = dcComp.SelectObject(&bmp);

		// again, this is only for dumb Win95/98 :-(
		// initialize background of compatible dc
		dcComp.BitBlt(0, 0, rcClip.Width(), rcClip.Height(), &m_dcBkg, 0, 0, SRCCOPY);

		// draw into comp dc
		VERIFY(DrawDibDraw(m_hDrawDib, dcComp.GetSafeHdc(), rcClip.left+m_nAVIOffsetX, rcClip.top+m_nAVIOffsetY,
						   m_nRealWidth, m_nRealHeight, lpBi, NULL,
						   0, 0, -1, -1, 0));

		// draw transparently to screen
		DrawTransparent(rcClip.left, rcClip.top,
						rcClip.Width(), rcClip.Height(), &dcComp, pDC);

		dcComp.SelectObject(bmpOld);
	}
}


void CAVICtrl::DrawTransparent(int x, int y, int nWidth, int nHeight, CDC *pSrcDC, CDC *pDstDC)
{
	CDC maskDC, memDC;
	CBitmap maskBmp, *pOldMaskBmp, memBmp, *pOldMemBmp;


	maskDC.CreateCompatibleDC(pSrcDC);
	maskBmp.CreateBitmap(nWidth, nHeight, 1, 1, NULL);
	pOldMaskBmp = maskDC.SelectObject(&maskBmp);

	memDC.CreateCompatibleDC(pDstDC);
	memBmp.CreateCompatibleBitmap(pDstDC, nWidth, nHeight);
	pOldMemBmp = memDC.SelectObject(&memBmp);

	memDC.BitBlt(0, 0, nWidth, nHeight, &m_dcBkg, 0, 0, SRCCOPY);

	pSrcDC->SetBkColor(m_clrTransp);
	maskDC.BitBlt(m_nAVIOffsetX, m_nAVIOffsetY, m_nRealWidth, m_nRealHeight, pSrcDC, m_nAVIOffsetX, m_nAVIOffsetY, SRCCOPY);

	pSrcDC->SetBkColor(BLACK);
	pSrcDC->SetTextColor(WHITE);
	pSrcDC->BitBlt(m_nAVIOffsetX, m_nAVIOffsetY, nWidth, nHeight, &maskDC, m_nAVIOffsetX, m_nAVIOffsetY, SRCAND);

	memDC.SetBkColor(WHITE);
	memDC.SetTextColor(BLACK);
	memDC.BitBlt(m_nAVIOffsetX, m_nAVIOffsetY, m_nRealWidth, m_nRealHeight, &maskDC, m_nAVIOffsetX, m_nAVIOffsetY, SRCAND);
	memDC.BitBlt(0, 0, nWidth, nHeight, pSrcDC, 0, 0, SRCPAINT);

	pDstDC->BitBlt(x, y, nWidth, nHeight, &memDC, 0, 0, SRCCOPY);

	memDC.SelectObject(pOldMemBmp);
	maskDC.SelectObject(pOldMaskBmp);
}


void CAVICtrl::InitBackground()
{
	if (!m_pAS || m_dwFlags & AVC_MAPWINDOWCOLOR)
	{
		return;
	}

	CWnd* pParentWnd;
	CRect rcAVIWnd, rcParent;

	// init
	pParentWnd = GetParent();
	_ASSERTE(pParentWnd);
	if (!pParentWnd)
	{
		return;
	}

	// calculate position of control in parent
	GetWindowRect(&rcAVIWnd);

    //// border moves window later, so we move it here too
    if (GetExStyle() & (WS_EX_CLIENTEDGE|WS_EX_DLGMODALFRAME))
    {
        rcAVIWnd.OffsetRect(GetSystemMetrics(SM_CXEDGE),GetSystemMetrics(SM_CYEDGE));
    }
    else if(GetStyle() & WS_BORDER)
    {
        rcAVIWnd.OffsetRect(GetSystemMetrics(SM_CXBORDER), GetSystemMetrics(SM_CYBORDER));
    }

	rcParent = rcAVIWnd;
	pParentWnd->ScreenToClient(&rcParent);
	GetClientRect(&rcAVIWnd); // recycle this rect...

	// get parents dc
	CClientDC dcParent(pParentWnd);

	// cleanup old dc & bmp if exist
	if (m_pbmpBkgOld)
	{
		m_dcBkg.SelectObject(m_pbmpBkgOld);
		m_dcBkg.DeleteDC();
		m_bmpBkg.DeleteObject();
	}

	// get parent image from behind control
	m_dcBkg.CreateCompatibleDC(&dcParent);
	m_bmpBkg.CreateCompatibleBitmap(&dcParent, rcAVIWnd.Width(), rcAVIWnd.Height());
	m_pbmpBkgOld = m_dcBkg.SelectObject(&m_bmpBkg);
	_ASSERTE(m_pbmpBkgOld != NULL);

	//ShowWindow(SW_HIDE);
	m_dcBkg.BitBlt(rcAVIWnd.left, rcAVIWnd.top, rcAVIWnd.Width(), rcAVIWnd.Height(),
				   &dcParent, rcParent.left, rcParent.top, SRCCOPY);
	//ShowWindow(SW_RESTORE);
}


COLORREF CAVICtrl::GetFirstPixelColor()
{
	_ASSERTE(m_pAS);
	_ASSERTE(m_pGF);

	LPBITMAPINFO lpbi;

	// fetch first frame
	lpbi = (LPBITMAPINFO)AVIStreamGetFrame(m_pGF, 0);
	_ASSERTE(lpbi);

	// currently works only with 8bit-BMPs
	if (!lpbi || lpbi->bmiHeader.biBitCount != 8)
	{
		return LTGREEN;
	}
	
	// get first pixel and use as index in the color table
	LPBYTE lpbyIndex = (LPBYTE)((DWORD)lpbi + lpbi->bmiHeader.biSize + (lpbi->bmiHeader.biClrUsed*sizeof(RGBQUAD)));
	RGBQUAD* pRGBFirst = (RGBQUAD*)(&lpbi->bmiColors[*lpbyIndex]);

	return RGB(pRGBFirst->rgbRed, pRGBFirst->rgbGreen, pRGBFirst->rgbBlue);
}


CString CAVICtrl::GetTempAVIFileName()
{
	CString sTempDir, sTempFile, sRet;

	VERIFY(GetTempPath(_MAX_PATH, sTempDir.GetBuffer(_MAX_PATH+1)));
	sTempDir.ReleaseBuffer();
	_ASSERTE(!sTempDir.IsEmpty());

	// make sure to create unique filename
	do
	{
		sTempFile.Format("AVC%X.AVI", GetTickCount());
		Sleep(100);
		sRet = sTempDir + sTempFile;
	}
	while (_taccess(sRet, 0) == 0);

	return sRet;
}
/////////////////////////////////////////////////////////////////////////////
// CAVICtrl private helper functions
void CAVICtrl::CtrlInit()
{
	m_pAS = NULL;
	m_pGF = NULL;
	m_pbmpBkgOld = NULL;
	m_nCurrentFrame = 0;
	m_nAVIOffsetX = m_nAVIOffsetY = 0;
	m_bPlaying = FALSE;
	m_bInitBkg = TRUE;
}

void CAVICtrl::CtrlDestroy()
{
	// still running?
	if (m_bPlaying)
	{
		Stop();
	}

	// close frame interface
	if (m_pGF)
	{
		VERIFY(AVIStreamGetFrameClose(m_pGF) == NOERROR);
		m_pGF = NULL;
	}

	// release avi stream
	if (m_pAS)
	{
		AVIStreamRelease(m_pAS);
	}

	// select previous bitmap before dc is destroyed
	if (m_pbmpBkgOld)
	{
		m_dcBkg.SelectObject(m_pbmpBkgOld);
	}

	// delete dc and bitmap
	if (m_dcBkg.m_hDC)
	{
		VERIFY(m_dcBkg.DeleteDC());
	}
	if (m_bmpBkg.m_hObject)
	{
		VERIFY(m_bmpBkg.DeleteObject());
	}

	// delete temp file if exist
	if (!m_csTempFile.IsEmpty())
	{
		VERIFY(DeleteFile(m_csTempFile));
		m_csTempFile.Empty();
	}
}



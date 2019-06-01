#include "Headers.h"
#include "resource.h"
#include "KoulesWin.h"
#include "ksrc\koules.h"
#include "ksrc\interface.h"
#include "ksrc\input.h"
#include "directdrawapp.h"

#pragma comment (lib,"ddraw.lib")
#pragma comment (lib,"dxguid.lib")


const DWORD desiredwidth=800;
const DWORD desiredheight=600;
const DWORD desireddepth=8;


BEGIN_MESSAGE_MAP(KoulesWin, DirectDrawWin)
	//{{AFX_MSG_MAP(KoulesWin)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_COMMAND(ID_APP_EXIT, OnAppExit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


KoulesWin::KoulesWin()
{
	for(int i=0;i<4;i++)
		m_key[i]=0;
	m_tc=0;
	m_pc=0;
	m_fps=0;
}

BOOL KoulesWin::CreateCustomSurfaces()
{
	// create your surfaces here...
	return TRUE;
}

void KoulesWin::DrawScene()
{
	static DWORD NewClk=0;
	static DWORD LastClk=0;
	
	NewClk=timeGetTime();
	if( (NewClk-LastClk) < 35)//30ms
		return;
	LastClk=timeGetTime();

	ClearSurface( backsurf, 0 );
	SetScreen(backsurf);
	gameloop();
	HDC dc;
	backsurf->GetDC(&dc);
	CDC *pDC=CDC::FromHandle(dc);
	pDC->SetTextColor(RGB(255,255,255));
	pDC->SetBkMode(TRANSPARENT);
	DrawFPS(pDC);
	backsurf->ReleaseDC(dc);
	m_pc++;
	primsurf->Flip( 0, DDFLIP_WAIT );
}

void KoulesWin::RestoreSurfaces()
{
	::Restore();//reload surface Restore define in koules.cpp
}

int KoulesWin::SelectInitialDisplayMode()
{
	DWORD curdepth=GetDisplayDepth();
	int i, nummodes=GetNumDisplayModes();
	DWORD w,h,d;

	if (curdepth!=desireddepth)
		ddraw2->SetDisplayMode( 640, 480, curdepth, 0, 0 );

	for (i=0;i<nummodes;i++)
	{
		GetDisplayModeDimensions( i, w, h, d );
		if (w==desiredwidth && h==desiredheight && d==desireddepth)
			return i;
	}

	for (i=0;i<nummodes;i++)
	{
		GetDisplayModeDimensions( i, w, h, d );
		if (d==desireddepth)
			return i;
	}
	return 0;
}

int KoulesWin::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (DirectDrawWin::OnCreate(lpCreateStruct) == -1)
		return -1;
	SetTimer(2,500,NULL);
	ClearSurface(primsurf,0,NULL);
	HDC dc;
	CString str="Loading .........";
	CSize sz;	
	primsurf->GetDC(&dc);
	CDC *pDC=CDC::FromHandle(dc);
	pDC->SetTextColor(RGB(255,255,255));
	pDC->SetBkMode(TRANSPARENT);
	sz=pDC->GetTextExtent(str);
	pDC->TextOut((GetDisplayRect().Width()-sz.cx)/2,
		(GetDisplayRect().Height()-sz.cy)/2,str);	
	primsurf->ReleaseDC(dc);
	gameinit();
	return 0;
}

void KoulesWin::DrawFPS(CDC * pDC)
{
	CString s;
	s.Format("FPS:%3d/Sec",m_fps);
	pDC->SetTextColor(RGB(255,255,255));
	pDC->TextOut(600,450,s);
}

void KoulesWin::OnTimer(UINT nIDEvent) 
{
	m_fps=m_pc*2;
	m_pc=0;
	DirectDrawWin::OnTimer(nIDEvent);
}

void KoulesWin::OnAppExit() 
{
	((DirectDrawApp*)AfxGetApp())->Exit();
}

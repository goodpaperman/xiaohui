// JumpyDraw.cpp : implementation file
//
// JumpyDraw is a animated static control control. Check out the 
// header file or the accompanying HTML doc file for details.
//
// Written by Fabian Toader (Fabi Pantera) (fabian_toader@hotmail.com)
// Copyright (c) 1999.
//
// This code may be used in compiled form in any way you desire. This
// file may be redistributed unmodified by any means PROVIDING it is 
// not sold for profit without the authors written consent, and 
// providing that this notice and the authors name is included. If 
// the source code in  this file is used in any commercial application 
// then a simple email would be nice.
//
// This file is provided "as is" with no expressed or implied warranty.
// The author accepts no liability if it causes any damage to your
// computer, causes your pet cat to fall ill, increases baldness or
// makes you car start emitting strange noises when you start it up.
//
// Expect bugs.
// 
// Please use and enjoy. Please let me know of any bugs/mods/improvements 
// that you have found/implemented and I will fix/incorporate them into this
// file. 
//

#include "stdafx.h"
#include "JumpyDraw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ID_JUMPY_REFRESH_DRAW WM_USER+1286 //the timer ID
const int LINEAR_WASH_SEGMENTS = 60; //used in the gradient function
/////////////////////////////////////////////////////////////////////////////
// CJumpyDraw

CJumpyDraw::CJumpyDraw()
{
	//default text goes here
	mstrJumpy = mstrActualText = "The quick brown fox jumps over the lazy dog. 1234567890";
	//default time period goes here
	mnTime = 1000;
	//default font name goes here
	mstrFont = "MS Sans Serif";
	//default char height goes here
	mnCharHeight = 24;
	//default text color goes here
	mTextColor = RGB(0, 255, 0);
	//default gradient colors goes here
	mGradientColorStart = RGB(123, 158, 198);
	mGradientColorEnd = RGB(0, 0, 255);
	//default shaddow color goes here
	mShaddowColor = RGB(0,0,0);
	mnIndexAleator = -1;
	mFontDummy.CreateFont(mnCharHeight, 0, 0, 0, 0,//nIsBold, 
		FALSE, //bIsItalic, 
		FALSE, //bIsUnderline, 
		0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
						 DEFAULT_QUALITY, DEFAULT_PITCH, mstrFont);
}

CJumpyDraw::~CJumpyDraw()
{
	mFontDummy.DeleteObject();
}


BEGIN_MESSAGE_MAP(CJumpyDraw, CStatic)
	//{{AFX_MSG_MAP(CJumpyDraw)
	ON_WM_TIMER()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJumpyDraw message handlers


//jumpy text function. Render the text using its parameters 
void CJumpyDraw::StartJumpyText(CString strJump, DWORD nTime, CString strFont, int nHeight, 
		COLORREF TextColor,	COLORREF ShaddowColor,
		COLORREF GradientColorStart,  
		COLORREF GradientColorEnd)

{
	CFont fontDummy;
	fontDummy.CreateFont(nHeight, 0, 0, 0, 0,//nIsBold, 
		FALSE, //bIsItalic, 
		FALSE, //bIsUnderline, 
		0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
						 DEFAULT_QUALITY, DEFAULT_PITCH, strFont);
	//set the new params
	mTextColor = TextColor;
	mGradientColorStart = GradientColorStart;
	mGradientColorEnd = GradientColorEnd;
	mShaddowColor = ShaddowColor;
	mFontDummy.DeleteObject();
	mFontDummy.Attach(fontDummy.Detach());
	SetFont(&mFontDummy);
	mstrJumpy = strJump;
	mnIndexAleator = -1;
	int nLenght = strJump.GetLength();
	mstrActualText = mstrJumpy;
	//start rendering
	KillTimer(ID_JUMPY_REFRESH_DRAW);
	SetTimer(ID_JUMPY_REFRESH_DRAW, (int)(nTime/nLenght), NULL);
}

//start jumpy function without parms. It use some default params which has been previously set
void CJumpyDraw::StartJumpyText()
{
	//set the font
	CFont fontDummy;
	fontDummy.CreateFont(mnCharHeight, 0, 0, 0, 0,//nIsBold, 
		FALSE, //bIsItalic, 
		FALSE, //bIsUnderline, 
		0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
						 DEFAULT_QUALITY, DEFAULT_PITCH, mstrFont);
	mFontDummy.DeleteObject();
	mFontDummy.Attach(fontDummy.Detach());
	SetFont(&mFontDummy);
	int nLenght = mstrJumpy	.GetLength();
	mstrActualText = mstrJumpy;
	mnIndexAleator = -1;
	//start rendering
	KillTimer(ID_JUMPY_REFRESH_DRAW);
	SetTimer(ID_JUMPY_REFRESH_DRAW, (int)(mnTime/nLenght), NULL);
}

//the timer handle
void CJumpyDraw::OnTimer(UINT nIDEvent) 
{
	if (ID_JUMPY_REFRESH_DRAW == nIDEvent)
	{
		mnIndexAleator++;//this member hold the index in the text
		if ((mnIndexAleator+1) == mstrJumpy.GetLength())
		{//the render should stop rendering
			KillTimer(ID_JUMPY_REFRESH_DRAW);
			CStatic::OnTimer(nIDEvent);
			mstrActualText = mstrJumpy;
			mnIndexAleator = -1;
			Invalidate();
			return;
		}
		CString strGet, strSet;
		GetWindowText(strGet);
		CString strShuffle = strGet;
		if (mnIndexAleator > 0)
			strShuffle = mstrJumpy.Right(mstrJumpy.GetLength() - mnIndexAleator);
		else
			strShuffle = mstrActualText;
		if (mnIndexAleator > 0)
			strSet = mstrJumpy.Left(mnIndexAleator);
		else
			strSet = "";
		//render just the right part
		ShuffleChars(strSet, strShuffle);
		//combine left and right part and force to redraw it
		strSet += strShuffle;
		mstrActualText = strSet;
		Invalidate();
	}
	CStatic::OnTimer(nIDEvent);
}

//function for shuffleing the strShuffle string
void CJumpyDraw::ShuffleChars(CString strLeft, CString &strShuffle)
{
	srand( (unsigned)time( NULL ) );
	for (int j=0; j<10;j++)
	{
		for (int i=0; i<3;i++)
		{
			int nFirst = rand() % strShuffle.GetLength();
			int nSecond = rand() % strShuffle.GetLength();
			TCHAR FirstChar = strShuffle.GetAt(nFirst);
			TCHAR SecondChar = strShuffle.GetAt(nSecond);
			strShuffle.SetAt(nFirst, SecondChar);
			strShuffle.SetAt(nSecond, FirstChar);
		}
		//combine the left and right part
		mstrActualText = strLeft+strShuffle;
		Invalidate();
	}
}

//the paint function. It simply draw the text and the gradient background
void CJumpyDraw::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	CRect rc;
	GetClientRect(&rc);
	//virtual dc used for non-flickering
	CDC dcMem;
	dcMem.CreateCompatibleDC(&dc);
	CBitmap bitmapMem;
	bitmapMem.CreateCompatibleBitmap(&dc, rc.Width(), rc.Height());
	CBitmap* pOldBit = dcMem.SelectObject(&bitmapMem);
	HBRUSH hbrBkGnd;
	hbrBkGnd = CreateSolidBrush(GetSysColor(COLOR_ACTIVECAPTION));
	CRect rectTemp(rc);
	rectTemp.left = 0;
	rectTemp.top = 0;
	FillRect(dcMem.m_hDC, &rectTemp, hbrBkGnd);    
	DeleteObject(hbrBkGnd);
	dcMem.SetBkMode(TRANSPARENT);

	//draw the gradient
	DrawLinearWash(&dcMem, &rc, 
		LINEAR_WASH_SEGMENTS, mGradientColorStart, mGradientColorEnd);

	CFont* pfontOld;
	pfontOld = dcMem.SelectObject(&mFontDummy);
	//draw shaddow text
	dcMem.SetTextColor(mShaddowColor);
	dcMem.DrawText(mstrActualText, rc, DT_VCENTER | DT_NOCLIP | DT_SINGLELINE | DT_CENTER);
	rc.top -= 4;
	rc.left -= 4;
	//draw text
	dcMem.SetTextColor(mTextColor);
	dcMem.DrawText(mstrActualText, rc, DT_VCENTER | DT_NOCLIP | DT_SINGLELINE | DT_CENTER);
	dcMem.SelectObject(pfontOld);
	dc.BitBlt(rc.left,rc.top,rc.Width(),rc.Height(),&dcMem,0,0,SRCCOPY);
	 // Done with off-screen bitmap and DC.    //
    dcMem.SelectObject(pOldBit);
	DeleteObject(bitmapMem.m_hObject);
	dcMem.DeleteDC();
}

//the gradient function
void CJumpyDraw::DrawLinearWash(CDC* pDC, CRect* prc, int iSegments,
						   COLORREF crStart, COLORREF crEnd)
{
	// Get the starting RGB values and calculate the incremental
	// changes to be applied.

	COLORREF cr;
	int iR = GetRValue(crStart);
	int iG = GetGValue(crStart);
	int iB = GetGValue(crStart);
	int idR = (GetRValue(crEnd) - iR) / (iSegments - 1);
	int idG = (GetGValue(crEnd) - iG) / (iSegments - 1);
	int idB = (GetBValue(crEnd) - iB) / (iSegments - 1);
	int icx = prc->Width() / iSegments, iLeft = prc->left, iRight;
	pDC->SelectStockObject(NULL_PEN);

	for (int i = 0; i < iSegments; i++, iR += idR, iG += idG, iB += idB)
	{
		// Use special code for the last segment to avoid any problems
		// with integer division.

		if (i == (iSegments - 1))
			iRight = prc->right;
		else
			iRight = iLeft + icx;

		cr = RGB(iR, iG, iB);
		
		// The following extra stack frame allocates and disposes
		// of the GDI objects nicely.

		{
			// Perform the drawing and restore the DC; the objects
			// will be freed automatically.

			CBrush br(cr);
			CBrush* pbrOld = pDC->SelectObject(&br);
			pDC->Rectangle(iLeft, prc->top, iRight + 1, prc->bottom);
			pDC->SelectObject(pbrOld);
		}

		// Reset the left side of the drawing rectangle.

		iLeft = iRight;
	}
}

//get/set functions
void CJumpyDraw::SetText(CString strValue)
{
	mstrJumpy = mstrActualText = strValue;
}

CString CJumpyDraw::GetText()
{
	return mstrJumpy;
}

void CJumpyDraw::SetFontFace(CString strFont)
{
	mstrFont = strFont;
}

CString CJumpyDraw::GetFontFace()
{
	return mstrFont;
}

int CJumpyDraw::GetCharHeight()
{
	return mnCharHeight;
}

void CJumpyDraw::SetCharHeight(int nHeight)
{
	mnCharHeight = nHeight;
}

COLORREF CJumpyDraw::GetTextColor()
{
	return mTextColor;
}

void CJumpyDraw::SetTextColor(COLORREF colourText)
{
	mTextColor = colourText;
}

COLORREF CJumpyDraw::GetGradientStartColor()
{
	return mGradientColorStart;
}

void CJumpyDraw::SetGradientStartColor(COLORREF startColor)
{
	mGradientColorStart = startColor;
}

COLORREF CJumpyDraw::GetGradientEndColor()
{
	return mGradientColorEnd;
}

void CJumpyDraw::SetGradientEndColor(COLORREF colourEnd)
{
	mGradientColorEnd = colourEnd;
}

COLORREF CJumpyDraw::GetShaddowColor()
{
	return mShaddowColor;
}

void CJumpyDraw::SetShaddowColor(COLORREF colorShaddow)
{
	mShaddowColor = colorShaddow;
}

void CJumpyDraw::SetJumpyTime(DWORD nTime)
{
	mnTime = nTime;
}

DWORD CJumpyDraw::GetJumpyTime()
{
	return mnTime;
}

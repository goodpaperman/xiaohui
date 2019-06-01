#if !defined(AFX_JUMPYDRAW_H__E1E3B9B5_5E9C_11D3_A785_0000214D19D7__INCLUDED_)
#define AFX_JUMPYDRAW_H__E1E3B9B5_5E9C_11D3_A785_0000214D19D7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// JumpyDraw.h : header file
//
// Written by Fabian Toader (fabian_toader@hotmail.com)
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
// The author accepts no liability if it causes any damage whatsoever.
// It's free - so you get what you pay for.

/////////////////////////////////////////////////////////////////////////////
// CJumpyDraw window

class CJumpyDraw : public CStatic
{
// Construction
public:
	CJumpyDraw();

// Attributes
private:
	int mnIndexAleator;
	COLORREF mTextColor, mShaddowColor;
	COLORREF mGradientColorStart, mGradientColorEnd;
	DWORD mnTime;
	CString mstrFont;
	int mnCharHeight;
	CString mstrJumpy;
	CFont mFontDummy;
	CString mstrActualText;
public:
	void ShuffleChars(CString strLeft, CString& strShuffle);
	void StartJumpyText();
	void StartJumpyText(CString strJump,
		DWORD nTime, CString strFont, int nHeight, 
		COLORREF TextColor, COLORREF ShaddowColor,
		COLORREF GradientColorStart, 
		COLORREF GradientColorEnd);
	void DrawLinearWash(CDC* pDC, CRect* prc, int iSegments,
						   COLORREF crStart, COLORREF crEnd);
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJumpyDraw)
	//}}AFX_VIRTUAL

// Implementation
public:
	//get/set functions
	DWORD GetJumpyTime();
	void SetJumpyTime(DWORD nTime);
	void SetShaddowColor(COLORREF colorShaddow);
	COLORREF GetShaddowColor();
	void SetGradientEndColor(COLORREF colourEnd);
	COLORREF GetGradientEndColor();
	void SetGradientStartColor(COLORREF startColor);
	COLORREF GetGradientStartColor();
	void SetTextColor(COLORREF colourText);
	COLORREF GetTextColor();
	void SetCharHeight(int nHeight);
	int GetCharHeight();
	CString GetFontFace();
	void SetFontFace(CString strFont);
	CString GetText();
	void SetText(CString strValue);
	virtual ~CJumpyDraw();

	// Generated message map functions
protected:
	//{{AFX_MSG(CJumpyDraw)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JUMPYDRAW_H__E1E3B9B5_5E9C_11D3_A785_0000214D19D7__INCLUDED_)

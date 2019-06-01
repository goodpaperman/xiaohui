// BCGToolBarImages.h: interface for the CBCGToolBarImages class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BCGTOOLBARIMAGES_H__6F1376A1_C668_11D1_B110_ABB329E56E43__INCLUDED_)
#define AFX_BCGTOOLBARIMAGES_H__6F1376A1_C668_11D1_B110_ABB329E56E43__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXTEMPL_H__
	#include "afxtempl.h"
#endif

// for custom drawing
typedef struct tagDrawState
{
	HBITMAP hbmMono;
	HBITMAP hbmMonoOld;
	HBITMAP hbmOldGlyphs;
}
CBCGDrawState;

#include "bcgcontrolbar.h"

class BCGCONTROLBARDLLEXPORT CBCGToolBarImages : public CObject
{
public:
	CBCGToolBarImages();
	virtual ~CBCGToolBarImages();

// Operations:
public:
	BOOL IsValid () const
	{
		return (m_hbmImageWell != NULL);
	}

	BOOL IsUserImagesList () const
	{
		return m_bUserImagesList;
	}

	void SetSizes (SIZE sizeButton, SIZE sizeImage);
	SIZE GetImageSize () const
	{
		return m_sizeImage;
	}

	SIZE GetButtonSize () const
	{
		return m_sizeButton;
	}

	int GetCount () const
	{
		return m_iCount;
	}

	BOOL Load (UINT uiResID, HINSTANCE hinstRes = NULL, BOOL bAdd = FALSE);
	BOOL Load (LPCTSTR lpszBmpFileName);
	BOOL Save (LPCTSTR lpszBmpFileName = NULL);

	BOOL PrepareDrawImage (CBCGDrawState& ds);
	BOOL Draw (CDC* pDC, 
				int x, int y,
				POINT ptOffset,
				int iImageIndex, 
				BOOL bHilite = FALSE, 
				BOOL bDisabled = FALSE,
				BOOL bIndeterminate = FALSE,
				BOOL bMenuMode = FALSE);
	void EndDrawImage (CBCGDrawState& ds);

	int AddImage (HBITMAP hbmp);
	BOOL UpdateImage (int iImage, HBITMAP hbmp);
	BOOL DeleteImage (int iImage);

	BOOL CopyImageToClipboard (int iImage);

	void OnSysColorChange();

	static COLORREF MapToSysColor (COLORREF color, BOOL bUseRGBQUAD = TRUE);
	static COLORREF MapFromSysColor (COLORREF color, BOOL bUseRGBQUAD = TRUE);
	static void FillDitheredRect (CDC* pDC, const CRect& rect);

protected:

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	void CreateMask(int iImage, CPoint offset, 
				BOOL bHilite, 
				BOOL bHiliteShadow,
				CSize size = CSize (-1, -1));
	static HBITMAP CreateDitherBitmap();
	void UpdateCount ();

// Attributes:
public:

protected:
	CSize				m_sizeImage;        // size of glyph
	CSize				m_sizeButton;       // size of button
	HBITMAP				m_hbmImageWell;		// glyphs only
	HINSTANCE			m_hInstImageWell;	// instance handle to load image well from
	BOOL				m_bUserImagesList;	// is user-defined images list?
	CString				m_strUDLPath;		// user-defined images path
	BOOL				m_bModified;		// is image modified?
	int					m_iCount;			// image counter
	CList<UINT, UINT>	m_lstOrigResIds;	// original resource ids
};

#endif // !defined(AFX_BCGTOOLBARIMAGES_H__6F1376A1_C668_11D1_B110_ABB329E56E43__INCLUDED_)

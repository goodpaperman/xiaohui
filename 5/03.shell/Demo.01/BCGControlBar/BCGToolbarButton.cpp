// BCGToolbarButton.cpp: implementation of the CBCGToolbarButton class.
//
//////////////////////////////////////////////////////////////////////

#include "Stdafx.h"
#include <..\\src\\afximpl.h>
#include "BCGToolbar.h"
#include "BCGToolbarButton.h"
#include "BCGToolBarImages.h"
#include "ImageHash.h"
#include "globals.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(CBCGToolbarButton, CObject, VERSIONABLE_SCHEMA | 1)

CLIPFORMAT CBCGToolbarButton::m_cFormat = (CLIPFORMAT)::RegisterClipboardFormat (_T("BCGToolbarButton"));

static const int TEXT_MARGIN = 3;
static const int SEPARATOR_WIDTH = 8;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBCGToolbarButton::CBCGToolbarButton()
{
	m_nID = 0;
	m_nStyle = TBBS_BUTTON;
	m_iImage = -1;
	m_iUserImage = -1;
	m_bUserButton = FALSE;
	m_bDragFromCollection = FALSE;
	m_bText = FALSE;
	m_bImage = TRUE;
	m_bWrap = FALSE;

	m_rect.SetRectEmpty ();
}
//*********************************************************************************
CBCGToolbarButton::CBCGToolbarButton(UINT uiID, int iImage, LPCTSTR lpszText, BOOL bUserButton)
{
	m_nID = uiID;
	m_nStyle = TBBS_BUTTON;

	m_iImage = -1;
	m_iUserImage = -1;

	m_bUserButton = bUserButton;
	SetImage (iImage);

	m_strText = (lpszText == NULL) ? _T("") : lpszText;
	m_bDragFromCollection = FALSE;
	m_bText = FALSE;
	m_bImage = TRUE;
	m_bWrap = FALSE;

	m_rect.SetRectEmpty ();

	if (m_nID != 0)
	{
		if (m_bUserButton)
		{
			if (m_iUserImage != -1)
			{
				g_ImageHash.Set (m_nID, m_iUserImage, TRUE);
			}
			else
			{
				m_iUserImage = g_ImageHash.Get (m_nID, TRUE);
			}
		}
		else
		{
			if (m_iImage != -1)
			{
				g_ImageHash.Set (m_nID, m_iImage, FALSE);
			}
			else
			{
				m_iImage = g_ImageHash.Get (m_nID, FALSE);
			}
		}
	}
}
//*********************************************************************************
CBCGToolbarButton::~CBCGToolbarButton()
{
}
//*********************************************************************************
void CBCGToolbarButton::CopyFrom (const CBCGToolbarButton& src)
{
	m_nID			= src.m_nID;
	m_bUserButton	= src.m_bUserButton;
	m_nStyle		= src.m_nStyle;
	SetImage (src.m_bUserButton ? src.m_iUserImage : src.m_iImage);
	m_strText		= src.m_strText;
	m_bText			= src.m_bText;
	m_bImage		= src.m_bImage;
	m_bWrap			= src.m_bWrap;
					
	m_bDragFromCollection = FALSE;
}					
//***************************************************************************************
void CBCGToolbarButton::Serialize (CArchive& ar)
{
	CObject::Serialize (ar);

	if (ar.IsLoading ())
	{
		int iImage;

		ar >> m_nID;
		ar >> m_nStyle;	
		ar >> iImage;	
		ar >> m_strText;	
		ar >> m_bUserButton;
		ar >> m_bDragFromCollection;
		ar >> m_bText;
		ar >> m_bImage;

		SetImage (iImage);
	}
	else
	{
		ar << m_nID;		
		ar << m_nStyle;	
		ar << GetImage ();
		ar << m_strText;
		ar << m_bUserButton;
		ar << m_bDragFromCollection;
		ar << m_bText;
		ar << m_bImage;
	}
}
//***************************************************************************************
CLIPFORMAT CBCGToolbarButton::GetClipboardFormat ()
{
	return m_cFormat;
}
//***************************************************************************************
CBCGToolbarButton* CBCGToolbarButton::CreateFromOleData  (COleDataObject* pDataObject)
{
	ASSERT (pDataObject != NULL);
	ASSERT (pDataObject->IsDataAvailable (CBCGToolbarButton::m_cFormat));

	CBCGToolbarButton* pButton = NULL;

	try
	{
		//-------------------------------------
		// Get file refering to clipboard data:
		//-------------------------------------
		CFile* pFile = pDataObject->GetFileData (GetClipboardFormat ());
		if (pFile == NULL)
		{
			return FALSE;
		}

		//-------------------------------------------------------
		// Connect the file to the archive and read the contents:
		//-------------------------------------------------------
		CArchive ar (pFile, CArchive::load);

		//----------------------------------------
		// First, read run-time class information:
		//----------------------------------------
		CRuntimeClass* pClass = ar.ReadClass ();
		ASSERT (pClass != NULL);

		pButton = (CBCGToolbarButton*) pClass->CreateObject ();
		ASSERT (pButton != NULL);

		pButton->Serialize (ar);
		ar.Close ();
		delete pFile;

		return pButton;
	}
	catch (COleException* pEx)
	{
		TRACE(_T("CBCGToolbarButton::CreateFromOleData. OLE exception: %x\r\n"),
			pEx->m_sc);
		pEx->Delete ();
		return NULL;
	}
	catch (CArchiveException* pEx)
	{
		TRACE(_T("CBCGToolbarButton::CreateFromOleData. Archive exception\r\n"));
		pEx->Delete ();
		return FALSE;
	}
	catch (CNotSupportedException *pEx)
	{
		TRACE(_T("CBCGToolbarButton::CreateFromOleData. \"Not Supported\" exception\r\n"));
		pEx->Delete ();
		return FALSE;
	}

	if (pButton != NULL)
	{
		delete pButton;
	}

	return NULL;
}
//***************************************************************************************
void CBCGToolbarButton::OnDraw (CDC* pDC, const CRect& rect, CBCGToolBarImages* pImages,
								BOOL bHorz, BOOL bCustomizeMode, BOOL bHighlight,
								BOOL bDrawBorder, BOOL bGrayDisabledButtons)
{
	ASSERT_VALID (pDC);
	ASSERT_VALID (this);

	BOOL bHot = bHighlight;

	//---------------
	// Interior grey:
	//---------------
	pDC->FillSolidRect (&rect, globalData.clrBtnFace);

	if (!bCustomizeMode && !bHighlight &&
		(m_nStyle & (TBBS_CHECKED | TBBS_INDETERMINATE)))
	{
		CRect rectDither = rect;
		rectDither.InflateRect (-afxData.cxBorder2, -afxData.cyBorder2);

		CBCGToolBarImages::FillDitheredRect (pDC, rectDither);
	}

	//--------------------
	// Draw button border:
	//--------------------
	if (!bCustomizeMode && HaveHotBorder () && bDrawBorder)
	{
		if (m_nStyle & (TBBS_PRESSED | TBBS_CHECKED))
		{
			//-----------------------
			// Pressed in or checked:
			//-----------------------
			pDC->Draw3dRect (&rect,
				afxData.clrBtnShadow,
				afxData.clrBtnHilite);
		}
		else if (bHighlight && !(m_nStyle & TBBS_DISABLED) &&
			!(m_nStyle & (TBBS_CHECKED | TBBS_INDETERMINATE)))
		{
			pDC->Draw3dRect (&rect, afxData.clrBtnHilite,
									afxData.clrBtnShadow);
		}
	}

	CSize sizeImage = (pImages == NULL) ? CSize (0, 0) : pImages->GetImageSize ();

	int x = rect.left;
	int y = rect.top;

	int iTextLen = 0;

	if (IsDrawText ())
	{
		CString strWithoutAmp = m_strText;
		strWithoutAmp.Remove (_T('&'));

		iTextLen = pDC->GetTextExtent (strWithoutAmp).cx + 2 * TEXT_MARGIN;
	}

	int dx = bHorz ? rect.Width () - iTextLen : rect.Width ();
	int dy = bHorz ? rect.Height () : rect.Height () - iTextLen;

	// determine offset of bitmap (centered within button)
	CPoint ptImageOffset;
	ptImageOffset.x = (dx - sizeImage.cx - 1) / 2;
	ptImageOffset.y = (dy - sizeImage.cy + 1) / 2;

	CPoint ptTextOffset (TEXT_MARGIN + 3, TEXT_MARGIN + 3);

	if (IsDrawText ())
	{
		TEXTMETRIC tm;
		pDC->GetTextMetrics (&tm);

		if (bHorz)
		{
			ptTextOffset.y = (dy - tm.tmHeight - 1) / 2;
		}
		else
		{
			ptTextOffset.x = (dx - tm.tmHeight + 1) / 2;
		}
	}

	if ((m_nStyle & (TBBS_PRESSED | TBBS_CHECKED)) && !bCustomizeMode)
	{
		// pressed in or checked

		ptImageOffset.x ++;
		ptImageOffset.y ++;

		ptTextOffset.x ++;

		if (bHorz)
		{
			ptTextOffset.y ++;
		}
		else
		{
			ptTextOffset.y --;
		}
	}

	BOOL bImageIsReady = FALSE;

	if ((m_nStyle & TBBS_PRESSED) || !(m_nStyle & TBBS_DISABLED) ||
		bCustomizeMode)
	{
		if (IsDrawImage () && pImages != NULL)
		{
			pImages->Draw (pDC, x, y, ptImageOffset, GetImage ());
		}

		if (bCustomizeMode || m_nStyle & TBBS_PRESSED)
		{
			bImageIsReady = TRUE;
		}
	}

	BOOL bDisabled = (bCustomizeMode && !IsEditable ()) ||
		(!bCustomizeMode && (m_nStyle & TBBS_DISABLED));

	if (!bImageIsReady)
	{
		if (!bHighlight)
		{
			bHighlight = !(m_nStyle & (TBBS_CHECKED | TBBS_INDETERMINATE));
		}

		if (IsDrawImage () && pImages != NULL)
		{
			pImages->Draw (pDC, x, y, ptImageOffset, 
							GetImage (), !bHighlight, bDisabled && bGrayDisabledButtons);
		}
	}

	if (IsDrawText ())
	{
		if (IsDrawImage ())
		{
			if (bHorz)
			{
				ptTextOffset.x += ptImageOffset.x + sizeImage.cx;
			}
			else
			{
				ptTextOffset.y += TEXT_MARGIN;
			}
		}

		CRect rectText = rect;
		rectText.left = x + ptTextOffset.x;
		
		CString strText = m_strText;
		UINT uiTextFormat = DT_SINGLELINE;

		if (bHorz)
		{
			rectText.top += ptTextOffset.y;
		}
		else
		{
			rectText.top = rect.bottom - ptTextOffset.y;
			rectText.bottom = rect.top;

			rectText.right = rectText.left;
			rectText.left = x + ptTextOffset.x;

			strText.Remove (_T('&'));
			uiTextFormat |= DT_NOCLIP;
		}

		pDC->SetTextColor (bDisabled ?
							globalData.clrGrayedText : 
								(bHot) ? CBCGToolBar::GetHotTextColor () :
										globalData.clrBtnText);
		pDC->DrawText (strText, &rectText, uiTextFormat);
	}
}
//***********************************************************************************
SIZE CBCGToolbarButton::OnCalculateSize (
								CDC* pDC,
								const CSize& sizeDefault,
								BOOL bHorz)
{
	CSize size = sizeDefault;

	if (m_nStyle & TBBS_SEPARATOR)
	{
		if (bHorz)
		{
			size.cx = m_iImage > 0 ? m_iImage : SEPARATOR_WIDTH;
		}
		else
		{
			size.cy = SEPARATOR_WIDTH;
		}
	}
	else
	{
		if (!IsDrawImage () || GetImage () < 0)
		{
			if (bHorz)
			{
				size.cx = 0;
			}
			else
			{
				size.cy = 0;
			}
		}

		if (IsDrawText () && !m_strText.IsEmpty ())
		{
			CString strWithoutAmp = m_strText;
			strWithoutAmp.Remove (_T('&'));

			int iTextLen = pDC->GetTextExtent (strWithoutAmp).cx + 2 * TEXT_MARGIN + 6;

			if (bHorz)
			{
				size.cx += iTextLen;
			}
			else
			{
				size.cy += iTextLen;
			}
		}
	}

	return size;
}
//************************************************************************************
BOOL CBCGToolbarButton::PrepareDrag (COleDataSource& srcItem)
{
	if (!CanBeStored ())
	{
		return TRUE;
	}

	try
	{
		CSharedFile globFile;
		CArchive ar (&globFile,CArchive::store);

		//---------------------------------
		// Save run-time class information:
		//---------------------------------
		CRuntimeClass* pClass = GetRuntimeClass ();
		ASSERT (pClass != NULL);

		ar.WriteClass (pClass);

		//---------------------
		// Save button context:
		//---------------------
		Serialize (ar);
		ar.Close();

		srcItem.CacheGlobalData (GetClipboardFormat (), globFile.Detach());
	}
	catch (COleException* pEx)
	{
		TRACE(_T("CBCGToolbarButton::PrepareDrag. OLE exception: %x\r\n"),
			pEx->m_sc);
		pEx->Delete ();
		return FALSE;
	}
	catch (CArchiveException* pEx)
	{
		TRACE(_T("CBCGToolbarButton::PrepareDrag. Archive exception\r\n"));
		pEx->Delete ();
		return FALSE;
	}

	return TRUE;
}
//****************************************************************************************
void CBCGToolbarButton::SetImage (int iImage)
{
	if (m_nStyle & TBBS_SEPARATOR)
	{
		m_iImage = iImage;	// Actualy, separator width!
		return;
	}

	if (m_bUserButton)
	{
		m_iUserImage = iImage;
	}
	else
	{
		m_iImage = iImage;
	}

	if (m_nID != 0 && iImage != -1)
	{
		g_ImageHash.Set (m_nID, iImage, m_bUserButton);
	}
	else if (m_nID != 0)
	{
		m_iImage = g_ImageHash.Get (m_nID, FALSE);
		m_iUserImage = g_ImageHash.Get (m_nID, TRUE);

		if (m_iImage == -1 && !m_bUserButton)
		{
			m_bUserButton = TRUE;
		}
		else if (m_iImage == -1 && m_bUserButton)
		{
			m_bUserButton = FALSE;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CBCGToolbarButton diagnostics

#ifdef _DEBUG
void CBCGToolbarButton::AssertValid() const
{
	CObject::AssertValid();
}
//******************************************************************************************
void CBCGToolbarButton::Dump(CDumpContext& dc) const
{
	CObject::Dump (dc);

	CString strId;
	strId.Format (_T("%x"), m_nID);

	dc << "[" << strId << " " << m_strText << "]";
	dc << "\n";
}

#endif

int CBCGToolbarButton::OnDrawOnCustomizeList (
	CDC* pDC, const CRect& rect, BOOL bSelected)
{
	int iWidth = 0;

	ASSERT_VALID (pDC);

	CBCGToolBarImages* pImages = m_bUserButton ?
		CBCGToolBar::GetUserImages () :
		CBCGToolBar::GetImages ();
	
	CBCGToolBarImages* pCommonImages = CBCGToolBar::GetImages ();
	CSize sizeButton = (pCommonImages == NULL) ? 
					CSize (0, 0) : pCommonImages->GetButtonSize ();

	CRect rectRow = rect;
	CRect rectText = rect;
	rectText.left += sizeButton.cx;

	iWidth = sizeButton.cx;

	//-------------------
	// Draw button image:
	//-------------------
	if (GetImage () >= 0 && pImages != NULL)
	{
		CRect rectImage = rect;
		rectImage.right = rectImage.left + sizeButton.cx;

		CBCGDrawState ds;
		pImages->PrepareDrawImage (ds);

		OnDraw (pDC, rectImage, pImages, TRUE, FALSE, bSelected);
		pImages->EndDrawImage (ds);

		rectRow.left = rectImage.right;
	}

	//-------------------
	// Draw button text:
	//-------------------
	if (!m_strText.IsEmpty ())
	{
		COLORREF clrTextOld;

		if (bSelected) 
		{
			pDC->FillSolidRect (rectRow, ::GetSysColor (COLOR_HIGHLIGHT));
			clrTextOld = pDC->SetTextColor (::GetSysColor (COLOR_HIGHLIGHTTEXT));
		} 
		else
		{
			pDC->FillSolidRect (rectRow, ::GetSysColor (COLOR_BTNFACE));
			clrTextOld = pDC->SetTextColor (::GetSysColor (COLOR_BTNTEXT));
		}

		pDC->DrawText (m_strText, rectText, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		pDC->SetTextColor (clrTextOld);

		int iTextWidth = min (rectText.Width (), pDC->GetTextExtent (m_strText).cx);
		iWidth += iTextWidth;
	}

	if (bSelected)
	{
		pDC->DrawFocusRect (rectRow);
	}

	return iWidth;
}

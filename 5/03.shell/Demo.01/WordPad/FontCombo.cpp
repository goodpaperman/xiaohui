// FontCombo.cpp: implementation of the CFontCombo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "wordpad.h"
#include "BCGToolBar.h"
#include "FontCombo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// reserve lobyte for charset
#define PRINTER_FONT	0x0100
#define TT_FONT			0x0200
#define DEVICE_FONT		0x0400

#define BMW 16
#define BMH 15

static int nFontSizes[] =
	{8, 9, 10, 11, 12, 14, 16, 18, 20, 22, 24, 26, 28, 36, 48, 72};

int CLocalComboBox::m_nFontHeight = 0;
BOOL CLocalComboBox::m_bHasFocus = FALSE;
CDC CLocalComboBox::m_dcPrinter;

class CFontDesc : public CObject
{
public:
	CFontDesc(LPCTSTR lpszName, LPCTSTR lpszScript, BYTE nCharSet,
		BYTE nPitchAndFamily, DWORD dwFlags);
	CString m_strName;
	CString m_strScript;
	BYTE m_nCharSet;
	BYTE m_nPitchAndFamily;
	DWORD m_dwFlags;
};

CFontDesc::CFontDesc(LPCTSTR lpszName, LPCTSTR lpszScript, BYTE nCharSet,
	BYTE nPitchAndFamily, DWORD dwFlags)
{
	m_strName = lpszName;
	m_strScript = lpszScript;
	m_nCharSet = nCharSet;
	m_nPitchAndFamily = nPitchAndFamily;
	m_dwFlags = dwFlags;
}

/////////////////////////////////////////////////////////////////////////////
// CFontComboBox

BEGIN_MESSAGE_MAP(CFontComboBox, CLocalComboBox)
	//{{AFX_MSG_MAP(CFontComboBox)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CFontComboBox::CFontComboBox()
{
	VERIFY(m_bmFontType.LoadBitmap(IDB_FONTTYPE));
}

void CFontComboBox::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
	ASSERT(lpDIS->CtlType == ODT_COMBOBOX);
	int id = (int)(WORD)lpDIS->itemID;

	CDC *pDC = CDC::FromHandle(lpDIS->hDC);
	CRect rc(lpDIS->rcItem);
	if (lpDIS->itemState & ODS_FOCUS)
		pDC->DrawFocusRect(rc);
	int nIndexDC = pDC->SaveDC();

	CBrush brushFill;
	if (lpDIS->itemState & ODS_SELECTED)
	{
		brushFill.CreateSolidBrush(::GetSysColor(COLOR_HIGHLIGHT));
		pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
	}
	else
		brushFill.CreateSolidBrush(pDC->GetBkColor());
	pDC->SetBkMode(TRANSPARENT);
	pDC->FillRect(rc, &brushFill);

	CFontDesc* pDesc= (CFontDesc*)lpDIS->itemData;
	ASSERT(pDesc != NULL);
	DWORD dwData = pDesc->m_dwFlags;
	if (dwData & (TT_FONT|DEVICE_FONT)) // truetype or device flag set by SetItemData
	{
		CDC dc;
		dc.CreateCompatibleDC(pDC);
		CBitmap* pBitmap = dc.SelectObject(&m_bmFontType);
		if (dwData & TT_FONT)
			pDC->BitBlt(rc.left, rc.top, BMW, BMH, &dc, BMW, 0, SRCAND);
		else // DEVICE_FONT
			pDC->BitBlt(rc.left, rc.top, BMW, BMH, &dc, 0, 0, SRCAND);
		dc.SelectObject(pBitmap);
	}

	rc.left += BMW + 6;
	CString strText;
	GetLBText(id, strText);
	pDC->TextOut(rc.left,rc.top,strText,strText.GetLength());

	pDC->RestoreDC(nIndexDC);
}

void CFontComboBox::MeasureItem(LPMEASUREITEMSTRUCT lpMIS)
{
	ASSERT(lpMIS->CtlType == ODT_COMBOBOX);
	ASSERT(m_nFontHeight > 0);
	CRect rc;

	GetWindowRect(&rc);
	lpMIS->itemWidth = rc.Width();
	lpMIS->itemHeight = max(BMH, m_nFontHeight);
}

int CFontComboBox::CompareItem(LPCOMPAREITEMSTRUCT lpCIS)
{
	ASSERT(lpCIS->CtlType == ODT_COMBOBOX);
	int id1 = (int)(WORD)lpCIS->itemID1;
	int id2 = (int)(WORD)lpCIS->itemID2;
	CString str1,str2;
	if (id1 == -1)
		return -1;
	if (id2 == -1)
		return 1;
	GetLBText(id1, str1);
	GetLBText(id2, str2);
	return str1.Collate(str2);
}

// find a font with the face name and charset
void CFontComboBox::MatchFont(LPCTSTR lpszName, BYTE nCharSet)
{
	int nFirstIndex = FindString(-1, lpszName);
	if (nFirstIndex != CB_ERR)
	{
		int nIndex = nFirstIndex;
		do
		{
			CFontDesc* pDesc = (CFontDesc*)GetItemData(nIndex);
			ASSERT(pDesc != NULL);
			// check the actual font name to avoid matching Courier western
			// to Courier New western
			if ((nCharSet == DEFAULT_CHARSET || pDesc->m_nCharSet == nCharSet) &&
				lstrcmp(lpszName, pDesc->m_strName)==0)
			{
				//got a match
				if (GetCurSel() != nIndex)
				{
					SetCurSel(nIndex);
				}
				return;
			}
			nIndex = FindString(nIndex, lpszName);
		} while (nIndex != nFirstIndex);
		// loop until found or back to first item again
	}
	//enter font name
	SetTheText(lpszName, TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// CSizeComboBox

CSizeComboBox::CSizeComboBox()
{
	m_nTwipsLast = 0;
}

void CSizeComboBox::EnumFontSizes(CDC& dc, LPCTSTR pFontName)
{
	ResetContent();
	if (pFontName == NULL)
		return;
	if (pFontName[0] == NULL)
		return;

	ASSERT(dc.m_hDC != NULL);
	m_nLogVert = dc.GetDeviceCaps(LOGPIXELSY);

	::EnumFontFamilies(dc.m_hDC, pFontName,
		(FONTENUMPROC) EnumSizeCallBack, (LPARAM) this);
}

void CSizeComboBox::TwipsToPointString(LPTSTR lpszBuf, int nTwips)
{
	ASSERT(lpszBuf != NULL);
	lpszBuf[0] = NULL;
	if (nTwips >= 0)
	{
		// round to nearest half point
		nTwips = (nTwips+5)/10;
		if ((nTwips%2) == 0)
			_stprintf(lpszBuf, _T("%ld"), nTwips/2);
		else
			_stprintf(lpszBuf, _T("%.1f"), (float)nTwips/2.F);
	}
}

void CSizeComboBox::SetTwipSize(int nTwips)
{
	if (nTwips != GetTwipSize())
	{
		TCHAR buf[10];
		TwipsToPointString(buf, nTwips);
		SetTheText(buf, TRUE);
	}
	m_nTwipsLast = nTwips;
}

int CSizeComboBox::GetTwipSize()
{
	// return values
	// -2 -- error
	// -1 -- edit box empty
	// >=0 -- font size in twips
	CString str;
	GetTheText(str);
	LPCTSTR lpszText = str;

	while (*lpszText == ' ' || *lpszText == '\t')
		lpszText++;

	if (lpszText[0] == NULL)
		return -1; // no text in control

	double d = _tcstod(lpszText, (LPTSTR*)&lpszText);
	while (*lpszText == ' ' || *lpszText == '\t')
		lpszText++;

	if (*lpszText != NULL)
		return -2;   // not terminated properly

	return (d<0.) ? 0 : (int)(d*20.);
}

BOOL CALLBACK AFX_EXPORT CSizeComboBox::EnumSizeCallBack(LOGFONT FAR* /*lplf*/,
		LPNEWTEXTMETRIC lpntm, int FontType, LPVOID lpv)
{
	CSizeComboBox* pThis = (CSizeComboBox*)lpv;
	ASSERT(pThis != NULL);
	TCHAR buf[10];
	if (
		(FontType & TRUETYPE_FONTTYPE) ||
		!( (FontType & TRUETYPE_FONTTYPE) || (FontType & RASTER_FONTTYPE) )
		) // if truetype or vector font
	{
		// this occurs when there is a truetype and nontruetype version of a font
		if (pThis->GetCount() != 0)
			pThis->ResetContent();

		for (int i = 0; i < 16; i++)
		{
			wsprintf(buf, _T("%d"), nFontSizes[i]);
			pThis->AddString(buf);
		}
		return FALSE; // don't call me again
	}
	// calc character height in pixels
	pThis->InsertSize(MulDiv(lpntm->tmHeight-lpntm->tmInternalLeading,
		1440, pThis->m_nLogVert));
	return TRUE; // call me again
}

void CSizeComboBox::InsertSize(int nSize)
{
	ASSERT(nSize > 0);
	DWORD dwSize = (DWORD)nSize;
	TCHAR buf[10];
	TwipsToPointString(buf, nSize);
	if (FindStringExact(-1, buf) == CB_ERR)
	{
		int nIndex = -1;
		int nPos = 0;
		DWORD dw;
		while ((dw = GetItemData(nPos)) != CB_ERR)
		{
			if (dw > dwSize)
			{
				nIndex = nPos;
				break;
			}
			nPos++;
		}
		nIndex = InsertString(nIndex, buf);
		ASSERT(nIndex != CB_ERR);
		if (nIndex != CB_ERR)
			SetItemData(nIndex, dwSize);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CLocalComboBox

BEGIN_MESSAGE_MAP(CLocalComboBox, CFlatComboBox)
	//{{AFX_MSG_MAP(CLocalComboBox)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	// Global help commands
END_MESSAGE_MAP()

void CLocalComboBox::GetTheText(CString& str)
{
	if (GetSafeHwnd () == NULL)
	{
		str.Empty ();
		return;
	}

	int nIndex = GetCurSel();
	if (nIndex == CB_ERR)
		GetWindowText(str);
	else
		GetLBText(nIndex, str);
}

void CLocalComboBox::SetTheText(LPCTSTR lpszText,BOOL bMatchExact)
{
	if (GetSafeHwnd () == NULL)
	{
		return;
	}

	int idx = (bMatchExact) ? FindStringExact(-1,lpszText) :
		FindString(-1, lpszText);
	SetCurSel( (idx==CB_ERR) ? -1 : idx);
	if (idx == CB_ERR)
		SetWindowText(lpszText);
}

BOOL CLocalComboBox::LimitText(int nMaxChars)
{
	BOOL b = CFlatComboBox::LimitText(nMaxChars);
	if (b)
		m_nLimitText = nMaxChars;
	return b;
}

int CLocalComboBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFlatComboBox::OnCreate(lpCreateStruct) == -1)
		return -1;
	SendMessage(WM_SETFONT, (WPARAM)GetStockObject(theApp.m_nDefFont));
	return 0;
}

BOOL CLocalComboBox::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		CBCGToolBar* pBar = (CBCGToolBar*)GetParent();
		switch (pMsg->wParam)
		{
		case VK_ESCAPE:
			SyncToView(pBar);
			NotifyOwner(NM_RETURN);
			return TRUE;
		case VK_RETURN:
			NotifyOwner(NM_RETURN);
			return TRUE;
		case VK_TAB:
			pBar->GetNextDlgTabItem(this)->SetFocus();
			return TRUE;
		case VK_UP:
		case VK_DOWN:
			if ((GetKeyState(VK_MENU) >= 0) && (GetKeyState(VK_CONTROL) >=0) &&
				!GetDroppedState())
			{
				ShowDropDown();
				return TRUE;
			}
		}
	}
	return CFlatComboBox::PreTranslateMessage(pMsg);
}

void CLocalComboBox::NotifyOwner(UINT nCode)
{
	CWnd* pWndParent = GetParent ();
	ASSERT_VALID (pWndParent);

	NMHDR nm;
	nm.hwndFrom = pWndParent->GetSafeHwnd ();
	nm.idFrom = pWndParent->GetDlgCtrlID();
	nm.code = nCode;
	pWndParent->GetOwner()->SendMessage(WM_NOTIFY, nm.idFrom, (LPARAM)&nm);
}

void CLocalComboBox::SetCharFormat(CCharFormat& cf)
{
	CWnd* pWndParent = GetParent ();
	ASSERT_VALID (pWndParent);

	CHARHDR fnm;
	fnm.hwndFrom = pWndParent->GetSafeHwnd ();
	fnm.idFrom = pWndParent->GetDlgCtrlID();
	fnm.code = FN_SETFORMAT;
	fnm.cf = cf;
	VERIFY(pWndParent->GetOwner()->SendMessage(WM_NOTIFY, fnm.idFrom, (LPARAM)&fnm));
}

void CLocalComboBox::SyncToView(CWnd* pWnd)
{
	USES_CONVERSION;

	ASSERT_VALID (pWnd);
	ASSERT (pWnd->GetSafeHwnd () != NULL);

	// get the current font from the view and update
	CHARHDR fh;
	CHARFORMAT& cf = fh.cf;
	fh.hwndFrom = pWnd->GetSafeHwnd ();
	fh.idFrom = pWnd->GetDlgCtrlID();
	fh.code = FN_GETFORMAT;
	VERIFY(pWnd->GetOwner()->SendMessage(WM_NOTIFY, fh.idFrom, (LPARAM)&fh));

	// the selection must be same font and charset to display correctly
	CObList listButtons;
	if (CBCGToolBar::GetCommandButtons (IDC_FONTNAME, listButtons) > 0)
	{
		for (POSITION posCombo = listButtons.GetHeadPosition (); posCombo != NULL;)
		{
			CBCGToolbarComboBoxButton* pCombo = 
				DYNAMIC_DOWNCAST (CBCGToolbarComboBoxButton, listButtons.GetNext (posCombo));
			ASSERT (pCombo != NULL);

			CFontComboBox* pWndCombo = (CFontComboBox*) pCombo->GetComboBox ();
			ASSERT_VALID (pWndCombo);

			if ((cf.dwMask & (CFM_FACE|CFM_CHARSET)) == (CFM_FACE|CFM_CHARSET))
				pWndCombo->MatchFont(A2T(cf.szFaceName), cf.bCharSet);
			else
				pWndCombo->SetTheText(_T(""));
		}
	}


	// SetTwipSize only updates if different
	// -1 means selection is not a single point size
	if (CBCGToolBar::GetCommandButtons (IDC_FONTSIZE, listButtons) > 0)
	{
		for (POSITION posCombo = listButtons.GetHeadPosition (); posCombo != NULL;)
		{
			CBCGToolbarComboBoxButton* pCombo = 
				DYNAMIC_DOWNCAST (CBCGToolbarComboBoxButton, listButtons.GetNext (posCombo));
			ASSERT (pCombo != NULL);

			CSizeComboBox* pWndCombo = (CSizeComboBox*) pCombo->GetComboBox ();
			ASSERT_VALID (pWndCombo);

			pWndCombo->SetTwipSize( (cf.dwMask & CFM_SIZE) ? cf.yHeight : -1);
		}
	}
}

void CLocalComboBox::OnPrinterChanged()
{
	theApp.CreatePrinterDC(m_dcPrinter);
	CFontNameComboBoxButton::RebuildFonts (m_dcPrinter);

	CObList listButtons;
	if (CBCGToolBar::GetCommandButtons (IDC_FONTNAME, listButtons) > 0)
	{
		for (POSITION posCombo = listButtons.GetHeadPosition (); posCombo != NULL;)
		{
			CFontNameComboBoxButton* pCombo = 
				DYNAMIC_DOWNCAST (CFontNameComboBoxButton, listButtons.GetNext (posCombo));
			ASSERT (pCombo != NULL);

			pCombo->SetFonts ();
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
// CFontNameComboBoxButton

IMPLEMENT_SERIAL(CFontNameComboBoxButton, CBCGToolbarComboBoxButton, 1)

CArray<CFontDesc*, CFontDesc*> CFontNameComboBoxButton::m_arrayFontDesc;
int CFontNameComboBoxButton::nCount = 0;

void CFontNameComboBoxButton::Initialize ()
{
	if (nCount++ == 0)
	{
		ASSERT (m_arrayFontDesc.GetSize () == 0);
		RebuildFonts (CLocalComboBox::m_dcPrinter);
	}
}

CFontNameComboBoxButton::~CFontNameComboBoxButton()
{
	if (--nCount == 0)
	{
		for (int i = 0; i < m_arrayFontDesc.GetSize (); i ++)
		{
			delete m_arrayFontDesc [i];
		}

		m_arrayFontDesc.SetSize (0);
	}
}

CComboBox* CFontNameComboBoxButton::CreateCombo (CWnd* pWndParent, const CRect& rect)
{
	CFontComboBox* pWndCombo = new CFontComboBox;

	CBCGToolBar* pWndToolBar = DYNAMIC_DOWNCAST (CBCGToolBar, pWndParent);
	if (pWndToolBar != NULL)
	{
		pWndCombo->m_nFontHeight = pWndToolBar->GetRowHeight () - 6;
	}

	if (!pWndCombo->Create (m_dwStyle, rect, pWndParent, m_nID))
	{
		delete pWndCombo;
		return NULL;
	}

	pWndCombo->LimitText (LF_FACESIZE);
	SetFonts ();

	return pWndCombo;
}

BOOL CFontNameComboBoxButton::NotifyCommand (int iNotifyCode)
{
	USES_CONVERSION;
	BOOL bRes = CBCGToolbarComboBoxButton::NotifyCommand (iNotifyCode);
	
	CFontComboBox* pCombo = (CFontComboBox*) GetComboBox ();
	ASSERT_VALID (pCombo);

	switch (iNotifyCode)
	{
	case CBN_KILLFOCUS:
		{
			pCombo->NotifyOwner (NM_KILLFOCUS);

			// this will retrieve the font entered in the edit control
			// it tries to match the font to something already present in the combo box
			// this effectively ignores case of a font the user enters
			// if a user enters arial, this will cause it to become Arial
			CString str;
			pCombo->GetTheText(str);    // returns "arial"
			pCombo->SetTheText(str);                    // selects "Arial"
			pCombo->GetTheText(str);    // returns "Arial"

			if (!str.IsEmpty ())
			{
				CCharFormat cf;
				cf.szFaceName[0] = NULL;

				cf.dwMask = CFM_FACE | CFM_CHARSET;
				int nIndex = pCombo->FindStringExact(-1, str);
				if (nIndex != CB_ERR)
				{
					CFontDesc* pDesc = (CFontDesc*)GetItemData(nIndex);
					ASSERT(pDesc != NULL);
					ASSERT(pDesc->m_strName.GetLength() < LF_FACESIZE);

					lstrcpynA(cf.szFaceName,
						T2A((LPTSTR) (LPCTSTR) pDesc->m_strName), LF_FACESIZE);
					cf.bCharSet = pDesc->m_nCharSet;
					cf.bPitchAndFamily = pDesc->m_nPitchAndFamily;
				}
				else // unknown font
				{
					ASSERT(str.GetLength() < LF_FACESIZE);
					lstrcpynA(cf.szFaceName,
						T2A((LPTSTR) (LPCTSTR) str), LF_FACESIZE);
					cf.bCharSet = DEFAULT_CHARSET;
					cf.bPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
				}

				pCombo->SetCharFormat(cf);
			}

			CLocalComboBox::m_bHasFocus = FALSE;
			bRes = TRUE;
			break;
		}

	case CBN_CLOSEUP:
		pCombo->NotifyOwner (NM_RETURN);
		bRes = TRUE;
		break;

	case CBN_SETFOCUS:
		pCombo->NotifyOwner (NM_SETFOCUS);
		CLocalComboBox::m_bHasFocus = TRUE;
		bRes = TRUE;
		break;
	}

	return bRes;
}

/////////////////////////////////////////////////////////////////////////////////////////
// CFontSizeComboBoxButton

IMPLEMENT_SERIAL(CFontSizeComboBoxButton, CBCGToolbarComboBoxButton, 1)

CComboBox* CFontSizeComboBoxButton::CreateCombo (CWnd* pWndParent, const CRect& rect)
{
	CSizeComboBox* pWndCombo = new CSizeComboBox;

	CBCGToolBar* pWndToolBar = DYNAMIC_DOWNCAST (CBCGToolBar, pWndParent);
	if (pWndToolBar != NULL)
	{
		pWndCombo->m_nFontHeight = pWndToolBar->GetRowHeight () - 6;
	}

	if (!pWndCombo->Create (m_dwStyle, rect, pWndParent, m_nID))
	{
		delete pWndCombo;
		return NULL;
	}

	pWndCombo->LimitText (4);
	return pWndCombo;
}

BOOL CFontSizeComboBoxButton::NotifyCommand (int iNotifyCode)
{
	BOOL bRes = CBCGToolbarComboBoxButton::NotifyCommand (iNotifyCode);
	BOOL bPrinterFont = FALSE;

	CSizeComboBox* pCombo = (CSizeComboBox*) GetComboBox ();
	ASSERT_VALID (pCombo);

	switch (iNotifyCode)
	{
	case CBN_DROPDOWN:
		{
			CWnd* pWndParent = pCombo->GetParent ();
			ASSERT_VALID (pWndParent);

			CObList listButtons;
			if (CBCGToolBar::GetCommandButtons (IDC_FONTNAME, listButtons) <= 0)
			{
				// Font name combo wasn't found!
				return FALSE;
			}
				
			CBCGToolbarComboBoxButton* pFontCombo = 
				DYNAMIC_DOWNCAST (CBCGToolbarComboBoxButton, listButtons.GetHead ());
			ASSERT (pFontCombo != NULL);

			CFontComboBox* pWndFontCombo = (CFontComboBox*) pFontCombo->GetComboBox ();
			ASSERT_VALID (pWndFontCombo);

			CString str;
			pWndFontCombo->GetTheText(str);
			LPCTSTR lpszName = NULL;
			BOOL bPrinterFont;
			int nIndex = pWndFontCombo->FindStringExact(-1, str);
			if (nIndex != CB_ERR)
			{
				CFontDesc* pDesc = (CFontDesc*)pWndFontCombo->GetItemData(nIndex);
				ASSERT(pDesc != NULL);
				bPrinterFont = pDesc->m_dwFlags & PRINTER_FONT;
				lpszName = pDesc->m_strName;
			}

			int nSize = pCombo->GetTwipSize();
			if (nSize == -2) // error
			{
				AfxMessageBox(IDS_INVALID_NUMBER, MB_OK|MB_ICONINFORMATION);
				nSize = pCombo->m_nTwipsLast;
			}
			else if ((nSize >= 0 && nSize < 20) || nSize > 32760)
			{
				AfxMessageBox(IDS_INVALID_FONTSIZE, MB_OK|MB_ICONINFORMATION);
				nSize = pCombo->m_nTwipsLast;
			}

			if (bPrinterFont)
			{
				pCombo->EnumFontSizes (CLocalComboBox::m_dcPrinter, lpszName);
			}
			else
			{
				pCombo->EnumFontSizes (theApp.m_dcScreen, lpszName);
			}

			pCombo->SetTwipSize(nSize);			
			bRes = TRUE;
		}
		break;

	case CBN_KILLFOCUS:
		{
			pCombo->NotifyOwner (NM_KILLFOCUS);

			int nSize = pCombo->GetTwipSize();
			if (nSize == -2)
			{
				AfxMessageBox(IDS_INVALID_NUMBER, MB_OK|MB_ICONINFORMATION);
				nSize = pCombo->m_nTwipsLast;
			}
			else if ((nSize >= 0 && nSize < 20) || nSize > 32760)
			{
				AfxMessageBox(IDS_INVALID_FONTSIZE, MB_OK|MB_ICONINFORMATION);
				nSize = pCombo->m_nTwipsLast;
			}
			else if (nSize > 0)
			{
				CCharFormat cf;
				cf.dwMask = CFM_SIZE;
				cf.yHeight = nSize;
				pCombo->SetCharFormat(cf);
			}
		}
		
		CLocalComboBox::m_bHasFocus = FALSE;
		bRes = TRUE;
		break;

	case CBN_CLOSEUP:
		pCombo->NotifyOwner (NM_RETURN);
		bRes = TRUE;
		break;

	case CBN_SETFOCUS:
		pCombo->NotifyOwner (NM_SETFOCUS);
		CLocalComboBox::m_bHasFocus = TRUE;
		bRes = TRUE;
		break;
	}

	return bRes;
}
//**************************************************************************************
void CFontNameComboBoxButton::Serialize (CArchive& ar)
{
	CBCGToolbarButton::Serialize (ar);

	// Override to disable item's data serialization!
	if (ar.IsLoading ())
	{
		ar >> m_iWidth;
		m_rect.right = m_rect.left + m_iWidth;
		ar >> m_dwStyle;
		ar >> m_iSelIndex;

		SetFonts ();
		SelectItem (m_iSelIndex);
	}
	else
	{
		ar << m_iWidth;
		ar << m_dwStyle;
		ar << m_iSelIndex;
	}
}
//****************************************************************************************
void CFontNameComboBoxButton::RebuildFonts (CDC& dc, BYTE nCharSet)
{
	CMapStringToPtr map;

	for (int i = 0; i < m_arrayFontDesc.GetSize (); i ++)
	{
		delete m_arrayFontDesc [i];
	}

	m_arrayFontDesc.SetSize (0);

	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));
	lf.lfCharSet = nCharSet;

	if (dc.m_hDC != NULL)
	{
		::EnumFontFamiliesEx(dc.m_hDC, &lf,
			(FONTENUMPROC) EnumFamPrinterCallBackEx, 0, NULL);
	}
	else
	{
		HDC hDC = theApp.m_dcScreen.m_hDC;
		ASSERT(hDC != NULL);

		::EnumFontFamiliesEx(hDC, &lf,
			(FONTENUMPROC) EnumFamScreenCallBackEx, 0, NULL);
	}
}
//****************************************************************************************
void CFontNameComboBoxButton::AddFont(ENUMLOGFONT* pelf, DWORD dwType, LPCTSTR lpszScript)
{
	LOGFONT& lf = pelf->elfLogFont;
	if (lf.lfCharSet == MAC_CHARSET) // don't put in MAC fonts, commdlg doesn't either
		return;
	// Don't display vertical font for FE platform
	if ((GetSystemMetrics(SM_DBCSENABLED)) && (lf.lfFaceName[0] == '@'))
		return;
	// don't put in non-printer raster fonts
	CFontDesc* pDesc = new CFontDesc(lf.lfFaceName, lpszScript,
		lf.lfCharSet, lf.lfPitchAndFamily, dwType);

	m_arrayFontDesc.Add (pDesc);
}
//****************************************************************************************
BOOL CALLBACK AFX_EXPORT CFontNameComboBoxButton::EnumFamPrinterCallBackEx(ENUMLOGFONTEX* pelf,
	NEWTEXTMETRICEX* /*lpntm*/, int FontType, LPVOID)
{
	DWORD dwData = PRINTER_FONT;
	if (FontType & TRUETYPE_FONTTYPE)
		dwData |= TT_FONT;
	else if (FontType & DEVICE_FONTTYPE)
		dwData |= DEVICE_FONT;

	AddFont ((ENUMLOGFONT*)pelf, dwData, CString(pelf->elfScript));
	return 1;
}
//****************************************************************************************
BOOL CALLBACK AFX_EXPORT CFontNameComboBoxButton::EnumFamScreenCallBackEx(ENUMLOGFONTEX* pelf,
	NEWTEXTMETRICEX* /*lpntm*/, int FontType, LPVOID pThis)
{
	// don't put in non-printer raster fonts
	if (FontType & RASTER_FONTTYPE)
		return 1;
	DWORD dwData = (FontType & TRUETYPE_FONTTYPE) ? TT_FONT : 0;
	AddFont((ENUMLOGFONT*)pelf, dwData, CString(pelf->elfScript));
	return 1;
}
//****************************************************************************************
void CFontNameComboBoxButton::SetFonts()
{
	CMapStringToPtr map;
	CString str;

	CFontComboBox* pCombo = (CFontComboBox*) GetComboBox ();
	pCombo->GetTheText(str);

	RemoveAllItems ();

	// now walk through the fonts and remove (charset) from fonts with only one

	// walk through fonts adding names to string map
	// first time add value 0, after that add value 1

	for (int i = 0; i < m_arrayFontDesc.GetSize (); i ++)
	{
		CFontDesc* pDesc = m_arrayFontDesc [i];
		ASSERT_VALID (pDesc);

		void* pv = NULL;
		if (map.Lookup(pDesc->m_strName, pv)) // found it
		{
			if (pv == NULL) // only one entry so far
			{
				map.RemoveKey(pDesc->m_strName);
				map.SetAt(pDesc->m_strName, (void*)1);
			}
		}
		else // not found
			map.SetAt(pDesc->m_strName, (void*)0);
	}

	for (i = 0; i < m_arrayFontDesc.GetSize (); i ++)
	{
		CFontDesc* pDesc = m_arrayFontDesc [i];

		str = pDesc->m_strName;
		void* pv = NULL;
		VERIFY(map.Lookup(str, pv));
		if (pv != NULL && !pDesc->m_strScript.IsEmpty())
		{
			str += " (";
			str += pDesc->m_strScript;
			str += ")";
		}

		AddItem (str, (DWORD)pDesc);
	}

	pCombo->SetTheText(str);
}

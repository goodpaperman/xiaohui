// FontCombo.h: interface for the CFontCombo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FONTCOMBO_H__F2E30723_F560_11D2_A713_0090274409AC__INCLUDED_)
#define AFX_FONTCOMBO_H__F2E30723_F560_11D2_A713_0090274409AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FlatComboBox.h"
#include "BCGToolbarComboBoxButton.h"

class CFontDesc;

struct CHARHDR : public tagNMHDR
{
	CHARFORMAT cf;
	CHARHDR() {cf.cbSize = sizeof(CHARFORMAT);}
};

#define FN_SETFORMAT    0x1000
#define FN_GETFORMAT    0x1001

/////////////////////////////////////////////////////////////////////////////
// CLocalComboBox

class CLocalComboBox : public CFlatComboBox
{
//Attributes
public:
	BOOL HasFocus()
	{
		HWND hWnd = ::GetFocus();
		return (hWnd == m_hWnd || ::IsChild(m_hWnd, hWnd));
	}

	void GetTheText(CString& str);
	void SetTheText(LPCTSTR lpszText,BOOL bMatchExact = FALSE);

protected:
	int m_nLimitText;

public:
	static int m_nFontHeight;
	static BOOL m_bHasFocus;
	static CDC m_dcPrinter;

// Operations
public:
	BOOL LimitText(int nMaxChars);
	void SetCharFormat(CCharFormat& cf);
	void NotifyOwner(UINT nCode);

	static void SyncToView(CWnd* pWnd);
	static void OnPrinterChanged();

// Implementation
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	// Generated message map functions
	//{{AFX_MSG(CLocalComboBox)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CFontComboBox

class CFontComboBox : public CLocalComboBox
{
public:
	CFontComboBox();

//Attributes
	CBitmap m_bmFontType;

//Operations
	void MatchFont (LPCTSTR lpszName, BYTE nCharSet);

//Overridables
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDIS);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMIS);
	virtual int CompareItem(LPCOMPAREITEMSTRUCT lpCIS);
	// Generated message map functions
	//{{AFX_MSG(CFontComboBox)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CSizeComboBox

class CSizeComboBox : public CLocalComboBox
{
public:
	CSizeComboBox();

//Attributes
	int m_nLogVert;
	int m_nTwipsLast;
public:
	void EnumFontSizes(CDC& dc, LPCTSTR pFontName);
	static BOOL FAR PASCAL EnumSizeCallBack(LOGFONT FAR* lplf,
		LPNEWTEXTMETRIC lpntm,int FontType, LPVOID lpv);
	void TwipsToPointString(LPTSTR lpszBuf, int nTwips);
	void SetTwipSize(int nSize);
	int GetTwipSize();
	void InsertSize(int nSize);
};


//////////////////////////////////////////////////////////////////////////////////
// CFontNameComboBoxButton class

class CFontNameComboBoxButton : public CBCGToolbarComboBoxButton  
{
	DECLARE_SERIAL(CFontNameComboBoxButton)

public:
	CFontNameComboBoxButton() 
	{
		Initialize ();
	}

	CFontNameComboBoxButton(UINT uiID, int iImage, DWORD dwStyle = CBS_DROPDOWNLIST, int iWidth = 0) :
		CBCGToolbarComboBoxButton (uiID, iImage, dwStyle, iWidth)
	{
		Initialize ();
	}

	virtual ~CFontNameComboBoxButton();

	virtual CComboBox* CreateCombo (CWnd* pWndParent, const CRect& rect);
	virtual BOOL NotifyCommand (int iNotifyCode);
	virtual void Serialize(CArchive& ar);

	static void AddFont(ENUMLOGFONT* pelf, DWORD dwType, LPCTSTR lpszScript = NULL);
	static void RebuildFonts (CDC& dc, BYTE nCharSet = DEFAULT_CHARSET);

	void SetFonts ();

protected:
	void Initialize ();

	static BOOL CALLBACK AFX_EXPORT EnumFamScreenCallBackEx(
		ENUMLOGFONTEX* pelf, NEWTEXTMETRICEX* /*lpntm*/, int FontType,
		LPVOID pThis);
	static BOOL CALLBACK AFX_EXPORT EnumFamPrinterCallBackEx(
		ENUMLOGFONTEX* pelf, NEWTEXTMETRICEX* /*lpntm*/, int FontType,
		LPVOID pThis);


protected:
	static CArray<CFontDesc*, CFontDesc*> m_arrayFontDesc;
	static int nCount;
};

//////////////////////////////////////////////////////////////////////////////////
// CFontSizeComboBoxButton class

class CFontSizeComboBoxButton : public CBCGToolbarComboBoxButton  
{
	DECLARE_SERIAL(CFontSizeComboBoxButton)

public:
	CFontSizeComboBoxButton() {}
	CFontSizeComboBoxButton(UINT uiID, int iImage, DWORD dwStyle = CBS_DROPDOWNLIST, int iWidth = 0) :
		CBCGToolbarComboBoxButton (uiID, iImage, dwStyle, iWidth) {}

	virtual CComboBox* CreateCombo (CWnd* pWndParent, const CRect& rect);
	virtual BOOL NotifyCommand (int iNotifyCode);
};

#endif // !defined(AFX_FONTCOMBO_H__F2E30723_F560_11D2_A713_0090274409AC__INCLUDED_)

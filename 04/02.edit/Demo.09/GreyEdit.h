#pragma once

#define MAXRGB					(RGB(255,255,255) + 1)
#define CTLCOLOR_WINDOWTEXT		(MAXRGB + COLOR_WINDOWTEXT)

class CGreyEdit : public CEdit
{
	DECLARE_DYNAMIC(CGreyEdit)

public:
	CGreyEdit();
	~CGreyEdit();

protected:
	CFont m_italicFont;
	CFont m_normalFont;
protected:
	CFont* GetItalicFont()
	{
		return &m_italicFont;
	}
	CFont* GetNormalFont()
	{
		return &m_normalFont;
	}
protected:
	int PointSizeToHeight(int iPointSize, HDC hDC);

protected:
	COLORREF GetTextColor(){return(m_clrTextColor);}
	void SetToGreyItalic();
	void SetToNormal();
	void SetText(CString &strText);
	CString GetText();
	BOOL IsDirty();
	void SetInitialText(CString &strInitialText);
	
public:
	BOOL Init(	UINT uiControlId, 
				CWnd *pParent, 
				const char *lpszDefaultText,
				LONG lBackgroundColor = CTLCOLOR_WINDOWTEXT,
				UINT uiAlignment = TA_LEFT);
				
	BOOL Init(	UINT uiControlId, 
				CWnd *pParent, 
				const char *lpszDefaultText,
				COLORREF clrBackgroundColor,
				UINT uiAlignment = TA_LEFT);
	
protected:
	UINT m_uiAlignment;
	CString m_sDefaultText;
	COLORREF m_clrTextColor;
	LONG m_lBackgroundColor;
	BOOL m_bInitialized;
	CBrush m_brBackground;
	CString m_strInitialText;
	
	BOOL UnSubclass();
	int PointSizeToHeight(int iPointSize, CDC *pDC);
	void SetBlankFieldToDefaultText();
	void CreateBackgroundBrush();

	//{{AFX_MSG(CGreyEdit)
	afx_msg void OnDestroy();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP();
};

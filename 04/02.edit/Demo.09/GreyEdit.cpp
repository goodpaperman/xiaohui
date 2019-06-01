#include "stdafx.h"  
#include "GreyEdit.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define MAXRGB					(RGB(255,255,255) + 1)
#define CTLCOLOR_WINDOWTEXT		(MAXRGB + COLOR_WINDOWTEXT)

IMPLEMENT_DYNAMIC(CGreyEdit, CEdit)
BEGIN_MESSAGE_MAP(CGreyEdit, CEdit)
	//{{AFX_MSG_MAP(CGreyEdit)
	ON_WM_DESTROY()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CGreyEdit::CGreyEdit()
{
	m_bInitialized = FALSE;
	m_lBackgroundColor = -1;
}

CGreyEdit::~CGreyEdit()
{
	if (m_bInitialized)
	{
		m_brBackground.DeleteObject();
	}
}


BOOL CGreyEdit::Init(UINT uiControlId, 
								CWnd *pParent, 
								const char *lpszDefaultText,
								COLORREF clrBackgroundColor,
								UINT uiAlignment)
{
	// Set fonts 
	CClientDC dcClient(CWnd::GetDesktopWindow());
	LOGFONT lf;
	
	memset(&lf, 0, sizeof LOGFONT);
	lf.lfHeight = PointSizeToHeight( 8, dcClient.m_hDC );       
	lf.lfWeight = FW_NORMAL;
	strcpy(lf.lfFaceName, "MS Sans Serif");               
	//lf.lfWeight = FW_BOLD;	
	lf.lfWeight = FW_NORMAL;
	VERIFY(m_normalFont.CreateFontIndirect(&lf));
	
	lf.lfItalic = TRUE;
	VERIFY(m_italicFont.CreateFontIndirect(&lf));

	return (Init(uiControlId, 
					pParent, 
					lpszDefaultText,
					(LONG)clrBackgroundColor,
					uiAlignment));
}								

BOOL CGreyEdit::Init(UINT uiControlId, 
								CWnd *pParent, 
								const char *lpszDefaultText,
								LONG lBackgroundColor,
								UINT uiAlignment)
{
	BOOL bSuccess = SubclassDlgItem(uiControlId,pParent);
	if (TRUE == bSuccess)
	{
		m_sDefaultText = lpszDefaultText;
		m_uiAlignment = uiAlignment;

		SetWindowText(m_sDefaultText);
		SetBlankFieldToDefaultText();
		m_lBackgroundColor = lBackgroundColor;
		CreateBackgroundBrush();	
		m_bInitialized = TRUE;
	}

	return (bSuccess);
}

int CGreyEdit::PointSizeToHeight(int iPointSize, CDC *pDC)
{
	return ( -( MulDiv ( iPointSize, pDC->GetDeviceCaps( LOGPIXELSY ), 72 ) ) );
}

BOOL CGreyEdit::UnSubclass()
{
    WNDPROC     OldWndProc;
    WNDPROC*    lplpfn = GetSuperWndProcAddr();

	// return if null
    if ( !*lplpfn )
        return FALSE;

    // Set the original window procedure
    OldWndProc = (WNDPROC)::SetWindowLong( m_hWnd, GWL_WNDPROC, (LONG) *lplpfn );

    // A subclassed window's procedure is always AfxWndProc.
    // If this is not TRUE, then it's not a subclassed window.
    if ( OldWndProc != AfxWndProc )
        return FALSE;

    Detach();
    return TRUE;
}

void CGreyEdit::OnDestroy()
{
	UnSubclass();
	CEdit::OnDestroy();
}

void CGreyEdit::SetToGreyItalic()
{
	SetFont(GetItalicFont());
	m_clrTextColor = RGB(192,192,192);
}

void CGreyEdit::SetToNormal()
{
	SetFont(GetNormalFont());
	m_clrTextColor = ::GetSysColor(COLOR_WINDOWTEXT);
}

void CGreyEdit::SetText(CString &strText)
{
	SetWindowText(strText);	
	SetBlankFieldToDefaultText();
}

CString CGreyEdit::GetText()
{
	CString strText;
	GetWindowText(strText);	
	
	strText.TrimLeft();
	strText.TrimRight();

	if (strText == m_sDefaultText)
	{
		strText = "";
	}
	return (strText);
}

void CGreyEdit::SetBlankFieldToDefaultText()
{
	CString strText;
	
	// set to default if it's blank
	GetWindowText(strText);

	strText.TrimLeft();
	strText.TrimRight();

	if (!strText.GetLength())
	{
		SetWindowText(m_sDefaultText);
	}

	// if it's default, set to grey italic	
	GetWindowText(strText);
	if (strText == m_sDefaultText)
	{
		SetToGreyItalic();
	}
	else
	{
		SetToNormal();
	}
	Invalidate(FALSE);
}

void CGreyEdit::OnSetFocus(CWnd* pOldWnd)
{
	SetToNormal();
	
	CString strText;
	GetWindowText(strText);
	if (strText == m_sDefaultText)
	{
		strText = "";
		SetWindowText(strText);
	}
	
	CEdit::OnSetFocus(pOldWnd);
}

void CGreyEdit::OnKillFocus(CWnd* pNewWnd)
{
	SetBlankFieldToDefaultText();
	
	CEdit::OnKillFocus(pNewWnd);
}

HBRUSH CGreyEdit::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbrReturnBrush;
	CPoint ptBrushOrigin(0,0);
	
	// make sure we have the most recent color for the background
	m_brBackground.DeleteObject();
	CreateBackgroundBrush();

	switch (nCtlColor)
	{
		case CTLCOLOR_EDIT:
			pDC->SetTextColor(GetTextColor());
			pDC->SetBkMode(TRANSPARENT);    
			ClientToScreen(&ptBrushOrigin);
			m_brBackground.UnrealizeObject();			
			pDC->SetBrushOrg(ptBrushOrigin.x, ptBrushOrigin.y);
			hbrReturnBrush = (HBRUSH)m_brBackground.m_hObject;
		break;
				
		case CTLCOLOR_MSGBOX:
			ClientToScreen(&ptBrushOrigin);
			m_brBackground.UnrealizeObject();			
			pDC->SetBrushOrg(ptBrushOrigin.x, ptBrushOrigin.y);
			hbrReturnBrush = (HBRUSH)m_brBackground.m_hObject;
		break;
		
		default:  
			// return a brush provided by the default window procedure
			hbrReturnBrush = (HBRUSH)Default();
	}
	
	return (hbrReturnBrush);
}

void CGreyEdit::CreateBackgroundBrush()
{
	ASSERT(m_lBackgroundColor > -1);
	COLORREF clrBackground;
	
	// an RGB value up to RGB(255,255,255)
	if (m_lBackgroundColor < MAXRGB)
	{
		clrBackground = (COLORREF)m_lBackgroundColor;
	}
	else
	{
		clrBackground = ::GetSysColor(m_lBackgroundColor - MAXRGB);
	}
	m_brBackground.CreateSolidBrush(clrBackground);
}

BOOL CGreyEdit::IsDirty()
{
	CString strCurrentText;
	GetWindowText(strCurrentText);
	
	return (strCurrentText != m_strInitialText && strCurrentText != m_sDefaultText);
}

void CGreyEdit::SetInitialText(CString &strInitialText)
{
	m_strInitialText = strInitialText;
}

int CGreyEdit::PointSizeToHeight(int iPointSize, HDC hDC)
{
	int iRetVal = 0;
	
	ASSERT(NULL != hDC);
	if (NULL != hDC)
	{                                
		iRetVal =  -(MulDiv(iPointSize, ::GetDeviceCaps( hDC, LOGPIXELSY ), 72));
	}

	return (iRetVal);
}

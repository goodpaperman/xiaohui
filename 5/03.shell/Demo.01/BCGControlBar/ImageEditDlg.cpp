// ImageEditDlg.cpp : implementation file
//

#include "stdafx.h"
#include <afxpriv.h>
#include "bcgbarres.h"
#include "ImageEditDlg.h"
#include "bcglocalres.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImageEditDlg dialog


#pragma warning (disable : 4355)

CImageEditDlg::CImageEditDlg(CBitmap* pBitmap, SIZE sizeImage, CWnd* pParent /*=NULL*/)
	: CDialog(CImageEditDlg::IDD, pParent),
	m_pBitmap (pBitmap),
	m_sizeImage (sizeImage),
	m_pWndPaletteBarDummyFrame (NULL),
	m_wndLargeDrawArea (this)
{
	ASSERT (m_pBitmap != NULL);

	//{{AFX_DATA_INIT(CImageEditDlg)
	//}}AFX_DATA_INIT
}

#pragma warning (default : 4355)

void CImageEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImageEditDlg)
	DDX_Control(pDX, IDC_BCGBARRES_PALETTE, m_wndPaletteBarLocation);
	DDX_Control(pDX, IDC_BCGBARRES_PREVIEW_AREA, m_wndPreview);
	DDX_Control(pDX, IDC_BCGBARRES_DRAW_AREA, m_wndLargeDrawArea);
	DDX_Control(pDX, IDC_BCGBARRES_COLORS, m_wndColor);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CImageEditDlg, CDialog)
	//{{AFX_MSG_MAP(CImageEditDlg)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BCGBARRES_COLORS, OnColors)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_KICKIDLE, OnKickIdle)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageEditDlg message handlers

BOOL CImageEditDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_wndLargeDrawArea.SetBitmap (m_pBitmap);

	//------------------------
	// Create the palette bar:
	//------------------------	
	{
		CBCGLocalResource locaRes;

		CRect rectPaletteBar;
		m_wndPaletteBarLocation.GetClientRect (&rectPaletteBar);
		m_wndPaletteBarLocation.MapWindowPoints (this, &rectPaletteBar);
		rectPaletteBar.DeflateRect (2, 2);

		m_wndPaletteBar.Create (this);
		m_wndPaletteBar.LoadToolBar (IDR_BCGRES_PALETTE, 0, 0, TRUE /* Locked bar */);

		m_wndPaletteBar.SetBarStyle(m_wndPaletteBar.GetBarStyle() |
			CBRS_TOOLTIPS | CBRS_FLYBY);
			
		m_wndPaletteBar.SetBarStyle (
			m_wndPaletteBar.GetBarStyle () & 
				~(CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

		m_wndPaletteBar.WrapToolBar (rectPaletteBar.Width () - 10);
		m_wndPaletteBar.MoveWindow (rectPaletteBar);

		m_wndPaletteBar.SetWindowPos (&wndTop, -1, -1, -1, -1,
			SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);

		m_pWndPaletteBarDummyFrame = new CPaletteCommandFrameWnd;
		m_pWndPaletteBarDummyFrame->Create (0, 
			CFrameWnd::rectDefault, this);

		m_wndPaletteBar.SetOwner (m_pWndPaletteBarDummyFrame);
	}
	
	//---------------------
	// Define preview area:
	//---------------------
	m_wndPreview.GetClientRect (&m_rectPreviewImage);
	m_wndPreview.MapWindowPoints (this, &m_rectPreviewImage);

	m_rectPreviewImage.left = (m_rectPreviewImage.left + m_rectPreviewImage.right - m_sizeImage.cx) / 2;
	m_rectPreviewImage.right = m_rectPreviewImage.left + m_sizeImage.cx;

	m_rectPreviewImage.top = (m_rectPreviewImage.top + m_rectPreviewImage.bottom - m_sizeImage.cy) / 2;
	m_rectPreviewImage.bottom = m_rectPreviewImage.top + m_sizeImage.cy;

	m_rectPreviewFrame = m_rectPreviewImage;
	m_rectPreviewFrame.InflateRect (4, 4);

	m_wndLargeDrawArea.m_rectParentPreviewArea = m_rectPreviewImage;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
//********************************************************************************
void CImageEditDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	dc.Draw3dRect (&m_rectPreviewFrame,
					::GetSysColor (COLOR_3DHILIGHT),
					::GetSysColor (COLOR_3DSHADOW));

	CBitmap* pbmOld = NULL;
	CDC dcMem;
		
	dcMem.CreateCompatibleDC (&dc);
	pbmOld = dcMem.SelectObject (m_pBitmap);

	dc.BitBlt (m_rectPreviewImage.left, m_rectPreviewImage.top,
				m_sizeImage.cx, m_sizeImage.cy, &dcMem,
				0, 0, SRCCOPY);

	dcMem.SelectObject(pbmOld);
	dcMem.DeleteDC();
}
//********************************************************************************
void CImageEditDlg::Clear() 
{
	CWindowDC	dc (this);
	CDC 		memDC;	

	memDC.CreateCompatibleDC (&dc);
	
	CBitmap* pOldBitmap = memDC.SelectObject (m_pBitmap);

	CRect rect (0, 0, m_sizeImage.cx, m_sizeImage.cy);
	memDC.FillSolidRect (&rect, ::GetSysColor (COLOR_3DFACE));

	memDC.SelectObject (pOldBitmap);

	InvalidateRect (m_rectPreviewImage);
	m_wndLargeDrawArea.Invalidate ();
}
//********************************************************************************
void CImageEditDlg::OnColors() 
{
	m_wndLargeDrawArea.SetColor (m_wndColor.GetColor ());
}
//********************************************************************************
void CImageEditDlg::Copy() 
{
	CBCGLocalResource locaRes;

	if (m_pBitmap == NULL)
	{
		return;
	}

	try
	{
		CWindowDC dc (this);

		//----------------------
		// Create a bitmap copy:
		//----------------------
		CDC memDCDest;
		memDCDest.CreateCompatibleDC (NULL);
		
		CDC memDCSrc;
		memDCSrc.CreateCompatibleDC (NULL);
		
		CBitmap bitmapCopy;
		if (!bitmapCopy.CreateCompatibleBitmap (&dc, m_sizeImage.cx, m_sizeImage.cy))
		{
			AfxMessageBox (IDP_BCGBARRES_CANT_COPY_BITMAP);
			return;
		}

		CBitmap* pOldBitmapDest = memDCDest.SelectObject (&bitmapCopy);
		CBitmap* pOldBitmapSrc = memDCSrc.SelectObject (m_pBitmap);

		memDCDest.BitBlt (0, 0, m_sizeImage.cx, m_sizeImage.cy,
						&memDCSrc, 0, 0, SRCCOPY);

		memDCDest.SelectObject (pOldBitmapDest);
		memDCSrc.SelectObject (pOldBitmapSrc);

		if (!OpenClipboard ())
		{
			AfxMessageBox (IDP_BCGBARRES_CANT_COPY_BITMAP);
			return;
		}

		if (!::EmptyClipboard ())
		{
			AfxMessageBox (IDP_BCGBARRES_CANT_COPY_BITMAP);
			::CloseClipboard ();
			return;
		}


		HANDLE hclipData = ::SetClipboardData (CF_BITMAP, bitmapCopy.Detach ());
		if (hclipData == NULL)
		{
			AfxMessageBox (IDP_BCGBARRES_CANT_COPY_BITMAP);
			TRACE (_T("CImageEditDlg::Copy() error. Error code = %x\n"), GetLastError ());
		}

		::CloseClipboard ();
	}
	catch (...)
	{
		CBCGLocalResource locaRes;
		AfxMessageBox (IDP_BCGBARRES_INTERLAL_ERROR);
	}
}
//********************************************************************************
void CImageEditDlg::Paste() 
{
	CBCGLocalResource locaRes;

	COleDataObject data;
	if (!data.AttachClipboard ())
	{
		AfxMessageBox (IDP_BCGBARRES_CANT_PASTE_BITMAP);
		return;
	}

	if (!data.IsDataAvailable (CF_BITMAP))
	{
		AfxMessageBox (IDP_BCGBARRES_CANT_PASTE_BITMAP);
		return;
	}

	tagSTGMEDIUM dataMedium;
	if (!data.GetData (CF_BITMAP, &dataMedium))
	{
		AfxMessageBox (IDP_BCGBARRES_CANT_PASTE_BITMAP);
		return;
	}

	CBitmap* pBmpClip = CBitmap::FromHandle (dataMedium.hBitmap);
	if (pBmpClip == NULL)
	{
		AfxMessageBox (IDP_BCGBARRES_CANT_PASTE_BITMAP);
		return;
	}

	BITMAP bmp;
	pBmpClip->GetBitmap (&bmp);

	if (bmp.bmWidth != m_sizeImage.cx ||
		bmp.bmHeight != m_sizeImage.cy)
	{
		CString strMessage;
		strMessage.Format (IDS_BCGBARRES_WRONG_IMAGE_SIZE,
						m_sizeImage.cx, m_sizeImage.cy);
		MessageBox (strMessage);
		return;
	}

	CDC memDCDst;
	CDC memDCSrc;

	memDCSrc.CreateCompatibleDC (NULL);
	memDCDst.CreateCompatibleDC (NULL);
	
	CBitmap* pSrcOldBitmap = memDCSrc.SelectObject (pBmpClip);
	if (pSrcOldBitmap == NULL)
	{
		AfxMessageBox (IDP_BCGBARRES_CANT_PASTE_BITMAP);
		return;
	}

	CBitmap* pDstOldBitmap = memDCDst.SelectObject (m_pBitmap);
	if (pDstOldBitmap == NULL)
	{
		AfxMessageBox (IDP_BCGBARRES_CANT_PASTE_BITMAP);
		
		memDCSrc.SelectObject (pSrcOldBitmap);
		return;
	}

	memDCDst.BitBlt (0, 0, m_sizeImage.cx, m_sizeImage.cy,
					&memDCSrc, 0, 0, SRCCOPY);

	memDCDst.SelectObject (pDstOldBitmap);
	memDCSrc.SelectObject (pSrcOldBitmap);

	InvalidateRect (m_rectPreviewImage);
	m_wndLargeDrawArea.Invalidate ();
}
//****************************************************************************************
LRESULT CImageEditDlg::OnKickIdle(WPARAM, LPARAM)
{
	CControlBar* pBar = &m_wndPaletteBar;
	pBar->OnUpdateCmdUI (m_pWndPaletteBarDummyFrame, TRUE);

    return 0;
}
//****************************************************************************************
BOOL CImageEditDlg::OnPickColor (COLORREF color)
{
	if (!m_wndColor.SelectColor (color))
	{
		return FALSE;
	}

	//-----------------------------------------
	// Move to the pen mode (not so good :-(!):
	//-----------------------------------------
	m_wndLargeDrawArea.SetMode (CImagePaintArea::IMAGE_EDIT_MODE_PEN);
	return TRUE;
}

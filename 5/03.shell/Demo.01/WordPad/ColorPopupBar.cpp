#include "stdafx.h"
#include <..\\src\\afximpl.h>
#include <math.h>
#include "wordpad.h"
#include "BCGPopupMenu.h"
#include "ColorPopupBar.h"
#include "ColorButton.h"
#include "ColorAutoButton.h"
#include "colorlis.h"

#pragma warning (disable : 4201)
	#include "mmsystem.h"
#pragma warning (default : 4201)

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define DEFAULT_BOX_VALUE -3
#define CUSTOM_BOX_VALUE  -2
#define INVALID_COLOUR    -1

#define MAX_COLOURS      100

static const int iVertMargin = 4;
static const int iHorzMargin = 4;

ColourTableEntry CColorPopupBar::m_crColours[] = 
{
    { RGB(0x00, 0x00, 0x00),    _T("Black")             },
    { RGB(0xA5, 0x2A, 0x00),    _T("Brown")             },
    { RGB(0x00, 0x40, 0x40),    _T("Dark Olive Green")  },
    { RGB(0x00, 0x55, 0x00),    _T("Dark Green")        },
    { RGB(0x00, 0x00, 0x5E),    _T("Dark Teal")         },
    { RGB(0x00, 0x00, 0x8B),    _T("Dark blue")         },
    { RGB(0x4B, 0x00, 0x82),    _T("Indigo")            },
    { RGB(0x28, 0x28, 0x28),    _T("Dark grey")         },

    { RGB(0x8B, 0x00, 0x00),    _T("Dark red")          },
    { RGB(0xFF, 0x68, 0x20),    _T("Orange")            },
    { RGB(0x8B, 0x8B, 0x00),    _T("Dark yellow")       },
    { RGB(0x00, 0x93, 0x00),    _T("Green")             },
    { RGB(0x38, 0x8E, 0x8E),    _T("Teal")              },
    { RGB(0x00, 0x00, 0xFF),    _T("Blue")              },
    { RGB(0x7B, 0x7B, 0xC0),    _T("Blue-grey")         },
    { RGB(0x66, 0x66, 0x66),    _T("Grey - 40")         },

    { RGB(0xFF, 0x00, 0x00),    _T("Red")               },
    { RGB(0xFF, 0xAD, 0x5B),    _T("Light orange")      },
    { RGB(0x32, 0xCD, 0x32),    _T("Lime")              }, 
    { RGB(0x3C, 0xB3, 0x71),    _T("Sea green")         },
    { RGB(0x7F, 0xFF, 0xD4),    _T("Aqua")              },
    { RGB(0x7D, 0x9E, 0xC0),    _T("Light blue")        },
    { RGB(0x80, 0x00, 0x80),    _T("Violet")            },
    { RGB(0x7F, 0x7F, 0x7F),    _T("Grey - 50")         },

    { RGB(0xFF, 0xC0, 0xCB),    _T("Pink")              },
    { RGB(0xFF, 0xD7, 0x00),    _T("Gold")              },
    { RGB(0xFF, 0xFF, 0x00),    _T("Yellow")            },    
    { RGB(0x00, 0xFF, 0x00),    _T("Bright green")      },
    { RGB(0x40, 0xE0, 0xD0),    _T("Turquoise")         },
    { RGB(0xC0, 0xFF, 0xFF),    _T("Skyblue")           },
    { RGB(0x48, 0x00, 0x48),    _T("Plum")              },
    { RGB(0xC0, 0xC0, 0xC0),    _T("Light grey")        },

    { RGB(0xFF, 0xE4, 0xE1),    _T("Rose")              },
    { RGB(0xD2, 0xB4, 0x8C),    _T("Tan")               },
    { RGB(0xFF, 0xFF, 0xE0),    _T("Light yellow")      },
    { RGB(0x98, 0xFB, 0x98),    _T("Pale green ")       },
    { RGB(0xAF, 0xEE, 0xEE),    _T("Pale turquoise")    },
    { RGB(0x68, 0x83, 0x8B),    _T("Pale blue")         },
    { RGB(0xE6, 0xE6, 0xFA),    _T("Lavender")          },
    { RGB(0xFF, 0xFF, 0xFF),    _T("White")             }
};

UINT CPN_SELCHANGE = ::RegisterWindowMessage (_T("CPN_SELCHANGE"));			// Colour Picker Selection change

/////////////////////////////////////////////////////////////////////////////
// CColorPopupBar

IMPLEMENT_SERIAL(CColorPopupBar, CBCGPopupMenuBar, 1)

CColorPopupBar::CColorPopupBar(COLORREF color, int nAutoColorIndex) :
	m_Color (color),
	m_nAutoColorIndex (nAutoColorIndex)
{
    Initialise();
}

CColorPopupBar::~CColorPopupBar()
{
    m_Palette.DeleteObject();
}

void CColorPopupBar::Initialise()
{
    m_nNumColours = sizeof(m_crColours)/sizeof(ColourTableEntry);
    ASSERT(m_nNumColours <= MAX_COLOURS);
    if (m_nNumColours > MAX_COLOURS)
        m_nNumColours = MAX_COLOURS;

	m_nNumColumns = 8;
    m_nNumRows = m_nNumColours / m_nNumColumns;

    // Create the palette
    struct {
        LOGPALETTE    LogPalette;
        PALETTEENTRY  PalEntry[MAX_COLOURS];
    } pal;

    LOGPALETTE* pLogPalette = (LOGPALETTE*) &pal;
    pLogPalette->palVersion    = 0x300;
    pLogPalette->palNumEntries = (WORD) m_nNumColours; 

    for (int i = 0; i < m_nNumColours; i++)
    {
        pLogPalette->palPalEntry[i].peRed   = GetRValue(m_crColours[i].crColour);
        pLogPalette->palPalEntry[i].peGreen = GetGValue(m_crColours[i].crColour);
        pLogPalette->palPalEntry[i].peBlue  = GetBValue(m_crColours[i].crColour);
        pLogPalette->palPalEntry[i].peFlags = 0;
    }

    m_Palette.CreatePalette(pLogPalette);
}
//*****************************************************************************************
void CColorPopupBar::AdjustLocations ()
{
	if (GetSafeHwnd () == NULL ||
		!::IsWindow (m_hWnd))
	{
		return;
	}

	ASSERT_VALID(this);

	CRect rectClient;	// Client area rectangle
	GetClientRect (&rectClient);

	int x = rectClient.left + iHorzMargin;
	int y = rectClient.top + iVertMargin;
	int i = 0;

	for (POSITION pos = m_Buttons.GetHeadPosition (); pos != NULL; i ++)
	{
		CBCGToolbarButton* pButton = (CBCGToolbarButton*) m_Buttons.GetNext (pos);
		ASSERT (pButton != NULL);

		CRect rectButton;

		if (i == 0 && m_nAutoColorIndex >= 0)	// Automatic color or separator
		{
			rectButton = CRect (
				CPoint (x, y),
				CSize (rectClient.Width () - 2 * iHorzMargin, 
						m_nAutoBoxHeight - iVertMargin / 2));
			y += m_nAutoBoxHeight;
		}
		else
		{
			if (x + m_BoxSize.cx >= rectClient.right + iHorzMargin)
			{
				x = rectClient.left + iHorzMargin;
				y += m_BoxSize.cy;
			}

			rectButton = CRect (CPoint (x, y), m_BoxSize);
			x += m_BoxSize.cx;
		}

		if (pButton->m_rect != rectButton)
		{
			pButton->m_rect = rectButton;
			pButton->OnMove ();
		}
	}
}
//***************************************************************************************
CSize CColorPopupBar::CalcSize ()
{
	CSize size (0, 0);

	size.cx = m_nNumColumns * m_BoxSize.cx;
	size.cy = m_nNumRows * m_BoxSize.cy;

	if (m_nAutoColorIndex >= 0)
	{
		size.cy += m_nAutoBoxHeight;
	}

	size.cy += 2 * iVertMargin;
	size.cx += 2 * iHorzMargin;

	return size;
}

BEGIN_MESSAGE_MAP(CColorPopupBar, CBCGPopupMenuBar)
	//{{AFX_MSG_MAP(CColorPopupBar)
	ON_WM_CREATE()
	ON_WM_QUERYNEWPALETTE()
	ON_WM_PALETTECHANGED()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorPopupBar message handlers

int CColorPopupBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPopupMenuBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_BoxSize = GetMenuImageSize ();
	m_BoxSize.cx += afxData.cxBorder2 * 2;
	m_BoxSize.cy += afxData.cyBorder2 * 2;

	m_nAutoBoxHeight = m_BoxSize.cy * 3 / 2;

	if (m_nAutoColorIndex >= 0)	// Automatic
	{
		InsertButton (
			new CColorAutoButton (m_nAutoColorIndex,
				_T("Automatic"),
				m_Color == (COLORREF) -1));
	}
	
	for (int i = 0; i < m_nNumColours; i ++)
	{
		InsertButton (
			new CColorButton (m_crColours [i].crColour,
							m_crColours [i].szName,
							m_Color == m_crColours [i].crColour));
	}
	
	return 0;
}
//*************************************************************************************
void CColorPopupBar::DoPaint(CDC* pDC)
{
    // Select and realize the palette
    CPalette* pOldPalette = NULL;
    if (pDC->GetDeviceCaps(RASTERCAPS) & RC_PALETTE)
    {
        pOldPalette = pDC->SelectPalette(&m_Palette, FALSE);
        pDC->RealizePalette();
    }

	CBCGPopupMenuBar::DoPaint(pDC);

    if (pOldPalette != NULL)
	{
        pDC->SelectPalette(pOldPalette, FALSE);
	}
}
//*************************************************************************************
BOOL CColorPopupBar::OnQueryNewPalette() 
{
    Invalidate();    
	return CBCGPopupMenuBar::OnQueryNewPalette();
}
//*************************************************************************************
void CColorPopupBar::OnPaletteChanged(CWnd* pFocusWnd) 
{
	CBCGPopupMenuBar::OnPaletteChanged(pFocusWnd);
	
    if (pFocusWnd->GetSafeHwnd() != GetSafeHwnd())
	{
        Invalidate();
	}
}
//*************************************************************************************
BOOL CColorPopupBar::OnSendCommand (const CBCGToolbarButton* pButton)
{
	COLORREF color = (COLORREF) -1;

	CColorButton* pColorButton = DYNAMIC_DOWNCAST (CColorButton, pButton);
	if (pColorButton != NULL)
	{
		color = pColorButton->GetColor ();
	}

	AfxGetMainWnd ()->SendMessage (CPN_SELCHANGE, (WPARAM) color);

	CBCGPopupMenu* pParentMenu = DYNAMIC_DOWNCAST (CBCGPopupMenu, GetParent ());
	if (pParentMenu != NULL)
	{
		CColorMenuButton* pColorMenuButton = 
			DYNAMIC_DOWNCAST (CColorMenuButton, pParentMenu->GetParentButton ());

		if (pColorMenuButton != NULL)
		{
			pColorMenuButton->SetColor (color);
		}

		//--------------------
		// Deactivate menubar:
		//--------------------
		CBCGToolBar* pToolBar = pParentMenu->GetParentToolBar ();
		if (pToolBar != NULL)
		{
			pToolBar->Deactivate ();
		}
	}

	//-----------------------
	// Close he parent frame:
	//-----------------------
	CFrameWnd* pParentFrame = GetParentFrame ();
	ASSERT_VALID (pParentFrame);

	pParentFrame->DestroyWindow ();
	return TRUE;
}
//*************************************************************************************
int CColorPopupBar::OnToolHitTest(CPoint point, TOOLINFO* pTI) const
{
	if (CBCGPopupMenuBar::OnToolHitTest(point, pTI) == -1)
	{
		return -1;
	}

	return ((CColorPopupBar*)this)->HitTest(point);
}

// ColorBtn.cpp : implementation file

#include "stdafx.h"
#include "ColorBtn.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CColorBtn

CColorBtn::CColorBtn()
{
    m_CurrentColor = RGB(255,255,255);

    m_ColorDlg.m_Parent = this;   // This will allow the dialog to position itself

    // Create the pens and brushes that we'll need to draw the button

    m_NullPen.CreateStockObject(NULL_PEN);
    m_BlackPen.CreateStockObject(BLACK_PEN);
    m_WhitePen.CreateStockObject(WHITE_PEN);

    m_NullBrush.CreateStockObject(NULL_BRUSH);
    m_BackBrush.CreateSolidBrush(GetSysColor(COLOR_3DFACE));
    m_DkGrayPen.CreatePen(PS_SOLID,1,RGB(128,128,128)); 

    m_ColorWellShape = RECTANGLE;

}

CColorBtn::~CColorBtn()
{
}


BEGIN_MESSAGE_MAP(CColorBtn, CButton)
	//{{AFX_MSG_MAP(CColorBtn)	
	ON_CONTROL_REFLECT(BN_CLICKED, OnClicked)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorBtn message handlers


void CColorBtn::DrawItem(LPDRAWITEMSTRUCT lpd)
{
    // Draw the button
    CBrush colorbrush;
    CDC DC;
    DC.Attach(lpd->hDC);
    int top,left,bottom,right;

    // Store this for convenience
    top    = lpd->rcItem.top;
    left   = lpd->rcItem.left;
    bottom = lpd->rcItem.bottom;
    right  = lpd->rcItem.right;
                
    colorbrush.CreateSolidBrush(m_CurrentColor);
    
    m_OldPen   = DC.SelectObject(&m_NullPen);
    m_OldBrush = DC.SelectObject(&m_BackBrush);

    // Clear the background using the 3DFACE color.
    DC.Rectangle(&lpd->rcItem);

    // Draw the border
    if (!(lpd->itemState & ODS_SELECTED))
    {
        // Button is up
        DC.SelectObject(&m_BlackPen);
        DC.MoveTo(left,bottom-1);
        DC.LineTo(right-1,bottom-1);
        DC.LineTo(right-1,top);
        DC.SelectObject(&m_DkGrayPen);
        DC.MoveTo(left+1,bottom-2);
        DC.LineTo(right-2,bottom-2);
        DC.LineTo(right-2,top+1);
        DC.SelectObject(&m_WhitePen);
        DC.LineTo(left+1,top+1);
        DC.LineTo(left+1,bottom-2);    
    }
    else
    {
        // Button is down
        DC.SelectObject(&m_DkGrayPen);            
        DC.MoveTo(left,bottom-1);
        DC.LineTo(left,top);
        DC.LineTo(right-1,top);
        DC.SelectObject(&m_WhitePen);
        DC.MoveTo(right-1,top-1);
        DC.LineTo(right-1,bottom-1);
        DC.LineTo(left+1,bottom-1);
        DC.SelectObject(&m_BlackPen);
        DC.MoveTo(left+1,bottom-2);
        DC.LineTo(left+1,top+1);
        DC.LineTo(right-2,top+1);
        // by moving this, we get the things inside the button
        // to draw themselves one pixel down and one to the right.
        // This completes the "pushed" effect
        left++;
        right++;
        bottom++;
        top++;
    }

    // The division
    DC.SelectObject(&m_WhitePen); 
    DC.MoveTo(right-10,top+4);
    DC.LineTo(right-10,bottom-4);
    DC.SelectObject(m_DkGrayPen);
    DC.MoveTo(right-11,top+4);
    DC.LineTo(right-11,bottom-4);

    // The triangle
    if (lpd->itemState & ODS_DISABLED)
        DC.SelectObject(m_DkGrayPen);
    else
        DC.SelectObject(m_BlackPen);
    
    DC.MoveTo(right-4,(bottom/2)-1);
    DC.LineTo(right-9,(bottom/2)-1);

    DC.MoveTo(right-5,(bottom/2));
    DC.LineTo(right-8,(bottom/2));

    if (lpd->itemState & ODS_DISABLED)    
    {
        DC.SetPixel(right-4,(bottom/2)-1,RGB(255,255,255));
        DC.SetPixel(right-5,(bottom/2),RGB(255,255,255));
        DC.SetPixel(right-6,(bottom/2)+1,RGB(255,255,255));
    }
    else
    {
        DC.SetPixel(right-6,(bottom/2)+1,RGB(0,0,0));
    }

    if (!(lpd->itemState & ODS_DISABLED))
    {
        // The color rectangle, only if enabled
        DC.SelectObject(&colorbrush);
        DC.Rectangle(left+5,top+4,right-15,bottom-4);    
    }

    if (lpd->itemState & ODS_FOCUS)
    {
        // Draw the focus
        // It would have been nice just to
        // draw a rectangle using a pen created
        // with the PS_ALTERNATE style, but
        // this is not supported by WIN95
        int i;
        for (i=left+3;i<right-4;i+=2)
        {
            DC.SetPixel(i,top+3,RGB(0,0,0));
            DC.SetPixel(i,bottom-4,RGB(0,0,0));
        }

        for (i=top+3;i<bottom-4;i+=2)
        {
            DC.SetPixel(left+3,i,RGB(0,0,0));
            DC.SetPixel(right-4,i,RGB(0,0,0));
        }       
    }
    DC.SelectObject(m_OldPen);
    DC.SelectObject(m_OldBrush);

    DC.Detach();    
}


void CColorBtn::OnClicked() 
{
    // When the button is clicked, show the dialog.
	if (m_ColorDlg.DoModal() == IDOK)
    {
        m_CurrentColor = m_ColorDlg.m_SelectedColor;
        InvalidateRect(NULL);
    }	
}

void CColorBtn::Serialize( CArchive& ar )
{
}

void CColorBtn::SetSelectedColor(COLORREF Color)
{
   m_CurrentColor = Color;
   InvalidateRect(NULL);
}

COLORREF CColorBtn::GetColor()
{
   return m_CurrentColor;
}


void CColorBtn::ClearColorWells()
{
   if(m_ColorDlg.m_Colors.GetSize() > 0)
      m_ColorDlg.m_Colors.RemoveAll();
}

void CColorBtn::AddColorWell(COLORREF Color)
{
   m_ColorDlg.m_Colors.Add(Color);
}

void CColorBtn::SetColorsFromArray(CArray<COLORREF, COLORREF&>* ColorArray)
{
   short array_size = ColorArray->GetSize();
   COLORREF local_color;
   m_ColorDlg.m_Colors.SetSize(array_size);

   for(short loop = 0; loop < array_size; loop++)
      {
      local_color = ColorArray->GetAt(loop);
      m_ColorDlg.m_Colors.SetAt(loop, local_color);
      }
}

void CColorBtn::SetBorderThickness(short Outer, short Inner)
{
   m_ColorDlg.m_OuterBorderThickness = Outer;
   m_ColorDlg.m_InnerBorderThickness = Inner;
}

void CColorBtn::SetDialogWidth(short Width)
{
   m_ColorDlg.m_DialogWidth = Width;
}

void CColorBtn::SetNumColorWellColumns(short NumCols)
{
   m_ColorDlg.m_NumColorWellColumns = NumCols;
}

void CColorBtn::SetColorWellHeight(short Height)
{
   m_ColorDlg.m_ColorWellHeight = Height;
}

void CColorBtn::MakeColorWellsIsotropic(BOOL Yes)
{
   if(Yes)
      m_ColorDlg.m_IsotropicWells = TRUE;
   else
      m_ColorDlg.m_IsotropicWells = FALSE;
}

void CColorBtn::SetColorWellShape(short Shape)
{
   switch(Shape)
      {
      case RECTANGLE:
      case ELLIPSE:
         m_ColorWellShape = Shape;
         break;
      default:
         m_ColorWellShape = RECTANGLE;
         break;
      }
}
   
short CColorBtn::GetColorWellShape()
{
   return m_ColorWellShape;
}

/////////////////////////////////////////////////////////////////////////////
// CColorBtnDlg dialog


CColorBtnDlg::CColorBtnDlg(CWnd* pParent /*=NULL*/)
{
	//{{AFX_DATA_INIT(CColorBtnDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
   m_SelectedColor = RGB(255,255,255);
   m_DialogWidth = 41;
   m_NumColorWellColumns = 4;
   m_ColorWellHeight = 9;
   m_OuterBorderThickness = 1;
   m_InnerBorderThickness = 1;
   m_StartingButtonID = 5000;
   m_IsotropicWells = TRUE;

   CreateDialogFromTemplate();
   
}

CColorBtnDlg::~CColorBtnDlg()
{
   GlobalUnlock(m_GlobalLock);
	GlobalFree(m_GlobalLock);
   
}

void CColorBtnDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CColorBtnDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CColorBtnDlg, CDialog)
	//{{AFX_MSG_MAP(CColorBtnDlg)
	ON_WM_LBUTTONDOWN()	
	ON_WM_LBUTTONUP()
    ON_WM_DRAWITEM()	
	//}}AFX_MSG_MAP
   // ON_COMMAND_RANGE(IDC_COLOR_WELL1,IDC_COLOR_WELL16,OnColor)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CColorBtnDlg message handlers

BOOL CColorBtnDlg::OnInitDialog() 
{
   CDialog::OnInitDialog();

   CRect dialog_rect, color_well_rect, parent_button_rect;
   short dialog_height, color_well_width;
   short num_buttons, num_rows;
   int tempx, tempy;

   // If no colors have been added, close
   if(m_Colors.GetSize() == 0)
      EndDialog(IDCANCEL);
   
   // Set the dialog size and add the controls
   // The width cannot be less than the number of columns * MIN_WIDTH
   // plus the inside and outside borders
   
   // Validate Border sizes
   if(m_OuterBorderThickness < MIN_OUTER_BORDER)
      m_OuterBorderThickness = MIN_OUTER_BORDER;
   if(m_OuterBorderThickness > MAX_OUTER_BORDER)
      m_OuterBorderThickness = MAX_OUTER_BORDER;

   if(m_InnerBorderThickness < MIN_INNER_BORDER)
      m_InnerBorderThickness = MIN_INNER_BORDER;
   if(m_InnerBorderThickness > MAX_INNER_BORDER)
      m_InnerBorderThickness = MAX_INNER_BORDER;

   if(m_NumColorWellColumns < MIN_NUMCOLORWELLCOLS)
      m_NumColorWellColumns = MIN_NUMCOLORWELLCOLS;
   if(m_NumColorWellColumns > MAX_NUMCOLORWELLCOLS)
      m_NumColorWellColumns = MAX_NUMCOLORWELLCOLS;
   
   // allow for the dialog border
   tempx = GetSystemMetrics(SM_CXDLGFRAME);

   // Calculate color width to ensure min sizes are met
   color_well_width = (m_DialogWidth -
                       (2*tempx) -
                       (2*m_OuterBorderThickness) -
                       ((m_NumColorWellColumns-1) * m_InnerBorderThickness)) /
                       m_NumColorWellColumns;
   
   if(color_well_width < MIN_WELL_WIDTH)
      {
      color_well_width = MIN_WELL_WIDTH;
      }
   
   // Calculate width from whole number color well width to avoid calculation losses
   m_DialogWidth = ((2*m_OuterBorderThickness) +
                        (2*tempx) +
                        (m_NumColorWellColumns * color_well_width) +
                        ((m_NumColorWellColumns-1)* m_InnerBorderThickness));


   
   // calculate # rows, checking for partial rows
   num_buttons = m_Colors.GetSize();
   num_rows = num_buttons/m_NumColorWellColumns;
   if( (num_rows * m_NumColorWellColumns) < num_buttons)
      {
      num_rows++;
      }

   // allow for the dialog border
   tempy = GetSystemMetrics(SM_CYDLGFRAME);

   if(m_ColorWellHeight < MIN_WELL_HEIGHT)
      m_ColorWellHeight = MIN_WELL_HEIGHT;

   // ignore custom well height if isotropic wells are selected
   if(m_IsotropicWells)
      m_ColorWellHeight = color_well_width;

   dialog_height = (2*m_OuterBorderThickness) +
                     (2*tempy) +
                     (m_ColorWellHeight*num_rows) +
                     (m_InnerBorderThickness *(num_rows-1));
   
    
	 m_Parent->GetWindowRect(&parent_button_rect);
    
    // Move the dialog to be below the button
    // Note: we are sizing the rectangle
    SetWindowPos(NULL,
               parent_button_rect.left,
               parent_button_rect.bottom,
               m_DialogWidth,
               dialog_height,
               SWP_NOZORDER | SWP_DRAWFRAME);

    GetWindowRect(&dialog_rect);

    // Check to see if the dialog has a portion outside the
    // screen, if so, adjust.
    
    if (dialog_rect.bottom > GetSystemMetrics(SM_CYSCREEN))
    {   
        dialog_rect.top = parent_button_rect.top-(dialog_rect.bottom-dialog_rect.top);        
    }

    if (dialog_rect.right > GetSystemMetrics(SM_CXSCREEN))
    {
        dialog_rect.left = GetSystemMetrics(SM_CXSCREEN) - 
           (dialog_rect.right-dialog_rect.left);
    }

    SetWindowPos(NULL,dialog_rect.left,dialog_rect.top,0,0,SWP_NOSIZE|SWP_NOZORDER);

    // Add the button controls to the dialog
    CButton *temp_button;
    short column = 1, row = 1;
    short upperleft_x, upperleft_y;
    
    for(short loop = 0; loop < num_buttons; loop++)
       {
       if(column > m_NumColorWellColumns)
          {
          row++;
          column = 1;
          }
       upperleft_x = m_OuterBorderThickness +
                  (column-1)*(color_well_width + m_InnerBorderThickness);
       upperleft_y = m_OuterBorderThickness +
                  (row-1)*(m_ColorWellHeight + m_InnerBorderThickness);

       color_well_rect.SetRect(upperleft_x, 
                     upperleft_y, 
                     upperleft_x + color_well_width, 
                     upperleft_y + m_ColorWellHeight);

       temp_button = new CButton;
       temp_button->Create( "", BS_OWNERDRAW | BS_PUSHBUTTON| WS_TABSTOP | WS_CHILD | 
          WS_VISIBLE | WS_EX_CLIENTEDGE, 
          color_well_rect, this, m_StartingButtonID + loop );
       
       column++;
       }

   
    // Capture the mouse, this allows the dialog to close when
    // the user clicks outside.
    // Remember that the dialog has no "close" button.
    SetCapture();
	
	return TRUE; 
}



void CColorBtnDlg::EndDialog( int nResult )
{
    ReleaseCapture();

    CDialog::EndDialog(nResult);
   
   // delete child buttons
   CWnd *child = (CWnd*) GetTopWindow();
   while(child != NULL)
      {
      delete child;
      child = (CWnd*) GetTopWindow();
      }

}


void CColorBtnDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
    RECT r;

    POINT p;
    p.x = point.x;
    p.y = point.y;

    ClientToScreen(&p);

    GetWindowRect(&r);

    // The user clicked...

    if (!PtInRect(&r,p))
    {
        //  ...outside the dialog, close.

        EndDialog(IDCANCEL);
    }
    else
    {
        //  ...inside the dialog. Since this window
        //     has the mouse captured, its children
        //     get no messages. So, check to see
        //     if the click was in one of its children
        //     and tell him.

        //     If the user clicks inside the dialog
        //     but not on any of the controls,
        //     ChildWindowFromPoint returns a
        //     pointer to the dialog. In this
        //     case we do not resend the message
        //     (obviously) because it would cause
        //     a stack overflow.
        
        CWnd *child = ChildWindowFromPoint(point);
         
        if (child && child != this)
           {
           OnColor(child->GetDlgCtrlID()); 
           }
    }
	
	CDialog::OnLButtonDown(nFlags, point);
}


void CColorBtnDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpd) 
{
	CDC dc;
   CPen m_NullPen;
   CBrush brush;
   CPen *oldpen;
   CBrush *oldbrush;
   short shape;

   // Draw the wells using the current color table
   m_NullPen.CreateStockObject(NULL_PEN);
   brush.CreateSolidBrush(m_Colors.GetAt(nIDCtl-m_StartingButtonID));

   dc.Attach(lpd->hDC);

   oldpen = dc.SelectObject(&m_NullPen);
   oldbrush = dc.SelectObject(&brush);
   
   // Draw the correct shape
   shape = ((CColorBtn*)m_Parent)->GetColorWellShape();
   switch(shape)
      {
      case CColorBtn::RECTANGLE:
         lpd->rcItem.right++;
         lpd->rcItem.bottom++;
         dc.Rectangle(&lpd->rcItem);
         break;
      case CColorBtn::ELLIPSE:
         lpd->rcItem.right++;
         lpd->rcItem.bottom++;
         dc.Ellipse(&lpd->rcItem);
         break;
      default:
         ASSERT(FALSE);
         break;
      }

   dc.SelectObject(oldpen);
   dc.SelectObject(oldbrush);

   dc.Detach();
	
}


void CColorBtnDlg::OnColor(UINT id)
{
    m_SelectedColor = m_Colors.GetAt(id-m_StartingButtonID);

    EndDialog(IDOK);
}

void CColorBtnDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
    // See notes for OnLButtonDown.   
    CWnd *child = ChildWindowFromPoint(point,CWP_ALL);
    
    if (child && child != this)
       {
       OnColor(child->GetDlgCtrlID());	
       }
	
	CDialog::OnLButtonUp(nFlags, point);
}

void CColorBtnDlg::CreateDialogFromTemplate()
{
   // Dialog Template info
   // now initialize the DLGTEMPLATE structure
	m_dlgTempl.cx = 40;  // 4 horizontal units are the width of one character
	m_dlgTempl.cy = 80;  // 8 vertical units are the height of one character
	m_dlgTempl.style = DS_MODALFRAME | WS_POPUP;
	m_dlgTempl.dwExtendedStyle = 0;
	m_dlgTempl.x = 0;
	m_dlgTempl.y = 0;
	m_dlgTempl.cdit = 0;  // start with 0 dialog items in the dialog

	// The first step is to allocate memory to define the dialog.  The information to be 
	// stored in the allocated buffer is the following:
	// 
	// 1.  DLGTEMPLATE structure
	// 2.    0x0000 (Word) indicating the dialog has no menu
	// 3.    0x0000 (Word) Let windows assign default class to the dialog
	// 4.    (Caption)  Null terminated unicode string
	
	// will first convert the control captions to UNICODE
	int		total_length = 0;  

	try  
	{
		int buffer_size =  sizeof(DLGTEMPLATE) + (3 * sizeof(WORD))/*menu and class and no caption*/;

		buffer_size = (buffer_size + 3) & ~3;  // adjust size to make first control DWORD aligned

		m_GlobalLock = GlobalAlloc(LHND, buffer_size);
		if (m_GlobalLock == NULL)
			AfxThrowMemoryException();

		BYTE*	buffer_ptr = (BYTE*)GlobalLock(m_GlobalLock);
		if (buffer_ptr == NULL)
		{
			GlobalFree(m_GlobalLock);
			AfxThrowMemoryException();
		}

		BYTE*	destination_ptr = buffer_ptr;
		// transfer DLGTEMPLATE structure to the buffer
		memcpy(destination_ptr, &m_dlgTempl, sizeof(DLGTEMPLATE));
		destination_ptr += sizeof(DLGTEMPLATE);
		*(WORD*)destination_ptr = 0; // no menu
		*(WORD*)(destination_ptr + 1) = 0;  // use default window class
      *(WORD*)(destination_ptr + 2) = 0;  // no caption
		destination_ptr += 3 * sizeof(WORD);
		
		ASSERT(destination_ptr - buffer_ptr == buffer_size); // just make sure we did not overrun the heap

		InitModalIndirect((DLGTEMPLATE*)buffer_ptr);

		
	}
	catch(CException *e)
	{
	   AfxMessageBox("System Out of Memory.", MB_ICONEXCLAMATION | MB_OK);
      delete e;
      throw;
	}

}


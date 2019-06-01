// AviCapTestView.cpp : implementation of the CAviCapTestView class
//

#include "stdafx.h"
#include "time.h"

#include "AviCapTest.h"

#include "AviCapTestDoc.h"
#include "AviCapTestView.h"

#include "ProgDlg.h"
#include "Info.h"

#include "EnhCtl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CAPDRVINFO		this_driver_cdi;
CProgressDlg	externProgressDlg;
CAviCapTestView *thisView = NULL; 

VOID CALLBACK avicap_progress(LPSTR , DWORD);
#define	START_PROGRESS(txt)			externProgressDlg.Create(this);\
									externProgressDlg.SetRange(0,100);\
									externProgressDlg.SetPos(0);\
									externProgressDlg.SetStatus(txt);

VOID MyCapDraw(BOOL);
//addition for image processing (Forward definition)
LRESULT FAR PASCAL MyFrameCallbackProc(HWND hWnd, LPVIDEOHDR lpVHdr);
void	_process_8bit_image(LPVOID, CSize);
void	_process_16bit_image(LPVOID, CSize);
void	_process_24bit_image(LPVOID, CSize);
void	_process_32bit_image(LPVOID, CSize);

LRESULT FAR PASCAL MyFrameCallbackProc(HWND hWnd, LPVIDEOHDR lpVHdr)
{
	thisView->DoSomeImageProcessing(lpVHdr);
	 return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAviCapTestView

IMPLEMENT_DYNCREATE(CAviCapTestView, CView)

BEGIN_MESSAGE_MAP(CAviCapTestView, CView)
	//{{AFX_MSG_MAP(CAviCapTestView)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_COMMAND(ID_FILE_DISPLAY, OnFileDisplay)
	ON_COMMAND(ID_FILE_DRIVER, OnFileDriver)
	ON_COMMAND(ID_FILE_FORMAT, OnFileFormat)
	ON_COMMAND(ID_FILE_PREVIEW, OnFilePreview)
	ON_UPDATE_COMMAND_UI(ID_FILE_PREVIEW, OnUpdateFilePreview)
	ON_COMMAND(ID_FILE_SOURCE, OnFileSource)
	ON_UPDATE_COMMAND_UI(ID_FILE_SOURCE, OnUpdateFileSource)
	ON_UPDATE_COMMAND_UI(ID_FILE_FORMAT, OnUpdateFileFormat)
	ON_UPDATE_COMMAND_UI(ID_FILE_DRIVER, OnUpdateFileDriver)
	ON_UPDATE_COMMAND_UI(ID_FILE_DISPLAY, OnUpdateFileDisplay)
	ON_COMMAND(ID_VIEW_AUTOSIZE, OnViewAutosize)
	ON_UPDATE_COMMAND_UI(ID_VIEW_AUTOSIZE, OnUpdateViewAutosize)
	ON_COMMAND(ID_VIEW_DRAW, OnViewDraw)
	ON_UPDATE_COMMAND_UI(ID_VIEW_DRAW, OnUpdateViewDraw)
	ON_COMMAND(ID_FILEENHCTL, OnFileenhctl)
	ON_UPDATE_COMMAND_UI(ID_FILEENHCTL, OnUpdateFileenhctl)
	ON_COMMAND(ID_VIEW_MINUS, OnViewMinus)
	ON_COMMAND(ID_VIEW_PLUS, OnViewPlus)
	ON_UPDATE_COMMAND_UI(ID_VIEW_MINUS, OnUpdateViewMinus)
    ON_UPDATE_COMMAND_UI(ID_VIEW_PLUS, OnUpdateViewPlus) 
	ON_COMMAND(ID_VIEW_PROCESS, OnViewProcess)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PROCESS, OnUpdateViewProcess)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAviCapTestView construction/destruction

CAviCapTestView::CAviCapTestView()
{
	thisView = this;
	bEnableProcessing = FALSE;
}

CAviCapTestView::~CAviCapTestView()
{
}

BOOL CAviCapTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style|=WS_CLIPCHILDREN;
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CAviCapTestView drawing

void CAviCapTestView::OnDraw(CDC* pDC)
{
	CAviCapTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if(!CaptureWindow.IsReady())
	{//Capture not ready
		CRect rc;
		GetClientRect(rc);
			
			CFont wFont;
			wFont.CreateFont(24, 0, 0, 0, 0,
							0, 0, 0,
                 			0, 0, 0, 0,
                 		VARIABLE_PITCH | FF_SWISS, "MS Sans Serif");
			CFont *of=pDC->SelectObject(&wFont);
			
			CString s="Capture device not ready or not found";
			pDC->SetBkMode(TRANSPARENT);
			pDC->SetTextColor(GetSysColor(COLOR_BTNSHADOW));
			pDC->DrawText(s,&rc,
					DT_CENTER|DT_SINGLELINE|DT_VCENTER);
			pDC->SelectObject(of);
	}
	else
	{
			CString s;
			s.Format("%dx%d pixels, %d bits",
				CaptureWindow.GetFrameSize().cx, CaptureWindow.GetFrameSize().cy, CaptureWindow.GetCurrentBitsResolution());

			pDC->SetBkMode(TRANSPARENT);
			pDC->SetTextColor(128);
			pDC->TextOut(2,2,s);
	
	}
}

/////////////////////////////////////////////////////////////////////////////
// CAviCapTestView diagnostics

#ifdef _DEBUG
void CAviCapTestView::AssertValid() const
{
	CView::AssertValid();
}

void CAviCapTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAviCapTestDoc* CAviCapTestView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAviCapTestDoc)));
	return (CAviCapTestDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAviCapTestView message handlers
#define CONNECT_CAPTURE	77
int CAviCapTestView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	SetTimer(CONNECT_CAPTURE, 200, NULL);
	return 0;
}

void CAviCapTestView::OnTimer(UINT nIDEvent) 
{
	
	if(nIDEvent == CONNECT_CAPTURE)
	{
		KillTimer(nIDEvent);

		CRect rect;
		GetClientRect(&rect);

		START_PROGRESS("Create capture window...");
		CaptureWindow.SetProgressCallback(avicap_progress);
		 if(CaptureWindow.Create(WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS, rect, 
				this, TRUE))
		 {
			externProgressDlg.SetWindowText("Testing driver");
			if(CaptureWindow.ConnectWithDriver(ANY_DRIVER))
				{
					CaptureWindow.SetPreviewRate(100);
					
					CaptureWindow.GetDriverInfo(&this_driver_cdi);
					CaptureWindow.StartPreview(TRUE);

					//Added Statement 
					CaptureWindow.SetFrameCallBack(MyFrameCallbackProc);
					//
				}
		 }
		externProgressDlg.DestroyWindow();
	}
}

void CAviCapTestView::OnDestroy() 
{
	if(CaptureWindow.IsReady())
		CaptureWindow.Disconnect();
	
	CView::OnDestroy();
	
}


VOID CALLBACK avicap_progress(LPSTR txt, DWORD percent)
{
	if( externProgressDlg.GetSafeHwnd() &&
		::IsWindow(externProgressDlg.GetSafeHwnd()))
	{
		externProgressDlg.SetPos(percent);
		if(txt)
			externProgressDlg.SetStatus(txt);
	}
}

void CAviCapTestView::OnFileDisplay() 
{
	CaptureWindow.DisplayDlg();
	
}

void CAviCapTestView::OnFileDriver() 
{
	
	CaptureWindow.GetDriverInfo(&this_driver_cdi);

	Info	infoDlg(this);
	CString s;
	CStringArray Names, Vers;

  	int	td=	CaptureWindow.GetDriversList(&Names, &Vers);

	s.Format("\r\n\tTotal capture drivers installed:%d\r\n\r\n", td);
		infoDlg.m_InfoBuffer+=s;

	for(int i=0; i<td;i++)	{ s.Format(" %d. %s.%s\r\n",i+1,Names[i],Vers[i]);
		infoDlg.m_InfoBuffer+=s;
	}
	//infoDlg.m_InfoBuffer+=line;
	infoDlg.m_InfoBuffer+="\r\n";
	infoDlg.m_InfoBuffer+="\t\tCurrent Driver info\r\n";
	infoDlg.m_InfoBuffer+="\r\n";

	
	s.Format("Capture driver:\t%s\r\n", CaptureWindow.GetDriverName());
		infoDlg.m_InfoBuffer+=s;
	s.Format("Driver version:\t%s\r\n", CaptureWindow.GetDriverVer());
		infoDlg.m_InfoBuffer+=s;
	s.Format("Buffers  count:\t%d\r\n", this_driver_cdi.dwInternalBufCnt);
		infoDlg.m_InfoBuffer+=s;
	s.Format("Compression:\t%s\r\n", this_driver_cdi.dwCompressed?"Yes":"No");
		infoDlg.m_InfoBuffer+=s;
	s.Format("Video standard:\t%s\r\n", this_driver_cdi.fNTSC?"NTSC":"PAL/SECAM");
		infoDlg.m_InfoBuffer+=s;
	
	s.Format("Bits resolution:\t%d bits\r\n", CaptureWindow.GetCurrentBitsResolution());
		infoDlg.m_InfoBuffer+=s;
		
		infoDlg.m_InfoBuffer+="++Supported bits resolution:\r\n";

		  if(CaptureWindow.IsSupportedBitsResolution(1))
			infoDlg.m_InfoBuffer+="\t\t\t1 bit\r\n";
		  if(CaptureWindow.IsSupportedBitsResolution(4))
			infoDlg.m_InfoBuffer+="\t\t\t4 bits\r\n";
		  if(CaptureWindow.IsSupportedBitsResolution(8))
			infoDlg.m_InfoBuffer+="\t\t\t8 bits\r\n";
		  if(CaptureWindow.IsSupportedBitsResolution(16))
			infoDlg.m_InfoBuffer+="\t\t\t16 bits\r\n";
		  if(CaptureWindow.IsSupportedBitsResolution(24))
			infoDlg.m_InfoBuffer+="\t\t\t24 bits\r\n";
		  if(CaptureWindow.IsSupportedBitsResolution(32))
			infoDlg.m_InfoBuffer+="\t\t\t32 bits\r\n";

	s.Format("Frame size:\t%dx%d pixels\r\n", CaptureWindow.GetFrameSize().cx, CaptureWindow.GetFrameSize().cy);
		infoDlg.m_InfoBuffer+=s;
	
	infoDlg.m_InfoBuffer+="++Supported frame sizes:\r\n";
		for(i=0;;i++)
		{
			CSize sz;
			if(!CaptureWindow.EnumValidFrameSize(sz, i)) break;
			s.Format("\t\t\t%dx%d pixels\r\n", sz.cx, sz.cy);
			infoDlg.m_InfoBuffer+=s;
		}

		infoDlg.DoModal();
		
}

void CAviCapTestView::OnFileFormat() 
{
	CaptureWindow.FormatDlg();
	InvalidateRect(NULL);
}

void CAviCapTestView::OnFilePreview() 
{
	
	CaptureWindow.StartPreview(!CaptureWindow.GetPreviewFlag());
	
}


void CAviCapTestView::OnFileSource() 
{
	CaptureWindow.VSourceDlg();
	InvalidateRect(NULL);
	
}

void CAviCapTestView::OnUpdateFileSource(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(CaptureWindow.IsReady()&&this_driver_cdi.fSourceDlgSup);
	
}

void CAviCapTestView::OnUpdateFileFormat(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(CaptureWindow.IsReady()&&this_driver_cdi.fFormatDlgSup);
	
}

void CAviCapTestView::OnUpdateFileDriver(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(CaptureWindow.IsReady());
	
}

void CAviCapTestView::OnUpdateFileDisplay(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(CaptureWindow.IsReady()&&this_driver_cdi.fDisplayDlgSup);
}

void CAviCapTestView::OnUpdateFilePreview(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(CaptureWindow.IsReady());
	pCmdUI->SetCheck(CaptureWindow.GetPreviewFlag()!=FALSE);
	
}

void CAviCapTestView::OnViewAutosize() 
{
	CaptureWindow.AdjustPlacement(FALSE);//no stretch - actual size
	
}

void CAviCapTestView::OnUpdateViewAutosize(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(CaptureWindow.IsReady());
	
}

static BOOL draw = FALSE;
CAviCap *CapWindow=NULL;
void CAviCapTestView::OnViewDraw() 
{
	
	draw=!draw;	
	CapWindow = &CaptureWindow;
	if(draw)	
		CaptureWindow.SetDrawCallBack((DRAWCALLBACK)MyCapDraw);
	else
		CaptureWindow.SetDrawCallBack(NULL);
}

void CAviCapTestView::OnUpdateViewDraw(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(CaptureWindow.IsReady());
	pCmdUI->SetCheck(draw);

}

// 
// This is the sample of how to manage capture settings,
// bypassing standard driver dialog
//
void CAviCapTestView::OnFileenhctl() 
{
	EnhCtl dlg;
	CString s;
	CSize sz;
		for(int i=0;;i++)
		{
			
			if(!CaptureWindow.EnumValidFrameSize(sz, i)) break;
			s.Format("%dx%d pixels", sz);
			dlg.m_formats_str.Add(s);
			if(CaptureWindow.GetFrameSize() == sz)
				dlg.m_iFormat=i;
		}


		  if(CaptureWindow.IsSupportedBitsResolution(1))
			{	if(CaptureWindow.GetCurrentBitsResolution() == 1) 
				dlg.m_iResolution=dlg.m_Resolutions_str.GetSize(); 
				 dlg.m_bitsRes[dlg.m_Resolutions_str.GetSize()] =1; 
					dlg.m_Resolutions_str.Add("1 bit");}
		  
		  if(CaptureWindow.IsSupportedBitsResolution(4))
			  {if(CaptureWindow.GetCurrentBitsResolution() == 4) 
				dlg.m_iResolution=dlg.m_Resolutions_str.GetSize();  
				 dlg.m_bitsRes[dlg.m_Resolutions_str.GetSize()] =4;
					dlg.m_Resolutions_str.Add("4 bits");}
		  
		  if(CaptureWindow.IsSupportedBitsResolution(8))
			  { if(CaptureWindow.GetCurrentBitsResolution() == 8) 
				dlg.m_iResolution=dlg.m_Resolutions_str.GetSize(); 
				 dlg.m_bitsRes[dlg.m_Resolutions_str.GetSize()] =1; 
					dlg.m_Resolutions_str.Add("8 bits");}
		 
		  if(CaptureWindow.IsSupportedBitsResolution(16))
		  {if(CaptureWindow.GetCurrentBitsResolution() == 16) 
				dlg.m_iResolution=dlg.m_Resolutions_str.GetSize();
				 dlg.m_bitsRes[dlg.m_Resolutions_str.GetSize()] =16; 
					dlg.m_Resolutions_str.Add("16 bits");}
		  
		  if(CaptureWindow.IsSupportedBitsResolution(24))
		  {if(CaptureWindow.GetCurrentBitsResolution() == 24) 
				dlg.m_iResolution=dlg.m_Resolutions_str.GetSize(); 
				 dlg.m_bitsRes[dlg.m_Resolutions_str.GetSize()] =24;
					dlg.m_Resolutions_str.Add("24 bits");}
		  
		  if(CaptureWindow.IsSupportedBitsResolution(32))
			  {if(CaptureWindow.GetCurrentBitsResolution() == 32) 
				dlg.m_iResolution=dlg.m_Resolutions_str.GetSize();  
				 dlg.m_bitsRes[dlg.m_Resolutions_str.GetSize()] =32;
					dlg.m_Resolutions_str.Add("32 bits");}

		if(dlg.DoModal()==IDOK)
		{
			//not so elegant, but it's work!
			BOOL r = CaptureWindow.SetBitResolution(dlg.m_bitsRes[dlg.m_iResolution]);
			if(CaptureWindow.EnumValidFrameSize(sz,dlg.m_iFormat))
				r|=CaptureWindow.SetFrameSize(sz);
			
			if(r)
			InvalidateRect(NULL);
		}
}

void CAviCapTestView::OnUpdateFileenhctl(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(CaptureWindow.IsReady());	
}

// Simple overlay drawing
//
VOID MyCapDraw(BOOL fneedStretch)
{	
	if(CapWindow) {
	CRect rc;
	CapWindow->GetClientRect(&rc);

	CDC *dc = CapWindow->GetDC();
	
	
	dc->SetTextColor(RGB(255,255,255));
	dc->SetBkMode(TRANSPARENT);
	char str[32];
	_strtime(str);
	
	
	dc->TextOut((rc.right)/2,(rc.bottom)/2, str);

	if(fneedStretch)
	{
		;//implement an additional paint operation here
	}
	CapWindow->ReleaseDC(dc);
	}
}


void CAviCapTestView::OnViewMinus() 
{
	CRect rc;
	CaptureWindow.GetClientRect(&rc);
	if(rc.Width()>64)
	{
		rc.right = (70*rc.right)/100;
		rc.bottom = (70*rc.bottom)/100;
		CaptureWindow.SetWindowPos(NULL,0,0 ,rc.right,rc.bottom,
			SWP_NOZORDER|SWP_NOMOVE|SWP_NOREDRAW);
		CaptureWindow.AdjustPlacement(TRUE);// stretch
		InvalidateRect(NULL);
	}
	
}

void CAviCapTestView::OnViewPlus() 
{
	CRect rc,rc2;
	CaptureWindow.GetClientRect(&rc);
	GetClientRect(&rc2);
	if(rc.Width()<rc2.Width())
	{
		rc.right = (100*rc.right)/70;
		rc.bottom = (100*rc.bottom)/70;

		if(rc.right>rc2.right)
			rc.right = rc2.right;
		if(rc.bottom>rc2.bottom)
			rc.bottom = rc2.bottom;

		CaptureWindow.SetWindowPos(NULL,0,0 ,rc.right,rc.bottom,
			SWP_NOZORDER|SWP_NOMOVE|SWP_NOREDRAW);
		CaptureWindow.AdjustPlacement(TRUE);// stretch
	}
	
}

void CAviCapTestView::OnUpdateViewMinus(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(CaptureWindow.IsReady());
	
}

void CAviCapTestView::OnUpdateViewPlus(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(CaptureWindow.IsReady());
}

void CAviCapTestView::OnViewProcess() 
{
	bEnableProcessing=!bEnableProcessing;	
}

void CAviCapTestView::OnUpdateViewProcess(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(CaptureWindow.IsReady());
	pCmdUI->SetCheck(bEnableProcessing);
}

void	CAviCapTestView::DoSomeImageProcessing(LPVIDEOHDR lpVHdr)
{
	if(!bEnableProcessing)	return;

	// actual image processing work done here
     LPBYTE nextImage = (LPBYTE)lpVHdr->lpData;
    // NB: actually, VFW  sends WM_PAINT message after the
	// calling of this callback, so, we can see the results
	// without any additional programming:)
		switch(CaptureWindow.GetCurrentBitsResolution())
		{
		case 8:	
			//I've never seen this resolution!
			_process_8bit_image(lpVHdr->lpData, CaptureWindow.GetFrameSize()); 
				break;
		case 16:
			// Note: this will work correctly only for RGB format.
			// I don't know how to recognize YVU format!
			// Who knows?:))
			_process_16bit_image(lpVHdr->lpData, CaptureWindow.GetFrameSize()); 
				break;
		case 24:
			_process_24bit_image(lpVHdr->lpData, CaptureWindow.GetFrameSize()); 
				break;
		case 32:
			_process_32bit_image(lpVHdr->lpData, CaptureWindow.GetFrameSize()); 
				break;
		default:
			//unknown format
			break;
		}
	 /********************************/
 		
}


//
//	The simplest image processors
//	Pixel(x,y) = Pixel(x+1,y)-Pixel(x,y)
//
void	_process_8bit_image(LPVOID buf, CSize sz)
{
	LPBYTE ptr = (LPBYTE)buf;
	int icount = sz.cx*sz.cy;
	
	//skip last pixel
	icount--;

	while(icount--)
		*ptr = *(ptr+1) - (*ptr++);
}

void	_process_16bit_image(LPVOID buf, CSize sz)
{
	LPWORD ptr = (LPWORD)buf;
	int icount = sz.cx*sz.cy;
	//skip last pixel
	icount--;

	while(icount--)
	{
		
		char b1 = (*ptr)&0x1f;
		char g1 = ((*ptr)>>5)&0x1f;
		char r1 = ((*ptr)>>10)&0x1f;

		char b2 = (*ptr+1)&0x1f;
		char g2 = ((*ptr+1)>>5)&0x1f;
		char r2 = ((*ptr+1)>>10)&0x1f;

		*ptr++ =  ((b2-b1)&0x1f) | (((g2-g1)&0x1f)<<5) | (((r2-r1)&0x1f)<<10);
	}
}

void	_process_24bit_image(LPVOID buf, CSize sz)
{
	LPBYTE ptr = (LPBYTE)buf;
	int icount = sz.cx*sz.cy * 3;
	
	//skip last pixel
	icount-=3;

	while(icount)
	{
		*ptr = *(ptr+3) - (*ptr++);
		*ptr = *(ptr+3) - (*ptr++);
		*ptr = *(ptr+3) - (*ptr++);
		icount-=3;
	}

}

void	_process_32bit_image(LPVOID buf, CSize sz)
{
	LPBYTE ptr = (LPBYTE)buf;
	int icount = sz.cx*sz.cy*4;
	
	//skip last pixel
	icount-=4;

	while(icount)
	{
		//ptr++;//skip empty byte

		*ptr = *(ptr+4) - (*ptr++);
		*ptr = *(ptr+4) - (*ptr++);
		*ptr = *(ptr+4) - (*ptr++);

		icount-=4;
		ptr++;//skip empty byte
	}
}


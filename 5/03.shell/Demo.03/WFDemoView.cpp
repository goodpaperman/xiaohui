// WFDemoView.cpp : implementation of the CWFDemoView class
//

#include "stdafx.h"
#include "WFDemo.h"

#include "WFDemoDoc.h"
#include "WFDemoView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWFDemoView

IMPLEMENT_DYNCREATE(CWFDemoView, CFormView)

BEGIN_MESSAGE_MAP(CWFDemoView, CFormView)
	//{{AFX_MSG_MAP(CWFDemoView)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_START, OnStart)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_VIEW, OnView)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()


const double PI = 4*atan(1)  ;
/////////////////////////////////////////////////////////////////////////////
// CWFDemoView construction/destruction

CWFDemoView::CWFDemoView()
	: CFormView(CWFDemoView::IDD)
{
	//{{AFX_DATA_INIT(CWFDemoView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CWFDemoView::~CWFDemoView()
{
}

void CWFDemoView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWFDemoView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BOOL CWFDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CWFDemoView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	CRect Rect ;
	
	//Calculate regtangle for chart .
	
	GetClientRect(&Rect) ;
	Rect.right = Rect.left+(Rect.Width()/2)  ;
	Rect.bottom = Rect.top + (3*Rect.Height()/4);
	
	//Allocate space for series .
	if ( !m_Chart2d.AllocSerie(100) ) {
		AfxMessageBox("Error allocating chart serie") ;
        return ;
	}

	// Customize chart 
	m_Chart2d.SetChartTitle("2D Chart");
	m_Chart2d.SetChartLabel("X","Y");
	m_Chart2d.SetGridXYNumber(5,2);
	m_Chart2d.SetAxisStyle(1);
	m_Chart2d.SetRange(0,100,0,5);
	m_Chart2d.SetAxisStyle(0);
	m_Chart2d.mpSerie[0].m_plotColor = RGB(0,125,255);
	m_Chart2d.m_BGColor = RGB(255,255,0);
	m_Chart2d.SetGridXYNumber(10,10);
	//m_Chart2d.bLogScale = TRUE ;

	// Create chart .
	m_Chart2d.Create(WS_CHILD|WS_VISIBLE,Rect,this,IDC_CHART2D);

	// 3D Chart create
#define TRACE_COUNT 20
	m_Chart3d.nSerieCount = TRACE_COUNT ;
	
	//Allocate space for series .
	if ( !m_Chart3d.AllocSerie(100) ) {
		AfxMessageBox("Error allocating chart serie") ;
        return ;
	}

	// Format color for each series .
	UINT i ,r,g ;
	r = 255 ;
	g = 0 ;
	for (i= 0 ; i < TRACE_COUNT ; i++){
		g += 255/TRACE_COUNT ;
		m_Chart3d.mpSerie[i].m_plotColor = RGB(r,g,0);
	}
	
	m_Chart3d.SetChartTitle("Waterfall Chart");
	m_Chart3d.SetChartLabel("X","Y");
	m_Chart3d.SetGridXYNumber(5,2);
	m_Chart3d.SetAxisStyle(1);
	m_Chart3d.SetRange3d(0,100,0,5,0,TRACE_COUNT);
	m_Chart3d.SetAxisAngle(-30,30);
	m_Chart3d.Create(WS_CHILD|WS_VISIBLE,Rect,this,IDC_CHART3D);
	m_Chart3d.SetWindowPos(NULL,Rect.left,Rect.top + Rect.Height()+3,i,i
		,SWP_NOSIZE|SWP_NOZORDER);

	bTimerCreate = FALSE ;

}

/////////////////////////////////////////////////////////////////////////////
// CWFDemoView printing

BOOL CWFDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CWFDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CWFDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CWFDemoView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	
	//Pause timer to prevent updating graph while printing .
	if(bTimerCreate){
		OnStart() ;
		Sleep(100);
	}
	m_Chart2d.PrintChart(pDC,500,200);
	m_Chart3d.PrintChart(pDC,500,1800);
		
}

/////////////////////////////////////////////////////////////////////////////
// CWFDemoView diagnostics

#ifdef _DEBUG
void CWFDemoView::AssertValid() const
{
	CFormView::AssertValid();
}

void CWFDemoView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CWFDemoDoc* CWFDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWFDemoDoc)));
	return (CWFDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWFDemoView message handlers


void CWFDemoView::OnTimer(UINT nIDEvent) 
{
	static BOOL bIsDone = TRUE ;
	double value ;
	double radian ;
	static double freq = 4.0	 ;
	static double ampl ;
	static double angle = 0.05 ;
	static double phase = 0  ;


	if(bIsDone)
	{
		bIsDone = FALSE ;
		ampl = 3.5 * (sin(angle))  ;
		angle += (1.4/double(TRACE_COUNT)) * PI ;
		
	
		if (freq > 30 ) 
			freq = 5 ;

		if(angle > (2 * PI))
			angle = 0.00005 ;
		
		radian = (freq * PI / 100) ;
		//phase += (4 / (2*PI)) ;

		if (phase >= (20*PI))
			phase = 0 ;

		//freq = 2.0 ;
		for ( int i = 0 ; i < 100 ; i++)
		{
			value = ampl * sin ( radian * ((double)i + phase)  ) ;
			m_Chart2d.SetXYValue((double)i,fabs(value),i,0);
			m_Chart3d.SetXYValue((double)i,fabs(value),i,0);
		}
		m_Chart3d.ShiftSerie();
		m_Chart2d.Invalidate();
		m_Chart3d.Invalidate();
		bIsDone = TRUE ;
	}	
	CFormView::OnTimer(nIDEvent);
}

void CWFDemoView::OnStart() 
{

	
	if ( !bTimerCreate ){
		SetTimer(1,500,NULL);
		bTimerCreate = TRUE ;
	} else {
		KillTimer(1) ;
		bTimerCreate = FALSE ;
	}
	
}



void CWFDemoView::OnDestroy() 
{
	CFormView::OnDestroy();
	
	// TODO: Add your message handler code here
	if(bTimerCreate) 
		KillTimer(1) ;
}

void CWFDemoView::OnView() 
{
	static BOOL bIsometric = TRUE  ;
	
	if(bIsometric) {
		// Set view to dimetric
		m_Chart3d.SetAxisAngle(-7,42);
		bIsometric = FALSE ;
	} else {
		m_Chart3d.SetAxisAngle(-30,30);
		bIsometric =TRUE ;
	}

	if(!bTimerCreate)
		m_Chart3d.Invalidate() ;

}

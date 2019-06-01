// ReStartView.cpp : implementation of the CReStartView class
//

#include "stdafx.h"
#include "ReStart.h"
#include "MainFrm.h"

#include "ReStartDoc.h"
#include "ReStartView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CReStartApp theApp;
#define PR_NONE		0
#define PR_RECORD		1
#define PR_PLAY		2
#define PR_RECPLAY	3
#define PR_PAUSE		4
/////////////////////////////////////////////////////////////////////////////
// CReStartView

IMPLEMENT_DYNCREATE(CReStartView, CFormView)

BEGIN_MESSAGE_MAP(CReStartView, CFormView)
	//{{AFX_MSG_MAP(CReStartView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_PLAY, OnPlay)
	ON_BN_CLICKED(IDC_PAUSE, OnPause)
	ON_BN_CLICKED(IDC_REWIND, OnRewind)
	ON_BN_CLICKED(IDC_FORWIND, OnForwind)
	ON_BN_CLICKED(IDC_STOP, OnStop)
	ON_BN_CLICKED(IDC_RECORD, OnRecord)
	ON_CBN_SELCHANGE(IDC_COMBO_MONO, OnSelchangeComboMono)
	ON_CBN_SELCHANGE(IDC_COMBO_KHZ, OnSelchangeComboKhz)
	ON_CBN_SELCHANGE(IDC_COMBO_BITS, OnSelchangeComboBits)
	ON_CBN_SELCHANGE(IDC_COMBO_RECORDING_TIME, OnSelchangeComboRecordingTime)
	ON_COMMAND(ID_VIEW_INFO_BAR, OnViewInfoBar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_INFO_BAR, OnUpdateViewInfoBar)
	ON_WM_DESTROY()
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
	ON_MESSAGE(WM_DESTROYINFOBAR, OnDestroyInfoBar)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReStartView construction/destruction

CReStartView::CReStartView()
	: CFormView(CReStartView::IDD)
{
	//{{AFX_DATA_INIT(CReStartView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	mMono = 1;
	mSampling = 8000;
	mBits = 16;

	m_nStatus=PR_NONE;
	m_wave = new CLowLevelAudioService;

	mTime = 5; 
	m_info = NULL;

	m_nFileTime=0;
	m_nFilePos=0;

	m_FileOpened = FALSE;
}

CReStartView::~CReStartView()
{
	if(m_wave)
		delete m_wave;
}

void CReStartView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReStartView)
	DDX_Control(pDX, IDC_COMBO_RECORDING_TIME, m_record_time);
	DDX_Control(pDX, IDC_COMBO_BITS, m_combo_bits);
	DDX_Control(pDX, IDC_COMBO_KHZ, m_combo_khz);
	DDX_Control(pDX, IDC_COMBO_MONO, m_combo_mono);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_PLAY,		mPlay);
	DDX_Control(pDX, IDC_PAUSE,	mPause);
	DDX_Control(pDX, IDC_REWIND,	mRewind);
	DDX_Control(pDX, IDC_FORWIND,	mForwind);
	DDX_Control(pDX, IDC_STOP,		mStop);
	DDX_Control(pDX, IDC_RECORD,	mRecord);

}

BOOL CReStartView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CFormView::PreCreateWindow(cs);
}

void CReStartView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	ResizeParentToFit();

	m_combo_mono.SetCurSel(0);
	m_combo_bits.SetCurSel(1);
	m_combo_khz.SetCurSel(0);
	m_record_time.SetCurSel(4);
    
	CRgn rgn;
	rgn.CreateEllipticRgn(5,5, 75, 45);
	mPlay.wSetBitmap(::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_PLAYU)), 
						  ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_PLAYD)),
						  FALSE, &rgn);
	mPlay.SetToolTip("Play");
	mPause.wSetBitmap(::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_PAUSEU)), 
						  ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_PAUSED)),
						  FALSE, &rgn);
	mPause.SetToolTip("Pause");
	mRewind.wSetBitmap(::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_REWINDU)), 
						  ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_REWINDD)),
						  FALSE, &rgn);
	mRewind.SetToolTip("Rewind");
	mForwind.wSetBitmap(::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_FORWINDU)), 
						  ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_FORWINDD)),
						  FALSE, &rgn);
	mForwind.SetToolTip("Forwind");
	mStop.wSetBitmap(::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_STOPU)), 
						  ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_STOPD)),
						  FALSE, &rgn);
	mStop.SetToolTip("Stop");
	mRecord.wSetBitmap(::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_RECORDU)), 
							::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_RECORDD)),
							FALSE, &rgn);
	mRecord.SetToolTip("Record");
	SetButtonState(0,0,0,0,0,1);
}

/////////////////////////////////////////////////////////////////////////////
// CReStartView printing

BOOL CReStartView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CReStartView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void CReStartView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void CReStartView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
}

/////////////////////////////////////////////////////////////////////////////
// CReStartView diagnostics

#ifdef _DEBUG
void CReStartView::AssertValid() const
{
	CFormView::AssertValid();
}

void CReStartView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CReStartDoc* CReStartView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CReStartDoc)));
	return (CReStartDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CReStartView message handlers

int CReStartView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	//hWnd = this->m_hWnd;

	return 0;
}

void CReStartView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
}

void CReStartView::SetButtonState(int play, int pause, int rewind, int forwind, int stop, int record)
{
	if(play == 1)
		mPlay.SetEnable(TRUE);
	else if(play == 0)
		mPlay.SetEnable(FALSE);

	if(pause == 1)
		mPause.SetEnable(TRUE);
	else if(pause == 0)
		mPause.SetEnable(FALSE);

	if(rewind == 1)
		mRewind.SetEnable(TRUE);
	else if(rewind == 0)
		mRewind.SetEnable(FALSE);

	if(forwind == 1)
		mForwind.SetEnable(TRUE);
	else if(forwind == 0)
		mForwind.SetEnable(FALSE);

	if(stop == 1)
		mStop.SetEnable(TRUE);
	else if(stop == 0)
		mStop.SetEnable(FALSE);

	if(record == 1)
		mRecord.SetEnable(TRUE);
	else if(record == 0)
		mRecord.SetEnable(FALSE);
}

void CReStartView::OnPlay() 
{
	if(!mPlay.GetEnable())
		return;

	SetButtonState(0,1,0,0,1,0);
	m_wave->SetWavePos(m_nFilePos);
	DrawInputWave(m_nFilePos);
	CDialogBar* pDlg = ((CMainFrame*)AfxGetMainWnd())->GetDlgIWave();
	pDlg->InvalidateRect(CRect(0, 0, 350, 60), TRUE);

	m_wave->PlayWave();
	m_nStatus = PR_PLAY;
	SetTimer(1, 500, NULL);
}

void CReStartView::OnPause() 
{
	if(!mPause.GetEnable())
		return;

	KillTimer(1);
	m_wave->PlayPause();
	m_nStatus = PR_PAUSE;
	SetButtonState(1,0,1,1,1,1);
}

void CReStartView::OnRewind() 
{
	if(!mRewind.GetEnable())
		return;

	if(m_nFilePos >= 1)
		m_nFilePos--;
	else
		m_nFilePos = 0;
}

void CReStartView::OnForwind() 
{
	if(!mForwind.GetEnable())
		return;
	
	if(m_nFilePos <= m_wave->m_nSec*2 -1)
		m_nFilePos++;
	else
		m_nFilePos = m_wave->m_nSec*2;
}

void CReStartView::OnStop() 
{
	if(!mStop.GetEnable())
		return;

	if(m_nStatus == PR_RECORD)
	{
		m_wave->StopRecord();
		KillTimer(2);
		m_nFileTime = m_nFilePos;
		m_nFilePos=0;
		m_wave->m_nSec = m_nFileTime/2;
	}
	else
	{
		if(m_nStatus != PR_PAUSE)
			m_wave->PlayPause();
		KillTimer(1);
		m_nFilePos = 0;
	}

	m_nStatus = PR_NONE;
	SetButtonState(1,0,1,1,1,1);
}

void CReStartView::OnRecord() 
{
	if(MessageBox("엔터키를 누르면 녹음을 시작합니다.", "녹음", MB_OKCANCEL | MB_ICONQUESTION) != IDOK)
		return;

	SetButtonState(0,0,0,0,1,0);
	m_wave->SetWaveInfo( mMono, mSampling, mBits);
	m_wave->SetDataSize(mTime);
	m_wave->wAllocMemory();
	m_wave->wSetWaveHeader();
	m_nFilePos=0;
	m_nFileTime = mTime;
	m_nStatus=PR_RECORD;
	m_wave->RecordWave();
	CDialogBar* pDlg = ((CMainFrame*)AfxGetMainWnd())->GetDlgOWave();
	pDlg->InvalidateRect(CRect(0, 0, 350, 60), TRUE);
	DrawOutputWave(m_nFilePos);
	SetTimer(2, 500, NULL);
	m_FileOpened = FALSE;

	CString str;
	SetDlgItemText(IDC_STATIC_SOURCE, "Record Voice");
	SetDlgItemText(IDC_STATIC_FILENAME, "Voice");
	SetDlgItemText(IDC_STATIC_FORMAT,SetFileInfo());

	str.Format("%d Byte", m_wave->lDatasize);
	SetDlgItemText(IDC_STATIC_SIZE, str);

	str.Format("%d Sec", m_wave->m_nSec);
	SetDlgItemText(IDC_STATIC_TIME, str);
}

void CReStartView::OnSelchangeComboMono() 
{
	switch(m_combo_mono.GetCurSel()){
	case 0:
		mMono = 1;
		break;
	case 1:
		mMono = 2;
		break;
	}
	OnSelchangeComboBits();
}

void CReStartView::OnSelchangeComboKhz() 
{
	switch(m_combo_khz.GetCurSel()){
	case 0:
		mSampling = 8000;
		break;
	case 1:
		mSampling = 11025;
		break;
	case 2:
		mSampling = 22050;
		break;
	case 3:
		mSampling = 44100;
		break;
	}
}

void CReStartView::OnSelchangeComboBits() 
{
	switch(m_combo_bits.GetCurSel()){
	case 0:
		mBits = 8;
		break;
	case 1:
		mBits = 16;
		break;
	case 2:
		mBits = 32;
		break;
	}
}

void CReStartView::OnSelchangeComboRecordingTime() 
{
	mTime = m_record_time.GetCurSel()+1;
}


void CReStartView::OnViewInfoBar() 
{
	CRect rect;
	AfxGetMainWnd()->GetWindowRect(rect);


	if(m_info == NULL)
	{
		m_info = new CInfoBar(this);
		m_info->Create();
		m_info->ShowWindow(TRUE);
		m_info->MoveWindow(rect.right+2, rect.top, 100, 600, TRUE);
	}
	else
	{
		m_info->DestroyWindow();
		delete m_info;
		m_info = NULL;
	}
}

void CReStartView::OnUpdateViewInfoBar(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_info != NULL);
}

void CReStartView::OnDestroyInfoBar()
{
	OnViewInfoBar();
}

void CReStartView::OnDestroy() 
{
	CFormView::OnDestroy();
	
	if(m_info)
	{
		m_info->DestroyWindow();
		delete m_info;
	}
}

CString CReStartView::SetFileInfo()
{
	CString str, tmp;

	if(m_wave->WaveRecord.wf.nChannels == 1)
		str = _T("Mono"), mMono = 1;
	else if(m_wave->WaveRecord.wf.nChannels == 2)
		str = _T("Stereo"), mMono = 2;

	tmp.Format(" %5dkHz", m_wave->WaveRecord.wf.nSamplesPerSec);
	str += tmp, mSampling = m_wave->WaveRecord.wf.nSamplesPerSec;

	tmp.Format(" %d Bits", m_wave->WaveRecord.wf.nBlockAlign*8);
	str += tmp, mBits =  m_wave->WaveRecord.wf.nBlockAlign*8;

	mTime = m_wave->m_nSec;
	m_nFileTime = mTime*2;

	return str;
}

void CReStartView::OnFileOpen() 
{
	CString str;
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "Wave Files (*.wav)|*.wav|All Files (*.*)|*.*||");
	if(dlg.DoModal() != IDOK)
		return;

	strcpy(m_strFileName, dlg.GetPathName());
	m_wave->LoadWaveFile(m_strFileName);
	m_OpenFile = dlg.GetFileName();
	SetDlgItemText(IDC_STATIC_SOURCE, "Open File");
	SetDlgItemText(IDC_STATIC_FILENAME, m_strFileName);
	SetDlgItemText(IDC_STATIC_FORMAT,SetFileInfo());

	str.Format("%d Byte", m_wave->lDatasize);
	SetDlgItemText(IDC_STATIC_SIZE, str);

	str.Format("%d Sec", m_wave->m_nSec);
	SetDlgItemText(IDC_STATIC_TIME, str);

	m_nFilePos=0;
	m_FileOpened = TRUE;
	SetButtonState(1,0,1,1,0,1);
	SetComboState();
}

void CReStartView::SetComboState()
{
	m_combo_mono.SetCurSel(m_wave->WaveRecord.wf.nChannels-1);

	switch((int)m_wave->WaveRecord.wf.nSamplesPerSec){
	case 8000:
		m_combo_khz.SetCurSel(0);
		break;
	case 11025:
		m_combo_khz.SetCurSel(1);
		break;
	case 22050:
		m_combo_khz.SetCurSel(2);
		break;
	case 44100:
		m_combo_khz.SetCurSel(3);
		break;
	}

	switch((int)m_wave->WaveRecord.wf.nBlockAlign){
	case 1:
		m_combo_bits.SetCurSel(0);
		break;
	case 2:
		m_combo_bits.SetCurSel(1);
		break;
	case 4:
		m_combo_bits.SetCurSel(2);
		break;
	}

	m_record_time.SetCurSel(m_wave->m_nSec-1);
}


void CReStartView::OnTimer(UINT nIDEvent) 
{
	switch(nIDEvent){
	case 1:
		{
			m_nFilePos++;
			DrawInputWave(m_nFilePos);
			if((m_wave->GetdwFlags() & WHDR_DONE) || m_nFilePos==m_nFileTime)
			{
				m_wave->PlayPause();
				KillTimer(1);
				m_nFilePos=0;
				m_nStatus = PR_NONE;
				SetButtonState(1,0,1,1,0,1);
			}
			break;
		}
	case 2:
		{
			m_nFilePos++;
			DrawOutputWave(m_nFilePos);
			if(m_nFilePos==m_nFileTime)
			{
				KillTimer(2);
				m_nFilePos=0;
				m_wave->StopRecord();
				m_nStatus = PR_NONE;
				SetButtonState(1,0,1,1,0,1);
			}
			break;
		}
	}
	CFormView::OnTimer(nIDEvent);
}

void CReStartView::DrawInputWave(int time)
{
	CDialogBar* pDlg = ((CMainFrame*)AfxGetMainWnd())->GetDlgIWave();
	CDC* pDC = pDlg->GetDC();
	m_wave->DrawWave(pDC,CRect(5, 5, 310/*340*/, 43),RGB(128,0,0),10,time);
    pDlg->ReleaseDC(pDC); 
}

void CReStartView::DrawOutputWave(int time)
{
	CDialogBar* pDlg = ((CMainFrame*)AfxGetMainWnd())->GetDlgOWave();
	CDC* pDC = pDlg->GetDC();
	m_wave->DrawWave(pDC,CRect(5, 5, 310/*340*/, 43),RGB(0,128,0),10,time);
    pDlg->ReleaseDC(pDC); 
}

void CReStartView::DrawWave(LPBYTE data)
{
	CRect rcClient = CRect(5,5, 700, 43);

	CClientDC dc(this);
	
	CBitmap Bitmap;
	CBitmap* pbmOld = NULL;

	CDC dcMem;
	dcMem.CreateCompatibleDC(&dc);

	Bitmap.CreateCompatibleBitmap(&dc,rcClient.Width(),rcClient.Height());
	
	pbmOld = dcMem.SelectObject(&Bitmap);

	dcMem.PatBlt(0, 0 ,rcClient.Width(), rcClient.Height(), WHITENESS);

	int x,y;
	dcMem.MoveTo(-1,rcClient.bottom/2);
  
	// display incomming signal
	for  (x =0 ; x < 320/2; x+=2)  // display Input
	{
		int gab;
		if(m_wave->WaveRecord.wBitsPerSample==8)
			gab=m_wave->Bit8Value(x);
		else if(m_wave->WaveRecord.wBitsPerSample==16)
			gab=m_wave->Bit16Value(x);
		else
			gab=m_wave->Bit32Value(x);

		y 	= rcClient.bottom/2+gab;
		dcMem.LineTo(x,y);
   }
	dc.BitBlt(rcClient.left, rcClient.top ,rcClient.Width(), rcClient.Height(),
				&dcMem, 0, 0, SRCCOPY);

	dcMem.SelectObject(pbmOld);
	dcMem.DeleteDC();
}
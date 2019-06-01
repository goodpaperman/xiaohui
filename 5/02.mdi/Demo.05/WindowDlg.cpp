// WindowDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mainfrm.h"
#include "WindowDlg.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWindowDlg dialog


CWindowDlg::CWindowDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWindowDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWindowDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CWindowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWindowDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWindowDlg, CDialog)
	//{{AFX_MSG_MAP(CWindowDlg)
	ON_BN_CLICKED(IDC_CLOSE, OnCloseBtn)
	ON_BN_CLICKED(IDC_SAVE, OnSaveBtn)
	ON_BN_CLICKED(IDC_ACTIVATE, OnActivateBtn)
	ON_LBN_SELCHANGE(IDC_WINDOWLIST, OnSelchangeWindowlist)
	ON_LBN_DBLCLK(IDC_WINDOWLIST, OnDblclkWindowlist)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWindowDlg message handlers

BOOL CWindowDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	Refresh();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CWindowDlg::Refresh()
{
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CListBox* lb = (CListBox*)GetDlgItem( IDC_WINDOWLIST );
	lb->ResetContent();

	CString str;
	int nCount = 0;
	int nIndex;

	CWnd * pWnd = pFrame->GetWindow (GW_CHILD);
	ASSERT (pWnd);
	pWnd = pWnd->GetWindow (GW_CHILD);
	while (pWnd)
	{
		nCount++;
		pWnd->GetWindowText( str );
		nIndex = lb->AddString( str );
		lb->SetItemDataPtr( nIndex, (void *)pWnd );

		if ( pWnd == (CWnd*)pFrame->GetActiveFrame() )
			lb->SetSel( nIndex );

		pWnd = pWnd->GetWindow (GW_HWNDNEXT);
	}

	OnSelchangeWindowlist();
}

void CWindowDlg::OnCloseBtn() 
{
	CListBox* lb = (CListBox*)GetDlgItem( IDC_WINDOWLIST );
	int nSelected = lb->GetSelCount();

	if ( nSelected <= 0 )
		return;

	int* nSelItems = new int[ nSelected ];
	lb->GetSelItems( nSelected, nSelItems );

	CWnd* Window;

	for ( int i = 0; i < nSelected; i++ )
	{
		Window = (CWnd*)lb->GetItemDataPtr( nSelItems[ i ] );
		//Window->DestroyWindow();
        //Window->CloseWindow(); 
        Window->SendMessage(WM_CLOSE); 
	}

	delete [] nSelItems;

	Refresh();

	if ( lb->GetCount() == 0 )
		OnOK();
}

void CWindowDlg::OnSaveBtn() 
{
	CListBox* lb = (CListBox*)GetDlgItem( IDC_WINDOWLIST );
	int nSelected = lb->GetSelCount();

	if ( nSelected <= 0 )
		return;

	int* nSelItems = new int[ nSelected ];
	lb->GetSelItems( nSelected, nSelItems );

	CWnd* Window;

	for ( int i = 0; i < nSelected; i++ )
	{
		Window = (CWnd*)lb->GetItemDataPtr( nSelItems[ i ] );
		Window->SendMessage( WM_COMMAND, ID_FILE_SAVE );
	}

	delete [] nSelItems;

	Refresh();
}

void CWindowDlg::OnActivateBtn() 
{
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CListBox* lb = (CListBox*)GetDlgItem( IDC_WINDOWLIST );
	int nSelected = lb->GetSelCount();

	if ( nSelected != 1 )
		return;

	int nSelItems[ 1 ];
	lb->GetSelItems( 1, nSelItems );

	CWnd* Window = (CWnd*)lb->GetItemDataPtr( nSelItems[ 0 ] );
	pFrame->MDIActivate( Window );
}

void CWindowDlg::OnSelchangeWindowlist() 
{
	CListBox* lb = (CListBox*)GetDlgItem( IDC_WINDOWLIST );

	int nSelected = lb->GetSelCount();

	if ( nSelected <= 0 )
	{
		GetDlgItem( IDC_CLOSE )->EnableWindow( FALSE );
		GetDlgItem( IDC_SAVE )->EnableWindow( FALSE );
	}
	else
	{
		GetDlgItem( IDC_CLOSE )->EnableWindow( TRUE );
		GetDlgItem( IDC_SAVE )->EnableWindow( TRUE );
	}

	if ( nSelected == 1 )
		GetDlgItem( IDC_ACTIVATE )->EnableWindow( TRUE );
	else
		GetDlgItem( IDC_ACTIVATE )->EnableWindow( FALSE );
}

void CWindowDlg::OnDblclkWindowlist() 
{
	CWindowDlg::OnOK();
}

void CWindowDlg::OnOK() 
{
	OnActivateBtn();

	CDialog::OnOK();
}

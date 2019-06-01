// BackPropDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestApp.h"
#include "BackPropDlg.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBackPropDlg dialog


CBackPropDlg::CBackPropDlg(CWnd* pParent)
	: CDialog(CBackPropDlg::IDD, pParent)
{
   ASSERT( pParent );
   m_pFrame = (CMainFrame*)pParent;   
	//{{AFX_DATA_INIT(CBackPropDlg)
	m_strFileName = m_pFrame->GetMDIClient().GetFileName();
	m_nMode = m_pFrame->GetMDIClient().GetDisplayMode();
	m_nX = m_pFrame->GetMDIClient().GetOrigin().x;
	m_nY = m_pFrame->GetMDIClient().GetOrigin().y;
	m_bAutoSave = m_pFrame->GetMDIClient().GetAutoSaveRestore();
	//}}AFX_DATA_INIT
}


void CBackPropDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBackPropDlg)		
    DDX_Control(pDX, IDC_SPIN2, m_ctlSpin2);
	DDX_Control(pDX, IDC_SPIN1, m_ctlSpin1);
	DDX_Text(pDX, IDC_FILENAME, m_strFileName);	
	DDX_Radio(pDX, IDC_TILED, m_nMode);
    DDX_Text(pDX, IDC_EDITX, m_nX);
	DDV_MinMaxUInt(pDX, m_nX, 0, 1000);
	DDX_Text(pDX, IDC_EDITY, m_nY);
	DDV_MinMaxUInt(pDX, m_nY, 0, 1000);
	DDX_Check(pDX, IDC_AUTOSAVE, m_bAutoSave);
	//}}AFX_DATA_MAP

   if ( pDX->m_bSaveAndValidate )
      m_pFrame->GetMDIClient().SetAutoSaveRestore( m_bAutoSave );
}

BEGIN_MESSAGE_MAP(CBackPropDlg, CDialog)
	//{{AFX_MSG_MAP(CBackPropDlg)
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	ON_BN_CLICKED(IDC_BKCOLOR, OnBkcolor)
	ON_BN_CLICKED(IDC_RESET, OnReset)	
    ON_BN_CLICKED(IDC_CENTERED, OnDisplay)	
	ON_BN_CLICKED(IDC_TILED, OnDisplay)	
	ON_BN_CLICKED(IDC_STRETCH, OnDisplay)
	ON_BN_CLICKED(IDC_CUSTOM, OnDisplay)
    ON_EN_CHANGE(IDC_EDITX, OnChangeEditx)
	ON_EN_CHANGE(IDC_EDITY, OnChangeEditx)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBackPropDlg message handlers

void CBackPropDlg::OnBrowse() 
{
	CFileDialog dlg( TRUE, _T( "bmp" ), m_strFileName, 
                    OFN_HIDEREADONLY, 
                    _T( "Bitmap Files (*.bmp)|*.bmp|All Files (*.*)|*.*||" ) );
   dlg.DoModal();
   m_pFrame->GetMDIClient().SetBitmap( dlg.GetPathName() );
   m_strFileName = dlg.GetPathName();
   UpdateData( FALSE );
}

void CBackPropDlg::OnBkcolor() 
{
    CColorDialog dlg( m_pFrame->GetMDIClient().GetBkColor() );
    dlg.m_cc.Flags |= CC_SHOWHELP;
    dlg.DoModal();   
    m_pFrame->GetMDIClient().SetBkColor( dlg.m_cc.rgbResult );
}

void CBackPropDlg::OnReset() 
{   
    m_pFrame->GetMDIClient().Reset();

	m_nMode = m_pFrame->GetMDIClient().GetDisplayMode();
	m_strFileName = m_pFrame->GetMDIClient().GetFileName();
    m_nX = m_pFrame->GetMDIClient().GetOrigin().x;
	m_nY = m_pFrame->GetMDIClient().GetOrigin().y;
    UpdateData( FALSE ); // Reload the data
}

BOOL CBackPropDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
   m_ctlSpin1.SetRange( 0, 1000 );
   m_ctlSpin2.SetRange( 0, 1000 );

   GetDlgItem( IDC_EDITX )->EnableWindow( m_nMode == 3 ? TRUE : FALSE );
   GetDlgItem( IDC_EDITY )->EnableWindow( m_nMode == 3 ? TRUE : FALSE );

   ASSERT( m_pFrame );
	return TRUE;
}

void CBackPropDlg::OnDisplay()
{
	UpdateData();
   m_pFrame->GetMDIClient().SetDisplayMode( CMDIClient::DisplayModesEnum( m_nMode ) );

   GetDlgItem( IDC_EDITX )->EnableWindow( m_nMode == 3 ? TRUE : FALSE );
   GetDlgItem( IDC_EDITY )->EnableWindow( m_nMode == 3 ? TRUE : FALSE );
}

void CBackPropDlg::OnChangeEditx() 
{
   if ( IsWindow( m_ctlSpin1 ) )
   {
      UpdateData();
      m_pFrame->GetMDIClient().SetOrigin( m_nX, m_nY );
   }
}

// TestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "gridlist.h"
#include "TestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// TestDlg dialog


TestDlg::TestDlg(CWnd* pParent /*=NULL*/)
: CDialog(TestDlg::IDD, pParent)
{
    //{{AFX_DATA_INIT(TestDlg)
    //}}AFX_DATA_INIT
    m_pImageList = 0;
}

TestDlg::~TestDlg()
{
    delete m_pImageList;
}


void TestDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(TestDlg)
    DDX_Control(pDX, IDC_LIST, m_GridListCtrl);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(TestDlg, CDialog)
//{{AFX_MSG_MAP(TestDlg)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// TestDlg message handlers

BOOL TestDlg::OnInitDialog() 
{
    CDialog::OnInitDialog();
    
    m_GridListCtrl.PrepareControl(0);
    TCHAR rgtsz[4][10] = {_T("Column 1"), _T("Column 2"), _T("Column 3"), _T("Column 4")};
    
    LV_ITEM			lvitem;
    LV_COLUMN		lvcolumn;
    CRect rect;
    m_GridListCtrl.GetWindowRect( &rect );
    
    // Insert Image Lists
    m_pImageList = new CImageList();
    m_pImageList->Create( IDB_BITMAP1, 16, 1, RGB(255,255,255) );
    m_GridListCtrl.SetImageList( m_pImageList, LVSIL_SMALL );
    
    // Insert columns using the order field
    int i;
    for(i = 0; i < 4; i++)  
    {
        lvcolumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH | LVCF_ORDER;
        lvcolumn.fmt = LVCFMT_LEFT;
        lvcolumn.pszText = rgtsz[i];
        lvcolumn.iSubItem = i;
        lvcolumn.iOrder = i;
        lvcolumn.cx = rect.Width() / 4;  
        m_GridListCtrl.InsertColumn(i, &lvcolumn);  
    }
    
    int iItem, iSubItem, iActualItem;
    TCHAR buffer[30];
    
    for (iItem = 0; iItem < 50; iItem++)  // will now insert the items and subitems into the list view.
    {
        for (iSubItem = 0; iSubItem < 4; iSubItem++)
        {
            lvitem.mask = LVIF_TEXT | (iSubItem == 0? LVIF_IMAGE : 0);
            lvitem.iItem = (iSubItem == 0)? iItem : iActualItem;
            lvitem.iSubItem = iSubItem;
            lvitem.iImage = (iItem%2)?0:2;
            sprintf( buffer, "Cell( %d, %d )", iItem+1, iSubItem+1);
            lvitem.pszText = buffer;
            
            if (iSubItem == 0)
                iActualItem = m_GridListCtrl.InsertItem(&lvitem);
            else
                m_GridListCtrl.SetItem(&lvitem);
        }
    }
    
    return TRUE;  // return TRUE  unless you set the focus to a control
}

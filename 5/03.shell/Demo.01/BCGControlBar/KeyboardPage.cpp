// KeyboardPage.cpp : implementation file
//

#include "stdafx.h"
#include "KeyboardPage.h"
#include "CBCGToolbarCustomize.h"
#include "bcglocalres.h"
#include "BCGToolbarButton.h"
#include "KeyHelper.h"
#include "BCGKeyboardManager.h"
#include "BCGMultiDocTemplate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CKeyboardPage property page

IMPLEMENT_DYNCREATE(CKeyboardPage, CPropertyPage)

CKeyboardPage::CKeyboardPage() : CPropertyPage(CKeyboardPage::IDD)
{
	//{{AFX_DATA_INIT(CKeyboardPage)
	m_strDesrcription = _T("");
	m_strAssignedTo = _T("");
	//}}AFX_DATA_INIT
	
	m_hAccelTable = NULL;
	m_lpAccel = NULL;
	m_nAccelSize = 0;
	m_pSelTemplate = NULL;
	m_pSelButton = NULL;
	m_pSelEntry = NULL;
}
//******************************************************************
CKeyboardPage::~CKeyboardPage()
{
	if (m_lpAccel != NULL)
	{
		delete m_lpAccel;
	}
}
//******************************************************************
void CKeyboardPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CKeyboardPage)
	DDX_Control(pDX, IDC_BCGBARRES_ASSIGNED_TO_TITLE, m_wndAssignedToTitle);
	DDX_Control(pDX, IDC_BCGBARRES_NEW_SHORTCUT_KEY, m_wndNewKey);
    //DDX_Control(pDX, IDC_BCGBARRES_NEW_HOT_KEY, m_wndHotKey); 
	DDX_Control(pDX, IDC_BCGBARRES_VIEW_TYPE, m_wndViewTypeList);
	DDX_Control(pDX, IDC_BCGBARRES_VIEW_ICON, m_wndViewIcon);
	DDX_Control(pDX, IDC_BCGBARRES_REMOVE, m_wndRemoveButton);
	DDX_Control(pDX, IDC_BCGBARRES_CURRENT_KEYS_LIST, m_wndCurrentKeysList);
	DDX_Control(pDX, IDC_BCGBARRES_COMMANDS_LIST, m_wndCommandsList);
	DDX_Control(pDX, IDC_BCGBARRES_CATEGORY, m_wndCategoryList);
	DDX_Control(pDX, IDC_BCGBARRES_ASSIGN, m_wndAssignButton);
	DDX_Text(pDX, IDC_BCGBARRES_COMMAND_DESCRIPTION, m_strDesrcription);
	DDX_Text(pDX, IDC_BCGBARRES_ASSIGNED_TO, m_strAssignedTo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CKeyboardPage, CPropertyPage)
	//{{AFX_MSG_MAP(CKeyboardPage)
	ON_BN_CLICKED(IDC_BCGBARRES_ASSIGN, OnAssign)
	ON_CBN_SELCHANGE(IDC_BCGBARRES_CATEGORY, OnSelchangeCategory)
	ON_LBN_SELCHANGE(IDC_BCGBARRES_COMMANDS_LIST, OnSelchangeCommandsList)
	ON_LBN_SELCHANGE(IDC_BCGBARRES_CURRENT_KEYS_LIST, OnSelchangeCurrentKeysList)
	ON_BN_CLICKED(IDC_BCGBARRES_REMOVE, OnRemove)
	ON_BN_CLICKED(IDC_BCGBARRES_RESET_ALL, OnResetAll)
	ON_CBN_SELCHANGE(IDC_BCGBARRES_VIEW_TYPE, OnSelchangeViewType)
	ON_EN_UPDATE(IDC_BCGBARRES_NEW_SHORTCUT_KEY, OnUpdateNewShortcutKey)
    //ON_EN_CHANGE(IDC_BCGBARRES_NEW_HOT_KEY, OnUpdateNewShortcutKey) 
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKeyboardPage message handlers

BOOL CKeyboardPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	ASSERT (g_pKeyboardManager != NULL);

	//---------------------------------
	// Initialize commands by category:
	//---------------------------------	
	CBCGToolbarCustomize* pWndParent = DYNAMIC_DOWNCAST (CBCGToolbarCustomize, GetParent ());
	ASSERT (pWndParent != NULL);

	pWndParent->FillCategotiesComboBox (m_wndCategoryList);
	
	m_wndCategoryList.SetCurSel (0);
	OnSelchangeCategory ();

	//-------------------------------------------------------------------
	// Find all application document templates and fill menues combobox
	// by document template data:
	//------------------------------------------------------------------
	CDocManager* pDocManager = AfxGetApp ()->m_pDocManager;
	if (pDocManager != NULL)
	{
		//---------------------------------------
		// Walk all templates in the application:
		//---------------------------------------
		for (POSITION pos = pDocManager->GetFirstDocTemplatePosition (); pos != NULL;)
		{
			CBCGMultiDocTemplate* pTemplate = 
				(CBCGMultiDocTemplate*) pDocManager->GetNextDocTemplate (pos);
			ASSERT_VALID (pTemplate);
			ASSERT_KINDOF (CDocTemplate, pTemplate);

			//-----------------------------------------------------
			// We are interessing CBCGMultiDocTemplate objects with
			// the shared menu only....
			//-----------------------------------------------------
			if (!pTemplate->IsKindOf (RUNTIME_CLASS (CMultiDocTemplate)) ||
				pTemplate->m_hAccelTable == NULL)
			{
				continue;
			}

			CString strName;
			pTemplate->GetDocString (strName, CDocTemplate::docName);

			int iIndex = m_wndViewTypeList.AddString (strName);
			m_wndViewTypeList.SetItemData (iIndex, (DWORD) pTemplate);
		}
	}

	//--------------------------
	// Add a default application:
	//--------------------------
	CFrameWnd* pWndMain = DYNAMIC_DOWNCAST (CFrameWnd, AfxGetMainWnd ());
	if (pWndMain != NULL && pWndMain->m_hAccelTable != NULL)
	{
		CBCGLocalResource locaRes;

		CString strName;
		strName.LoadString (IDS_BCGBARRES_DEFAULT_VIEW);

		int iIndex = m_wndViewTypeList.AddString (strName);
		m_wndViewTypeList.SetItemData (iIndex, (DWORD) NULL);

		m_wndViewTypeList.SetCurSel (iIndex);
		OnSelchangeViewType();
	}

	if (m_wndViewTypeList.GetCurSel () == CB_ERR)
	{
		m_wndViewTypeList.SetCurSel (0);
		OnSelchangeViewType();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
//******************************************************************
void CKeyboardPage::OnAssign()
{
	ASSERT (m_lpAccel != NULL);
	ASSERT (m_pSelButton != NULL);

	//-----------------------------------------------------------
	// Obtain a new acceleration entry from the keyboard control:
	//-----------------------------------------------------------
    ASSERT (m_wndNewKey.IsKeyDefined ());

    ACCEL* pAccel = (ACCEL*) m_wndNewKey.GetAccel ();
    ASSERT (pAccel != NULL);

    pAccel->cmd = (USHORT) m_pSelButton->m_nID;
    //ACCEL accel = {0}; 
    //USHORT sht = 0; 
    //m_wndHotKey.GetHotKey(accel.key, sht); 
    //accel.fVirt = sht; 
    //accel.cmd = (USHORT)m_pSelButton->m_nID; 

	//----------------------------
	// Create a new entries array:
	//----------------------------
	LPACCEL lpAccelOld = m_lpAccel;

	m_lpAccel = new ACCEL [m_nAccelSize + 1];
	ASSERT (m_lpAccel != NULL);

	memcpy (m_lpAccel, lpAccelOld, sizeof (ACCEL) * m_nAccelSize);
	m_lpAccel [m_nAccelSize ++] = *pAccel; //accel;

	delete lpAccelOld;

	g_pKeyboardManager->UpdateAcellTable (
		m_pSelTemplate, m_lpAccel, m_nAccelSize);

	AddKeyEntry (&m_lpAccel [m_nAccelSize - 1]);

	m_wndNewKey.ResetKey ();
    //m_wndHotKey.SetWindowText(""); 
	OnUpdateNewShortcutKey ();
}
//******************************************************************
void CKeyboardPage::OnSelchangeCategory() 
{
	UpdateData ();

	int iIndex = m_wndCategoryList.GetCurSel ();
	if (iIndex == LB_ERR)
	{
		ASSERT (FALSE);
		return;
	}

	m_wndCommandsList.ResetContent ();
	m_wndCurrentKeysList.ResetContent ();

	CObList* pCategoryButtonsList = 
		(CObList*) m_wndCategoryList.GetItemData (iIndex);
	ASSERT_VALID (pCategoryButtonsList);

	for (POSITION pos = pCategoryButtonsList->GetHeadPosition (); pos != NULL;)
	{
		CBCGToolbarButton* pButton = (CBCGToolbarButton*) pCategoryButtonsList->GetNext (pos);
		ASSERT (pButton != NULL);

		if (pButton->m_nID > 0 && pButton->m_nID != (UINT) -1)
		{
			int iIndex = m_wndCommandsList.AddString (pButton->m_strText);
			m_wndCommandsList.SetItemData (iIndex, (DWORD) pButton);
		}
	}

	m_wndNewKey.EnableWindow (FALSE);
    //m_wndHotKey.EnableWindow(FALSE); 
}
//******************************************************************
void CKeyboardPage::OnSelchangeCommandsList() 
{
	m_strDesrcription.Empty ();
	m_wndCurrentKeysList.ResetContent ();
	OnSelchangeCurrentKeysList ();

	int iIndex = m_wndCommandsList.GetCurSel ();
	if (iIndex == LB_ERR)
	{
		m_pSelButton = NULL;
		m_wndNewKey.EnableWindow (FALSE);
        //m_wndHotKey.EnableWindow(FALSE); 
		UpdateData (FALSE);
		return;
	}

	//-------------------------
	// Set command description:
	//-------------------------
	m_pSelButton = (CBCGToolbarButton*) m_wndCommandsList.GetItemData (iIndex);
	ASSERT_VALID (m_pSelButton);

	CFrameWnd* pParent = GetParentFrame ();
	if (pParent != NULL && pParent->GetSafeHwnd () != NULL)
	{
		pParent->GetMessageString (m_pSelButton->m_nID,
					m_strDesrcription);
	}

	//--------------------------------------------
	// Fill keys associated with selected command:
	//--------------------------------------------
	ASSERT (m_lpAccel != NULL);
	for (int i = 0; i < m_nAccelSize; i ++)
	{
		if (m_pSelButton->m_nID == m_lpAccel [i].cmd)
		{
			AddKeyEntry (&m_lpAccel [i]);
		}
	}

	m_wndNewKey.EnableWindow ();
    //m_wndHotKey.EnableWindow(); 
	UpdateData (FALSE);
}
//******************************************************************
void CKeyboardPage::OnSelchangeCurrentKeysList() 
{
	int iIndex = m_wndCurrentKeysList.GetCurSel ();
	if (iIndex == LB_ERR)
	{
		m_pSelEntry = NULL;
		m_wndRemoveButton.EnableWindow (FALSE);
		return;
	}
	
	m_pSelEntry = (LPACCEL) m_wndCurrentKeysList.GetItemData (iIndex);
	ASSERT (m_pSelEntry != NULL);

	m_wndRemoveButton.EnableWindow ();
}
//******************************************************************
void CKeyboardPage::OnRemove() 
{
	ASSERT (m_pSelEntry != NULL);
	ASSERT (m_lpAccel != NULL);

	//----------------------------
	// Create a new entries array:
	//----------------------------
    if(m_nAccelSize > 0)
    {
        LPACCEL lpAccelOld = m_lpAccel;
        
        m_lpAccel = new ACCEL [m_nAccelSize - 1];
        ASSERT (m_lpAccel != NULL);
        
        int iNewIndex = 0;
        for (int i = 0; i < m_nAccelSize; i ++)
        {
            if (m_pSelEntry != &lpAccelOld [i])
            {
                m_lpAccel [iNewIndex ++] = lpAccelOld [i];
            }
        }
        
        delete lpAccelOld;
        m_nAccelSize --;
        
        g_pKeyboardManager->UpdateAcellTable (
            m_pSelTemplate, m_lpAccel, m_nAccelSize);
    }

	OnSelchangeCommandsList ();
}
//******************************************************************
void CKeyboardPage::OnResetAll() 
{
	{
		CBCGLocalResource locaRes;
		if (AfxMessageBox (IDS_BCGBARRES_RESET_KEYBOARD, MB_YESNO | MB_ICONQUESTION) != IDYES)
		{
			return;
		}
	}

	g_pKeyboardManager->ResetAll ();
	
	OnSelchangeViewType();
	OnSelchangeCommandsList ();
}
//******************************************************************
void CKeyboardPage::OnSelchangeViewType() 
{
	m_hAccelTable = NULL;
	m_pSelTemplate = NULL;

	if (m_lpAccel != NULL)
	{
		delete m_lpAccel;
		m_lpAccel = NULL;
	}

	int iIndex = m_wndViewTypeList.GetCurSel ();
	if (iIndex == CB_ERR)
	{
		m_wndViewIcon.SetIcon (NULL);
		return;
	}

	HICON hicon = NULL;

	CBCGMultiDocTemplate* pTemplate = 
			(CBCGMultiDocTemplate*) m_wndViewTypeList.GetItemData (iIndex);
	if (pTemplate != NULL)
	{
		ASSERT_VALID (pTemplate);

		hicon = AfxGetApp ()->LoadIcon (pTemplate->GetResId ());
		m_hAccelTable = pTemplate->m_hAccelTable;
	}
	else
	{
		CFrameWnd* pWndMain = DYNAMIC_DOWNCAST (CFrameWnd, AfxGetMainWnd ());
		if (pWndMain != NULL)
		{
			hicon = (HICON) GetClassLong (*pWndMain, GCL_HICON);
			m_hAccelTable = pWndMain->m_hAccelTable;
		}
	}

	if (hicon == NULL)
	{
		hicon = ::LoadIcon(NULL, IDI_APPLICATION);
	}

	m_wndViewIcon.SetIcon (hicon);

	ASSERT (m_hAccelTable != NULL);

	m_nAccelSize = ::CopyAcceleratorTable (m_hAccelTable, NULL, 0);

	m_lpAccel = new ACCEL [m_nAccelSize];
	ASSERT (m_lpAccel != NULL);

	::CopyAcceleratorTable (m_hAccelTable, m_lpAccel, m_nAccelSize);
	m_pSelTemplate = pTemplate;

	OnSelchangeCommandsList ();
}
//******************************************************************
void CKeyboardPage::AddKeyEntry (LPACCEL pEntry)
{
	ASSERT (pEntry != NULL);

	CKeyHelper helper (pEntry);
	
	CString str;
	helper.Format (str);

	int iIndex = m_wndCurrentKeysList.AddString (str);
	m_wndCurrentKeysList.SetItemData (iIndex, (DWORD) pEntry);
}
//******************************************************************
void CKeyboardPage::OnUpdateNewShortcutKey() 
{
    ACCEL* pAccel = (ACCEL*) m_wndNewKey.GetAccel ();
    ASSERT (pAccel != NULL);
    //ACCEL accel = {0}; 
    //USHORT sht = 0; 
    //m_wndHotKey.GetHotKey(accel.key, sht); 
    //accel.fVirt = sht; 


	m_strAssignedTo.Empty ();
	m_wndAssignedToTitle.ShowWindow (SW_HIDE);
	m_wndAssignButton.EnableWindow (FALSE);

	//if (m_wndNewKey.IsKeyDefined ())
	{
		ASSERT (m_lpAccel != NULL);

		BOOL bIsAlreadyDefined = FALSE;
		for (int i = 0; !bIsAlreadyDefined && i < m_nAccelSize; i ++)
		{
			const BYTE fRelFlags = FCONTROL | FALT | FSHIFT | FVIRTKEY;

			if (pAccel->key == m_lpAccel [i].key &&
				(pAccel->fVirt & fRelFlags) == (m_lpAccel [i].fVirt & fRelFlags))
            //if(accel.key == m_lpAccel[i].key && 
            //    (accel.fVirt & fRelFlags) == (m_lpAccel[i].fVirt & fRelFlags))
			{
                //CFrameWnd* pFrame = GetParentFrame(); 
                //ASSERT(pFrame != NULL); 
                //pFrame->GetMessageString(m_lpAccel[i].cmd, m_strAssignedTo); 

                CBCGToolbarCustomize* pWndParent = DYNAMIC_DOWNCAST (CBCGToolbarCustomize, GetParent ());
                ASSERT (pWndParent != NULL);

                LPCTSTR lpszName = pWndParent->GetCommandName (m_lpAccel [i].cmd);
                if (lpszName != NULL)
                {
                    m_strAssignedTo = lpszName;
                }
                else
                {
                    m_strAssignedTo = _T("????");
                }

				bIsAlreadyDefined = TRUE;
			}
		}

		if (!bIsAlreadyDefined)
		{
			CBCGLocalResource locaRes;
			m_strAssignedTo.LoadString (IDP_BCGBARRES_UNASSIGNED);
			
			m_wndAssignButton.EnableWindow ();
		}

		m_wndAssignedToTitle.ShowWindow (SW_SHOW);
	}

	UpdateData (FALSE);
}

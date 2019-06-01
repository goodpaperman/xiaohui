// TabFrm.cpp : implementation of the CTabFrm class
//

#include "stdafx.h"
#include "TabFrm.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
static void ExecuteMenu(UINT id,CWnd* wnd)
{
    
    CMenu popMenu;
    CWnd* pwnd;
    if (wnd == NULL)
        pwnd = AfxGetMainWnd();
    else pwnd = wnd;
    popMenu.LoadMenu(id);
    
    CPoint posMouse;
    ::GetCursorPos(&posMouse);
    
    popMenu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,posMouse.x,posMouse.y,pwnd);
}

/////////////////////////////////////////////////////////////////////////////
// CTabFrm

IMPLEMENT_DYNCREATE(CTabFrm, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CTabFrm, CMDIChildWnd)
    //{{AFX_MSG_MAP(CTabFrm)
    ON_WM_CREATE()
    ON_WM_SIZE()
    ON_COMMAND(IDM_TAB_BUTTON, OnTabButton)
    ON_COMMAND(IDM_TAB_BOTTOM, OnTabBottom)
    ON_COMMAND(IDM_TAB_FLAT, OnTabFlat)
    ON_UPDATE_COMMAND_UI(IDM_TAB_BUTTON, OnUpdateTabButton)
    ON_UPDATE_COMMAND_UI(IDM_TAB_BOTTOM, OnUpdateTabBottom)
    ON_UPDATE_COMMAND_UI(IDM_TAB_FLAT, OnUpdateTabFlat)
    //}}AFX_MSG_MAP
    ON_COMMAND_RANGE(IDM_SELECTOR_G1,IDM_SELECTOR_G10,OnSelGroup)
    ON_UPDATE_COMMAND_UI_RANGE (IDM_SELECTOR_G1,IDM_SELECTOR_G10,OnUpdateSelGroupUI)
    ON_COMMAND_RANGE(IDM_REPLACE_VIEW1,IDM_REPLACE_VIEW15,OnReplaceView)
    ON_UPDATE_COMMAND_UI_RANGE (IDM_REPLACE_VIEW1,IDM_REPLACE_VIEW15,OnUpdateReplaceViewUI)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabFrm construction/destruction

CTabFrm::CTabFrm()
{
    // TODO: add member initialization code here
    m_CurGrp = -1; // gruppo Corrente;
    m_nRighe=1;
    m_nColonne=2;
    m_pGroups = NULL;
    TRACE0("COSTRUTTORE CTabFrm\n");
    for ( int i=0;i<21;i++)
        m_nPosTab[i] = 0;
    
}

CTabFrm::~CTabFrm()
{
}


/////////////////////////////////////////////////////////////////////////////
// CTabFrm diagnostics

#ifdef _DEBUG
void CTabFrm::AssertValid() const
{
    CMDIChildWnd::AssertValid();
}

void CTabFrm::Dump(CDumpContext& dc) const
{
    CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTabFrm message handlers

void CTabFrm::OnSize(UINT nType, int cx, int cy) 
{
    
    CMDIChildWnd::OnSize(nType, cx, cy);
    TRACE2("onsizeframe cx = %d cy = %d\n",cx,cy);
    // TODO: Add your message handler code here
    //if (!OnGet2WayFrame())
    SizeSheetFrame();
}

void CTabFrm::ActivateFrame(int nCmdShow) 
{
    // TODO: Add your specialized code here and/or call the base class
    TRACE0("ACTIVATE FRAME\n");	
    CMDIChildWnd::ActivateFrame(nCmdShow);
    //if (!OnGet2WayFrame())
    SizeSheetFrame();
    
    
}

BOOL CTabFrm::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
    // TODO: Add your specialized code here and/or call the base class
    NMHDR* pnmh = (LPNMHDR) lParam;
    //   HWND hwndFrom; 
    //   UINT idFrom; 
    //   UINT code; 
    // the sheet resizes the page whenever it is activated so we need to size it correctly
    //		TRACE("OnNotify %d\n",pnmh->code);
    
    if (NM_RCLICK == pnmh->code)
    {
        //	if (id >= m_wndTab.GetCount())
        //		return CTabFrm::OnNotify(wParam, lParam, pResult);
        DWORD dwpos = ::GetMessagePos();
        CPoint point((int)LOWORD (dwpos),(int) HIWORD (dwpos));
        m_wndTab.ScreenToClient(&point);
        TC_HITTESTINFO fi;
        fi.pt.x = point.x;
        fi.pt.y = point.y;
        int id =m_wndTab.HitTest(&fi);
        if (id == -1)
            return CMDIChildWnd::OnNotify(wParam, lParam, pResult);
        UINT idmenu;
        if (OnNeedContext(id,m_wndTab.GetCurSel(),idmenu))
            ExecuteMenu(idmenu,NULL);
        
        return TRUE;
    }
    if (TTN_NEEDTEXT == pnmh->code)
    {
        int id = pnmh->idFrom;
        if (id == -1)
            return CMDIChildWnd::OnNotify(wParam, lParam, pResult);
        //	if (id >= m_wndTab.GetCount())
        //		return CTabFrm::OnNotify(wParam, lParam, pResult);
        TOOLTIPTEXT* pTTT = (TOOLTIPTEXT*)pnmh;
        CString s;
        if (OnNeedTooltip(id,s))
        { 
            lstrcpy(pTTT->szText,(const char*)s);
            return TRUE;
        }
        else
            return CMDIChildWnd::OnNotify(wParam, lParam, pResult);
 	}

     if (pnmh->idFrom != 1000)
        return CMDIChildWnd::OnNotify(wParam, lParam, pResult);
            
    if (TCN_SELCHANGE != pnmh->code)
        return CMDIChildWnd::OnNotify(wParam, lParam, pResult);
            
    TRACE1("TCN_SELCHANGE = %d\n",pnmh->idFrom);
            
    int sel = m_wndTab.GetCurSel();
    ChangeSelector(sel);
    return TRUE;
}


void CTabFrm::OnTabButton() 
{
    // TODO: Add your command handler code here
    DWORD s = m_wndTab.GetStyle();
    if (s & TCS_BUTTONS)
    {
        m_wndTab.ModifyStyle(TCS_TABS|TCS_BUTTONS|TCS_FLATBUTTONS,TCS_TABS);
        if (m_pGroups)
        {
            m_pGroups->m_bTab = TRUE;
        }
        
    }
    else
    {
        m_wndTab.ModifyStyle(TCS_TABS|TCS_BUTTONS|TCS_FLATBUTTONS,TCS_BUTTONS);
        if (m_pGroups)
        {
            m_pGroups->m_bBottom = FALSE;
            m_pGroups->m_bTab = FALSE;
        }
        
    }
    SizeSheetFrame();
    
}

void CTabFrm::OnTabBottom() 
{
    // TODO: Add your command handler code here
    DWORD s = m_wndTab.GetStyle();
    if (s & TCS_BOTTOM)
    {
        m_wndTab.ModifyStyle(TCS_BOTTOM,0);
        if (m_pGroups)
        {
            m_pGroups->m_bBottom = FALSE;
        }
        
    }
    else  // METTO BOTTOM ALLORA FORZO TABS
    {
        m_wndTab.ModifyStyle(TCS_BUTTONS|TCS_BOTTOM|TCS_TABS|TCS_FLATBUTTONS,TCS_BOTTOM|TCS_TABS);
        if (m_pGroups)
        {
            m_pGroups->m_bBottom = TRUE;
            m_pGroups->m_bTab = TRUE;
        }
        
    }
    SizeSheetFrame();
    
}

void CTabFrm::OnTabFlat() 
{
    // TODO: Add your command handler code here
    DWORD s = m_wndTab.GetStyle();
    if (s & TCS_FLATBUTTONS)
    {
        m_wndTab.ModifyStyle(TCS_FLATBUTTONS,0);
    }
    else  
    {
        m_wndTab.ModifyStyle(TCS_FLATBUTTONS|TCS_BUTTONS|TCS_TABS,TCS_FLATBUTTONS|TCS_BUTTONS);
    }
    SizeSheetFrame();
    
}

void CTabFrm::OnUpdateTabButton(CCmdUI* pCmdUI) 
{
    // TODO: Add your command update UI handler code here
    DWORD s = m_wndTab.GetStyle();
    if (s & TCS_BUTTONS)
        pCmdUI->SetText("Tabs");
    else
    {
        pCmdUI->SetText("Buttons");
        pCmdUI->Enable(!(s & TCS_BOTTOM));
    }
}

void CTabFrm::OnUpdateTabBottom(CCmdUI* pCmdUI) 
{
    // TODO: Add your command update UI handler code here
    DWORD s = m_wndTab.GetStyle();
    if (s & TCS_BOTTOM)
        pCmdUI->SetText("Tab up");
    else
        pCmdUI->SetText("Tab Down");
    
}

void CTabFrm::OnUpdateTabFlat(CCmdUI* pCmdUI) 
{
    // TODO: Add your command update UI handler code here
    DWORD s = m_wndTab.GetStyle();
    BOOL c = s & TCS_FLATBUTTONS;
    pCmdUI->SetCheck(c);
    BOOL b = !(s & TCS_BOTTOM);
    pCmdUI->Enable(b);
    if (b)
        if (c)
            pCmdUI->SetText("Normal Button");
        else
            pCmdUI->SetText("Flat Button");
        
}


BOOL CTabFrm::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
    OnGetGroups(&m_pGroups); // acquisisce struttura dati
    if (m_nRighe+m_nColonne==0)
        return CMDIChildWnd::OnCreateClient(lpcs,pContext);
    if (m_pGroups != NULL)
        if (m_pGroups->m_nGruppi > 0)
            m_CurGrp = m_pGroups->m_nGruppoIniziale; 
        
    SetNomeOggetto(m_pGroups->m_ListaGruppi[m_CurGrp].m_NomeGruppo);
        
    if (m_CurGrp < 0)
        return CMDIChildWnd::OnCreateClient(lpcs,pContext);
    CSize size(lpcs->cx,lpcs->cx);
    if (OnGet2WayFrame())  // 2 pannelli quelo a destra col tab
    {
        return FALSE;
    }
    else
    {
        if (!CreaTabControl(this))
            return FALSE;
        BuildGroup();
            
        // creo la View del pannello sinistro (la prima view della lista)
        pContext->m_pNewViewClass = m_pGroups->m_ListaGruppi[m_CurGrp].m_listview[0];
        if  (!CreateView (pContext))
            return FALSE;
    }
    //if (!OnGet2WayFrame())
    //   SetActiveView((CView*)GetPane(0,0));
        
    return TRUE;
}

BOOL CTabFrm::OnGet2WayFrame()
{
    // TODO: Add your specialized code here and/or call the base class
    return FALSE;
}

void CTabFrm::OnGetGroups(GROUP_SELECTOR_LIST** gruppo) 
{
    // TODO: Add your command handler code here
    *gruppo = NULL;
}

/////////////////////////////////////////////////////////////////////////////
// CTabFrm message handlers



void CTabFrm::OnReplaceView(UINT id) 
{
    // TODO: Add your command handler code here
    int of = (int) id - IDM_REPLACE_VIEW1;
    if (m_wndTab.GetCurSel() != of)
        m_wndTab.SetCurSel(of);
    
    ChangeSelector(of);
}


void CTabFrm::OnUpdateReplaceViewUI(CCmdUI* pCmdUI) 
{
    // TODO: Add your command update UI handler code here
    if (m_CurGrp < 0)
    {
        pCmdUI->Enable(FALSE);
        return;
        
    }
    int of =  (int)(pCmdUI->m_nID) - IDM_REPLACE_VIEW1;
    
    pCmdUI->SetCheck(m_wndTab.GetCurSel() == of);
    BOOL b =  of < m_pGroups->m_ListaGruppi[m_CurGrp].m_nViews;
    pCmdUI->Enable(b);
    if (b)
        pCmdUI->SetText(m_pGroups->m_ListaGruppi[m_CurGrp].m_prompt[of]);
    
    
}

void CTabFrm::OnSelGroup(UINT id) 
{
    // TODO: Add your command handler code here
    if (m_CurGrp < 0)
        return;

    int of = (int) id - IDM_SELECTOR_G1;
    if (of >= m_pGroups->m_nGruppi)
        return;

    SetNomeOggetto(m_pGroups->m_ListaGruppi[of].m_NomeGruppo);
    if (m_CurGrp == of)
    {
        for (int tipg=0;tipg<m_pGroups->m_ListaGruppi[of].m_nViews;tipg++)
        {
            CString s = GetNomeOggetto();
            if (!s.IsEmpty())
                s += " : ";
            s += m_pGroups->m_ListaGruppi[of].m_prompt[tipg];
            m_strTip.SetAt(tipg,s);    
        }
        return;
    }
            
    m_nPosTab[m_CurGrp] = m_wndTab.GetCurSel();
    if (m_nPosTab[m_CurGrp] < 0)
        m_nPosTab[m_CurGrp] = 0;
    m_CurGrp = of;    
    BuildGroup();
    for (int tipg=0;tipg<m_pGroups->m_ListaGruppi[of].m_nViews;tipg++)
    {
        CString s = GetNomeOggetto();
        if (!s.IsEmpty())
            s += " : ";
        s += m_pGroups->m_ListaGruppi[of].m_prompt[tipg];
        m_strTip.SetAt(tipg,s);    
    }
            
    if (m_nPosTab[m_CurGrp] >= m_pGroups->m_ListaGruppi[m_CurGrp].m_nViews)
        m_nPosTab[m_CurGrp] = 0;
    if (m_nPosTab[m_CurGrp])
        m_wndTab.SetCurSel(m_nPosTab[m_CurGrp]);
            
    ChangeSelector(m_nPosTab[m_CurGrp]);
    // m_wndSplitter.RecalcLayout();
    TRACE2("CURRENT GROUP IS %d numero view = %d\n",
        m_CurGrp,m_pGroups->m_ListaGruppi[m_CurGrp].m_nViews);    
}

void CTabFrm::OnUpdateSelGroupUI (CCmdUI* pCmdUI)
{
    // TODO: Add your command update UI handler code here
    if (m_CurGrp < 0)
    {
        pCmdUI->Enable(FALSE);
        return;	
    }
    int of =  (int)(pCmdUI->m_nID) - IDM_SELECTOR_G1;
    pCmdUI->SetCheck(m_CurGrp == of);
    BOOL b = of < m_pGroups->m_nGruppi;
    pCmdUI->Enable( b);
    if (b)
        pCmdUI->SetText(m_pGroups->m_ListaGruppi[of].m_NomeGruppo);
    
}


void  CTabFrm::BuildGroup()
{
    if (m_pGroups == NULL)
        return;

   int nelement = m_pGroups->m_ListaGruppi[m_CurGrp].m_nViews;
   char** prompt =   m_pGroups->m_ListaGruppi[m_CurGrp].m_prompt;
   CRuntimeClass** listview =  m_pGroups->m_ListaGruppi[m_CurGrp].m_listview;
   TRACE0("build group CBaseSelectSplitter\n");
   if (nelement == 0)
       return;
   TC_ITEM tc;
   tc.cchTextMax = 80;
   tc.mask =  TCIF_TEXT;
   m_wndTab.DeleteAllItems();
   m_strTip.RemoveAll();
   m_strTip.SetSize(nelement);
   CString s;
   for(int i=0;i<nelement;i++)
   {
       tc.pszText = prompt[i];
       s = GetNomeOggetto();
       if (!s.IsEmpty())
           s += " : ";
       s += prompt[i];
       m_strTip.SetAt(i, s);
       m_wndTab.InsertItem( i, &tc );
   }       
}
// private methods
BOOL CTabFrm::CreaTabControl(CWnd* pParent)
{
    DWORD stile = WS_CHILD|WS_VISIBLE | WS_CLIPSIBLINGS ;
    if (m_pGroups)
    {
        if (m_pGroups->m_bTab ) // stile tab
            stile |= TCS_TABS;
        else
            stile |= TCS_BUTTONS;
        
        if (m_pGroups->m_bTab) // stile tab
            if (m_pGroups->m_bBottom == TRUE) // alto o basso
                stile |= TCS_BOTTOM;
    }
    stile |= TCS_TOOLTIPS;
    stile |= TCS_HOTTRACK;
    
    // TODO: Add your specialized creation code here
    if (!m_wndTab.Create(stile,CRect(0,0,0,0),pParent ,1000)) // 
        return -1;
    TabCtrl_SetExtendedStyle(m_wndTab.m_hWnd,TCS_EX_FLATSEPARATORS);
    
    OnReserved(m_nReservedx,m_nReservedy);
    
    return TRUE;
}

void CTabFrm::SizeSheetFrame()
{
    if (OnGet2WayFrame())
    {
        return;
    }
    CView* p = GetActiveView();
    if (p == NULL)
        return;
    if (p->m_hWnd == NULL)
        return;
    if (m_wndTab.m_hWnd == NULL)
        return;
    CRect r;
    GetClientRect(r);
    int cx = r.Width();
    int cy = r.Height();
    m_wndTab.AdjustRect(FALSE,&r);
    r.right -= m_nReservedx;
    r.bottom -= m_nReservedy;
    
    HDWP hdwp;
    hdwp = ::BeginDeferWindowPos(2);
    ::DeferWindowPos(hdwp,m_wndTab.m_hWnd,NULL,0,0,cx,cy,SWP_NOMOVE | SWP_NOZORDER);
    ::DeferWindowPos(hdwp,p->m_hWnd,HWND_TOP,r.left,r.top,r.right-r.left,r.bottom-r.top,0);
    ::EndDeferWindowPos(hdwp);
}

BOOL  CTabFrm::ReplaceView(CRuntimeClass * pViewClass)
{
    TRACE0("REPLACE VIEW");
    CCreateContext context;
    CView* pV = GetActiveView();
    CRect r;
    pV->GetClientRect(r);
    
    // Get pointer to CDocument object so that it can be used in the creation 
    // process of the new view
    CDocument * pDoc= pV->GetDocument();
    
    // set flag so that document will not be deleted when view is destroyed
    pDoc->m_bAutoDelete=FALSE;    
    // Delete existing view 
    pV->DestroyWindow();
    // set flag back to default 
    pDoc->m_bAutoDelete=TRUE;
    
    // Create new view                      
    
    context.m_pNewViewClass=pViewClass;
    context.m_pCurrentDoc=pDoc;
    context.m_pNewDocTemplate=NULL;
    context.m_pLastView=NULL;
    context.m_pCurrentFrame=NULL;
    CView* pNewView = (CView*)CreateView(&context);
    if (pNewView == NULL)
        return FALSE;
    pNewView->OnInitialUpdate();
    SetActiveView(pNewView);
    if (!OnGet2WayFrame())
        SizeSheetFrame();
    return TRUE;
    
}

// interfaccia




BOOL CTabFrm::OnNeedTooltip(int id,CString& s)
{
    int n = m_strTip.GetSize();
    TRACE2("ON NEED TOOLTIP %d size = %d\n",id,n);
    if (!n)
        return FALSE;
    if (id >= n)
        return FALSE;
    s = m_strTip[id];
    return TRUE;
}

void CTabFrm::ChangeSelector(int sel)
{
    TRACE1("SELEZIONATO SELETTORE NUMERO %d\n",sel);
    
    if (OnGet2WayFrame())
    {
        return;
    }
    else
        ReplaceView(m_pGroups->m_ListaGruppi[m_CurGrp].m_listview[sel]);
}

BOOL CTabFrm::OnNeedContext(int id,int idsel,UINT& idmenu)
{
    return FALSE;
}

void CTabFrm::OnReserved(int& dx,int& dy)
{
    dx= 0; //30;
    dy = 0; //80;
}

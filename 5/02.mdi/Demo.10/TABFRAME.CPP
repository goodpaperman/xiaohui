// TabFrame.cpp : implementation of the CTabFrame class
//

#include "stdafx.h"
#include "TabFrame.h"
#include "Resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabFrame

IMPLEMENT_DYNCREATE(CTabFrame, CTabFrm)

BEGIN_MESSAGE_MAP(CTabFrame, CTabFrm)
//{{AFX_MSG_MAP(CTabFrame)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()
//
int CTabFrame::m_nDx = 0;
int CTabFrame::m_nDy = 0;
UINT CTabFrame::m_ID_menuSel = IDR_TABCONTEXT;
UINT CTabFrame::m_ID_menuNoSel= IDR_TABCONTEXT;
GROUP_SELECTOR_LIST* CTabFrame::m_pGroups1 = NULL;

/////////////////////////////////////////////////////////////////////////////
// CTabFrame construction/destruction

CTabFrame::CTabFrame()
{
    // TODO: add member initialization code here
    
}

CTabFrame::~CTabFrame()
{
}


/////////////////////////////////////////////////////////////////////////////
// CTabFrame diagnostics

#ifdef _DEBUG
void CTabFrame::AssertValid() const
{
    CTabFrm::AssertValid();
}

void CTabFrame::Dump(CDumpContext& dc) const
{
    CTabFrm::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTabFrame message handlers


// interfaccia

BOOL CTabFrame::OnGet2WayFrame()
{
    // TODO: Add your specialized code here and/or call the base class
    return FALSE;
}

void CTabFrame::OnGetGroups(GROUP_SELECTOR_LIST** gruppo) 
{
    // TODO: Add your command handler code here
    *gruppo = m_pGroups1;
}





void CTabFrame::OnReserved(int& dx,int& dy)
{
    dx = m_nDx;
    dy = m_nDy;
}



BOOL CTabFrame::OnNeedContext(int id,int idsel,UINT& idmenu)
{
    if ( id == idsel)
        idmenu = m_ID_menuSel;
    else
        idmenu = m_ID_menuNoSel;
    if (idmenu < 0)
        return FALSE;
    else
        return TRUE;
    
}
/////////////////////////////////////////////////////////////////////////////
// CTabFrame message handlers



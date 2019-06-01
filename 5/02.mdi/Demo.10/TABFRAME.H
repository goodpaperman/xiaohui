// TabFrame.h : interface of the CTabFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TabFrame_H__372D012B_02B8_11D2_959C_A1732ADF685D__INCLUDED_)
#define AFX_TabFrame_H__372D012B_02B8_11D2_959C_A1732ADF685D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "TabFrm.h"


class CTabFrame : public CTabFrm
{
    DECLARE_DYNCREATE(CTabFrame)
public:
    CTabFrame();
private:
    static GROUP_SELECTOR_LIST* m_pGroups1;
    //
    static UINT m_ID_menuSel;
    static UINT m_ID_menuNoSel;
    static int m_nDx;
    static int m_nDy;
private:
    
    // Attributes
public:
    
    // Operations
public:
    // Operations
public:
    //
   	static   void SetSelector(GROUP_SELECTOR_LIST* psel) {m_pGroups1 = psel;}
   	static   void SetTabContext(UINT idsel,UINT idnosel) {m_ID_menuSel = idsel; m_ID_menuNoSel = idnosel;}
   	static   void SetTabReserved(int dx,int dy) {m_nDx = dx; m_nDy = dy;}
    
    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CTabFrame)
    //}}AFX_VIRTUAL
    
    // Implementation
public:
    virtual ~CTabFrame();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
    
    // Generated message map functions
protected:
    //{{AFX_MSG(CTabFrame)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
protected:
    //GENERAL INTERFACE
    // interface
protected:
    virtual void OnReserved(int& dx,int& dy);
    virtual BOOL OnNeedContext(int id,int idsel,UINT& idmenu);
    virtual BOOL OnGet2WayFrame();
    virtual void OnGetGroups(GROUP_SELECTOR_LIST** gruppo);
};

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TabFrame_H__372D012B_02B8_11D2_959C_A1732ADF685D__INCLUDED_)

// TabFrm.h : interface of the CTabFrm class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BASESHEETFRM_H__372D012B_02B8_11D2_959C_A1732ADF685D__INCLUDED_)
#define AFX_BASESHEETFRM_H__372D012B_02B8_11D2_959C_A1732ADF685D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

struct SELECTOR_VIEWS
{
    int m_nViews;
    char** m_prompt; 
    CRuntimeClass** m_listview ; 
    char* m_NomeGruppo;
};

struct GROUP_SELECTOR_LIST
{
    int m_nGruppi;
    int m_nGruppoIniziale;
    BOOL m_bTab; // stile tab
    BOOL m_bBottom; // alto o basso
    SELECTOR_VIEWS* m_ListaGruppi;
};



class  CTabFrm : public CMDIChildWnd
{
    DECLARE_DYNCREATE(CTabFrm)
public:
    CTabFrm();
private:
    CTabCtrl m_wndTab;
    int m_nReservedx;
    int m_nReservedy;
    BOOL  ReplaceView(CRuntimeClass * pViewClass);
    void SizeSheetFrame();
    BOOL CreaTabControl(CWnd* pParent);
    void  BuildGroup();
    //
private:
    int m_nRighe;
    int m_nColonne;
    int m_CurGrp; // gruppo Corrente;
    GROUP_SELECTOR_LIST* m_pGroups;
    CStringArray m_strTip;
    CString m_strNomeOggetto;
    int m_nPosTab[21]; // POSIZIONE INIZIALE TAB[GRUPPO];
    
    // Attributes
public:
    
    // Operations
public:
    
    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CTabFrm)
public:
    virtual void ActivateFrame(int nCmdShow = -1);
protected:
    virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
    virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
    //}}AFX_VIRTUAL
    
    // Implementation
public:
    virtual ~CTabFrm();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
    
    // Generated message map functions
protected:
    //{{AFX_MSG(CTabFrm)
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnTabButton();
    afx_msg void OnTabBottom();
    afx_msg void OnTabFlat();
    afx_msg void OnUpdateTabButton(CCmdUI* pCmdUI);
    afx_msg void OnUpdateTabBottom(CCmdUI* pCmdUI);
    afx_msg void OnUpdateTabFlat(CCmdUI* pCmdUI);
    //}}AFX_MSG
    afx_msg void OnSelGroup(UINT id);
    afx_msg void OnUpdateSelGroupUI (CCmdUI*);
    afx_msg void OnReplaceView(UINT id);
    afx_msg void OnUpdateReplaceViewUI (CCmdUI*);
    DECLARE_MESSAGE_MAP()
protected:
    virtual void OnReserved(int& dx,int& dy);
    virtual void ChangeSelector(int sel);
    virtual BOOL OnNeedTooltip(int id,CString& s);
    virtual BOOL OnNeedContext(int id,int idsel,UINT& idmenu);
    virtual BOOL OnGet2WayFrame();
    virtual void OnGetGroups(GROUP_SELECTOR_LIST** gruppo);
public:
    void SetNomeOggetto(const char* s)  {m_strNomeOggetto = s;}
    CString GetNomeOggetto() { return m_strNomeOggetto;}
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BASESHEETFRM_H__372D012B_02B8_11D2_959C_A1732ADF685D__INCLUDED_)

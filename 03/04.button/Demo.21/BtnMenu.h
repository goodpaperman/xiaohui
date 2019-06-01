
// BtnMenu.h : header file

//


/////////////////////////////////////////////////////////////////////////////

// CBtnMenu window

#ifndef _BTNMENU_H

#define _BTNMENU_H


class CBtnMenu : public CButton

{
    
    
    // Construction
    
    
public:
    
    BOOL m_bLBtnDown;
    
    CBrush m_brBackground;
    
    COLORREF m_crText;
    
    CBtnMenu();
    
    void SetBkgndColor (COLORREF rgb);
    
    void SetTextColor (COLORREF rgb);
    
    void SetBitmap (UINT);
    
    
    // Attributes
    
    
public:
    
    
    // Operations
    
    
public:
    
    
    // Overrides
    
    // ClassWizard generated virtual function overrides
    
    //{{AFX_VIRTUAL(CBtnMenu)
    
public:
    
    virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
    
    //}}AFX_VIRTUAL
    
    
    // Implementation
    
    
protected:
    
    
    COLORREF m_clrBack;
    
    COLORREF m_clrText;
    
    UINT m_idBitmap;
    
    
    
public:
    
    UINT m_idCursor;
    
    void SetCursor (UINT idCursor);
    
    virtual ~CBtnMenu();
    
    
    // Generated message map functions
    
    
protected:
    
    //{{AFX_MSG(CBtnMenu)
    
    afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
    
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    
    afx_msg void OnTimer(UINT nIDEvent);
    
    //}}AFX_MSG
    
    
    DECLARE_MESSAGE_MAP()
        
};


/////////////////////////////////////////////////////////////////////////////

#endif //_BTNMENU_H


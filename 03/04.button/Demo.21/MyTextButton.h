///////////////////////////////////////////////////////////////////////////

//

// MyTextButton.h interface for CMyTextButton

// (c) Roger Onslow, 1997

// use freely and enjoy

///////////////////////////////////////////////////////////////////////////

//


#ifndef _CMyTextButton_

#define _CMyTextButton_


///////////////////////////////////////////////////////////////////////////

//

// CMyTextButton control


class CMyTextButton : public CButton {
    
    bool m_bUse3D;
    
public:
    
    CMyTextButton() : m_bUse3D(true) {}
    
    void Use3D(bool bUse3D=true) { m_bUse3D = bUse3D; }
    
protected:
    
    void Draw(CDC* pDC, const CRect& rect, UINT state);
    
    //{{AFX_MSG(CMyTextButton)
    
    afx_msg void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
    
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    
    //}}AFX_MSG
    
    //{{AFX_VIRTUAL(CMyTextButton)
    
    virtual void PreSubclassWindow();
    
    //}}AFX_VIRTUAL
    
    DECLARE_MESSAGE_MAP()
        
};


///////////////////////////////////////////////////////////////////////////

//


#endif


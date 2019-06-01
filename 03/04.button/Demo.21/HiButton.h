/************************************ 

  REVISION LOG ENTRY 
  
    Revision By: Mihai Filimon 
    
      Revised on 7/3/98 12:20:46 PM 
      
        HiButton.h : header file 
        
************************************/ 


#if !defined(AFX_HIBUTTON_H__44AF4523_1247_11D2_863B_0040055C08D9__INCLUDED_) 


#define AFX_HIBUTTON_H__44AF4523_1247_11D2_863B_0040055C08D9__INCLUDED_ 


#if _MSC_VER >= 1000 

#pragma once 

#endif // _MSC_VER >= 1000 


///////////////////////////////////////////////////////////////////////////// 


// CHiButton window 


class CHiButton : public CButton 

{ 
    
    // Construction 
    
public: 
    
    CHiButton(); 
    
    BOOL m_bInsideButton; 
    
    HBITMAP SetBitmap( HBITMAP hBitmap ); 
    
    HICON SetIcon( HICON hIcon ); 
    
    HCURSOR SetCursor( HCURSOR hCursor ); 
    
    // Attributes 
    
public: 
    
    
    // Operations 
    
public: 
    
    
    // Overrides 
    
    // ClassWizard generated virtual function overrides 
    
    //{{AFX_VIRTUAL(CHiButton) 
    
protected: 
    
    virtual void PreSubclassWindow(); 
    
    virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam); 
    
    //}}AFX_VIRTUAL 
    
    
    // Implementation 
    
public: 
    
    virtual ~CHiButton(); 
    
    
    // Generated message map functions 
    
protected: 
    
    //{{AFX_MSG(CHiButton) 
    
    // NOTE - the ClassWizard will add and remove member functions here. 
    
    //}}AFX_MSG 
    
    
    DECLARE_MESSAGE_MAP() 
        
private: 
    
    CButton m_wndButtonInside; 
    
}; 


///////////////////////////////////////////////////////////////////////////// 


//{{AFX_INSERT_LOCATION}} 

// Microsoft Developer Studio will insert additional declarations immediately before the previous line. 


#endif // !defined(AFX_HIBUTTON_H__44AF4523_1247_11D2_863B_0040055C08D9__INCLUDED_) 


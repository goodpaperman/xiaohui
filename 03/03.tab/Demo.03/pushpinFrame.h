/*
Module : PUSHPINFRAME.H
Purpose: Interface of a push pin property dialog similar 
         to the ones seen in VC 4/5
Created: PJN / 24-11-1997
History: None

Copyright (c) 1997 by PJ Naughter.  
All rights reserved.

*/


#ifndef __PUSHPINFRAME_H__
#define __PUSHPINFRAME_H__

////////////////////////////////// Includes ///////////////////////////////////
#include "pushpin.h"




////////////////////////////////// Classes ////////////////////////////////////
class CPushPinFrame : public CFrameWnd
{
public:
//constructors / destructors
	CPushPinFrame();
  virtual ~CPushPinFrame();

//add the class which will do the be used as the modeless 
//property sheet which will be embedded inside the dialog
  void SetAttachedPropertySheet(CRuntimeClass* pRuntimeModelessPropSheet);

//retrieves a pointer to the property sheet child window
  CPropertySheet* GetAttachProperySheet() const { return m_pModelessPropSheet; };


protected:
	//{{AFX_VIRTUAL(CPushPinFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

	DECLARE_DYNCREATE(CPushPinFrame)

	//{{AFX_MSG(CPushPinFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

  BOOL OwnedBySameParent(CWnd* pWnd);

  CPushPinButton  m_PushPin;
  CRuntimeClass*  m_pRuntimeModelessPropSheet;
  CPropertySheet* m_pModelessPropSheet;
};


#endif	// __PUSHPINFRAME_H__

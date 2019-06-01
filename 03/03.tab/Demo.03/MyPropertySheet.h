#ifndef __MYPROPERTYSHEET_H__
#define __MYPROPERTYSHEET_H__

#include "MyPropertyPage1.h"

class CMyPropertySheet : public CPropertySheet
{
	DECLARE_DYNCREATE(CMyPropertySheet)

public:
	CMyPropertySheet(CWnd* pWndParent = NULL);

public:
	CMyPropertyPage1 m_Page1;
	CMyPropertyPage2 m_Page2;


	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyPropertySheet)
	//}}AFX_VIRTUAL

public:
	virtual ~CMyPropertySheet();
  virtual void PostNcDestroy();

protected:
	//{{AFX_MSG(CMyPropertySheet)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif	// __MYPROPERTYSHEET_H__

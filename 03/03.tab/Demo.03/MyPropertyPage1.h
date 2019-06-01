#ifndef __MYPROPERTYPAGE1_H__
#define __MYPROPERTYPAGE1_H__

#include "resource.h"

class CMyPropertyPage1 : public CPropertyPage
{
	DECLARE_DYNCREATE(CMyPropertyPage1)

public:
	CMyPropertyPage1();
	~CMyPropertyPage1();

	//{{AFX_DATA(CMyPropertyPage1)
	enum { IDD = IDD_PROPPAGE1 };
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CMyPropertyPage1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CMyPropertyPage1)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};


class CMyPropertyPage2 : public CPropertyPage
{
	DECLARE_DYNCREATE(CMyPropertyPage2)

public:
	CMyPropertyPage2();
	~CMyPropertyPage2();

	//{{AFX_DATA(CMyPropertyPage2)
	enum { IDD = IDD_PROPPAGE2 };
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CMyPropertyPage2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CMyPropertyPage2)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};



#endif // __MYPROPERTYPAGE1_H__

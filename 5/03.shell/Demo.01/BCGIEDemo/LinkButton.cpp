// LinkButton.cpp: implementation of the CLinkButton class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BCGIEDemo.h"
#include "LinkButton.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(CLinkButton, CBCGToolbarButton, 1)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLinkButton::CLinkButton()
{
	Initialize ();
}
//***************************************************************************************
CLinkButton::CLinkButton(LPCTSTR lpszLabel, LPCTSTR lpszURL)
{
	m_strURL = lpszURL;
	m_strText = lpszLabel;

	Initialize ();
}
//***************************************************************************************
CLinkButton::~CLinkButton()
{

}
//***************************************************************************************
void CLinkButton::Initialize ()
{
	m_nID = ID_LINK_1;
	SetImage (15);
	m_bImage = m_bText = TRUE;
}
//*********************************************************************************
void CLinkButton::CopyFrom (const CBCGToolbarButton& src)
{
	CBCGToolbarButton::CopyFrom (src);

	const CLinkButton& srcLinkButton = (const CLinkButton&) src;
	m_strURL = srcLinkButton.m_strURL;
}					
//***************************************************************************************
void CLinkButton::Serialize (CArchive& ar)
{
	CBCGToolbarButton::Serialize (ar);

	if (ar.IsLoading ())
	{
		ar >> m_strURL;
	}
	else
	{
		ar << m_strURL;
	}
}

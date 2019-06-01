// KeyHelper.cpp: implementation of the CKeyHelper class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "KeyHelper.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CKeyHelper::CKeyHelper(LPACCEL lpAccel) :
	m_lpAccel (lpAccel)
{
}
//*******************************************************************
CKeyHelper::CKeyHelper() :
	m_lpAccel (NULL)
{
}
//*******************************************************************
CKeyHelper::~CKeyHelper()
{
}
//*******************************************************************
void CKeyHelper::Format (CString& str) const
{
	str.Empty ();

	if (m_lpAccel == NULL)
	{
		ASSERT (FALSE);
		return;
	}

	if (m_lpAccel->fVirt & FCONTROL)
	{
		AddVirtKeyStr (str, VK_CONTROL);
	}

	if (m_lpAccel->fVirt & FSHIFT)
	{
		AddVirtKeyStr (str, VK_SHIFT);
	}

	if (m_lpAccel->fVirt & FALT)
	{
		AddVirtKeyStr (str, VK_MENU);
	}

	if (m_lpAccel->fVirt & FVIRTKEY)
	{
		AddVirtKeyStr (str, m_lpAccel->key, TRUE);
	}
	else
	{
		str += (char) m_lpAccel->key;
	}
}
//******************************************************************
void CKeyHelper::AddVirtKeyStr (CString& str, UINT uiVirtKey, BOOL bLast) const
{
	#define BUFFER_LEN 50
	TCHAR szBuffer [BUFFER_LEN + 1];

	long lParam = MapVirtualKey (uiVirtKey, 0) << 16;
	::GetKeyNameText (lParam, szBuffer, BUFFER_LEN);

	str += szBuffer;

	if (!bLast)
	{
		str += '+';
	}
}

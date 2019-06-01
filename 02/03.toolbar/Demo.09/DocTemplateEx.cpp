// DocTemplateEx.cpp: implementation of the CDocTemplateEx class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SwitchTB.h"
#include "DocTemplateEx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDocTemplateEx::CDocTemplateEx (UINT nIDResource, CRuntimeClass* pDocClass, CRuntimeClass* pFrameClass, CRuntimeClass* pViewClass )
	: 	CDocTemplate (nIDResource, pDocClass, pFrameClass, pViewClass )
{

}

CDocTemplateEx::~CDocTemplateEx()
{

}

int CDocTemplateEx::GetResourceID ()
{
	return (m_nIDResource);
}


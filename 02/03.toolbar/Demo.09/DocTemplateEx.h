// DocTemplateEx.h: interface for the CDocTemplateEx class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DOCTEMPLATEEX_H__0ED95744_DBDF_11D2_9146_0060082BE95D__INCLUDED_)
#define AFX_DOCTEMPLATEEX_H__0ED95744_DBDF_11D2_9146_0060082BE95D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDocTemplateEx : public CDocTemplate
// This cass adds only one feature to CDocTemplate:
// the 'GetResourceID' function.
{
public:
// construction / destruction
	CDocTemplateEx (UINT nIDResource, CRuntimeClass* pDocClass, CRuntimeClass* pFrameClass, CRuntimeClass* pViewClass );
	virtual ~CDocTemplateEx();
// attributes
	int GetResourceID ();

};

#endif // !defined(AFX_DOCTEMPLATEEX_H__0ED95744_DBDF_11D2_9146_0060082BE95D__INCLUDED_)

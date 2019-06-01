/****************************************************************************************
//	Copyright (c) 1999, Huang Shansong (ª∆…ΩÀ…)
//	Department of Automation, Tsinghua University, Beijing, P.R.China
//	hsssp@263.net or pingersoft@263.net
//	You may freely use or modify this code provided this 
//	copyright is included in all derived versions.
//	If you enhance it, please mail one copy to me. Thanks.
****************************************************************************************/

#ifndef __HSS_CONFIGRATIONS_OPTIONS_H__
#define __HSS_CONFIGRATIONS_OPTIONS_H__

#include <afxtempl.h>

typedef struct _OPTIONITEM
{
	char szText[100];		//Text shown in TreeCtrl, '\t' means one Indent, or child item.
	char szName[50];		//ID of a Option
	int iTrueValue;			//True value (>=0)
	union
	{
		UINT iTrueImage;		//True Image in the TreeCtrl
		UINT iImage;			//Image
	};
	union
	{
		UINT iFalseImage;		//False Image in the TreeCtrl
		UINT iSelectedImage;	//Selected Image
	};
	int iCritical;			//Critical Level
	BOOL fEnable;			//Enable or not
}OPTIONITEM;

class COptions
{
public:
	COptions();
	virtual ~COptions();
public:
	CMap<CString, LPCSTR, int, int&> m_Options;
	CMap<CString, LPCSTR, int, int&> m_Backups;
	CMap<UINT, UINT, int, int&> m_ImgIndex;
	CList<OPTIONITEM*, OPTIONITEM*&> m_Items;

	CImageList m_Img;
	enum OptionFlags 
	{
		CheckTrue = (int)-1,
		CheckFalse = (int)0
	};
	enum EnableFlags
	{
		Enable = (int)3, 
		Disable = (int)2, 
		StaticEnable = (int)1, 
		StaticDisable = (int)0
	};

public:
	int operator [](CString);
	int operator [](char*);

	void* SetOptionItem(CString name, CString text, int truevalue, UINT on, UINT off, UINT critical = 0, int enable = COptions::Enable);
	//To a Check Option£¨truevalue = COptions::CheckTrue == -1
	void* SetOptionItem(CString text, UINT img, UINT simg);

	BOOL GetOption(CString key, int val);
	BOOL SetOption(CString key, int val);
	BOOL AddImg(UINT img);

	int GetImageIndex(UINT img);
	int GetOption(CString key);

	void RegSave(CString section);
	void RegLoad(CString section);

	void BeginTrans();
	void CommitTrans();
	void RollbackTrans();

	void SetStaticEnable(void* p);
	void SetStaticDisable(void * p);
	void ClearStatic(void *p);

};

#endif
/****************************************************************************************
//	Copyright (c) 1999, Huang Shansong (黄山松)
//	Department of Automation, Tsinghua University, Beijing, P.R.China
//	hsssp@263.net or pingersoft@263.net
//	You may freely use or modify this code provided this 
//	copyright is included in all derived versions.
//	If you enhance it, please mail one copy to me. Thanks.
****************************************************************************************/

#include "stdafx.h"
#include "options.h"

/****************************************************************************************
* Function	:	COptions::COptions
* Description		:	
* Return Value	:	
****************************************************************************************/
COptions::COptions()
{
	m_Img.Create(16, 16, TRUE, 5, 1);
}

/****************************************************************************************
* Function	:	COptions::~COptions
* Description		:	
* Return Value	:	
****************************************************************************************/
COptions::~COptions()
{
	for (POSITION pos = m_Items.GetHeadPosition(); pos != NULL; )
	{
		delete m_Items.GetNext(pos);
	}
	m_Items.RemoveAll();
}

/****************************************************************************************
* Function	:	COptions::SetOptionItem
* Description		:	生成一个不对应于任何实际的选项的显示项目。
* Return Value	:	void*
* Parameter		:	CString text	-	
* Parameter		:	UINT img    	-	
* Parameter		:	UINT simg   	-	
****************************************************************************************/
void* COptions::SetOptionItem(CString text, UINT img, UINT simg)
{
	return SetOptionItem("", text, -1, img, simg);
}

/****************************************************************************************
* Function	:	COptions::SetOptionItem
* Description		:	设置（生成）一个对应于一个实际的选项设置的显示条目。
* Return Value	:	void*
* Parameter		:	CString name 	-	选项名称
* Parameter		:	CString text 	-	显示名称，\t表明Indent的级次。
* Parameter		:	int truevalue	-	真值为何？
										COptions::CheckTrue
										COptions::CheckFalse
										0, 1, ...
* Parameter		:	UINT on      	-	为真的时候的图标的资源号
* Parameter		:	UINT off     	-	为假的时候的图标的资源号
* Parameter		:	UINT critical	-	重要等级
* Parameter		:	int enable   	-	是否禁止
****************************************************************************************/
void* COptions::SetOptionItem(CString name, CString text, int truevalue, UINT on, UINT off, /*UINT critical, */int enable)
{
	/*
	char szText[50];		//显示在TreeCtrl里的名字，'\t'表明一个Indent，子Item
	char szName[50];		//Option的名字
	int iTrueValue;			//真值(>=0)
	UINT iTrueImage;		//为真时在StateImage里的图标
	UINT iFalseImage;		//为假时在StateImage里的图标
	UINT iImage;			//图标
	UINT iSelectedImage;	//选中时的图标
	int iCritical;			//严重程度
	void* pNext;
	*/
	OPTIONITEM * oi = new OPTIONITEM;
	ASSERT(strlen(text) < 99);
	ASSERT(strlen(name) < 49);
	strcpy(oi->szName, (LPSTR)(LPCSTR)name);
	strcpy(oi->szText, (LPSTR)(LPCSTR)text);
	oi->iTrueValue = truevalue;
	oi->iImage = AddImg(on);
	oi->iSelectedImage = AddImg(off);
	//oi->iCritical = critical;
	oi->fEnable = enable;

	m_Items.AddTail(oi);

	return oi;
}

/****************************************************************************************
* Function	:	COptions::AddImg
* Description		:	
* Return Value	:	int     	-	
* Parameter		:	UINT img	-	
****************************************************************************************/
int COptions::AddImg(UINT img)
{
	if (img == 0)
		return -1;
	int index;
	if (!m_ImgIndex.Lookup(img, index))
	{
		CBitmap bmp;
		if (!bmp.LoadBitmap(img))
			return -1;
		index = m_Img.Add(&bmp, (COLORREF)0xFFFFFF);
		if (index == -1)
			return -1;
		m_ImgIndex.SetAt(img, index);
	}
	return index;
}

/****************************************************************************************
* Function	:	COptions::GetOption
* Description		:	
* Return Value	:	BOOL       	-	
* Parameter		:	CString key	-	
* Parameter		:	int val    	-	
****************************************************************************************/
BOOL COptions::GetOption(CString key, int val)
{
	return (m_Options.Lookup(key, val));
}

/****************************************************************************************
* Function	:	COptions::GetOption
* Description		:	
* Return Value	:	int        	-	
* Parameter		:	CString key	-	
****************************************************************************************/
int COptions::GetOption(CString key)
{
	int i;
	VERIFY(m_Options.Lookup(key, i));
	return i;
}

/****************************************************************************************
* Function	:	COptions::SetOption
* Description		:	
* Return Value	:	BOOL       	-	
* Parameter		:	CString key	-	
* Parameter		:	int val    	-	
****************************************************************************************/
BOOL COptions::SetOption(CString key, int val)
{
	m_Options.SetAt(key, val);
	return true;
}

/****************************************************************************************
* Function	:	COptions::GetImageIndex
* Description		:	
* Return Value	:	int     	-	
* Parameter		:	UINT img	-	
****************************************************************************************/
int COptions::GetImageIndex(UINT img)
{
	int i;
	if (m_ImgIndex.Lookup(img, i))
		return i;
	return -1;
}

/****************************************************************************************
* Function	:	COptions::RegSave
* Description		:	
* Return Value	:	void
* Parameter		:	CString section	-	
****************************************************************************************/
void COptions::RegSave(CString section)
{
	CString key;
	int val;
	for (POSITION pos = m_Options.GetStartPosition() ; pos != NULL ; )
	{
		m_Options.GetNextAssoc(pos, key, val);
		AfxGetApp()->WriteProfileInt(section, key, val);
	}
}

/****************************************************************************************
* Function	:	COptions::RegLoad
* Description		:	
* Return Value	:	void
* Parameter		:	CString section	-	
****************************************************************************************/
void COptions::RegLoad(CString section)
{
	CString key;
	int val;
	for (POSITION pos = m_Options.GetStartPosition() ; pos != NULL ; )
	{
		m_Options.GetNextAssoc(pos, key, val);
		val = AfxGetApp()->GetProfileInt(section, key, val);
		m_Options.SetAt(key, val);
	}
}

/****************************************************************************************
* Function	:	COptions::BeginTrans
* Description		:	
* Return Value	:	void
****************************************************************************************/
void COptions::BeginTrans()
{
	m_Backups.RemoveAll();
	CString key;
	int val;
	for (POSITION pos = m_Options.GetStartPosition() ; pos != NULL; )
	{
		m_Options.GetNextAssoc(pos, key, val);
		m_Backups.SetAt(key, val);
	}
}

/****************************************************************************************
* Function	:	COptions::CommitTrans
* Description		:	
* Return Value	:	void
****************************************************************************************/
void COptions::CommitTrans()
{
}

/****************************************************************************************
* Function	:	COptions::RollbackTrans
* Description		:	
* Return Value	:	void
****************************************************************************************/
void COptions::RollbackTrans()
{
	CString key;
	int val;
	for (POSITION pos = m_Options.GetStartPosition() ; pos != NULL; )
	{
		m_Options.GetNextAssoc(pos, key, val);
		m_Backups.Lookup(key, val);
		m_Options.SetAt(key, val);
	}
}

/****************************************************************************************
* Function	:	[]
* Description		:	
* Return Value	:	int COptions::operator	-	
* Parameter		:	CString str           	-	
****************************************************************************************/
int COptions::operator [](CString str)
{
	return GetOption(str);
}

/****************************************************************************************
* Function	:	[]
* Description		:	
* Return Value	:	int COptions::operator	-	
* Parameter		:	char* str             	-	
****************************************************************************************/
int COptions::operator [](char* str)
{
	return GetOption((CString)str);
}

/****************************************************************************************
* Function	:	COptions::SetStaticEnable
* Description		:	
* Return Value	:	void
* Parameter		:	void* p	-	
****************************************************************************************/
void COptions::SetStaticEnable(void* p)
{
	((OPTIONITEM*)p)->fEnable = COptions::StaticEnable;
}

/****************************************************************************************
* Function	:	COptions::SetStaticDisable
* Description		:	
* Return Value	:	void
* Parameter		:	void * p	-	
****************************************************************************************/
void COptions::SetStaticDisable(void * p)
{
	((OPTIONITEM*)p)->fEnable = COptions::StaticDisable;
}

/****************************************************************************************
* Function	:	COptions::ClearStatic
* Description		:	
* Return Value	:	void
* Parameter		:	void *p	-	
****************************************************************************************/
void COptions::ClearStatic(void *p)
{
	((OPTIONITEM*)p)->fEnable = COptions::Enable;
}
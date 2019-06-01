/****************************************************************************************
//	Copyright (c) 1999, Huang Shansong (��ɽ��)
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
* Description		:	����һ������Ӧ���κ�ʵ�ʵ�ѡ�����ʾ��Ŀ��
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
* Description		:	���ã����ɣ�һ����Ӧ��һ��ʵ�ʵ�ѡ�����õ���ʾ��Ŀ��
* Return Value	:	void*
* Parameter		:	CString name 	-	ѡ������
* Parameter		:	CString text 	-	��ʾ���ƣ�\t����Indent�ļ��Ρ�
* Parameter		:	int truevalue	-	��ֵΪ�Σ�
										COptions::CheckTrue
										COptions::CheckFalse
										0, 1, ...
* Parameter		:	UINT on      	-	Ϊ���ʱ���ͼ�����Դ��
* Parameter		:	UINT off     	-	Ϊ�ٵ�ʱ���ͼ�����Դ��
* Parameter		:	UINT critical	-	��Ҫ�ȼ�
* Parameter		:	int enable   	-	�Ƿ��ֹ
****************************************************************************************/
void* COptions::SetOptionItem(CString name, CString text, int truevalue, UINT on, UINT off, /*UINT critical, */int enable)
{
	/*
	char szText[50];		//��ʾ��TreeCtrl������֣�'\t'����һ��Indent����Item
	char szName[50];		//Option������
	int iTrueValue;			//��ֵ(>=0)
	UINT iTrueImage;		//Ϊ��ʱ��StateImage���ͼ��
	UINT iFalseImage;		//Ϊ��ʱ��StateImage���ͼ��
	UINT iImage;			//ͼ��
	UINT iSelectedImage;	//ѡ��ʱ��ͼ��
	int iCritical;			//���س̶�
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
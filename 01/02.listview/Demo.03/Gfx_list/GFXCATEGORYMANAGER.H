// GfxCategoryManager.h: interface for the CGfxCategoryManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GFXCATEGORYMANAGER_H__F2CEE8B3_014D_11D2_83E4_0000B43382FE__INCLUDED_)
#define AFX_GFXCATEGORYMANAGER_H__F2CEE8B3_014D_11D2_83E4_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

enum { fcFixedTextCategory = 0, fcUserCategory, fcTimeCategory, fcVariableTextCategory, fcNumericCategory };

class CGfxListCtrl;
class CGfxCategoryManager;

class CGfxCategoryManager  
{
public:
	class CGfxCategory
	{
	public:
		void Clear();
		void Init(const char * _cText, const double _dbMin, const double _dbMax);
		void Init(const char * _cText, const CTime _tmFrom, const CTime _tmTo);
		void Init(const char * _cText, const char * _cCategory);

		char * cText;
		long * pItems, iItems, lKind;
		bool   bExpanded;

		char * cCategory;
		double dbMin, dbMax;
		CTime  tmFrom, tmTo;
	};

public:
	int InsertNewItem(CGfxListCtrl * pList, const long lData);
	void RemoveCategoryItems(const int iCat, const int iIdx, CGfxListCtrl * pList);
	void FillCategoryItems(const int iCat, const int iIdx, CGfxListCtrl * pList);
	void InsertCategoryInList(CGfxListCtrl * pList);
	int IsListItemACategory(DWORD dwData);
	void ResetList(CGfxListCtrl * pList);
	void SetupList(CGfxListCtrl * pList);
	void AddItemToCategory(const int _iCategory, const long dwData);
	int AddCategory(const char * cText, const dbMin, const dbMax);
	int AddCategory(const char * cText, const CTime tmFrom, const CTime tmTo);
	int AddCategory(const char * cText, const char * cCategory);
	int FindCategory(const double dbVal);
	int FindCategory(const CTime tmTime);
	int FindCategory(const char * cText);

	void	(CWnd::*m_fpCategoryFun)(CGfxCategoryManager * , long &);
	void	(CWnd::*m_fpDaoCategoryFun)(CGfxCategoryManager *);
				
	void	SetCategoryCallback(void (CWnd::*fpCategoryFun)(CGfxCategoryManager * , long &)) { m_fpCategoryFun = fpCategoryFun; };
	void	SetDaoCategoryCallback(void (CWnd::*fpDaoCategoryFun)(CGfxCategoryManager *)) { m_fpDaoCategoryFun = fpDaoCategoryFun; };

//	int		(__cdecl *m_fpCompareFun)(const void *elem1, const void *elem2);
//	void	SetCompareCallback(int (__cdecl *fpCompareFun)(const void *, const void *)) { m_fpCompareFun = fpCompareFun; };

	CGfxCategoryManager();
	virtual ~CGfxCategoryManager();

	long   iCategory, lMode;
	long * pItems, iItems;

	CGfxCategory * pCategory;

	CWnd * pCallBackOwner;
	
};

#endif // !defined(AFX_GFXCATEGORYMANAGER_H__F2CEE8B3_014D_11D2_83E4_0000B43382FE__INCLUDED_)

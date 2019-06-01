#if !defined(AFX_BASETREEVIEW_H__FA327061_63AC_11D2_89CB_D1CE14573F5F__INCLUDED_)
#define AFX_BASETREEVIEW_H__FA327061_63AC_11D2_89CB_D1CE14573F5F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BaseTreeView.h : header file
//
#include <list>
using namespace std;

/////////////////////////////////////////////////////////////////////////////
// CTreeViewExt view
#define	WM_DATAAVAILABLE	WM_USER+101

// type T specifies any used defined structure specific to the tree data
template<class T>
class CTreeViewExt
{
protected:
		
	virtual ~CTreeViewExt() {}

	struct TreeData
	{
	public:
		unsigned short		m_nImage; // Image index in case you provide image 
									// for tree items
		CString				m_strText; // Text for the item
		T					m_Data; // Data 
		HTREEITEM			m_hHandle; // This sometimes refers to handle of 
										// the tree item of this object and 
										// otherwise to the parent
	public:
		TreeData() : m_nImage(-1),
			m_hHandle(NULL)
		{
		}

		bool operator==(const TreeData& Data)
		{
			return m_Data == Data.m_Data;
		}
	};

protected:
	list<TreeData>		m_ItemList;

public:
	// OnInitialUpdate starts a new thread with this function
	static UINT InitialThreadProc(LPVOID pData)
	{
		ASSERT(pData!=NULL);
		CTreeViewExt* pThis = static_cast<CTreeViewExt*>(pData);
		ASSERT(pThis!=NULL);
		return pThis->ThreadProc();
	}
	// The real thread function
	UINT ThreadProc()
	{
		// remember to call CoInitialize() here if you are calling COM functions
		GetRootItems(m_ItemList);
		GetTreeCtrl().SendMessage(WM_DATAAVAILABLE,0,0);
		list<TreeData>::iterator it, itTemp, itEnd, itInner;

		// here we start adding entries to the list in a loop and periodically
		// sending message to out control to populate the data
		// list intially has entries only for the root items and then it grows
		// as GetChildItem() returns more entries

		itEnd = m_ItemList.end();
		itEnd--;
		for(it = m_ItemList.begin(); it!=m_ItemList.end(); )
		{
			list<TreeData> List;
			GetChildItems(it,List);
			//adjust parent
			for(itInner = List.begin(); itInner!=List.end(); ++itInner)
				itInner->m_hHandle = it->m_hHandle;
			
			// append at the end of the list
			m_ItemList.insert(m_ItemList.end(),List.begin(),List.end());
						
			itTemp = it;
			++it;

			if(itTemp==itEnd)
			{
				m_ItemList.erase(itTemp);
				GetTreeCtrl().SendMessage(WM_DATAAVAILABLE,0,0);
				itEnd = m_ItemList.end();
				itEnd--;
			}
			else
			{
				m_ItemList.erase(itTemp);
			}
		}
		return 1;
	}

	virtual void GetRootItems(list<TreeData>& List) = 0;
	virtual void GetChildItems(list<TreeData>::iterator it, list<TreeData>& List) = 0;
	virtual CTreeCtrl& GetTreeCtrl() const = 0;

	// just populate the tree. You can modify this function as you see fit to your
	// application. Note that this function gets called in the main thread
	LONG OnDataAvailable(WPARAM wParam, LPARAM lParam)
	{
		list<TreeData>::iterator it;
		HTREEITEM hItem;
		TV_ITEM tvI;
		TV_INSERTSTRUCT tvIns;
		HTREEITEM hParent = NULL, hPrev = NULL;
		bool bFirst = true;

		for(it = m_ItemList.begin(); it!=m_ItemList.end();++it)
		{
			hParent = it->m_hHandle;
			if(bFirst)
			{
				hPrev = hParent;
				bFirst = false;
			}

			tvI.mask = TVIF_TEXT  | TVIF_IMAGE | TVIF_SELECTEDIMAGE| TVIF_CHILDREN;
			tvI.pszText = (LPSTR)(LPCTSTR)it->m_strText;
			tvI.cchTextMax = it->m_strText.GetLength();
			tvI.iImage = it->m_nImage;
			tvI.iSelectedImage = it->m_nImage;
		
			tvIns.item = tvI;
			tvIns.hInsertAfter = TVI_SORT;
			tvIns.hParent = it->m_hHandle;
			tvIns.item.cChildren = 1 ;

			hItem = GetTreeCtrl().InsertItem(&tvIns);

			if(hParent!=hPrev)
			{
				GetTreeCtrl().Expand(hPrev,TVE_EXPAND);
				hPrev = hParent;
			}
			else
			{
				//hPrev = hParent;
			}
			
			it->m_hHandle = hItem;
		}
		
		if(hPrev)
			GetTreeCtrl().Expand(hPrev,TVE_EXPAND);
		return 1;
	}

		
// Attributes
public:

// Operations
public:
	 void OnInitialUpdate()
	{
		AfxBeginThread(InitialThreadProc, (LPVOID)this,THREAD_PRIORITY_LOWEST);
	}



// Implementation
protected:


};

/////////////////////////////////////////////////////////////////////////////
// CTreeViewExt



//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BASETREEVIEW_H__FA327061_63AC_11D2_89CB_D1CE14573F5F__INCLUDED_)

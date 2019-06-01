// TreeDropTarget.h
// For OLE Drag and Drop between tree controls
// Designed and developed by Vinayak Tadas
// vinayakt@aditi.com
// 

#if !defined(AFX_TREEDROPTARGET_H__246241C3_897C_11D3_A59E_00A02411D21E__INCLUDED_)
#define AFX_TREEDROPTARGET_H__246241C3_897C_11D3_A59E_00A02411D21E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TreeDropTarget.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTreeDropTarget


class CDragDropTreeCtrl;
class CTreeDropTarget :public COleDropTarget	
{
// Overrides
	public:
			virtual DROPEFFECT OnDragEnter( CWnd* pWnd, COleDataObject* pDataObject, 
			DWORD dwKeyState, CPoint point );
			virtual DROPEFFECT OnDragOver( CWnd* pWnd, COleDataObject* pDataObject, 
			DWORD dwKeyState, CPoint point );
			virtual void OnDragLeave( CWnd* pWnd );
			virtual BOOL OnDrop(CWnd* pWnd, COleDataObject* pDataObject,
			DROPEFFECT dropEffect, CPoint point);
// Members
	public:
		//Static variable to store the window handle of source tree control
		static HWND m_shWndTreeCtrl;
	private:
		// Pointer to source tree control
		CDragDropTreeCtrl *m_pSourceTreeCtrl;
		// Pointer to destination tree  control
		CDragDropTreeCtrl *m_pDestTreeCtrl;
		// Recursive Function for adding items from source tree to destination tree
		void AddItem(HTREEITEM hSrcTItem,HTREEITEM hDestTItem );
		// Function to get the index of the item�s image and its 
		// selected image within the tree control�s image list
		void GetItemImages(HTREEITEM hSrcTItem, int &nSelItem, int &nNonSelItem);
		HTREEITEM m_hDestItem;
};
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TREEDROPTARGET_H__246241C3_897C_11D3_A59E_00A02411D21E__INCLUDED_)

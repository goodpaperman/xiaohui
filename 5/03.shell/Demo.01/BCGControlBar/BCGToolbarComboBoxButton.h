// BCGToolbarComboBoxButton.h: interface for the CBCGToolbarComboBoxButton class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BCGTOOLBARCOMBOBOXBUTTON_H__D5B381B4_CC65_11D1_A648_00A0C93A70EC__INCLUDED_)
#define AFX_BCGTOOLBARCOMBOBOXBUTTON_H__D5B381B4_CC65_11D1_A648_00A0C93A70EC__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXTEMPL_H__
	#include "afxtempl.h"
#endif

#include "bcgcontrolbar.h"
#include "BCGToolbarButton.h"

class BCGCONTROLBARDLLEXPORT CBCGToolbarComboBoxButton : public CBCGToolbarButton  
{
	DECLARE_SERIAL(CBCGToolbarComboBoxButton)

public:
	CBCGToolbarComboBoxButton();
	CBCGToolbarComboBoxButton(UINT uiID, int iImage, DWORD dwStyle = CBS_DROPDOWNLIST, int iWidth = 0);
	virtual ~CBCGToolbarComboBoxButton();

// Operations:
	int AddItem (LPCTSTR lpszItem, DWORD dwData = 0);
	int GetCount () const;
	LPCTSTR GetItem (int iIndex = -1) const;
	DWORD GetItemData (int iIndex = -1) const;
	void RemoveAllItems ();
	BOOL SelectItem (int iIndex);
	BOOL SelectItem (DWORD dwData);
	BOOL SelectItem (LPCTSTR lpszText);

// Overrides:
	virtual CComboBox* CreateCombo (CWnd* pWndParent, const CRect& rect);

	virtual void OnDraw (CDC* pDC, const CRect& rect, CBCGToolBarImages* pImages,
						BOOL bHorz = TRUE, BOOL bCustomizeMode = FALSE,
						BOOL bHighlight = FALSE,
						BOOL bDrawBorder = TRUE,
						BOOL bGrayDisabledButtons = TRUE);
	virtual void CopyFrom (const CBCGToolbarButton& src);
	virtual void Serialize (CArchive& ar);
	virtual SIZE OnCalculateSize (CDC* pDC, const CSize& sizeDefault, BOOL bHorz);
	virtual BOOL OnClick (CWnd* pWnd, BOOL bDelay = TRUE);
	virtual void OnChangeParentWnd (CWnd* pWndParent);
	virtual void OnMove ();
	virtual void OnSize (int iSize);
	virtual HWND GetHwnd ()
	{	
		return m_pWndCombo->GetSafeHwnd ();
	}
	virtual BOOL NotifyCommand (int iNotifyCode);
	
	virtual BOOL CanBeStretched () const
	{	
		return TRUE;	
	}
	virtual void OnAddToCustomizePage ();
	virtual HBRUSH OnCtlColor(CDC* pDC, UINT nCtlColor);
	virtual BOOL HaveHotBorder () const
	{
		return m_pWndCombo->GetSafeHwnd () == NULL ||
			(m_pWndCombo->GetStyle () & WS_VISIBLE) == 0;
	}

	virtual int OnDrawOnCustomizeList (
			CDC* pDC, const CRect& rect, BOOL bSelected);

	virtual void DuplicateData () {}

protected:
	void Initialize ();
	void AdjustRect ();

// Attributes:
public:
	CComboBox* GetComboBox () const
	{
		return m_pWndCombo;
	}
	
protected:
	DWORD				m_dwStyle;
	CComboBox*			m_pWndCombo;

	CStringList			m_lstItems;
	CList<DWORD, DWORD>	m_lstItemData;
	int					m_iWidth;
	int					m_iSelIndex;
};

#endif // !defined(AFX_BCGTOOLBARCOMBOBOXBUTTON_H__D5B381B4_CC65_11D1_A648_00A0C93A70EC__INCLUDED_)

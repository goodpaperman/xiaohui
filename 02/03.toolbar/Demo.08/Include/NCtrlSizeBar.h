#ifndef _NCTRLSIZEBAR_H
#define _NCTRLSIZEBAR_H

#include "NGenericDockBar.h"
#pragma message ("Include "__FILE__)

#ifndef NGTB_PROJECT
#define NGTB_EXPORT __declspec(dllimport)
#else
#define NGTB_EXPORT __declspec(dllexport)
#endif

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CListControlBar window

class NGTB_EXPORT CListControlBar : public CNGenericDockBar
{
// Construction
public:
	DECLARE_DYNAMIC(CListControlBar);

	CListControlBar();

// Attributes
public:
	CListCtrl  			m_ListCtrl;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListControlBar)
	//}}AFX_VIRTUAL
protected:
//	virtual CSize CalcFixedLayout(BOOL bStretch, BOOL bHorz);

	virtual void ClickListControl(NMHDR* pNMHDR);
	virtual void DblclkListControl(NMHDR* pNMHDR);
	virtual void KillfocusListControl(NMHDR* pNMHDR);
	virtual void OutofmemoryListControl(NMHDR* pNMHDR);
	virtual void RclickListControl(NMHDR* pNMHDR);
	virtual void RdblclkListControl(NMHDR* pNMHDR);
	virtual void ReturnListControl(NMHDR* pNMHDR);
	virtual void SetfocusListControl(NMHDR* pNMHDR);
	virtual void BegindragListControl(NM_LISTVIEW* pNMListView);
	virtual void BeginlabeleditListControl(LV_DISPINFO* pDispInfo);
	virtual void BeginrdragListControl(NM_LISTVIEW* pNMListView);
	virtual void ColumnclickListControl(NM_LISTVIEW* pNMListView);
	virtual void DeleteallitemsListControl(NM_LISTVIEW* pNMListView);
	virtual void DeleteitemListControl(NM_LISTVIEW* pNMListView);
	virtual void EndlabeleditListControl(LV_DISPINFO* pDispInfo);
	virtual void GetdispinfoListControl(LV_DISPINFO* pDispInfo);
	virtual void InsertitemListControl(NM_LISTVIEW* pNMListView);
	virtual void ItemchangedListControl(NM_LISTVIEW* pNMListView);
	virtual void KeydownListControl(LV_KEYDOWN* pLVKeyDow);
	virtual void ItemchangingListControl(NM_LISTVIEW* pNMListView);
	virtual void SetdispinfoListControl(LV_DISPINFO* pDispInfo);
	virtual void TrackListControl(HD_NOTIFY *phdn);
	virtual void ItemclickListControl(HD_NOTIFY *phdn);
	virtual void ItemdblclickListControl(HD_NOTIFY *phdn);
	virtual void BegintrackListControl(HD_NOTIFY *phdn);
	virtual void EndtrackListControl(HD_NOTIFY *phdn);
	virtual void DividerdblclickListControl(HD_NOTIFY *phdn);

// Implementation
public:
	virtual ~CListControlBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CListControlBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void PopupMessage();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);

	afx_msg void OnClickListControl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkListControl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKillfocusListControl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnOutofmemoryListControl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclickListControl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRdblclkListControl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReturnListControl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSetfocusListControl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBegindragListControl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBeginlabeleditListControl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBeginrdragListControl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnColumnclickListControl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeleteallitemsListControl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeleteitemListControl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEndlabeleditListControl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnGetdispinfoListControl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnInsertitemListControl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangedListControl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangingListControl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeydownListControl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSetdispinfoListControl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTrackListControl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemclickListControl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemdblclickListControl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBegintrackListControl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEndtrackListControl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDividerdblclickListControl(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif

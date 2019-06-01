///////////////////////////////////////////////////////////////////////////////
//
//  Filename:       DualListManager.h
//
//  AUTHOR     :    Copyright (C) Steve Aube, February 2000
//                  SteveAube@yahoo.com
//
//                  You can reuse and redistribute this code, provided this 
//                  header is kept as is.
//
//  Description:    This class is intended to handle moving item between two
//                  listboxes. One list represents the list of available items
//                  and the other represents the list of choosen items. This
//                  class is intended to be a member of CDialog, CFormView or
//                  CPropertyPage. All the parent class has to do is properly 
//                  initialize this class and call a couple of member functions
//                  and this class will take care of the following things:
//                  - If the "Add" button is pressed the selected item(s) are
//                    moved from the available list to the choosen list.
//                  - If the "Add All" button is pressed all of the items in
//                    are moved from the available list to the choosen list.
//                  - If the "Remove" button is pressed the selected item(s) 
//                    are moved from the choosen list to the available list.
//                  - If the "Remove All" button is pressed all of the items in
//                    are moved from the choosen list to the available list.
//                  - If the "Move Up" button is pressed the selected item(s)
//                    in the choosen list are moved up in the list by one.
//                    This button can be pressed repeatedly until all of the 
//                    selected items have reached the top of the list. When
//                    that occurs the button is disabled.
//                  - If the "Move Down" button is pressed the selected item(s)
//                    in the choosen list are moved down in the list by one.
//                  - Allows double clicking on an item to move it to the
//                    opposite list.
//                  - When item(s) are moved from one list to another the 
//                    item that was moved is selected in the list it was moved
//                    to. The list that had the item removed selects the item
//                    that is at the location of the first item that was moved.
//                    If the item at the bottom of the list is moved the item
//                    immediately above it is selected. If the last item in 
//                    the list is removed there is no selection.
//                  - Enabling/disabling of buttons - when items are moved 
//                    between lists and up and down in the choosen list the 
//                    availability of buttons changes. For instance if an item
//                    is moved to the top of the choosen list the "Move Up" 
//                    button doesn't make sense. When this occurs the "Move Up"
//                    button is automatically disabled.
//                  - Keyboard support - disabling a button that has the focus
//                    causes problems for keyboard users. This code checks to 
//                    see if a button has the focus before it disables it. If
//                    it does the focus is forwarded to the next avaiabled 
//                    control.
//                  
//                  How to use this class:
//                  - Add a member variable of this class type to the dialog
//                    box, property page or form view where you want to use it.
//                  - From the initialization method (OnInitDialog() for a 
//                    dialog box and a property page and OnInitialUpdate() for
//                    a view) do the following things in this order:
//                    - Add the items to the available and choosen lists with
//                      the calls AddItemToAvailableList(...) and 
//                      AddItemToChoosenList(...). The first parameter is the
//                      name of the item and the second parameter is a unique
//                      identifier for the item.
//                    - Call InitializeControls(...) with a pointer the parent
//                      window and the IDs of all of the controls.
//                  - Override OnCmdMsg(...) 
//                  
//                  Notes:
//                  - If you don't need certain features (like the ability to
//                    move an item up or down in the choosen list) simply
//                    provide a NULL value for that id. The rest of the class
//                    will continue work correctly. The IDs for the two lists
//                    are required since a dual list manager doesn't make sense
//                    unless it has two lists to work with.
//                  - This code will work with single, multiple and extended
//                    listboxes.
//                  - The order of the controls doesn't matter. You can put 
//                    the choosen list on the left, right, top or bottom of the
//                    selected list. Just make sure you supply the control IDs
//                    in the right order.
//                  
//                  Implementation details:
//                  This class keeps track of the items in both listboxes in
//                  internal CArrays. The names associated with the items
//                  are tracked in a CMap and the item data value is used as
//                  the key. Keeping these separate lists simplfies moving
//                  items and keeping track of selection state.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __DualListManager_H__
#define __DualListManager_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>

class CDualListManager 
{
// Construction/Destruction
public:
    CDualListManager(void);
    ~CDualListManager(void);

    void AddItemToAvailableList(LPCTSTR lpszItem, long lItemData);
    void AddItemToChoosenList(LPCTSTR lpszItem, long lItemData);
	void InitializeControls(CWnd * pWndParent,
                            int    iIDAvailableList,
                            int    iIDChoosenList,
                            int    iIDAddButton,
                            int    iIDAddAllButton,
                            int    iIDRemoveButton,
                            int    iIDRemoveAllButton,
                            int    iIDMoveUpButton,
                            int    iIDMoveDownButton);
	BOOL ProcessCmdMsg(int nID, int nCode);

private:
    void    EnableButtons(void);
    void    EnableWindow(int iIDControl, BOOL bEnable);
    void    FillListboxes(CArray<long, long> * pSelectedArray = NULL, BOOL bRemoving = FALSE);
    void    MoveAll(CListBox & rLBFrom, CListBox & rLBTo, CArray<long, long> & rArrayFrom, CArray<long, long> & rArrayTo);
    void    MoveUpOrDown(BOOL bMovingUp);
    void    MoveSelected(CListBox & rLBFrom, CArray<long, long> & rArrayFrom, CArray<long, long> & rArrayTo, BOOL bRemoving);
    void    SelectLBItem(CListBox & rListBox, int iItem);

private:
    CMap  <long, long, CString, CString> m_KeyMap;
    CArray<long, long>                   m_ArrayChoosen;
    CArray<long, long>                   m_ArrayAvailable;
	CListBox	m_ctrlAvailableList;
	CListBox	m_ctrlChoosenList;
	int         m_iIDAvailableList;
	int         m_iIDChoosenList;
	int         m_iIDAddButton;
	int         m_iIDAddAllButton;
	int         m_iIDRemoveButton;
	int         m_iIDRemoveAllButton;
	int         m_iIDMoveUpButton;
	int         m_iIDMoveDownButton;
    CWnd  *     m_pWndParent;
	BOOL        m_bAvailableListSingleSelType;
	BOOL        m_bChoosenListSingleSelType;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif

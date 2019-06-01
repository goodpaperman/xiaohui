///////////////////////////////////////////////////////////////////////////////
//
//  Filename:       DualListManager.cpp
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

#include "stdafx.h"
#include "DualListManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


///////////////////////////////////////////////////////////////////////////////
//
//  Method:			CDualListManager
//
//  Purpose:		Constructor - initializes member data
//
//  Inputs:
//
//		void
//
//  Outputs:
//
//		None
//
//  Return value:
//
//		None
//
//  Exceptions:		None
//
///////////////////////////////////////////////////////////////////////////////
CDualListManager::CDualListManager(void)
: m_pWndParent(NULL)
, m_iIDAvailableList(0)
, m_iIDChoosenList(0)
, m_iIDAddButton(0)
, m_iIDAddAllButton(0)
, m_iIDRemoveButton(0)
, m_iIDRemoveAllButton(0)
, m_iIDMoveUpButton(0)
, m_iIDMoveDownButton(0)
, m_bAvailableListSingleSelType(0)
, m_bChoosenListSingleSelType(0)
{
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method:			~CDualListManager
//
//  Purpose:		Destructor - detach the listbox handles
//
//  Inputs:
//
//      void
//
//  Outputs:
//
//		None
//
//  Return value:
//
//		None
//
//  Exceptions:		None
//
///////////////////////////////////////////////////////////////////////////////
CDualListManager::~CDualListManager(void)
{
    m_ctrlAvailableList.Detach();
    m_ctrlChoosenList.Detach();
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method:			InitializeControls
//
//                  Should be called from the initialization method 
//                  (OnInitDialog() for a dialog box and a property page and 
//                  OnInitialUpdate() for a view). Before calling this method 
//                  the client code should add the listbox items to the two 
//                  lists with calls to AddItemToAvailableList(...) and 
//                  AddItemToChoosenList(...). 
//                  
//                  This method sets up this class to handle all of the 
//                  messages for the given controls.
//  Inputs:
//
//		CWnd*  pWndParent   - pointer to the parent window (should be a CDialog
//                            CPropertyPage, CFormView etc.)
//
//		int    iIDAvailableList - resource id of the available listbox
//
//		int    iIDChoosenList - resource id of the choosen listbox
//
//		int    iIDAddButton - resource id of the add button
//
//		int    iIDAddAllButton - resource id of the add all button
//
//		int    iIDRemoveButton - resource id of the remove button
//
//		int    iIDRemoveAllButton - resource id of the remove all button
//
//		int    iIDMoveUpButton - resource id of the up button
//
//		int    iIDMoveDownButton - resource id of the down button
//
//  Outputs:
//
//		None
//
//  Return value:
//
//		void 
//
//  Exceptions:		None
//
///////////////////////////////////////////////////////////////////////////////
void CDualListManager::InitializeControls(CWnd*  pWndParent,
                                         int    iIDAvailableList,
                                         int    iIDChoosenList,
                                         int    iIDAddButton,
                                         int    iIDAddAllButton,
                                         int    iIDRemoveButton,
                                         int    iIDRemoveAllButton,
                                         int    iIDMoveUpButton,
                                         int    iIDMoveDownButton)
{
    // Hold on to all of the passed in parameters.
    m_pWndParent = pWndParent;
    m_iIDAvailableList = iIDAvailableList;
    m_iIDChoosenList = iIDChoosenList;
    m_iIDAddButton = iIDAddButton;
    m_iIDAddAllButton = iIDAddAllButton;
    m_iIDRemoveButton = iIDRemoveButton;
    m_iIDRemoveAllButton = iIDRemoveAllButton;
    m_iIDMoveUpButton = iIDMoveUpButton;
    m_iIDMoveDownButton = iIDMoveDownButton;
    m_bAvailableListSingleSelType = FALSE;
    m_bChoosenListSingleSelType = FALSE;

    // This class doesn't make sense unless a parent window and two listboxes 
    // are supplied. It also doesn't make sense without at least some of the 
    // other controls. However, there is no specific set of controls that are 
    // required so no checks are done here.
    ASSERT(m_pWndParent);
    ASSERT(m_iIDAvailableList);
    ASSERT(m_iIDChoosenList);

    // Attach the control items to the windows. The lists have to exist and we
    // access them continually so having a listbox control just simplifies this
    // code.
    m_ctrlAvailableList.Attach(m_pWndParent->GetDlgItem(m_iIDAvailableList)->GetSafeHwnd());
    m_ctrlChoosenList.Attach(m_pWndParent->GetDlgItem(m_iIDChoosenList)->GetSafeHwnd());

    // Check to see whether each list is a single or multi select listbox
    m_bAvailableListSingleSelType = (m_ctrlAvailableList.GetStyle() & (LBS_MULTIPLESEL | LBS_EXTENDEDSEL) ) ? FALSE: TRUE ;
    m_bChoosenListSingleSelType   = (m_ctrlChoosenList.GetStyle() & (LBS_MULTIPLESEL | LBS_EXTENDEDSEL) ) ? FALSE: TRUE ;

    // Re-fill the listboxes with the contents of the array
    FillListboxes();

    // Select the first item in each of the listboxes
    SelectLBItem(m_ctrlAvailableList, 0);
    SelectLBItem(m_ctrlChoosenList, 0);

    // Now enable/disable the move buttons based on the contents and selction 
    // state of the listbox controls.
    EnableButtons();
}


///////////////////////////////////////////////////////////////////////////////
//
//  Method:			AddItemToAvailableList
//
//  Purpose:		Adds the passed in item to the array of items identified
//                  as being currently available for selection.  Also adds the 
//                  item to the map so the name can be looked up later.
//
//  Inputs:
//
//		LPCTSTR lpszItem
//
//		long lItemData
//
//  Outputs:
//
//		None
//
//  Return value:
//
//		void 
//
//  Exceptions:		None
//
///////////////////////////////////////////////////////////////////////////////
void CDualListManager::AddItemToAvailableList(LPCTSTR lpszItem, long lItemData)
{
    m_ArrayAvailable.Add(lItemData);
    m_KeyMap.SetAt(lItemData, lpszItem);
}


///////////////////////////////////////////////////////////////////////////////
//
//  Method:			AddItemToChoosenList
//
//  Purpose:		Adds the passed in item to the array of items identified
//                  as being currently choosen. Also adds the item to the
//                  map so the name can be looked up later.
//
//  Inputs:
//
//		LPCTSTR lpszItem
//
//		long lItemData
//
//  Outputs:
//
//		None
//
//  Return value:
//
//		void 
//
//  Exceptions:		None
//
///////////////////////////////////////////////////////////////////////////////
void CDualListManager::AddItemToChoosenList(LPCTSTR lpszItem, long lItemData)
{
    m_ArrayChoosen.Add(lItemData);
    m_KeyMap.SetAt(lItemData, lpszItem);
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method:			MoveAll
//
//  Purpose:		Moves all of the selected items from one listbox to the
//                  other.
//
//  Inputs:
//
//		CListBox & rLBFrom - listbox moving from
//
//		CArray<long, long> & rArrayFrom - array moving from
//
//		CArray<long, long> & rArrayTo - array moving to
//
//  Outputs:
//
//		None
//
//  Return value:
//
//		void 
//
//  Exceptions:		None
//
///////////////////////////////////////////////////////////////////////////////
void CDualListManager::MoveAll(CListBox & rLBFrom, CListBox & rLBTo, CArray<long, long> & rArrayFrom, CArray<long, long> & rArrayTo) 
{
    CString csName;

    // Move all of the remaining items in the listbox to the opposite array
    int iCount = rLBFrom.GetCount();
    for(int iIndex = 0; iIndex < iCount; ++iIndex)
    {
        long lVal = rLBFrom.GetItemData(iIndex);
        rArrayTo.Add(lVal);
    }

    // Clear the array of items we are clearing out
    rArrayFrom.RemoveAll();

    // Re-fill the listboxes with the contents of the array
    FillListboxes();

    // Select the first item in the to listbox
    SelectLBItem(rLBTo, 0);
}


///////////////////////////////////////////////////////////////////////////////
//
//  Method:			MoveSelected
//
//  Purpose:		Moves the selected items from one listbox and places them
//                  in the other listbox.
//
//  Inputs:
//
//		CListBox & rLBFrom - listbox moving from
//
//		CArray<long, long> & rArrayFrom - array moving from
//
//		CArray<long, long> & rArrayTo - array moving to
//
//		BOOL bRemoving - TRUE if we are removing items 
//                       FALSE if we are adding items
//
//  Outputs:
//
//		None
//
//  Return value:
//
//		void 
//
//  Exceptions:		None
//
///////////////////////////////////////////////////////////////////////////////
void CDualListManager::MoveSelected(CListBox & rLBFrom, CArray<long, long> & rArrayFrom, CArray<long, long> & rArrayTo, BOOL bRemoving)
{
    CArray<long, long>  SelectedArray;

    // Loops through all of the items in the from listbox 
    int iSelFirst = -1;
    int iCount    = rLBFrom.GetCount();
    for(int iIndex = 0; iIndex < iCount; ++iIndex)
    {
        // Check to see if this item is currently selected
        if( 0 < rLBFrom.GetSel( iIndex ) )
        {
            // Hang onto the first selected item in the list so we can keep
            // the item at that position selected.
            if(-1 == iSelFirst)
                iSelFirst = iIndex;

            // Get the item data for this item
            long lItemData = rLBFrom.GetItemData(iIndex);

            // Add the item data value to the list of selected items
            SelectedArray.Add(lItemData);

            // Add this item to the other array of items 
            rArrayTo.Add(lItemData);

            // Find this item in the array we are moving it out of and remove it
            int iCount2 = rArrayFrom.GetSize();
            for(int iIndex2 = 0; iIndex2 < iCount2; ++iIndex2)
            {
                if( lItemData == rArrayFrom[iIndex2] )
                {
                    rArrayFrom.RemoveAt(iIndex2);
                    break;
                }
            }
        }
    }

    // Re-fill the listboxes with the contents of the array
    FillListboxes(&SelectedArray, bRemoving);

    // Select one item in the from listbox at the location of the first 
    // selected item before the items were moved.
    if(-1 != iSelFirst)
    {
        SelectLBItem(rLBFrom, rLBFrom.GetCount() <= iSelFirst 
                              ? rLBFrom.GetCount() - 1 : iSelFirst);
    }
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method:			MoveUpOrDown
//
//  Purpose:		Moves the hilighted items in the list of choosen items 
//                  either up or down depending on the value of the passed in
//                  flag.
//                  
//                  If more than one item is selected all of the items are
//                  moved as a block. If one or more items have reached the 
//                  top or bottom while other haven't those items stay at their
//                  current location and the other continue to move.
//
//  Inputs:
//
//		BOOL bMovingUp - TRUE if the items should be moved up
//                       FALSE if the items should be moved down
//
//  Outputs:
//
//		None
//
//  Return value:
//
//		void 
//
//  Exceptions:		None
//
///////////////////////////////////////////////////////////////////////////////
void CDualListManager::MoveUpOrDown(BOOL bMovingUp) 
{
    int                 iIndex, iIndex2, iCount, iCount2, iOffset, iInsertAt;
    int                 iIndexSelectedMarker = -1;
    long                lItemData;
    CString             csName;
    CArray<long, long>  SelectedArray;

    // Get the count of items in the list control
    iCount = m_ctrlChoosenList.GetCount();

    // Set the base loop index and the increment/decrement value based on the
    // direction the item are being moved (up or down).
    iIndex  = (TRUE  == bMovingUp) ? 0  : iCount - 1;
    iOffset = (TRUE  == bMovingUp) ? -1 : 1;
    
    // Loop through all of the items in the list.
    while( (TRUE  == bMovingUp && iIndex < iCount) || 
           (FALSE == bMovingUp && iIndex >= 0) )
    {
        // Check if this item is selected.
        if( 0 < m_ctrlChoosenList.GetSel( iIndex ) )
        {
            // Get the item data for this item
            lItemData = m_ctrlChoosenList.GetItemData(iIndex);

            // Build a list of the selected items so we can reselect them
            // later.
            SelectedArray.Add(lItemData);

            // Don't move selected items past other selected items
            if(-1 != iIndexSelectedMarker)
            {
                // Loop through the enabled list looking for the current item
                // which is identified by the item data value.
                iCount2 = m_ArrayChoosen.GetSize();

                for(iIndex2 = 0; iIndex2 < iCount2; ++iIndex2)
                {
                    // Find the index of this item in enabled list
                    if( lItemData == m_ArrayChoosen[iIndex2] )
                    {
                        // Remove the item from its current position
                        m_ArrayChoosen.RemoveAt(iIndex2);

                        // Reinsert the item in the array one space higher 
                        // than its previous position
                        iInsertAt = (iIndex2 + iOffset) < 0 ? 0 : iIndex2 + iOffset;
                        m_ArrayChoosen.InsertAt(iInsertAt, lItemData);
                        break;
                    }
                }
            }
        }
        // If this item wasn't selected save the index so we can check it later
        // so we don't move past the any selected items.
        else if(-1 == iIndexSelectedMarker)
        {
            iIndexSelectedMarker = iIndex;
        }

        iIndex = (TRUE  == bMovingUp) ? iIndex + 1 : iIndex - 1;
    }

    // Re-fill the listboxes with the contents of the array
    FillListboxes(&SelectedArray);
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method:			FillListboxes
//
//  Purpose:		Fills both listboxes with the current contents of their
//                  associated arrays. This method also reselects the items
//                  in the passed in array of selected items in appropriate
//                  list.
//
//  Inputs:
//
//		CArray<long
//
//		long> * pSelectedArray
//
//		BOOL bRemoving
//
//  Outputs:
//
//		None
//
//  Return value:
//
//		void 
//
//  Exceptions:		None
//
///////////////////////////////////////////////////////////////////////////////
void CDualListManager::FillListboxes(CArray<long, long> * pSelectedArray, BOOL bRemoving)
{
    int     iIndex, iIndex2, iCount;
    CString csName;

    // Clear and refill the listbox of disabled commands from the disabled
    // command array.
    m_ctrlAvailableList.ResetContent();
    iCount = m_ArrayAvailable.GetSize();
    for(iIndex = 0; iIndex < iCount; ++iIndex)
    {
        m_KeyMap.Lookup(m_ArrayAvailable[iIndex], csName);
        iIndex2 = m_ctrlAvailableList.AddString(csName);
        m_ctrlAvailableList.SetItemData(iIndex2, m_ArrayAvailable[iIndex]);
    }

    // Clear and refill the listbox of enabled commands from the enabled
    // command array.
    m_ctrlChoosenList.ResetContent();
    iCount = m_ArrayChoosen.GetSize();
    for(iIndex = 0; iIndex < iCount; ++iIndex)
    {
        m_KeyMap.Lookup(m_ArrayChoosen[iIndex], csName);
        iIndex2 = m_ctrlChoosenList.AddString(csName);
        m_ctrlChoosenList.SetItemData(iIndex2, m_ArrayChoosen[iIndex]);
    }

    // Now reselect the items that were selected before we moved them.
    if(NULL != pSelectedArray)
    {
        iCount = pSelectedArray->GetSize();
        for(iIndex = 0; iIndex < iCount; ++iIndex)
        {
            m_KeyMap.Lookup(pSelectedArray->GetAt(iIndex), csName);
            if(TRUE == bRemoving)
            {
                iIndex2 = m_ctrlAvailableList.FindStringExact(-1, csName);
                SelectLBItem(m_ctrlAvailableList, iIndex2);
            }
            else
            {
                iIndex2 = m_ctrlChoosenList.FindStringExact(-1, csName);
                SelectLBItem(m_ctrlChoosenList, iIndex2);
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method:			EnableButtons
//
//  Purpose:		Enables/disables all of the buttons Add; Add All; Remove: 
//                  Remove All; Move Up; Move Down; based on the contents and 
//                  selction state of the listbox controls.
//
//  Inputs:
//
//		void
//
//  Outputs:
//
//		None
//
//  Return value:
//
//		void 
//
//  Exceptions:		None
//
///////////////////////////////////////////////////////////////////////////////
void CDualListManager::EnableButtons(void)
{
    int     iSelCountAvailable;
    int     iCountAvailable    = m_ctrlAvailableList.GetCount();
    int     iSelCountChoosen   = m_ctrlChoosenList.GetSelCount();
    int     iCountChoosen      = m_ctrlChoosenList.GetCount();

    // If either of the listboxes are single selection listboxes the call to 
    // GetSelCount() will return -1 even if an item is selected. This code 
    // checks the style flag for each control and calls GetCurSel or 
    // GetSelCount depending on which style the given listbox has.
    // Get the count for the available list
    if(TRUE == m_bAvailableListSingleSelType)
    {
        iSelCountAvailable = (-1 == m_ctrlAvailableList.GetCurSel()) ? 0 : 1;
    }
    else
    {
        iSelCountAvailable = m_ctrlAvailableList.GetSelCount();
    }
    // Get the count for the choosen list
    if(TRUE == m_bChoosenListSingleSelType)
    {
        iSelCountChoosen = (-1 == m_ctrlChoosenList.GetCurSel()) ? 0 : 1;
    }
    else
    {
        iSelCountChoosen = m_ctrlChoosenList.GetSelCount();
    }

    BOOL    bEnableMoveUp   = FALSE;
    BOOL    bEnableMoveDown = FALSE;

    // Now enable/disable the move buttons based on the contents and selction 
    // state of the listbox controls.
    EnableWindow( m_iIDAddButton, iSelCountAvailable > 0 ? TRUE : FALSE);
    EnableWindow( m_iIDAddAllButton, iCountAvailable > 0 ? TRUE : FALSE);
    EnableWindow( m_iIDRemoveButton, iSelCountChoosen > 0 ? TRUE : FALSE);
    EnableWindow( m_iIDRemoveAllButton, iCountChoosen > 0 ? TRUE : FALSE);

    // Determine whether or not the up and down buttons should be enabled or
    // disabled based on what is selected and where it is in the list.
    if(0 < iSelCountChoosen)
    {
        int     iSelFirst = -1, iSelLast = -1;

        // Loop through all of the items in the list.
        for(int iIndex = 0; iIndex < iCountChoosen; ++iIndex)
        {
            // Check if this item is selected.
            if( 0 < m_ctrlChoosenList.GetSel( iIndex ) )
            {
                if(-1 == iSelFirst)
                {
                    iSelFirst = iIndex;
                }
                iSelLast = iIndex;
            }
        }

        // Up is disabled if all of the selected items are at the top of the listbox
        bEnableMoveUp   = (iSelFirst == 0 &&  (iSelLast - iSelFirst + 1) == iSelCountChoosen)
                          ? FALSE: TRUE;

        // Down is disabled if all of the selected items are at the bottom of the listbox
        bEnableMoveDown = (iSelLast == iCountChoosen - 1  &&  (iSelLast - iSelFirst + 1) == iSelCountChoosen)
                          ? FALSE: TRUE;
    }

    // Enable/disable the up and down buttons
    EnableWindow(m_iIDMoveUpButton, bEnableMoveUp);
    EnableWindow(m_iIDMoveDownButton, bEnableMoveDown);
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method:			EnableWindow
//
//  Purpose:		Enables/disables a control based on the contents and 
//                  selection state of the listboxes. Advances the focus to the
//                  next control if the control being disabled has the focus.
//
//  Inputs:
//
//		int iIDControl
//
//		BOOL bEnable
//
//  Outputs:
//
//		None
//
//  Return value:
//
//		void 
//
//  Exceptions:		None
//
///////////////////////////////////////////////////////////////////////////////
void CDualListManager::EnableWindow(int iIDControl, BOOL bEnable)
{
    // If we are about to disable a control and it is the control that currently
    // has the focus advance the focus to the next control before disabling it.
    CWnd * pWnd = m_pWndParent->GetFocus();
    if(NULL != pWnd)
    {
        if( FALSE == bEnable && m_pWndParent->GetFocus()->GetDlgCtrlID() == iIDControl)
        {
            // Use SendMessage instead of call NextDlgCtrl() which would force
            // us to cast the rWndParent. Since we don't know if it is a CDialog,
            // CView, CProperyPage etc. calling SendMessage is the way to go.
            m_pWndParent->SendMessage(WM_NEXTDLGCTL, 0, 0L);
        }
    }

    // Now disable the control whose id was passed in if it is a valid window.
    // It may not be if this class was constructed with a NULL ID for a given
    // control
    pWnd = m_pWndParent->GetDlgItem(iIDControl);
    if(NULL != pWnd)
    {
        pWnd->EnableWindow( bEnable );
    }
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method:			SelectLBItem
//
//  Purpose:		Checks to see if the listbox is a single or multi select
//                  listbox and calls the appropriate selection method on the
//                  CListBox class.
//
//  Inputs:
//
//		CListBox & rListBox
//
//		int iItem
//
//  Outputs:
//
//		None
//
//  Return value:
//
//		void 
//
//  Exceptions:		None
//
///////////////////////////////////////////////////////////////////////////////
void CDualListManager::SelectLBItem(CListBox & rListBox, int iItem)
{
    if(rListBox.GetStyle() & (LBS_MULTIPLESEL | LBS_EXTENDEDSEL))
    {
        rListBox.SetSel(iItem);
    }
    else
    {
        rListBox.SetCurSel(iItem);
    }
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method:			ProcessCmdMsg
//
//  Purpose:		Should be called from the parents OnCmdMsg(...) method.
//                  Processes the windows commands associated with the buttons
//                  and listbox controls. Normally this would happen in the 
//                  message map but since the ids of the controls are passed
//                  into this class the message map cannot be used.
//                  
//                  The parent can also process the message if it wants or it
//                  can check the return code and bypass the message if it was
//                  handled by this method.
//
//  Inputs:
//
//		int nID - id of the control the message is associated with
//
//		int nCode - message value
//
//  Outputs:
//
//		None
//
//  Return value:
//
//		BOOL 
//
//  Exceptions:		None
//
///////////////////////////////////////////////////////////////////////////////
BOOL CDualListManager::ProcessCmdMsg(int nID, int nCode) 
{
    BOOL bProcessed = TRUE;

    // Add - button handler
    if(nID == m_iIDAddButton)
        MoveSelected(m_ctrlAvailableList, m_ArrayAvailable, m_ArrayChoosen, FALSE);
    // Add All - button handler
    else if(nID == m_iIDAddAllButton)
        MoveAll(m_ctrlAvailableList, m_ctrlChoosenList, m_ArrayAvailable, m_ArrayChoosen);
    // Remove - button handler
    else if(nID == m_iIDRemoveButton)
        MoveSelected(m_ctrlChoosenList, m_ArrayChoosen, m_ArrayAvailable, TRUE);
    // Remove All - button handler
    else if(nID == m_iIDRemoveAllButton)
        MoveAll(m_ctrlChoosenList, m_ctrlAvailableList, m_ArrayChoosen, m_ArrayAvailable);
    // Move Down - button handler
    else if(nID == m_iIDMoveDownButton)
        MoveUpOrDown(FALSE);
    // Move Up - button handler
    else if(nID == m_iIDMoveUpButton)
        MoveUpOrDown(TRUE);
    // Double Click on an item in the from list - handler
	else if(nID == m_iIDAvailableList && nCode == LBN_DBLCLK)
        MoveSelected(m_ctrlAvailableList, m_ArrayAvailable, m_ArrayChoosen, FALSE);
    // Double Click on an item in the to list - handler
	else if(nID == m_iIDChoosenList && nCode == LBN_DBLCLK)
        MoveSelected(m_ctrlChoosenList, m_ArrayChoosen, m_ArrayAvailable, TRUE);
    // Selection changed in the from list - handler
	else if(nID == m_iIDAvailableList && nCode == LBN_SELCHANGE)
        EnableButtons();
    // Selection changed in the to list - handler
	else if(nID == m_iIDChoosenList && nCode == LBN_SELCHANGE)
        EnableButtons();
    // All other messages are sent to the base class.
    else
        bProcessed = FALSE;

    // If we processed the message then update the buttons to reflect any 
    // changes we made.
    if(TRUE == bProcessed)
    {
        EnableButtons();
    }
	
    return bProcessed;
}


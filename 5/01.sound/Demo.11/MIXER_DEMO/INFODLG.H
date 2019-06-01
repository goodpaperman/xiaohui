//=============================================================================
// Copyright Langis Pitre 1998
// You may do whatever you want with this code, as long as you include this
// copyright notice in your implementation files.
//
// If you wish to add new classes to this collection, feel free to do so.
// But please send me your code so that I can update the collection.
//
// Comments and bug reports: lpitre@sympatico.ca
//
//=============================================================================
// InfoDlg.h : header file
//

#if !defined( AFX_INFODLG_H__368DA871_35E1_11D2_A1BF_000000000000__INCLUDED_ )
#define AFX_INFODLG_H__368DA871_35E1_11D2_A1BF_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <mmsystem.h>

//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
//  
//  Structures used to hold the information about mixer lines and controls
//  
//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
struct LineInfo
//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
{
	LineInfo() { pControl = NULL; list = NULL; }
	~LineInfo(){ 
		if( pControl ) delete[] pControl;
		if( list ){
			for( UINT i = 0; i < line.cControls; i++ )
				if( list[i] ) delete[] list[i];
			delete[] list;
		}
	}

	MIXERLINE line;
	MIXERCONTROL *pControl;
	MIXERCONTROLDETAILS_LISTTEXT **list;
};

//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
struct DestLineInfo
//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
{
	DestLineInfo() { pSrcLine = NULL; }
	~DestLineInfo() { if( pSrcLine ) delete[] pSrcLine; }

	LineInfo  DstLine;
	LineInfo *pSrcLine;
};

//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
struct CapsInfo
//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
{
	CapsInfo() { pDstLine = NULL; }
	~CapsInfo() { Flush(); }

	void Flush() {  if( pDstLine ) delete[] pDstLine; pDstLine = NULL; }

	MIXERCAPS caps;
	DestLineInfo *pDstLine;
};

//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
//
// This class implements the Info dialog that pops up when the user selects
// the main window's 'Device caps' menu command. It contains a tree control
// and a listbox. When the dialog is created, it queries the mixer device
// for all available mixer lines and controls. The information gathered is
// saved in the CapsInfo structure, and the name of lines and controls found
// is used to fill the tree control. When the user selects an item in the tree
// control, the list box is filled with info about this item.
//
//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
class CInfoDlg : public CDialog
//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
{
public:
	CInfoDlg( CWnd* pParent = NULL );
	
	void FillMixerInfoTree();
	void FillListBox( LPARAM param );

	//{{AFX_DATA( CInfoDlg )
	enum { IDD = IDD_INFO_DIALOG };
	CListBox	m_InfoList;
	CTreeCtrl	m_InfoTree;
	//}}AFX_DATA

	//{{AFX_VIRTUAL( CInfoDlg )
	protected:
	virtual void DoDataExchange( CDataExchange* pDX );    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:
	
	CImageList m_ImageList;
	CapsInfo   m_Info;

	void AddControls( HMIXER &hMixer, LineInfo &lInfo, HTREEITEM parent, int DstIndex, int SrcIndex );
	void PrintMixerLine( MIXERLINE &line );
	void PrintMixerControl( LineInfo &lInfo, int controlIndex );

	HTREEITEM InsertTreeItem( HTREEITEM parent, LPSTR name, LPARAM lparam ); 

	//{{AFX_MSG( CInfoDlg )
	afx_msg void OnSelchangedInfoTree( NMHDR* pNMHDR, LRESULT* pResult );
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined( AFX_INFODLG_H__368DA871_35E1_11D2_A1BF_000000000000__INCLUDED_ )

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
//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
//
// InfoDlg.cpp : CInfoDlg class implementation file
//
//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
#include "stdafx.h"
#include "mixercontrols.h"
#include "InfoDlg.h"
#include "mmreg.h"
#include "MixerBase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// type of object to insert in the tree control and info structures
enum { TYPE_ROOT, TYPE_DSTLINE, TYPE_SRCLINE, TYPE_DSTCTRL, TYPE_SRCCTRL };

//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
inline DWORD MakeLParam( int m, int n, int o, int p )
//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
{
	return(MAKELPARAM(MAKEWORD(BYTE(m),BYTE(n)),MAKEWORD(BYTE(o),BYTE(p))));
}


//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
// Name   : CInfoDlg
//          
// Descr. : 
//          
// Arg    : CWnd* pParent /*=NULL*/ : 
//-----------------------------------------------------------------------------
CInfoDlg::CInfoDlg( CWnd* pParent /*=NULL*/ ) : CDialog( CInfoDlg::IDD, pParent )
{
	//{{AFX_DATA_INIT( CInfoDlg )
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
// Name   : DoDataExchange
//          
// Descr. : 
//          
// Return : void
// Arg    : CDataExchange* pDX : 
//-----------------------------------------------------------------------------
void CInfoDlg::DoDataExchange( CDataExchange* pDX )
{
	CDialog::DoDataExchange( pDX );
	//{{AFX_DATA_MAP( CInfoDlg )
	DDX_Control( pDX, IDC_INFO_LIST, m_InfoList );
	DDX_Control( pDX, IDC_INFO_TREE, m_InfoTree );
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP( CInfoDlg, CDialog )
	//{{AFX_MSG_MAP( CInfoDlg )
	ON_NOTIFY( TVN_SELCHANGED, IDC_INFO_TREE, OnSelchangedInfoTree )
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
// Name   : OnInitDialog
//          
// Descr. : 
//          
// Return : BOOL
//-----------------------------------------------------------------------------
BOOL CInfoDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_ImageList.Create( IDB_TREE_BITMAP, 16, 0, RGB(255,255,255) );

	m_InfoTree.SetImageList( &m_ImageList, TVSIL_NORMAL );
	
	FillMixerInfoTree();

	return TRUE;
}


//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
// Name   : FillMixerInfoTree
//          
// Descr. : Fills the CapsInfo structure and the tree control with the
//          mixer device capabilities, i.e. all the audio lines and controls
//          available. For every new tree control item added, the lParam
//          field is used to store the type of mixer object it refers to, as
//          well as the destination line index, the source line index, and the
//          mixer control index ( 4 bytes of the 32-bit value ). The MakeLParam
//          inline function is used to construct the lParam from the 4 fields.
//          
// Return : void
//-----------------------------------------------------------------------------
void CInfoDlg::FillMixerInfoTree()
{
	HTREEITEM parent;
	HTREEITEM item;
	HTREEITEM subitem;
	
	HMIXER hMixer = 0;

	UINT nbMixers = mixerGetNumDevs();
	if( nbMixers < 1 )
	{
		AfxMessageBox( "No mixer device present" );
		return;
	}
	
	if ( hMixer )
		mixerClose( hMixer );

	if( mixerOpen( &hMixer, 0, 0, 0, 0 ) != MMSYSERR_NOERROR )
	{
		AfxMessageBox( "Could not open mixer device" );
		return;
	}

	m_Info.Flush();

	if( mixerGetDevCaps( ( UINT )hMixer, &m_Info.caps, sizeof( MIXERCAPS ) ) != MMSYSERR_NOERROR )
	{
		AfxMessageBox( "Error querying device capabilities." );
		return;
	}

	parent = InsertTreeItem( NULL, m_Info.caps.szPname, MakeLParam( TYPE_ROOT, 0 , 0, 0 ) );
	m_InfoTree.SetItemImage( parent, 0, 0 );

	m_Info.pDstLine = new DestLineInfo[m_Info.caps.cDestinations];

	// list the destination lines and their controls

	int nDest = m_Info.caps.cDestinations;
	for( int i = 0; i < nDest; i++ )
	{

		m_Info.pDstLine[i].DstLine.line.cbStruct = sizeof( MIXERLINE );
		m_Info.pDstLine[i].DstLine.line.dwSource = 0;
		m_Info.pDstLine[i].DstLine.line.dwDestination = i;
		mixerGetLineInfo( ( HMIXEROBJ )hMixer, &m_Info.pDstLine[i].DstLine.line, MIXER_GETLINEINFOF_DESTINATION );
				
		item = InsertTreeItem( parent, m_Info.pDstLine[i].DstLine.line.szName, MakeLParam( TYPE_DSTLINE, i, 0, 0 ) );
		m_InfoTree.SetItemImage( item, 1, 1 );

		AddControls( hMixer, m_Info.pDstLine[i].DstLine, item, i, -1 );
					
		// for each destination line, list the source lines and their controls
		UINT nconn = m_Info.pDstLine[i].DstLine.line.cConnections;
		
		m_Info.pDstLine[i].pSrcLine = new LineInfo[nconn];
		ASSERT( m_Info.pDstLine[i].pSrcLine != NULL );

		for( UINT j = 0; j < nconn; j++ )
		{
			m_Info.pDstLine[i].pSrcLine[j].line.cbStruct = sizeof( MIXERLINE );
			m_Info.pDstLine[i].pSrcLine[j].line.dwSource = j;
			m_Info.pDstLine[i].pSrcLine[j].line.dwDestination = i;
			mixerGetLineInfo( ( HMIXEROBJ )hMixer, &m_Info.pDstLine[i].pSrcLine[j].line, MIXER_GETLINEINFOF_SOURCE );
		 
			subitem = InsertTreeItem( item, m_Info.pDstLine[i].pSrcLine[j].line.szName, 
				                      MakeLParam( TYPE_SRCLINE, i, j, 0 ) );
			m_InfoTree.SetItemImage( subitem, 2, 2 );
			
			AddControls( hMixer, m_Info.pDstLine[i].pSrcLine[j], subitem, i, j );
		}
	}

	if ( hMixer )
		mixerClose( hMixer );
}

//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
// Name   : InsertTreeItem
//          
// Descr. : Utility function that adds an item to the tree control
//          
// Return : HTREEITEM        : the item added
//
// Arg    : HTREEITEM parent : parent tree item
// Arg    : LPSTR name       : tree item label
// Arg    : LPARAM lparam    : user data
//-----------------------------------------------------------------------------
HTREEITEM CInfoDlg::InsertTreeItem( HTREEITEM parent, LPSTR name, LPARAM lparam )
{
	HTREEITEM item;
	TV_INSERTSTRUCT	itemNew;

	itemNew.hParent = parent;
	itemNew.hInsertAfter = TVI_LAST;
	itemNew.item.mask = TVIF_TEXT | TVIF_PARAM;
	itemNew.item.pszText = name;
	itemNew.item.lParam  = lparam;
	
	item = m_InfoTree.InsertItem( &itemNew );

	return item;
}

//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
// Name   : AddControls
//          
// Descr. : Adds items to both the tree control and the CapsInfo structure.
//          
// Return : void
// Arg    : HMIXER &hMixer   : handle of mixer device
// Arg    : LineInfo &lInfo  : LineInfo structure to fill
// Arg    : HTREEITEM parent : parent of item(s) to add to tree control
// Arg    : int DstIndex     : index of destination line
// Arg    : int SrcIndex     : index of source line
//-----------------------------------------------------------------------------
void CInfoDlg::AddControls( HMIXER &hMixer, LineInfo &lInfo, HTREEITEM parent, int DstIndex, int SrcIndex )
{
    MIXERLINECONTROLS mixerLineControl;
	HTREEITEM item;

	UINT ncontrols = lInfo.line.cControls;
	
	lInfo.pControl = new MIXERCONTROL[ncontrols];
	ASSERT( lInfo.pControl != NULL );
	lInfo.list = new MIXERCONTROLDETAILS_LISTTEXT* [ncontrols];
	ASSERT( lInfo.list != NULL );
	
	mixerLineControl.cbStruct  = sizeof( MIXERLINECONTROLS );
	mixerLineControl.dwLineID  = lInfo.line.dwLineID;
	mixerLineControl.cControls = ncontrols;
	mixerLineControl.cbmxctrl  = sizeof( MIXERCONTROL );
	mixerLineControl.pamxctrl  = lInfo.pControl;
	
	mixerGetLineControls( ( HMIXEROBJ )hMixer, &mixerLineControl, MIXER_GETLINECONTROLSF_ALL );
	
	for( UINT k = 0; k < ncontrols; k++ )
	{
		if( SrcIndex == -1 ) // it's a destination line
		{
			item = InsertTreeItem( parent, lInfo.pControl[k].szName, 
			                       MakeLParam( TYPE_DSTCTRL, DstIndex, 0, k ) );
		}
		else
		{
			item = InsertTreeItem( parent, lInfo.pControl[k].szName,
				                   MakeLParam( TYPE_SRCCTRL, DstIndex, SrcIndex, k ) );
		}
		
		m_InfoTree.SetItemImage( item, 3, 3 );

		if( lInfo.pControl[k].cMultipleItems > 0 )
		{			
			MIXERCONTROLDETAILS details;
			details.cbStruct       = sizeof( MIXERCONTROLDETAILS );
			details.dwControlID    = lInfo.pControl[k].dwControlID;
			details.cMultipleItems = lInfo.pControl[k].cMultipleItems;
			details.cbDetails      = sizeof( MIXERCONTROLDETAILS_LISTTEXT );
			
			int listSize;
			if( lInfo.pControl[k].fdwControl & MIXERCONTROL_CONTROLF_UNIFORM )
			{
				details.cChannels = 1;
				listSize = lInfo.pControl[k].cMultipleItems;
			}
			else
			{
				details.cChannels = lInfo.line.cChannels;
				listSize = lInfo.pControl[k].cMultipleItems*lInfo.line.cChannels;
			}
			
			lInfo.list[k] = new MIXERCONTROLDETAILS_LISTTEXT[listSize];
			
			details.paDetails = lInfo.list[k];
			
			if( mixerGetControlDetails( ( HMIXEROBJ )hMixer, &details, 
				MIXER_GETCONTROLDETAILSF_LISTTEXT ) != MMSYSERR_NOERROR )
			{
				TRACE( "CInfoDlg::AddControls, mixerGetControlDetails failed\n" );
				return;
			}
		}
		else
		{
			lInfo.list[k] = NULL;
		}
	}
}

//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
// Name   : OnSelchangedInfoTree
//          
// Descr. : Called when the tree control's selection changed. Resets and fills
//          the info listbox with the appropriate information from the CapsInfo
//          structure.
//          
// Return : void
// Arg    : NMHDR* pNMHDR    : 
// Arg    : LRESULT* pResult : 
//-----------------------------------------------------------------------------
void CInfoDlg::OnSelchangedInfoTree( NMHDR* pNMHDR, LRESULT* pResult ) 
{
	NM_TREEVIEW* pNMTreeView = ( NM_TREEVIEW* )pNMHDR;

	m_InfoList.ResetContent();
	FillListBox( m_InfoTree.GetItemData( pNMTreeView->itemNew.hItem ) );
	
	*pResult = 0;
}

//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
// Name   : FillListBox
//          
// Descr. : Fills the list box with the mixer information.
//          In order to be able to find quickly the mixer line or control that
//          corresponds to a given tree control item, the param parameter was
//          filled by the 'MakeLParam' inline function with these fields:
//
//          MakeLParam( object type,
//                      destination line index, 
//                      source line index,
//                      control index ) 
//          
// Return : void
// Arg    : LPARAM param : 
//-----------------------------------------------------------------------------
void CInfoDlg::FillListBox( LPARAM param )
{
	int loWord = LOWORD( param );
	int hiWord = HIWORD( param );

	int type  = LOBYTE( loWord );
	int destI = HIBYTE( loWord );
	
	int srcI = LOBYTE( hiWord );
	int ctrI = HIBYTE( hiWord );

	switch( type )
	{
	case TYPE_DSTLINE:
		PrintMixerLine( m_Info.pDstLine[destI].DstLine.line );
		break;
	case TYPE_SRCLINE:
		PrintMixerLine( m_Info.pDstLine[destI].pSrcLine[srcI].line );
		break;
	case TYPE_DSTCTRL:
		PrintMixerControl( m_Info.pDstLine[destI].DstLine, ctrI );
		break;
	case TYPE_SRCCTRL:
		PrintMixerControl( m_Info.pDstLine[destI].pSrcLine[srcI], ctrI );
		break;
	default:
		m_InfoList.AddString( "Choose an item from the tree to display information." );
	}
}

//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
// Name   : PrintMixerLine
//          
// Descr. : Fills the listbox with info about a mixer line
//          
// Return : void
// Arg    : MIXERLINE &line : 
//-----------------------------------------------------------------------------
void CInfoDlg::PrintMixerLine( MIXERLINE &line )
{
	char buffer[128];

	m_InfoList.AddString( " -- Mixer Line --" );
	m_InfoList.AddString( "--------------------------------------------------" );

	sprintf( buffer, "Line Type:  %s", CMixerBase::GetLineTypeString(line.dwComponentType) );
	m_InfoList.AddString( buffer );
	m_InfoList.AddString( "--------------------------------------------------" );
	
	sprintf( buffer,  "Line Type no.:  -- 0x%.8x -- ", line.dwComponentType );
	m_InfoList.AddString( buffer );

	sprintf( buffer,  "Name: %s", line.szName );
	m_InfoList.AddString( buffer );

	sprintf( buffer,  "Short Name: %s", line.szShortName );
	m_InfoList.AddString( buffer );

	sprintf( buffer,  "Line ID: 0x%.8X", line.dwLineID );
	m_InfoList.AddString( buffer );


	switch( line.fdwLine )
	{
		case MIXERLINE_LINEF_ACTIVE:
			m_InfoList.AddString( "Audio line is active. Signal is probably passing through the line." );
			break;
		case MIXERLINE_LINEF_DISCONNECTED:
			m_InfoList.AddString( "Audio line is disconnected." );
			break;
		case MIXERLINE_LINEF_SOURCE:
			m_InfoList.AddString( "Audio line is an audio source line associated with a single audio destination line." );
			break;
	}

	sprintf( buffer,  "Target type: %lu -- ", line.Target.dwType );
	switch( line.Target.dwType )
	{
	case MIXERLINE_TARGETTYPE_WAVEOUT:
		strcat( buffer, "MIXERLINE_TARGETTYPE_WAVEOUT" );
		break;
	case MIXERLINE_TARGETTYPE_WAVEIN:
		strcat( buffer, "MIXERLINE_TARGETTYPE_WAVEIN" );
		break;
	case MIXERLINE_TARGETTYPE_MIDIOUT:
		strcat( buffer, "MIXERLINE_TARGETTYPE_MIDIOUT" );
		break;
	case MIXERLINE_TARGETTYPE_MIDIIN:
		strcat( buffer, "MIXERLINE_TARGETTYPE_MIDIIN" );
		break;
	case MIXERLINE_TARGETTYPE_AUX:
		strcat( buffer, "MIXERLINE_TARGETTYPE_AUX" );
		break;
	default:
		strcat( buffer, "UNKNOWN" );
		break;
	}
	m_InfoList.AddString( buffer );
	
	sprintf( buffer,  "Target name: %s", line.Target.szPname );
	m_InfoList.AddString( buffer );

	sprintf( buffer,  "Manufacturer and product IDs: %u -- %u", line.Target.wMid , line.Target.wPid );
	m_InfoList.AddString( buffer );
	
	if( line.dwComponentType > MIXERLINE_COMPONENTTYPE_DST_FIRST && line.dwComponentType <= MIXERLINE_COMPONENTTYPE_DST_LAST )
	{
		sprintf( buffer,  "Number of associated source lines: %lu", line.cConnections );
		m_InfoList.AddString( buffer );
	}
	sprintf( buffer,  "Number of channels: %lu", line.cChannels );
	m_InfoList.AddString( buffer );

	sprintf( buffer,  "Number of controls: %lu", line.cControls );
	m_InfoList.AddString( buffer );
}

//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
// Name   : PrintMixerControl
//          
// Descr. : Fills the listbox with info about a mixer control
//          
// Return : void
// Arg    : LineInfo &lInfo  : 
// Arg    : int controlIndex : 
//-----------------------------------------------------------------------------
void CInfoDlg::PrintMixerControl( LineInfo &lInfo, int controlIndex )
{
	char buffer[128];
	m_InfoList.AddString( " -- Mixer Control --" );
	m_InfoList.AddString( "--------------------------------------------------" );
	
	sprintf( buffer, "Control Type: %s", CMixerBase::GetControlTypeString( lInfo.pControl[controlIndex].dwControlType ) );
	m_InfoList.AddString( buffer );
	m_InfoList.AddString( "--------------------------------------------------" );
	
	sprintf( buffer,  "Control Type ID:  -- 0x%.8x -- ", lInfo.pControl[controlIndex].dwControlType );
	m_InfoList.AddString( buffer );

	sprintf( buffer,  "Short Name: %s", lInfo.pControl[controlIndex].szShortName );
	m_InfoList.AddString( buffer );

	sprintf( buffer,  "Name: %s", lInfo.pControl[controlIndex].szName );
	m_InfoList.AddString( buffer );

	sprintf( buffer,  "Control ID: 0x%.8X", lInfo.pControl[controlIndex].dwControlID );
	m_InfoList.AddString( buffer );


	switch( lInfo.pControl[controlIndex].dwControlType & MIXERCONTROL_CT_UNITS_MASK )
	{
		case MIXERCONTROL_CT_UNITS_UNSIGNED:
			m_InfoList.AddString( "Units: unsigned" );
			break;
		case MIXERCONTROL_CT_UNITS_PERCENT:
			m_InfoList.AddString( "Units: percent (unsigned)" );
			break;
		case MIXERCONTROL_CT_UNITS_SIGNED:
			m_InfoList.AddString( "Units: signed" );
			break;
		case MIXERCONTROL_CT_UNITS_BOOLEAN:
			m_InfoList.AddString(  "Units: boolean" );
			break;
		case MIXERCONTROL_CT_UNITS_DECIBELS:
			m_InfoList.AddString( "Units: decibels (signed)" );
			break;
		case MIXERCONTROL_CT_UNITS_CUSTOM:
			m_InfoList.AddString( "Units: custom" );
			break;
		default:
			m_InfoList.AddString( "Units: unknown" );
			break;
	}

	sprintf( buffer,  " - Min: %ld", lInfo.pControl[controlIndex].Bounds.lMinimum );
	m_InfoList.AddString( buffer );
	sprintf( buffer,  " - Max: %ld", lInfo.pControl[controlIndex].Bounds.lMaximum );
	m_InfoList.AddString( buffer );

	sprintf( buffer,  " - Steps: %lu", lInfo.pControl[controlIndex].Metrics.cSteps );
	m_InfoList.AddString( buffer );

	m_InfoList.AddString( "Status and support flags:"  );

	if( lInfo.pControl[controlIndex].fdwControl & MIXERCONTROL_CONTROLF_UNIFORM )
	{
		m_InfoList.AddString( "   - Uniform control" );
	}
	
	if( lInfo.pControl[controlIndex].fdwControl & MIXERCONTROL_CONTROLF_DISABLED )
		m_InfoList.AddString( "   - Control is disabled" );

	if( lInfo.pControl[controlIndex].fdwControl & MIXERCONTROL_CONTROLF_MULTIPLE )
		m_InfoList.AddString( "   - Multiple control. The control has two or more possible settings." );

	if( lInfo.pControl[controlIndex].cMultipleItems > 0 )
	{
		sprintf( buffer,  "Number of items per channel: %d", lInfo.pControl[controlIndex].cMultipleItems );
		m_InfoList.AddString( buffer );

		int listSize;
		if( lInfo.pControl[controlIndex].fdwControl & MIXERCONTROL_CONTROLF_UNIFORM )
		{
			listSize = lInfo.pControl[controlIndex].cMultipleItems;
		}
		else
		{
			listSize = lInfo.pControl[controlIndex].cMultipleItems*lInfo.line.cChannels;
		}
		
		for ( int i = 0; i < listSize; i++ )
		{
			sprintf( buffer,  "  -- Name: %s", lInfo.list[controlIndex][i].szName );
			m_InfoList.AddString( buffer );
		}	
	}
}


//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
// Name   : OnDestroy
//          
// Descr. : clean up image list and CapsInfo structure
//          
// Return : void
//-----------------------------------------------------------------------------
void CInfoDlg::OnDestroy() 
{
	CDialog ::OnDestroy();
	m_Info.Flush();
	m_ImageList.DeleteImageList();
}

//	AutoFillEdit Class
//
//  Copyright 2000 Softhor
//
//  Via Adige, 31 - 81100 CASERTA - Italy
//
//  Anybody can use this code or a part of it in every program,
//  commercial or not, without fee or royalty to pay.
//
//  Please don't modify this notice.

// AFEdit.cpp : implementation file
//

#include "stdafx.h"
#include "AFEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MIN_WORD_LEN	3
#define MAX_WORDS		128

/////////////////////////////////////////////////////////////////////////////
// CAFEdit

CAFEdit::CAFEdit()
{
}

CAFEdit::~CAFEdit()
{
}


BEGIN_MESSAGE_MAP(CAFEdit, CEdit)
	//{{AFX_MSG_MAP(CAFEdit)
	ON_CONTROL_REFLECT(EN_KILLFOCUS, OnKillfocus)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAFEdit message handlers

bool CAFEdit::AddString(CString sString)
{
	bool bRet;

	// I mean it's not useful to store short words
	if( sString.GetLength() < MIN_WORD_LEN )
		return false;

	// cannot add more than 128 strings
	if( m_strList.GetCount() > MAX_WORDS )
		return false;

	if( m_strList.IsEmpty() ) {
		// if list is empty add first string
		try {
			m_strList.AddHead( sString );
			bRet = true;
		} catch( CMemoryException *e ) {
			e->Delete();
			bRet = false;
		}
	} else {
		if( !m_strList.Find( sString ) ) {
			// insert into sorted list searching for a valid position
			int nCount = m_strList.GetCount();
			POSITION pos = m_strList.GetHeadPosition();
			for( int f=0; f<nCount; f++ ) {
				// ascending order
				if( sString < m_strList.GetAt( pos ) ) {
					break;
				} else {
					m_strList.GetNext( pos );
				}
			}
			try {
				if( f == nCount )
					m_strList.AddTail( sString );
				else
					m_strList.InsertBefore( pos, sString );
				bRet = true;
			} catch( CMemoryException *e ) {
				e->Delete();
				bRet = false;
			}
		} else
			bRet = true;
	}

	return bRet;
}

void CAFEdit::OnKillfocus() 
{
	// TODO: Add your control notification handler code here
	CString sBuffer, sDummy;
	GetWindowText( sBuffer );
	int nLen, nPos, nSpacePos = 0, x;

	if( nPos < 0 )
		return;

	// exclude spaces
	sBuffer.TrimLeft();
	sBuffer.TrimRight();

	if( sBuffer.IsEmpty() )
		return;

	nLen = sBuffer.GetLength();
	nPos = nLen-1;

	for( x=nLen; x>0; x-- )
		if( isspace( sBuffer.GetAt(x-1)) )
			break;
	nSpacePos = x;
	sDummy = sBuffer.Right( sBuffer.GetLength() - nSpacePos);
	AddString( sDummy );
}

void CAFEdit::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
#ifdef _DEBUG
	CString sBuffer;
	POSITION pos;
	for( int f=0; f<m_strList.GetCount(); f++ ) {
		pos = m_strList.FindIndex( f );
		sBuffer += m_strList.GetAt( pos );
		sBuffer += "\n\r";
	}

	MessageBox( sBuffer, "List", MB_OK );
#endif	
	CEdit::OnLButtonDblClk(nFlags, point);
}

void CAFEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	CEdit::OnChar(nChar, nRepCnt, nFlags);

	TRACE("%c %d\n", nChar, nChar );

	// Skip if BackSpace
	if( nChar == VK_BACK )
		return;

	if( nChar == VK_SPACE || nChar == 10 || nChar == 13) 		// not VK_RETURN (0x0D) BUT CR (0x0A), 
		OnKillfocus();

	POSITION pos;
	CString sBuffer, sDummy, sWord;
	int nLen, nLastSpace, nWordLen;

	GetWindowText( sBuffer );
	nLen = sBuffer.GetLength();
	sDummy = sBuffer;
	for( int x=nLen; x>0; x-- )
		if( isspace( sBuffer.GetAt(x-1)))
			break;

	nLastSpace = x-1;
	if( nLastSpace > 0 )
		sWord = sBuffer.Right( nLen - nLastSpace - 1 );
	else
		sWord = sBuffer;
	nWordLen = sWord.GetLength();

	if( !sWord.IsEmpty() ) {
		// maybe a fast search method could be appreciated
		for( int f=0; f<m_strList.GetCount(); f++ ) {
			pos = m_strList.FindIndex( f );
			if( sWord == m_strList.GetAt( pos ).Left( nWordLen )) {
				sDummy += m_strList.GetAt( pos ).Right( m_strList.GetAt( pos ).GetLength() - nWordLen );
				SetWindowText( sDummy );
				// select automatically inserted text
				SetSel( nLen, nLen + m_strList.GetAt( pos ).GetLength(), false );
				break;
			}
		}
	}
}

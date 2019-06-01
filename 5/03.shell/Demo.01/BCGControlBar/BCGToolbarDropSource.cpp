// BCGToolbarDropSource.cpp : implementation file
//

#include "stdafx.h"
#include "BCGToolbarDropSource.h"
#include "bcgbarres.h"
#include "bcglocalres.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBCGToolbarDropSource

CBCGToolbarDropSource::CBCGToolbarDropSource()
{
	m_bDeleteOnDrop = TRUE;
	m_bEscapePressed = FALSE;
	m_bDragStarted = FALSE;

	m_hcurDelete = NULL;
	m_hcurMove = NULL;
	m_hcurCopy = NULL;
}

CBCGToolbarDropSource::~CBCGToolbarDropSource()
{
	::DeleteObject (m_hcurDelete);
	::DeleteObject (m_hcurMove);
	::DeleteObject (m_hcurCopy);
}


BEGIN_MESSAGE_MAP(CBCGToolbarDropSource, COleDropSource)
	//{{AFX_MSG_MAP(CBCGToolbarDropSource)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBCGToolbarDropSource message handlers

SCODE CBCGToolbarDropSource::GiveFeedback(DROPEFFECT dropEffect) 
{
	HCURSOR hcur = NULL;

	switch (dropEffect)
	{
	case DROPEFFECT_MOVE:
		hcur = m_hcurMove;
		break;

	case DROPEFFECT_COPY:
		hcur = m_hcurCopy;
		break;

	default:
		hcur = m_hcurDelete;
		break;
	}

	if (hcur == NULL)
	{
		return COleDropSource::GiveFeedback(dropEffect);
	}

	::SetCursor (hcur);
	return S_OK;
}

SCODE CBCGToolbarDropSource::QueryContinueDrag(BOOL bEscapePressed, DWORD dwKeyState) 
{
	if (m_bDeleteOnDrop && m_hcurDelete != NULL)
	{
		::SetCursor (m_hcurDelete);
	}

	m_bEscapePressed = bEscapePressed;
	return COleDropSource::QueryContinueDrag(bEscapePressed, dwKeyState);
}

BOOL CBCGToolbarDropSource::OnBeginDrag(CWnd* pWnd) 
{
	if (m_hcurDelete == NULL)
	{
		CBCGLocalResource locaRes;
		m_hcurDelete = AfxGetApp ()->LoadCursor (IDC_BCGBARRES_DELETE);
		m_hcurMove = AfxGetApp ()->LoadCursor (IDC_BCGBARRES_MOVE);
		m_hcurCopy = AfxGetApp ()->LoadCursor (IDC_BCGBARRES_COPY);
	}

	m_bDragStarted = TRUE;
	return COleDropSource::OnBeginDrag(pWnd);
}

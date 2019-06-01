// A flat popup menu for controls
// Copyright (c) 1999 Andy Brown <andy@mirage.dabsol.co.uk>
// You may do whatever you like with this file, I just don't care.


#include "stdafx.h"
#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)


/***************/
/* Message map */
/***************/

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/***************/
/* Constructor */
/***************/

CMainFrame::CMainFrame()
{
}


/**************/
/* Destructor */
/**************/

CMainFrame::~CMainFrame()
{
}


/**************************/
/* CMainFrame diagnostics */
/**************************/

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

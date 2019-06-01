// A flat popup menu for controls
// Copyright (c) 1999 Andy Brown <andy@mirage.dabsol.co.uk>
// You may do whatever you like with this file, I just don't care.


#if !defined(AFX_MAINFRM_H__570E5255_6392_11D3_A25F_0000B45C6D5E__INCLUDED_)
#define AFX_MAINFRM_H__570E5255_6392_11D3_A25F_0000B45C6D5E__INCLUDED_
#pragma once


// main frame window

class CMainFrame : public CFrameWnd
{	
protected:
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

	//{{AFX_MSG(CMainFrame)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	//{{AFX_VIRTUAL(CMainFrame)
	//}}AFX_VIRTUAL

	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};


//{{AFX_INSERT_LOCATION}}


#endif // !defined(AFX_MAINFRM_H__570E5255_6392_11D3_A25F_0000B45C6D5E__INCLUDED_)

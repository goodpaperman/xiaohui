// A flat popup menu for controls
// Copyright (c) 1999 Andy Brown <andy@mirage.dabsol.co.uk>
// You may do whatever you like with this file, I just don't care.


#if !defined(AFX_SAMPLEVIEW_H__570E5259_6392_11D3_A25F_0000B45C6D5E__INCLUDED_)
#define AFX_SAMPLEVIEW_H__570E5259_6392_11D3_A25F_0000B45C6D5E__INCLUDED_
#pragma once


// view class

class CSampleView : public CView
{
public:
	CFont		*m_pFont;
	int			 m_Height;
	COLORREF m_crText;
	COLORREF m_crBack;
	CBrush	*m_pBrush;
	CRect		 m_rcFile;
	CRect		 m_rcEdit;
	CRect		 m_rcControl;
	bool		 m_bCheck1;
	bool		 m_bCheck2;

protected:
	CSampleView();
	DECLARE_DYNCREATE(CSampleView)

	//{{AFX_MSG(CSampleView)
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void ControlMenu(CPoint point);
	void FileMenu(void);
	void EditMenu(void);
	void EditColor(COLORREF& cr);

public:
	//{{AFX_VIRTUAL(CSampleView)
	public:
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

	virtual ~CSampleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};


//{{AFX_INSERT_LOCATION}}


#endif // !defined(AFX_SAMPLEVIEW_H__570E5259_6392_11D3_A25F_0000B45C6D5E__INCLUDED_)

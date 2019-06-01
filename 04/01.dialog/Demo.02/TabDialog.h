#if !defined(AFX_TabDialog_H__BC899533_D4A7_11D3_83CF_00105ABE120C__INCLUDED_)
#define AFX_TabDialog_H__BC899533_D4A7_11D3_83CF_00105ABE120C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// TabDialog.h : header file
//
#define TAB_BORDER_LEFT    0
#define TAB_BORDER_RIGHT   1
#define TAB_BORDER_TOP     2
#define TAB_BORDER_BOTTOM  3

/////////////////////////////////////////////////////////////////////////////
// CTabDialog dialog
class CPolygon  
{
public:
	CPolygon();
	virtual ~CPolygon();
	
	int m_nPoints;
	LPPOINT m_pPoints;
	void AddPoint(POINT &point);
	void AddPoint(int x, int y);
	void Free();

};

class CTabDialog : public CDialog
{
// Construction
public:
	CTabDialog( UINT nIDTemplate,CWnd* pParent = NULL);   // standard constructor

//private members
private :	

	CPolygon m_polygon;		// polygon used to draw the Tab borders
	CRgn m_Rgn;				// region  used to draw the Window
	CRgn m_testRgn;			// region  used for hitTest
	int m_nInitialWidth;	// initial window Width
	int m_nInitialHeight;	// initial window Height	

	BOOL m_bMoving;			// moving state of the window
	int m_dx;				// delta between Window left border and mouse x position
	int m_dy;				// delta between Window top border and mouse y position

	int m_bHiddenStatus;	// Current Hidden status of the Window
	int m_nXControlsMoved;	// old x translation of the controls
	int m_nYControlsMoved;	// old y translation of the controls
	int m_nXIcon;			// x Icon Position
	int m_nYIcon;			// y Icon Position
	int m_nXDC;				// x Title Position
	int m_nYDC;				// y Title Position
	CRect m_DCRect;			// x Title Rectangle
	CRect m_closeRect;		// closeBox Rectangle

	int m_nTabRound;		// round tab value

	CDC m_pDC;				// CDC used to draw the text in memory 
	CBitmap m_bitmap;		// Bitmap used to draw the text in memory 
	
// private functions
	void CreateTabPolygon();

	void OnAutoHide();

	void OnTopMost();

	void HideTabWindow();
	void ShowTabWindow();
	void MoveDialogControls(int nX,int nY);

	void InitTitleDC();

	void PositionWindowOnBorder( CPoint point);

	void ComputeTabSize();

// public members
public  :
	int m_nBorderPos;	// position of the Window on the Desktop border
	int m_nXpos;		// X position of the Window on the Desktop border
	int m_nYpos;		// Y position of the Window on the Desktop border
	int m_nTabHeight;	// Default tab height
	int m_nTabWidth;	// Default tab width

	HICON m_hTitleIcon; // Icon used on the Tab
	BOOL m_bAutoTabSize;// True if the tab is autoSized
	CString m_sTitle;	// Title String 
	BOOL m_bCloseBox;	// True if we want a close box

	BOOL m_bTopMost;		// True if Window needs to be topMost
	BOOL m_bAutoHide;		// True if Window autoHides when the mouse leave it

// public functions

	void SetTopMost(BOOL bTopMost);
	void SetAutoHide(BOOL bAutoHide);


// Dialog Data
	//{{AFX_DATA(CTabDialog)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabDialog)
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTabDialog)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	virtual BOOL OnInitDialog();
	afx_msg BOOL CTabDialog::OnEraseBkgnd(CDC *pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};




//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TabDialog_H__BC899533_D4A7_11D3_83CF_00105ABE120C__INCLUDED_)

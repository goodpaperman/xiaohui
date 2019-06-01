
/*************************************************************************

ColorBtn.h header file

CColorBtn: A control panel like color picker
           by The Gremlin

Compatibility: Visual C++ 4.0 and up.

*******************
Altered to create a customizable color picker by Corey Spagnoli 12/1998
   - removed resource dependencies and 'other' button support
   - configured for run-time changes
   - enabled on the fly dialog calculations
   - added circular shapes
   - took out registry support (using database to fill color arrays)
   - changed hungarian notation to match my company's standards 
    (my apologies to hungarian lovers like me, but rules are rules)

**************************************************************************/

#ifndef _COLORBTN_H_
#define _COLORBTN_H_

#include <afxtempl.h>

// Utility class for the dialog
class CColorBtnDlg : public CDialog
{
// Construction
public:
enum COLOR_DIALOG_CONSTANTS
   {
   MIN_WELL_WIDTH = 5,
   MIN_WELL_HEIGHT = 5,
   MIN_INNER_BORDER = 0,
   MAX_INNER_BORDER = 5,
   MIN_OUTER_BORDER = 0,
   MAX_OUTER_BORDER = 10,
   MIN_NUMCOLORWELLCOLS = 1,
   MAX_NUMCOLORWELLCOLS = 40
   };
	
   CButton *m_Parent;

   CArray<COLORREF, COLORREF&> m_Colors;
   COLORREF m_SelectedColor;
   
   CColorBtnDlg(CWnd* pParent = NULL);   // standard constructor
   ~CColorBtnDlg();
   
   short m_DialogWidth;
   short m_NumColorWellColumns;
   short m_ColorWellHeight;
   short m_OuterBorderThickness;
   short m_InnerBorderThickness;
   UINT  m_StartingButtonID;
   BOOL  m_IsotropicWells;

private:
   DLGTEMPLATE m_dlgTempl;
   HGLOBAL m_GlobalLock;

public:
// Dialog Data
	//{{AFX_DATA(CColorBtnDlg)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorBtnDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
   
	// Generated message map functions
	//{{AFX_MSG(CColorBtnDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG

	void OnColor(UINT id);    
   void EndDialog( int nResult );
   void CreateDialogFromTemplate();

	DECLARE_MESSAGE_MAP()

};



class CColorBtn : public CButton
{
// Construction
public:
   enum {
      RECTANGLE,
      ELLIPSE,
      TRIANGLE,
      HEX
      } shapes;

    CColorBtn();

    // The selected color,set this variable to initialize the 
    // button's color and read to see the results
   COLORREF m_CurrentColor;
   
   // Thse functions pass values through to Dialog (m_ColorDlg)
   void ClearColorWells();
   void AddColorWell(COLORREF Color);
   void SetColorsFromArray(CArray<COLORREF, COLORREF&>* ColorArray);
   void SetBorderThickness(short Outer, short Inner);
   void SetDialogWidth(short Width);
   void SetNumColorWellColumns(short NumCols);
   void SetColorWellHeight(short Height);
   void MakeColorWellsIsotropic(BOOL Yes = TRUE);
   void SetColorWellShape(short Shape);
   short GetColorWellShape();



    // Use Serialize to store the color table in a file. Call at the document's Serialize()  
	static void Serialize( CArchive& ar );
   
   void SetSelectedColor(COLORREF Color);  
   COLORREF GetColor();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorBtn)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CColorBtn();

	// Generated message map functions
protected:
	//{{AFX_MSG(CColorBtn)
	afx_msg void OnClicked();
	//}}AFX_MSG

    void DrawItem(LPDRAWITEMSTRUCT);

	DECLARE_MESSAGE_MAP()

private:

    // A number of pens and brushes needed to paint the button

    CPen *m_OldPen;
    CBrush *m_OldBrush;
    CPen m_BlackPen;
    CPen m_DkGrayPen;
    CPen m_WhitePen;
    CBrush m_BackBrush;
    CBrush m_NullBrush;
    CPen m_NullPen;

    CColorBtnDlg m_ColorDlg;
    short m_ColorWellShape;
};




#endif

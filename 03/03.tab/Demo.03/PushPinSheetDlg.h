#include "pushpinFrame.h"


class CPushPinSheetDlg : public CDialog
{
public:
	CPushPinSheetDlg(CWnd* pParent = NULL);	// standard constructor

protected:
	//{{AFX_DATA(CPushPinSheetDlg)
	enum { IDD = IDD_PUSHPINSHEET_DIALOG };
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CPushPinSheetDlg)
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

  void OnProperties();

	//{{AFX_MSG(CPushPinSheetDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	HICON m_hIcon;
	CPushPinFrame* m_pPropFrame;
};


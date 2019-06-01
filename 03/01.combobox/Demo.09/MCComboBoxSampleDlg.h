// MCComboBoxSampleDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMCComboBoxSampleDlg dialog
#include "MultiColumnComboBox.h"

class CMCComboBoxSampleDlg : public CDialog
{
// Construction
public:
	CMCComboBoxSampleDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMCComboBoxSampleDlg)
	enum { IDD = IDD_MCCOMBOBOXSAMPLE_DIALOG };
	CMultiColumnComboBox	m_ComboBoxControl4;
	CMultiColumnComboBox	m_ComboBoxControl3;
	CMultiColumnComboBox	m_ComboBoxControl2;
	CMultiColumnComboBox	m_ComboBoxControl1;
	CString	m_ComboBoxString1;
	CString	m_ComboBoxString2;
	CString	m_ComboBoxString3;
	CString	m_ComboBoxString4;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMCComboBoxSampleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMCComboBoxSampleDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnEnableddisabled();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

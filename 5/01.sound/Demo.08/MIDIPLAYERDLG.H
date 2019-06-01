// MidiPlayerDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMidiPlayerDlg dialog

#include "Sequencer.h"
#include "Hyperlink.h"

class CMidiPlayerDlg : public CDialog
{
// Construction
public:
	CMidiPlayerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMidiPlayerDlg)
	enum { IDD = IDD_MIDIPLAYER_DIALOG };
	CButton	m_btnStop;
	CButton	m_btnPlay;
	CProgressCtrl	m_ProgressBar;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMidiPlayerDlg)
	public:
	virtual int DoModal();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMidiPlayerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnFileOpen();
	afx_msg void OnPlay();
	afx_msg void OnStop();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClose();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	afx_msg LONG OnMciNotify(UINT wFlags, LONG lDevId);

	CSequencer m_Sequencer;
};

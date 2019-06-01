// MidiSampleDlg.h : header file
//

#if !defined(AFX_MIDISAMPLEDLG_H__AD8DF4A5_587E_11D2_A78C_000000000000__INCLUDED_)
#define AFX_MIDISAMPLEDLG_H__AD8DF4A5_587E_11D2_A78C_000000000000__INCLUDED_

#include "MIDI.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMidiSampleDlg;

extern UINT		RWM_POSITIONCHANGED;	// a registered message
extern UINT		RWM_PLAYEDOFF;

class CMyMidi : public CMIDI {
	CMidiSampleDlg * m_pDlg;
	public:
		void	SetOwner(CMidiSampleDlg * pDlg) {
					m_pDlg = pDlg;
				}
	protected:
			// called when the specified system-exclusive or stream buffer
			// has been played and is being returned to the application
			// We use this method to get the current buffer position.
			// The implementation of this method is at the end of this
			// header file.
		inline virtual void	OnMidiOutDone(MIDIHDR & hdr);

		inline virtual void OnMidiOutClose();
};

/////////////////////////////////////////////////////////////////////////////
// CMidiSampleDlg dialog

class CMidiSampleDlg : public CDialog
{
// Construction
public:
	CMidiSampleDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMidiSampleDlg)
	enum { IDD = IDD_MIDISAMPLE_DIALOG };
	CSliderCtrl	m_ctrlTempo;
	CSliderCtrl	m_ctrlVolume;
	CButton	m_ctrlStop;
	CButton	m_ctrlPlay;
	CButton	m_ctrlPause;
	int		m_nVolume;
	CString	m_strPosition;
	int		m_nTempo;
	CString	m_strTempo;
	CString	m_strVolume;
	BOOL	m_bInfinite;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMidiSampleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CMyMidi m_midiMusic;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMidiSampleDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnPlay();
	afx_msg void OnStop();
	afx_msg void OnPause();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLoop();
	//}}AFX_MSG

	// The responder to the RWM_POSITIONCHANGED registered message
	afx_msg LONG	OnSetPosition(WPARAM, LPARAM);
	afx_msg LONG	OnPlayedOff(WPARAM, LPARAM);

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.


inline void	CMyMidi::OnMidiOutDone(MIDIHDR & hdr) {
	// Always call base method !
	CMIDI::OnMidiOutDone(hdr);
	ASSERT(m_pDlg != 0);
	m_pDlg->PostMessage(RWM_POSITIONCHANGED, WPARAM(m_dwProgressBytes));
}

inline void CMyMidi::OnMidiOutClose() {
	// Always call base method!
	CMIDI::OnMidiOutClose();
	ASSERT(m_pDlg != 0);
	m_pDlg->PostMessage(RWM_PLAYEDOFF);
}

#endif // !defined(AFX_MIDISAMPLEDLG_H__AD8DF4A5_587E_11D2_A78C_000000000000__INCLUDED_)

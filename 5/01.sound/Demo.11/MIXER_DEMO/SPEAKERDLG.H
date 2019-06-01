//=============================================================================
// Copyright Langis Pitre 1998
// You may do whatever you want with this code, as long as you include this
// copyright notice in your implementation files.
//
// If you wish to add new classes to this collection, feel free to do so.
// But please send me your code so that I can update the collection.
//
// Comments and bug reports: lpitre@sympatico.ca
//
//=============================================================================
// SpeakerDlg.h : header file
//

#if !defined(AFX_SPEAKERDLG_H__B000D3C7_0897_11D2_A16F_000000000000__INCLUDED_)
#define AFX_SPEAKERDLG_H__B000D3C7_0897_11D2_A16F_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "MixerClasses.h"

//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
//
// This class implements the controls for the speakers' destination line
// If you look at the class declaration, you'll see that it only has
// variable declarations and two methods. This is all it takes to have
// working mixer controls; control initialization is done in OnInitDialog().
//
//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
class CSpeakerDlg : public CDialog
//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
{
public:
	CSpeakerDlg();

	//{{AFX_DATA(CSpeakerDlg)
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CSpeakerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

protected:

	CMixerFader	m_mainVolume;
	CMixerFader  m_mainLeft;
	CMixerFader  m_mainRight;
	CMixerFader  m_mainBalance;
	CMixerFader	 m_mainBass;
	CMixerFader	 m_mainTreble;
	CMixerNumber m_mainGain;
	CMixerSwitch m_mainEnhance;

	CMixerFader	 m_cdVolume;
	CMixerFader	 m_cdBalance;
	CMixerFader	 m_waveVolume;
	CMixerFader	 m_waveBalance;
	CMixerFader	 m_synthVolume;
	CMixerFader	 m_synthBalance;
	CMixerFader	 m_auxVolume;
	CMixerFader	 m_auxBalance;
	CMixerFader	 m_mikeVolume;
	CMixerFader	 m_mikeBalance;
	CMixerFader	 m_pcVolume;
	CMixerFader	 m_pcBalance;

	CMixerSwitch m_mainMute;
	CMixerSwitch m_cdMute;
	CMixerSwitch m_waveMute;
	CMixerSwitch m_synthMute;
	CMixerSwitch m_auxMute;
	CMixerSwitch m_mikeMute;
	CMixerSwitch m_pcMute;

	CMixerPeakMeter m_peakMeter;

	//{{AFX_MSG(CSpeakerDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPEAKERDLG_H__B000D3C7_0897_11D2_A16F_000000000000__INCLUDED_)

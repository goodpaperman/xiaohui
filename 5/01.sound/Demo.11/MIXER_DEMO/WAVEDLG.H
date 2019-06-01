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
#if !defined(AFX_WAVEDLG_H__225A02B2_3466_11D2_A1BA_000000000000__INCLUDED_)
#define AFX_WAVEDLG_H__225A02B2_3466_11D2_A1BA_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "MixerClasses.h"

//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
//
// This class implements the controls for the recording (wave-in) destination
// line. If you look at the class declaration, you'll see that it only has
// variable declarations and one method. This is all it takes to have
// working mixer controls; control initialization is done in OnInitDialog().
//
//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
class CWaveDlg : public CDialog
//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
{
public:
	CWaveDlg();

	//{{AFX_DATA(CWaveDlg)
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CWaveDlg)
	//}}AFX_VIRTUAL

protected:
	
	CMixerNumber    m_mainGain;
	CMixerPeakMeter m_peakMeter;
	
	CMixerSwitch  m_cdSelect;
	CMixerSwitch  m_synthSelect;
	CMixerSwitch  m_auxSelect;
	CMixerSwitch  m_mikeSelect;

	CMixerFader	m_cdVolume;
	CMixerFader	m_cdBalance;
	CMixerFader	m_synthVolume;
	CMixerFader	m_synthBalance;
	CMixerFader	m_auxVolume;
	CMixerFader	m_auxBalance;
	CMixerFader	m_mikeVolume;
	CMixerFader	m_mikeBalance;
	CMixerSwitch m_mikeGain;


	//{{AFX_MSG(CWaveDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WAVEDLG_H__225A02B2_3466_11D2_A1BA_000000000000__INCLUDED_)

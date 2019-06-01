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
// WaveDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MixerControls.h"
#include "WaveDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif




//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
// Name   : CWaveDlg
//          
// Descr. : Class constructor. Note that in order to create a modeless dialog,
//          I have modified the constructor provided by Class Wizard so
//          that it calls the protected form of CDialog's constructor.
//          
//-----------------------------------------------------------------------------
CWaveDlg::CWaveDlg() : CDialog()
{
	//{{AFX_DATA_INIT(CWaveDlg)
	//}}AFX_DATA_INIT
}

BEGIN_MESSAGE_MAP(CWaveDlg, CDialog)
	//{{AFX_MSG_MAP(CWaveDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
// Name   : OnInitDialog
//          
// Descr. : After CDialog::OnInitDialog(), all the controls are subclassed and
//          initialized.
//          
// Return : BOOL
//-----------------------------------------------------------------------------
BOOL CWaveDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_mainGain.SubclassDlgItem( IDC_GAIN_SPIN, this );
	m_mainGain.Init( MIXERLINE_COMPONENTTYPE_DST_WAVEIN,
	                 NO_SOURCE,
	                 MIXERCONTROL_CONTROLTYPE_UNSIGNED );

	m_peakMeter.SubclassDlgItem( IDC_PEAK_STATIC, this );
	m_peakMeter.Init( MIXERLINE_COMPONENTTYPE_DST_WAVEIN, NO_SOURCE );
	
	m_synthSelect.SubclassDlgItem( IDC_SYNTH_SELECT, this );
	m_synthSelect.Init( MIXERLINE_COMPONENTTYPE_DST_WAVEIN,
	                 NO_SOURCE,
	                 MIXERCONTROL_CONTROLTYPE_MIXER, 0 );

	m_cdSelect.SubclassDlgItem( IDC_CD_SELECT, this );
	m_cdSelect.Init( MIXERLINE_COMPONENTTYPE_DST_WAVEIN,
	                 NO_SOURCE,
	                 MIXERCONTROL_CONTROLTYPE_MIXER, 1 );

	m_auxSelect.SubclassDlgItem( IDC_LINEIN_SELECT, this );
	m_auxSelect.Init( MIXERLINE_COMPONENTTYPE_DST_WAVEIN,
	                 NO_SOURCE,
	                 MIXERCONTROL_CONTROLTYPE_MIXER, 2 );

	m_mikeSelect.SubclassDlgItem( IDC_MIKE_SELECT, this );
	m_mikeSelect.Init( MIXERLINE_COMPONENTTYPE_DST_WAVEIN,
	                 NO_SOURCE,
	                 MIXERCONTROL_CONTROLTYPE_MIXER, 3 );

		
	m_cdVolume.SubclassDlgItem( IDC_CD_VOLUME, this );
	m_cdVolume.Init( MIXERLINE_COMPONENTTYPE_DST_WAVEIN,
	                 MIXERLINE_COMPONENTTYPE_SRC_COMPACTDISC,
	                 MIXERCONTROL_CONTROLTYPE_VOLUME,
					 CMixerFader::MAIN );
	
	m_cdBalance.SubclassDlgItem( IDC_CD_BALANCE, this );
	m_cdBalance.Init( MIXERLINE_COMPONENTTYPE_DST_WAVEIN,
	                  MIXERLINE_COMPONENTTYPE_SRC_COMPACTDISC,
	                  MIXERCONTROL_CONTROLTYPE_VOLUME, 
					  CMixerFader::BALANCE );
		
	m_synthVolume.SubclassDlgItem( IDC_SYNTH_VOLUME, this );
	m_synthVolume.Init( MIXERLINE_COMPONENTTYPE_DST_WAVEIN,
	                    MIXERLINE_COMPONENTTYPE_SRC_SYNTHESIZER,
						MIXERCONTROL_CONTROLTYPE_VOLUME, 
						CMixerFader::MAIN );	
	
	m_synthBalance.SubclassDlgItem( IDC_SYNTH_BALANCE, this );
	m_synthBalance.Init( MIXERLINE_COMPONENTTYPE_DST_WAVEIN,
	                     MIXERLINE_COMPONENTTYPE_SRC_SYNTHESIZER,
						 MIXERCONTROL_CONTROLTYPE_VOLUME, 
						 CMixerFader::BALANCE );
	
	m_auxVolume.SubclassDlgItem( IDC_AUX_VOLUME, this );
	m_auxVolume.Init( MIXERLINE_COMPONENTTYPE_DST_WAVEIN,
	                  MIXERLINE_COMPONENTTYPE_SRC_LINE,
					  MIXERCONTROL_CONTROLTYPE_VOLUME, 
					  CMixerFader::MAIN );	
	
	m_auxBalance.SubclassDlgItem( IDC_AUX_BALANCE, this );
	m_auxBalance.Init( MIXERLINE_COMPONENTTYPE_DST_WAVEIN,
	                   MIXERLINE_COMPONENTTYPE_SRC_LINE,
					   MIXERCONTROL_CONTROLTYPE_VOLUME, 
					   CMixerFader::BALANCE );
	
	m_mikeVolume.SubclassDlgItem( IDC_MIKE_VOLUME, this );
	m_mikeVolume.Init( MIXERLINE_COMPONENTTYPE_DST_WAVEIN,
	                   MIXERLINE_COMPONENTTYPE_SRC_MICROPHONE,
					   MIXERCONTROL_CONTROLTYPE_VOLUME, 
					   CMixerFader::MAIN );	
					
	m_mikeBalance.SubclassDlgItem( IDC_MIKE_BALANCE, this );
	m_mikeBalance.Init( MIXERLINE_COMPONENTTYPE_DST_WAVEIN,
	                    MIXERLINE_COMPONENTTYPE_SRC_MICROPHONE,
						MIXERCONTROL_CONTROLTYPE_VOLUME, 
						CMixerFader::BALANCE );

	m_mikeGain.SubclassDlgItem( IDC_MIKE_GAIN, this );
	m_mikeGain.Init( MIXERLINE_COMPONENTTYPE_DST_WAVEIN,
	                 MIXERLINE_COMPONENTTYPE_SRC_MICROPHONE,
	                 MIXERCONTROL_CONTROLTYPE_ONOFF, 0 );	
	

	GetDlgItem(IDC_GAIN_STATIC)->SetWindowText(  m_mainGain.GetLineShortName() );
	GetDlgItem(IDC_NAME_STATIC)->SetWindowText(  m_mainGain.GetLineName() );
	GetDlgItem(IDC_INPUT_STATIC)->SetWindowText( m_auxSelect.GetControlName() );

	GetDlgItem(IDC_SYNTH_STATIC)->SetWindowText(  m_synthVolume.GetLineShortName() );
	GetDlgItem(IDC_LINEIN_STATIC)->SetWindowText( m_auxVolume.GetLineShortName() );
	GetDlgItem(IDC_MIKE_STATIC)->SetWindowText(   m_mikeVolume.GetLineShortName() );
	GetDlgItem(IDC_CD_STATIC)->SetWindowText(     m_cdVolume.GetLineShortName() );
	
	return TRUE;
}
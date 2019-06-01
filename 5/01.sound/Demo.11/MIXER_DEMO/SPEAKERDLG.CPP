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
// SpeakerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MixerControls.h"
#include "SpeakerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
// Name   : CSpeakerDlg
//          
// Descr. : Class constructor. Note that in order to create a modeless dialog,
//          I have modified the constructor provided by Class Wizard so
//          that it calls the protected form of CDialog's constructor.
//          
//-----------------------------------------------------------------------------
CSpeakerDlg::CSpeakerDlg() : CDialog()
{
	//{{AFX_DATA_INIT( CSpeakerDlg )
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
}


//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
// Name   : DoDataExchange
//          
// Descr. : 
//          
// Return : void
// Arg    : CDataExchange* pDX : 
//-----------------------------------------------------------------------------
void CSpeakerDlg::DoDataExchange( CDataExchange* pDX )
{
	CDialog::DoDataExchange( pDX );
	//{{AFX_DATA_MAP( CSpeakerDlg )
	DDX_Control( pDX, IDC_MAIN_VOLUME,   m_mainVolume );
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP( CSpeakerDlg, CDialog )
	//{{AFX_MSG_MAP( CSpeakerDlg )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
// Name   : OnInitDialog
//          
// Descr. : After calling CDialog::OnInitDialog(), all the controls are
//          subclassed and initialized.
//          
// Return : BOOL
//-----------------------------------------------------------------------------
BOOL CSpeakerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Init the controls. all these controls must be either subclassed or
	// use DDE to work. For example, m_mainVolume is not subclassed since
	// it's been associated with the resource slider in DoDataExchange().

	m_mainVolume.Init( MIXERLINE_COMPONENTTYPE_DST_SPEAKERS,
	                   NO_SOURCE,
	                   MIXERCONTROL_CONTROLTYPE_VOLUME, 
					   CMixerFader::MAIN );

	m_mainBalance.SubclassDlgItem( IDC_MAIN_BALANCE, this );
	m_mainBalance.Init( MIXERLINE_COMPONENTTYPE_DST_SPEAKERS,
	                    NO_SOURCE,
	                    MIXERCONTROL_CONTROLTYPE_VOLUME, 
	                    CMixerFader::BALANCE );

	// I added these two sliders to demontrate how they work in conjunction
	// with the main and balance sliders
	m_mainLeft.SubclassDlgItem( IDC_MAIN_LEFT, this );
	m_mainLeft.Init( MIXERLINE_COMPONENTTYPE_DST_SPEAKERS,
	                    NO_SOURCE,
	                    MIXERCONTROL_CONTROLTYPE_VOLUME, 
	                    CMixerFader::LEFT );
	
	m_mainRight.SubclassDlgItem( IDC_MAIN_RIGHT, this );
	m_mainRight.Init( MIXERLINE_COMPONENTTYPE_DST_SPEAKERS,
	                    NO_SOURCE,
	                    MIXERCONTROL_CONTROLTYPE_VOLUME, 
	                    CMixerFader::RIGHT );


	m_mainBass.SubclassDlgItem( IDC_MAIN_BASS, this );
	m_mainBass.Init( MIXERLINE_COMPONENTTYPE_DST_SPEAKERS,
	                 NO_SOURCE,
	                 MIXERCONTROL_CONTROLTYPE_BASS, 
					 CMixerFader::MAIN );
	
	m_mainTreble.SubclassDlgItem( IDC_MAIN_TREBLE, this );
	m_mainTreble.Init( MIXERLINE_COMPONENTTYPE_DST_SPEAKERS,
	                   NO_SOURCE,
	                   MIXERCONTROL_CONTROLTYPE_TREBLE, 
					   CMixerFader::MAIN );
	
	m_mainGain.SubclassDlgItem( IDC_GAIN_SPIN, this );
	m_mainGain.Init( MIXERLINE_COMPONENTTYPE_DST_SPEAKERS,
	                 NO_SOURCE,
	                 MIXERCONTROL_CONTROLTYPE_UNSIGNED );

	m_mainEnhance.SubclassDlgItem( IDC_ENHANCE_CHECK, this );
	m_mainEnhance.Init( MIXERLINE_COMPONENTTYPE_DST_SPEAKERS,
	                    NO_SOURCE,
	                    MIXERCONTROL_CONTROLTYPE_ONOFF, 0 );	
	
	m_cdVolume.SubclassDlgItem( IDC_CD_VOLUME, this );
	m_cdVolume.Init( MIXERLINE_COMPONENTTYPE_DST_SPEAKERS,
	                 MIXERLINE_COMPONENTTYPE_SRC_COMPACTDISC,
	                 MIXERCONTROL_CONTROLTYPE_VOLUME,
					 CMixerFader::MAIN );
	
	m_cdBalance.SubclassDlgItem( IDC_CD_BALANCE, this );
	m_cdBalance.Init( MIXERLINE_COMPONENTTYPE_DST_SPEAKERS,
	                  MIXERLINE_COMPONENTTYPE_SRC_COMPACTDISC,
	                  MIXERCONTROL_CONTROLTYPE_VOLUME, 
					  CMixerFader::BALANCE );
	
	m_waveVolume.SubclassDlgItem( IDC_WAVE_VOLUME, this );
	m_waveVolume.Init( MIXERLINE_COMPONENTTYPE_DST_SPEAKERS,
	                   MIXERLINE_COMPONENTTYPE_SRC_WAVEOUT,
					   MIXERCONTROL_CONTROLTYPE_VOLUME, 
					   CMixerFader::MAIN );	
	
	m_waveBalance.SubclassDlgItem( IDC_WAVE_BALANCE, this );
	m_waveBalance.Init( MIXERLINE_COMPONENTTYPE_DST_SPEAKERS,
	                    MIXERLINE_COMPONENTTYPE_SRC_WAVEOUT,
						MIXERCONTROL_CONTROLTYPE_VOLUME, 
						CMixerFader::BALANCE );
	
	// there is a peak meter associated with my wave out
	// audio line. let's create one
	
	m_peakMeter.SubclassDlgItem( IDC_PEAK_STATIC, this );
	m_peakMeter.Init( MIXERLINE_COMPONENTTYPE_DST_SPEAKERS,
	                  MIXERLINE_COMPONENTTYPE_SRC_WAVEOUT );
	
	m_synthVolume.SubclassDlgItem( IDC_SYNTH_VOLUME, this );
	m_synthVolume.Init( MIXERLINE_COMPONENTTYPE_DST_SPEAKERS,
	                    MIXERLINE_COMPONENTTYPE_SRC_SYNTHESIZER,
						MIXERCONTROL_CONTROLTYPE_VOLUME, 
						CMixerFader::MAIN );	
	
	m_synthBalance.SubclassDlgItem( IDC_SYNTH_BALANCE, this );
	m_synthBalance.Init( MIXERLINE_COMPONENTTYPE_DST_SPEAKERS,
	                     MIXERLINE_COMPONENTTYPE_SRC_SYNTHESIZER,
						 MIXERCONTROL_CONTROLTYPE_VOLUME, 
						 CMixerFader::BALANCE );
	
	m_auxVolume.SubclassDlgItem( IDC_AUX_VOLUME, this );
	m_auxVolume.Init( MIXERLINE_COMPONENTTYPE_DST_SPEAKERS,
	                  MIXERLINE_COMPONENTTYPE_SRC_LINE,
					  MIXERCONTROL_CONTROLTYPE_VOLUME, 
					  CMixerFader::MAIN );	
	
	m_auxBalance.SubclassDlgItem( IDC_AUX_BALANCE, this );
	m_auxBalance.Init( MIXERLINE_COMPONENTTYPE_DST_SPEAKERS,
	                   MIXERLINE_COMPONENTTYPE_SRC_LINE,
					   MIXERCONTROL_CONTROLTYPE_VOLUME, 
					   CMixerFader::BALANCE );
	
	m_mikeVolume.SubclassDlgItem( IDC_MIKE_VOLUME, this );
	m_mikeVolume.Init( MIXERLINE_COMPONENTTYPE_DST_SPEAKERS,
	                   MIXERLINE_COMPONENTTYPE_SRC_MICROPHONE,
					   MIXERCONTROL_CONTROLTYPE_VOLUME, 
					   CMixerFader::MAIN );	
	
	m_mikeBalance.SubclassDlgItem( IDC_MIKE_BALANCE, this );
	m_mikeBalance.Init( MIXERLINE_COMPONENTTYPE_DST_SPEAKERS,
	                    MIXERLINE_COMPONENTTYPE_SRC_MICROPHONE,
						MIXERCONTROL_CONTROLTYPE_VOLUME, 
						CMixerFader::BALANCE );	

	m_pcVolume.SubclassDlgItem( IDC_PC_VOLUME, this );
	m_pcVolume.Init( MIXERLINE_COMPONENTTYPE_DST_SPEAKERS,
	                   MIXERLINE_COMPONENTTYPE_SRC_PCSPEAKER,
					   MIXERCONTROL_CONTROLTYPE_VOLUME, 
					   CMixerFader::MAIN );	
	
	m_pcBalance.SubclassDlgItem( IDC_PC_BALANCE, this );
	m_pcBalance.Init( MIXERLINE_COMPONENTTYPE_DST_SPEAKERS,
	                    MIXERLINE_COMPONENTTYPE_SRC_PCSPEAKER,
						MIXERCONTROL_CONTROLTYPE_VOLUME, 
						CMixerFader::BALANCE );
				
	// init all mute controls

	m_mainMute.SubclassDlgItem( IDC_MAIN_MUTE, this );
	m_mainMute.Init( MIXERLINE_COMPONENTTYPE_DST_SPEAKERS,
	                 NO_SOURCE,
	                 MIXERCONTROL_CONTROLTYPE_MUTE, 0 );	
	
	m_cdMute.SubclassDlgItem( IDC_CD_MUTE, this );
	m_cdMute.Init( MIXERLINE_COMPONENTTYPE_DST_SPEAKERS,
	               MIXERLINE_COMPONENTTYPE_SRC_COMPACTDISC,
				   MIXERCONTROL_CONTROLTYPE_MUTE, 0 );	
	
	m_waveMute.SubclassDlgItem( IDC_WAVE_MUTE, this );
	m_waveMute.Init( MIXERLINE_COMPONENTTYPE_DST_SPEAKERS,
	                 MIXERLINE_COMPONENTTYPE_SRC_WAVEOUT,
					 MIXERCONTROL_CONTROLTYPE_MUTE, 0 );	
	
	m_synthMute.SubclassDlgItem( IDC_SYNTH_MUTE, this );
	m_synthMute.Init( MIXERLINE_COMPONENTTYPE_DST_SPEAKERS,
	                  MIXERLINE_COMPONENTTYPE_SRC_SYNTHESIZER,
	                  MIXERCONTROL_CONTROLTYPE_MUTE, 0 );	
	
	m_auxMute.SubclassDlgItem( IDC_AUX_MUTE, this );
	m_auxMute.Init( MIXERLINE_COMPONENTTYPE_DST_SPEAKERS,
	                MIXERLINE_COMPONENTTYPE_SRC_LINE,
	                MIXERCONTROL_CONTROLTYPE_MUTE, 0 );	
	
	m_mikeMute.SubclassDlgItem( IDC_MIKE_MUTE, this );
	m_mikeMute.Init( MIXERLINE_COMPONENTTYPE_DST_SPEAKERS,
	                 MIXERLINE_COMPONENTTYPE_SRC_MICROPHONE,
	                 MIXERCONTROL_CONTROLTYPE_MUTE, 0 );	
	
	m_pcMute.SubclassDlgItem( IDC_PC_MUTE, this );
	m_pcMute.Init( MIXERLINE_COMPONENTTYPE_DST_SPEAKERS,
	                 MIXERLINE_COMPONENTTYPE_SRC_PCSPEAKER,
	                 MIXERCONTROL_CONTROLTYPE_MUTE, 0 );	
			
	// any CMixerBase-derived class can retrieve the long and short names of
	// the associated mixer control and mixer line
	GetDlgItem(IDC_MAIN_STATIC)->SetWindowText(   m_mainVolume.GetLineShortName() );
	GetDlgItem(IDC_NAME_STATIC)->SetWindowText(   m_mainVolume.GetLineName() );
	GetDlgItem(IDC_ENHANCE_CHECK)->SetWindowText( m_mainEnhance.GetControlName() );

	GetDlgItem(IDC_GAIN_STATIC)->SetWindowText(   m_mainGain.GetControlShortName() );
	GetDlgItem(IDC_BASS_STATIC)->SetWindowText(   m_mainBass.GetControlShortName() );
	GetDlgItem(IDC_TREBLE_STATIC)->SetWindowText( m_mainTreble.GetControlShortName() );
	GetDlgItem(IDC_WAVE_STATIC)->SetWindowText(   m_waveVolume.GetLineName() );
	GetDlgItem(IDC_SYNTH_STATIC)->SetWindowText(  m_synthVolume.GetLineName() );
	GetDlgItem(IDC_LINEIN_STATIC)->SetWindowText( m_auxVolume.GetLineName() );
	GetDlgItem(IDC_MIKE_STATIC)->SetWindowText(   m_mikeVolume.GetLineName() );
	GetDlgItem(IDC_CD_STATIC)->SetWindowText(     m_cdVolume.GetLineName() );
	GetDlgItem(IDC_PC_STATIC)->SetWindowText(     m_pcVolume.GetLineName() );
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}


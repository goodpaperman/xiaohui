// Sound.h: interface for the CSoundIn class.
//
//////////////////////////////////////////////////////////////////////
/*
   
	    This program is Copyright  Developped by Yannick Sustrac
                   yannstrc@mail.dotcom.fr
		        http://www.mygale.org/~yannstrc/
 

This program is free software; you can redistribute it and/or modify it under the terms
of the GNU General Public License as published by the Free Software Foundation; either
version 2 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program;
if not, write to the Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

*/
//////////////////////////////////////////////////////////////////////////////////////////    


#if !defined(AFX_SOUND_H__69C928C4_1F19_11D2_8045_30460BC10000__INCLUDED_)
#define AFX_SOUND_H__69C928C4_1F19_11D2_8045_30460BC10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <mmsystem.h>

#define MAX_SAMPLES 8192   //>>>>>>>> must also be defined in CFft
#define MAX_VOIE 2
#define MAX_SIZE_SAMPLES  1  // WORD
#define MAX_SIZE_INPUT_BUFFER   MAX_SAMPLES*MAX_VOIE*MAX_SIZE_SAMPLES 
#define DEFAULT_CAL_OFFSET -395 // >>>>> depends of you sound card
#define DEFAULT_CAL_GAIN   1.0


class CSoundIn  
{
public:

	// used for int FFT
	SHORT  InputBuffer[MAX_SIZE_INPUT_BUFFER];

	WAVEINCAPS		m_WaveInDevCaps;
    HWAVEIN			m_WaveIn;
	WAVEHDR			m_WaveHeader;
    WAVEFORMATEX	m_WaveFormat;
	
	short m_CalOffset;
	double m_CalGain;


	HANDLE m_WaveInEvent;
	CWinThread * m_WaveInThread;
	BOOL m_TerminateThread;

	UINT m_WaveInSampleRate;
	int m_NbMaxSamples;
	UINT m_SizeRecord;
	WORD 	m_Toggle; /*0 or 1 according the buffer currently loaded*/

public :	
	void StartMic();
	void StopMic();
	void CloseMic();
	void AddBuffer();

public :
	virtual void RazBuffers();
    virtual void ComputeSamples(SHORT *);  // calibrate the samples for the basse class 
											// this function is overloaded by the parent
											// it need to call this function first to calibrate them



//////////////////////////////////////////////////////
// functions members
	MMRESULT OpenMic();
	void WaveInitFormat(   WORD    nCh, // number of channels (mono, stereo)
							DWORD   nSampleRate, // sample rate
							WORD    BitsPerSample);
	//void CALLBACK waveInProc( HWAVEIN hwi,  UINT uMsg,   DWORD dwInstance,   DWORD dwParam1, DWORD dwParam2 );
	
	CSoundIn();
	virtual ~CSoundIn();

};

// global Thread procedure 
	UINT WaveInThreadProc( LPVOID pParam);

#endif
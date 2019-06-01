// SoundOut.h: interface for the CSound class.
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

#if !defined(AFX_SOUNDOUT_H__69C928C4_1F19_11D2_8045_30460BC10000__INCLUDED_)
#define AFX_SOUNDOUT_H__69C928C4_1F19_11D2_8045_30460BC10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <mmsystem.h>

#define MAX_OUTPUT_SAMPLES 100000   
#define MAX_VOIE 2
#define MAX_SIZE_SAMPLES  1  // WORD
#define MAX_SIZE_OUTPUT_BUFFER   MAX_OUTPUT_SAMPLES*MAX_VOIE*MAX_SIZE_SAMPLES 


class CSoundOut  
{
public:

	SHORT  OutputBuffer[MAX_SIZE_OUTPUT_BUFFER];

	WAVEOUTCAPS		m_WaveOutDevCaps;
    HWAVEOUT		m_WaveOut;
	WAVEHDR			m_WaveHeader;
    WAVEFORMATEX	m_WaveFormat;
	


	HANDLE m_WaveOutEvent;
	CWinThread * m_WaveOutThread;
	BOOL m_TerminateThread;

	UINT m_WaveOutSampleRate;
	int  m_NbMaxSamples;
	UINT m_SizeRecord;


//////////////////////////////////////////////////////
// functions members

public :	
	void StartOutput();
	void StopOutput();
	void CloseOutput();
	void AddBuffer();

public :
	virtual void RazBuffers();
    virtual void ComputeSamples(SHORT *);  
	

	MMRESULT OpenOutput();
	void WaveInitFormat(    WORD    nCh,		 // number of channels (mono, stereo)
							DWORD   nSampleRate, // sample rate
							WORD    BitsPerSample);
	
	CSoundOut();
	virtual ~CSoundOut();

};

// Unique global Thread procedure  for the sound Output
	UINT WaveOutThreadProc( LPVOID pParam);

#endif
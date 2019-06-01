// Sound.cpp: implementation of the CSoundIn class.
//
/////////////////////////////////////////////////////////////////////////////////////////
/*
   
	    This program is Copyright  Developped by Yannick Sustrac
                   yannstrc@mail.dotcom.fr
		        http://www.mygale.org/~yannstrc
 

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



#include "stdafx.h"
#include "SoundIn.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define real double

UINT WaveInThreadProc(void * pParam);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSoundIn::CSoundIn()
{
  m_NbMaxSamples = 2048;
  m_CalOffset = DEFAULT_CAL_OFFSET;
  m_CalGain = DEFAULT_CAL_GAIN;
  m_WaveInSampleRate = 11025;
}

CSoundIn::~CSoundIn()
{
	CloseMic();
}
///////////////////////////////////////////////////////////////////
MMRESULT CSoundIn::OpenMic()
{
     MMRESULT result;

    result=waveInGetNumDevs(); 
	if (result == 0)
	{
        AfxMessageBox("No Sound Device");
		return result;
	}

   // test for Mic available   
   result=waveInGetDevCaps (0, &m_WaveInDevCaps, sizeof(WAVEINCAPS));
   
   if ( result!= MMSYSERR_NOERROR)
   {
       AfxMessageBox(_T("Cannot determine sound card capabilities !"));
   }

	// The Sound Devive is OK now we can create an Event  and start the Thread
	m_WaveInEvent = CreateEvent(NULL,FALSE,FALSE,"WaveInThreadEvent");
	m_TerminateThread = FALSE;
	m_WaveInThread= AfxBeginThread(WaveInThreadProc,this,THREAD_PRIORITY_NORMAL,0,CREATE_SUSPENDED,NULL);   
	m_WaveInThread->m_bAutoDelete = TRUE;
	m_WaveInThread->ResumeThread();

	// init format 
	WaveInitFormat(1/* mono*/,m_WaveInSampleRate /* khz */,16 /* bits */); 

	
	// Open Input 
	result = waveInOpen( &m_WaveIn,0, &m_WaveFormat,(DWORD)m_WaveInEvent ,NULL ,CALLBACK_EVENT); 
	if ( result!= MMSYSERR_NOERROR)
	{
        AfxMessageBox(_T("Cannot Open Sound Input Device!"));
	    return result;
	}
  // prepare header
   /*
    typedef struct {     LPSTR  lpData;     
					 DWORD  dwBufferLength; 
					DWORD  dwBytesRecorded;  
					DWORD  dwUser; 
					DWORD  dwFlags; 
					DWORD  dwLoops;
					struct wavehdr_tag * lpNext;  
					DWORD  reserved; 
	} WAVEHDR; 
	*/
	m_SizeRecord = m_NbMaxSamples;
    m_WaveHeader.lpData = (CHAR *)&InputBuffer[0];
    m_WaveHeader.dwBufferLength = m_SizeRecord*2;
	m_WaveHeader.dwFlags = 0;

    result = waveInPrepareHeader( m_WaveIn, &m_WaveHeader, sizeof(WAVEHDR) ); 
   if ( (result!= MMSYSERR_NOERROR) || ( m_WaveHeader.dwFlags != WHDR_PREPARED) )
   {
        AfxMessageBox(_T("Cannot Prepare Header !"));
	    return result;
   }

   result = waveInAddBuffer( m_WaveIn, &m_WaveHeader, sizeof(WAVEHDR) );
   if  (result!= MMSYSERR_NOERROR) 
   {
        AfxMessageBox(_T("Cannot Add Buffer !"));
	    return result;
   }

   // all is correct now we can start the process
   result = waveInStart( m_WaveIn );
   if  (result!= MMSYSERR_NOERROR) 
   {
        AfxMessageBox(_T("Cannot Start Wave In !"));
	    return result;
   }
   return result;
}



void CSoundIn::AddBuffer()
{
	
    MMRESULT result;

    result = waveInUnprepareHeader( m_WaveIn, &m_WaveHeader, sizeof(WAVEHDR) ); 
   if  (result!= MMSYSERR_NOERROR) 
   {
        AfxMessageBox(_T("Cannot UnPrepareHeader !"));
        return;
   };
 	m_SizeRecord = m_NbMaxSamples;
    m_WaveHeader.lpData = (CHAR *)&InputBuffer[0];
    m_WaveHeader.dwBufferLength = m_SizeRecord *2;
	m_WaveHeader.dwFlags = 0;
    result = waveInPrepareHeader( m_WaveIn, &m_WaveHeader, sizeof(WAVEHDR) ); 
   if ( (result!= MMSYSERR_NOERROR) || ( m_WaveHeader.dwFlags != WHDR_PREPARED) )
        AfxMessageBox(_T("Cannot Prepare Header !"));

   result = waveInAddBuffer( m_WaveIn, &m_WaveHeader, sizeof(WAVEHDR) );
   if  (result!= MMSYSERR_NOERROR) 
        AfxMessageBox(_T("Cannot Add Buffer !"));

   result = waveInStart( m_WaveIn );
   if  (result!= MMSYSERR_NOERROR) 
        AfxMessageBox(_T("Cannot Start Wave In !"));
}

/*
WAVE_FORMAT_1M08  11.025 kHz, mono, 8-bit 
WAVE_FORMAT_1M16  11.025 kHz, mono, 16-bit 
WAVE_FORMAT_1S08  11.025 kHz, stereo, 8-bit 
WAVE_FORMAT_1S16  11.025 kHz, stereo, 16-bit 
WAVE_FORMAT_2M08  22.05 kHz, mono, 8-bit 
WAVE_FORMAT_2M16  22.05 kHz, mono, 16-bit 
WAVE_FORMAT_2S08  22.05 kHz, stereo, 8-bit 
WAVE_FORMAT_2S16  22.05 kHz, stereo, 16-bit 
WAVE_FORMAT_4M08  44.1 kHz, mono, 8-bit 
WAVE_FORMAT_4M16  44.1 kHz, mono, 16-bit 
WAVE_FORMAT_4S08  44.1 kHz, stereo, 8-bit 
WAVE_FORMAT_4S16  44.1 kHz, stereo, 16-bit 
*/ 

void CSoundIn:: WaveInitFormat(    WORD    nCh, // number of channels (mono, stereo)
								DWORD   nSampleRate, // sample rate
								WORD    BitsPerSample)
{
		m_WaveFormat.wFormatTag = WAVE_FORMAT_PCM;
		m_WaveFormat.nChannels = nCh;
		m_WaveFormat.nSamplesPerSec = nSampleRate;
		m_WaveFormat.nAvgBytesPerSec = nSampleRate * nCh * BitsPerSample/8;
		m_WaveFormat.nBlockAlign = m_WaveFormat.nChannels * BitsPerSample/8;
		m_WaveFormat.wBitsPerSample = BitsPerSample;
		m_WaveFormat.cbSize = 0;
}   


///////////////////////////////////////////////////////////////////////////
// the comutation for the input samples need to be calibrated according
// to the sound board  add an Offset and a Mult coef.

void CSoundIn::ComputeSamples(SHORT *pt)
{
	    int i;
		for ( i = 0 ; i<m_NbMaxSamples; i++) // scaling the input samples du to the sound card
		{
            //InputBuffer[i] += m_CalOffset;
            //InputBuffer[i] *=m_CalGain;
		}
}  


void CSoundIn::CloseMic()
{
	m_TerminateThread = TRUE;
    if (m_WaveInEvent )
		SetEvent(m_WaveInEvent);
    Sleep(50);  // wait for the thread to terminate

	if (m_WaveIn) 
		waveInStop(m_WaveIn);
    if (m_WaveIn) 
		waveInClose(m_WaveIn);
}

void CSoundIn::RazBuffers()
{
		for (int i=0;i<MAX_SAMPLES;i++)
		{
	        InputBuffer[i] = 0;
	        //InputBuffer[i] = 0;
		}
}

void CSoundIn::StopMic()
{
	waveInStop(m_WaveIn);
	waveInReset(m_WaveIn);
}

void CSoundIn::StartMic()
{
	waveInStart(m_WaveIn);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//    Glogal Thread procedure for the CSoundIn class
//    It cannot be included inside the Class
//   
// The LPARAM is the Class pointer (this) it can be the base class CSoundIn ptr or a derived new class
// The value of this parametre can change according the Topmost class of the process 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define PT_S ((CSoundIn*)pParam) 

UINT WaveInThreadProc(void * pParam)
{
   UINT result;
   UINT FirstPass = TRUE;

	if ( FirstPass)
		result = WaitForSingleObject(((CSoundIn*)pParam)->m_WaveInEvent,INFINITE);
	FirstPass = FALSE;
    
	while (!((CSoundIn*)pParam)->m_TerminateThread)
	{
		result = WaitForSingleObject(((CSoundIn*)pParam)->m_WaveInEvent,INFINITE);
		if ((result == WAIT_OBJECT_0)&&(!((CSoundIn*)pParam)->m_TerminateThread ))
		{
			PT_S->AddBuffer();      // Toggle as changed state here !Toggle point to the just received buffer
		    PT_S->ComputeSamples(PT_S->InputBuffer);
		}
		else
			return 0;  // 
	}
    return 0;
}


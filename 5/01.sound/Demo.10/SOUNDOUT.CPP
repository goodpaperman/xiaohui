// SoundOut.cpp: implementation of the CSoundOut class.
//
//////////////////////////////////////////////////////////////////////
/*
   
	    This program is Developped by Yannick Sustrac
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

#include "stdafx.h"
#include "math.h"
#include "snd.h"
#include "SoundOut.h"

#pragma comment(lib, "winmm")


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define real double
//void CALLBACK waveOutProc( HWAVEOut hwi,  UINT uMsg,   DWORD dwInstance,   DWORD dwParam1, DWORD dwParam2 );

UINT WaveOutThreadProc(void * pParam);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSoundOut::CSoundOut()
{
  int i;
  double k;
  m_NbMaxSamples = MAX_OUTPUT_SAMPLES;
  m_WaveOutSampleRate = 11025;

  /* init the sound Ouutput buffer with a signal noise */
  k =2.0*3.1416*(double)500.0/(double)m_WaveOutSampleRate;
  for (i = 0 ; i< m_NbMaxSamples; i++)
	   OutputBuffer[i] = (SHORT)(10000.0*sin(k*(double)i/*++*/)) ;
}

CSoundOut::~CSoundOut()
{
	CloseOutput();
}

///////////////////////////////////////////////////////////////////
MMRESULT CSoundOut::OpenOutput()
{
     MMRESULT result;

    result=waveOutGetNumDevs(); 
	if (result == 0)
	{
        AfxMessageBox("No Sound Output Device");
		return result;
	}

   // test for Mic available   
   result=waveOutGetDevCaps (0, &m_WaveOutDevCaps, sizeof(WAVEOUTCAPS));
   
   if ( result!= MMSYSERR_NOERROR)
   {
       AfxMessageBox(_T("Sound output Cannot determine card capabilities !"));
   }

	// The SoundOut Devive is OK now we can create an Event  and start the Thread
	m_WaveOutEvent = CreateEvent(NULL,FALSE,FALSE,"WaveOutThreadEvent");
	m_TerminateThread = FALSE;
	m_WaveOutThread= AfxBeginThread(WaveOutThreadProc,this,THREAD_PRIORITY_NORMAL,0,CREATE_SUSPENDED,NULL);   
	m_WaveOutThread->m_bAutoDelete = TRUE;
	m_WaveOutThread->ResumeThread();

	// init format 
	WaveInitFormat(1/* mono*/,m_WaveOutSampleRate /* khz */,16 /* bits */); 

	
	// Open Output 
	result = waveOutOpen( &m_WaveOut,0, &m_WaveFormat,(DWORD)m_WaveOutEvent ,NULL ,CALLBACK_EVENT); 
	if ( result!= MMSYSERR_NOERROR)
	{
        AfxMessageBox(_T("Sound output Cannot Open Device!"));
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
//	m_Toggle = FALSE;
	m_SizeRecord = m_NbMaxSamples;
    m_WaveHeader.lpData = (CHAR *)&OutputBuffer[0];
    m_WaveHeader.dwBufferLength = m_SizeRecord*2;
	m_WaveHeader.dwFlags = 0;

    result = waveOutPrepareHeader( m_WaveOut, &m_WaveHeader, sizeof(WAVEHDR) ); 
  //MMRESULT waveOutPrepareHeader( HWAVEOUT hwi, LPWAVEHDR pwh, UINT cbwh ); 
   if ( (result!= MMSYSERR_NOERROR) || ( m_WaveHeader.dwFlags != WHDR_PREPARED) )
   {
        AfxMessageBox(_T(" Sound Output Cannot Prepare Header !"));
	    return result;
   }

   result = waveOutWrite( m_WaveOut, &m_WaveHeader, sizeof(WAVEHDR) );
   if  (result!= MMSYSERR_NOERROR) 
   {
        AfxMessageBox(_T(" Sound Output Cannot Write Buffer !"));
	    return result;
   }

   // all is correct now we can start the process
   result = waveOutRestart( m_WaveOut );
   if  (result!= MMSYSERR_NOERROR) 
   {
        AfxMessageBox(_T(" Sound Output Cannot Start Wave Out !"));
	    return result;
   }
   return result;
}



void CSoundOut::AddBuffer()
{
	
    MMRESULT result;

    result = waveOutUnprepareHeader( m_WaveOut, &m_WaveHeader, sizeof(WAVEHDR) ); 
   if  (result!= MMSYSERR_NOERROR) 
   {
        //AfxMessageBox(_T("Sound output Cannot UnPrepareHeader !"));
        return;
   };
 	m_SizeRecord = m_NbMaxSamples;
    m_WaveHeader.lpData = (CHAR *)&OutputBuffer[0];
    m_WaveHeader.dwBufferLength = m_SizeRecord *2;
	m_WaveHeader.dwFlags = 0;
    result = waveOutPrepareHeader( m_WaveOut, &m_WaveHeader, sizeof(WAVEHDR) ); 
  //MMRESULT waveOutPrepareHeader( HWAVEOUT hwi, LPWAVEHDR pwh, UINT cbwh ); 
   if ( (result!= MMSYSERR_NOERROR) || ( m_WaveHeader.dwFlags != WHDR_PREPARED) )
        AfxMessageBox(_T("Sound output Cannot Prepare Header !"));

   result = waveOutWrite( m_WaveOut, &m_WaveHeader, sizeof(WAVEHDR) );
   if  (result!= MMSYSERR_NOERROR) 
        AfxMessageBox(_T("Sound output Cannot Add Buffer !"));

   result = waveOutRestart( m_WaveOut );
   if  (result!= MMSYSERR_NOERROR) 
        AfxMessageBox(_T(" Sound Output Cannot Start Wave Out !"));
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

void CSoundOut:: WaveInitFormat(    WORD    nCh, // number of channels (mono, stereo)
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
// the comutation for the Output samples need to be calibrated according
// to the SoundOut board  add an Offset and a Mult coef.

void CSoundOut::ComputeSamples(SHORT *pt)
{
}  


void CSoundOut::CloseOutput()
{
	if (m_WaveOut) 
		waveOutPause(m_WaveOut);
    Sleep(50);  // wait for the pause
	//	CloseHandle(m_WaveOut);
	m_TerminateThread = TRUE;
    if (m_WaveOutEvent )
		SetEvent(m_WaveOutEvent);
    Sleep(50);  // wait for the thread to terminate

   if (m_WaveOut) 
   {
		waveOutReset(m_WaveOut);
		waveOutClose(m_WaveOut);
   }
}

void CSoundOut::RazBuffers()
{
		for (int i=0;i<MAX_OUTPUT_SAMPLES;i++)
		{
	        OutputBuffer[i] = 0;
		}
}

void CSoundOut::StopOutput()
{
	waveOutPause(m_WaveOut);
}

void CSoundOut::StartOutput()
{
	waveOutRestart(m_WaveOut);
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//    Glogal Thread procedure for the CSoundOut class
//    It cannot be included inside the Class
//   
// The LPARAM is the Class pointer it can be the base class CSoundOut
// or a drived class like CFft 
// The value of this parametre can change according because 
//  OpenMic() call a virtual funtion 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define PT_S ((CSoundOut*)pParam) 

UINT WaveOutThreadProc(void * pParam)
{
//   CSoundOut * SoundOut = (class CSoundOut *)pParam;
   UINT result;
   UINT FirstPass = TRUE;


	if ( FirstPass)
		result = WaitForSingleObject(((CSoundOut*)pParam)->m_WaveOutEvent,INFINITE);
	FirstPass = FALSE;
    
	while (!((CSoundOut*)pParam)->m_TerminateThread)
	{
		result = WaitForSingleObject(((CSoundOut*)pParam)->m_WaveOutEvent,INFINITE);
		if ((result == WAIT_OBJECT_0)&&(!((CSoundOut*)pParam)->m_TerminateThread ))
		{
			PT_S->AddBuffer();      // Toggle as changed state here !Toggle point to the just received buffer
		    PT_S->ComputeSamples(PT_S->OutputBuffer);
		}
		else
			return 0;  // 
	}
    return 0;
}





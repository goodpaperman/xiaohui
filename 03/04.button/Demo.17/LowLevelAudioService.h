/*===============================================================
   Low-Level Wave 서비스를 이용한 wave 출력 입력 저장 클래스 헤더
================================================================*/

// LowLevelAudioService.h : interface of the CCtiChatView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(_LOW_LEVEL_AUDIO_SERVICE_H_)
#define _LOW_LEVEL_AUDIO_SERVICE_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#if !defined(_INC_MMSYSTEM)
	#include <mmsystem.h>
	#pragma message("Automatically Adding mmsystem.h ")
	#ifdef _AFXDLL
		#pragma comment(lib, "winmm.lib ")	
		#pragma message("Automatically linking with winmm.lib ")
	#endif
#endif

class CLowLevelAudioService
{
public:
   CLowLevelAudioService();
   ~CLowLevelAudioService();

   int erroCode;//에라 코드
   
	// wAllocMemory()
	// 내부 함수 데이터 크기만큼 메모리에 alloc시킨다.
   int wAllocMemory();

   // wFreeMemory()
   // 메모리를 해제한다.
   void wFreeMemory();
   
	// wSetWaveHeader()
   // 웨이브 디바이스에 보낼 헤더를 설정한다.
   // pWave는 음성 데이터가 적재되어 있는 메모리 포인터
   // lDatasize 음성 데이터의 크기
   void wSetWaveHeader();
  
	// LoadWaveFile(LPSTR filename)
   // 파일을 지정하면 지정한 파일에서 웨이브 파일을 읽고
   // 데이터는 pWave에, 데이터 크기는 lDatasize에 저장하고
   // 웨이브 디바이스에 보낼 헤더를 설정한다.
   int LoadWaveFile(LPSTR filename);
   
	// wOpenOutDevice()
   // 내부 함수 출력 디바이스를 연다.
   int wOpenOutDevice();
   
	// SetDataSize(int sec);  
   // 데이터 크기를 설정한다.
   // sec는 초단위
   // 본 함수는 레코딩할 때 몇 초로 할 것인지를 나타냄.
   void SetDataSize(int sec);
   
	
   // wOpenRecDevice() 
   // 녹음을 하기 위한 웨이브 디바이스를 연다.
   int wOpenRecDevice();
   
   // SetWaveInfo(int MonoStero,int Sampling,int BitSample)
   // 웨이브 파일을 녹음하기 위해서는 일단 정보가 필요하다.
	// 몇 비트로, 몇 kHz로, 모노인지 스테레오인지 등등을 설정해야 한다.
   void SetWaveInfo(int MonoStero,int Sampling,int BitSample);
   
	// OpenWaveDevice(int mode)
   // 웨이브 디바이스를 연다.
   // mode가 TRUE이면 출력하기 위해 열고
   // mode가 FALSE이면 레코딩하기 위해 연다.
   int OpenWaveDevice(int mode);
   
	// PlayWave()
   // 웨이브를 출력한다.
   // 출력시킬 경우 안에 디바이스를 여는 함수가 내장되어 있으므로
   // OpenWaveDevice 함수를 쓸 필요없다.
   int PlayWave();
   
	// Play()
   // 디바이스가 열린 상태에서 플레이 
   // 본 함수는 OpenWaveDevice가 미리 설정되어 있어야 한다.
   int Play();
   
	// PlayPause()
	// 현재 출력을 잠시 중단한다.
   int PlayPause();
   
	// wCloseOutDevice()
   // 출력 디바이스를 닫는다.
   int wCloseOutDevice();
   
	// StopRecord();
   // 레코드 하는 것을 멈춘다.
   int StopRecord();

   // wCloseRecDevice()
   // 레코드 디바이스를 닫는다.
   int wCloseRecDevice();
   
	// CloseWaveDevice(int mode)
   // 웨이브 디바이스를 닫는다.
   int CloseWaveDevice(int mode);
   
	// RecordWave()
   // 웨이브를 녹음한다. 
   // 디바이스를 열 필요없음.
   int RecordWave();
   
	// Record()
   // 웨이브를 녹음한다.
   // 디바이스 열 필요 있음.
   int Record();
   
	// DrawWave(CDC *pDC,CRect rect,COLORREF Color,int step,int pos);
   // rect로 설정한 박스에 천연의 색으로 웨이브 파장을 그려라! 
	// pos는 0.5초 단위의 위치, step은 몇 바이트씩 건너뛰면서 그릴 것인지 만약,
	// 1이면 1바이트, 1바이트 모두 그리기 때문에 파장은 진하고 그리는 속도는 느리다. 
	void DrawWave(CDC *pDC,CRect rect,COLORREF Color,int step,int pos);
   
	// Bit8Value(int num)
   // 8비트일 때 현재 바이트값을 정한다.
   int Bit8Value(int num);
   
	// Bit16Value(int num)
   // 16비트일 때 현재 바이트값을 정한다.
   int Bit16Value(int num);
   
	// Bit32Value(int num)
   // 32비트일 때 현재 바이트값을 정한다.
   int Bit32Value(int num);
   
	// SetWavePos(int point)
   // 웨이브의 위치를 변화시킨다.
   int SetWavePos(int point);
   
	// GetdwFlags()
   // 헤더에 dwFlags를 리턴한다.
   int GetdwFlags();
   
	// SaveWaveFile(LPSTR filename)
   // 지정된 파일에 데이터를 저장한다.
   int SaveWaveFile(LPSTR filename);
   
public:
	PCMWAVEFORMAT WaveRecord;//웨이브 정보
	long lDatasize;//웨이브 데이터 크기
	int m_nSec; //녹음하려고 하는 데이터의 시간 초단위 
	WAVEHDR WaveHeader; //웨이브 데이터 헤더

protected:
	//웨이브 디바이스
	HWAVEIN hWaveInn;//녹음하기 위한 디바이스
	HWAVEOUT hWaveOut;//출력하기 위한 디바이스

	//웨이브 헤더 정보


	//웨이브 데이터
	int m_nPassTime;//웨이브 데이터의 처음 포인터
	HANDLE waveDataBlock;//웨이브 데이터 블록
	LPBYTE pWave;//웨이브 데이터 포인터


	// 파일을 로드할 경우 멤버
	char m_strFileName[80];//파일을 로드할 경우 사용하는 파일명 데이터
	MMCKINFO MMCkInfoParent;//부모 청크 정보 구조체
	MMCKINFO MMCkInfoChild;//자직 청크 정보 구조체
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_LOW_LEVEL_AUDIO_SERVICE_H_)

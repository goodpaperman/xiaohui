/*===============================================================
   Low-Level Wave 서비스를 이용한 wave 출력 입력 저장 클래스
================================================================*/
#include "stdafx.h"
#include "LowLevelAudioService.h"
#include <string.h>

//생성자
CLowLevelAudioService::CLowLevelAudioService()
{
	pWave=NULL;
	waveDataBlock=NULL;
	m_nPassTime=0;
}


CLowLevelAudioService::~CLowLevelAudioService()
{
	wFreeMemory();
}


// wAllocMemory()
// 내부 함수 데이터 크기만큼 메모리에 alloc시킨다.
int CLowLevelAudioService::wAllocMemory()
{
	if(pWave)
		wFreeMemory();

	//lDatasize만큼 메모리 설정
   waveDataBlock = ::GlobalAlloc(GMEM_MOVEABLE,lDatasize);
  
   if(waveDataBlock == NULL)
		return FALSE;
  
   //메모리를 pOutWave에 연결시킨다.
   pWave = (LPBYTE)::GlobalLock(waveDataBlock);
   return TRUE;
}


// wFreeMemory()
// 메모리를 해제한다.
void CLowLevelAudioService::wFreeMemory()
{

	//현재 데이터 블럭이 설정되어 있으면 해제하라.
	if(waveDataBlock)
	{
		::GlobalUnlock(waveDataBlock);
		::GlobalFree(waveDataBlock);
		waveDataBlock=NULL;
		pWave=NULL;
	}
}


// wSetWaveHeader()
// 웨이브 디바이스에 보낼 헤더를 설정한다.
// pWave는 음성 데이터가 적재되어 있는 메모리 포인터
// lDatasize 음성 데이터의 크기
void CLowLevelAudioService::wSetWaveHeader()
{
   WaveHeader.lpData=(LPSTR) pWave+((m_nPassTime/2)*WaveRecord.wf.nAvgBytesPerSec);
   WaveHeader.dwBufferLength = lDatasize-((m_nPassTime/2)*WaveRecord.wf.nAvgBytesPerSec);
   WaveHeader.dwFlags=0L;
   WaveHeader.dwLoops =0L;
   WaveHeader.dwBytesRecorded=lDatasize-((m_nPassTime/2)*WaveRecord.wf.nAvgBytesPerSec);
}

// LoadWaveFile(LPSTR filename)
// 파일을 지정하면 지정한 파일에서 웨이브 파일을 읽고
// 데이터는 pWave에, 데이터 크기는 lDatasize에 저장하고
// 웨이브 디바이스에 보낼 헤더를 설정한다.
int CLowLevelAudioService::LoadWaveFile(LPSTR filename)
{

	//파일명을 클래스 맴버에 저장
	lstrcpy((LPTSTR)m_strFileName, (LPTSTR)filename);

	//파일을 열고
	HMMIO hmmio = mmioOpen((LPSTR)m_strFileName,NULL,MMIO_READ);

	//파일이 없으면
	if(!hmmio)
	{
		AfxMessageBox("파일이 없습니다.!");
		return FALSE;
	}

	//부모 청크를 찾기 위해서 키워드는 WAVE이므로 일단 WAVE를 
	// fccType에 저장한다.
	MMCkInfoParent.fccType = mmioFOURCC('W','A','V','E');
	
	//부모 청크를 찾아라.
   erroCode = mmioDescend(hmmio,&MMCkInfoParent,NULL,MMIO_FINDRIFF);
 
	//부모 청크를 못 찾으면 
	if(erroCode)
	{
		AfxMessageBox("웨이브 파일이 아닙니다.");
		mmioClose(hmmio,0);
		return FALSE;
	}

	//자식 청크를 찾기 위해서는 fmt를 찾아야 하므로 fmt
	//를 ckid에 저장
	MMCkInfoChild.ckid = mmioFOURCC('f','m','t',' '); 
	
	//자식 청크를 찾아라.
	erroCode = mmioDescend(hmmio,&MMCkInfoChild,&MMCkInfoParent,MMIO_FINDCHUNK);
	
	//못 찾으면 
	if(erroCode)
	{
		AfxMessageBox("fmt Descending Error");
		mmioClose(hmmio,0);
		return FALSE;
	}

	//찾은 다음부터가 웨이브 정보이므로 읽어야 한다.
	DWORD bytesRead = mmioRead(hmmio,(LPSTR)&WaveRecord,MMCkInfoChild.cksize);
	
	//읽지 못하면
	if(bytesRead<=0)
	{
		AfxMessageBox("wave format read Error");
		mmioClose(hmmio,0);
		return FALSE;
	}

   //이제 다시 올라와서
   erroCode = mmioAscend(hmmio,&MMCkInfoChild,0);
   
	//못 올라오면
   if(erroCode)
   {
		AfxMessageBox("Error Ascending in file");
		mmioClose(hmmio,0);
		return FALSE;
   }

   //데이터를 찾아야 하므로 ckid에 data 설정
   MMCkInfoChild.ckid = mmioFOURCC('d','a','t','a');

   //데이터를 찾는다.
   erroCode = mmioDescend(hmmio,&MMCkInfoChild,&MMCkInfoParent,MMIO_FINDCHUNK);

   //못 찾으면 
   if(erroCode)
   {
		AfxMessageBox("data 청크를 찾을 수가 없습니다.");
		mmioClose(hmmio,0);
		return FALSE;
   }
   //데이터 크기를 얻는다.
   lDatasize = MMCkInfoChild.cksize;

   //메모리에 데이터를 넣을 장소 만들기
   if(!wAllocMemory())
   {
		AfxMessageBox("적재할 메모리가 부족합니다");
		mmioClose(hmmio,0);
		return FALSE;
   }

   //데이터를 읽는다.
   if(mmioRead(hmmio,(LPSTR)pWave,lDatasize) != lDatasize)
   {
		AfxMessageBox("데이터를 읽을 수가 없습니다.");
		mmioClose(hmmio,0);
		return FALSE;
   }

   //웨이브 디바이스에 보낼 헤더를 설정한다.
   wSetWaveHeader();

	//파일을 찾는다.
   mmioClose(hmmio,0);  

   m_nSec=(int)lDatasize/WaveRecord.wf.nAvgBytesPerSec;

   return TRUE;
}


// SaveWaveFile(LPSTR filename)
// 지정된 파일에 데이터를 저장한다.
int CLowLevelAudioService::SaveWaveFile(LPSTR filename)
{
	HFILE Inn;
	DWORD len;

	Inn =_lcreat(filename,0);
	if(Inn==NULL)
	{
		AfxMessageBox("공유원칙을 어겼습니다.");
		return FALSE;
   }
	
	//RIFF, 즉 헤더를 넣는다.
	_lwrite(Inn,(LPSTR)"RIFF",4);
	len=40+lDatasize;
 
	//전체 크기 -4를 넣는다.
	_lwrite(Inn,(LPSTR)&len,4);
 
	//WAVE라는 글자를 쓴다.
	_lwrite(Inn,(LPSTR)"WAVE",4);
 
	//fmt라고 기록하여 정보 처음을 알린다.
	_lwrite(Inn,(LPSTR)"fmt ",4);
 
	//웨이브 포맷 청크를 넣는다. 웨이브 포맷 청크는 16
	len=16;
	_lwrite(Inn,(LPSTR)&len,4);

	short i;
	i=1;

	//웨이브 포맷이라는 정보를 넣는다. 웨이브 포맷=1
	_lwrite(Inn,(LPSTR)&i,2);
 
	//스테레오 모노 정보를 넣는다.
	i=(short)WaveRecord.wf.nChannels;
	_lwrite(Inn,(LPSTR)&i,2);
	
	//샘플링수를 넣는다.
	_lwrite(Inn,(LPSTR)&WaveRecord.wf.nSamplesPerSec,4);

	//초당 필요한 바이트수를 넣는다.
	_lwrite(Inn,(LPSTR)&WaveRecord.wf.nAvgBytesPerSec,4);

	//한 개의 샘플바이트 
	i=(short)WaveRecord.wf.nBlockAlign;
	_lwrite(Inn,(LPSTR)&i,2);

	//샘플당 비트수
	i=(short)WaveRecord.wBitsPerSample;
	_lwrite(Inn,(LPSTR)&i,2);

	//데이터 청크라고 설정
	_lwrite(Inn,(LPSTR)"data",4);
 
	//데이터 크기를 넣는다.
	_lwrite(Inn,(LPSTR)&lDatasize,4);

	//데이터를 넣는다.
	if(lDatasize!=(long)_lwrite(Inn,(LPSTR)pWave,lDatasize))
	{
		AfxMessageBox("저장할 용량이 없습니다.");
		return FALSE;
   }

	_lclose(Inn);

   return TRUE;
}


// wOpenOutDevice()
// 내부 함수 출력 디바이스를 연다.
int CLowLevelAudioService::wOpenOutDevice()
{
	//출력 디바이스를 연다.
	erroCode = waveOutOpen((LPHWAVEOUT)&hWaveOut,NULL,(tWAVEFORMATEX*)&WaveRecord,0L,0L,0L);
	if(erroCode)
	{
		AfxMessageBox("Out 디바이스를 열 수 없습니다.");
		return FALSE;
	}

   erroCode=waveOutPrepareHeader(hWaveOut,&WaveHeader, sizeof(WaveHeader));
   if(erroCode)
   {
		AfxMessageBox("Preapre Header Error");
		return FALSE;
   }
 
   return TRUE;
}


// SetDataSize(int sec);  
// 데이터 크기를 설정한다.
// sec는 초단위
// 본 함수는 레코딩할 때 몇 초로 할 것인지를 나타냄.
void CLowLevelAudioService::SetDataSize(int sec)
{
   m_nSec = sec;
   lDatasize=(DWORD)WaveRecord.wf.nAvgBytesPerSec*sec;
}


// wOpenRecDevice() 
// 녹음을 하기 위한 웨이브 디바이스를 연다.
int CLowLevelAudioService::wOpenRecDevice()
{
   erroCode=waveInOpen((LPHWAVEIN)&hWaveInn,WAVE_MAPPER,(tWAVEFORMATEX*)&WaveRecord,0L,0L,0L);
	if(erroCode)
	{
		AfxMessageBox("Record 디바이스를 열 수 없습니다.");
		return FALSE;
	}

	erroCode=waveInPrepareHeader(hWaveInn,&WaveHeader, sizeof(WaveHeader));
   if(erroCode)
   {
		AfxMessageBox("wave in prepare header error");
		return FALSE;
   }

	return TRUE;
}


// SetWaveInfo(int MonoStero,int Sampling,int BitSample)
// 웨이브 파일을 녹음하기 위해서는 일단 정보가 필요하다.
// 몇 비트로, 몇 kHz로, 모노인지 스테레오인지 등등을 설정해야 한다.
void CLowLevelAudioService::SetWaveInfo(int MonoStero,int Sampling,int BitSample)
{
	int chk,byte;
	//비트 샘플을 보고 바이트로 환산한다.
	//8비트는 1바이트
	if(BitSample==8)
		chk=1;

	//16비트는 2바이트
	else if(BitSample==16)
		chk=2;

	//32비트는 4바이트
	else
		chk=4;
 
	byte = chk*MonoStero;

	WaveRecord.wf.wFormatTag=1;//웨이브 파일 포맷을 읽을 것
	WaveRecord.wf.nChannels=MonoStero;//모노냐 스테레오냐
	WaveRecord.wf.nSamplesPerSec=Sampling;//샘플링 비율

	// 11kHz=11025 22kHz=22050 44kHz=44100 8kHz = 8000
	//초당 필요한 바이트수
	// 샘플링×모노 스테레오×chk
	WaveRecord.wf.nAvgBytesPerSec=Sampling*MonoStero*chk;

	// 한 개의 정보 블럭
	WaveRecord.wf.nBlockAlign=byte;

	// 비트 샘플 8비트 16비트 32비트 
	WaveRecord.wBitsPerSample=BitSample;
}


// OpenWaveDevice(int mode)
// 웨이브 디바이스를 연다.
// 모드가 TRUE면 출력하기 위해 열고
// 모드가 FALSE면 레코딩하기 위해 연다.
int CLowLevelAudioService::OpenWaveDevice(int mode)
{
	if(mode)
		erroCode=wOpenOutDevice();
	else
		erroCode=wOpenRecDevice();

	return erroCode;
}


// PlayWave()
// 웨이브를 출력한다.
// 출력시킬 경우 안에 디바이스를 여는 함수가 내장되어 있으므로
// OpenWaveDevice 함수를 쓸 필요없다.
int CLowLevelAudioService::PlayWave()
{
	//헤더를 설정하고
	wSetWaveHeader();
   
	//디바이스를 연 다음
   if(!wOpenOutDevice())
		return FALSE;
   
	//출력한다.
   if(!Play())
		return FALSE;
   
	return TRUE;
}


// Play()
// 디바이스가 열린 상태에서 플레이 
// 본 함수는 OpenWaveDevice가 미리 설정되어 있어야 한다.
int CLowLevelAudioService::Play()
{
   //출력한다.
   erroCode = waveOutWrite(hWaveOut,&WaveHeader,sizeof(WaveHeader));
   if(erroCode)
   {
		AfxMessageBox("음성 파일 출력 실패");
		return FALSE;
   }
   return TRUE;
}


// PlayPause()
// 현재 출력을 잠시 중단한다.
int CLowLevelAudioService::PlayPause()
{
   erroCode=waveOutPause(hWaveOut);
   if(erroCode)
   {
		AfxMessageBox("임시 멈춤 실패");
		return FALSE;
   }
   wCloseOutDevice();
   return TRUE;
}


// wCloseOutDevice()
// 출력 디바이스를 닫는다.
int CLowLevelAudioService::wCloseOutDevice()
{
   erroCode=waveOutReset(hWaveOut);
   if(erroCode)
   {
		AfxMessageBox("재설정 실패");
		return FALSE;
   }

   erroCode=waveOutUnprepareHeader(hWaveOut,&WaveHeader,sizeof(WaveHeader));
   if(erroCode)
   {
		AfxMessageBox("헤더 해제 실패");
		return FALSE;
   }

   erroCode=waveOutClose(hWaveOut);
   if(erroCode)
   {
		AfxMessageBox("웨이브 디바이스 닫기 실패");
		return FALSE;
   }
   return TRUE;
}


// StopRecord();
// 레코드 하는 것을 멈춘다.
int CLowLevelAudioService::StopRecord()
{
	erroCode=waveInStop(hWaveInn);
	if(erroCode)
	{
		AfxMessageBox("wave stop error");
		return FALSE;
	}

	erroCode=waveInReset(hWaveInn);
	if(erroCode)
	{
		AfxMessageBox("wave Reset error");
		return FALSE;
	}
 
	wCloseRecDevice();
   
	return TRUE;
}


// wCloseRecDevice()
// 레코드 디바이스를 닫는다.
int CLowLevelAudioService::wCloseRecDevice()
{
	erroCode=waveInUnprepareHeader(hWaveInn,&WaveHeader,sizeof(WaveHeader));
	if(erroCode)
	{
		AfxMessageBox("wave Unprepare error");
		return FALSE;
	}

	erroCode=waveInClose(hWaveInn);
	if(erroCode)
	{
		AfxMessageBox("wave close error");
		return FALSE;
	}
	
	return TRUE;
}


// CloseWaveDevice(int mode)
// 웨이브 디바이스를 닫는다.
int CLowLevelAudioService::CloseWaveDevice(int mode)
{
	if(mode)
		erroCode=wCloseOutDevice();
	else
		erroCode=wCloseRecDevice();

	return erroCode;
}
  

// GetdwFlags()
// 헤더에 dwFlags를 리턴한다.
int CLowLevelAudioService::GetdwFlags()
{
	return WaveHeader.dwFlags;
}


// SetWavePos(int point)
// 웨이브의 위치를 변화시킨다.
int CLowLevelAudioService::SetWavePos(int point)
{
   m_nPassTime=point;
   return TRUE;
}


// RecordWave()
// 웨이브를 녹음한다. 
// 디바이스를 열 필요없음.
int CLowLevelAudioService::RecordWave()
{
   //헤더를 설정하고
   wSetWaveHeader();
   
	//디바이스를 연 다음
   if(!wOpenRecDevice())
		return FALSE;
   
	if(!Record())
		return FALSE;
   return TRUE;
}


// Record()
// 웨이브를 녹음한다.
// 디바이스 열 필요 있음.
int CLowLevelAudioService::Record()
{
   erroCode=waveInAddBuffer(hWaveInn,&WaveHeader,sizeof(WaveHeader));
   if(erroCode)
   {
		AfxMessageBox("waveInAddBuffer Error");
		return FALSE;
   }

	erroCode=waveInStart(hWaveInn);
   if(erroCode)
   {
		AfxMessageBox("wave record error");
		return FALSE;
   }

   return TRUE;
}


// DrawWave(CDC *pDC,CRect rect,COLORREF Color,int step,int pos);
// rect로 설정한 박스에 천연의 색으로 웨이브 파장을 그려라!
// pos는 0.5초 단위의 위치, step는 몇 바이트씩 건너뛰면서
// 그릴 것인지 만약 1이면 1바이트 1바이트 모두 그리기 때문에
// 파장은 진하고 그리는 속도는 느리다. */
void CLowLevelAudioService::DrawWave(CDC *pDC,CRect rect,COLORREF Color,int step,int pos)
{
	int i,xpos;
	int gab;
	float j;
	float yper,averloop;

	CPen Pen;
	CPen *pOldPen;

	Pen.CreatePen(PS_SOLID,0,Color);
	pOldPen=(CPen *)pDC->SelectObject(&Pen);

	yper=(float)(rect.bottom-rect.top)/256;
	averloop= (float)lDatasize/(rect.right-rect.left);

	i=(pos-1)*(WaveRecord.wf.nAvgBytesPerSec/2);
	if(pos==0)
		return;
	xpos=int(i/averloop+0.5f);
	int k=0;
	int middle;

	for(;i<(int)(pos)*((int)WaveRecord.wf.nAvgBytesPerSec/2) && i < lDatasize;)
	{
		for(j=0;j<averloop+0.5;j=j+step)
		{
			i=i+step;
			if(WaveRecord.wBitsPerSample==8)
				gab=Bit8Value(i);
			else if(WaveRecord.wBitsPerSample==16)
				gab=Bit16Value(i);
			else
				gab=Bit32Value(i);
			
			middle=rect.bottom-((rect.bottom-rect.top)/2);
			if(k==0)
				pDC->MoveTo(xpos+rect.left,int(middle+(gab*yper)+0.5f));
			else
				pDC->LineTo(xpos+rect.left,int(middle+(gab*yper)+0.5f));
			k++;
		}
		xpos++;
	}

	pDC->SelectObject(pOldPen);
	Pen.DeleteObject();
}


// Bit8Value(int num)
// 8비트일 때 현재 바이트값을 정한다.
int CLowLevelAudioService::Bit8Value(int num)
{
	int gab;
	if(WaveHeader.lpData[num]&0x80)
		gab=-(128+WaveHeader.lpData[num]);
	else
		gab=128-WaveHeader.lpData[num];
 
	return gab;
}


// Bit16Value(int num)
// 16비트일 때 현재 바이트값을 정한다.
int CLowLevelAudioService::Bit16Value(int num)
{
	union ci{ 
		char c[2];
		short gab;
   } charint;

	int gab;

	charint.c[0]=WaveHeader.lpData[num];
	charint.c[1]=WaveHeader.lpData[num+1];
	gab=65535-charint.gab;
 
	//이 부분 256은 위의 DrawWave에서 256이 있기 때문
	gab=gab/256;
	gab=gab-256;
	
	return gab;
}


// Bit32Value(int num)
// 32비트일 때 현재 바이트값을 정한다.
int CLowLevelAudioService::Bit32Value(int num)
{
	union ci{ 
		char c[4];
		DWORD gab;
   } charint;

	int gab;
	charint.c[0]=WaveHeader.lpData[num];
	charint.c[1]=WaveHeader.lpData[num+1];

	charint.c[2]=WaveHeader.lpData[num+2];
	charint.c[3]=WaveHeader.lpData[num+3];

	gab=0xFFFF-charint.gab;

	//이 부분 65535은 위의 DrawWave에서 256이 있기 때문
	gab=gab/65535;
	gab=gab-65535;
	
	return gab;
}

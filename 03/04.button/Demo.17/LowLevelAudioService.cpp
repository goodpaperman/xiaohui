/*===============================================================
   Low-Level Wave ���񽺸� �̿��� wave ��� �Է� ���� Ŭ����
================================================================*/
#include "stdafx.h"
#include "LowLevelAudioService.h"
#include <string.h>

//������
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
// ���� �Լ� ������ ũ�⸸ŭ �޸𸮿� alloc��Ų��.
int CLowLevelAudioService::wAllocMemory()
{
	if(pWave)
		wFreeMemory();

	//lDatasize��ŭ �޸� ����
   waveDataBlock = ::GlobalAlloc(GMEM_MOVEABLE,lDatasize);
  
   if(waveDataBlock == NULL)
		return FALSE;
  
   //�޸𸮸� pOutWave�� �����Ų��.
   pWave = (LPBYTE)::GlobalLock(waveDataBlock);
   return TRUE;
}


// wFreeMemory()
// �޸𸮸� �����Ѵ�.
void CLowLevelAudioService::wFreeMemory()
{

	//���� ������ ���� �����Ǿ� ������ �����϶�.
	if(waveDataBlock)
	{
		::GlobalUnlock(waveDataBlock);
		::GlobalFree(waveDataBlock);
		waveDataBlock=NULL;
		pWave=NULL;
	}
}


// wSetWaveHeader()
// ���̺� ����̽��� ���� ����� �����Ѵ�.
// pWave�� ���� �����Ͱ� ����Ǿ� �ִ� �޸� ������
// lDatasize ���� �������� ũ��
void CLowLevelAudioService::wSetWaveHeader()
{
   WaveHeader.lpData=(LPSTR) pWave+((m_nPassTime/2)*WaveRecord.wf.nAvgBytesPerSec);
   WaveHeader.dwBufferLength = lDatasize-((m_nPassTime/2)*WaveRecord.wf.nAvgBytesPerSec);
   WaveHeader.dwFlags=0L;
   WaveHeader.dwLoops =0L;
   WaveHeader.dwBytesRecorded=lDatasize-((m_nPassTime/2)*WaveRecord.wf.nAvgBytesPerSec);
}

// LoadWaveFile(LPSTR filename)
// ������ �����ϸ� ������ ���Ͽ��� ���̺� ������ �а�
// �����ʹ� pWave��, ������ ũ��� lDatasize�� �����ϰ�
// ���̺� ����̽��� ���� ����� �����Ѵ�.
int CLowLevelAudioService::LoadWaveFile(LPSTR filename)
{

	//���ϸ��� Ŭ���� �ɹ��� ����
	lstrcpy((LPTSTR)m_strFileName, (LPTSTR)filename);

	//������ ����
	HMMIO hmmio = mmioOpen((LPSTR)m_strFileName,NULL,MMIO_READ);

	//������ ������
	if(!hmmio)
	{
		AfxMessageBox("������ �����ϴ�.!");
		return FALSE;
	}

	//�θ� ûũ�� ã�� ���ؼ� Ű����� WAVE�̹Ƿ� �ϴ� WAVE�� 
	// fccType�� �����Ѵ�.
	MMCkInfoParent.fccType = mmioFOURCC('W','A','V','E');
	
	//�θ� ûũ�� ã�ƶ�.
   erroCode = mmioDescend(hmmio,&MMCkInfoParent,NULL,MMIO_FINDRIFF);
 
	//�θ� ûũ�� �� ã���� 
	if(erroCode)
	{
		AfxMessageBox("���̺� ������ �ƴմϴ�.");
		mmioClose(hmmio,0);
		return FALSE;
	}

	//�ڽ� ûũ�� ã�� ���ؼ��� fmt�� ã�ƾ� �ϹǷ� fmt
	//�� ckid�� ����
	MMCkInfoChild.ckid = mmioFOURCC('f','m','t',' '); 
	
	//�ڽ� ûũ�� ã�ƶ�.
	erroCode = mmioDescend(hmmio,&MMCkInfoChild,&MMCkInfoParent,MMIO_FINDCHUNK);
	
	//�� ã���� 
	if(erroCode)
	{
		AfxMessageBox("fmt Descending Error");
		mmioClose(hmmio,0);
		return FALSE;
	}

	//ã�� �������Ͱ� ���̺� �����̹Ƿ� �о�� �Ѵ�.
	DWORD bytesRead = mmioRead(hmmio,(LPSTR)&WaveRecord,MMCkInfoChild.cksize);
	
	//���� ���ϸ�
	if(bytesRead<=0)
	{
		AfxMessageBox("wave format read Error");
		mmioClose(hmmio,0);
		return FALSE;
	}

   //���� �ٽ� �ö�ͼ�
   erroCode = mmioAscend(hmmio,&MMCkInfoChild,0);
   
	//�� �ö����
   if(erroCode)
   {
		AfxMessageBox("Error Ascending in file");
		mmioClose(hmmio,0);
		return FALSE;
   }

   //�����͸� ã�ƾ� �ϹǷ� ckid�� data ����
   MMCkInfoChild.ckid = mmioFOURCC('d','a','t','a');

   //�����͸� ã�´�.
   erroCode = mmioDescend(hmmio,&MMCkInfoChild,&MMCkInfoParent,MMIO_FINDCHUNK);

   //�� ã���� 
   if(erroCode)
   {
		AfxMessageBox("data ûũ�� ã�� ���� �����ϴ�.");
		mmioClose(hmmio,0);
		return FALSE;
   }
   //������ ũ�⸦ ��´�.
   lDatasize = MMCkInfoChild.cksize;

   //�޸𸮿� �����͸� ���� ��� �����
   if(!wAllocMemory())
   {
		AfxMessageBox("������ �޸𸮰� �����մϴ�");
		mmioClose(hmmio,0);
		return FALSE;
   }

   //�����͸� �д´�.
   if(mmioRead(hmmio,(LPSTR)pWave,lDatasize) != lDatasize)
   {
		AfxMessageBox("�����͸� ���� ���� �����ϴ�.");
		mmioClose(hmmio,0);
		return FALSE;
   }

   //���̺� ����̽��� ���� ����� �����Ѵ�.
   wSetWaveHeader();

	//������ ã�´�.
   mmioClose(hmmio,0);  

   m_nSec=(int)lDatasize/WaveRecord.wf.nAvgBytesPerSec;

   return TRUE;
}


// SaveWaveFile(LPSTR filename)
// ������ ���Ͽ� �����͸� �����Ѵ�.
int CLowLevelAudioService::SaveWaveFile(LPSTR filename)
{
	HFILE Inn;
	DWORD len;

	Inn =_lcreat(filename,0);
	if(Inn==NULL)
	{
		AfxMessageBox("������Ģ�� �����ϴ�.");
		return FALSE;
   }
	
	//RIFF, �� ����� �ִ´�.
	_lwrite(Inn,(LPSTR)"RIFF",4);
	len=40+lDatasize;
 
	//��ü ũ�� -4�� �ִ´�.
	_lwrite(Inn,(LPSTR)&len,4);
 
	//WAVE��� ���ڸ� ����.
	_lwrite(Inn,(LPSTR)"WAVE",4);
 
	//fmt��� ����Ͽ� ���� ó���� �˸���.
	_lwrite(Inn,(LPSTR)"fmt ",4);
 
	//���̺� ���� ûũ�� �ִ´�. ���̺� ���� ûũ�� 16
	len=16;
	_lwrite(Inn,(LPSTR)&len,4);

	short i;
	i=1;

	//���̺� �����̶�� ������ �ִ´�. ���̺� ����=1
	_lwrite(Inn,(LPSTR)&i,2);
 
	//���׷��� ��� ������ �ִ´�.
	i=(short)WaveRecord.wf.nChannels;
	_lwrite(Inn,(LPSTR)&i,2);
	
	//���ø����� �ִ´�.
	_lwrite(Inn,(LPSTR)&WaveRecord.wf.nSamplesPerSec,4);

	//�ʴ� �ʿ��� ����Ʈ���� �ִ´�.
	_lwrite(Inn,(LPSTR)&WaveRecord.wf.nAvgBytesPerSec,4);

	//�� ���� ���ù���Ʈ 
	i=(short)WaveRecord.wf.nBlockAlign;
	_lwrite(Inn,(LPSTR)&i,2);

	//���ô� ��Ʈ��
	i=(short)WaveRecord.wBitsPerSample;
	_lwrite(Inn,(LPSTR)&i,2);

	//������ ûũ��� ����
	_lwrite(Inn,(LPSTR)"data",4);
 
	//������ ũ�⸦ �ִ´�.
	_lwrite(Inn,(LPSTR)&lDatasize,4);

	//�����͸� �ִ´�.
	if(lDatasize!=(long)_lwrite(Inn,(LPSTR)pWave,lDatasize))
	{
		AfxMessageBox("������ �뷮�� �����ϴ�.");
		return FALSE;
   }

	_lclose(Inn);

   return TRUE;
}


// wOpenOutDevice()
// ���� �Լ� ��� ����̽��� ����.
int CLowLevelAudioService::wOpenOutDevice()
{
	//��� ����̽��� ����.
	erroCode = waveOutOpen((LPHWAVEOUT)&hWaveOut,NULL,(tWAVEFORMATEX*)&WaveRecord,0L,0L,0L);
	if(erroCode)
	{
		AfxMessageBox("Out ����̽��� �� �� �����ϴ�.");
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
// ������ ũ�⸦ �����Ѵ�.
// sec�� �ʴ���
// �� �Լ��� ���ڵ��� �� �� �ʷ� �� �������� ��Ÿ��.
void CLowLevelAudioService::SetDataSize(int sec)
{
   m_nSec = sec;
   lDatasize=(DWORD)WaveRecord.wf.nAvgBytesPerSec*sec;
}


// wOpenRecDevice() 
// ������ �ϱ� ���� ���̺� ����̽��� ����.
int CLowLevelAudioService::wOpenRecDevice()
{
   erroCode=waveInOpen((LPHWAVEIN)&hWaveInn,WAVE_MAPPER,(tWAVEFORMATEX*)&WaveRecord,0L,0L,0L);
	if(erroCode)
	{
		AfxMessageBox("Record ����̽��� �� �� �����ϴ�.");
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
// ���̺� ������ �����ϱ� ���ؼ��� �ϴ� ������ �ʿ��ϴ�.
// �� ��Ʈ��, �� kHz��, ������� ���׷������� ����� �����ؾ� �Ѵ�.
void CLowLevelAudioService::SetWaveInfo(int MonoStero,int Sampling,int BitSample)
{
	int chk,byte;
	//��Ʈ ������ ���� ����Ʈ�� ȯ���Ѵ�.
	//8��Ʈ�� 1����Ʈ
	if(BitSample==8)
		chk=1;

	//16��Ʈ�� 2����Ʈ
	else if(BitSample==16)
		chk=2;

	//32��Ʈ�� 4����Ʈ
	else
		chk=4;
 
	byte = chk*MonoStero;

	WaveRecord.wf.wFormatTag=1;//���̺� ���� ������ ���� ��
	WaveRecord.wf.nChannels=MonoStero;//���� ���׷�����
	WaveRecord.wf.nSamplesPerSec=Sampling;//���ø� ����

	// 11kHz=11025 22kHz=22050 44kHz=44100 8kHz = 8000
	//�ʴ� �ʿ��� ����Ʈ��
	// ���ø������ ���׷�����chk
	WaveRecord.wf.nAvgBytesPerSec=Sampling*MonoStero*chk;

	// �� ���� ���� ��
	WaveRecord.wf.nBlockAlign=byte;

	// ��Ʈ ���� 8��Ʈ 16��Ʈ 32��Ʈ 
	WaveRecord.wBitsPerSample=BitSample;
}


// OpenWaveDevice(int mode)
// ���̺� ����̽��� ����.
// ��尡 TRUE�� ����ϱ� ���� ����
// ��尡 FALSE�� ���ڵ��ϱ� ���� ����.
int CLowLevelAudioService::OpenWaveDevice(int mode)
{
	if(mode)
		erroCode=wOpenOutDevice();
	else
		erroCode=wOpenRecDevice();

	return erroCode;
}


// PlayWave()
// ���̺긦 ����Ѵ�.
// ��½�ų ��� �ȿ� ����̽��� ���� �Լ��� ����Ǿ� �����Ƿ�
// OpenWaveDevice �Լ��� �� �ʿ����.
int CLowLevelAudioService::PlayWave()
{
	//����� �����ϰ�
	wSetWaveHeader();
   
	//����̽��� �� ����
   if(!wOpenOutDevice())
		return FALSE;
   
	//����Ѵ�.
   if(!Play())
		return FALSE;
   
	return TRUE;
}


// Play()
// ����̽��� ���� ���¿��� �÷��� 
// �� �Լ��� OpenWaveDevice�� �̸� �����Ǿ� �־�� �Ѵ�.
int CLowLevelAudioService::Play()
{
   //����Ѵ�.
   erroCode = waveOutWrite(hWaveOut,&WaveHeader,sizeof(WaveHeader));
   if(erroCode)
   {
		AfxMessageBox("���� ���� ��� ����");
		return FALSE;
   }
   return TRUE;
}


// PlayPause()
// ���� ����� ��� �ߴ��Ѵ�.
int CLowLevelAudioService::PlayPause()
{
   erroCode=waveOutPause(hWaveOut);
   if(erroCode)
   {
		AfxMessageBox("�ӽ� ���� ����");
		return FALSE;
   }
   wCloseOutDevice();
   return TRUE;
}


// wCloseOutDevice()
// ��� ����̽��� �ݴ´�.
int CLowLevelAudioService::wCloseOutDevice()
{
   erroCode=waveOutReset(hWaveOut);
   if(erroCode)
   {
		AfxMessageBox("�缳�� ����");
		return FALSE;
   }

   erroCode=waveOutUnprepareHeader(hWaveOut,&WaveHeader,sizeof(WaveHeader));
   if(erroCode)
   {
		AfxMessageBox("��� ���� ����");
		return FALSE;
   }

   erroCode=waveOutClose(hWaveOut);
   if(erroCode)
   {
		AfxMessageBox("���̺� ����̽� �ݱ� ����");
		return FALSE;
   }
   return TRUE;
}


// StopRecord();
// ���ڵ� �ϴ� ���� �����.
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
// ���ڵ� ����̽��� �ݴ´�.
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
// ���̺� ����̽��� �ݴ´�.
int CLowLevelAudioService::CloseWaveDevice(int mode)
{
	if(mode)
		erroCode=wCloseOutDevice();
	else
		erroCode=wCloseRecDevice();

	return erroCode;
}
  

// GetdwFlags()
// ����� dwFlags�� �����Ѵ�.
int CLowLevelAudioService::GetdwFlags()
{
	return WaveHeader.dwFlags;
}


// SetWavePos(int point)
// ���̺��� ��ġ�� ��ȭ��Ų��.
int CLowLevelAudioService::SetWavePos(int point)
{
   m_nPassTime=point;
   return TRUE;
}


// RecordWave()
// ���̺긦 �����Ѵ�. 
// ����̽��� �� �ʿ����.
int CLowLevelAudioService::RecordWave()
{
   //����� �����ϰ�
   wSetWaveHeader();
   
	//����̽��� �� ����
   if(!wOpenRecDevice())
		return FALSE;
   
	if(!Record())
		return FALSE;
   return TRUE;
}


// Record()
// ���̺긦 �����Ѵ�.
// ����̽� �� �ʿ� ����.
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
// rect�� ������ �ڽ��� õ���� ������ ���̺� ������ �׷���!
// pos�� 0.5�� ������ ��ġ, step�� �� ����Ʈ�� �ǳʶٸ鼭
// �׸� ������ ���� 1�̸� 1����Ʈ 1����Ʈ ��� �׸��� ������
// ������ ���ϰ� �׸��� �ӵ��� ������. */
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
// 8��Ʈ�� �� ���� ����Ʈ���� ���Ѵ�.
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
// 16��Ʈ�� �� ���� ����Ʈ���� ���Ѵ�.
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
 
	//�� �κ� 256�� ���� DrawWave���� 256�� �ֱ� ����
	gab=gab/256;
	gab=gab-256;
	
	return gab;
}


// Bit32Value(int num)
// 32��Ʈ�� �� ���� ����Ʈ���� ���Ѵ�.
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

	//�� �κ� 65535�� ���� DrawWave���� 256�� �ֱ� ����
	gab=gab/65535;
	gab=gab-65535;
	
	return gab;
}

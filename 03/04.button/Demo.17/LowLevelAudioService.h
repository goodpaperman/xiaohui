/*===============================================================
   Low-Level Wave ���񽺸� �̿��� wave ��� �Է� ���� Ŭ���� ���
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

   int erroCode;//���� �ڵ�
   
	// wAllocMemory()
	// ���� �Լ� ������ ũ�⸸ŭ �޸𸮿� alloc��Ų��.
   int wAllocMemory();

   // wFreeMemory()
   // �޸𸮸� �����Ѵ�.
   void wFreeMemory();
   
	// wSetWaveHeader()
   // ���̺� ����̽��� ���� ����� �����Ѵ�.
   // pWave�� ���� �����Ͱ� ����Ǿ� �ִ� �޸� ������
   // lDatasize ���� �������� ũ��
   void wSetWaveHeader();
  
	// LoadWaveFile(LPSTR filename)
   // ������ �����ϸ� ������ ���Ͽ��� ���̺� ������ �а�
   // �����ʹ� pWave��, ������ ũ��� lDatasize�� �����ϰ�
   // ���̺� ����̽��� ���� ����� �����Ѵ�.
   int LoadWaveFile(LPSTR filename);
   
	// wOpenOutDevice()
   // ���� �Լ� ��� ����̽��� ����.
   int wOpenOutDevice();
   
	// SetDataSize(int sec);  
   // ������ ũ�⸦ �����Ѵ�.
   // sec�� �ʴ���
   // �� �Լ��� ���ڵ��� �� �� �ʷ� �� �������� ��Ÿ��.
   void SetDataSize(int sec);
   
	
   // wOpenRecDevice() 
   // ������ �ϱ� ���� ���̺� ����̽��� ����.
   int wOpenRecDevice();
   
   // SetWaveInfo(int MonoStero,int Sampling,int BitSample)
   // ���̺� ������ �����ϱ� ���ؼ��� �ϴ� ������ �ʿ��ϴ�.
	// �� ��Ʈ��, �� kHz��, ������� ���׷������� ����� �����ؾ� �Ѵ�.
   void SetWaveInfo(int MonoStero,int Sampling,int BitSample);
   
	// OpenWaveDevice(int mode)
   // ���̺� ����̽��� ����.
   // mode�� TRUE�̸� ����ϱ� ���� ����
   // mode�� FALSE�̸� ���ڵ��ϱ� ���� ����.
   int OpenWaveDevice(int mode);
   
	// PlayWave()
   // ���̺긦 ����Ѵ�.
   // ��½�ų ��� �ȿ� ����̽��� ���� �Լ��� ����Ǿ� �����Ƿ�
   // OpenWaveDevice �Լ��� �� �ʿ����.
   int PlayWave();
   
	// Play()
   // ����̽��� ���� ���¿��� �÷��� 
   // �� �Լ��� OpenWaveDevice�� �̸� �����Ǿ� �־�� �Ѵ�.
   int Play();
   
	// PlayPause()
	// ���� ����� ��� �ߴ��Ѵ�.
   int PlayPause();
   
	// wCloseOutDevice()
   // ��� ����̽��� �ݴ´�.
   int wCloseOutDevice();
   
	// StopRecord();
   // ���ڵ� �ϴ� ���� �����.
   int StopRecord();

   // wCloseRecDevice()
   // ���ڵ� ����̽��� �ݴ´�.
   int wCloseRecDevice();
   
	// CloseWaveDevice(int mode)
   // ���̺� ����̽��� �ݴ´�.
   int CloseWaveDevice(int mode);
   
	// RecordWave()
   // ���̺긦 �����Ѵ�. 
   // ����̽��� �� �ʿ����.
   int RecordWave();
   
	// Record()
   // ���̺긦 �����Ѵ�.
   // ����̽� �� �ʿ� ����.
   int Record();
   
	// DrawWave(CDC *pDC,CRect rect,COLORREF Color,int step,int pos);
   // rect�� ������ �ڽ��� õ���� ������ ���̺� ������ �׷���! 
	// pos�� 0.5�� ������ ��ġ, step�� �� ����Ʈ�� �ǳʶٸ鼭 �׸� ������ ����,
	// 1�̸� 1����Ʈ, 1����Ʈ ��� �׸��� ������ ������ ���ϰ� �׸��� �ӵ��� ������. 
	void DrawWave(CDC *pDC,CRect rect,COLORREF Color,int step,int pos);
   
	// Bit8Value(int num)
   // 8��Ʈ�� �� ���� ����Ʈ���� ���Ѵ�.
   int Bit8Value(int num);
   
	// Bit16Value(int num)
   // 16��Ʈ�� �� ���� ����Ʈ���� ���Ѵ�.
   int Bit16Value(int num);
   
	// Bit32Value(int num)
   // 32��Ʈ�� �� ���� ����Ʈ���� ���Ѵ�.
   int Bit32Value(int num);
   
	// SetWavePos(int point)
   // ���̺��� ��ġ�� ��ȭ��Ų��.
   int SetWavePos(int point);
   
	// GetdwFlags()
   // ����� dwFlags�� �����Ѵ�.
   int GetdwFlags();
   
	// SaveWaveFile(LPSTR filename)
   // ������ ���Ͽ� �����͸� �����Ѵ�.
   int SaveWaveFile(LPSTR filename);
   
public:
	PCMWAVEFORMAT WaveRecord;//���̺� ����
	long lDatasize;//���̺� ������ ũ��
	int m_nSec; //�����Ϸ��� �ϴ� �������� �ð� �ʴ��� 
	WAVEHDR WaveHeader; //���̺� ������ ���

protected:
	//���̺� ����̽�
	HWAVEIN hWaveInn;//�����ϱ� ���� ����̽�
	HWAVEOUT hWaveOut;//����ϱ� ���� ����̽�

	//���̺� ��� ����


	//���̺� ������
	int m_nPassTime;//���̺� �������� ó�� ������
	HANDLE waveDataBlock;//���̺� ������ ���
	LPBYTE pWave;//���̺� ������ ������


	// ������ �ε��� ��� ���
	char m_strFileName[80];//������ �ε��� ��� ����ϴ� ���ϸ� ������
	MMCKINFO MMCkInfoParent;//�θ� ûũ ���� ����ü
	MMCKINFO MMCkInfoChild;//���� ûũ ���� ����ü
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_LOW_LEVEL_AUDIO_SERVICE_H_)

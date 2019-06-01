#include "..\headers.h"
#include "..\resource.h"
#include "..\DirectDrawWin.h"
#include "mmsystem.h"
#include "dsound.h"
#include "sound.h"
#define SOUND_SAMP	22100
#define	SOUND_NUM	7

int             sound = 1;
int				sndinit	= 0;

LPDIRECTSOUNDBUFFER	LoadRaw(int id);
#pragma	comment(lib,"dsound.lib")

LPDIRECTSOUND	lpDS=NULL;
LPDIRECTSOUNDBUFFER	primbuff=NULL;
LPDIRECTSOUNDBUFFER soundeffect[SOUND_NUM]={NULL};
static int sound_id[SOUND_NUM]={
  IDR_RAWS,
  IDR_RAWE,
  IDR_RAWCO,
  IDR_RAWD1,
  IDR_RAWD2,
  IDR_RAWCR1,
  IDR_RAWCR2
}; 

BOOL	InitDirectSound()
{
	if(DirectSoundCreate(NULL,&lpDS,NULL)!=DS_OK)
		return FALSE;
	if(lpDS->SetCooperativeLevel(GetDDWin()->m_hWnd,DSSCL_NORMAL)!=DS_OK)
		return FALSE;
	DSBUFFERDESC buffdesc;
	ZeroMemory(&buffdesc,sizeof(buffdesc));
	buffdesc.dwSize=sizeof(buffdesc);
	buffdesc.dwFlags=DSBCAPS_PRIMARYBUFFER;
	buffdesc.lpwfxFormat=NULL;
	if(lpDS->CreateSoundBuffer(&buffdesc,&primbuff,NULL)!=DS_OK)
		return FALSE;
	sndinit=1;
	for(int i=0;i<SOUND_NUM;i++)
		if((soundeffect[i]=LoadRaw(sound_id[i]))==NULL)
			sndinit=0;
	return TRUE;
}

BOOL	ReleaseDirectSound()
{
	for(int i=0;i<SOUND_NUM;i++)
		if(soundeffect[i])
			soundeffect[i]->Release();
	if(primbuff)
		primbuff->Release();
	if(lpDS)
		lpDS->Release();
	return TRUE;
}

LPDIRECTSOUNDBUFFER	LoadRaw(int id)
{
	DSBUFFERDESC buffdesc;
	WAVEFORMATEX wav;
	LPDIRECTSOUNDBUFFER	lpdsb=NULL;
	DWORD	len;
	LPBYTE	buf;
	LPBYTE	ptr1;
	LPBYTE	ptr2;
	DWORD	size1;
	DWORD	size2;

	HMODULE hm=AfxGetResourceHandle();
	HRSRC hr=::FindResource(hm,MAKEINTRESOURCE(id),_T("RAW"));
	len=SizeofResource(hm,hr);

	HGLOBAL hg=::LoadResource(hm,hr);
	if(!hg)
		return NULL;
	buf=(LPBYTE)::LockResource(hg);
	if(!buf)
		return NULL;
	wav.wFormatTag=1;
	wav.wBitsPerSample=8;
	wav.nSamplesPerSec=SOUND_SAMP;
	wav.nChannels=1;
	wav.nBlockAlign=1;
	wav.cbSize=0;
	wav.nAvgBytesPerSec=SOUND_SAMP;

	ZeroMemory(&buffdesc,sizeof(buffdesc));
	buffdesc.dwSize=sizeof(buffdesc);
	buffdesc.dwFlags=DSBCAPS_CTRLDEFAULT|DSBCAPS_STATIC;
	buffdesc.lpwfxFormat=&wav;
	buffdesc.dwBufferBytes=len;

	if(lpDS->CreateSoundBuffer(&buffdesc,&lpdsb,NULL)!=DS_OK)
		return NULL;
	if(lpdsb->Lock(0,len,(LPLPVOID)&ptr1,&size1,(LPLPVOID)&ptr2,&size2,0)!=DS_OK)
	{
		lpdsb->Release();
		return NULL;
	}
	
	memcpy(ptr1,buf,size1);
	if(size2)
	{
		memcpy(ptr2,buf+size1,size2);
	}
	if(lpdsb->Unlock(ptr1,size1,ptr2,size2)!=DS_OK)
	{
		lpdsb->Release();
		return NULL;
	}
	return lpdsb;
}

extern  void	play_sound(int n)
{
	if(n<SOUND_NUM)
	{
		soundeffect[n]->SetCurrentPosition(0);
		soundeffect[n]->Play(0,0,0);
	}
}
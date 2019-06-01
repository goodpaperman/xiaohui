// Sound.cpp: implementation of the CSound class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Tetris.h"
#include "Sound.h"
#include <io.h>



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


HINSTANCE CSound :: m_hLib;
CSound::SoundFnc CSound::m_fncSoundPlayer;
BOOL	CSound :: m_bHaveSound = InitSound();
BOOL	CSound :: m_bWantSound = TRUE;


CSound::CSound()
{
	VERIFY(m_hApplication = ::GetModuleHandle(0));

	HRSRC hResInfo = ::FindResource(m_hApplication, MAKEINTRESOURCE(IDR_MidiRussians), "MIDI");
	ASSERT(hResInfo != 0);

	HGLOBAL hRes = ::LoadResource(m_hApplication, hResInfo);
	ASSERT(hRes != 0);

	void * pSound = ::LockResource(hRes);
	ASSERT(pSound == hRes);

	DWORD dwSize = ::SizeofResource(m_hApplication, hResInfo);
	TRACE("Size of MIDI sound: %lu\n", dwSize);

	LPCTSTR pszFile = _ttempnam(0, 0);
	if( pszFile ) {
		CString strFile = pszFile;
		strFile += TEXT(".mid");
		free(LPVOID(pszFile));
		if( _taccess(LPCTSTR(strFile), 0) != 0 ) {
			TRACE("Tempfile to use: \"%s\"\n", LPCTSTR(strFile));
			try {
				CFile file(strFile, CFile::modeCreate|CFile::modeWrite);
				file.Write(pSound, UINT(dwSize));
				file.Close();
				CString strOpen;
				strOpen.Format(TEXT("open %s alias tetris"), strFile);
				if( m_hLib ) {
					MusicFnc fncMusicPlayer = MusicFnc(::GetProcAddress(m_hLib, TEXT("mciSendStringA")));
					if( fncMusicPlayer ) {
						VERIFY((*fncMusicPlayer)(strOpen, 0, 0, 0) == 0);
						VERIFY((*fncMusicPlayer)(TEXT("play tetris"), 0, 0, 0) == 0);
					}
				}
			} catch(...) {
			}
		}
	}
}


CSound::~CSound()
{
	StopSounds();
}


//////////////////////////////////////////////////////////////////////
// Operations
//////////////////////////////////////////////////////////////////////

void CSound :: PlaySound( CSound::SoundType eType, BOOL bAsync /* = FALSE */, BOOL bLoop /* = FALSE */ ) {
	if( m_bHaveSound && m_bWantSound ) {
		ASSERT(m_hApplication);
		ASSERT(m_fncSoundPlayer);

		UINT uResource = 0;

		switch( eType ) {
			case SND_STOPALLSOUNDS:
				(*m_fncSoundPlayer)(0, 0, SND_PURGE);
				return;

			case SND_KEYPRESSED:
				uResource = IDR_SndKey;
				break;

			case SND_PLACE:
				uResource = IDR_SndPlace;
				break;

			case SND_LEVELWARP:
				uResource = IDR_SndLevelWarp;
				break;

			case SND_GAMEOVER:
				uResource = IDR_SndGameOver;
				break;
		}

		// wrong sound specified ?
		ASSERT(uResource > 0);

		DWORD dwFlags = SND_NODEFAULT|SND_NOSTOP|SND_NOWAIT|SND_RESOURCE;
		if( bAsync )
			dwFlags |= SND_ASYNC;
		else
			dwFlags |= SND_SYNC;
		if( bLoop )
			dwFlags |= SND_LOOP;

		(*m_fncSoundPlayer)(MAKEINTRESOURCE(uResource), m_hApplication, dwFlags);
	}
}


BOOL CSound::InitSound()
{
	m_hLib = ::LoadLibrary(TEXT("winmm.dll"));
	if( m_hLib ) {
		m_fncSoundPlayer = SoundFnc(::GetProcAddress(m_hLib, TEXT("PlaySound")));
		if( m_fncSoundPlayer )
			return TRUE;
	}
	return FALSE;
}

// Sound.h: interface for the CSound class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOUND_H__07950063_0476_11D2_A72C_000000000000__INCLUDED_)
#define AFX_SOUND_H__07950063_0476_11D2_A72C_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <mmsystem.h>

#ifdef PlaySound
	#undef PlaySound
#endif

class CSound  
{

	friend class COptionsDlg;

public:
	CSound();
	virtual ~CSound();

public:
	enum SoundType {
		SND_STOPALLSOUNDS = 0,
		SND_KEYPRESSED,
		SND_PLACE,
		SND_LEVELWARP,
		SND_GAMEOVER
	};

public:
	void	PlaySound( enum SoundType, BOOL bAsync = TRUE, BOOL bLoop = FALSE );
	void	StopSounds() {
				PlaySound(SND_STOPALLSOUNDS);
			}

private:
	typedef BOOL (WINAPI *SoundFnc)(LPCSTR, HMODULE, DWORD);
	typedef MCIERROR (WINAPI *MusicFnc)(LPCTSTR, LPTSTR, UINT, HANDLE);
	static HINSTANCE	m_hLib;
	static SoundFnc		m_fncSoundPlayer;
	static BOOL			m_bHaveSound;
	static BOOL			m_bWantSound;
	HMODULE				m_hApplication;

	static BOOL InitSound();
protected:
	HANDLE m_hRes;
};

#endif // !defined(AFX_SOUND_H__07950063_0476_11D2_A72C_000000000000__INCLUDED_)

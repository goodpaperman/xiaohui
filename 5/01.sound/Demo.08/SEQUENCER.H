//////////////////////////////////////////////////////////////////////////
// CSequencer header file
//
// This class encapsulates the MCI API for the MIDI sequencer device
//
// Copyright (C) 1997, 1998 Giancarlo Iovino (giancarlo@saria.com)
// All rights reserved. May not be sold for profit.
//
// This software is provided 'as it is' without implicit or explicit
// warranty.
//
// This code was develeped for MFC Programmer's Sourcebook
// (http://www.codeguru.com)
//

#if !defined(AFX_SEQUENCER_H_FSF54252554_14512_798711_11A30B987GSDA_INCLUDED_)
#define AFX_SEQUENCER_H_FSF54252554_14512_798711_11A30B987GSDA_INCLUDED_

#include "mci.h"

//////////////////////////////////////////////////////////////////////////
// CSequencer
//

class CSequencer : public CMciDevice {

public:
	// Specific time formats	
	static const DWORD FormatMilliseconds;
	static const DWORD FormatSmpte24;
	static const DWORD FormatSmpte25;
	static const DWORD FormatSmpte30;
	static const DWORD FormatSmpte30drop;
	static const DWORD FormatSongPtr;

	// Specific status
	static const DWORD StatusCurrentTrack;
	static const DWORD StatusDivisionType;
	static const DWORD StatusLength;
	static const DWORD StatusMaster;
	static const DWORD StatusOffset;
	static const DWORD StatusPort;
	static const DWORD StatusPosition;
	static const DWORD StatusSlave;
	static const DWORD StatusStart;
	static const DWORD StatusTempo;
	
	// Specific info
	static const DWORD InfoCopyright;
	static const DWORD InfoFile;
	static const DWORD InfoName;	
	
	// Constants for SetPort()
	static const DWORD SeqNone;
	static const DWORD MidiMapper;

	// Constants for SetMaster() and SetSlave()	
	static const DWORD SeqSmpte;
	static const DWORD SeqMidi;

	// Constats for SetSlave()
	static const DWORD SeqFile;

	// Values returned by GetStatus(StatusDivisionType)
	static const DWORD DivPpqn;
	static const DWORD DivSmpte24;
	static const DWORD DivSmpte25;
	static const DWORD DivSmpte30;
	static const DWORD DivSmpte30drop;

	// Open/Save
	DWORD Open(LPCSTR lpszFileName, BOOL bShareable = FALSE);
	DWORD Save(LPCSTR lpszFileName);
	
	// Play/Stop/Pause
	DWORD Play(BOOL bAsync = TRUE);
	DWORD Play(DWORD dwFrom, DWORD dwTo, BOOL bAsync = TRUE);
	DWORD Stop();		
	DWORD Pause();
	DWORD Resume();

	// Seek	
	DWORD Seek(DWORD dwTo, BOOL bAsync = FALSE);
	DWORD SeekToStart(BOOL bAsync = FALSE);
	DWORD SeekToEnd(BOOL bAsync = FALSE);

	// Device status important items
	DWORD GetSongLength(DWORD dwTrack);
	DWORD GetNumberOfTracks();		
	DWORD GetCurrentTrack();
	DWORD GetCurrentPos();
	DWORD GetStartPos();
	DWORD GetPort();
	DWORD GetTempo();
	DWORD GetOffset();
	DWORD GetMaster();
	DWORD GetSlave();
	BOOL IsReady();
	
	// Track info		
	DWORD GetTrackPos(DWORD dwTrack);
	DWORD GetTrackLength(DWORD dwTrack);
	
	// Get/Set the time format
	DWORD GetTimeFormat();
	DWORD SetTimeFormat(DWORD dwTimeFormat);

	// Set
	DWORD SetTempo(DWORD dwTempo);
	DWORD SetPort(DWORD dwPort);
	DWORD SetOffset(DWORD dwOffset);
	DWORD SetMaster(DWORD dwSynchType);
	DWORD SetSlave(DWORD dwSynchType);

protected:
	DWORD Seek(DWORD dwTo, DWORD dwFlags, BOOL bAsync);
	DWORD Set(DWORD dwWhat);	
	DWORD GetDevCapsItem(DWORD dwItem);	
	DWORD GetTrackInfo(DWORD dwTrack, DWORD dwItem);
	
};

#endif // !defined(AFX_SEQUENCER_H_FSF54252554_14512_798711_11A30B987GSDA_INCLUDED_)
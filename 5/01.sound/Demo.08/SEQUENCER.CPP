//////////////////////////////////////////////////////////////////////////
// CSequencer implementation file
//
// This class encapsulates the MCI API for the MIDI Player device
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

#include "stdafx.h"
#include "Sequencer.h"

//////////////////////////////////////////////////////////////////////////
// CSequencer implementation
//
const DWORD CSequencer::FormatMilliseconds = MCI_FORMAT_MILLISECONDS;
const DWORD CSequencer::FormatSmpte24	   = MCI_FORMAT_SMPTE_24;
const DWORD CSequencer::FormatSmpte25	   = MCI_FORMAT_SMPTE_25;
const DWORD CSequencer::FormatSmpte30	   = MCI_FORMAT_SMPTE_30;
const DWORD CSequencer::FormatSmpte30drop  = MCI_FORMAT_SMPTE_30DROP;
const DWORD CSequencer::FormatSongPtr	   = MCI_SEQ_FORMAT_SONGPTR;

const DWORD CSequencer::StatusCurrentTrack = MCI_STATUS_CURRENT_TRACK;
const DWORD CSequencer::StatusDivisionType = MCI_SEQ_STATUS_DIVTYPE;
const DWORD CSequencer::StatusLength	   = MCI_STATUS_LENGTH;
const DWORD CSequencer::StatusMaster	   = MCI_SEQ_STATUS_MASTER;
const DWORD CSequencer::StatusOffset	   = MCI_SEQ_STATUS_OFFSET;
const DWORD CSequencer::StatusPort		   = MCI_SEQ_STATUS_PORT;
const DWORD CSequencer::StatusPosition	   = MCI_STATUS_POSITION;
const DWORD CSequencer::StatusSlave		   = MCI_SEQ_STATUS_SLAVE;
const DWORD CSequencer::StatusStart		   = MCI_STATUS_START;
const DWORD CSequencer::StatusTempo		   = MCI_SEQ_STATUS_TEMPO;

const DWORD CSequencer::InfoCopyright = MCI_INFO_COPYRIGHT;
const DWORD CSequencer::InfoFile	  = MCI_INFO_FILE;
const DWORD CSequencer::InfoName	  = MCI_INFO_NAME;	

const DWORD CSequencer::SeqNone	   = MCI_SEQ_NONE;
const DWORD CSequencer::MidiMapper = MIDI_MAPPER;
const DWORD CSequencer::SeqFile = MCI_SEQ_FILE;

const DWORD CSequencer::SeqSmpte = MCI_SEQ_SMPTE;
const DWORD CSequencer::SeqMidi  = MCI_SEQ_MIDI;

const DWORD CSequencer::DivPpqn		   = MCI_SEQ_DIV_PPQN;
const DWORD CSequencer::DivSmpte24	   = MCI_SEQ_DIV_SMPTE_24;
const DWORD CSequencer::DivSmpte25	   = MCI_SEQ_DIV_SMPTE_25;
const DWORD CSequencer::DivSmpte30	   = MCI_SEQ_DIV_SMPTE_30;
const DWORD CSequencer::DivSmpte30drop = MCI_SEQ_DIV_SMPTE_30DROP;

// Open
DWORD CSequencer::Open(LPCSTR lpszFileName, BOOL bShareable /*=FALSE*/) 
{
	DWORD dwReturn;
	MCI_OPEN_PARMS mciOpenParms;

	// Opens a device by specifying a device-type constant.
	mciOpenParms.lpstrDeviceType = (LPCSTR) MCI_DEVTYPE_SEQUENCER;
	mciOpenParms.lpstrElementName = lpszFileName;

	DWORD dwFlags = MCI_OPEN_TYPE|MCI_OPEN_TYPE_ID|MCI_WAIT|MCI_OPEN_ELEMENT;
	if (bShareable) dwFlags |= MCI_OPEN_SHAREABLE;

	dwReturn = SendCommand(MCI_OPEN, dwFlags, 
			(DWORD)(LPVOID) &mciOpenParms);

	if (dwReturn == 0) {
		// The device opened successfully; get the device ID.
		m_wDeviceID = mciOpenParms.wDeviceID;		
	}
	
	return dwReturn;
}

// Saves the opened file
DWORD CSequencer::Save(LPCSTR lpszFileName) {
	MCI_SAVE_PARMS mciSaveParms;

	mciSaveParms.lpfilename = lpszFileName;

	return SendCommand(MCI_SAVE, MCI_SAVE_FILE, (DWORD) &mciSaveParms);
}

// Sets the device time format.
DWORD CSequencer::SetTimeFormat(DWORD dwTimeFormat) {   
	MCI_SET_PARMS mciSetParms;
	
	mciSetParms.dwTimeFormat = dwTimeFormat;

	return SendCommand(MCI_SET, 
        	MCI_SET_TIME_FORMAT, (DWORD)(LPVOID) &mciSetParms);    
}

// Sets the MIDI port
DWORD CSequencer::SetPort(DWORD dwPort) {   
	MCI_SEQ_SET_PARMS mciSeqSetParms;
	/*
	MCI_SEQ_NONE 
	Closes the previously used port (if any). 
	The sequencer behaves exactly the same as
	if a port were open, except no MIDI message is sent.
	MIDI_MAPPER 
	Sets the port opened to the MIDI mapper.
	*/
	mciSeqSetParms.dwPort = dwPort;

	return SendCommand(MCI_SET, 
        	MCI_SEQ_SET_PORT, (DWORD)(LPVOID) &mciSeqSetParms);    
}

// Sets the song tempo
DWORD CSequencer::SetTempo(DWORD dwTempo) {   
	MCI_SEQ_SET_PARMS mciSeqSetParms;

	mciSeqSetParms.dwTempo = dwTempo;

	return SendCommand(MCI_SET, 
        	MCI_SEQ_SET_TEMPO, (DWORD)(LPVOID) &mciSeqSetParms);    
}

// Changes the SMPTE offset of a sequence to that specified by
// the dwOffset parameter.
// This affects only sequences with a SMPTE division type.
DWORD CSequencer::SetOffset(DWORD dwOffset) {
	MCI_SEQ_SET_PARMS mciSeqSetParms;

	mciSeqSetParms.dwOffset = dwOffset;

	return SendCommand(MCI_SET, 
        	MCI_SEQ_SET_OFFSET, (DWORD)(LPVOID) &mciSeqSetParms);    
}

// Sets the sequencer as a source of synchronization data
DWORD CSequencer::SetMaster(DWORD dwSynchType) {
	MCI_SEQ_SET_PARMS mciSeqSetParms;

	mciSeqSetParms.dwMaster = dwSynchType;

	return SendCommand(MCI_SET, 
        	MCI_SEQ_SET_MASTER, (DWORD)(LPVOID) &mciSeqSetParms);    
}

// Retrieves the synchronization type used for master operation
DWORD CSequencer::GetMaster() {
	return GetStatus(StatusMaster);
}

// Sets the sequencer to receive synchronization data
DWORD CSequencer::SetSlave(DWORD dwSynchType) {
	MCI_SEQ_SET_PARMS mciSeqSetParms;

	mciSeqSetParms.dwSlave = dwSynchType;

	return SendCommand(MCI_SET, 
        	MCI_SEQ_SET_SLAVE, (DWORD)(LPVOID) &mciSeqSetParms);    
}

// Retrieves the synchronization type used for slave operation
DWORD CSequencer::GetSlave() {
	return GetStatus(StatusSlave);
}

// Retrieves the current time format
DWORD CSequencer::GetTimeFormat() {
	return GetStatus(MCI_STATUS_TIME_FORMAT);
}

// Plays from a position to another
DWORD CSequencer::Play(DWORD dwFrom, DWORD dwTo, BOOL bAsync /*=TRUE*/)
{
	MCI_PLAY_PARMS mciPlayParms;
    mciPlayParms.dwFrom = dwFrom;
	mciPlayParms.dwTo = dwTo;
	
	DWORD dwFlags = MCI_FROM | MCI_TO;
	if (bAsync) {		
		mciPlayParms.dwCallback = (DWORD) m_hMainWnd;
		dwFlags |= MCI_NOTIFY;
	}

	return SendCommand(MCI_PLAY, dwFlags, (DWORD)(LPVOID) &mciPlayParms);
}

// Plays a song
DWORD CSequencer::Play(BOOL bAsync /*=TRUE*/)
{
	MCI_PLAY_PARMS mciPlayParms;
	
	DWORD dwFlags = 0L;
	if (bAsync) {		
		mciPlayParms.dwCallback = (DWORD) m_hMainWnd;
		dwFlags |= MCI_NOTIFY;
	}

	return SendCommand(MCI_PLAY, dwFlags, (DWORD)(LPVOID) &mciPlayParms);
}

// Stops playback
DWORD CSequencer::Stop() {
	MCI_GENERIC_PARMS mciGenericParms;

	mciGenericParms.dwCallback = (DWORD) m_hMainWnd;

	return SendCommand(MCI_STOP, 0, (DWORD) &mciGenericParms);
}

// Pauses playback
DWORD CSequencer::Pause() {
	MCI_GENERIC_PARMS mciGenericParms;

	mciGenericParms.dwCallback = (DWORD) m_hMainWnd;
	
	return SendCommand(MCI_PAUSE, 0, (DWORD) &mciGenericParms);
}

// Resumes playback
DWORD CSequencer::Resume() {
	MCI_GENERIC_PARMS mciGenericParms;

	mciGenericParms.dwCallback = (DWORD) m_hMainWnd;
	
	return SendCommand(MCI_RESUME, 0, (DWORD) &mciGenericParms);
}

// Retrieves the starting position of a track
DWORD CSequencer::GetTrackPos(DWORD dwTrack) {	
	return GetTrackInfo(dwTrack, StatusPosition);	
}

// Retrieves the length of a track
DWORD CSequencer::GetTrackLength(DWORD dwTrack) {	
	return GetTrackInfo(dwTrack, StatusLength);
}

// Retrieves the total song length
DWORD CSequencer::GetSongLength(DWORD dwTrack) {	
	return GetStatus(StatusLength);
}

// Retrieves a track information
DWORD CSequencer::GetTrackInfo(DWORD dwTrack, DWORD dwItem) {	
	MCI_STATUS_PARMS mciStatusParms;
	mciStatusParms.dwCallback = (DWORD) m_hMainWnd;
	mciStatusParms.dwItem = dwItem;
	mciStatusParms.dwTrack = dwTrack;
	mciStatusParms.dwReturn = 0;
	
	SendCommand(MCI_STATUS, 
		MCI_STATUS_ITEM|MCI_TRACK, (DWORD) &mciStatusParms);
		
	return mciStatusParms.dwReturn;
}

// Retrieves the current track
DWORD CSequencer::GetCurrentTrack() {
	return GetStatus(StatusCurrentTrack);
}

// Retrieves the current position
DWORD CSequencer::GetCurrentPos() {
	return GetStatus(StatusPosition);
}

// Retrieves the starting position
DWORD CSequencer::GetStartPos() {
	return GetStatus(StatusStart);
}

// Gets the number of playable tracks
DWORD CSequencer::GetNumberOfTracks() {
	return GetStatus(StatusNumberOfTracks);
}

// Retrieves the MIDI port
DWORD CSequencer::GetPort() {
	return GetStatus(StatusPort);
}

// Retrieves the tempo
DWORD CSequencer::GetTempo() {
	return GetStatus(StatusTempo);
}

// Retrieves the SMTPE offset
DWORD CSequencer::GetOffset() {
	return GetStatus(StatusOffset);
}

// Seek to a specified position
DWORD CSequencer::Seek(DWORD dwTo, BOOL bAsync /*=FALSE*/) {
	return Seek(dwTo, MCI_TO, bAsync);
}

// Seek to end
DWORD CSequencer::SeekToStart(BOOL bAsync /*=FALSE*/) {
	return Seek(0, MCI_SEEK_TO_START, bAsync);
}

// Seek to start
DWORD CSequencer::SeekToEnd(BOOL bAsync /*=FALSE*/) {
	return Seek(0, MCI_SEEK_TO_END, bAsync);
}

// Generic Seek
DWORD CSequencer::Seek(DWORD dwTo, DWORD dwFlags, BOOL bAsync) {	
	MCI_SEEK_PARMS mciSeekParms;

	if (bAsync) {
		mciSeekParms.dwCallback = (DWORD) m_hMainWnd;
		dwFlags |= MCI_NOTIFY;
	}

	mciSeekParms.dwTo = dwTo;
    	
	return SendCommand(MCI_SEEK, dwFlags, (DWORD) &mciSeekParms);	
}

// Checks if the device is Ready to be operated
BOOL CSequencer::IsReady() {
	return GetStatus(StatusReady);
}

// Generic MCI_SET command
DWORD CSequencer::Set(DWORD dwWhat)
{
	MCI_SET_PARMS mciSetParms;

	mciSetParms.dwCallback = (DWORD) m_hMainWnd;
	
	return SendCommand(MCI_SET, dwWhat, (DWORD) &mciSetParms);
}

// Generic MCI_GETDEVCAPS_ITEM command
DWORD CSequencer::GetDevCapsItem(DWORD dwItem) {	
	MCI_GETDEVCAPS_PARMS mciCapsParms;

	mciCapsParms.dwCallback = (DWORD) m_hMainWnd;
	mciCapsParms.dwItem = dwItem;
	mciCapsParms.dwReturn = 0;
	
	SendCommand(MCI_GETDEVCAPS, MCI_GETDEVCAPS_ITEM,
		(DWORD) &mciCapsParms);
	
	return mciCapsParms.dwReturn;
}


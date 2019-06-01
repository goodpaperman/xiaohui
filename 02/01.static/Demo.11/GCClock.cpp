#include "stdafx.h"
#include "GCClock.h"

CGCClock::CGCClock() : CGCColorStatic()
{
	m_b24hr = FALSE;
	m_uiHour = 0;
	m_uiMinutes = 0;
	m_bAlarmSet = FALSE;
	m_bAlarmRunning = FALSE;
	m_bAlarmActivated = FALSE;
}


CGCClock::~CGCClock()
{
}


BEGIN_MESSAGE_MAP(CGCClock, CGCColorStatic)
	ON_WM_TIMER()
END_MESSAGE_MAP()


void CGCClock::OnTimer(UINT nIDEvent) 
{
	// The CGCClock class is derived from the CGCColorStatic class.
	// Since the CGCColorStatic class provides the capability to flash the background
	// or text using timer events, we must distinguish between CGCColorStatic timer events
	// and the CGCClock's clock update timer event. Verify that the current timer
	// event is the CGCClock class' update event.  If it isn't route it on to the
	// parent class' OnTimer() event handler because that may be one of the 
	// CGCColorStatic class' flashing timer events.
	
	if (nIDEvent != CLOCK_UPDATE_TIMER_ID) CGCColorStatic::OnTimer(nIDEvent);

	// If we are here then the current timer event is the clock's update event.

	// Get the current time.
	GetLocalTime(&m_CurrentDateTime);

	// Format it for display.
	FormatTime();

	// Display the time.
	SetWindowText(m_FormattedTime);

	// If it is time for the alarm, initiate flashing of the background
	// by calling the inherited FlashBackground() method.

	if ( (!m_bAlarmRunning) && m_bAlarmSet && m_bAlarmActivated && 
		( (m_CurrentDateTime.wHour >= m_uiHour)
		  &&
		  (m_CurrentDateTime.wMinute >= m_uiMinutes)
		)
	   )
	{
		FlashBackground(TRUE,FALSE,1);
		m_bAlarmRunning = TRUE;
		// Here is where you would add sound for the alarm.
	}
}



void CGCClock::FormatTime()
{

	if (m_b24hr)
		m_FormattedTime.Format("%02d:%02d:%02d",
                               m_CurrentDateTime.wHour,
							   m_CurrentDateTime.wMinute,
							   m_CurrentDateTime.wSecond);
	else
	{
		if (m_CurrentDateTime.wHour > 12)
		{
			UINT th;
			th = m_CurrentDateTime.wHour - 12;
			m_FormattedTime.Format("%2d:%02d:%02d p.m.",
				                   th,
								   m_CurrentDateTime.wMinute,
								   m_CurrentDateTime.wSecond);
		}
		else
			m_FormattedTime.Format("%d:%02d:%02d a.m.",
				                   m_CurrentDateTime.wHour,
								   m_CurrentDateTime.wMinute,
								   m_CurrentDateTime.wSecond);

	}

}


BOOL CGCClock::Start()
{
	GetLocalTime(&m_CurrentDateTime);
	FormatTime();
	SetWindowText(m_FormattedTime);
	UINT id = this->SetTimer(CLOCK_UPDATE_TIMER_ID,1000,NULL);
	if (id == 0) return FALSE;

	return TRUE;
}

void CGCClock::Format(const BOOL bTwentyFourHour)
{
	m_b24hr = bTwentyFourHour;
	FormatTime();
	SetWindowText(m_FormattedTime);
}






void CGCClock::GetAlarmTime(UINT &Hour, UINT &Minutes, BOOL& Active) const
{
	Hour = m_uiHour;
	Minutes = m_uiMinutes;
	Active = m_bAlarmRunning;
}

BOOL CGCClock::SetAlarm(const UINT Hour, const UINT Minutes)
{
	if ( Hour <= 0 ) return FALSE;

	m_bAlarmSet = TRUE;

	if (m_bAlarmRunning)
	{
		// Since we are setting a new alarm time, kill the current alarm
		// if it is active (going off).
		FlashBackground(FALSE,FALSE);
		m_bAlarmRunning = FALSE;
	}

	m_uiHour = Hour;
	m_uiMinutes = Minutes;

	return TRUE;
}

BOOL CGCClock::ActivateAlarm(const BOOL bOn)
{
	BOOL prev = m_bAlarmActivated;
	m_bAlarmActivated = bOn;
	return prev;
}

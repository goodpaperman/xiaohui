// ****************************************************************************
// ****************************************************************************
//
//                                    CGCClock
//                           Developed By: George Chastain
//                                    11/10/99
//
//                                   Version 1.0
//
// Derived from the CGCColorStatic class, this class provides the ability to
// quickly include a clock in your GUI/MMI.  Since it is publicly derived from
// the CGCColorStatic class, all the CGCColorStatic class' methods are 
// available for controlling the look of the clock.
//
// ****************************************************************************
// ****************************************************************************

#if !defined(__CGCClock__)
#define __CGCClock__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "GCColorStatic.h"


class CGCClock : public CGCColorStatic
{
public:

	
	// Start() - Must be called to initialize and start the clock.
	//           Returns FALSE if a failure occurred starting the clock.
	//
	BOOL Start();


	// NOTE: As of Version 1.0 of this class, audible signals for the Alarm are
	// not supported.  This will be added in a future version.
	//

	// SetAlarm() - Currently, all this does is flash the background at the
	// specified time.  This could be modified to add sound.
	// Function returns TRUE if Alarm time successfully set. FALSE if not.
	//
	BOOL SetAlarm(const UINT Hour, const UINT Minutes);

	// GetAlarmTime() - Returns the Hour and Minutes for which the alarm has been set.
	//                  If the Alarm has not been set, 0 is returned for both Hour
	//                  and Minutes.  Active returns TRUE if the Alarm is set to go off.
	//					Active returns FALSE if the Alarm has been deactivated.
	//
	void GetAlarmTime(UINT& Hour, UINT& Minutes, BOOL& Active) const;

	// ActivateAlarm() - Used to turn the alarm on/off.  If this is called with bOn
	// set to TRUE, then the Alarm will "sound" when the time set by calling SetAlarm()
	// is reached.  If ActivateAlarm() is called with bOn set to FALSE, then the
	// alarm will not sound when the time specified by SetAlarm() is reached.
	//
	BOOL ActivateAlarm(const BOOL bOn = TRUE);
	
	// Format() - Set the display of the clock to 12-hour mode or 24-hour
	// (also commonly referred to as Military Time) format.
	//
	void Format(const BOOL bTwentyFourHour = FALSE);

	CGCClock();
	~CGCClock();
protected:
	afx_msg void OnTimer(UINT nIDEvent);
	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bAlarmActivated;
	BOOL m_bAlarmRunning;

	enum {CLOCK_UPDATE_TIMER_ID = 2};	// We use id of 2 because 1 is reserved for CGCColorStatic.

	CString m_FormattedTime;		// Time formatted for display.

	BOOL m_b24hr;					// Are we to display in 24-Hour (military) time format?

	void FormatTime();				// Used to format the time for display.

	SYSTEMTIME m_CurrentDateTime;	// Current LOCAL time.

	// Variables used for the alarm. 
	BOOL m_bAlarmSet;	// Is the alarm set?
	UINT m_uiHour;		// What time is the alarm set for?
	UINT m_uiMinutes;	

};

#endif
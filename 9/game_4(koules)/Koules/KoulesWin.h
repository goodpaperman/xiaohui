#ifndef KOULESWIN_H
#define KOULESWIN_H


#include "DirectDrawWin.h"
#define TIMER 10

class KoulesWin : public DirectDrawWin
{
public:
	int m_fps;
	DWORD m_pc;
	void DrawFPS(CDC * pDC);
	DWORD m_tc;
	KoulesWin();
protected:
	//{{AFX_MSG(KoulesWin)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnAppExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int SelectInitialDisplayMode();
	BOOL CreateCustomSurfaces();
	void DrawScene();
	void RestoreSurfaces();
	BOOL m_key[4];//uslr
private:
};


#endif

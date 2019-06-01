/***********************************************************
*  rcfiles.c saving and loading of rc files                *
 ***********************************************************/
#include "koules.h"

void
save_rc ()
{
	CString s;
	s.LoadString(IDS_REGSUB);
	HKEY hk=NULL;
	DWORD d;
	if(RegOpenKeyEx(HKEY_CURRENT_USER,s,0,KEY_READ,&hk)!=ERROR_SUCCESS)
	{
		RegCreateKeyEx(HKEY_CURRENT_USER,s,0,NULL,REG_OPTION_NON_VOLATILE,
			KEY_ALL_ACCESS,NULL,&hk,&d);
	}
	RegSetValueEx(hk,"keys",0,REG_BINARY,(LPBYTE)keys,sizeof(keys));
	RegSetValueEx(hk,"rotation",0,REG_BINARY,(LPBYTE)rotation,sizeof(rotation));
	d=mouseplayer;
	RegSetValueEx(hk,"mouseplayer",0,REG_DWORD,(LPBYTE)&d,sizeof(DWORD));
	d=maxlevel;
	RegSetValueEx(hk,"maxlevel",0,REG_DWORD,(LPBYTE)&d,sizeof(DWORD));
	d=lastlevel;
	RegSetValueEx(hk,"lastlevel",0,REG_DWORD,(LPBYTE)&d,sizeof(DWORD));
	d=nrockets;
	RegSetValueEx(hk,"nrockets",0,REG_DWORD,(LPBYTE)&d,sizeof(DWORD));
	d=gameplan;
	RegSetValueEx(hk,"gameplan",0,REG_DWORD,(LPBYTE)&d,sizeof(DWORD));
	d=difficulty;
	RegSetValueEx(hk,"difficulty",0,REG_DWORD,(LPBYTE)&d,sizeof(DWORD));
	if(hk)
		RegCloseKey(hk);
}


void
load_rc ()
{
	CString st;
	st.LoadString(IDS_REGSUB);
	HKEY hk=NULL;
	DWORD d;
	if(RegOpenKeyEx(HKEY_CURRENT_USER,st,0,KEY_READ,&hk)!=ERROR_SUCCESS)
	{
		RegCreateKeyEx(HKEY_CURRENT_USER,st,0,NULL,REG_OPTION_NON_VOLATILE,
			KEY_ALL_ACCESS,NULL,&hk,&d);
		return;//use default!
	}
	ULONG p;
	ULONG s;
	s=sizeof(keys);
	RegQueryValueEx(hk,"keys",0,&p,(LPBYTE)keys,&s);
	s=sizeof(rotation);
	RegQueryValueEx(hk,"rotation",0,&p,(LPBYTE)rotation,&s);
	s=sizeof(DWORD);
	RegQueryValueEx(hk,"mouseplayer",0,&p,(LPBYTE)&d,&s);
	mouseplayer=d;
	s=sizeof(DWORD);
	RegQueryValueEx(hk,"maxlevel",0,&p,(LPBYTE)&d,&s);
	maxlevel=d;
	s=sizeof(DWORD);
	RegQueryValueEx(hk,"lastlevel",0,&p,(LPBYTE)&d,&s);
	lastlevel=d;
	s=sizeof(DWORD);
	RegQueryValueEx(hk,"nrockets",0,&p,(LPBYTE)&d,&s);
	nrockets=d;
	s=sizeof(DWORD);
	RegQueryValueEx(hk,"gameplan",0,&p,(LPBYTE)&d,&s);
	gameplan=d;
	s=sizeof(DWORD);
	RegQueryValueEx(hk,"difficulty",0,&p,(LPBYTE)&d,&s);
	difficulty=d;
	if(hk)
		RegCloseKey(hk);
}

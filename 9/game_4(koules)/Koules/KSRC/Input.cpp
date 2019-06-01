#include "koules.h"
#include "..\DirectDrawWin.h"
#include "input.h"
#pragma comment(lib,"dinput.lib")

BYTE key_press[256]={0};//push down and release ,a action
BYTE key_state[256]={0};//pushing ,a state
DIMOUSESTATE MouseState;//state
BOOL mouse_button[4]={0};//action

int mousespeed=1;
int mousethreshold1=4;
int mousethreshold2=0;

BOOL MouseAcquire=FALSE;
BOOL KeyAcquire=FALSE;
LPDIRECTINPUT lpDi=NULL;
GUID KeyGUID;
GUID MouseGUID;
LPDIRECTINPUTDEVICE DIKey=NULL;
LPDIRECTINPUTDEVICE DIMouse=NULL;
BOOL MouseFound=FALSE;
BOOL KeyFound=FALSE;
int MouseX=400;
int MouseY=300;

extern void SetCurPos(int x,int y)
{
	MouseX=x;
	MouseY=y;
}

extern INLINE IsPressing(BYTE scancode)
{
	return key_state[scancode]!=0;
}

BOOL CALLBACK DIEnumDevicesPro(LPDIDEVICEINSTANCE lpddi,LPVOID pvRef)
{
	
	if(GET_DIDEVICE_TYPE(lpddi->dwDevType)==DIDEVTYPE_KEYBOARD)
	{
		KeyGUID=lpddi->guidProduct;
		KeyFound=TRUE;
	}
	if(GET_DIDEVICE_TYPE(lpddi->dwDevType)==DIDEVTYPE_MOUSE)
	{
		MouseGUID=lpddi->guidProduct;
		MouseFound=TRUE;
	}

	if(MouseFound && KeyFound)
		return DIENUM_STOP;
	else
		return DIENUM_CONTINUE;
}

extern BOOL InitDirectInput()
{
	if(DirectInputCreate(AfxGetInstanceHandle(),DIRECTINPUT_VERSION,&lpDi,NULL)!=DI_OK)
		return FALSE;
	
	if(lpDi->EnumDevices(0,(LPDIENUMDEVICESCALLBACK)DIEnumDevicesPro,NULL,DIEDFL_ATTACHEDONLY)!=DI_OK)
		return FALSE;
	
	if(lpDi->CreateDevice(KeyGUID,&DIKey,NULL)!=DI_OK)
		return FALSE;
	if(lpDi->CreateDevice(MouseGUID,&DIMouse,NULL)!=DI_OK)
		return FALSE;
	
	if(DIKey->SetCooperativeLevel(GetDDWin()->m_hWnd,DISCL_NONEXCLUSIVE|DISCL_FOREGROUND)!=DI_OK)
		return FALSE;
	if(DIMouse->SetCooperativeLevel(GetDDWin()->m_hWnd,DISCL_NONEXCLUSIVE|DISCL_FOREGROUND)!=DI_OK)
		return FALSE;
	
	if(DIKey->SetDataFormat(&c_dfDIKeyboard)!=DI_OK)
		return FALSE;
	if(DIMouse->SetDataFormat(&c_dfDIMouse)!=DI_OK)
		return FALSE;
	
	GetDDWin()->SetForegroundWindow();
	if(DIKey->Acquire()!=DI_OK)
		return FALSE;
	KeyAcquire=TRUE;
	if(DIMouse->Acquire()!=DI_OK)
		return FALSE;
	MouseAcquire=TRUE;
	UpdateInput();
	
	//get the mouse speed!
	CString s;
	s.LoadString(IDS_MOUSEREG);
	BYTE buff[255];
	int t;
	HKEY hk=NULL;
	DWORD bufflen=255;
	DWORD p;

	if(RegOpenKeyEx(HKEY_CURRENT_USER,s,0,KEY_READ,&hk)!=ERROR_SUCCESS)
		return TRUE;
	bufflen=255;
	if(RegQueryValueEx(hk,"MouseSpeed",0,&p,buff,&bufflen)==ERROR_SUCCESS)
	{
		t=atoi((char *)buff);
		if(t>=0 && t<3)//can't too fast
			mousespeed=t;
	}
	bufflen=255;
	if(RegQueryValueEx(hk,"MouseThreshold1",0,&p,buff,&bufflen)==ERROR_SUCCESS)
	{
		t=atoi((char *)buff);
		if(t>=0 && t<=10)//can't too slow
			mousethreshold1=t;
	}
	bufflen=255;
	if(RegQueryValueEx(hk,"MouseThreshold2",0,&p,buff,&bufflen)==ERROR_SUCCESS)
	{
		t=atoi((char *)buff);
		if(t>=0 && t<=20)//can't too slow
			mousethreshold2=t;
	}
	return TRUE;
}

extern BOOL ReleaseDirectInput()
{
	if(KeyAcquire)
	{
		DIKey->Unacquire();
		KeyAcquire=FALSE;
	}
	if(MouseAcquire)
	{
		DIMouse->Unacquire();
		MouseAcquire=FALSE;
	}
	if(DIKey)
		DIKey->Release();
	if(DIMouse)
		DIMouse->Release();
	lpDi->Release();
	return FALSE;
}

extern void UpdateInput(void)
{
	HRESULT dirval;
	while(1)
	{
		dirval=DIKey->GetDeviceState(256,key_state);
		if(dirval==DIERR_NOTACQUIRED||dirval==DIERR_INPUTLOST)
			DIKey->Acquire();
		else
			break;
	}
	while(1)
	{
		dirval=DIMouse->GetDeviceState(sizeof(MouseState),&MouseState);
		if(dirval==DIERR_NOTACQUIRED||dirval==DIERR_INPUTLOST)
			DIMouse->Acquire();
		else
			break;
	}
	int dx=(short)MouseState.lX;
	int dy=(short)MouseState.lY;
	switch(mousespeed)
	{
	case 0:
		break;
	case 1:
		if(abs(dx)>mousethreshold1)
			dx*=2;
		if(abs(dy)>mousethreshold1)
			dy*=2;
		break;
	default:
		if(abs(dx)>mousethreshold2)
			dx*=3;
		else if(abs(dx)>mousethreshold1)
			dx*=2;
		if(abs(dy)>mousethreshold2)
			dy*=3;
		else if(abs(dy)>mousethreshold1)
			dy*=2;
		break;
	}
	MouseX+=dx;
	MouseY+=dy;
	int w,h;
	w=GetDDWin()->GetDisplayRect().Width();
	h=GetDDWin()->GetDisplayRect().Height();
	if(MouseX<0)
		MouseX=0;
	if(MouseX>=w)
		MouseX=w-1;
	if(MouseY<0)
		MouseY=0;
	if(MouseY>=h)
		MouseY=h-1;
}

extern int mouse_getbutton()
{
	if(MouseState.rgbButtons[0])
		return 1;
	if(MouseState.rgbButtons[1])
		return 2;
	if(MouseState.rgbButtons[2])
		return 3;
	if(MouseState.rgbButtons[3])
		return 4;
	return 0;
}

extern int mouse_getx()
{
	return MouseX;
}

extern int mouse_gety()
{
	return MouseY;
}

extern int IsPressed(unsigned char c)
{
	if(key_state[c] && !key_press[c])
	{
		key_press[c]=TRUE;
		return TRUE;
	}
	else if(!key_state[c] && key_press[c])
	{
		key_press[c]=FALSE;
	}
	return FALSE;
}

/*here is probably bug....
   some users reported that these functions not work...
   probably sometimes some keys are reported as pressed */

extern int Pressed ()
{
	int             z;
	for(int i=0;i<4;i++)
	{
		if(MouseState.rgbButtons[i] && !mouse_button[i])
		{
			mouse_button[i]=TRUE;
			return 1;
		}
		else if(!MouseState.rgbButtons[i] && mouse_button[i])
		{
			mouse_button[i]=FALSE;
		}
	}
	for (z = 0; z < 256; z++)
		if (IsPressed (z))
			return 1;
  return (0);
}

extern  int GetKey ()
{
	int             z, k = 0;
	if (MouseButtons ())
		return (1);
	for (z = 0; z < 256; z++)
		if (IsPressed (z))
		{
			if (k)
				return (0);
			k = z;
		}
	return (k);
}

/*==========================================================
		Move Pic.cpp -- A move-picture game with SDK
			Soft Zealot (R) Robin Hood, 2001						
	  SoftZealot@china.com		Soft_Zealot@china.com
==========================================================*/

#include <windows.h>

// ȫ�ֱ���
HINSTANCE					hInst ;
TCHAR						szAppName[] = TEXT ("���ƴͼ") ;
static TCHAR				szFileName [MAX_PATH],
							szTitleName [MAX_PATH] ;
static TCHAR				szFilter[] = TEXT ("Bitmap Files (*.BMP)\0*.bmp\0")
										TEXT ("All Files (*.*)\0*.*\0\0") ;
static TCHAR				szWinGame[] = TEXT ("��ϲ��ϲ����ʤ���ˣ�");

// ���ں���
LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;
BOOL CALLBACK AboutDlgProc (HWND, UINT, WPARAM, LPARAM) ;

// ��λͼ�ļ�����λͼ����
HBITMAP CreateBitmapObjectFromDibFile (HDC, PTSTR) ;

// ��ʼ��OPENFILENAME�ṹ
void InitOfnStruct (OPENFILENAME&, HWND) ;
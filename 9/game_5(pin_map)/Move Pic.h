/*==========================================================
		Move Pic.cpp -- A move-picture game with SDK
			Soft Zealot (R) Robin Hood, 2001						
	  SoftZealot@china.com		Soft_Zealot@china.com
==========================================================*/

#include <windows.h>

// 全局变量
HINSTANCE					hInst ;
TCHAR						szAppName[] = TEXT ("奇幻拼图") ;
static TCHAR				szFileName [MAX_PATH],
							szTitleName [MAX_PATH] ;
static TCHAR				szFilter[] = TEXT ("Bitmap Files (*.BMP)\0*.bmp\0")
										TEXT ("All Files (*.*)\0*.*\0\0") ;
static TCHAR				szWinGame[] = TEXT ("恭喜恭喜，你胜利了！");

// 窗口函数
LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;
BOOL CALLBACK AboutDlgProc (HWND, UINT, WPARAM, LPARAM) ;

// 从位图文件创建位图对象
HBITMAP CreateBitmapObjectFromDibFile (HDC, PTSTR) ;

// 初始化OPENFILENAME结构
void InitOfnStruct (OPENFILENAME&, HWND) ;
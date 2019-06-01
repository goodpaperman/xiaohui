/*==========================================================
		Move Pic.cpp -- A move-picture game with SDK
			Soft Zealot (R) Robin Hood, 2001						
	  SoftZealot@china.com		Soft_Zealot@china.com

	====================================================
	我正在学习SDK编程，尝试编写了一个小游戏，因为我讨厌
	一些无聊的编程问题，我喜欢有意思的编程工作 :)

	这个游戏完全是用SDK编写的，没有涉及MFC，其中打开图片
	的函数是Charles Petzold的《Windows程序设计》一书中的
	源代码，我只不过加上了注释，看懂了意思而已。其他的代
	码是我自己编写的，你可以任意使用其中的代码。

	欢迎大家和我讨论编程的问题，你可以在www.csdn.net的专
	家门诊的vc部分找到我，我的id是Soft_Zealot或者
	SoftZealot， :)，不好意思，水平不够只好多注册几个。

	如果你发现了bug或者找到了任何能够改进程序性能或者任何
	能够使code更精炼的方法，请你通知我，我会很高兴能够更
	加完善这个游戏。

	====================================================
	有待完成:
	1.胜利时通知游戏者游戏时间
	3.可不可以找到寻找最佳解的算法
	4.如何加入预览功能，可不可以采用类似Splash方法

	====================================================
	bugs :
	1.显示图片后每个Static控件排列不整齐
	2.由于对图像处理和windows底层工作原理还不是很清楚，所
	以有可能会有内存泄漏
==========================================================*/

#include <windows.h>
#include <commdlg.h>
#include <time.h>

#include "Move Pic.h"
#include "resource.h"

/*==========================================================
					应用程序入口函数
==========================================================*/
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
					PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szMenuName[] = TEXT ("MainMenu") ;
	HWND         hwnd ;
	MSG          msg ;
	WNDCLASS     wndclass ;
	
	// save the application's HINSTANCE
	hInst = hInstance ;

	wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
	wndclass.lpfnWndProc   = WndProc ;		// WndProc !!! here
	wndclass.cbClsExtra    = 0 ;
	wndclass.cbWndExtra    = 0 ;
	wndclass.hInstance     = hInstance ;
	wndclass.hIcon         = LoadIcon (hInstance, "AppIcon") ;	// how to load self-cus icon
	wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
	wndclass.hbrBackground = (HBRUSH) GetStockObject (LTGRAY_BRUSH) ;
	wndclass.lpszMenuName  = szMenuName ;
	wndclass.lpszClassName = szAppName ;
	
	if (!RegisterClass (&wndclass))
	{
		MessageBox (NULL, TEXT ("This program requires Windows NT!"), 
					szAppName, MB_ICONERROR) ;
		return 0 ;
	}
	
	// Caculate the window's size and position, I don't like huge_window :-)
	int cxWindow, cyWindow;
	cxWindow = GetSystemMetrics (SM_CXSCREEN) / 3;
	cyWindow = GetSystemMetrics (SM_CYSCREEN) / 3;
	
	hwnd = CreateWindow (szAppName,						// window class name
						TEXT ("奇幻拼图  Soft Zealot"),	// window caption
						WS_OVERLAPPEDWINDOW,			// window style
						cxWindow,						// initial x position
						cyWindow,						// initial y position
						cxWindow,						// initial x size
						cyWindow,						// initial y size
						NULL,							// parent window handle
						NULL,							// window menu handle
						hInstance,						// program instance handle
						NULL) ;							// creation parameters
	
	ShowWindow (hwnd, iCmdShow) ;
	UpdateWindow (hwnd) ;
	
	// message WM_QUIT cause function GetMessage return 0
	while (GetMessage (&msg, NULL, 0, 0))
	{
		TranslateMessage (&msg) ;
		DispatchMessage (&msg) ;
	}
	
	return msg.wParam ;
}


/*==========================================================
						窗口函数
==========================================================*/
LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HMENU			hMenu ;
	static HWND				hwndPic_Button[4][4] ;
	static int				iStcPos[4][4], iStcPosSave[4][4] ;
	static HBITMAP			hBitmap, hBmpStc ;
	static int				cxClient, cyClient ;
	static int				i, j ;
	static int				idStcClk, idStcBlank ;
	static OPENFILENAME		ofn ;
	static bool				bWinFlag ;
	BITMAP					bitmap ;
	HDC						hdc, hdcMem, hdcStc ;
	PAINTSTRUCT				ps ;
	RECT					rcClient, rcWin ;
	int						iStcClkPos, iStcBlankPos ;
	int						cxScr, cyScr ;
	float					fcxDiv, fcyDiv, fDiv ;

	switch (message)
	{
	case WM_CREATE:
		InitOfnStruct (ofn, hwnd) ;
		// create statics who hold pic
		for (i = 0; i < 4; i++)
			for (j = 0; j < 4; j++)
			{
				hwndPic_Button[i][j] = 
					CreateWindow (TEXT ("Static"), NULL,
								WS_CHILD | WS_VISIBLE | SS_NOTIFY | SS_BITMAP | SS_SUNKEN,
								0, 0, 0, 0,
								hwnd, (HMENU) (4 * i + j), hInst, NULL) ;
				iStcPos[i][j] = 4 * i + j ;
			}

		// 使static控件不能接收mouse点击消息
		bWinFlag = true ;

		// 开始使reset菜单无效
		hMenu = GetMenu (hwnd) ;
		EnableMenuItem (hMenu, IDM_GAME_RESET, MF_GRAYED) ;
		
		return 0 ;

	case WM_SIZE:
		// get client area size
		cxClient = LOWORD (lParam);
		cyClient = HIWORD (lParam);

		// move the statics to the new center
		for (i = 0; i < 4; i++)
			for (j = 0; j < 4; j++)
			{
				MoveWindow (hwndPic_Button[i][j], 
							(iStcPos[i][j] % 4) * cxClient / 4,
							(iStcPos[i][j] / 4) * cyClient / 4,
							cxClient / 4, cyClient / 4, TRUE);
			}
	
	case WM_PAINT:
		hdc = BeginPaint (hwnd, &ps) ;
		
		EndPaint (hwnd, &ps) ;		
		return 0 ;

	// 处理菜单命令
	case WM_COMMAND:
		switch (LOWORD (wParam))
		{	
		case IDM_GAME_RESET:
			/*==================================================
			游戏复位：因为Static已经加载图像，窗口也得到调整，所
			以我们需要打开图像时，每个Static的位置，在这里恢复
			Static的位置就行了。如果以后加入计时功能，就需要复位
			开始时间。
			==================================================*/
			// 恢复初始Static位置信息
			for (i = 0; i < 4; i++)
				for (j = 0; j < 4; j++)
				{
					iStcPos[i][j] = iStcPosSave[i][j] ;
					// 移动Static控件回到初始位置
					MoveWindow (hwndPic_Button[i][j], 
							(iStcPos[i][j] % 4) * cxClient / 4,
							(iStcPos[i][j] / 4) * cyClient / 4,
							cxClient / 4, cyClient / 4, TRUE);
				}

			bWinFlag = false ;

			return 0 ;

        case IDM_PIC_OPEN:
			// 显示打开文件对话框
			if (!GetOpenFileName (&ofn))
				return 0 ;
			
			// 如果已经有一个DIB，删除它
			if (hBitmap)
			{
				DeleteObject (hBitmap) ;
				hBitmap = NULL ;
			}
			
			// 从DIB创建DDB
			SetCursor (LoadCursor (NULL, IDC_WAIT)) ;	// 使用漏斗指针
			ShowCursor (TRUE) ;
			
			hdc = GetDC (hwnd) ;
			hBitmap = CreateBitmapObjectFromDibFile (hdc, szFileName) ;
			ReleaseDC (hwnd, hdc) ;
			
			ShowCursor (FALSE) ;
			SetCursor (LoadCursor (NULL, IDC_ARROW)) ;	// 恢复箭头指针
			
			// 使客户区无效以便稍后重绘
			InvalidateRect (hwnd, NULL, TRUE) ;
			
			if (hBitmap == NULL)
			{
				// 如果不能载入DIB文件，显示错误消息
				MessageBox (hwnd, TEXT ("Cannot load DIB file"), 
							szAppName, MB_OK | MB_ICONEXCLAMATION) ;
			}
			else
			{
				/*==================================================
				在调整窗口大小之前随机安排Static控件的位置，以便调整
				窗口的时候也随机产生了Static的布局。注意分割后的图像
				仍然是按照顺序(id)分配给Static的，随机的只是位置。
				==================================================*/
				srand ( (unsigned int) time (NULL));	// for random seed

				int iRanA, iRanB ;
				for (i = 0; i < 32; i++)
				{
					// 得到 0 -- 16 之间的两个随机数
					iRanA = rand( ) % 16 ;
					do
					{
						iRanB = rand( ) % 16 ;
					}
					while (iRanA == iRanB);

					// 随机调整 Note: index = id   XXX[index] = pos
					iStcBlankPos = iStcPos[iRanA / 4][iRanA % 4] ;
					iStcPos[iRanA / 4][iRanA % 4] = iStcPos[iRanB / 4][iRanB % 4] ;
					iStcPos[iRanB / 4][iRanB % 4] = iStcBlankPos ;
				}

				// 保存开始状态
				for (i = 0; i < 4; i++)
					for (j = 0; j < 4; j++)
					{
						iStcPosSave[i][j] = iStcPos[i][j] ;

						MoveWindow (hwndPic_Button[i][j], 
							(iStcPos[i][j] % 4) * cxClient / 4,
							(iStcPos[i][j] / 4) * cyClient / 4,
							cxClient / 4, cyClient / 4, TRUE);
					}


				/*==================================================
								调整窗口大小以适应图像
				==================================================*/
				GetWindowRect (hwnd, &rcWin);
				GetClientRect (hwnd, &rcClient);

				GetObject (hBitmap, sizeof (BITMAP), &bitmap) ;

				cxScr = GetSystemMetrics (SM_CXSCREEN) ;
				cyScr = GetSystemMetrics (SM_CYSCREEN) ;

				// 计算最合适的显示尺寸
				fcxDiv = 5 * (float) (bitmap.bmWidth) /	(float) (cxScr) / 2 ;
				fcyDiv = 5 * (float) (bitmap.bmHeight) / (float) (cyScr) / 3 ;

				// 获得相对于最合适的显示区域，图像比较宽的一边
				if ( (fDiv = (fcxDiv > fcyDiv) ? fcxDiv : fcyDiv) <= 1)
					fDiv = 1 ;

				// 计算出最合适的大小，并保持图像长宽比例
				cxClient = (int) (bitmap.bmWidth / fDiv) ;
				cyClient = (int) (bitmap.bmHeight / fDiv) ;

				// 重新计算窗口尺寸和坐标
				rcWin.left   -= (cxClient - (rcClient.right - rcClient.left)) / 2 ;
				rcWin.right  += (cxClient - (rcClient.right - rcClient.left)) / 2 ;
				rcWin.top    -= (cyClient - (rcClient.bottom - rcClient.top)) / 2 ;
				rcWin.bottom += (cyClient - (rcClient.bottom - rcClient.top)) / 2 ;

				// 经过多次打开图像后，窗口位置就不再是屏幕中央了。不知道哪里出了问题

				MoveWindow (hwnd, rcWin.left, rcWin.top, rcWin.right - rcWin.left,
							rcWin.bottom - rcWin.top, TRUE);

				/*==================================================
								让Static显示图像
				==================================================*/
				// Static控件应该调整了位置和大小。下面显示图像
				hdc = GetDC (hwnd) ;

				// 把图像载入内存设备表
				hdcMem = CreateCompatibleDC (hdc) ;
				SelectObject (hdcMem, hBitmap) ;
				
				for (i = 0; i < 4; i++)
					for (j = 0; j < 4; j++)
					{
						// 这里以后应该改进，因为我希望空白地方能够出现在随机位置
						if (i * 4 + j == 15)
						{	idStcBlank = 15;
							break ;
						}

						hdcStc = CreateCompatibleDC (hdc) ;
						// 创建新的图像句柄
						hBmpStc = CreateCompatibleBitmap (hdc,
														  cxClient / 4,
														  cyClient / 4);
						SelectObject (hdcStc, hBmpStc) ;

						// 分割图像并拷贝到hdcStc内存设备表
						StretchBlt (hdcStc,	0, 0, 
									cxClient / 4,
									cyClient / 4,
									hdcMem,
									bitmap.bmWidth * j / 4,
									bitmap.bmHeight * i / 4,
									bitmap.bmWidth / 4,
									bitmap.bmHeight / 4,
									SRCCOPY) ;
						
						// 设置对应的Static控件的图像
						SendDlgItemMessage (hwnd,
											4 * i + j, 
											STM_SETIMAGE,
											(WPARAM) IMAGE_BITMAP,
											(LPARAM) hBmpStc) ;

						DeleteObject (hBmpStc) ;	// 删除句柄，这一句可以不要，什么影响？
						DeleteDC (hdcStc) ;
					}

				DeleteDC (hdcMem) ;
				ReleaseDC (hwnd, hdc) ;

				// 使Static控件可以接受mouse点击消息
				bWinFlag = false ;
				// 使reset菜单有效
				EnableMenuItem (hMenu, IDM_GAME_RESET, MF_ENABLED) ;
			}
			
			return 0 ;

		case ID_GAME_EXIT:	// 退出游戏
			SendMessage (hwnd, WM_CLOSE, 0, 0);
			return 0;

		case ID_HELP_ABOUT:
			DialogBox (hInst, TEXT ("AboutDlg"), hwnd, AboutDlgProc) ;
			return 0;

		default:
			if (bWinFlag == false)
			{
				/*==================================================
							Windows通知Static被鼠标点击
				原本应该这样，像菜单项处理一样，使用case id来判断，
				但是我们就要重复16次，为了方便和美观，我就这样处理。
				因为除了菜单消息就是点击Static控件消息了。
				==================================================*/
				// 获得被点击的Static控件的id
				idStcClk = (int) LOWORD (wParam) ;
	
				// 得到BlankStatic和被点击的Static控件的位置信息
				iStcClkPos = iStcPos[idStcClk / 4][idStcClk % 4] ;
				iStcBlankPos = iStcPos[idStcBlank / 4][idStcBlank % 4] ;
			
				// 判断是否应该对点击做出反应
				if (iStcClkPos == iStcBlankPos)		// player click the blank static
					return 0 ;

				if (iStcClkPos != iStcBlankPos - 4 &&	// not up static of blank static
					iStcClkPos != iStcBlankPos + 4 &&	// not below static of blank static
					iStcClkPos != iStcBlankPos - 1 &&	// not left static of blank static
					iStcClkPos != iStcBlankPos + 1)		// not right static of blank static
					return 0 ;

				// 移动Static控件
				MoveWindow (hwndPic_Button[idStcClk / 4][idStcClk % 4],
							(iStcBlankPos % 4) * cxClient / 4,
							(iStcBlankPos / 4) * cyClient / 4,
							cxClient / 4, cyClient / 4, TRUE) ;
	
				MoveWindow (hwndPic_Button[idStcBlank / 4][idStcBlank % 4],
							(iStcClkPos % 4) * cxClient / 4,
							(iStcClkPos / 4) * cyClient / 4,
							cxClient / 4, cyClient / 4, TRUE) ;

				// 更新Static控件的位置信息
				iStcPos[idStcClk / 4][idStcClk % 4] = iStcBlankPos ;
				iStcPos[idStcBlank / 4][idStcBlank / 4] = iStcClkPos ;

				// 判断是否胜利
				int iWinFlag = 0 ;
				for (i = 0; i < 4; i++)
					for (j = 0; j < 4; j++)
						if (iStcPos[i][j] == 4 * i + j)
							iWinFlag ++ ;

				if (iWinFlag == 16)	// win the game
				{
					// 显示祝贺信息
					MessageBox (hwnd, szWinGame, szAppName,
								MB_OK | MB_ICONINFORMATION) ;
					bWinFlag = true ;
				}
			}

			return 0 ;
		}
		break;		

	case WM_DESTROY:
		if (hBitmap)
			DeleteObject (hBitmap) ;

		PostQuitMessage (0) ;
		return 0 ;
	}
	
	return DefWindowProc (hwnd, message, wParam, lParam) ;
}


/*==========================================================
				从位图文件创建位图对象
==========================================================*/
HBITMAP CreateBitmapObjectFromDibFile (HDC hdc, PTSTR szFileName)
{
	BITMAPFILEHEADER * pbmfh ;
	BOOL               bSuccess ;
	DWORD              dwFileSize, dwHighSize, dwBytesRead ;
	HANDLE             hFile ;
	HBITMAP            hBitmap ;
	
	// 打开文件: 只读，写禁止
	hFile = CreateFile (szFileName, GENERIC_READ, FILE_SHARE_READ, NULL, 
						OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL) ;
	
	if (hFile == INVALID_HANDLE_VALUE)
		return NULL ;
	
	// 读入整个文件
	dwFileSize = GetFileSize (hFile, &dwHighSize) ;
	
	if (dwHighSize)
	{
		CloseHandle (hFile) ;
		return NULL ;
	}
	
	pbmfh = (BITMAPFILEHEADER *) malloc (dwFileSize) ;
	
	if (!pbmfh)
	{
		CloseHandle (hFile) ;
		return NULL ;
	}
	
	bSuccess = ReadFile (hFile, pbmfh, dwFileSize, &dwBytesRead, NULL) ;
	CloseHandle (hFile) ;
	
	// 验证文件
	if (!bSuccess || (dwBytesRead != dwFileSize)
					|| (pbmfh->bfType != * (WORD *) "BM") 
					|| (pbmfh->bfSize != dwFileSize))
	{
		free (pbmfh) ;
		return NULL ;
	}
	
	// 创建DDB
	hBitmap = CreateDIBitmap	(hdc, 
								(BITMAPINFOHEADER *) (pbmfh + 1),
								CBM_INIT,
								(BYTE *) pbmfh + pbmfh->bfOffBits,
								(BITMAPINFO *) (pbmfh + 1),
								DIB_RGB_COLORS) ;
	free (pbmfh) ;
	
	return hBitmap ;
}


/*==========================================================
				初始化OPENFILENAME结构
==========================================================*/
void InitOfnStruct (OPENFILENAME& ofn, HWND hWin)
{
	// initialize OPENFILENAME struct
	ofn.lStructSize       = sizeof (OPENFILENAME) ;
	ofn.hwndOwner         = hWin ;
	ofn.hInstance         = NULL ;
	ofn.lpstrFilter       = szFilter ;
	ofn.lpstrCustomFilter = NULL ;
	ofn.nMaxCustFilter    = 0 ;
	ofn.nFilterIndex      = 0 ;
	ofn.lpstrFile         = szFileName ;
	ofn.nMaxFile          = MAX_PATH ;
	ofn.lpstrFileTitle    = szTitleName ;
	ofn.nMaxFileTitle     = MAX_PATH ;
	ofn.lpstrInitialDir   = NULL ;
	ofn.lpstrTitle        = NULL ;
	ofn.Flags             = 0 ;
	ofn.nFileOffset       = 0 ;
	ofn.nFileExtension    = 0 ;
	ofn.lpstrDefExt       = TEXT ("bmp") ;
	ofn.lCustData         = 0 ;
	ofn.lpfnHook          = NULL ;
	ofn.lpTemplateName    = NULL ;
}


/*==========================================================
					对话框窗口函数
==========================================================*/
BOOL CALLBACK AboutDlgProc (HWND hDlg, UINT message, 
                            WPARAM wParam, LPARAM lParam)
{
     switch (message)
     {
     case WM_INITDIALOG :
          return TRUE ;
          
     case WM_COMMAND :
          switch (LOWORD (wParam))
          {
          case IDOK :
               EndDialog (hDlg, 0) ;
               return TRUE ;
          }
          break ;
     }
     return FALSE ;
}
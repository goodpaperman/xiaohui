/*==========================================================
		Move Pic.cpp -- A move-picture game with SDK
			Soft Zealot (R) Robin Hood, 2001						
	  SoftZealot@china.com		Soft_Zealot@china.com

	====================================================
	������ѧϰSDK��̣����Ա�д��һ��С��Ϸ����Ϊ������
	һЩ���ĵı�����⣬��ϲ������˼�ı�̹��� :)

	�����Ϸ��ȫ����SDK��д�ģ�û���漰MFC�����д�ͼƬ
	�ĺ�����Charles Petzold�ġ�Windows������ơ�һ���е�
	Դ���룬��ֻ����������ע�ͣ���������˼���ѡ������Ĵ�
	�������Լ���д�ģ����������ʹ�����еĴ��롣

	��ӭ��Һ������۱�̵����⣬�������www.csdn.net��ר
	�������vc�����ҵ��ң��ҵ�id��Soft_Zealot����
	SoftZealot�� :)��������˼��ˮƽ����ֻ�ö�ע�Ἰ����

	����㷢����bug�����ҵ����κ��ܹ��Ľ��������ܻ����κ�
	�ܹ�ʹcode�������ķ���������֪ͨ�ң��һ�ܸ����ܹ���
	�����������Ϸ��

	====================================================
	�д����:
	1.ʤ��ʱ֪ͨ��Ϸ����Ϸʱ��
	3.�ɲ������ҵ�Ѱ����ѽ���㷨
	4.��μ���Ԥ�����ܣ��ɲ����Բ�������Splash����

	====================================================
	bugs :
	1.��ʾͼƬ��ÿ��Static�ؼ����в�����
	2.���ڶ�ͼ�����windows�ײ㹤��ԭ�����Ǻ��������
	���п��ܻ����ڴ�й©
==========================================================*/

#include <windows.h>
#include <commdlg.h>
#include <time.h>

#include "Move Pic.h"
#include "resource.h"

/*==========================================================
					Ӧ�ó�����ں���
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
						TEXT ("���ƴͼ  Soft Zealot"),	// window caption
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
						���ں���
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

		// ʹstatic�ؼ����ܽ���mouse�����Ϣ
		bWinFlag = true ;

		// ��ʼʹreset�˵���Ч
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

	// ����˵�����
	case WM_COMMAND:
		switch (LOWORD (wParam))
		{	
		case IDM_GAME_RESET:
			/*==================================================
			��Ϸ��λ����ΪStatic�Ѿ�����ͼ�񣬴���Ҳ�õ���������
			��������Ҫ��ͼ��ʱ��ÿ��Static��λ�ã�������ָ�
			Static��λ�þ����ˡ�����Ժ�����ʱ���ܣ�����Ҫ��λ
			��ʼʱ�䡣
			==================================================*/
			// �ָ���ʼStaticλ����Ϣ
			for (i = 0; i < 4; i++)
				for (j = 0; j < 4; j++)
				{
					iStcPos[i][j] = iStcPosSave[i][j] ;
					// �ƶ�Static�ؼ��ص���ʼλ��
					MoveWindow (hwndPic_Button[i][j], 
							(iStcPos[i][j] % 4) * cxClient / 4,
							(iStcPos[i][j] / 4) * cyClient / 4,
							cxClient / 4, cyClient / 4, TRUE);
				}

			bWinFlag = false ;

			return 0 ;

        case IDM_PIC_OPEN:
			// ��ʾ���ļ��Ի���
			if (!GetOpenFileName (&ofn))
				return 0 ;
			
			// ����Ѿ���һ��DIB��ɾ����
			if (hBitmap)
			{
				DeleteObject (hBitmap) ;
				hBitmap = NULL ;
			}
			
			// ��DIB����DDB
			SetCursor (LoadCursor (NULL, IDC_WAIT)) ;	// ʹ��©��ָ��
			ShowCursor (TRUE) ;
			
			hdc = GetDC (hwnd) ;
			hBitmap = CreateBitmapObjectFromDibFile (hdc, szFileName) ;
			ReleaseDC (hwnd, hdc) ;
			
			ShowCursor (FALSE) ;
			SetCursor (LoadCursor (NULL, IDC_ARROW)) ;	// �ָ���ͷָ��
			
			// ʹ�ͻ�����Ч�Ա��Ժ��ػ�
			InvalidateRect (hwnd, NULL, TRUE) ;
			
			if (hBitmap == NULL)
			{
				// �����������DIB�ļ�����ʾ������Ϣ
				MessageBox (hwnd, TEXT ("Cannot load DIB file"), 
							szAppName, MB_OK | MB_ICONEXCLAMATION) ;
			}
			else
			{
				/*==================================================
				�ڵ������ڴ�С֮ǰ�������Static�ؼ���λ�ã��Ա����
				���ڵ�ʱ��Ҳ���������Static�Ĳ��֡�ע��ָ���ͼ��
				��Ȼ�ǰ���˳��(id)�����Static�ģ������ֻ��λ�á�
				==================================================*/
				srand ( (unsigned int) time (NULL));	// for random seed

				int iRanA, iRanB ;
				for (i = 0; i < 32; i++)
				{
					// �õ� 0 -- 16 ֮������������
					iRanA = rand( ) % 16 ;
					do
					{
						iRanB = rand( ) % 16 ;
					}
					while (iRanA == iRanB);

					// ������� Note: index = id   XXX[index] = pos
					iStcBlankPos = iStcPos[iRanA / 4][iRanA % 4] ;
					iStcPos[iRanA / 4][iRanA % 4] = iStcPos[iRanB / 4][iRanB % 4] ;
					iStcPos[iRanB / 4][iRanB % 4] = iStcBlankPos ;
				}

				// ���濪ʼ״̬
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
								�������ڴ�С����Ӧͼ��
				==================================================*/
				GetWindowRect (hwnd, &rcWin);
				GetClientRect (hwnd, &rcClient);

				GetObject (hBitmap, sizeof (BITMAP), &bitmap) ;

				cxScr = GetSystemMetrics (SM_CXSCREEN) ;
				cyScr = GetSystemMetrics (SM_CYSCREEN) ;

				// ��������ʵ���ʾ�ߴ�
				fcxDiv = 5 * (float) (bitmap.bmWidth) /	(float) (cxScr) / 2 ;
				fcyDiv = 5 * (float) (bitmap.bmHeight) / (float) (cyScr) / 3 ;

				// ������������ʵ���ʾ����ͼ��ȽϿ��һ��
				if ( (fDiv = (fcxDiv > fcyDiv) ? fcxDiv : fcyDiv) <= 1)
					fDiv = 1 ;

				// ���������ʵĴ�С��������ͼ�񳤿����
				cxClient = (int) (bitmap.bmWidth / fDiv) ;
				cyClient = (int) (bitmap.bmHeight / fDiv) ;

				// ���¼��㴰�ڳߴ������
				rcWin.left   -= (cxClient - (rcClient.right - rcClient.left)) / 2 ;
				rcWin.right  += (cxClient - (rcClient.right - rcClient.left)) / 2 ;
				rcWin.top    -= (cyClient - (rcClient.bottom - rcClient.top)) / 2 ;
				rcWin.bottom += (cyClient - (rcClient.bottom - rcClient.top)) / 2 ;

				// ������δ�ͼ��󣬴���λ�þͲ�������Ļ�����ˡ���֪�������������

				MoveWindow (hwnd, rcWin.left, rcWin.top, rcWin.right - rcWin.left,
							rcWin.bottom - rcWin.top, TRUE);

				/*==================================================
								��Static��ʾͼ��
				==================================================*/
				// Static�ؼ�Ӧ�õ�����λ�úʹ�С��������ʾͼ��
				hdc = GetDC (hwnd) ;

				// ��ͼ�������ڴ��豸��
				hdcMem = CreateCompatibleDC (hdc) ;
				SelectObject (hdcMem, hBitmap) ;
				
				for (i = 0; i < 4; i++)
					for (j = 0; j < 4; j++)
					{
						// �����Ժ�Ӧ�øĽ�����Ϊ��ϣ���հ׵ط��ܹ����������λ��
						if (i * 4 + j == 15)
						{	idStcBlank = 15;
							break ;
						}

						hdcStc = CreateCompatibleDC (hdc) ;
						// �����µ�ͼ����
						hBmpStc = CreateCompatibleBitmap (hdc,
														  cxClient / 4,
														  cyClient / 4);
						SelectObject (hdcStc, hBmpStc) ;

						// �ָ�ͼ�񲢿�����hdcStc�ڴ��豸��
						StretchBlt (hdcStc,	0, 0, 
									cxClient / 4,
									cyClient / 4,
									hdcMem,
									bitmap.bmWidth * j / 4,
									bitmap.bmHeight * i / 4,
									bitmap.bmWidth / 4,
									bitmap.bmHeight / 4,
									SRCCOPY) ;
						
						// ���ö�Ӧ��Static�ؼ���ͼ��
						SendDlgItemMessage (hwnd,
											4 * i + j, 
											STM_SETIMAGE,
											(WPARAM) IMAGE_BITMAP,
											(LPARAM) hBmpStc) ;

						DeleteObject (hBmpStc) ;	// ɾ���������һ����Բ�Ҫ��ʲôӰ�죿
						DeleteDC (hdcStc) ;
					}

				DeleteDC (hdcMem) ;
				ReleaseDC (hwnd, hdc) ;

				// ʹStatic�ؼ����Խ���mouse�����Ϣ
				bWinFlag = false ;
				// ʹreset�˵���Ч
				EnableMenuItem (hMenu, IDM_GAME_RESET, MF_ENABLED) ;
			}
			
			return 0 ;

		case ID_GAME_EXIT:	// �˳���Ϸ
			SendMessage (hwnd, WM_CLOSE, 0, 0);
			return 0;

		case ID_HELP_ABOUT:
			DialogBox (hInst, TEXT ("AboutDlg"), hwnd, AboutDlgProc) ;
			return 0;

		default:
			if (bWinFlag == false)
			{
				/*==================================================
							Windows֪ͨStatic�������
				ԭ��Ӧ����������˵����һ����ʹ��case id���жϣ�
				�������Ǿ�Ҫ�ظ�16�Σ�Ϊ�˷�������ۣ��Ҿ���������
				��Ϊ���˲˵���Ϣ���ǵ��Static�ؼ���Ϣ�ˡ�
				==================================================*/
				// ��ñ������Static�ؼ���id
				idStcClk = (int) LOWORD (wParam) ;
	
				// �õ�BlankStatic�ͱ������Static�ؼ���λ����Ϣ
				iStcClkPos = iStcPos[idStcClk / 4][idStcClk % 4] ;
				iStcBlankPos = iStcPos[idStcBlank / 4][idStcBlank % 4] ;
			
				// �ж��Ƿ�Ӧ�öԵ��������Ӧ
				if (iStcClkPos == iStcBlankPos)		// player click the blank static
					return 0 ;

				if (iStcClkPos != iStcBlankPos - 4 &&	// not up static of blank static
					iStcClkPos != iStcBlankPos + 4 &&	// not below static of blank static
					iStcClkPos != iStcBlankPos - 1 &&	// not left static of blank static
					iStcClkPos != iStcBlankPos + 1)		// not right static of blank static
					return 0 ;

				// �ƶ�Static�ؼ�
				MoveWindow (hwndPic_Button[idStcClk / 4][idStcClk % 4],
							(iStcBlankPos % 4) * cxClient / 4,
							(iStcBlankPos / 4) * cyClient / 4,
							cxClient / 4, cyClient / 4, TRUE) ;
	
				MoveWindow (hwndPic_Button[idStcBlank / 4][idStcBlank % 4],
							(iStcClkPos % 4) * cxClient / 4,
							(iStcClkPos / 4) * cyClient / 4,
							cxClient / 4, cyClient / 4, TRUE) ;

				// ����Static�ؼ���λ����Ϣ
				iStcPos[idStcClk / 4][idStcClk % 4] = iStcBlankPos ;
				iStcPos[idStcBlank / 4][idStcBlank / 4] = iStcClkPos ;

				// �ж��Ƿ�ʤ��
				int iWinFlag = 0 ;
				for (i = 0; i < 4; i++)
					for (j = 0; j < 4; j++)
						if (iStcPos[i][j] == 4 * i + j)
							iWinFlag ++ ;

				if (iWinFlag == 16)	// win the game
				{
					// ��ʾף����Ϣ
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
				��λͼ�ļ�����λͼ����
==========================================================*/
HBITMAP CreateBitmapObjectFromDibFile (HDC hdc, PTSTR szFileName)
{
	BITMAPFILEHEADER * pbmfh ;
	BOOL               bSuccess ;
	DWORD              dwFileSize, dwHighSize, dwBytesRead ;
	HANDLE             hFile ;
	HBITMAP            hBitmap ;
	
	// ���ļ�: ֻ����д��ֹ
	hFile = CreateFile (szFileName, GENERIC_READ, FILE_SHARE_READ, NULL, 
						OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL) ;
	
	if (hFile == INVALID_HANDLE_VALUE)
		return NULL ;
	
	// ���������ļ�
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
	
	// ��֤�ļ�
	if (!bSuccess || (dwBytesRead != dwFileSize)
					|| (pbmfh->bfType != * (WORD *) "BM") 
					|| (pbmfh->bfSize != dwFileSize))
	{
		free (pbmfh) ;
		return NULL ;
	}
	
	// ����DDB
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
				��ʼ��OPENFILENAME�ṹ
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
					�Ի��򴰿ں���
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
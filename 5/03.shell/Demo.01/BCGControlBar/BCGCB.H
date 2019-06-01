#ifndef __BCGCB_H
#define __BCGCB_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXTEMPL_H__
#include <afxtempl.h>
#endif

#ifdef _AFXDLL
	#ifdef _DEBUG
		#ifdef _UNICODE
			#pragma comment(lib,"BCGControlBarUD.lib") 
			#pragma message("Automatically linking with BCGControlBarUD.dll")
		#else
			#pragma comment(lib,"BCGControlBard.lib") 
			#pragma message("Automatically linking with BCGControlBard.dll")
		#endif
	#else
		#ifdef _UNICODE
			#pragma comment(lib,"BCGControlBarU.lib") 
			#pragma message("Automatically linking with BCGControlBarU.dll") 
		#else
			#pragma comment(lib,"BCGControlBar.lib") 
			#pragma message("Automatically linking with BCGControlBar.dll") 
		#endif
	#endif
#else
	#ifdef _DEBUG
		#ifdef _UNICODE
			#pragma comment(lib,"BCGControlBarStaticud.lib") 
			#pragma message("Automatically linking with BCGControlBarStaticud.lib") 
		#else
			#pragma comment(lib,"BCGControlBarStaticd.lib") 
			#pragma message("Automatically linking with BCGControlBarStaticd.lib") 
		#endif
	#else
		#ifdef _UNICODE
			#pragma comment(lib,"BCGControlBarStaticU.lib") 
			#pragma message("Automatically linking with BCGControlBarStaticU.lib") 
		#else
			#pragma comment(lib,"BCGControlBarStatic.lib") 
			#pragma message("Automatically linking with BCGControlBarStatic.lib") 
		#endif
	#endif
#endif

//------------------
// BCG control bars:
//------------------
#include "BCGToolBar.h"
#include "BCGMenuBar.h"

//-------------------------
// BCG control bar buttons:
//-------------------------
#include "BCGToolbarButton.h"
#include "BCGToolbarComboBoxButton.h"
#include "BCGToolbarMenuButton.h"

//-------------------------------------------------------------------------
// BCG frame windows (replaces CFrameWnd, CMDIFrameWnd and COleIPFrameWnd):
//-------------------------------------------------------------------------
#include "BCGFrameWnd.h"
#include "BCGMDIFrameWnd.h"
#include "BCGOleIPFrameWnd.h"

//-------------------------
// BCG customization stuff:
//-------------------------
#include "CBCGToolbarCustomize.h"

#include "BCGContextMenuManager.h"
#include "BCGKeyboardManager.h"
#include "BCGMouseManager.h"

#include "BCGPopupMenu.h"
#include "BCGToolBarImages.h"

#endif // __BCGCB_H

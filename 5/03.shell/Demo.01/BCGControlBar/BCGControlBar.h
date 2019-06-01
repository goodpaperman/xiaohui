#ifndef __BCGCONTROLBAR_H
#define __BCGCONTROLBAR_H

#ifdef _AFXDLL
	#ifdef _BCGCONTROLBAR_
	   #define BCGCONTROLBARDLLEXPORT  _declspec(dllexport)
	#else
	   #define BCGCONTROLBARDLLEXPORT  _declspec(dllimport)
	#endif
#else
	#define BCGCONTROLBARDLLEXPORT
#endif

#endif // __BCGCONTROLBAR_H

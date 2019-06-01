// StackUp.h: interface for the CStackUp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STACKUP_H__573AEE73_E265_11D1_BF48_C98235055E4A__INCLUDED_)
#define AFX_STACKUP_H__573AEE73_E265_11D1_BF48_C98235055E4A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CGame;
class CLogo;

#define FIRST_INIT_LOGO   1
#define INIT_LOGO         2
#define INIT_GAME         3
#define RUNNING_LOGO      4
#define RUNNING_GAME      5
#define QUIT              6

class CStackUp  
{
public:
	CStackUp();
	virtual ~CStackUp();

  CLogo* m_pLogo;
  CGame* m_pGame;
  short m_State;
  CWinApp* m_pThisApp;

  bool Init();
  void Finish();
  bool Frame();
  void Activate();
};

#endif // !defined(AFX_STACKUP_H__573AEE73_E265_11D1_BF48_C98235055E4A__INCLUDED_)

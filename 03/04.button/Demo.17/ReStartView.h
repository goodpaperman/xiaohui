// ReStartView.h : interface of the CReStartView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_RESTARTVIEW_H__4A734422_EB5C_11D3_B07D_0050DAB826FF__INCLUDED_)
#define AFX_RESTARTVIEW_H__4A734422_EB5C_11D3_B07D_0050DAB826FF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "StaticButton.h"
#include "InfoBar.h"
#include "LowLevelAudioService.h"


#define WM_DESTROYINFOBAR WM_USER + 5

class CReStartDoc;
class CReStartView : public CFormView
{
protected: // create from serialization only
	CReStartView();
	DECLARE_DYNCREATE(CReStartView)
	//HWND hWnd;
public:
	//{{AFX_DATA(CReStartView)
	enum { IDD = IDD_RESTART_FORM };
	CComboBox	m_record_time;
	CComboBox	m_combo_bits;
	CComboBox	m_combo_khz;
	CComboBox	m_combo_mono;
	//}}AFX_DATA

// Attributes
public:
	CReStartDoc* GetDocument();
	CStaticButton mPlay;
	CStaticButton mPause;
	CStaticButton mRewind;
	CStaticButton mForwind;
	CStaticButton mStop;
	CStaticButton mRecord;

	int mMono;		// 모노 스테레오
	int mSampling; // 샘플링 주파수
	int mBits;		// 비트
	int mTime;		// 녹음 시간

	CInfoBar*	m_info;
	CLowLevelAudioService *m_wave;
	CString  m_OpenFile;

	BOOL m_FileOpened;
	char m_strFileName[80];

	int m_nFileTime;//파일 출력 시간
	int m_nFilePos;//파일 출력 장치의 위치

	int m_nStatus;//현재 가동 상태


// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReStartView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	CString SetFileInfo();
	void SetComboState();
	void SetButtonState(int,int,int,int,int,int);
	void DrawInputWave(int);
	void DrawOutputWave(int);
	void DrawWave(LPBYTE data);
	virtual ~CReStartView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CReStartView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPlay();
	afx_msg void OnPause();
	afx_msg void OnRewind();
	afx_msg void OnForwind();
	afx_msg void OnStop();
	afx_msg void OnRecord();
	afx_msg void OnSelchangeComboMono();
	afx_msg void OnSelchangeComboKhz();
	afx_msg void OnSelchangeComboBits();
	afx_msg void OnSelchangeComboRecordingTime();
	afx_msg void OnViewInfoBar();
	afx_msg void OnUpdateViewInfoBar(CCmdUI* pCmdUI);
	afx_msg void OnDestroy();
	afx_msg void OnFileOpen();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	afx_msg void OnDestroyInfoBar();
};

#ifndef _DEBUG  // debug version in ReStartView.cpp
inline CReStartDoc* CReStartView::GetDocument()
   { return (CReStartDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RESTARTVIEW_H__4A734422_EB5C_11D3_B07D_0050DAB826FF__INCLUDED_)

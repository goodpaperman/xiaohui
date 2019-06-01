// FrameGrabberTestDoc.h : interface of the CFrameGrabberTestDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FRAMEGRABBERTESTDOC_H__7E92FA32_976C_11D3_B4B8_8E815E0D4B38__INCLUDED_)
#define AFX_FRAMEGRABBERTESTDOC_H__7E92FA32_976C_11D3_B4B8_8E815E0D4B38__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CBitmapEx.h"

class CFrameGrabberTestDoc : public CDocument
{
protected: // create from serialization only
	CFrameGrabberTestDoc();
	DECLARE_DYNCREATE(CFrameGrabberTestDoc)

// Attributes
public:
	CBitmapEx	m_ImageBitmap;
	UINT		m_ProcessorMode;
// Operations
public:
	void	ProcessImage(LPBITMAPINFO lpBi);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFrameGrabberTestDoc)
	public:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFrameGrabberTestDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	BOOL ApplyFilter(LPBITMAPINFO lpBi);
	BOOL RunDetector(LPBITMAPINFO lpBi);
// Generated message map functions
protected:
	//{{AFX_MSG(CFrameGrabberTestDoc)
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSimpleFilter(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSimpleViewer(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDetector(CCmdUI* pCmdUI);
	afx_msg void OnDetector();
	afx_msg void OnSimpleFilter();
	afx_msg void OnSimpleViewer();
	afx_msg void OnFileSaveAs();
	afx_msg void OnUpdateFileSaveAs(CCmdUI* pCmdUI);
	afx_msg void OnPause();
	afx_msg void OnUpdatePause(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FRAMEGRABBERTESTDOC_H__7E92FA32_976C_11D3_B4B8_8E815E0D4B38__INCLUDED_)

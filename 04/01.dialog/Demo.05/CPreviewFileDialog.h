#ifndef __PREVIEWFILEDIALOG__
#define __PREVIEWFILEDIALOG__
// PreviewFileDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPreviewFileDialog dialog


#include "cdib.h"

class CAbstractPreview
{
public:
	virtual void SetPreviewFile(const CString& csFileName)=0;
	virtual void DrawPreview(CDC *pDC,int x,int y,int width,int height)=0;
	virtual CRect Calc(int bmpWid,int bmpDep,int wndWid,int wndDep);
};





class CPreviewFileDialog : public CFileDialog
{
	DECLARE_DYNAMIC(CPreviewFileDialog)

public:
	CPreviewFileDialog(CAbstractPreview *pPreview,BOOL bOpenFileDialog, // TRUE for FileOpen, FALSE for FileSaveAs
		LPCTSTR lpszDefExt = NULL,
		LPCTSTR lpszFileName = NULL,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCTSTR lpszFilter = NULL,
		CWnd* pParentWnd = NULL);

protected:
	//{{AFX_MSG(CPreviewFileDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickedPreview();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	virtual void OnFileNameChange();
	virtual void OnFolderChange();
	virtual void OnInitDone();

	CButton checkBox;
	CRect PreviewRect;
	BOOL m_bPreview;
	CAbstractPreview *m_pPreview;
	CRgn m_Region;
	CString m_csFileName;
	BOOL m_bChanged;
};

#endif

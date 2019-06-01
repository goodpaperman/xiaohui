/************************************
  REVISION LOG ENTRY
  Revision By: Mihai Filimon
  Revised on 7/22/98 9:21:30 AM
  Comments: DragPage.h header file for CDragPage
 ************************************/

#if !defined(AFX_DRAGPAGE_H__91E4A9F5_1FA5_11D2_864F_0040055C08D9__INCLUDED_)
#define AFX_DRAGPAGE_H__91E4A9F5_1FA5_11D2_864F_0040055C08D9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CSheetAlpha;

struct SRectSave
{
private:
	CRect m_rectBMP;
	CBitmap* m_pBMPSave;
	CDC* m_pDC;
public:
	// Function name	: SRectSave
	// Description	    : Default constructor of this structure
	// Return type		: 
	SRectSave()
	{
		m_pDC = NULL;
		m_pBMPSave = NULL;
		m_rectBMP.SetRectEmpty();
	}

	// Function name	: ~SRectSave
	// Description	    : virtual default destructor, will destroy created bitmap for you.
	// Return type		: virtual 
	virtual ~SRectSave()
	{
		Destroy();
	}

	// Function name	: Destroy
	// Description	    : Destroy all saved.
	// Return type		: void 
	void Destroy()
	{
		if (m_pBMPSave)
		{
			m_pBMPSave->DeleteObject();
			delete m_pBMPSave;
		}
		m_pBMPSave = NULL;
		m_pDC = NULL;
		m_rectBMP.SetRectEmpty();
	}

	// Function name	: Restore
	// Description	    : Restore the zone saved in m_pBMPSave at m_rectBMP in m_pDC, if all OK
	// Return type		: void 
	void Restore()
	{
		if (m_pBMPSave && m_pBMPSave->GetSafeHandle())
			if (!m_rectBMP.IsRectEmpty())
			{
				m_pDC = CDC::FromHandle(::GetDC(NULL));
				CDC dc;
				VERIFY(dc.CreateCompatibleDC(m_pDC));
				CBitmap* pOldBitmap = dc.SelectObject(m_pBMPSave);
				 m_pDC->BitBlt(m_rectBMP.left, m_rectBMP.top, m_rectBMP.Width(), m_rectBMP.Height(), &dc, 0, 0 , SRCCOPY);
				dc.SelectObject(pOldBitmap);
				::ReleaseDC(NULL, m_pDC->m_hDC);
			}
		Destroy();
	}

	// Function name	: Save
	// Description	    : Save the zone rectBMP from pDC
	// Return type		: void 
	// Argument         : CRect rectBMP
	void Save(CRect rectBMP)
	{
		// Must call Save before call Restore.
		ASSERT ( NULL == m_pBMPSave );
		ASSERT ( m_rectBMP.IsRectEmpty() );
		ASSERT ( !rectBMP.IsRectEmpty());

		if (m_pBMPSave = new CBitmap())
		{
			m_pDC = CDC::FromHandle(::GetDC(NULL));
			m_rectBMP = rectBMP;
			VERIFY(m_pBMPSave->CreateCompatibleBitmap(m_pDC, m_rectBMP.Width(), m_rectBMP.Height()));
			CDC dc;
			VERIFY(dc.CreateCompatibleDC(m_pDC));
			CBitmap* pOldBitmap = dc.SelectObject(m_pBMPSave);
			 dc.BitBlt(0,0, m_rectBMP.Width(), m_rectBMP.Height(), m_pDC, m_rectBMP.left, m_rectBMP.top, SRCCOPY);
			dc.SelectObject(pOldBitmap);
			::ReleaseDC(NULL, m_pDC->m_hDC);
		}
	}

	// Function name	: SRectSave::IsChanged
	// Description	    : Return TRUE if something must changed
	// Return type		: BOOL 
	// Argument         : CPoint ptnNew
	BOOL SRectSave::IsChanged(CPoint ptnNew)
	{
		return !(m_rectBMP.TopLeft() == ptnNew);
	}


};

class CDragPage
{
protected:
	BOOL m_bDragging;
	CWnd* m_pViewStartDrag;
	CWnd* m_pViewTrackDrag;
public:
	virtual void SetTrackDrag(CWnd* pWnd);
	CWnd* GetTrackDrag() { return m_pViewTrackDrag; };
	CWnd* GetStartDrag() { return m_pViewStartDrag; };
	CDragPage();
	CDragPage(CDragPage& dragSource);
	virtual ~CDragPage();
	void Set(BOOL bDragging = FALSE, CWnd* pViewStartDrag = NULL);
	void Reset();
	BOOL IsDragging();
	void Draw(CSheetAlpha* pSheet);
private:
	SRectSave* m_pRectSave;
};


#endif //AFX_DRAGPAGE_H__91E4A9F5_1FA5_11D2_864F_0040055C08D9__INCLUDED_
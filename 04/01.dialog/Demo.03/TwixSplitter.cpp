#include "stdafx.h"
#include "TwixSplitter.h"

static int AFXAPI CanSplitRowCol(CSplitterWnd::CRowColInfo* pInfoBefore,
	int nBeforeSize, int nSizeSplitter)
	// request to split Before row at point nBeforeSize
	// returns size of new pane (nBeforeSize will be new size of Before pane)
	// return -1 if not big enough
{
	ASSERT(pInfoBefore->nCurSize > 0);
	ASSERT(pInfoBefore->nMinSize > 0);
	ASSERT(nBeforeSize <= pInfoBefore->nCurSize);

	// space gets take from before pane (weird UI for > 2 splits)
	if (nBeforeSize < pInfoBefore->nMinSize)
	{
		TRACE0("Warning: split too small to fit in a new pane.\n");
		return -1;
	}

	int nNewSize = pInfoBefore->nCurSize - nBeforeSize - nSizeSplitter;
	if (nBeforeSize < pInfoBefore->nMinSize)
	{
		TRACE0("Warning: split too small to shrink old pane.\n");
		return -1;
	}
	if (nNewSize < (pInfoBefore+1)->nMinSize)
	{
		TRACE0("Warning: split too small to create new pane.\n");
		return -1;
	}
	return nNewSize;
}

BOOL CTwixSplitter::SplitRow(int cyBefore)
{
	ASSERT_VALID(this);
	ASSERT(GetStyle() & SPLS_DYNAMIC_SPLIT);
	ASSERT(m_pDynamicViewClass != NULL);
	ASSERT(m_nRows < m_nMaxRows);

	cyBefore -= m_cyBorder;
	int rowNew = m_nRows;
	int cyNew = CanSplitRowCol(&m_pRowInfo[rowNew-1], cyBefore, m_cySplitter);
	if (cyNew == -1)
		return FALSE;   // too small to split

	// create the scroll bar first (so new views can see that it is there)
	if (m_bHasVScroll &&
		!CreateScrollBarCtrl(SBS_VERT, AFX_IDW_VSCROLL_FIRST + rowNew))
	{
		TRACE0("Warning: SplitRow failed to create scroll bar.\n");
		return FALSE;
	}

	m_nRows++;  // bump count during view creation

	// create new views to fill the new row (RecalcLayout will position)
	if(m_nCols > 1)
	{
		CWnd* pWnd = GetPane(0, 1);
		ASSERT_VALID(pWnd);
		pWnd->SetDlgCtrlID(IdFromRowCol(1, 0));
		m_nCols = 1;
		if(m_bHasHScroll)
			GetDlgItem(AFX_IDW_HSCROLL_FIRST+1)->DestroyWindow();
	}
	else
		for (int col = 0; col < m_nCols; col++)
		{
			CSize size(m_pColInfo[col].nCurSize, cyNew);
			if (!CreateView(rowNew, col, m_pDynamicViewClass, size, NULL))
			{
				TRACE0("Warning: SplitRow failed to create new row.\n");
				// delete anything we partially created 'col' = # columns created
				while (col > 0)
					DeleteView(rowNew, --col);
				if (m_bHasVScroll)
					GetDlgItem(AFX_IDW_VSCROLL_FIRST + rowNew)->DestroyWindow();
				m_nRows--;      // it didn't work out
				return FALSE;
			}
		}

	// new parts created - resize and re-layout
	m_pRowInfo[rowNew-1].nIdealSize = cyBefore;
	m_pRowInfo[rowNew].nIdealSize = cyNew;
	ASSERT(m_nRows == rowNew+1);
	RecalcLayout();

	return TRUE;
}

BOOL CTwixSplitter::SplitColumn(int cxBefore)
{
	ASSERT_VALID(this);
	ASSERT(GetStyle() & SPLS_DYNAMIC_SPLIT);
	ASSERT(m_pDynamicViewClass != NULL);
	ASSERT(m_nCols < m_nMaxCols);

	cxBefore -= m_cxBorder;
	int colNew = m_nCols;
	int cxNew = CanSplitRowCol(&m_pColInfo[colNew-1], cxBefore, m_cxSplitter);
	if (cxNew == -1)
		return FALSE;   // too small to split

	// create the scroll bar first (so new views can see that it is there)
	if (m_bHasHScroll &&
		!CreateScrollBarCtrl(SBS_HORZ, AFX_IDW_HSCROLL_FIRST + colNew))
	{
		TRACE0("Warning: SplitRow failed to create scroll bar.\n");
		return FALSE;
	}

	m_nCols++;  // bump count during view creation

	// create new views to fill the new column (RecalcLayout will position)
	if(m_nRows > 1)
	{
		CWnd* pWnd = GetPane(1, 0);
		ASSERT_VALID(pWnd);
		pWnd->SetDlgCtrlID(IdFromRowCol(0, 1));
		m_nRows = 1;
		if(m_bHasVScroll)
			GetDlgItem(AFX_IDW_VSCROLL_FIRST+1)->DestroyWindow();
	}
	else
		for (int row = 0; row < m_nRows; row++)
		{
			CSize size(cxNew, m_pRowInfo[row].nCurSize);
			if (!CreateView(row, colNew, m_pDynamicViewClass, size, NULL))
			{
				TRACE0("Warning: SplitColumn failed to create new column.\n");
				// delete anything we partially created 'col' = # columns created
				while (row > 0)
					DeleteView(--row, colNew);
				if (m_bHasHScroll)
					GetDlgItem(AFX_IDW_HSCROLL_FIRST + colNew)->DestroyWindow();
				m_nCols--;      // it didn't work out
				return FALSE;
			}
		}

	// new parts created - resize and re-layout
	m_pColInfo[colNew-1].nIdealSize = cxBefore;
	m_pColInfo[colNew].nIdealSize = cxNew;
	ASSERT(m_nCols == colNew+1);
	RecalcLayout();

	return TRUE;
}

void CTwixSplitter::DeleteView(int row, int col)
{
	ASSERT_VALID(this);

	// if active child is being deleted - activate next
	CWnd* pPane = GetPane(row, col);
//	ASSERT_KINDOF(CView, pPane);
	if (GetActivePane() == pPane)
		ActivateNext(FALSE);

	// default implementation assumes view will auto delete in PostNcDestroy
	pPane->DestroyWindow();
}

void CTwixSplitter::SplitRow()
{
	// half split
	if(1 == m_nRows)
		SplitRow(m_pRowInfo[0].nCurSize / 2);
}

void CTwixSplitter::SplitColumn()
{
	// half split
	if(1 == m_nCols)
		SplitColumn(m_pColInfo[0].nCurSize / 2);
}

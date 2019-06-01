// AutoCompletionComboBox.cpp : implementation file
//

#include "stdafx.h"
#include "AutoCompletion.h"
#include "AutoCompletionComboBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAutoCompletionComboBox

CAutoCompletionComboBox::CAutoCompletionComboBox()
: CComboBox(),
  m_pEdit(NULL)
{
}

CAutoCompletionComboBox::~CAutoCompletionComboBox()
{
}


BEGIN_MESSAGE_MAP(CAutoCompletionComboBox, CComboBox)
	//{{AFX_MSG_MAP(CAutoCompletionComboBox)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAutoCompletionComboBox message handlers

void CAutoCompletionComboBox::HandleCompletion()
{
  // Make sure we can 'talk' to the edit control
  if ( m_pEdit == NULL )  
  {
    m_pEdit = new CEdit();
    m_pEdit->SubclassWindow(GetDlgItem(1001)->GetSafeHwnd());
  }

  // Save the state of the edit control
  CString windowtext;
  m_pEdit->GetWindowText(windowtext);

  int start,end;
  m_pEdit->GetSel(start,end);

  // Perform actual completion
  int bestindex = -1;
  //int bestfrom  = INT_MAX;
  int bestfrom = -1; 
  for ( int x = 0; x < GetCount(); x++ )
  {
    CString s;
    GetLBText(x,s);

    //int from = s.Find(windowtext);
    int from = -1; 
    for(int i=0; i<windowtext.GetLength() && i<s.GetLength(); i++)
    {
        if(windowtext[i] == s[i])
            from = i; 
        else 
            break; 
    }

    //if ( from != -1 && from < bestfrom )
    if(from != -1 && from > bestfrom)
    {
      bestindex = x;
      bestfrom  = from;
    }
  }

  if ( bestindex != -1 && GetCurSel() != bestindex )
  {
    // Select the matching entry in the list
    ShowDropDown(TRUE);
    SetCurSel(bestindex);

    // Restore the edit control
    m_pEdit->SetWindowText(windowtext);
    m_pEdit->SetSel(start,end);
  }
}

BOOL CAutoCompletionComboBox::OnCommand(WPARAM wParam, LPARAM lParam) 
{
  if ( HIWORD(wParam) == EN_CHANGE )
  {
    HandleCompletion();
    return true;
  }

	return CComboBox::OnCommand(wParam, lParam);
}

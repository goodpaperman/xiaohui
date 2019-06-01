// ChessBoard1.cpp : implementation file
//

#include "stdafx.h"
#include "ChessBoard1.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChessBoard


CChessBoard::~CChessBoard()
{
}


BEGIN_MESSAGE_MAP(CChessBoard, CWnd)
	//{{AFX_MSG_MAP(CChessBoard)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(UM_COMRUN, OnComRun)
	ON_MESSAGE(WM_TRANCHESS, OnTranChess)
END_MESSAGE_MAP()

void delay(INT32 millisecond)
{
	clock_t start = clock();
	do
	{ 
		MSG msg;
		if (::PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE ) ) 
		{ 
			if ( !AfxGetApp()->PumpMessage()) 
			{ 
			::PostQuitMessage(0); 
			 return;
			} 
		} 
	}while(clock()<start+millisecond);
}

void CChessBoard::MoveBack()
{
	if(cur_step<2)
		return;
   UINT8 comside = computer_side;
   UINT8 step = cur_step;
   INT16 movearray[64];
   memcpy(movearray, step_array, 64*sizeof(INT16));
   init_board(&m_oChessBoard);
   computer_side = comside;
   UINT8 col= CHESS_BLACK;
   for(int i=0; i<step-2; i++, col = ~col & 3)
        do_move_chess(&m_oChessBoard, movearray[i], col, 0);
   OnPaint();
   Invalidate(); 
}

void CChessBoard::OnTranChess(WPARAM wParam, LPARAM lParam)
{
    //OnPaint(); 
	int row = wParam/10-1;
	int col = wParam%10-1;
    CRect r(col*COL_WIDTH+22, row*ROW_WIDTH+22,
		    col*COL_WIDTH+COL_WIDTH+22, row*ROW_WIDTH+ROW_WIDTH+22);

    m_bPlayMotive = FALSE; 
	OnPaint(); 
	InvalidateRect(&r);

    if((lParam>>16) !=0)
    	 PlayMotive(row, col, UINT8(lParam));
	//else
	//	MessageBeep(MB_OK);

      
	//delay(200);

}
/////////////////////////////////////////////////////////////////////////////
// CChessBoard message handlers
void CChessBoard::OnComRun(WPARAM wParam, LPARAM lParam)
{
	//m_oChessBoard.FindAndCalc(m_iCurColor);
	computer_play(&m_oChessBoard, m_hWnd); 
  //  m_iCurColor = (~m_iCurColor)& 0x03; 
    //WORD status1 = calc_board_status(&m_oChessBoard, CHESS_BLACK); 
	//WORD status2 = calc_board_status(&m_oChessBoard, CHESS_WHITE); 
    UINT16 wscore, bscore;
	get_chess_score(&m_oChessBoard, wscore, bscore);
	GetParent()->SendMessage(UM_RECALC, WPARAM(wscore|0x80000000), LPARAM(bscore)); 
	//Invalidate(); 
 
}
void CChessBoard::NewGame()
{
	if(cur_step >0)
	{
		if(MessageBox("开始新游戏吗?", "黑白棋", MB_YESNO|MB_ICONQUESTION) == IDYES)
		{
	
	       init_board(&m_oChessBoard);
	       Invalidate(); 
		}
	}
}

BOOL CChessBoard::Create(RECT &rect, CWnd *pParentWnd, UINT nID)
{
	// TODO: Add your specialized code here and/or call the base class
	CString szClassName = AfxRegisterWndClass(CS_CLASSDC|CS_SAVEBITS|
		                                      CS_HREDRAW|CS_VREDRAW,
                                              0, (HBRUSH)CBrush(RGB(0,0,255)), 0);
    //rect.right = rect.left + COL_WIDTH*BOARD_COLS;
    //rect.bottom = rect.top + ROW_WIDTH*BOARD_ROWS;
	rect.right = rect.left + 380+3;
	rect.bottom = rect.top +380+3;
	if(!CWnd::CreateEx(WS_EX_CLIENTEDGE, szClassName, _T(""),
		                WS_CHILD|WS_VISIBLE|WS_TABSTOP, rect, 
						pParentWnd, nID, NULL)) //WS_EX_CLIENTEDGE

		   return FALSE;
    UpdateWindow();
	m_bitBlackChess.LoadBitmap(IDB_BLACKCHESS);
	m_bitChessBoard.LoadBitmap(IDB_CHESSBOARD);
	m_bitWhiteChess.LoadBitmap(IDB_WHITECHESS);
//	m_motive[0].LoadBitmap(IDB_WHITECHESS); 
//	m_motive[1].LoadBitmap(IDB_TURN1);
	m_motive[0].LoadBitmap(IDB_WHITECHESS); 
	m_motive[1].LoadBitmap(IDB_TURN1);
	m_motive[2].LoadBitmap(IDB_TURN2); 
	m_motive[3].LoadBitmap(IDB_TURN3); 
	m_motive[4].LoadBitmap(IDB_TURN4); 
	m_motive[5].LoadBitmap(IDB_TURN5); 
	m_motive[6].LoadBitmap(IDB_TURN6); 
	m_motive[7].LoadBitmap(IDB_BLACKCHESS); 
//	m_motive[10].LoadBitmap(IDB_TURN6); 
//	m_motive[11].LoadBitmap(IDB_BLACKCHESS);



	//m_hicBlack=AfxGetApp()->LoadIcon(IDC_BLACK); 
	//m_hicWhite=AfxGetApp()->LoadIcon(IDC_WHITE);
	return TRUE;
}
void CChessBoard::PlayMotive(int row, int col, UINT8 obcolor)
{
	m_iMotivex = col*COL_WIDTH+24;
	m_iMotivey = row*COL_WIDTH+24;
	CRect r(m_iMotivex, m_iMotivey, m_iMotivex+COL_WIDTH, m_iMotivey +ROW_WIDTH);
	m_bPlayMotive = TRUE; 
	if(obcolor == CHESS_BLACK)
	{
		for(m_iMotiveNumber =0; m_iMotiveNumber<8; m_iMotiveNumber++)
		{
			OnPaint();
			InvalidateRect(&r); 
			delay(50);
		}
	}
	else
	{
		for(m_iMotiveNumber =7; m_iMotiveNumber>=0; m_iMotiveNumber--)
		{
			OnPaint();
			InvalidateRect(&r); 
			delay(50);
		}
	}
	m_bPlayMotive = FALSE;
}
void CChessBoard::OnPaint() 
{

	CPaintDC dc(this); // device context for painting
	CDC imgdc;
	imgdc.CreateCompatibleDC(&dc);
	imgdc.SelectObject(&m_bitChessBoard); 
    dc.BitBlt(0, 0, 380, 380, &imgdc,0,0,SRCCOPY);  	
	if(m_bPlayMotive)
	{
		imgdc.SelectObject(&m_motive[m_iMotiveNumber]);  
		dc.BitBlt(m_iMotivex, m_iMotivey, 39, 39, &imgdc, 0, 0, SRCCOPY);
		return;
	}
  
    for(int i=0; i<BOARD_ROWS; i++)
		for(int j=0; j<BOARD_COLS; j++)
		{
			if(m_oChessBoard.board[i+1][j+1] == CHESS_BLACK)
			{
                imgdc.SelectObject(&m_bitBlackChess); 
                dc.BitBlt(j*COL_WIDTH+24, i*ROW_WIDTH+24, 39, 39, &imgdc,0,0,SRCCOPY);
				//dc.DrawIcon(j*COL_WIDTH+9, i*ROW_WIDTH+9, m_hicBlack);
			}
			else if(m_oChessBoard.board[i+1][j+1] == CHESS_WHITE)
			{
				imgdc.SelectObject(&m_bitWhiteChess); 
                dc.BitBlt(j*COL_WIDTH+24, i*ROW_WIDTH+24, 39, 39, &imgdc,0,0,SRCCOPY);
			    //dc.DrawIcon(j*COL_WIDTH+9, i*ROW_WIDTH+9, m_hicWhite);
			}
            
		}
		
 
	// Do not call CWnd::OnPaint() for painting messages
}

void CChessBoard::OnLButtonDown(UINT nFlags, CPoint point) 
{

	BYTE row = (point.y-22)/ROW_WIDTH+1;
	BYTE col = (point.x-22)/COL_WIDTH+1;
	//if(m_iCurColor != CHESS_BLACK)
	//	return;
	if(do_move_chess(&m_oChessBoard, row*10+col, ~computer_side&3, m_hWnd))
	{
		//WORD status1 = calc_board_status(&m_oChessBoard, CHESS_BLACK); 
		//WORD status2 = calc_board_status(&m_oChessBoard, CHESS_WHITE); 
		//GetParent()->SendMessage(UM_RECALC, WPARAM(status1<<16|status2)); 
		UINT16 wscore, bscore;
	    get_chess_score(&m_oChessBoard, wscore, bscore);
	    GetParent()->SendMessage(UM_RECALC, WPARAM(wscore), LPARAM(bscore)); 
       // m_iCurColor = (~m_iCurColor)& 0x03;
		PostMessage(UM_COMRUN);
		CMenu *pMenu = GetParent()->GetMenu();   
        (pMenu->GetSubMenu(1))->EnableMenuItem(IDC_BUTTON1, 
		               MF_BYCOMMAND|MF_GRAYED|MF_DISABLED);
		//m_oChessBoard.FindAndCalc(m_iCurColor);
        //m_iCurColor = (~m_iCurColor)& 0x03;  
	}
	else
		MessageBeep(MB_OK);

	CWnd::OnLButtonDown(nFlags, point);
}

int CChessBoard::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
    EndWaitCursor();
	return 0;
}

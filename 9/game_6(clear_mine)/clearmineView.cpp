// clearmineView.cpp : implementation of the CClearmineView class
//

#include "stdafx.h"
#include "clearmine.h"

#include "clearmineDoc.h"
#include "clearmineView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClearmineView

IMPLEMENT_DYNCREATE(CClearmineView, CView)

BEGIN_MESSAGE_MAP(CClearmineView, CView)
	//{{AFX_MSG_MAP(CClearmineView)
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClearmineView construction/destruction

CClearmineView::CClearmineView()
{
	for(int a=0;a<10;a++)
	{
		
	
		for(int b=0;b<10;b++)
		{
			int x=100+30*a;
			int y=100+30*b;
		IsMine[a][b]=0;

				   RectLeftTopX[a][b]=y;
				   RectLeftTopY[a][b]=x;
				
		}
	}
	for(a=0;a<10;a++)
	{
		for(int b=0;b<10;b++)
		{
			int x=130+30*a;
			int y=130+30*b;
                   RectRightDownX[a][b]=y;
				   RectRightDownY[a][b]=x;
		}
	}
	
	    
		/*IsMine[1][1]=1;
		IsMine[5][8]=1;
		IsMine[5][2]=1;
		IsMine[3][8]=1;
		IsMine[0][1]=1;
		IsMine[1][9]=1;
		IsMine[7][7]=1;
		IsMine[3][7]=1;
		IsMine[1][0]=1;
		IsMine[0][0]=1;
		IsMine[9][7]=1;
		IsMine[2][9]=1;
		IsMine[7][5]=1;
		IsMine[4][8]=1;
		IsMine[9][9]=1;*/
	int i;

	//srand( (unsigned ) time (NULL) );
    for(i=0;i<10;i++)
    {
        for(int j=0;j<10;j++)
        {
            IsMine[i][j]=rand()/30000;
        }
    }


		IsDown=0;
		x=0;
		y=0;
		clearmines=0;

		second=0;
		minute=0;
		hour=0;
		seconds=0;
		IsBegin=0;
	

	
	


			// TODO: add construction code here

}

CClearmineView::~CClearmineView()
{
}

BOOL CClearmineView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CClearmineView drawing

void CClearmineView::OnDraw(CDC* pDC)
{
		SetTimer(1,1000,NULL);


	//画出工作区
     if(IsDown==1)
	 {
       pDC->TextOut(420,100,time);
	   UpdateWindow();

                if(IsMine[x][y]==1)
				{
				
				CString outIn;
				outIn.Format("你在 :(%d,%d),%d个雷",x,y,HowManyMine(x,y));
				MessageBox("你输了!","对不起!",MB_OK);
				IsBegin=0;
				seconds=0;
				

				}
				else
				{
					if(clearmines==84)
					{
						AfxMessageBox("你赢了！祝贺你");
						clearmines=0;
						IsBegin=0;
						seconds=0;
					}
					else
					{
		 CString liwei;
		 liwei.Format("%d",HowManyMine(x,y));
		 pDC->TextOut((RectLeftTopX[x][y]+10),(RectLeftTopY[x][y]+10),liwei);
		 UpdateData(false);
		 clearmines++;
		

		 IsDown=0;
					}
				}
	 }
	 else
	 {for(int a=100;a<=400;a+=30)
	{
		
		for(int b=100;b<=400;b+=30)
		{
         pDC->MoveTo(a,b);
 	     pDC->LineTo(400,b);
		 pDC->MoveTo(a,b);
		pDC->LineTo(a,400);
		}
		
	}
	 }

	


	
	CClearmineDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
		/*CString test;
	int c=0;
	for( int a1=0;a1<10;a1++)
	{
	

		for(int b1=0;b1<10;b1++)
		{
			                        //*c+=15;	

	                               //test.Format("(%d,%d):%d",a1,b1,IsMine[a1][b1]);
	                                   //pDC->TextOut(450,c,test);
		}
	}*///检查数组数据是否正确？RectRightDownX[a1][b1],RectRightDownY[a1][b1]// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CClearmineView diagnostics

#ifdef _DEBUG
void CClearmineView::AssertValid() const
{
	CView::AssertValid();
}

void CClearmineView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CClearmineDoc* CClearmineView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CClearmineDoc)));
	return (CClearmineDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CClearmineView message handlers

void CClearmineView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	
	for(int a=0;a<10;a++)
	{
		for(int b=0;b<10;b++)
		{
			CRect rect(RectLeftTopX[a][b],RectLeftTopY[a][b],RectRightDownX[a][b],
				RectRightDownY[a][b]);
			if(rect.PtInRect(point))
			{
	
                x=a;
				y=b;
				IsDown=1;
				IsBegin=1;
				

				OnDraw(CClearmineView::GetWindowDC());
		        IsDown=0;
				
			}
		}
	}
				// TODO: Add your message handler code here and/or call default
	
	CView::OnLButtonDown(nFlags, point);
}
int CClearmineView::HowManyMine(int a,int b)
{
	int i=0;
	int bianx0=a+1;
	int oldb=b;
	
	if((a==0)&&(b!=0)&&(b!=9))
	{

		for(;a<=bianx0;a++)
		{
			for(b=(oldb-1);b<=(oldb+1);b++)
			{
	
			if(IsMine[a][b]==1)
			{
				i++;
				 
			}
			}
		}
		return i;
	}
  int bianx9=a;
  int biany9=b;
	if((a==9)&&(b!=0)&&(b!=9))
	{

		a--;
		for(; a<=bianx9;a++)
		{
			for(b=(biany9-1);b<=(biany9+1);b++)
			{	 

				if(IsMine[a][b]==1)
				{
					i++;
				
				}
			}
		}
		return i;
	}
	int biany00=b;
	int bianx00=a;
	if((b==0)&&(a!=0)&&(a!=9))
	{

		for(;b<=(biany00+1);b++)
		{
			for(a=(bianx00-1);a<=(bianx00+1);a++)
			{
	
				if(IsMine[a][b]==1)
				{
					i++;
					 
			}
			}
		}
		return i;
	}
	int biany99=b;
	int bianx99=a;
	if((b==9)&&(a!=0)&(a!=9))
	{
	
		b--;
		for(;b<=biany99;b++)
		{
			for(a=(bianx99-1);a<=(bianx99+1);a++)
			{
	
				if(IsMine[a][b]==1)
				{
					i++;
					 
				}
			}
		}
		return i;
	}
if((a==0)&&(b==0))
	{
	      int oldb0=b;
	
		for(	int cx=a+1;a<=cx;a++)
		{
			for(	b=oldb0;b<=(oldb0+1);b++)
			{
		
				if(IsMine[a][b]==1)
				{

					i++;
     
	
		
				}
			}
		}
		return i;
	}
if((a==9)&&(b==9))
{
	int cx=a;
	int cy=b;
	a--;

	for(;a<=cx;a++)
	{
		for(b=(cy-1);b<=cy;b++)
		{ 

			if(IsMine[a][b]==1)
			{
				i++;
				
			}
		}
	}
	return i;
}
if((a==0)&&(b==9))
{
	int cx=a+1;
	int cy=b;

	for(;a<=cx;a++)
	{
		for(b=(cy-1);b<=cy;b++)
		{
	
			if(IsMine[a][b]==1)
			{
				i++;
		
			}
		}
	}
	return i;
}
if((a==9)&&(b==0))
{
	int cx=a;
	int cy=b;
	a--;
	for(;a<=cx;a++)
	{
		for(b=cy;b<=(cy+1);b++)
		{
	
			if(IsMine[a][b]==1)
			{
				i++;
				 
			}
		}
	}
	return i;
}

	

	
	int s=a;
    int r=b;


	for(a=(s-1);a<=(s+1);a++)
	{
		for(b=(r-1);b<=(r+1);b++)
		{

			  if(IsMine[a][b]==1)
			{
				i++;
              
			}
		}
	}

	return i;
}
void CClearmineView::TestIsMine(int a,int b)
{
    CString test;

	

	test.Format("(%d,%d)处有雷!",a,b);
    AfxMessageBox(test);
}


void CClearmineView::OnTimer(UINT nIDEvent,CDC *pDC) 
{
	pDC=CClearmineView::GetWindowDC();
	if(IsBegin==1)
	{
	seconds++;
	CString timer;
	if(seconds<=59)
	{
		timer.Format("使用时间:0 小时0分钟%d秒",seconds);
		time=timer;
	}
	if((seconds>=60)&&(seconds<=3599))
	{
		minute=seconds/60;
		second=seconds-minute*60;
		timer.Format("使用时间:0 小时%d分钟%d秒",minute,second);
		time=timer;
	}
	if(seconds>=3600)
	{
		hour=seconds/3600;
		minute=(seconds-(hour*3600))/60;
		second=seconds-hour*3600-minute*60;
	timer.Format("使用时间:%d小时%d分钟%d秒",hour,minute,second);
	time=timer;
	}
    

	pDC->TextOut(420,100,time);
	UpdateWindow();
	ReleaseDC(pDC);


	}	// TODO: Add your message handler code here and/or call default
	
	CView::OnTimer(nIDEvent);
}

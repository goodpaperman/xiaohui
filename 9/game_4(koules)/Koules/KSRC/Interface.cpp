#include "koules.h"
#include "interface.h"

LPDIRECTDRAWSURFACE draw_surf;  //main draw surface
LPBYTE font_buff=NULL;

VScreenType background;
VScreenType starbackground;
LPDIRECTDRAWSURFACE      
		bball_bitmap,
		apple_bitmap,
		inspector_bitmap,
		mouse_bitmap,
        lunatic_bitmap,
		lball_bitmap[NLETTERS],
        hole_bitmap,
		ball_bitmap,
		eye_bitmap[MAXROCKETS],
		rocket_bitmap[MAXROCKETS],
        ehole_bitmap,
		koules_bitmap;

extern int TextLen (char *text)
{
	return strlen(text)*9;
}

void outchar(LPBYTE vbuff,DWORD linelen,int x,int y,BYTE c,int color)
{
	WORD k;
	LPBYTE fbuff=font_buff+c*16;//font_data
	int lc=y;
	y*=linelen;
	for(int i=0;i<16;i++,lc++,y+=linelen)
	{
	k=*(fbuff+i);
	if(lc>=0 && lc<600)
		for(int j=0;j<8;j++)
		{
		if(k & 0x80)
			*(vbuff+x+j+y)=(BYTE)color;
		k<<=1;
		}
	}
}

extern void					DrawText(int x, int y, char *text,int color)
{
	DDSURFACEDESC desc;
	ZeroMemory( &desc, sizeof(desc) );
	desc.dwSize = sizeof(desc);
	HRESULT r=draw_surf->Lock( 0, &desc, DDLOCK_WAIT | DDLOCK_WRITEONLY, 0 );
	if (r!=DD_OK)
		return ;
	BYTE* surfbits = (BYTE*)desc.lpSurface;
	int tx=x;
	while(*text)
	{
		outchar(surfbits,desc.lPitch,tx,y,*text,(BYTE)color);
		tx+=9;
		text++;
	}
	draw_surf->Unlock( 0 );
}

extern void DrawBlackMaskedText (int x, int y, char *text)
{
	DrawText(x,y,text,0);
}

extern void DrawRedMaskedText(int x, int y, char *text)
{
	DrawText(x,y,text,66);
}

extern void DrawWhiteMaskedText (int x, int y, char *text)
{
	DrawText(x,y,text,255);
}

extern void DrawRectangle (int x1, int y1, int x2, int y2, int color)
{
	HDC dc;
	POINT pts[5];
	pts[0].x=x1,pts[0].y=y1;
	pts[1].x=x2,pts[1].y=y1;
	pts[2].x=x2,pts[2].y=y2;
	pts[3].x=x1,pts[3].y=y2;
	pts[4].x=x1,pts[4].y=y1;
	HPEN pen=CreatePen(PS_SOLID,1,PTORGB(color));
	draw_surf->GetDC(&dc);
	SelectObject(dc,pen);
	Polyline(dc,pts,5);
	draw_surf->ReleaseDC(dc);
	DeleteObject(pen);
}

extern LPDIRECTDRAWSURFACE CompileBitmap (int x, int y, char *bitmap)
{
	int sx=(x+3)& ~3;
	LPBYTE p= new BYTE[sx*y];
	LPBYTE realdata=(LPBYTE)bitmap;
	ZeroMemory(p,sx*y);
	if(sx!=x)
	{
		for(int i=0;i<y;i++)
			memcpy(p+sx*i,bitmap+x*i,x);
		realdata=p;
	}
	LPDIRECTDRAWSURFACE surf= GetDDWin()->CreateSurface(sx,y);
	GetDDWin()->Copy_Bmp08_Surface08( surf,realdata,sx,y);
	DDCOLORKEY ddc;
    ddc.dwColorSpaceLowValue=0;
    ddc.dwColorSpaceHighValue=0;
	surf->SetColorKey(DDCKEY_SRCBLT,&ddc);
	Addsurf(sx,y,(char *)realdata,surf);
	return surf;
}

extern void FillRectangle(CONST int x,CONST int y,CONST int x1,CONST int y1,CONST int color)
{
	HDC dc;
	HBRUSH br=CreateSolidBrush(PTORGB(color));
	CRect rc(x,y,x1,y1);
	draw_surf->GetDC(&dc);
	FillRect(dc,rc,br);
	draw_surf->ReleaseDC(dc);
	DeleteObject(br);
}

extern void Line(CONST int x1,CONST int y1,CONST int x2,CONST int y2,CONST int color)
{
	HDC dc;
	HPEN pen=CreatePen(PS_SOLID,1,PTORGB(color));
	draw_surf->GetDC(&dc);
	SelectObject(dc,pen);
	MoveToEx(dc,x1,y1,NULL);
	LineTo(dc,x2,y2);
	draw_surf->ReleaseDC(dc);
	DeleteObject(pen);
}

extern void INLINE PutBitmap(CONST int x,CONST int y,CONST int xsize,CONST int ysize,LPDIRECTDRAWSURFACE bitmap)
{
	GetDDWin()->BltSurface(draw_surf,bitmap,x,y,TRUE);
}

extern INLINE void
CopyVSToVS (VScreenType source, VScreenType destination)
{
	GetDDWin()->BltSurface(destination,source,0,0,FALSE);
}

extern INLINE void
CopyToScreen (VScreenType source)
{
	GetDDWin()->BltSurface(GetDDWin()->primsurf,source,0,0,FALSE);
}

extern  COLORREF PTORGB(int color)
{
	PALETTEENTRY pt; 
	GetDDWin()->palette->GetEntries(0,color,
    1,&pt);
	return RGB(pt.peRed,pt.peGreen,pt.peBlue);
}

surf_queue surf_header={0,0,NULL,NULL,NULL};

extern void	Addsurf(int sx,int sy,char *data,LPDIRECTDRAWSURFACE lpsurf)
{
	surf_queue *p=&surf_header;
	while(p->next)
		p=p->next;
	surf_queue *q=new surf_queue;
	q->bitmap=data;
	q->lpsurf=lpsurf;
	q->sx=sx;
	q->sy=sy;
	q->next=NULL;
	p->next=q;
}

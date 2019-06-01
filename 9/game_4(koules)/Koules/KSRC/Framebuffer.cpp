/***********************************************************
*  framebuffer.c fast 8 bit framebuffer bitmap creation    *
*                routines                                  *
***********************************************************/
#include "koules.h"
#include "interface.h"

#define NCOLORS 32

#define HOLE_XCENTER (2*HOLE_RADIUS-3*HOLE_RADIUS/4)
#define HOLE_YCENTER (2*HOLE_RADIUS-HOLE_RADIUS/4)
#define HOLE_MAX_RADIUS (HOLE_RADIUS/DIV+0.5*HOLE_RADIUS/DIV)
#define HOLE_SIZE_MAX (radius*radius)

static LPDIRECTDRAWSURFACE
draw_ball_bitmap (int radius, CONST int color)
{
	char           *bitmap = NULL, *point;
	int             x, y, r;
	radius /= DIV;
	bitmap = (char *)malloc ((radius * 2) * (radius * 2) + 2);
	point = bitmap;
	for (y = 0; y < radius * 2; y++)
    for (x = 0; x < radius * 2; x++, point++)
    {
		if ((x - radius) * (x - radius) + (y - radius) * (y - radius)< (radius - 0.5) * (radius - 0.5))
		{
			r =(int)( (x - 3 * radius / 4) * (x - 3 * radius / 4) +	(y - radius / 4) * (y - radius / 4));
			r =(int)( r * 32 / (1.5 * radius) / (1.5 * radius));
			if (r > 31)
				r = 31;
	    *point = color + r;
		}
		else
			*point = 0;
	}
	return (CompileBitmap (radius * 2, radius * 2, (char *) bitmap));
}

static LPDIRECTDRAWSURFACE
draw_ball_bitmap_with_char (int radius, CONST int color,char c)
{
	char           *bitmap = NULL, *point;
	int             x, y, r;
	radius /= DIV;
	bitmap = (char *)malloc ((radius * 2) * (radius * 2) + 2);
	point = bitmap;
	for (y = 0; y < radius * 2; y++)
    for (x = 0; x < radius * 2; x++, point++)
	{
		if ((x - radius) * (x - radius) + (y - radius) * (y - radius)
	    < (radius - 0.5) * (radius - 0.5))
		{
			r =(int)( (x - 3 * radius / 4) * (x - 3 * radius / 4) +(y - radius / 4) * (y - radius / 4));
			r =(int)( r * 32 / (1.5 * radius) / (1.5 * radius));
			if (r > 31)
				r = 31;
			*point = color + r;
		}
		else
			*point = 0;
	}
	WORD k;
	LPBYTE fbuff=font_buff+c*16;
	for(int i=15;i>=0;i--)
	{
	k=*(fbuff+i);
	for(int j=0;j<8;j++,k<<=1)
		if(k & 0x80)
			*(bitmap+4+j+(15-i)*radius * 2)=0;
	}
	return (CompileBitmap (radius * 2, radius * 2, (char *) bitmap));
}

static LPDIRECTDRAWSURFACE
draw_reversed_ball_bitmap (int radius, CONST int color)
{
	char           *bitmap = NULL, *point;
	int             x, y, r;
	radius /= DIV;
	bitmap =(char *) malloc ((radius * 2) * (radius * 2) + 2);
	point = bitmap;
	for (y = 0; y < radius * 2; y++)
		for (x = 0; x < radius * 2; x++, point++)
		{
			if ((x - radius) * (x - radius) + (y - radius) * (y - radius)< (radius - 0.5) * (radius - 0.5))
			{
				r =(int)( (x - 3 * radius / 4) * (x - 3 * radius / 4) +
				(y - radius / 4) * (y - radius / 4));
				r =(int)( r * 32 / (1.5 * radius) / (1.5 * radius));
				if (r > 31)
				r = 31;
				*point = color + 16 + r / 2;
			}
		else
			*point = 0;
		}
	return (CompileBitmap (radius * 2, radius * 2, (char *) bitmap));
}
static LPDIRECTDRAWSURFACE
create_koules_bitmap (void)
{
	int i,j;
	HMODULE hm=AfxGetResourceHandle();
	HRSRC hr=::FindResource(hm,MAKEINTRESOURCE(IDR_KOULES),_T("MONOMASK"));
	HGLOBAL hg=::LoadResource(hm,hr);
	LPBYTE buff=(LPBYTE)::LockResource(hg);
	LPBYTE bitmap=new BYTE[320*80];
	TRACE("%d",buff);
	LPBYTE p=bitmap;
	for(i=0;i<80;i++)
		for(j=0;j<40;j++)
		{
			BYTE c=buff[i*40+j];
			for(int n=0;n<8;n++,c<<=1)
			{
				if(c&0x80)
					*p=0xff;
				else
					*p=0;
				p++;
			}
		}
	//160-191-blue
	const int cs=160;
	const int ce=191;
	for(i=79;i>12;i--)
		for(j=0;j<320;j++)
			if(bitmap[i*320+j])
				bitmap[i*320+j]=cs+(ce-cs)*(79-i)/65;
	
	for(i=0;i<5;i++)
		for(j=0;j<320;j++)
			if(bitmap[i*320+j])
				bitmap[i*320+j]=j<146 ? cs+(ce-cs)*j/146 : cs+(ce-cs)*(293-j)/146;

	return (CompileBitmap (320,80,(char *) bitmap));
}

static LPDIRECTDRAWSURFACE
draw_apple_bitmap (int radius, CONST int color)
{
	char           *bitmap = NULL, *point;
	int             x, y, r;
	int             radius1;
	radius /= DIV;
	bitmap = (char *)malloc ((radius * 2) * (radius * 2) + 2);
	point = bitmap;
	for (y = 0; y < radius * 2; y++)
	    for (x = 0; x < radius * 2; x++, point++)
		{
			if (DIV == 2)
				radius1 = radius * (abs (x - radius) / 2 + 25) / 30;
			else
				radius1 = radius * (abs (x - radius) / 2 + 50) / 60;
			if (radius1 > radius)
				radius1 = radius;
			if ((x - radius) * (x - radius) + (y - radius) * (y - radius)
				< ((radius1) * (radius1)))
			{
				r =(int)( (x - 3 * radius / 4) * (x - 3 * radius / 4) +
				(y - radius / 4) * (y - radius / 4));
				r =(int)( 3 + r * 22 / (1.5 * radius1) / (1.5 * radius1));
				if (r > 31)
					r = 31;
				*point = color + r;
			}
		else
			*point = 0;
		}
	return (CompileBitmap (radius * 2, radius * 2, (char *) bitmap));
}

static double    err = 0.0;
#define errdist(c) c

void create_bitmap ()
{
	int             x, y, r, po, radius;
	char (* hole_data)[HOLE_RADIUS * 2]= new char [HOLE_RADIUS * 2][HOLE_RADIUS * 2];
	char (* ehole_data)[HOLE_RADIUS * 2]= new char [HOLE_RADIUS * 2][HOLE_RADIUS * 2];
	for (x = 0; x < HOLE_RADIUS * 2; x++)
		for (y = 0; y < HOLE_RADIUS * 2; y++)
		{
			if (DIV == 1)
				radius = HOLE_RADIUS / 2 + (int) (atan (fabs (x - HOLE_RADIUS + 0.5) / fabs (y - HOLE_RADIUS + 0.5)) * HOLE_RADIUS / 2) % (HOLE_RADIUS / 2);
			else
				radius = HOLE_RADIUS / 4;
			if ((x - HOLE_RADIUS / DIV) * (x - HOLE_RADIUS / DIV) + (y - HOLE_RADIUS / DIV) * (y - HOLE_RADIUS / DIV)
				< radius * radius)
			{
				r = (x - HOLE_RADIUS / DIV) * (x - HOLE_RADIUS / DIV) +
				(y - HOLE_RADIUS / DIV) * (y - HOLE_RADIUS / DIV);
				r = r * 24 / HOLE_SIZE_MAX;
				if (r > 23)
					r = 23;
				hole_data[x][y] = 64 + r + 1;
				ehole_data[x][y] = 128 + r + 1;
			}
		else
			hole_data[x][y] = 0,
			ehole_data[x][y] = 0;
		}
	hole_bitmap=CompileBitmap (HOLE_RADIUS * 2, HOLE_RADIUS * 2, (char *) hole_data);
	ehole_bitmap=CompileBitmap (HOLE_RADIUS * 2, HOLE_RADIUS * 2, (char *) ehole_data);
	for (po = 0; po < MAXROCKETS; po++)
		eye_bitmap[po] = draw_ball_bitmap (EYE_RADIUS+1, 32 + 32 * po);
	ball_bitmap = draw_ball_bitmap (BALL_RADIUS, ball (0));
	mouse_bitmap = draw_ball_bitmap (MOUSE_RADIUS * DIV, 32 + 32 * 2);
	bball_bitmap = draw_ball_bitmap (BBALL_RADIUS, 4 * 32);
	apple_bitmap = draw_apple_bitmap (APPLE_RADIUS, ball (0));
	inspector_bitmap = draw_ball_bitmap (INSPECTOR_RADIUS, 160);
	lunatic_bitmap = draw_reversed_ball_bitmap (LUNATIC_RADIUS, 192);
	lball_bitmap[0] = draw_ball_bitmap_with_char (BALL_RADIUS, 4 * 32,'A');
	lball_bitmap[1] = draw_ball_bitmap_with_char (BALL_RADIUS, 5 * 32,'M');
	lball_bitmap[2] = draw_reversed_ball_bitmap (BALL_RADIUS, 192);
	lball_bitmap[3] = draw_reversed_ball_bitmap (BALL_RADIUS, 0);
	lball_bitmap[4] = draw_reversed_ball_bitmap (BALL_RADIUS, 3 * 32 - 5);
	for (x = 0; x < 5; x++)
		rocket_bitmap[x] = draw_ball_bitmap (ROCKET_RADIUS, rocketcolor[x]);
	koules_bitmap=create_koules_bitmap();
}

void
drawstarbackground ()
{
	int             x;
	int             x1, y1, c1;
	HDC dc;
	GetDDWin()->ClearSurface(starbackground,0);
	starbackground->GetDC(&dc);
	for (x = 0; x < 700 / DIV / DIV; x++)
	{
		x1 = rand () % MAPWIDTH;
		y1 = rand () % (MAPHEIGHT + 20);
		c1 = rand () % 32 + 192;
		SetPixel (dc,x1, y1, c1);
    }
	starbackground->ReleaseDC(dc);
}

void
createbackground ()
{
	int             x, y;
	unsigned char           *data;
	CRect rc=GetDDWin()->GetDisplayRect();
    data = (unsigned char *) new char[GAMEHEIGHT*GAMEWIDTH];
	for (y = 0; y < GAMEHEIGHT; y++)
		for (x = 0; x < GAMEWIDTH; x++)
		{
		int             i = 0;
		int             n = 0;
		int             c;
		if (x > 0)
		{
			i += data[x - 1+y*rc.right];
			n++;
		}
		if (y > 0)
		{
			i += data[x+(y-1)*rc.right];
			n++;
		}
		c = (i + (rand () % 16)) / (n + 1);
		if (c > 9)
			c = 9;
		data[x+y*rc.right]=c & 0xff;
		}
		for (y = 0; y < GAMEHEIGHT; y++)
			for (x = 0; x < GAMEWIDTH; x++)
				data[x+y*rc.right]=back (0) + data[x+y*rc.right];
  	GetDDWin()->Copy_Bmp08_Surface08(background,data,GAMEWIDTH,GAMEHEIGHT);
	delete data;
}


void
drawbackground ()
{
	SetScreen (background);
	GetDDWin()->ClearSurface(background,0);
	createbackground();
	Line (0, MAPHEIGHT, MAPWIDTH , MAPHEIGHT, back (16));
}

#ifndef INTERFACE_H
#define INTERFACE_H

#include "..\DirectDrawWin.H"

#define EYE_RADIUS (DIV==1?5:6)
#define MOUSE_RADIUS 4

typedef LPDIRECTDRAWSURFACE VScreenType;


extern LPDIRECTDRAWSURFACE draw_surf;
extern LPBYTE font_buff;

extern VScreenType background;
extern VScreenType starbackground;

extern int      GAMEWIDTH;
extern int      GAMEHEIGHT;
extern int      MAPWIDTH;
extern int      MAPHEIGHT;
extern int      DIV;

extern LPDIRECTDRAWSURFACE 
		bball_bitmap,
		apple_bitmap,
		inspector_bitmap,
		mouse_bitmap,
        lunatic_bitmap,
		lball_bitmap[NLETTERS],
        hole_bitmap,
		ehole_bitmap,
		ball_bitmap,
		eye_bitmap[MAXROCKETS],
        rocket_bitmap[MAXROCKETS],
		koules_bitmap;
				

extern COLORREF				PTORGB(int color);
extern int					TextLen (char *text);
extern void					DrawBlackMaskedText (int x, int y, char *text);
extern void					DrawWhiteMaskedText (int x, int y, char *text);
extern void					DrawRedMaskedText(int x, int y, char *text);
extern void					DrawText(int x, int y, char *text,int color);
extern void					DrawRectangle (int x1, int y1, int x2, int y2, int color);
extern LPDIRECTDRAWSURFACE	CompileBitmap (int x, int y, char *bitmap);
extern void					FillRectangle(CONST int x,CONST int y,CONST int x1,CONST int y1,CONST int color);
extern void					Line(CONST int x1,CONST int y1,CONST int x2,CONST int y2,CONST int color);
extern void					PutBitmap(CONST int x,CONST int y,CONST int xsize,CONST int ysize,LPDIRECTDRAWSURFACE bitmap);
extern void					CopyVSToVS (VScreenType source, VScreenType destination);
extern void					CopyToScreen (VScreenType source);
void	INLINE				SetScreen(LPDIRECTDRAWSURFACE screen)
{
	draw_surf=screen;
}
  
struct surf_queue//for restore losted surf
{
	int sx;
	int sy;
	char *bitmap;
	LPDIRECTDRAWSURFACE lpsurf;
	surf_queue * next;
};

extern surf_queue surf_header;

extern void	Addsurf(int sx,int sy,char *data,LPDIRECTDRAWSURFACE lpsurf);
extern void     setcustompalette (int, double);
extern void     fadeout ();
extern void     fadein ();

#endif
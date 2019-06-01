/***********************************************************
*  init.c jlib depended initialization routines            *
***********************************************************/
#include "koules.h"
#include "input.h"
#include "interface.h"
#include "framebuffer.h"
#include "sound.h"

int             GAMEWIDTH = 640;
int             GAMEHEIGHT = 460;
int             MAPWIDTH = 640;
int             MAPHEIGHT = 460;
int             DIV = 1;



extern void     fadein1 ();

extern void     points ();
extern void     points1 ();
char            hole_data[HOLE_RADIUS * 2][HOLE_RADIUS * 2];
char            ehole_data[HOLE_RADIUS * 2][HOLE_RADIUS * 2];
extern unsigned char     rocketcolor[5];
extern void     starwars ();
extern void     game ();


#define NCOLORS 32

#define HOLE_XCENTER (2*HOLE_RADIUS-3*HOLE_RADIUS/4)
#define HOLE_YCENTER (2*HOLE_RADIUS-HOLE_RADIUS/4)
#define HOLE_MAX_RADIUS (HOLE_RADIUS/DIV+0.5*HOLE_RADIUS/DIV)
#define HOLE_SIZE_MAX (radius*radius)

static int      koules_vt;
static int      separate_vt;
static int      original_vt;
static int      ttyfd;

char *framebuff;

static void initialize ()
{
	CRect rc=GetDDWin()->GetDisplayRect();
	GAMEWIDTH=rc.right;
	GAMEHEIGHT=rc.bottom-34;
	MAPWIDTH=GAMEWIDTH;
	MAPHEIGHT=rc.bottom-34;
	setcustompalette (0, 1);
	background = GetDDWin()->CreateSurface(GAMEWIDTH,GAMEHEIGHT);
	starbackground = GetDDWin()->CreateSurface(MAPWIDTH,rc.bottom);
	draw_surf=GetDDWin()->backsurf;
}

void uninitialize ()
{
	fadeout();
	GetDDWin()->ClearSurface(GetDDWin()->primsurf,0,NULL);
	GetDDWin()->ClearSurface(GetDDWin()->backsurf,0,NULL);
}

extern void gameinit(void)
{
	srand (time (NULL));
	HMODULE hm=AfxGetResourceHandle();
	HRSRC hr=::FindResource(hm,MAKEINTRESOURCE(IDR_ASCIIFONT),_T("ASCIIFONT"));
	HGLOBAL hg=::LoadResource(hm,hr);
	font_buff=(LPBYTE)::LockResource(hg);
	InitDirectSound();
	sound = sndinit;
	create_bitmap ();
	initialize ();
	gamemode = MENU;
	drawbackground ();
	drawstarbackground ();
	keys[0][0] = SCANCODE_CURSORBLOCKUP;
	keys[0][1] = SCANCODE_CURSORBLOCKDOWN;
	keys[0][2] = SCANCODE_CURSORBLOCKLEFT;
	keys[0][3] = SCANCODE_CURSORBLOCKRIGHT;

	keys[1][0] = SCANCODE_CURSORUP;
	keys[1][1] = SCANCODE_CURSORDOWN;
	keys[1][2] = SCANCODE_CURSORLEFT;
	keys[1][3] = SCANCODE_CURSORRIGHT;
	starwars ();
	load_rc ();

	SetCurPos(GetDDWin()->GetDisplayRect().Width()/2,GetDDWin()->GetDisplayRect().Height()/2);
	init_menu ();
}
/***********************************************************
*  menu.c                                                  *
*   GUI menuing system					   *
***********************************************************/

#include "koules.h"
#include "interface.h"
#include "input.h"
#include "sound.h"
#define TEXTW 9
#define TEXTH 16
int		onmenu=-1;

typedef struct
{
	char           *text;
    void            (*func) ();
}
Menu;

typedef struct
{
	int             x;
	int				y;
	int				*number;
	int				max;
	int				min;
    int             line;
    void            (*func) ();
}
Numbers;

int             ssound = 1;
static Numbers  minim[2], maxim[2];
static int      nmenu;
static int      nnumbers;
static Menu     menu[20];
static int      selected = 0;
static double    mx1, my1, mx1p, my1p;
static double    mx2, my2, mx2p, my2p;
static int      mtime;
static char    playertext[] = " 1  PLAYER";
static char    leveltext[] = "LEVEL  000 ";

int YPOSITION(int i)
{
	return (MAPHEIGHT/2+20-5*nmenu+20*i);
}

int XPOSITION(int i)
{
	return (MAPWIDTH/2-TextLen(menu[i].text)/2);
}

int XPOSITION1(int i)
{
	return (MAPWIDTH/2+TextLen(menu[i].text)/2);
}

static int      player, keynum, lastplayer;
static void     main_menu ();
static void     change_menu ();

static void
player_change ()
{
	player = (selected - 2) / 2;
	lastplayer = (selected - 2) / 2;

	if (player == mouseplayer)
		return;
	keynum = 0;
	gamemode = KEYS;
}


static void
control_change ()
{
  int             player;
  player = (selected - 1) / 2;

  if (player == mouseplayer)
    {
      mouseplayer = -1;
    }
  else

    {
      if (!rotation[player])
	{
	  rotation[player] = 1;
	}
      else
	{
	  rotation[player] = 0;

	  if (mouseplayer == -1)
	    mouseplayer = player;

	}
    }
  change_menu ();
}

void
start ()
{
	int             i;
	for (i = 0; i < nrockets; i++)
    {
      object[i].score = 0;
    }
	sound = ssound;
	gamemode = GAME;
	show_playerdata=TRUE;
	show_player=1;
	gameplan_init ();
	init_objects ();
}


static void
playerchange ()
{
	if (nrockets > 5)
		nrockets = 1; 
	playertext[1] = nrockets + '0';
}

static void
levelchange ()
{
	sprintf (leveltext, "LEVEL  %03i ", lastlevel + 1);
}


static void
quit ()
{
	save_rc();
	uninitialize ();
	AfxGetMainWnd()->PostMessage(WM_COMMAND,ID_APP_EXIT,NULL);
}

static void
fit_selector ()
{
	mtime = MENUTIME;
	mx1p = (XPOSITION (selected) - 2 - mx1) / mtime;
	mx2p = (XPOSITION1 (selected) + 2 - mx2) / mtime;
	my1p = (YPOSITION (selected) - 2 - my1) / mtime;
	my2p = (YPOSITION (selected) + TEXTH+2 + 0 - my2) / mtime;
}

static void
to_main_menu ()
{
	save_rc ();
	main_menu ();
}

static void
change_menu ()
{
	static char     s[2][5][40], *s1;
	int             i;
    {
		menu[0].text = "BACK TO MAIN MENU";
		menu[0].func = to_main_menu;
    }
	nnumbers = 0;
	for (i = 0; i < nrockets; i++)
    {
		if (i == mouseplayer)
			s1 = "MOUSE";
		else if (rotation[i])
			s1 = "ROTATION KEYBOARD";
		else
			s1 = "KEYBOARD";
		sprintf (s[0][i], "PLAYER %i:%s", i + 1, s1);

		if (i == mouseplayer)
			sprintf (s[1][i], "NO CONFIG FOR MOUSE");
		else
			sprintf (s[1][i], "CHANGE KEYS");
		menu[i * 2 + 1].text = s[0][i];
		menu[i * 2 + 2].text = s[1][i];
		menu[i * 2 + 1].func = control_change;
		menu[i * 2 + 2].func = player_change;
	}
	nmenu = nrockets * 2 + 1;
	if (selected >= nmenu)
	    selected = 0;
	fit_selector ();
}

static void
deathmatch ()
{
	gameplan = DEATHMATCH;
	main_menu ();
}

static void
cooperative ()
{
	gameplan = COOPERATIVE;
	main_menu ();
}

static void
setsound ()
{
	if (sndinit)
		ssound = !ssound;
	main_menu ();
}

static void
veryhard ()
{
	difficulty = 0;
	main_menu ();
}

static void
hard ()
{
	difficulty = 1;
	main_menu ();
}

static void
medium ()
{
	difficulty = 2;
	main_menu ();
}

static void
easy ()
{
	difficulty = 3;
	main_menu ();
}

static void
veryeasy ()
{
	difficulty = 4;
	main_menu ();
}

static void
change_mode ()
{
	nnumbers = 0;
	menu[0].text = "DEATH MATCH(DOOM)";
	menu[0].func = deathmatch;
	menu[1].text = "COOPERATIVE";
	menu[1].func = cooperative;
	nmenu = 2;
	selected = 1;
	fit_selector ();
}

static void
change_obtiznost ()
{
	menu[0].text = "NIGHTMARE";
	menu[0].func = veryhard;
	menu[1].text = "HARD";
	menu[1].func = hard;
	menu[2].text = "MEDIUM";
	menu[2].func = medium;
	menu[3].text = "EASY";
	menu[3].func = easy;
	menu[4].text = "VERY EASY";
	menu[4].func = veryeasy;
	nnumbers = 0;
	nmenu = 5;
	selected = 2;
	fit_selector ();
}

static void
main_menu ()
{
	nnumbers = 2;
	nmenu = 8;

	menu[0].text = "START GAME";
	menu[1].text = playertext;
	menu[2].text = leveltext;
	menu[3].text = "CONTROL";
	menu[4].text = "GAME MODE";
	menu[5].text = "DIFFICULTY";
	menu[6].text = ssound ? "SOUND ON" : (sndinit ? "SOUND OFF" : "SOUND OFF-NOT INITIALIZED");
	menu[7].text = "QUIT";

	menu[0].func = start;
	menu[1].func = playerchange;
	menu[2].func = playerchange;
	menu[3].func = change_menu;
	menu[4].func = change_mode;
	menu[5].func = change_obtiznost;
	menu[6].func = setsound;
	menu[7].func = quit;
	minim[0].func = playerchange;	
	maxim[0].func = playerchange;
	maxim[1].func = levelchange;
	minim[1].func = levelchange;

	minim[0].x = XPOSITION (1);
	minim[0].y = YPOSITION (1);
	maxim[0].x = XPOSITION (1) + TEXTW * 2;
	maxim[0].y = YPOSITION (1);
	minim[1].x = XPOSITION (2) + 6 * TEXTW;
	minim[1].y = YPOSITION (2);
	maxim[1].x = XPOSITION (2) + 10 * TEXTW;
	maxim[1].y = YPOSITION (2);
	minim[0].max = 5;
	minim[0].min = 1;
	maxim[0].max = 5;
	maxim[0].min = 1;
	minim[0].line = 1;
	minim[0].number = &nrockets;
	maxim[0].line = 1;
	maxim[0].number = &nrockets;
	minim[1].line = 2;
	minim[1].number = &lastlevel;
	minim[1].max = maxlevel;
	minim[1].min = 0;
	maxim[1].line = 2;
	maxim[1].number = &lastlevel;
	maxim[1].max = maxlevel;
	maxim[1].min = 0;
	
	playerchange ();
	levelchange ();

	selected = 0;
	fit_selector ();
}
/***************************************************************************/
/***************************************************************************/
void
init_menu ()
{
	mx1 = 10;
	mx2 = MAPWIDTH - 10;
	my2 = 10;
	my2 = MAPHEIGHT - 10;
	ssound = sound;
	playertext[1] = nrockets + '0';
	main_menu ();
}

#define MLine(dc,x,y,x1,y1) MoveToEx(dc,x,y,NULL),LineTo(dc,x1,y1)
void
draw_menu (CONST int draw)
{
	int             i;
	
	sound = 0;
	if (draw)
    {
		levelchange ();
		DrawRectangle ((int) mx1, (int) my1, (int) mx2, (int) my2, ball (2));
		DrawRectangle ((int) mx1 + 1, (int) my1 + 1, (int) mx2 + 1, (int) my2 + 1, ball (20));
		
		{
			HDC dc;
			HPEN pen=CreatePen(PS_SOLID,1,PTORGB(ball (2)));
			draw_surf->GetDC(&dc);
			SelectObject(dc,pen);
			
			for (i = 0; i < nnumbers; i++)
			{	
			//we should do it faster
			int sy=minim[i].y + TEXTH/2 -1;
			MLine (dc,minim[i].x, sy, minim[i].x + 6, sy );
			MLine (dc,minim[i].x + 3, sy - 3, minim[i].x	, sy);
			MLine (dc,minim[i].x + 4, sy - 3, minim[i].x + 1, sy);
			MLine (dc,minim[i].x + 3, sy + 3, minim[i].x	, sy);
			MLine (dc,minim[i].x + 4, sy + 3, minim[i].x + 1, sy);
			
			sy=maxim[i].y + TEXTH/2 -1;
			MLine (dc,maxim[i].x + 2, sy, maxim[i].x + 8, sy);
			MLine (dc,maxim[i].x + 5, sy - 3, maxim[i].x + 8,sy);
			MLine (dc,maxim[i].x + 4, sy - 3, maxim[i].x + 7,sy);
			MLine (dc,maxim[i].x + 5, sy + 3, maxim[i].x + 8,sy);
			MLine (dc,maxim[i].x + 4, sy + 3, maxim[i].x + 7,sy);
			}
			draw_surf->ReleaseDC(dc);
			DeleteObject(pen);
			
		}
		for (i = 0; i < nmenu; i++)
		{
			if(i==onmenu)
			{
				DrawRedMaskedText ((int) XPOSITION (i) + 2, (int) YPOSITION (i) + 2, menu[i].text);
				DrawRedMaskedText ((int) XPOSITION (i) + 1, (int) YPOSITION (i) + 1, menu[i].text);
			}
			else
			{
				DrawWhiteMaskedText ((int) XPOSITION (i) + 1, (int) YPOSITION (i) + 1, menu[i].text);
				DrawWhiteMaskedText ((int) XPOSITION (i), (int) YPOSITION (i), menu[i].text);
			}
		}
	}
	if (mtime)
    {
		mtime--;
		my1 += my1p;
		mx1 += mx1p;
		my2 += my2p;
		mx2 += mx2p;
    }
	PutBitmap((GAMEWIDTH-320)/2,GAMEHEIGHT/4-80/2,320,80,koules_bitmap);
}

static int      inctime, changed, waittime;
static void
increase (int i)
{
	changed = 1;
	if (waittime)
    {
		waittime--;
		return;
    }
	waittime = inctime;
	if (inctime > 1)
		inctime--;
	else
		(*maxim[i].number) += 2;
	(*maxim[i].number)++;
	if (*maxim[i].number > maxim[i].max)
		*maxim[i].number = maxim[i].min;
	maxim[i].func ();
	save_rc ();
}

static void
decrease (int i)
{
	changed = 1;
	if (waittime)
    {
		waittime--;
		return;
    }
	waittime = inctime;
	if (inctime > 1)
		inctime--;
	else
		(*maxim[i].number) -= 2;
	(*minim[i].number)--;
	if (*minim[i].number < minim[i].min)
		*minim[i].number = minim[i].max;
	minim[i].func ();
	save_rc ();
}

void
menu_keys ()
{
	static int      enter;
	int             ent = 0;

	static int      button;
	int             but = 0;

	if (maxim[1].max != maxlevel)
	    main_menu ();
	changed = 0;
	if (IsPressingLeft ())
    {
		int             i;
		for (i = 0; i < nnumbers; i++)
			if (maxim[i].line == selected)
				decrease (i);
    }
	if (IsPressingRight ())
    {
		int             i;
		for (i = 0; i < nnumbers; i++)
			if (maxim[i].line == selected)
				increase (i);
	}

	but = MouseButtons ();
	if (but)
    {
		int             i;
		for (i = 0; i < nnumbers; i++)
		{
			if (MouseX () > maxim[i].x &&
				MouseX () < maxim[i].x + TEXTW &&
				MouseY () > maxim[i].y &&
				MouseY () < maxim[i].y + TEXTH)
				increase (i);
			if (MouseX () > minim[i].x &&
				MouseX () < minim[i].x + TEXTW &&
				MouseY () > minim[i].y &&
				MouseY () < minim[i].y + TEXTH)
				decrease (i);
		}
    }
	CPoint pt(MouseX(),MouseY());
	onmenu=-1;
	for(int i=0;i<nmenu;i++)
	{
		CRect rc((int) XPOSITION (i),
			(int) YPOSITION (i), (int) XPOSITION1 (i),
			(int) YPOSITION (i) + TEXTH);
		if(rc.PtInRect(pt))
		{
			onmenu=i;
			break;
		}
	}
	if (onmenu!=-1)
	{
		selected = onmenu;
		fit_selector ();
	}
	if (!but && button)
    {
		if (onmenu!=-1)
		{
			menu[selected].func ();
			button = 0;
			return;
		}
    }
	button = but;

	if (IsPressedEsc ())
    {
		if (nnumbers == 2)
			quit ();
		to_main_menu ();
	}
	if (IsPressingUp () && !mtime && selected > 0)
	    selected--, fit_selector ();
	if (IsPressingDown () && !mtime && selected < nmenu - 1)
	    selected++, fit_selector ();
	if (IsPressingEnter () && !mtime)
		ent = 1;
	if (!ent && enter)
    {
		menu[selected].func ();
    }
	enter = ent;
	if (!changed)
		inctime = 7, waittime = 0;
}

void
keys_keys ()
{
	static int      lscan_code;
	int             scan_code;
	scan_code = GetKey ();
	if (!scan_code && lscan_code)
    {
		keys[player][keynum] = lscan_code;
		keynum++;
		if (keynum > (rotation[player] ? 2 : 3))
		{
			player++;
			keynum = 0;
			if (player > lastplayer)
			{
				change_menu ();
				gamemode = MENU;
			}
		}
    }
	lscan_code = scan_code;
}


void
draw_keys (int draw)
{
	char            s[20];
	static char    *key[4] =
	{"UP", "DOWN", "LEFT", "RIGHT"};
	static char    *rkey[3] =
	{"ACCELERATION", "ROTATE LEFT", "ROTATE RIGHT"};
	if (!draw)
		return;
	nmenu = 2;
	sprintf (s, "PLAYER:%i", player + 1);
	DrawWhiteMaskedText ((int) (MAPWIDTH / 2 - TEXTW * strlen (s)), (int) YPOSITION (0), s);
	if (rotation[player])
		sprintf (s, "KEY:%s", rkey[keynum]);
	else
		sprintf (s, "KEY:%s", key[keynum]);
		DrawWhiteMaskedText ((int) (MAPWIDTH / 2 - TEXTW * strlen (s)), (int) YPOSITION (1), s);
}


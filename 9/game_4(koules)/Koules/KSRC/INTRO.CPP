/***********************************************************
*  intro.c intro outro code                                *
 ***********************************************************/
#include "koules.h"
#include "interface.h"
#include "input.h"
#include "text.h"
#include "sound.h"
#define def 20
extern void     fadein1 ();
extern void     points ();
extern void     points1 ();

void
draw_koules (CONST int c, CONST int s, CONST int r)
{
	int             i;
	for (i = 0; i < 360; i += 60)
		switch (c)
		{
		case 0:
			PutBitmap ((int) (MAPWIDTH / 2 - BALL_RADIUS / DIV + sin (RAD (i + s)) * r),
			(int) (MAPHEIGHT / 2 - BALL_RADIUS / DIV + cos (RAD (i + s)) * r),
				BALL_RADIUS * 2 / DIV, BALL_RADIUS * 2 / DIV, ball_bitmap);
			break;
		case 1:
			PutBitmap ((int) (MAPWIDTH / 2 - BALL_RADIUS / DIV + sin (RAD (i + s)) * r),
				(int) (MAPHEIGHT / 2 - BALL_RADIUS / DIV + cos (RAD (i + s)) * r),
				BALL_RADIUS * 2 / DIV, BALL_RADIUS * 2 / DIV, lball_bitmap[0]);
		break;
		default:
			PutBitmap ((int) (MAPWIDTH / 2 - BALL_RADIUS / DIV + sin (RAD (i + s)) * r),
			(int) (MAPHEIGHT / 2 - BALL_RADIUS / DIV + cos (RAD (i + s)) * r),
			BALL_RADIUS * 2 / DIV, BALL_RADIUS * 2 / DIV, lball_bitmap[1]);
		break;
      }
}

void koulescreator (CONST int r)
{
	int             time = 100;
	int             z1;
	int             x, y;
	int             x1, y1, i;
	Effect (S_CREATOR1);
	for (i = 0; i < 360; i += 60)
    {
		x1 =(int)( (MAPWIDTH / 2 - +sin (RAD (i)) * r));
		y1 =(int)( (MAPHEIGHT / 2 - +cos (RAD (i)) * r));
		for (z1 = 0; z1 < BALL_RADIUS * BALL_RADIUS * M_PI / DIV / DIV; z1++)
		{
			x = rand () % GAMEWIDTH;
			y = rand () % GAMEHEIGHT;
			addpoint (x * 256 * DIV, y * 256 * DIV,
				(x1 - x) * 256 / (time) * DIV,
				(y1 - y) * 256 / (time) * DIV,
				ball (rand () % 32),
				time);
		}
    }
}

void starcreator ()
{
	int             time = 100;
	int             z;
	int             x, y;
	Effect (S_CREATOR1);
	for (z = 0; z < ROCKET_RADIUS * ROCKET_RADIUS * M_PI / DIV / DIV; z++)
    {
		x = rand () % GAMEWIDTH;
		y = rand () % GAMEHEIGHT;
		addpoint (x * 256 * DIV, y * 256 * DIV,
			(MAPWIDTH / 2 - x) * 256 / (time) * DIV,
			(MAPHEIGHT / 2 - y) * 256 / (time) * DIV,
			(rand () % 32),
			time);
    }
}

void
draw_player (CONST int x, CONST int y, CONST double r, CONST int z, CONST int r1)
{
	int             x1, y1;
	PutBitmap ((int) x - ROCKET_RADIUS / DIV, (int) y - ROCKET_RADIUS / DIV,
		ROCKET_RADIUS * 2 / DIV, ROCKET_RADIUS * 2 / DIV, rocket_bitmap[z]);
	x1 =(int)( x * DIV + sin (r - RAD (30)) * r1 - EYE_RADIUS);
	y1 =(int)( y * DIV + cos (r - RAD (30)) * r1 - EYE_RADIUS);
	PutBitmap (x1 / DIV, y1 / DIV,
	     EYE_RADIUS * 2 / DIV, EYE_RADIUS * 2 / DIV, eye_bitmap[z]);
	x1 =(int)( x * DIV + sin (r + RAD (30)) * r1 - EYE_RADIUS);
	y1 =(int)( y * DIV + cos (r + RAD (30)) * r1 - EYE_RADIUS);
	PutBitmap (x1 / DIV, y1 / DIV,
	     EYE_RADIUS * 2 / DIV, EYE_RADIUS * 2 / DIV, eye_bitmap[z]);
}

#define TEXTW 50
#define TEXTH 25

void
starwars ()
{
  int             y, i, z;
  double           r[3];
  double          angle = 0;

  int             actu = 0;
  int             time = 0;
  int             time1 = 0;

  int             playx = 0, playy = 0;
  int             bballx = 0, bbally = 0;
  double          playr = RAD (0), playp = 0.03;
  int             sizes[300];
  DWORD				VlastClk;
  DWORD				VnewClk;
  int             wait = 0;

  double          r1;
  double          rp[3];
	Effect (S_START);
	fadeout ();
	for (y = 0; y < TEXTSIZE; y++)
		sizes[y] = (GAMEWIDTH-TextLen(stext[y])) / 2;
  VlastClk=timeGetTime();
  VnewClk=timeGetTime();

  r[1] = r[2] = r[0] = sqrt ((MAPWIDTH / 2) * (MAPWIDTH / 2) +
			     (MAPHEIGHT / 2) * (MAPHEIGHT / 2));
  rp[0] = 0.0 / DIV;
  rp[1] = 0.6 / DIV;
  rp[2] = 0.6 / DIV;
  r1 = r[0];
	int t=650;
	DWORD tc=timeGetTime();;
#define speed 0.1
	for (i = -720; i < (TEXTSIZE + 10) * TEXTW; i += 1)
    {
		VlastClk=timeGetTime();
		CopyVSToVS (starbackground, GetDDWin()->backsurf);
		SetScreen (GetDDWin()->backsurf);
		for (z = 0; z < 3; z++)
		{
			if (r[z] <= ROCKET_RADIUS / DIV + BALL_RADIUS / DIV)
			{
				rp[z] = -6 / DIV;
				Effect (S_COLIZE);
			}
		if (r[z] < r1)
			draw_koules (rp[z] > 0 ? z : 0, (int) angle, (int)r[z]);
		}
		if (bbally > -20 && bballx)
			PutBitmap ((int) bballx - (BBALL_RADIUS) / DIV, bbally,
			BBALL_RADIUS * 2 / DIV, BBALL_RADIUS * 2 / DIV, bball_bitmap);
		points ();
		for (y = 0; y < TEXTSIZE; y++)
		{
			if (y * TEXTW + - i <600 && y * TEXTW + - i > -16)
			{
				textcolor = (40 + (y * TEXTW - i)) * 32 / 650;
				if (textcolor <= 0)
					continue;
				actu = y;
				DrawText(sizes[y], y * TEXTW - i,stext[y],textcolor);
			}
		}
		if (playx)
			draw_player (playx, playy, playr, 0, EYE_RADIUS1);
		if (actu == PLAYERLINE && !time)
			starcreator (), time = 1;
		if(t!=0)
		{
			DWORD temp=timeGetTime();
			t-=(int)((temp-tc)*speed);
			tc=temp;
			if(t<0)
				t=0;
		}
		PutBitmap(0,t,320,80,koules_bitmap);
		
		CopyToScreen (GetDDWin()->backsurf);
		fadein1 ();
		tc=timeGetTime();
		points1 ();


		if (actu >= KOULESLINE && !time1)
		koulescreator (MAPHEIGHT / 2 - 20), time1 = 1;
		if (time1)
			time1++;
		if (time1 == 100)
	r[0] = MAPHEIGHT / 2 - 20;
      if (time1 > 100)
	r[0] -= rp[0], angle += 0.3;


      playr += playp;
      if (playr < RAD (-45))
	playp = 0.015, playr = RAD (-45);
      if (playr > RAD (45))
	playp = -0.03, playr = RAD (45);
      if (actu >= D1LINE)
	r[1] -= rp[1];
      if (actu >= D2LINE)
	r[2] -= rp[2];
      if (actu >= BLINE && !bballx)
	bballx = MAPWIDTH / 2,
	  bbally = MAPHEIGHT + 30;
      if (bballx)
	bbally--;
      if (bbally > 0 && bbally < MAPHEIGHT / 2 + ROCKET_RADIUS / 2)
	{
	  playy -= 10;
	  	     Effect (S_END);
	}
      if (time)
	time++;
      if (time == 100)
	  {
			playx = MAPWIDTH / 2, playy = MAPHEIGHT / 2, playr = RAD (180), rp[0] = 1.5 / DIV;
	  	  Effect (S_CREATOR2);
	  }
	VnewClk=timeGetTime();
		wait = (int)((def-VnewClk + VlastClk)/5)*5;
		if(wait>0)
	      Sleep (wait);
	  TRACE("%d,",wait);  
      UpdateInput ();
      if (Pressed ())
	  {
		fadeout ();
		GetDDWin()->ClearSurface(GetDDWin()->primsurf,0,NULL);
		fadein();
		return;
		}
	
    }
  fadeout ();
  GetDDWin()->ClearSurface(GetDDWin()->primsurf,0,NULL);
  fadein();
}

void clearpoints ()
{
	int             i;
	for (i = 0; i < MAXPOINT; i++)
		point[i].time = 0;
}

void outro (CONST int size, char *text[])
{
	int             y, i;

	int             actu = -1;

	int             sizes[300];
  DWORD				VlastClk;
  DWORD				VnewClk;
	int             wait = 0;

	fadeout ();
	clearpoints ();
	for (y = 0; y < size; y++)
		sizes[y] = (GAMEWIDTH-TextLen(text[y])) / 2;
	VlastClk=timeGetTime();
	VnewClk=timeGetTime();

	for (i = -600; i < (size + 4) * TEXTW; i += 1)
    {
		VlastClk=timeGetTime();
		SetScreen (GetDDWin()->backsurf);
		CopyVSToVS (starbackground, GetDDWin()->backsurf);
		points ();
		for (y = 0; y < size; y++)
	    {
			if (y * TEXTW - i <600 && y * TEXTW - i > -16)
			{
				textcolor = (40 + (y * TEXTW - i)) * 32 / 650;
				if (textcolor <= 0)
					continue;
				actu = y;
				DrawText(sizes[y], y * TEXTW - i,text[y],textcolor);
			}
	    }
		CopyToScreen (GetDDWin()->backsurf);
		fadein1 ();
		points1 ();
		VnewClk=timeGetTime();
		wait = (int)((def-VnewClk + VlastClk)/10)*10;
		if(wait>0)
	      Sleep (wait);

		if (actu >= 0)
		{
			UpdateInput ();
			if (Pressed ())
			{
			fadeout ();
			GetDDWin()->ClearSurface(GetDDWin()->primsurf,0,NULL);
			fadein();
			return;
			}
		}
    }
	fadeout ();
  	GetDDWin()->ClearSurface(GetDDWin()->primsurf,0,NULL);
	fadein();
	return;
}

void staraccel (CONST double x1, CONST double y1, CONST double r)
{
	int             y;
	for (y = 0; y < 5 / DIV / DIV; y++)
    {
		double           p;
		p = RAD (rand () % 45 - 22);
		addpoint ((int)(x1 * 256),
			(int)(y1 * 256),
			(int)((-sin (r + p) * 0.08 * 10) * (rand () % 512)),
			(int)((-cos (r + p) * 0.08 * 10) * (rand () % 512)),
			(int)(rocket (rand () % 16)), 30);
    }
}

void outro2 ()
{
	int             y, i, z;
	int             actu = 0;
	double           width = 0;
	int             size = TEXTSIZE2;
	int             sizes[300], nrockets1;
	int             wait = 0;
	int		 first=1;
	double           playy = MAPHEIGHT + 20;
	double           playr = RAD (180);
	double           playp = 0;
	double           er = EYE_RADIUS1;
	double           erp = 2;

	DWORD				VlastClk;
	DWORD				VnewClk;


	fadeout ();
	clearpoints ();
	nrockets1 = nrockets - 1;
	if (nrockets1 == 0)
		nrockets1 = 1;
	for (y = 0; y < size; y++)
		sizes[y] = (GAMEWIDTH-TextLen(text2[y])) / 2;

	VlastClk=timeGetTime();
	VnewClk=timeGetTime();
	Effect (S_START);
	for (i = -600; i < (size + 5) * TEXTW; i += 1)
    {
		VlastClk=timeGetTime();
		CopyVSToVS (starbackground, GetDDWin()->backsurf);
		SetScreen (GetDDWin()->backsurf);
		points ();
		for (y = 0; y < size; y++)
	    {
			if (y * TEXTW - i <600 && y * TEXTW - i > -16)
			{
				textcolor = (40 + (y * TEXTW - i)) * 32 / 650;
				if (textcolor <= 0)
				    continue;
				actu = y;
  				DrawText(sizes[y], y * TEXTW - i,text2[y],textcolor);
			}
	    }
		for (z = 0; z < nrockets; z++)
	    {
			if(!first) draw_player ((int)(MAPWIDTH / 2 - width / 2 + z * width / (nrockets1)), (int)(playy), (int)(playr),(int)( z), (int) er);
	    }
		first=0;
		CopyToScreen (GetDDWin()->backsurf);
		fadein1 ();
		points1 ();
		width = (200 * (nrockets - 1) * playy / MAPHEIGHT + 20 * (nrockets - 1)) / DIV;
		if (playy > MAPHEIGHT / 2 || actu > CONTLINE)
		{
			playy -= 0.6 / DIV;
			playr = RAD (180);
			for (z = 0; z < nrockets; z++)
			{
				staraccel ((MAPWIDTH / 2 - width / 2 + z * width / (nrockets1)) * DIV, (playy) * DIV, playr);
			}
			er = EYE_RADIUS1;
		}
		else
		{
			playr += playp;
			if (playr < RAD (-45))
				playp = 0.015, playr = RAD (-45);
			if (playr > RAD (45))
				playp = -0.03, playr = RAD (45);
			if (actu > UDIVLINE)
			{
				erp += (2 * EYE_RADIUS1 - er) / 10;
				erp *= 0.98;
				er += erp;
			}
		}
		VnewClk=timeGetTime();
		wait = (int)((def-VnewClk + VlastClk)/5)*5;
		if(wait>0)
			Sleep (wait);
		if (actu > 0)
		{
			UpdateInput ();
			if (Pressed ())
			{
			fadeout ();
			GetDDWin()->ClearSurface(GetDDWin()->primsurf,0,NULL);
			fadein();
			return;
			}
		}
    }
	fadeout ();
	GetDDWin()->ClearSurface(GetDDWin()->primsurf,0,NULL);
	fadein();
	return;
}


void outro1 ()
{
  outro (TEXTSIZE1, text1);
}

void intro_intro ()
{
  outro (INTROSIZE, introtext);
}

void hole_intro ()
{
  outro (HOLESIZE, holetext);
}

void inspector_intro ()
{
  outro (INSPECTORSIZE, inspectortext);
}

void bball_intro ()
{
  outro (BBALLSIZE, bballtext);
}

void bbball_intro ()
{
  outro (BBBALLSIZE, bbballtext);
}

void maghole_intro ()
{
  outro (MAGSIZE, magholetext);
}

void spring_intro ()
{
  outro (SPRINGTSIZE, springtext);
}

void thief_intro ()
{
  outro (THIEFSIZE, thieftext);
}

void ttool_intro ()
{
  outro (TTOOLSIZE, ttooltext);
}

void finder_intro ()
{
  outro (FINDERSIZE, findertext);
}

void lunatic_intro ()
{
  outro (LUNATICSIZE, lunatictext);
}

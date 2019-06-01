/***********************************************************
*                      K O U L E S                         *
*  koules.c main game routines                             *
 ***********************************************************/
#define VARIABLES_HERE
#include "koules.h"
#include "interface.h"
#include "framebuffer.h"
#include "input.h"
#include "sound.h"

int             nobjects = 8;
int             nrockets = 1;
int             drawpointer = 1;
int             difficulty = 2;
int             cit = 0;
Object          object[MAXOBJECT];
Point           point[MAXPOINT];
extern BOOL		show_playerdata=FALSE;
extern int		show_player=0;

void Restore()
{
	if(background->IsLost())
	{
		background->Restore();
		createbackground ();
	}
	if(starbackground->IsLost())
	{
		starbackground->Restore();
		drawstarbackground ();
	}
	surf_queue *p=surf_header.next;
	DDCOLORKEY ddc;
	ddc.dwColorSpaceLowValue=0;
	ddc.dwColorSpaceHighValue=0;
			
	while(p)
	{
		if(p->lpsurf->IsLost())
		{
			p->lpsurf->Restore();
			GetDDWin()->Copy_Bmp08_Surface08(p->lpsurf,
			(LPBYTE)p->bitmap,p->sx,p->sy);
			p->lpsurf->SetColorKey(DDCKEY_SRCBLT,&ddc);
		}
		p=p->next;
	}
}


unsigned char   rocketcolor[5] =
{96, 160, 64, 96, 128};

int             lastlevel = 0, maxlevel = 0;
char			control[MAXROCKETS];
struct			control  controls[MAXROCKETS];
int             dosprings = 0;
int             randsprings = 0;
int             textcolor;
int             tbreak;
int             gameplan = COOPERATIVE;
int             npoint = 0;
int             gamemode;
int             keys[5][4];
int             rotation[MAXROCKETS];
int             a_bballs, a_rockets, a_balls, a_holes, a_apples, a_inspectors,
                a_lunatics, a_eholes;
int             mouseplayer = -1;
double          ROCKET_SPEED = 1.2;
double          BALL_SPEED = 1.2;
double          BBALL_SPEED = 1.2;
double          SLOWDOWN = 0.8;
double          GUMM = 20;
double          BALLM = 10;
double          LBALLM = 3;
double          BBALLM = 8;
double          APPLEM = 34;
double          INSPECTORM = 2;
double          LUNATICM = 3.14;
double          ROCKETM = 4;

void addpoint (CONST int x, CONST int y, CONST int xp, CONST int yp, CONST int color, CONST int time)
{
	point[npoint].x = x / DIV;
	point[npoint].y = y / DIV;
	point[npoint].xp = xp / DIV;
	point[npoint].yp = yp / DIV;
	point[npoint].time = time;

	point[npoint].color = color;
	npoint++;
	if (npoint >= MAXPOINT)
		npoint = 0;
}

void points ()
{
	int x, y;
	Point          *p, *lp;
	lp = &point[MAXPOINT];
	DDSURFACEDESC desc;
	ZeroMemory( &desc, sizeof(desc) );
	desc.dwSize = sizeof(desc);
	HRESULT r=draw_surf->Lock( 0, &desc, DDLOCK_WAIT | DDLOCK_WRITEONLY, 0 );
	if (r!=DD_OK)
		return ;//can't lock so return 
	BYTE* surfbits = (BYTE*)desc.lpSurface;

	for (p = point; p < lp; p++)
	{
		if (p->time > 0)
		{
			p->time--;
			x = (p->x += p->xp) >> 8;
			y = (p->y += p->yp) >> 8;
			////////////////!!!!!!!!!!!!!!!!!!!!!!
			if (x > 0 && x < MAPWIDTH &&
				y > 0 && y < MAPHEIGHT)
				*(surfbits+y*desc.lPitch+x)=p->color;
			else
				p->time = 0;
		}
    } 
	
	draw_surf->Unlock( 0 );
}

void points1 ()
{
	Point          *p, *lp;
	lp = &point[MAXPOINT];
	for (p = point; p < lp; p++)
    {
		if (p->time > 0)
		{
			p->time--;
			p->x += p->xp;
			p->y += p->yp;
		}
    }
}

INLINE int radius (CONST int type)
{
	switch (type)
    {
	case EHOLE:
	case HOLE:
		return (HOLE_RADIUS);
    case ROCKET:
      return (ROCKET_RADIUS);
    case BALL:
    case LBALL:
      return (BALL_RADIUS);
    case BBALL:
      return (BBALL_RADIUS);
    case APPLE:
      return (APPLE_RADIUS);
    case INSPECTOR:
      return (INSPECTOR_RADIUS);
    case LUNATIC:
      return (LUNATIC_RADIUS);
    }
  return (0);
}

static INLINE int color (CONST int type, CONST int i, CONST int letter)
{
  switch (type)
    {
    case EHOLE:
      return (128);
    case HOLE:
      return (64);
    case ROCKET:
      return (rocketcolor[i]);
    case BALL:
      return (64);
    case LBALL:
      switch (letter)
	{
	case L_ACCEL:
	  return (128);
	case L_GUMM:
	  return (160);
	case L_THIEF:
	  return (192);
	case L_FINDER:
	  return (3 * 32);
	case L_TTOOL:
	  return (3 * 32);
	}

    case BBALL:
      return (128);
    case APPLE:
      return (64);
    case INSPECTOR:
      return (160);
    case LUNATIC:
      return (3 * 32);
    }
  return (0);
}

INLINE double M (CONST int type)
{
  switch (type)
    {
    case APPLE:
      return (APPLEM);
    case INSPECTOR:
      return (INSPECTORM);
    case LUNATIC:
      return (LUNATICM);
    case HOLE:
    case EHOLE:
      return (BBALLM);
    case ROCKET:
      return (ROCKETM);
    case BALL:
    case LBALL:
      return (BALLM);
    case BBALL:
      return (BBALLM);
    }
  return (0);
}

int find_possition (double *x, double *y, CONST double radius)
{
  int             x1, y1, i, y2 = 0;
  double           xp, yp;
rerand:;
  x1 = rand () % (GAMEWIDTH - 60) + 30;
  y1 = rand () % (GAMEHEIGHT - 60) + 30;
  for (i = 0; i < nobjects; i++)
    {
      xp = x1 - object[i].x;
      yp = y1 - object[i].y;
      if (xp * xp + yp * yp < (radius + object[i].radius) *
	  (radius + object[i].radius))
	{
	  y2++;
	  if (y2 > 10000)
	    return (0);
	  goto rerand;

	}
    }
  *x = (double) x1;
  *y = (double) y1;
  return (1);
}

INLINE void normalize (double *x, double *y, double size)
{
  double           length = sqrt ((*x) * (*x) + (*y) * (*y));
  if (length == 0)
    length = 1;
  *x *= size / length;
  *y *= size / length;
}


static void move_objects ()
{
	int             i;
	for (i = 0; i < nobjects; i++)
    if (object[i].type == CREATOR)
    {
		object[i].time--;
		if (object[i].time <= 0)
		{
	    Effect (S_CREATOR2);
			object[i].live = object[i].live1;
			object[i].type = object[i].ctype;
			if (object[i].type == ROCKET)
				object[i].time = 200;
			object[i].radius = radius (object[i].ctype);
			object[i].M = M (object[i].ctype);
		}
    }
	else if (object[i].live)
    {
		object[i].x += object[i].fx * (GAMEWIDTH / 640.0 + 1) / 2;
		object[i].y += object[i].fy * (GAMEWIDTH / 640.0 + 1) / 2;
    }
}

char            str[2]={0,0};
static void draw_objects (CONST int draw)
{
	char            s[80];
	int             i;
	if (draw)
    {
		CopyVSToVS (background,draw_surf);
      /* Now draw the objects in backscreen. */
		points ();
		for (i = 0; i < nobjects; i++)
		if (object[i].live && object[i].lineto != -1 && object[object[i].lineto].live)
			Line ((int)(object[i].x / DIV),
			(int)(object[i].y / DIV),
			(int)(object[object[i].lineto].x / DIV),
			(int)(object[object[i].lineto].y / DIV),
			255);
		for (i = 0; i < nobjects; i++)
			if (object[i].live)
			{
			    switch (object[i].type)
				{
				case BALL:
					PutBitmap ((int) (object[i].x - BALL_RADIUS) / DIV, (int) (object[i].y - BALL_RADIUS) / DIV,
					BALL_RADIUS * 2 / DIV, BALL_RADIUS * 2 / DIV, ball_bitmap);
				break;
				case LBALL:
					switch (object[i].letter)
					{
					case L_ACCEL:
						PutBitmap ((int) (object[i].x - BALL_RADIUS) / DIV, (int) (object[i].y - BALL_RADIUS) / DIV,
						BALL_RADIUS * 2 / DIV, BALL_RADIUS * 2 / DIV, lball_bitmap[0]);
					break;
					case L_GUMM:
						PutBitmap ((int) (object[i].x - BALL_RADIUS) / DIV, (int) (object[i].y - BALL_RADIUS) / DIV,
							BALL_RADIUS * 2 / DIV, BALL_RADIUS * 2 / DIV, lball_bitmap[1]);
					break;
					case L_THIEF:
						PutBitmap ((int) (object[i].x - BALL_RADIUS) / DIV, (int) (object[i].y - BALL_RADIUS) / DIV,
						BALL_RADIUS * 2 / DIV, BALL_RADIUS * 2 / DIV, lball_bitmap[2]);
					break;
					case L_FINDER:
						PutBitmap ((int) (object[i].x - BALL_RADIUS) / DIV, (int) (object[i].y - BALL_RADIUS) / DIV,
						BALL_RADIUS * 2 / DIV, BALL_RADIUS * 2 / DIV, lball_bitmap[3]);
					break;
					case L_TTOOL:
						PutBitmap ((int) (object[i].x - BALL_RADIUS) / DIV, (int) (object[i].y - BALL_RADIUS) / DIV,
						BALL_RADIUS * 2 / DIV, BALL_RADIUS * 2 / DIV, lball_bitmap[4]);
						if (DIV == 1)
						{
							str[0] = object[i].letter;
							DrawBlackMaskedText ((int) object[i].x / DIV - 4, (int) object[i].y / DIV - 6, str);
						}

					break;
					}
				break;
				case HOLE:
					PutBitmap ((int) (object[i].x - HOLE_RADIUS) / DIV, (int) (object[i].y - HOLE_RADIUS) / DIV,
					HOLE_RADIUS * 2, HOLE_RADIUS * 2, hole_bitmap);
				break;
				case EHOLE:
					PutBitmap ((int) (object[i].x - HOLE_RADIUS) / DIV, (int) (object[i].y - HOLE_RADIUS) / DIV,
					HOLE_RADIUS * 2, HOLE_RADIUS * 2, ehole_bitmap);
				break;
				case BBALL:
					PutBitmap ((int) (object[i].x - BBALL_RADIUS) / DIV, (int) (object[i].y - BBALL_RADIUS) / DIV,
					BBALL_RADIUS * 2 / DIV, BBALL_RADIUS * 2 / DIV, bball_bitmap);
				break;
				case INSPECTOR:
					PutBitmap ((int) (object[i].x - INSPECTOR_RADIUS) / DIV, (int) (object[i].y - INSPECTOR_RADIUS) / DIV,
					INSPECTOR_RADIUS * 2 / DIV, INSPECTOR_RADIUS * 2 / DIV, inspector_bitmap);
				break;
				case LUNATIC:
					PutBitmap ((int) (object[i].x - LUNATIC_RADIUS) / DIV, (int) (object[i].y - LUNATIC_RADIUS) / DIV,
					LUNATIC_RADIUS * 2 / DIV, LUNATIC_RADIUS * 2 / DIV, lunatic_bitmap);
				break;
				case APPLE:
					PutBitmap ((int) (object[i].x - APPLE_RADIUS) / DIV, (int) (object[i].y - APPLE_RADIUS) / DIV,
					APPLE_RADIUS * 2 / DIV, APPLE_RADIUS * 2 / DIV, apple_bitmap);
					Line ((int) (object[i].x + 10) / DIV, (int) (object[i].y - APPLE_RADIUS - 10) / DIV,
					(int) (object[i].x) / DIV, (int) (object[i].y - APPLE_RADIUS + 10) / DIV, 150);
					Line ((int) (object[i].x + 10) / DIV + 1, (int) (object[i].y - APPLE_RADIUS - 10) / DIV,
					(int) (object[i].x) / DIV + 1, (int) (object[i].y - APPLE_RADIUS + 10) / DIV, 150);
					if (DIV == 1)
						Line ((int) (object[i].x + 10) / DIV + 2, (int) (object[i].y - APPLE_RADIUS - 10) / DIV,
						(int) (object[i].x) / DIV + 2, (int) (object[i].y - APPLE_RADIUS + 10) / DIV, 150);
					PutBitmap ((int) (object[i].x - EYE_RADIUS) / DIV,
					(int) (object[i].y + APPLE_RADIUS - 15) / DIV,
					EYE_RADIUS * 2 / DIV, EYE_RADIUS * 2 / DIV, eye_bitmap[0]);
				break;
				case ROCKET:
				{
					int             x1, y1;
					PutBitmap ((int) (object[i].x - ROCKET_RADIUS) / DIV, (int) (object[i].y - ROCKET_RADIUS) / DIV,
						ROCKET_RADIUS * 2 / DIV, ROCKET_RADIUS * 2 / DIV, rocket_bitmap[i]);
					if (!object[i].thief)
					{
						x1 =(int)( object[i].x + sin (object[i].rotation - RAD (30)) * EYE_RADIUS1 - EYE_RADIUS);
						y1 =(int)( object[i].y + cos (object[i].rotation - RAD (30)) * EYE_RADIUS1 - EYE_RADIUS);
						PutBitmap ((int) (x1 / DIV), (int) (y1 / DIV),
						(int) (EYE_RADIUS * 2 / DIV), (EYE_RADIUS * 2 / DIV), eye_bitmap[i]);
						x1 =(int)( object[i].x + sin (object[i].rotation + RAD (30)) * EYE_RADIUS1 - EYE_RADIUS);
						y1 =(int)( object[i].y + cos (object[i].rotation + RAD (30)) * EYE_RADIUS1 - EYE_RADIUS);
						PutBitmap ((int) (x1 / DIV), (int) (y1 / DIV),
						(int) (EYE_RADIUS * 2 / DIV), (EYE_RADIUS * 2 / DIV), eye_bitmap[i]);
					}
					else
					{
						x1 =(int)( object[i].x + sin (object[i].rotation - RAD (30)) * EYE_RADIUS1 - BALL_RADIUS);
						y1 =(int)( object[i].y + cos (object[i].rotation - RAD (30)) * EYE_RADIUS1 - BALL_RADIUS);
	
					    PutBitmap ((int) (x1 / DIV), (int) (y1 / DIV),
							(int) (BALL_RADIUS * 2 / DIV), (BALL_RADIUS * 2 / DIV), lball_bitmap[2]);
						x1 =(int)( object[i].x + sin (object[i].rotation + RAD (30)) * EYE_RADIUS1 - BALL_RADIUS);
						y1 =(int)( object[i].y + cos (object[i].rotation + RAD (30)) * EYE_RADIUS1 - BALL_RADIUS);
						PutBitmap ((int) (x1 / DIV), (int) (y1 / DIV),
						(int) (BALL_RADIUS * 2 / DIV), (BALL_RADIUS * 2 / DIV), lball_bitmap[2]);
					}
				}
				break;
			}
		}
    }
  /*if draw */
	else
	points1 ();
	switch (gamemode)
    {
    case MENU:
		draw_menu (draw);
		break;
    case KEYS:
		draw_keys (draw);
		break;
	default:
		break;
    }
	if (draw && (gamemode == MENU || (gamemode == GAME && mouseplayer != -1)) &&
      MouseX () >= 0 && MouseY () >= 0 && MouseX () < MAPWIDTH &&
      MouseY () < MAPHEIGHT && drawpointer)
    {
		PutBitmap (MouseX () - MOUSE_RADIUS, MouseY () - MOUSE_RADIUS,
		     MOUSE_RADIUS * 2, MOUSE_RADIUS * 2, mouse_bitmap);
    }

	if (draw)
    {
		if (gameplan == COOPERATIVE && gamemode == GAME && DIV == 1)
		{
			sprintf (s, "level: %3i", lastlevel + 1);
			DrawWhiteMaskedText ((MAPWIDTH / 3 - 38 * 4) / 2 - TextLen(s) /2, MAPHEIGHT + 1, s);
		}
		sprintf (s, " lives: %6i%6i%6i%6i%6i",
	       nrockets >= 1 ? object[0].live1 : 0,
	       nrockets >= 2 ? object[1].live1 : 0,
	       nrockets >= 3 ? object[2].live1 : 0,
	       nrockets >= 4 ? object[3].live1 : 0,
	       nrockets >= 5 ? object[4].live1 : 0);
		DrawWhiteMaskedText (MAPWIDTH / 2 - TextLen(s) /2, MAPHEIGHT + 1, s);
		sprintf (s, "scores: %6i%6i%6i%6i%6i",
	       object[0].score,
	       object[1].score,
	       object[2].score,
	       object[3].score,
	       object[4].score);
		DrawWhiteMaskedText (MAPWIDTH / 2 - TextLen(s) /2, MAPHEIGHT + 12, s);
		if(show_playerdata)
		{
			sprintf (s, "Weight: %5.2f", object[0].M);
			int l=MAPWIDTH - TextLen(s);
			DrawWhiteMaskedText (l, MAPHEIGHT , s);
			sprintf (s, " Accel: %5.2f", object[0].accel);
			DrawWhiteMaskedText (MAPWIDTH - TextLen(s), MAPHEIGHT + 13, s);
			sprintf (s, "Player %1i:", show_player);
			DrawWhiteMaskedText (l - TextLen(s) - 10, MAPHEIGHT , s);
		}
	}
}

void explosion (CONST int x, CONST int y, CONST int type, CONST int letter, CONST int n)
{
  double           i;
  int             speed;
  int             color1;
  int             radius1 = radius (type);
  for (i = 0; i < RAD (360); i += RAD (360.0) * DIV * DIV / radius1 / radius1 / M_PI)
    {
      speed = rand () % 3096 + 10;
      if (DIV == 1)
	color1 = color (type, n, letter) + (rand () % 16);
      else
	color1 = color (type, n, letter) + (rand () % 32);
      addpoint (x * 256, y * 256,
		(int)(sin (i) * (speed)),
		(int)(cos (i) * (speed)),
		color1,
		rand () % 100 + 10);
    }
}

static void rocket_destroyed (CONST int player)
{
  int             i, nalive = 0, igagnant = 0;
  if (gamemode == GAME)
    switch (gameplan)
      {
      case DEATHMATCH:
	if (nrockets == 1)
	  return;
	for (i = 0; i < nrockets; i++)
	  if (object[i].type == ROCKET && object[i].live && i != player)
	    {
	      object[i].score += 100;
	      nalive++;
	      igagnant = i;
	    }
	if (nalive == 1)	/* winner bonus */
	  object[igagnant].score += 50;
      }
}

void destroy (CONST int i)
{
	int             y;
	if (object[i].x - object[i].radius < 0)
		object[i].x = object[i].radius + 1, object[i].fx *= -1;
	if (object[i].y - object[i].radius < 0)
		object[i].y = object[i].radius + 1, object[i].fy *= -1;
	if (object[i].x + object[i].radius > GAMEWIDTH)
		object[i].x = GAMEWIDTH - object[i].radius - 1, object[i].fx *= -1;
	if (object[i].y + object[i].radius > GAMEHEIGHT)
		object[i].y = GAMEHEIGHT - object[i].radius - 1, object[i].fy *= -1;
	switch (object[i].type)
    {
	case LBALL:
	    Effect (S_DESTROY_BALL);
		object[i].live = 0, explosion ((int)(object[i].x), (int)(object[i].y), object[i].type, object[i].letter, i);
		if (object[i].letter == L_THIEF && allow_finder ())
		{
			object[i].live = 1;
			object[i].letter = L_FINDER;
		}
      break;
    case APPLE:
        Effect (S_DESTROY_ROCKET);
		object[i].live = 0, explosion ((int)(object[i].x), (int)(object[i].y), object[i].type, object[i].letter, i);
	break;
    case BALL:
    case EHOLE:
    case BBALL:
    case INSPECTOR:
    case LUNATIC:
	      Effect (S_DESTROY_BALL);
		if ((y = create_letter ()) != 0)
		{
			object[i].type = LBALL;
			object[i].M = LBALLM;
			switch (y)
			{
			case 1:
				object[i].letter = L_ACCEL;
				break;
			case 2:
				object[i].letter = L_GUMM;
				break;
			case 3:
				object[i].letter = L_THIEF;
				break;
			case 4:
				object[i].letter = L_FINDER;
				break;
			case 5:
				object[i].letter = L_TTOOL;
				break;
			}
		}
		else
			object[i].live = 0, explosion ((int)(object[i].x),(int)( object[i].y), object[i].type, object[i].letter, i);
		break;
    case ROCKET:
      Effect (S_DESTROY_ROCKET);
		object[i].live1--, object[i].live--, explosion ((int)(object[i].x),(int)( object[i].y), object[i].type, object[i].letter, i);
		rocket_destroyed (i);
		if (object[i].live)
		{
			object[i].fx = 0;
			object[i].fy = 0;
			object[i].rotation = 0;
			object[i].type = ROCKET;
			object[i].accel = ROCKET_SPEED;
			creator_rocket (i);
		}
		break;
	}
}

static void check_limit ()
{
	int             i;
	for (i = 0; i < nobjects; i++)
		if (object[i].live)
		{
			if (object[i].x - object[i].radius < 0 || object[i].x + object[i].radius >= GAMEWIDTH ||
				object[i].y - object[i].radius <= 0 || object[i].y + object[i].radius >= GAMEHEIGHT)
			{
				destroy (i);
			}
		}
}

/*
 * count number of creatures
 */
static void update_values ()
{
  int             i;
  a_holes = 0;
  a_rockets = 0;
  a_balls = 0;
  a_bballs = 0;
  a_apples = 0;
  a_eholes = 0;
  a_inspectors = 0;
  a_lunatics = 0;
  for (i = 0; i < nobjects; i++)
    {
      if (object[i].live)
	{
	  switch (object[i].type)
	    {
	    case HOLE:
	      a_holes++;
	      break;
	    case EHOLE:
	      a_eholes++;
	      break;
	    case ROCKET:
	      a_rockets++;
	      break;
	    case LBALL:
	    case BALL:
	      a_balls++;
	      break;
	    case BBALL:
	      a_bballs++;
	      break;
	    case APPLE:
	      a_apples++;
	      break;
	    case INSPECTOR:
	      a_inspectors++;
	      break;
	    case LUNATIC:
	      a_lunatics++;
	      break;
	    }
	}
      if (object[i].type == CREATOR)
	{
	  switch (object[i].ctype)
	    {
	    case BBALL:
	      a_bballs++;
	      break;
	    case HOLE:
	      a_holes++;
	      break;
	    case EHOLE:
	      a_eholes++;
	      break;
	    case ROCKET:
	      a_rockets++;
	      break;
	    case LBALL:
	    case BALL:
	      a_balls++;
	      break;
	    case APPLE:
	      a_apples++;
	      break;
	    case INSPECTOR:
	      a_inspectors++;
	      break;
	    case LUNATIC:
	      a_lunatics++;
	      break;
	    }
	}
    }

}

/*
 * accelerate rocket
 */
void accel (CONST int i)
{
  int             y;
    {
      object[i].time = 0;
      object[i].fx += sin (object[i].rotation) * object[i].accel,
	object[i].fy += cos (object[i].rotation) * object[i].accel;
	for (y = 0; y < 5 / DIV / DIV; y++)
	  {
	    double           p;
	    p = RAD (rand () % 45 - 22);
	    addpoint ((int)(object[i].x * 256),
		      (int)(object[i].y * 256),
		      (int)((object[i].fx - sin (object[i].rotation + p) * object[i].accel * 10) * (rand () % 512)),
		      (int)((object[i].fy - cos (object[i].rotation + p) * object[i].accel * 10) * (rand () % 512)),
		      rocket (rand () % 16), 10);
	  }
    }
}


static void sprocess_keys ()
{
  int             i;
  if (gamemode != GAME)
    return;
  for (i = 0; i < MAXROCKETS; i++)
    {
      if (object[i].live && object[i].type == ROCKET)
	{
	  switch (controls[i].type)
	    {
	    case C_JOYSTICK1:
	      {
		double          a, x = controls[i].jx, y = controls[i].jy;
		a = atan (fabs (y) / fabs (x));
		if (x < 0 && y >= 0)
		  object[i].rotation = a + RAD (90);
		else if (x < 0 && y < 0)
		  object[i].rotation = RAD (90) - a;
		else if (x >= 0 && y < 0)
		  object[i].rotation = a + RAD (270);
		else if (x >= 0 && y >= 0)
		  object[i].rotation = RAD (270) - a;
		if (controls[i].mask)
		  accel (i);
	      }
	      break;
	    case C_MOUSE:
	      {
		double          dx, dy, a;
		dx = object[i].x - controls[i].mx;
		dy = object[i].y - controls[i].my;
		if (dx == 0)
		  dx = 0.001;
		a = atan (fabs (dy) / fabs (dx));
		if (dx < 0 && dy >= 0)
		  object[i].rotation = a + RAD (90);
		else if (dx < 0 && dy < 0)
		  object[i].rotation = RAD (90) - a;
		else if (dx >= 0 && dy < 0)
		  object[i].rotation = a + RAD (270);
		else if (dx >= 0 && dy >= 0)
		  object[i].rotation = RAD (270) - a;
		if (controls[i].mask)
		  accel (i);
	      }
	      break;
	    case C_RKEYBOARD:
	      if (controls[i].mask & 1)
		object[i].rotation += ROTSTEP;
	      if (controls[i].mask & 2)
		object[i].rotation -= ROTSTEP;
	      if (controls[i].mask & 4)
		accel (i);
	      break;
	    case C_KEYBOARD:
	      switch (controls[i].mask)
		{
		case 1:
		  object[i].rotation = RAD (-135), accel (i);
		  break;
		case 2:
		  object[i].rotation = RAD (135), accel (i);
		  break;
		case 3:
		  object[i].rotation = RAD (45), accel (i);
		  break;
		case 4:
		  object[i].rotation = RAD (-45), accel (i);
		  break;
		case 5:
		  object[i].rotation = RAD (-90), accel (i);
		  break;
		case 6:
		  object[i].rotation = RAD (90), accel (i);
		  break;
		case 7:
		  object[i].rotation = RAD (180), accel (i);
		  break;
		case 8:
		  object[i].rotation = RAD (0), accel (i);
		  break;
		}

	    }
	}
    }
}

void process_keys ()
{
	int             i;

	if (IsPressedP () && gamemode!=MENU)
    {
		SetScreen (GetDDWin()->backsurf);
		DrawWhiteMaskedText (MAPWIDTH / 2 - 20, MAPHEIGHT / 2 - 4, "PAUSE");
		CopyToScreen(GetDDWin()->backsurf);
		tbreak = 1;
		while(IsPressedP())
			UpdateInput();
		while(!IsPressedP())
			UpdateInput();
		while(IsPressedP())
			UpdateInput();

	}
	switch (gamemode)
	{
	case MENU:
		menu_keys ();
		break;
	case KEYS:
		keys_keys ();
		break;
	case GAME:
		/* Move. */
		if (mouseplayer != -1 && object[mouseplayer].type == ROCKET)
		{
			controls[mouseplayer].mx = MouseX () * DIV;
			controls[mouseplayer].my = MouseY () * DIV;
			controls[mouseplayer].mask = MouseButtons () != 0;
			controls[mouseplayer].type = C_MOUSE;
		}
		if (IsPressedEsc ())
		{
			gamemode = MENU;
			while(IsPressedEsc())
				UpdateInput();
		}
		if (IsPressed (SCANCODE_TAB))
		{
			show_player++;
			if(show_player>nrockets)
			{
				show_player=0;
				show_playerdata=FALSE;
			}
			else
				show_playerdata=TRUE;
			while(IsPressed (SCANCODE_TAB))
				UpdateInput();
		}
		for (i = 0; i < nrockets; i++)
		{
			if (i == mouseplayer)
				continue;
			if (object[i].type != ROCKET)
				continue;
			if (rotation[i])
			{
				char            s = 0;
				if (IsPressing (keys[i][1]))
					s = 1;
				if (IsPressing (keys[i][2]))
					s |= 2;
				if (IsPressing (keys[i][0]))
					s |= 4;
				controls[i].type = C_RKEYBOARD;
				controls[i].mask = s;
			}
			else
			{
				int             s = 0;
				if (IsPressing(keys[i][2]) && IsPressing(keys[i][0]))
					s = 1;
				else if (IsPressing(keys[i][3]) && IsPressing(keys[i][0]))
					s = 2;
				else if (IsPressing(keys[i][1]) && IsPressing(keys[i][3]))
					s = 3;
				else if (IsPressing(keys[i][1]) && IsPressing(keys[i][2]))
					s = 4;
				else if (IsPressing(keys[i][2]))
					s = 5;
				else if (IsPressing(keys[i][3]))
					s = 6;
				else if (IsPressing(keys[i][0]))
					s = 7;
				else if (IsPressing(keys[i][1]))
					s = 8;
				controls[i].type = C_KEYBOARD;
				controls[i].mask = s;
			}
		}
		break;
	}
}

#define MIN(a,b) ((a)>(b)?(b):(a))
/*
 * Make creations happen as coalescing circular cloud.  Do this by
 * creating random points within circle defined from center of screen, and
 * giving them velocity towards desired final point.
 */

void creators_points (int radius, int x1, int y1, int color1)
{
    int             z, x, y, x2, y2;
    double r;
    int             time = 50;
    int             midX, midY, r2,r1;

    midX = GAMEWIDTH / 2;
    midY = GAMEHEIGHT / 2;
    r2 = r1 = MIN(midX, midY);
    r2 *= r2;

    z =(int)( radius * radius * M_PI / DIV / DIV);
    while (z--) {
	do {
	    x = rand() % GAMEWIDTH;
	    y = rand() % GAMEHEIGHT;
	} while (((x-midX)*(x-midX) + (y-midY)*(y-midY)) > r2);
	r=sqrt((double)((x-midX)*(x-midX) + (y-midY)*(y-midY)));
	r=(r*radius/r1)/r*0.9;
	x2=x1+(int)((x-midX)*r);
	y2=y1+(int)((y-midY)*r);

	addpoint(x * 256, y * 256,
		    (x2 - x) * 256 / (time),
		    (y2 - y) * 256 / (time),
		    color1 + (rand() % (DIV == 1 ? 16 : 32)),
		    time);
    }
}

void creator (CONST int type)
{
  int             i;
  int             color1 = color (type, 0, 0);
  for (i = nrockets; i < nobjects && (object[i].live ||
				      object[i].type == CREATOR);
       i++);
  if (i >= MAXOBJECT)
    return;
  if (!find_possition (&object[i].x, &object[i].y, radius (type)))
    return;
  if (i >= nobjects)
    nobjects = i + 1;
  object[i].live = 0;
  object[i].live1 = 1;
  object[i].lineto = -1;
  object[i].ctype = type;
  object[i].fx = 0.0;
  object[i].fy = 0.0;
  object[i].time = 50;
  object[i].rotation = 0;
  object[i].type = CREATOR;
  object[i].M = M (type);
  object[i].radius = radius (type);
  object[i].accel = ROCKET_SPEED;
  object[i].letter = ' ';
    creators_points ((int)(object[i].radius),(int)( object[i].x),(int)( object[i].y), color1);
  Effect (S_CREATOR1);
}


void creator_rocket (CONST int i)
{
  int             type = ROCKET;
  int             color1 = color (ROCKET, i, 0);
  if (!find_possition (&object[i].x, &object[i].y, radius (type)))
    return;
  if (sound)
    object[i].live1 = object[i].live;
  object[i].live = 0;
  object[i].thief = 0;
  object[i].ctype = type;
  object[i].lineto = -1;
  object[i].fx = 0.0;
  object[i].fy = 0.0;
  object[i].time = 50;
  object[i].rotation = 0;
  object[i].type = CREATOR;
  object[i].M = ROCKETM;
  object[i].radius = ROCKET_RADIUS;
  object[i].accel = ROCKET_SPEED;
  object[i].letter = ' ';
    creators_points (ROCKET_RADIUS, (int)(object[i].x), (int)(object[i].y), color1);
}

static void update_forces ()
{
  int             i;
  int             r;
  double           d;
  double           xp, yp;
  int             frocket = 0;
  for (i = 0; i < nobjects; i++)
    {
      if (object[i].live)
	{
	  if (object[i].lineto != -1)
	    {
	      if (!object[object[i].lineto].live)
		object[i].lineto = -1;
	      else if (object[i].lineto == i)
		object[i].lineto = -1;
	      else
		{
		  int             force;
		  xp = object[i].x - object[object[i].lineto].x;
		  yp = object[i].y - object[object[i].lineto].y;
		  force =(int)( sqrt (xp * xp + yp * yp));
		  if (force >= 2 * SPRINGSIZE || gameplan == COOPERATIVE)
		    {
		      force = force - SPRINGSIZE;
		      if (force < 0)
			force *= 3;
		      force = force / SPRINGSTRENGTH;
		      normalize (&xp, &yp, force * BALL_SPEED / object[i].M);
		      object[i].fx -= xp;
		      object[i].fy -= yp;
		      normalize (&xp, &yp, force * BALL_SPEED / object[object[i].lineto].M);
		      object[object[i].lineto].fx += xp;
		      object[object[i].lineto].fy += yp;
		    }
		}
	    }
	  if (object[i].type == ROCKET && object[i].time)
	    object[i].time--;
	  if (object[i].type == ROCKET && !object[i].time)
	    {
	      d = 640 * 640;
	      frocket = -1;
	      for (r = 0; r < nobjects; r++)
		{
		  if (object[r].live && !object[r].time && object[r].type == EHOLE)
		    {
		      int             distance;
		      double           gravity;
		      xp = object[r].x - object[i].x;
		      yp = object[r].y - object[i].y;
		      distance =(int)( sqrt (xp * xp + yp * yp));
		      gravity = BALL_SPEED * (gameplan == COOPERATIVE ? 200 : 50) / distance;
		      if (gravity > BALL_SPEED * 4 / 5)
			gravity = BALL_SPEED * 4 / 5;
		      normalize (&xp, &yp, gravity);
		      object[i].fx += xp;
		      object[i].fy += yp;
		    }
		}

	    }
	  if (object[i].type == BALL || object[i].type == LBALL || object[i].type == BBALL || object[i].type == LUNATIC)
	    {
	      frocket = -1;
	      d = 640 * 640;
	      for (r = 0; r < nrockets; r++)
		{
		  if (object[r].live && !object[r].time)
		    {
		      xp = object[r].x - object[i].x;
		      yp = object[r].y - object[i].y;
		      if (xp * xp + yp * yp < d)
			d = xp * xp + yp * yp, frocket = r;
		    }
		}
	      if (frocket != -1)
		xp = object[frocket].x - object[i].x,
		  yp = object[frocket].y - object[i].y;
	      else
		xp = GAMEWIDTH / 2 - object[i].x,
		  yp = GAMEHEIGHT / 2 - object[i].y;
	      if (object[i].type == LUNATIC && !(rand () % 4))
		{
		  xp = rand ();
		  yp = rand () + 1;
		}
	      switch (object[i].type)
		{
		case BBALL:
		  normalize (&xp, &yp, BBALL_SPEED);
		  break;
		case BALL:
		case LUNATIC:
		case LBALL:
		  normalize (&xp, &yp, BALL_SPEED);
		  break;
		}
	      object[i].fx += xp;
	      object[i].fy += yp;
	    }
	  object[i].fx *= SLOWDOWN,
	    object[i].fy *= SLOWDOWN;
	}
    }
}

static void colisions ()
{
  int             i, y;
  int             colize = 0;
  static int      ctime = 0;
  double           xp, yp, gummfactor;
  for (i = 0; i < nobjects; i++)
    if (object[i].live)
      for (y = i + 1; y < nobjects; y++)
	if (object[y].live)
	  {
	    xp = object[y].x - object[i].x;
	    yp = object[y].y - object[i].y;
	    if (xp * xp + yp * yp < (object[y].radius + object[i].radius) *
		(object[y].radius + object[i].radius))
	      {
		colize = 1;
		if (object[i].type == HOLE || object[i].type == EHOLE)
		  {
		    if (object[y].type != APPLE)
		      destroy (y);
		    if (object[i].type == EHOLE)
		      destroy (i);
		    continue;
		  }
		if (object[y].type == HOLE || object[y].type == EHOLE)
		  {
		    if (object[i].type != APPLE)
		      destroy (i);
		    if (object[y].type == EHOLE)
		      destroy (y);
		    continue;
		  }
		if (object[i].type == ROCKET)
		  {
		    if (object[y].thief == 1 && object[i].thief == 1)
		      {
			double           tmp;
			tmp = object[i].M;
			object[i].M = object[y].M;
			object[y].M = tmp;
			object[i].thief = 0;
			object[y].thief = 0;
		      }
		    if (object[y].type == BBALL && object[i].thief == 1)
		      {
			object[i].M += object[y].M - M (BALL);
			object[i].thief = 0;
			object[y].M = M (BALL);
		      }
		    else if (object[y].type == ROCKET && object[i].thief == 1)
		      {
			object[i].M += object[y].M - M (ROCKET);
			object[i].accel += object[y].accel - ROCKET_SPEED;
			object[i].thief = 0;
			object[y].M = M (object[i].type);
			object[y].accel = ROCKET_SPEED - A_ADD;
		      }
		    if (object[i].type == ROCKET && object[y].thief == 1)
		      {
			object[y].M += object[i].M - M (ROCKET);
			object[y].accel += object[i].accel - ROCKET_SPEED;
			object[y].thief = 0;
			object[i].M = M (object[y].type);
			object[i].accel = ROCKET_SPEED - A_ADD;
		      }
		    if (gameplan == COOPERATIVE)
		      object[i].score++;
		    if (object[y].letter == L_ACCEL)
		      object[i].accel += A_ADD,
			object[i].score += 10;
		    if (object[y].letter == L_GUMM)
		      object[i].M += M_ADD,
			object[i].score += 10;
		    if (object[y].letter == L_THIEF)
		      object[i].M = M (object[i].type),
			object[i].accel = ROCKET_SPEED - A_ADD,
			object[i].score -= 30;
		    if (object[y].letter == L_FINDER)
		      {
			object[i].accel += A_ADD * (rand () % 5);
			object[i].M += M_ADD * (rand () % 10);
			object[i].score += 30;
		      }
		    if (object[y].letter == L_TTOOL)
		      {
			object[i].thief = 1;
			object[i].score += 30;
		      }

		    object[y].letter = ' ';
		    if (object[y].type == LBALL)
		      object[y].type = BALL;
		    if (object[y].type == BALL && dosprings && !(rand () % randsprings))
		      object[y].lineto = i;

		    if (gameplan == DEATHMATCH && object[y].type == ROCKET && dosprings && !(rand () % (2 * randsprings)))
		      object[y].lineto = i;
		  }
		if (object[y].type == LUNATIC)
		  {
		    gummfactor = -ROCKETM / LUNATICM;
		  }
		else if (object[i].type == LUNATIC)
		  {
		    gummfactor = -LUNATICM / ROCKETM;
		  }
		else
		  gummfactor = object[i].M / object[y].M;
		normalize (&xp, &yp, gummfactor * GUMM);
		object[y].fx += xp;
		object[y].fy += yp;
		normalize (&xp, &yp, 1 / gummfactor * GUMM);
		object[i].fx -= xp;
		object[i].fy -= yp;
		if (object[i].type == ROCKET && object[i].time)
		  object[i].fx = 0,
		    object[i].fy = 0;
		if (object[y].type == ROCKET && object[y].time)
		  object[y].fx = 0,
		    object[y].fy = 0;
		if (object[y].type == INSPECTOR && object[i].type == ROCKET)
		  {
		    object[y].fx = 0,
		      object[y].fy = 0;
		    object[i].fx *= -2,
		      object[i].fy *= -2;
		  }
	      }
	  }
  if (colize && !ctime)
    {
	  Effect (S_COLIZE);
      ctime = 4;
    }
  if (ctime)
    ctime--;
}

void gameloop(void)
{
	UpdateInput();
	process_keys ();
    sprocess_keys ();
    update_values ();
    update_game ();
    update_forces ();
    colisions ();
    move_objects ();
    check_limit ();
	draw_objects (1);
}

void		USleep(DWORD millsec)
{
	DWORD t,t1;
	t1=t=timeGetTime();
	while((t1-t)<millsec)
	{	
		t1=timeGetTime();
		UpdateInput();
		if(Pressed())
			break;
	}
}
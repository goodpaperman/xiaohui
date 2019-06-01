/***********************************************************
*                      K O U L E S                         *
*  koules.h                                                *
***********************************************************/
#ifndef __KOULE_INCLUDED___
#define __KOULE_INCLUDED___

#include "..\headers.h"

//defines
#define M_PI 3.14

#define CONST const
#define INLINE __inline
#define DUMMY do { } while (0)

#define MENUTIME 5

#define back(x) (32 + x)
#define ball(x) (64 + x)
#define rocket(x) (96 + x)

#define PLAY_X1 0
#define PLAY_Y1 0

#define RAD(n)  ((double)(n)/180.0*M_PI)
#define ROTSTEP RAD(10)

#define BALL_RADIUS 8
#define BBALL_RADIUS 16
#define APPLE_RADIUS 32
#define INSPECTOR_RADIUS 14
#define LUNATIC_RADIUS EYE_RADIUS
#define HOLE_RADIUS 12
#define ROCKET_RADIUS 14
#define EYE_RADIUS1 10
#define SPRINGSIZE (4*BBALL_RADIUS)
#define SPRINGSTRENGTH (BBALL_RADIUS/2)

#define NTRACKS 4
#define NTRACKS 4
#define ROCKET 1
#define BALL 2

#define LBALL 3
#define CREATOR 4
#define HOLE 5
#define BBALL 6
#define APPLE 7
#define INSPECTOR 8
#define EHOLE 9
#define LUNATIC 10

#define MAXOBJECT 255
#define MAXPOINT (4000)
#define MAXROCKETS 5

#define L_ACCEL 'A'
#define L_GUMM 'M'
#define L_THIEF 'T'
#define L_FINDER 'G'
#define L_TTOOL 'S'
#define A_ADD 0.13
#define M_ADD 0.8
#define NLETTERS 5

#define LETTER 1024

#define S_START 0
#define S_END 1
#define S_COLIZE 2
#define S_DESTROY_BALL 3
#define S_DESTROY_ROCKET 4
#define S_CREATOR1 5
#define S_CREATOR2 6

#define C_REMOTE 0
#define C_KEYBOARD 1
#define C_RKEYBOARD 2
#define C_JOYSTICK1 3
#define C_JOYSTICK2 4
#define C_MOUSE 5

#define DEATHMATCH 0
#define COOPERATIVE 1

#define NSAMPLES 7

#define MENU 1
#define KEYS 2
#define GAME 3
#define JOY 4
#define WAIT 5
#define PREGAME 6


typedef struct
{
	int             type;
    int             thief;
    int             ctype;
    int             live;
    int             time;
    int             score;
    int             lineto;
    double           x;
    double           y;
    double           fx;		/*forces */
    double           fy;
    double           rotation;	/*for rockets */
    int             live1;	/*backup for rockets */
    double           M;
    int             radius;
    double           accel;
    char            letter;
  }
Object;
typedef struct
  {
    int             x, y, xp, yp, time, color;
  }
Point;

struct control
  {
    int             type;
    double          jx, jy;
    int             mx, my;
    int             mask;
  };

extern double    ROCKET_SPEED;
extern double    BALL_SPEED;
extern double    BBALL_SPEED;
extern double    SLOWDOWN;
extern double    GUMM;

extern double    BALLM;
extern double    LBALLM;
extern double    BBALLM;
extern double    APPLEM;
extern double    INSPECTORM;
extern double    LUNATICM;
extern double    ROCKETM;

extern int		onmenu;
extern int      dosprings;
extern int      difficulty;
extern int      randsprings;
extern int      nobjects;
extern int      drawpointer;
extern int      textcolor;
extern int      nrockets;
extern Object   object[MAXOBJECT];
extern Point    point[MAXPOINT];
extern int      gameplan;
extern int      rotation[MAXROCKETS];
extern char     control[MAXROCKETS];
extern struct control controls[5];
extern int      lastlevel, maxlevel;

extern int      mouseplayer;
extern int      gamemode;
extern int      tbreak;

extern int      a_bballs, a_rockets, a_balls, a_holes, a_apples, a_inspectors,
                a_lunatics, a_eholes;

extern int      keys[5][4];

extern unsigned char     rocketcolor[5];
extern void     normalize (double *, double *, CONST double);
extern void     addpoint (CONST int, CONST int, CONST int, CONST int, CONST int, CONST int);
extern void     destroy (CONST int);
extern void     creator (CONST int);
extern void     creator_rocket (CONST int);
extern void     uninitialize ();
extern void     draw_menu (CONST int);
extern void     draw_joy (CONST int);
extern void     init_menu ();
extern void     menu_keys ();

extern void     draw_keys (int);
extern void     keys_keys ();
extern void     joy_keys ();
extern void     gameplan_init ();

extern void     update_game ();
extern void     init_objects ();
extern void     outro1 ();
extern void     outro2 ();
extern void     clearpoints ();
extern void     intro_intro ();
extern void     lunatic_intro ();
extern void     spring_intro ();
extern void     thief_intro ();
extern void     finder_intro ();
extern void     ttool_intro ();
extern void     hole_intro ();
extern void     inspector_intro ();
extern void     bball_intro ();
extern void     bbball_intro ();
extern void     maghole_intro ();
extern void     load_rc ();
extern void     save_rc ();
extern int      allow_finder ();
extern void gameloop(void);
extern void gameinit(void);
extern void		USleep(DWORD millsec);
extern void Restore();

extern int      find_possition (double *, double *, CONST double);
extern int      radius (CONST int);
extern double    M (CONST int);
extern int      create_letter ();
extern BOOL		show_playerdata;
extern int		show_player;
#endif

extern	int sound;
extern  int sndinit;

#define S_START 0
#define S_END 1
#define S_COLIZE 2
#define S_DESTROY_BALL 3
#define S_DESTROY_ROCKET 4
#define S_CREATOR1 5
#define S_CREATOR2 6

#define Effect(p)	(sound ? play_sound(p):0)

extern  void	play_sound(int n);
extern	BOOL	InitDirectSound();
extern	BOOL	ReleaseDirectSound();

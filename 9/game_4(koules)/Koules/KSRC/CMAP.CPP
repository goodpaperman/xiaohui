/***********************************************************
*  cmap.c cmap routines for 256color librarys-svgalib style*
***********************************************************/
#include "koules.h"
#include "..\DirectDrawWin.H"

static int	fadedout = 0;

static INLINE int col(int p, CONST double p1)
{
	p = (int)(p*p1);
	if (p > 63)
		return (63);
	if (p < 0)
		return (0);
	return (p);
}

void setcustompalette (CONST int p, CONST double p1)
{ /* 0-31 black to yellow for starwars scroller */
  /* 32-63    black to red */
  /* 64-96    for red koules */
  /* 96-128   for yellow rockets */
  /* 128-160   for green rockets */
  /* 160-192   for blue rockets */
  /* 192-256   gray cmap for stars */
	RGBQUAD         pal[256];
	int             i;
	for (i = 0; i < 64; i++)
    {
		int             r, g, b;
		r = g = b = 0;
		if ((i & 32) > 0)
			b = (i & 31) << 1;
		if (i < 32)
		{
			r = (i & 3) << 4;	// 2 bits 
			g = (i & 4) << 3;	// 1 bit 
			b = (i & 24) << 1;//2 bits 
		}
		pal[i].rgbRed = col (r + p, p1);
		pal[i].rgbGreen = col (g + p, p1);
		pal[i].rgbBlue = col (b + p, p1);
    }
	for (i = 64; i < 64 + 32; i++)
    {
		int             r, g, b;
		r = g = b = 0;
		r = (32 - (i - 63)) << 1;
		if (i < 64 + 8)
			b = g = (((8 - (i - 63))) << 5) / 5;
		pal[i].rgbRed = col (r + p, p1);
		pal[i].rgbGreen = col (g + p, p1);
		pal[i].rgbBlue = col (b + p, p1);
    }
	for (i = 96; i < 96 + 32; i++)
    {
		int             r, g, b;
		r = g = b = 0;
		r = g = (32 - (i - 95)) << 1;
		if (i < 96 + 8)
			b = ((8 - (i - 95))) << 3;
		pal[i].rgbRed = col (r + p, p1);
		pal[i].rgbGreen = col (g + p, p1);
		pal[i].rgbBlue = col (b + p, p1);
    }
	for (i = 128; i < 128 + 32; i++)
    {
		int             r, g, b;
		r = g = b = 0;
		g = (32 - (i - 127)) << 1;
		if (i < 128 + 8)
			r = b = ((8 - (i - 127))) << 3;
		pal[i].rgbRed = col (r + p, p1);
		pal[i].rgbGreen = col (g + p, p1);
		pal[i].rgbBlue = col (b + p, p1);
    }
	for (i = 160; i < 160 + 32; i++)
    {
		int             r, g, b;
		r = g = b = 0;
		b = (32 - (i - 159)) << 1;
		if (i < 160 + 8)
			r = g = (((8 - (i - 159))) << 3) / 2;
		pal[i].rgbRed = col (r + p, p1);
		pal[i].rgbGreen = col (g + p, p1);
		pal[i].rgbBlue = col (b + p, p1);
    }
	for (i = 0; i < 32; i++)
    {
		pal[i].rgbRed = col (i * 2 + p, p1);
		pal[i].rgbGreen = col (i * 2 + p, p1);
		pal[i].rgbBlue = col (p, p1);
    }
	for (i = 0; i < 32; i++)
    {
		pal[192 + i].rgbRed = col (i * 2 + p, p1);
		pal[192 + i].rgbGreen = col (i * 2 + p, p1);
		pal[192 + i].rgbBlue = col (i * 2 + p, p1);

	  pal[192 + i+32].rgbRed = col (i * 2+1 + p, p1);
      pal[192 + i+32].rgbGreen = col (i * 2+1 + p, p1);
      pal[192 + i+32].rgbBlue = col (i * 2+1 + p, p1);

    }
	pal[0].rgbRed = 0;
	pal[0].rgbGreen = 0;
	pal[0].rgbBlue = 0;
	pal[255].rgbRed = col (64 + p, p1);
	pal[255].rgbGreen = col (64 + p, p1);
	pal[255].rgbBlue = col (64 + p, p1);
	for(i=0;i<256;i++)
	{
		pal[i].rgbRed <<=2;
		pal[i].rgbGreen <<=2;
		pal[i].rgbBlue <<=2;
	}
	GetDDWin()->CreatePalette(pal,256);
}

void fadeout ()
{
	if (!fadedout)
    {
		double           i;
		for (i = 1; i >= 0; i -= 0.1)
		{
			setcustompalette (0, i);
			USleep (50), tbreak = 1;
		}
		setcustompalette (-65, 0);
		fadedout = 1;
    }
}


void fadein ()
{
	if (fadedout)
    {
		double           i;
		for (i = 0; i <= 1; i += 0.1)
		{
			setcustompalette (0, i);
			USleep (100), tbreak = 1;
		}
		setcustompalette (0, 1);
		fadedout = 0;
    }
}

void fadein1 ()			/*better for star background */
{
	if (fadedout)
    {
		int             i;
		for (i = -64; i <= 0; i += 6)
		{
			setcustompalette (i, 1);
			USleep (100), tbreak = 1;
		}
		setcustompalette (0, 1);
		fadedout = 0;
    }
}

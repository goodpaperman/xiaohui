/***********************************************************
*  interface.h   interface for vgakeyboard                 *
***********************************************************/
#ifndef INPUT_H
#define INPUT_H

extern void UpdateInput(void);
extern BOOL InitDirectInput();
extern BOOL ReleaseDirectInput();
extern int mouse_getbutton();
extern int IsPressed(BYTE);
extern INLINE IsPressing(BYTE);
extern int mouse_getx();
extern int mouse_gety();
extern int Pressed ();
extern  int GetKey ();
extern void SetCurPos(int x,int y);

extern BOOL MouseFound;
#define SCANCODE_TAB				15
#define SCANCODE_P					25
#define SCANCODE_ESCAPE				1
#define SCANCODE_ENTER				28
#define SCANCODE_SPACE				57
#define SCANCODE_KEYPADENTER		28
#define SCANCODE_CURSORUP			200
#define SCANCODE_CURSORBLOCKUP		200
#define SCANCODE_CURSORDOWN			208
#define SCANCODE_CURSORBLOCKDOWN	208
#define SCANCODE_CURSORLEFT			203
#define	SCANCODE_CURSORBLOCKLEFT	203	
#define SCANCODE_CURSORRIGHT		205
#define	SCANCODE_CURSORBLOCKRIGHT	205

#define MouseButtons() mouse_getbutton()
#define MouseX() mouse_getx()
#define MouseY() mouse_gety()

#define IsPressedEsc() IsPressed (SCANCODE_ESCAPE)
#define IsPressedP() IsPressed (SCANCODE_P)
#define IsPressingEnter() (IsPressing (SCANCODE_ENTER)||\
                        IsPressing (SCANCODE_SPACE)||\
                        IsPressing (SCANCODE_KEYPADENTER))
#define IsPressingUp() (IsPressing (SCANCODE_CURSORUP) ||\
		     IsPressing (SCANCODE_CURSORBLOCKUP))
#define IsPressingDown() (IsPressing (SCANCODE_CURSORDOWN) ||\
		     IsPressing (SCANCODE_CURSORBLOCKDOWN))
#define IsPressingLeft() (IsPressing (SCANCODE_CURSORLEFT) ||\
		     IsPressing (SCANCODE_CURSORBLOCKLEFT))
#define IsPressingRight() (IsPressing (SCANCODE_CURSORRIGHT) ||\
		     IsPressing (SCANCODE_CURSORBLOCKRIGHT))
#endif

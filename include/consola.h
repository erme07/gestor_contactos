#ifndef _COLOR_
#define _COLOR_

//COLORES PARA CONSOLA
#define FGRED 	FOREGROUND_RED
#define FGBLUE 	FOREGROUND_BLUE
#define FGGREEN FOREGROUND_GREEN
#define FGINT 	FOREGROUND_INTENSITY

#define BGRED 	BACKGROUND_RED
#define BGBLUE 	BACKGROUND_BLUE
#define BGGREEN BACKGROUND_GREEN
#define BGINT 	BACKGROUND_INTENSITY

#define IDI_ICON1 101

//VARIABLES GLOBALES PARA MANEJAR CONSOLA
extern HANDLE hConsole;
extern HWND wConsole;
extern WORD invert, initial, orange, red, yellow;

void initConsole(void);
void setConsoleColor(WORD); 
void disableResize(void);
void setConsoleSize(int,int);
void setCursorPos(int,int); 
void changeIcon(void);        
	
#endif //_COLOR_
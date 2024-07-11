#include <windows.h>
#include <stdio.h>
#include "consola.h"
#include "menu.h"

//VARIABLES GLOBALES PARA MANEJAR CONSOLA
HANDLE hConsole;
HWND wConsole;
WORD invert, initial, orange, red, yellow;

void initConsole(){
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    wConsole = GetConsoleWindow();
    invert = BGBLUE | BGGREEN | BGRED;
	initial = FGBLUE | FGGREEN | FGRED;
	orange = FGRED | FGGREEN;
	yellow = FGRED | FGGREEN | FGINT;
	red = FGRED | FGINT;
}
void setConsoleColor(WORD color) {
    SetConsoleTextAttribute(hConsole, color);
}
void setConsoleSize(int width, int height){
    RECT r;
    GetWindowRect(wConsole, &r); // Obtiene el tamaño actual de la consola
    MoveWindow(wConsole, r.left, r.top, width, height, TRUE);
}
void disableResize(){
    LONG style = GetWindowLong(wConsole, GWL_STYLE);
    style &= ~WS_SIZEBOX;
    SetWindowLong(wConsole, GWL_STYLE, style);
}
void setCursorPos(int x, int y) {
    COORD pos = {x,y}; //posicion.X = x;  //posicion.Y = y;
    SetConsoleCursorPosition(hConsole, pos);
}
void changeIcon(){
    HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
    SendMessage(wConsole, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
    SendMessage(wConsole, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
}

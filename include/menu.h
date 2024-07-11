#ifndef _MENU_
#define _MENU_

//CODIGO ASCII DE LAS TECLAS
#define KEY0		48  // Tecla 0
#define KEY1 		49  // Tecla 1
#define KEY2 		50  // Tecla 2
#define KEY3 		51  // Tecla 3
#define KEY4 		52  // Tecla 4
#define KEY5 		53  // Tecla 5
#define KEY6 		54  // Tecla 6
#define ENTER 		13  // ENTER
#define ARROWUP 	72  // flecha arriba
#define ARROWDOWN	80  // flecha abajo
#define ARROWLEFT 	75  // flecha izquierda
#define ARROWRIGHT	77  // flecha derecha

//INDICADOR DE OPCION SELECCIONADA
#define ESP  ">  "

void menu(int);
void opcOneSelec(void);
void opcTwoSelec(void);
void opcThreeSelec(void);
void opcFourSelec(void);
void opcFiveSelec(void);
void opcSixSelec(void);
int defineOption(int,int);

void menuEdit(int);
void opcNameEdit(void);
void opcSurnameEdit(void);
void opcPhoneEdit(void);
void opcMailEdit(void);
void opcExitEdit(void);
int defineEdit(int,int);

void menuDelete(int);
void opcConfirm(void);
void opcCancel(void);
int defineDelete(int,int);
	
#endif //_MENU_

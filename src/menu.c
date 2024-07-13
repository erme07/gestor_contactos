#include <stdio.h>
#include <stdlib.h>
//#include <windows.h>
#include <conio.h>
#include "consola.h"
#include "menu.h"

void menu(int opcion){
    system("cls");
	setConsoleColor(yellow);
	printf("\n\t\t\t GESTOR DE CONTACTOS \n\n");
	setConsoleColor(initial);
	switch(opcion){
        case 1: opcOneSelec(); break;
        case 2: opcTwoSelec(); break;
        case 3: opcThreeSelec(); break;
        case 4: opcFourSelec(); break;
        case 5: opcFiveSelec(); break;
        case 6: opcSixSelec(); break;
    }
	printf("\n Navegue entre las opciones y presione ENTER: ");
}

int defineOption(int key, int opt){
    if(key == 224){
        key = getch();
        if(key == ARROWUP)
            return (opt == 1) ? 6 : opt-1;
    	else if(key == ARROWDOWN)
            return (opt == 6) ? 1 : opt+1;
	else 
		return opt;
    }else 
		return (key >= KEY1 && key <= KEY6) ? key-48 : opt;
}

void opcOneSelec(){
	setConsoleColor(orange);
    printf(" %s1) Agregar Contacto\n",ESP);
    setConsoleColor(initial);
	printf(" 2) Mostrar Contactos\n 3) Buscar Contactos\n 4) Editar Contacto\n 5) Eliminar Contacto\n 6) Salir\n");	
}
void opcTwoSelec(){
	printf(" 1) Agregar Contacto\n");
    setConsoleColor(orange);
    printf(" %s2) Mostrar Contactos\n",ESP);
    setConsoleColor(initial);
    printf(" 3) Buscar Contactos\n 4) Editar Contacto\n 5) Eliminar Contacto\n 6) Salir\n");
}
void opcThreeSelec(){
	printf(" 1) Agregar Contacto\n 2) Mostrar Contactos\n");
    setConsoleColor(orange);
    printf(" %s3) Buscar Contactos\n",ESP);
    setConsoleColor(initial);
    printf(" 4) Editar Contacto\n 5) Eliminar Contacto\n 6) Salir\n");
}
void opcFourSelec(){
	printf(" 1) Agregar Contacto\n 2) Mostrar Contactos\n 3) Buscar Contactos\n");
    setConsoleColor(orange);
    printf(" %s4) Editar Contacto\n",ESP);
    setConsoleColor(initial);
    printf(" 5) Eliminar Contacto\n 6) Salir\n");
}
void opcFiveSelec(){
	printf(" 1) Agregar Contacto\n 2) Mostrar Contactos\n 3) Buscar Contactos\n 4) Editar Contacto\n");
    setConsoleColor(orange);
    printf(" %s5) Eliminar Contacto\n",ESP);
    setConsoleColor(initial);
    printf(" 6) Salir\n");
}
void opcSixSelec(){
	printf(" 1) Agregar Contacto\n 2) Mostrar Contactos\n 3) Buscar Contactos\n 4) Editar Contacto\n 5) Eliminar Contacto\n");
    setConsoleColor(red);
    printf(" %s6) Salir\n",ESP);
    setConsoleColor(initial);
}

//-------------

void menuEdit(int opcion){
	setConsoleColor(orange);
	printf("\n EDICI%cN DE CONTACTO \n\n",224);
    setConsoleColor(yellow);
    printf(" Seleccione el dato que quiere editar:\n\n");
    setConsoleColor(initial);
	switch(opcion){
        case 1: opcNameEdit(); break;
        case 2: opcSurnameEdit(); break;
        case 3: opcPhoneEdit(); break;
        case 4: opcMailEdit(); break;
        case 5: opcExitEdit(); break;
    }
	printf("\n Navegue entre las opciones y presione ENTER: ");
}

int defineEdit(int key, int opt){
    if(key == 224){
        key = getch();
        if(key == ARROWUP)
            return (opt == 1) ? 5 : opt-1;
    	else if(key == ARROWDOWN)
            return (opt == 5) ? 1 : opt+1;
	else 
		return opt;
    }else 
		return (key >= KEY1 && key <= KEY5) ? key-48 : opt;
}

void opcNameEdit(){
	setConsoleColor(orange);
    printf(" %s1) Nombre\n",ESP);
    setConsoleColor(initial);
	printf(" 2) Apellido\n 3) Tel%cfono\n 4) Correo\n 5) Salir\n",130);	
}
void opcSurnameEdit(){
	printf(" 1) Nombre\n");
    setConsoleColor(orange);
    printf(" %s2) Apellido\n",ESP);
    setConsoleColor(initial);
    printf(" 3) Tel%cfono\n 4) Correo\n 5) Salir\n",130);
}
void opcPhoneEdit(){
	printf(" 1) Nombre\n 2) Apellido\n");
    setConsoleColor(orange);
    printf(" %s3) Tel%cfono\n",ESP,130);
    setConsoleColor(initial);
    printf(" 4) Correo\n 5) Salir\n");
}
void opcMailEdit(){
	printf(" 1) Nombre\n 2) Apellido\n 3) Tel%cfono\n",130);
    setConsoleColor(orange);
    printf(" %s4) Correo\n",ESP);
    setConsoleColor(initial);
    printf(" 5) Salir\n");
}
void opcExitEdit(){
	printf(" 1) Nombre\n 2) Apellido\n 3) Tel%cfono\n 4) Correo\n",130);
    setConsoleColor(red);
    printf(" %s5) Salir\n",ESP);
    setConsoleColor(initial);
}

//-------------

void menuDelete(int opcion){
	setConsoleColor(orange);
	printf("\n ELIMINAR CONTACTO \n\n");
    setConsoleColor(yellow);
    printf(" Quiere eliminar el contacto seleccionado?\n\n");
    setConsoleColor(initial);
	switch(opcion){
        case 1: opcCancel(); break;
        case 2: opcConfirm(); break;
    }
	printf("\n Navegue entre las opciones y presione ENTER: ");
}

int defineDelete(int key, int opt){
    if(key == 224){
        key = getch();
        if(key == ARROWUP)
            return (opt == 1) ? 2 : opt-1;
    	else if(key == ARROWDOWN)
            return (opt == 2) ? 1 : opt+1;
	else 
		return opt;
    }else 
		return (key >= KEY1 && key <= KEY2) ? key-48 : opt;
}

void opcConfirm(){
    printf(" 1) Cancelar\n");
    setConsoleColor(red);
	printf(" %s2) Confirmar\n",ESP);
	setConsoleColor(initial);
}
void opcCancel(){
    setConsoleColor(orange);
    printf(" %s1) Cancelar\n",ESP);
    setConsoleColor(initial);
    printf(" 2) Confirmar\n");
}

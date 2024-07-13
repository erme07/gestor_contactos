#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include "contactlist.h"
#include "consola.h"
#include "menu.h"
#include "draw.h"


Contact createContact(){
	Contact c;
	system("cls");
  setConsoleColor(orange);
	printf("\n CREAR NUEVO CONTACTO\n\n");
  setConsoleColor(initial);
  printf(" Ingrese los datos de la persona\n\n");
	printf(" %11s: ","Nombre");
	fflush(stdin);
  setConsoleColor(yellow);
	scanf("%24[^\n]",c.nombre);
  setConsoleColor(initial);
	printf(" %11s: ","Apellido");
	fflush(stdin);
  setConsoleColor(yellow);
	scanf("%24[^\n]",c.apellido);
  setConsoleColor(initial);
	printf(" %6s%cfono: ","Tel",130);
	fflush(stdin);
  setConsoleColor(yellow);
	scanf("%d",&c.telefono);
  setConsoleColor(initial);
	printf(" %11s: ","Correo");
	fflush(stdin);
  setConsoleColor(yellow);
	scanf("%49[^\n]",c.correo);
  setConsoleColor(initial);
	c.next = NULL;
	printf("\n ");
	system("pause");
	system("cls");
	return c;
}

Contact *addContact(Contact cont){
	Contact* c=(Contact*)malloc(sizeof(Contact));
	if(c==NULL){
		perror("Error al asignar memoria, ");
		return NULL;	
	}
	strcpy(c->nombre,cont.nombre);
	strcpy(c->apellido,cont.apellido);
	strcpy(c->correo,cont.correo);
	c->telefono = cont.telefono;
	c->next = NULL;
	return c;
}

void deleteContact(List *l, Contact *c){
	int opc=2,keydown=0;
	do{
		printContact(c);
		menuDelete(opc);
		keydown = getch();
    opc = defineDelete(keydown, opc);
    if(keydown == ENTER){
      if(opc==2){
        l->total--;
        free(c);
      }
      else if(opc==1){
        pushOrderContact(l, c);
        l->total--;
      }
      
		}
	}while( keydown != ENTER);
}

void editContact(Contact *c){
	int opc=1,keydown=0;
	do{	
		printContact(c);
		menuEdit(opc);
		keydown = getch();
    	opc = defineEdit(keydown, opc); 
    	if(keydown == ENTER){
    		switch(opc){
    			case 1:
    				printf("\n\n Ingrese el nombre modificado: ");
					fflush(stdin);
					scanf("%24[^\n]",c->nombre);
					break;
    			case 2: 
					printf("\n\n Ingrese el apellido modificado: ");
					fflush(stdin);
					scanf("%24[^\n]",c->apellido);
					break;
    			case 3: 
					printf("\n\n Ingrese el tel%cfono modificado: ",130);
					fflush(stdin);
					scanf("%d",&c->telefono);
					break;
    			case 4:
					printf("\n\n Ingrese el correo modificado: ");
					fflush(stdin);
					scanf("%49[^\n]",c->correo);
					break;
			} 	
		}
	}while( !(opc == 5 && keydown == ENTER));
}

void pushContact(List *l, Contact *c){
	if(isEmpty(l)){
		l->first=c;
		l->last=c;
	}else{
		l->last->next=c;
		l->last=c;
	}
	l->total++;
}

int compareContacts(Contact *a, Contact *b) {
  char auxnombre[25],auxapellido[25];
  strcpy(auxnombre, b->nombre);
  strcpy(auxapellido, b->apellido);
  toLowerCase(auxnombre);
  toLowerCase(auxapellido);
  int cmpName = strcmp(a->nombre, auxnombre);
  if (cmpName == 0)
    return strcmp(a->apellido, auxapellido);
  return cmpName;
}

void pushOrderContact(List *l, Contact *c){
	Contact *current= l->first;
	if (current == NULL || compareContacts(c, l->first) < 0) {
        c->next = l->first;
        l->first = c;
        if (l->last == NULL)
            l->last = c;
    } else {
        while (current->next != NULL && compareContacts(c, current->next) > 0)
            current = current->next;
        c->next = current->next;
        current->next = c;
        if (c->next == NULL)
            l->last = c;
    }
	l->total++;
}

void printContact(Contact *c){
	system("cls");
	setConsoleColor(yellow);
	printf("\n  #  %-25s %-25s %-15s %-45s\n","Nombre","Apellido","Telefono","Correo");
	drawSeparator();
	setConsoleColor(initial);
	printf(" 01  ");
	printf("%s ",c->nombre);
	setCursorPos(31, 3);
	printf("%s ",c->apellido);
	setCursorPos(57, 3);
	printf("%d ",c->telefono);
	setCursorPos(73, 3);
	printf("%s\n\n",c->correo);		
}

void toLowerCase(char *str){
	while (*str) {
		*str = tolower((unsigned char) *str);
		str++;
	}
}

int findStr(char *str1, char *str2) {
	char *tempStr1 = malloc(strlen(str1) + 1);
	int result;
	strcpy(tempStr1, str1);
	toLowerCase(tempStr1);
	if(strstr(tempStr1, str2)==NULL)
		result = 0;
	else
		result = 1;
	free(tempStr1);
	return result;
}

List *searchContacts(List *l){
	List *slist = createList();
	Contact *current = l->first;
	Contact *aux;
	char name[25];
	system("cls");
	do{
		printf("\n Ingrese el nombre a buscar: ");
		scanf("%24[^\n]",name);
		fflush(stdin);
		system("cls");
		if(strlen(name) < 3)
			printf("\n El nombre debe debe ser de al menos tres caracteres\n");
	}while(strlen(name) < 3);
	toLowerCase(name);	
	while(current != NULL){
		if(findStr(current->nombre,name)==1){
			aux = addContact(*current);
			pushContact(slist,aux);
		}
		current = current->next;
	}
	return slist;
}

int selectContact(List *l,int mode){
	int cont=1,page=0,totalpage,key,selected=1;
	Contact *current;
	
	totalpage=l->total/15;
	if(l->total%15!=0)
		totalpage++;	
	system("cls");	
	if(isEmpty(l)){
		printf("\n AUN NO HAY CONTACTOS\n\n ");
		system("pause");
	}
	else{
		do{
			current = l->first;
			cont=1;
			system("cls");
			setConsoleColor(yellow);
			printf("\n  #  %-25s %-25s %-15s %-45s\n","Nombre","Apellido","Telefono","Correo");
			drawSeparator();
			setConsoleColor(initial);
			while(current != NULL){
				if(selected==cont){
					setConsoleColor(invert);
					printf("%118s"," "); //relleno toda la linea con espacios pintados
					setCursorPos(0, cont+2-(15*page));//vuelvo a la primer posicion para comenzar a escribir los datos
				}
				if((cont>=1+(page*15)) && (cont<=15+(page*15))){
					printf(" %02d  ",cont);
					printf("%s ",current->nombre);
					setCursorPos(31, cont+2-(15*page));
					printf("%s ",current->apellido);
					setCursorPos(57, cont+2-(15*page));
					printf("%d ",current->telefono);
					setCursorPos(73, cont+2-(15*page));
					printf("%s\n",current->correo);
				}
				setConsoleColor(initial);
				current = current->next;
				cont++;
			}
			if(totalpage>1){
				drawPagination(page,totalpage);
			}
      setConsoleColor(yellow);
      if(mode == EDIT)
        printf("\n Seleccione el contacto que quiere EDITAR\n");
      else
        printf("\n Seleccione el contacto que quiere ELIMINAR\n");
      setConsoleColor(initial);
      printf("\n Navegue y presione ENTER para elegir (0 para cancelar) ");
			do{
				key=getch();
				if(key == 224)
					key = getch();
				if(key == ARROWDOWN){ //flecha down
					if(selected%15==0 && selected != l->total)
						page++;	
					if(totalpage==1)
						selected = (selected == l->total) ? 1 : selected + 1;
					else if(selected != l->total){
						selected++;
					}
				}else if(key == ARROWUP){ //flecha up
					if((selected-1)%15 == 0 && selected!=1)
						page--;
					if(totalpage==1)
						selected = (selected == 1) ? l->total : selected - 1;
					else if(selected != 1){
						selected--;
					}
				}else if(key == ARROWRIGHT && page+1<totalpage){ //flecha der
					selected = (selected+15 <= l->total) ? selected+15 : l->total;
					page++;
				}else if(key == ARROWLEFT && page+1>1){ //flecha izq
					if(selected-15>=1)
						selected-=15;
					page--;
				}
			}while(key!=ENTER && key!=ARROWUP && key!=ARROWDOWN && key!=ARROWLEFT && key!=ARROWRIGHT && key!=KEY0);
		}while(key != ENTER && key!=KEY0);
		if(key==KEY0)
			return 0;
		else
			return selected;
	}
	return 0;
}
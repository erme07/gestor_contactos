#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "contactlist.h"
#include "consola.h"
#include "menu.h"
#include "draw.h"


void freeMemory(List *l){
	Contact *current= l->first;
	Contact *next;
	while(current != NULL){
		next = current->next;
		free(current);
		current = next;
	}
	l->first = NULL;
	free(l);
}

void loadList(List* l) {
	FILE* file = fopen("./data/data.txt", "r");
	if (file == NULL) {
		perror("Error al abrir el archivo, ");
		printf("\n\n ");
		system("pause");
		return;
	}
	Contact c;
	while (fscanf(file, "%24[^,],%24[^,],%d,%44[^\n]\n", c.nombre, c.apellido, &c.telefono, c.correo) == 4) {
		pushContact(l,addContact(c));
	}
	fclose(file);
}

void saveList(List* l) {
	FILE* file = fopen("data/data.txt", "w");
	if (file == NULL) {
		perror("Error al abrir el archivo, ");
		printf("\n\n ");
		system("pause");
		return;
	}
	Contact* current = l->first;
	while (current != NULL) {
		fprintf(file, "%s,%s,%d,%s\n", current->nombre, current->apellido, current->telefono, current->correo);
		current = current->next;
	}
	fclose(file);
}

List *createList(){
	List *l=(List*)malloc(sizeof(List));
	if(l==NULL){
		perror("Error al asignar memoria, ");
		return NULL;	
	}
	l->first = NULL;
	l->total = 0;
	l->last = NULL;
	return l;
}

int isEmpty(List *l){
	return (l->first==NULL) ? 1 : 0;
}

void printList(List *l){
	int cont=1,page=0,totalpage,key;
	Contact *current= l->first;
	
	totalpage=l->total/15;
	if(l->total%15!=0)
		totalpage++;
		
	system("cls");	
	if(isEmpty(l)){
		printf("\n AUN NO HAY CONTACTOS\n\n ");
		system("pause");
	}else{
		do{
			system("cls");
			setConsoleColor(yellow);
			printf("\n  #  %-25s %-25s Tel%cfono%-7s %-45s\n","Nombre","Apellido",130," ","Correo");
			drawSeparator();
			setConsoleColor(initial);
			while(current != NULL){
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
				current = current->next;
				cont++;
			}
			current= l->first;
			cont=1;
			
			if(totalpage==1){
				printf("\n\n ");
				system("pause");
				key = ENTER;
			}else{
				drawPagination(page,totalpage);
				current= l->first;
				cont=1;
				printf(" Navegue con las flechas de direcci%cn, presione ENTER para salir...",162);
				key=getch();
				if(key == 224)
					key = getch();
				if(key == ARROWRIGHT && page+1<totalpage)
					page++;
				else if(key == ARROWLEFT && page+1>1)
					page--;
			}	
		}while(totalpage != 1 && key != ENTER);
	}
}

void modifyList(List *l, int numcontact,int mode){
	Contact *c,*current;
	if(numcontact!=0){
		int cont=1;
		current=l->first;
		
		if(numcontact==1){
			l->first = current->next;
			current->next = NULL;
			c = current;
		}else{
			while(current != NULL){
				if(cont+1==numcontact){
					c = current->next;
					current->next = c->next;
					c->next = NULL;
					break;
				}
				current = current->next;
				cont++;
			}
		}
		if(mode == EDIT){
			editContact(c);
			pushOrderContact(l, c);
			l->total--;
		}
		else
			deleteContact(l,c);
	}
}
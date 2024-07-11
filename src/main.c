#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <ctype.h>
#include "consola.h"
#include "menu.h"

#define EDIT 	1
#define DLETE 	0


typedef struct contact{
	char nombre[25];
	char apellido[25];
	char correo[45];
	int telefono;
	struct contact *next;
}Contact;

typedef struct list{
	Contact *first;
	int total;
	Contact *last;
}List;


List *createList();
void saveList(List*);
void loadList(List*);
void printList(List*);
void printContact(Contact*);

int isEmpty(List*);

Contact createContact();
Contact *addContact(Contact);
int compareContacts(Contact*,Contact*);
void pushContact(List*,Contact*);
void pushOrderContact(List*,Contact*);

void freeMemory(List*);
void drawSeparator();
void drawPagination(int,int);

void toLowerCase(char*);
char *findStr(const char*, const char*);
List *searchContacts(List*);
int selectContact(List*);
void modifyList(List*,int,int);
void editContact(Contact*);
void deleteContact(List*,Contact*);

int main() {
	int opc = 1, keydown = 0;
    List *list = createList();
    List *searchlist;
    Contact c;
    
    initConsole();
    SetConsoleTitle("Agenda Electronica");
    changeIcon();
    setConsoleSize(1000, 500);
    disableResize();
    setConsoleColor(initial);
    loadList(list);
    
	do{
		menu(opc);
		keydown = getch();
    	opc = defineOption(keydown, opc); 
    	if(keydown == ENTER){
    		switch(opc){
    			case 1:
    				c = createContact();
    				pushOrderContact(list,addContact(c));
    				saveList(list);
					break;
    			case 2: 
					printList(list);
					break;
    			case 3: 
					searchlist = searchContacts(list);
					printList(searchlist);
					freeMemory(searchlist);
					break;
    			case 4:
					modifyList(list,selectContact(list),EDIT);
					saveList(list);
					break;
    			case 5: 
					modifyList(list,selectContact(list),DLETE);
					saveList(list);
					break;
			} 	
		}
	}while( !(opc == 6 && keydown == ENTER));
	saveList(list);
	freeMemory(list);
	return 0;
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

Contact createContact(){
	Contact c;
	system("cls");
	printf("\n AGREGAR CONTACTO\n\n");
	printf(" Ingrese el nombre: ");
	fflush(stdin);
	scanf("%24[^\n]",c.nombre);
	printf(" Ingrese el apellido: ");
	fflush(stdin);
	scanf("%24[^\n]",c.apellido);
	printf(" Ingrese el tel%cfono: ",130);
	fflush(stdin);
	scanf("%d",&c.telefono);
	printf(" Ingrese el correo: ");
	fflush(stdin);
	scanf("%49[^\n]",c.correo);
	c.next = NULL;
	printf("\n ");
	system("pause");
	system("cls");
	return c;
}

int isEmpty(List *l){
	return (l->first==NULL) ? 1 : 0;
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
    int cmpName = strcmp(a->nombre, b->nombre);
    if (cmpName == 0) 
        return strcmp(a->apellido, b->apellido);
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

void drawSeparator(){
	int i;
	setConsoleColor(orange);
	printf(" %c%c  ",196,196);
	for(i=0;i<25;i++)
		printf("%c",196);
	printf(" ");
	for(i=0;i<25;i++)
		printf("%c",196);
	printf(" ");
	for(i=0;i<15;i++)
		printf("%c",196);
	printf(" ");
	for(i=0;i<45;i++)
		printf("%c",196);
	printf("\n");
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

void drawPagination(int page,int totalpage){
	int simbolo;
	printf("\n ");
	setConsoleColor(orange);
	for(int i=0;i<11;i++){
		if(i==0) simbolo = 218;
		if(i>0 && i<10) simbolo = 196;
		if(i==10) simbolo = 191;
		printf("%c",simbolo);
	}
	printf("%93s"," ");
	for(int i=0;i<11;i++){
		if(i==0) simbolo = 218;
		if(i>0 && i<10) simbolo = 196;
		if(i==10) simbolo = 191;
		printf("%c",simbolo);
	}
	printf("\n %c ",179);
	setConsoleColor(yellow);
	printf("<- PREV ");
	setConsoleColor(orange);
	printf("%c%44s%02d/%02d%44s%c ",179," ",page+1,totalpage," ",179);
	setConsoleColor(yellow);
	printf("NEXT ->");
	setConsoleColor(orange);
	printf(" %c\n ",179);
	for(int i=0;i<11;i++){
		if(i==0) simbolo = 192;
		if(i>0 && i<10) simbolo = 196;
		if(i==10) simbolo = 217;
		printf("%c",simbolo);
	}
	printf("%93s"," ");
	for(int i=0;i<11;i++){
		if(i==0) simbolo = 192;
		if(i>0 && i<10) simbolo = 196;
		if(i==10) simbolo = 217;
		printf("%c",simbolo);
	}
	printf("\n\n");
	setConsoleColor(initial);
}

void printList(List *l){
	int cont=1,page=0,totalpage,key;
	Contact *current= l->first;
	
	totalpage=l->total/15;
	if(l->total%15!=0)
		totalpage++;
		
	system("cls");	
	if(isEmpty(l)){
		printf(" Aun no hay contactos");
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

int selectContact(List *l){
	int cont=1,page=0,totalpage,key,selected=1;
	Contact *current;
	
	totalpage=l->total/15;
	if(l->total%15!=0)
		totalpage++;	
	system("cls");	
	if(isEmpty(l))
		printf(" Aun no hay contactos");
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
			printf("\n Navegue y presione ENTER para seleccionar el contacto (0 para cancelar)... ");
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

void deleteContact(List *l, Contact *c){
	int opc=2,keydown=0;
	do{	
		printContact(c);
		menuDelete(opc);
		keydown = getch();
    	opc = defineDelete(keydown, opc);
    	if(keydown == ENTER){
    		if(opc==2)
    			free(c);
			else if(opc==1)
				pushOrderContact(l, c);	
		}
	}while( keydown != ENTER);
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
		}
		else
			deleteContact(l,c);
	}
}



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

void loadList(List* l) {
    FILE* file = fopen("data.txt", "r");
    if (file == NULL) {
        perror("Error al abrir el archivo, ");
        return;
    }
    Contact c;
    while (fscanf(file, "%24[^,],%24[^,],%d,%44[^\n]\n", c.nombre, c.apellido, &c.telefono, c.correo) == 4) {
		pushContact(l,addContact(c));
    }
    fclose(file);
}

void saveList(List* l) {
    FILE* file = fopen("data.txt", "w");
    if (file == NULL) {
        perror("Error al abrir el archivo, ");
        return;
    }
    Contact* current = l->first;
    while (current != NULL) {
        fprintf(file, "%s,%s,%d,%s\n", current->nombre, current->apellido, current->telefono, current->correo);
        current = current->next;
    }
    fclose(file);
}

void toLowerCase(char *str){
    while (*str) {
        *str = tolower((unsigned char) *str);
        str++;
    }
}

char *findStr(const char *str1, const char *str2) {
    char tempStr1[strlen(str1) + 1];
    strcpy(tempStr1, str1);
    toLowerCase(tempStr1);
    return strstr(tempStr1, str2);
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
		if(findStr(current->nombre,name)){
			aux = addContact(*current);
			pushContact(slist,aux);
		}
		current = current->next;
	}
	return slist;
}
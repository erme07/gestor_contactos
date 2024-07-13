#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "consola.h"
#include "menu.h"
#include "contactlist.h"

int main() {
	int opc = 1, keydown = 0;
	List *list = createList();
	List *searchlist;
	Contact c;
	
	initConsole();
	SetConsoleTitle("Gestor de Contactos");
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
					modifyList(list,selectContact(list,EDIT),EDIT);
					saveList(list);
					break;
				case 5: 
					modifyList(list,selectContact(list,DLETE),DLETE);
					saveList(list);
					break;
			} 	
		}
	}while( !(opc == 6 && keydown == ENTER));
	saveList(list);
	freeMemory(list);
	return 0;
}
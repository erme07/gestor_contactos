#ifndef _CONTACT_
#define _CONTACT_

#define EDIT 		1
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


Contact createContact();
Contact *addContact(Contact);
int compareContacts(Contact*,Contact*);
void pushContact(List*,Contact*);
void pushOrderContact(List*,Contact*);

void toLowerCase(char*);
int findStr(char*, char*);
List *searchContacts(List*);
int selectContact(List*,int);

void editContact(Contact*);
void deleteContact(List*,Contact*);
void printContact(Contact*);

List *createList();
void saveList(List*);
void loadList(List*);
void printList(List*);

int isEmpty(List*);
void freeMemory(List*);
void modifyList(List*,int,int);

#endif //_CONTACT_
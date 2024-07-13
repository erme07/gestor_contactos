#include <stdio.h>
#include "consola.h"
#include "draw.h"

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

void isFirstPage(int page,char color){
	if((page+1)==1)
		setConsoleColor(initial);
	else{
		if(color == 'o')
			setConsoleColor(orange);
		else if(color == 'y')
			setConsoleColor(yellow);
	}
}

void isLastPage(int page,int totalpage, char color){
	if((page+1)==totalpage)
		setConsoleColor(initial);
	else{
		if(color == 'o')
			setConsoleColor(orange);
		else if(color == 'y')
			setConsoleColor(yellow);
	}
}

void printTopHalfButton(){
	int simbolo;
	for(int i=0;i<11;i++){
		if(i==0) simbolo = 218;
		if(i>0 && i<10) simbolo = 196;
		if(i==10) simbolo = 191;
		printf("%c",simbolo);
	}
}

void printBottomHalfButton(){
	int simbolo;
	for(int i=0;i<11;i++){
		if(i==0) simbolo = 192;
		if(i>0 && i<10) simbolo = 196;
		if(i==10) simbolo = 217;
		printf("%c",simbolo);
	}
}

void drawPagination(int page,int totalpage){
	printf("\n ");
	isFirstPage(page, 'o');
	printTopHalfButton();
	printf("%95s"," ");
	isLastPage(page,totalpage, 'o');
	printTopHalfButton();
	isFirstPage(page, 'o');
	printf("\n %c ",179);
	isFirstPage(page, 'y');
	printf("<- PREV ");
	isFirstPage(page, 'o');
	printf("%c", 179);
	setConsoleColor(orange);
	printf("%45s%02d/%02d%45s"," ",page+1,totalpage," ");
	isLastPage(page,totalpage, 'o');
	printf("%c", 179);
	isLastPage(page,totalpage, 'y');
	printf(" NEXT ->");
	isLastPage(page,totalpage, 'o');
	printf(" %c\n ",179);
	isFirstPage(page, 'o');
	printBottomHalfButton();
	printf("%95s"," ");
	isLastPage(page,totalpage, 'o');
	printBottomHalfButton();
	printf("\n\n");
	setConsoleColor(initial);
}
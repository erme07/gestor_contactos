#ifndef _DRAW_
#define _DRAW_

void drawSeparator();
void drawPagination(int page, int totalpage);
void printBottomHalfButton();
void printTopHalfButton();
void isLastPage(int page, int totalpage, char color);
void isFirstPage(int page, char color);

#endif //_DRAW_
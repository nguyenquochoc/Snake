#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include "kmin_console.h"

#define MAX 100
#define LEN 1
#define XUONG 2
#define TRAI 3
#define PHAI 4
void gotoxy(int x, int y)
{
    static HANDLE h = NULL;  
    if(!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { x, y };  
    SetConsoleCursorPosition(h,c);
}
struct TOADO{
	int x;
	int y;
};
TOADO ran[MAX];
int sodot = 3;//so luomg pt dau tien
int i ;
void khoitaoran(){
	ran[0].x = 10;
	ran[1].x = 11;
	ran[2].x = 12;
	ran[0].y = ran[1].y = ran[2].y = 1;
};
void hienthiran(){
	for(i = 0; i < sodot;i++){
		gotoxy(ran[i].x,ran[i].y);
		printf("e");
	}
};
void dichuyen(int huong){
	for(i= sodot - 1;i > 0;i --){
		ran[i] = ran[i -1];
	}
	switch (huong){
		case LEN:
			ran[0].y--;
			break;
		case XUONG:
			ran[0].y++;
			break;
		case TRAI:
			ran[0].x--;
			break;
		case PHAI:
			ran[0].x++;
			break;	
	}
};
void batsukien(int &huong){
	int key = getch();
	if (key == 'w' || key == 'W' || key == 72){
		huong = LEN;
		gotoxy(15,13);
		printf("as");
	}
	else if (key == 's' || key == 'S' || key == 80){
		huong = XUONG;
	}
	else if (key == 'a' || key == 'A' || key == 75){
		huong = TRAI;
	}
	else if (key == 'd' || key == 'D' || key == 77){
		huong = PHAI;
	}
};
int main(){
	/*Sleep(1000);
	for (i = 0 ; i <256;i++){
		printf("%d : %c \n",i,(char)i);
	}
	*/
	int huong = PHAI;//huong ban dau khi vao game

	khoitaoran();
	while(1){
		system("cls");
	
		dichuyen(huong);
		hienthiran();
		
		Sleep(500);
		batsukien(huong);
	}
}

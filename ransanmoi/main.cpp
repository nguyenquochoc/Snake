#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include "kmin_console.h"
#include <ctime>
#include <stdlib.h>

#define MAX 100
#define LEN 1
#define XUONG 2
#define TRAI 3
#define PHAI 4
#define TUONG_TREN 2
#define TUONG_DUOI 15
#define TUONG_TRAI 2
#define TUONG_PHAI 65
struct TOADO{
	int x;
	int y;
};
TOADO ran[MAX];
int i ;
int sodot;
int speed = 150;
enum state{
	MENU, INGAME, SETTING, INFORMATION, EXIT
}state;
void khoitaoran(){
	ran[0].x = TUONG_TRAI + 25;
	ran[1].x = TUONG_TRAI + 26;
	ran[2].x = TUONG_TRAI + 27;
	ran[0].y = ran[1].y = ran[2].y = TUONG_TREN + 7;
};
void hienthiran(TOADO dotcuoi){
	for(i = 0; i < sodot;i++){
		
		gotoXY(ran[i].x,ran[i].y);
		if(i == 0){
			setTextColor (12);
			printf("%c",64);
		}else{
			setTextColor (9);
			printf("%c",219);
		}
		noCursorType();
	}
	gotoXY(dotcuoi.x,dotcuoi.y);
	printf(" ");
};
TOADO dichuyen(int huong){
	TOADO dotcuoi = ran[sodot-1];
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
	return dotcuoi;
};
void batsukien(int &huong){
	int key = inputKey();
	if (key == 'w' || key == 'W' || key == 1072 && huong !=XUONG){
		huong = LEN;
	}
	else if (key == 's' || key == 'S' || key == 1080 && huong !=LEN){
		huong = XUONG;
	}
	else if (key == 'a' || key == 'A' || key == 1075 && huong !=PHAI){
		huong = TRAI;
	}
	else if (key == 'd' || key == 'D' || key == 1077 && huong !=TRAI){
		huong = PHAI;
	}
};
void vetuong(){
	setTextColor (6);
	for(i = TUONG_TRAI;i<=TUONG_PHAI;i++){
		gotoXY(i,TUONG_TREN);//in tuong tren,duoi thi y k thay doi
		printf("*");
		gotoXY(i,TUONG_DUOI);
		printf("*");
	}
	for(i = TUONG_TREN;i<=TUONG_DUOI;i++){
		gotoXY(TUONG_TRAI,i);//in tuong trai phai thi x  k thay doi
		printf("*");
		gotoXY(TUONG_PHAI,i);
		printf("*");
	}
};
bool kiemtrathua(){
	if(ran[0].y == TUONG_TREN || ran[0].y == TUONG_DUOI){
		return true;
	}
	if(ran[0].x == TUONG_TRAI || ran[0].x == TUONG_PHAI){
		return true;
	}
	for(i = 1; i < sodot ; i ++){
		if(ran[0].x == ran[i].x && ran[0].y == ran[i].y){
			return true;
		}
	}
	return false;
};
void xulythua(){
	if(kiemtrathua() == true){
		gotoXY(TUONG_TRAI + 20,TUONG_TREN + 5);
		printf("GAME OVER!!!!");
	
	}
};

TOADO hienthimoi(){
	// random trong doan (a,b)
	// a + rand()%(b - a + 1
	srand(time(NULL));// chi in moi trong tuong
	int x = TUONG_TRAI + 1 + rand()%(TUONG_PHAI - TUONG_TRAI - 1);
	int y = TUONG_TREN + 1 + rand()%(TUONG_DUOI - TUONG_TREN - 1);
	for(i = 0;i<sodot;i++){// kiem tra moi cot trung voi than ran k neu co in lai moi
		if(ran[i].x == x && ran[i].y == y ){
			srand(time(NULL));
			x = TUONG_TRAI + 1 + rand()%(TUONG_PHAI - TUONG_TRAI - 1);
			y = TUONG_TREN + 1 + rand()%(TUONG_DUOI - TUONG_TREN - 1);
		}
	}
	setTextColor (10);
	gotoXY (x,y);
	printf("o");
	return TOADO{x,y};
};
void themdot(){
	ran[sodot] = ran[sodot - 1];
	sodot ++;
}
bool anmoi(TOADO moi){
	if(ran[0].x == moi.x && ran[0].y == moi.y){
		return true;
	}else{
		return false;
	}
};
void choilai(){
	int key;
	setTextColor (11);
	gotoXY(TUONG_TRAI + 20,TUONG_TREN + 6);
	printf("PLAY AGAIN ??");
	gotoXY(TUONG_TRAI + 20,TUONG_TREN + 7);
	printf("YES");
	gotoXY(TUONG_TRAI + 30,TUONG_TREN + 7);
	printf("NO");
	int dem = 1;
	gotoXY(TUONG_TRAI + 19,TUONG_TREN + 7);
	printf(">");
	while(1){
		if(kbhit()){
			key = getch();
			if(key == 77){// sang phai
				dem ++;
				if(dem == 3){
					dem = 1;
				}
			}if(key == 75){//sangtrai
				dem --;
				if(dem == 0){
					dem = 2;
				}
			}
			switch(dem){
				case 1:
					gotoXY(TUONG_TRAI + 19,TUONG_TREN + 7);
					printf(">");
					gotoXY(TUONG_TRAI + 29,TUONG_TREN + 7);
					printf(" ");
					
				break;
				case 2:
					gotoXY(TUONG_TRAI + 19,TUONG_TREN + 7);
					printf(" ");
					gotoXY(TUONG_TRAI + 29,TUONG_TREN + 7);
					printf(">");
					
			}
		}
		if(key == 13){
			if(dem == 1){
				speed = 150;
				state = INGAME;
				break;
			}else{
				state = MENU;
				break;
			}
		}
	}
}
void menu(){
	clrscr();
	setTextColor (11);
	for(i = 10;i<=30;i++){
		gotoXY(i,3);//in tuong tren,duoi thi y k thay doi
		printf("*");
		gotoXY(i,10);
		printf("*");
	}
	for(i = 3;i<=10;i++){
		gotoXY(10,i);//in tuong trai phai thi x  k thay doi
		printf("*");
		gotoXY(30,i);
		printf("*");
	}
	setTextColor (12);
	gotoXY(15,5);
	printf("1.PLAY");
	gotoXY(15,6);
	printf("2.SETTING");
	gotoXY(15,7);
	printf("3.INFORMATION");
	gotoXY(15,8);
	printf("4.EXIT");
	gotoXY(13,5);
	printf("->");
	noCursorType();
	int dem = 1;
	int demcu = 1;
	int key;
	while(state == MENU){
		if(kbhit()){
			key = getch();
			if(key == 80){//nut xuong
				dem ++;
				if(dem == 5){
					dem = 1;
				}
			}
			if(key == 72){//nut len
				dem --;
				if(dem == 0 ){
					dem = 4;
				}
			}
			switch(dem){
				case 1:
					if(demcu != dem){
						gotoXY(13,6);
						printf("  ");
						gotoXY(13,7);
						printf("  ");
						gotoXY(13,8);
						printf("  ");
						gotoXY(13,5);
						printf("->");
						demcu = 1;
					}
				break;
				case 2:
					if(demcu != dem){
						gotoXY(13,5);
						printf("  ");
						gotoXY(13,7);
						printf("  ");
						gotoXY(13,8);
						printf("  ");
						gotoXY(13,6);
						printf("->");
						demcu = 2;
					}
				break;
				case 3:
					if(demcu != dem){
						gotoXY(13,5);
						printf("  ");
						gotoXY(13,6);
						printf("  ");
						gotoXY(13,7);
						printf("->");
						gotoXY(13,8);
						printf("  ");
						demcu = 3;
					}
				break;
				case 4:
					if(demcu != dem){
						gotoXY(13,5);
						printf("  ");
						gotoXY(13,6);
						printf("  ");
						gotoXY(13,7);
						printf("  ");
						gotoXY(13,8);
						printf("->");
						demcu = 4;
					}
				break;
			}
		if(key==13){
			switch (dem){
				case 1:			
					state = INGAME;
				break;
				case 2:
					state = SETTING;
				break;
				case 3 :
					state = INFORMATION;
				break;	
				case 4:
					state = EXIT;
				break;	
			}
		}
	}
	Sleep(50);
}
}
void ingame(){
	clrscr();
	int diem = 0;
	sodot = 3;//so luomg pt dau tien
	gotoXY(TUONG_TRAI + 3, TUONG_TREN - 1 );
	setTextColor (10);
	printf(" TOTAL : 0");
	int huong = TRAI;//huong ban dau khi vao game
	vetuong();
	khoitaoran();
	TOADO moi = hienthimoi();
	while(1){
		//system("cls"); hai ham nay giong nhau
		//clrscr();
		TOADO dotcuoi = dichuyen(huong);
		batsukien(huong);
		hienthiran(dotcuoi);
		if(anmoi(moi) == true){
			moi = hienthimoi();
			themdot();
			gotoXY(TUONG_TRAI + 3, TUONG_TREN - 1 );
			diem = diem + 10;
			printf(" TOTAL : %d", diem);
			speed = speed - 2;
		}
		if(kiemtrathua() == true){
			break;
		}
		Sleep(speed);
	}
	xulythua();
	choilai();
}
int  setting( int &speed){
	clrscr();
	gotoXY(30,7);
	setTextColor (6);
	printf("YOUR SNAKE SPEED : ");
	gotoXY(30,8);
	setTextColor (11);
	printf("1    2    3    4    5");
	gotoXY(29,8);
	setTextColor (9);
	printf(">");
	int key;
	int dem = 1;
	int demcu = 1;
	while(1){
		if(kbhit()){
			key = getch();
			if(key == 77){// sang phai
				dem ++;
				if(dem == 6){
					dem = 1;
				}
			}if(key == 75){//sangtrai
				dem --;
				if(dem == 0){
					dem = 5;
				}
			}
			switch(dem){
				case 1:
					gotoXY(29,8);
					printf(">");
					gotoXY(34,8);
					printf(" ");
					gotoXY(39,8);
					printf(" ");
					gotoXY(44,8);
					printf(" ");
					gotoXY(49,8);
					printf(" ");
				break;
				case 2:
				    gotoXY(29,8);
					printf(" ");
					gotoXY(34,8);
					printf(">");
					gotoXY(39,8);
					printf(" ");
					gotoXY(44,8);
					printf(" ");
					gotoXY(49,8);
					printf(" ");
				break;
				case 3:
				    gotoXY(29,8);
					printf(" ");
					gotoXY(34,8);
					printf(" ");
					gotoXY(39,8);
					printf(">");
					gotoXY(44,8);
					printf(" ");
					gotoXY(49,8);
					printf(" ");
				break;
				case 4:
				    gotoXY(29,8);
					printf(" ");
					gotoXY(34,8);
					printf(" ");
					gotoXY(39,8);
					printf(" ");
					gotoXY(44,8);
					printf(">");
					gotoXY(49,8);
					printf(" ");
				break;
				case 5:
				    gotoXY(29,8);
					printf(" ");
					gotoXY(34,8);
					printf(" ");
					gotoXY(39,8);
					printf(" ");
					gotoXY(44,8);
					printf(" ");
					gotoXY(49,8);
					printf(">");
				break;
			}
			if(key == 13){
				state = MENU;
				gotoXY(25,5);
				printf("%d",dem);
				switch (dem){
					case 1:
						speed = 50;
						break;
					case 2:
						speed = 100;
						break;
					case 3:
						speed = 150;
						break;
					case 4:
						speed = 200;
						break;
					case 5:
						speed = 250;
						break;
				}
				break;
			}
		}
	}
	return speed;
};
void information(){
	clrscr();
	while(state == INFORMATION){
		vetuong();
		setTextColor (11);
		gotoXY(TUONG_TRAI + 18,TUONG_TREN + 1);
		printf("_______GAME SNAKE_______");
		setTextColor (14);
		gotoXY(TUONG_TRAI + 12,TUONG_TREN + 3);
		printf("1. PRESS (UP,W,w) to go up");
		gotoXY(TUONG_TRAI + 12,TUONG_TREN + 4);
		printf("2. PRESS (DOWN,S,s) to go down");
		gotoXY(TUONG_TRAI + 12,TUONG_TREN + 5);
		printf("3. PRESS (RIGHT,D,d) to go right ");
		gotoXY(TUONG_TRAI + 12,TUONG_TREN + 6);
		printf("4. PRESS (LEFT,A,a) to go left");
		gotoXY(TUONG_TRAI + 12,TUONG_TREN + 7);
		printf("5. Eat Food To Lengthen The Snake");
		gotoXY(TUONG_TRAI + 19,TUONG_TREN + 9);
		setTextColor (2);
		printf("DESIGN BY HOCNGUYEN");
		noCursorType();
		Sleep(100);
		if(inputKey() == 13){
			state = MENU;
		}
	}
};
void exit(){
	//clrscr();
	exit();
}
int main(){
	state = MENU;
	while(1){
		switch(state){
			case INGAME:
				ingame();
				break;
			case MENU:
				menu();
				break;
			case SETTING:
				setting(speed);
				break;
			case INFORMATION:
				information();
				break;
			case EXIT:
				exit();
				break;
		}
	}	
}

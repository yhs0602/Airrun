/*
변수 명명 규칙
함수명: 소문자-대문자 대문자
변수명: 소문자
자료형: 대문자
*/ 
#include <stdio.h>
#include <Windows.h>
#include <WinGdi.h>
#include <time.h>
#include <stdio.h>
#pragma comment(lib,"winmm")
#include <mmsystem.h>
#include "resource.h"

#define NITEMTYPES 2
#define MAX_BULLETDAMAGE 10

extern HBITMAP hbitsurround[5];
extern HBITMAP hbititem[NITEMTYPES];
extern HBITMAP hbitenemy;
extern HBITMAP hbitbullet[MAX_BULLETDAMAGE],hbitnuclear;
extern HBITMAP hbitplayer,hbitexplosion;
extern HBITMAP hbitcloud;
extern int running;
extern int score;
extern int surnumtodraw;
extern int enemynum,bulletnum;
extern unsigned int cloud_x,cloud_y,count;
extern BOOL sound,stelse;
extern char scoretext[128];
extern HWND hWnd;
extern HWND hButton; 
extern HINSTANCE g_hinst;

class World;
class Item;
class Enemy;
class Bullet;
class Player;
class Game;


#define MAX_ENEMY 200
#define HBIT_ENEMY_SIZE 20
#define SIZE_BEX 20
#define SIZE_BEY 20


class Item
{
      public:
             World * world;
             int x,y;
             BOOL show;
             void draw(HDC hdc);
             void update();
             Item(int x, int y, int type);
             int itemtype;
             void Init();
			 void OnCollide(Player *p);
             int age;             
};

class Enemy
{
      public:
      int x, y, life;
      World *world;
      BOOL show;
      int explosioncount;
      Enemy();    
      void check();
      void move();
      void work();
      void draw(HDC hdc);
      void Init();
};

#define SIZE_BMX 10
#define SIZE_BMY 19
#define MAX_BULLET 200
class Bullet
{
      public:
             World *world;
             Bullet();
             int x,y,damage;
             BOOL show, forward;
             void move();
             void draw(HDC hdc);
             void Init();
};

#define SIZE_BIX 10
#define SIZE_BIY 10


#define SIZE_BPX 20
#define SIZE_BPY 20
class Player
{
      public:
             World *world;
             int x,y,life,left_nuclear,nucleartimercount,pc,damagelevel;
             BOOL bshoot,bshow,bnuclear;
             Player();
             void move(int key);            
             int check();
             void nuclear();
             void draw(HDC hdc);
             void work();
             void Init();
};


extern int SIZE_X;
extern int SIZE_Y;
extern int SIZE_BATX;
extern int SIZE_BATY;

#define SIZE_BCX 135
#define SIZE_BCY 60

#define IDC_BUTTONSTART 1

//////////////////////////////////////gamelib////////////////////////////////////
void DrawBitmap(HDC hdc,HBITMAP hbit, int x, int y, int width, int height,BOOL trans);
void DrawBitmap(HDC hdc,HBITMAP hbit, int x, int y, int width, int height);
void DrawBitmap(HDC hdc,int x,int y,HBITMAP hBit);
void TransBlt(HDC hdc, int x, int y, HBITMAP hbitmap, COLORREF clrMask);
void playBGM(int num);
void myPlaySound(char *filename);
void StopSound();
void mPlaySound(char* a, HINSTANCE g,unsigned int mode);
int menu();
void start();
int  checkbounce(int x, int y, int size_x, int size_y);
void make_enemies();
void shoot(int x, int y, BOOL forward,int damage);
void kill_entities();
void dropItem(int x, int y, int type);
int  checkbounceItem(int x, int y, int size_x, int size_y);

////////////////////////////////////////renderer/////////////////////////////////
void Render();
void rnCreate(HWND hwnd,HDC dc);
void rnSize(int size_x,int size_y);
void rnDestroy();

extern Player *player;
//extern World *theworld;

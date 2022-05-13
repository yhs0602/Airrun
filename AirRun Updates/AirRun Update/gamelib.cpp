#include "main.h"
HBITMAP hBit;
////////////////////////////////////////Bitmap/////////////////////////////////////////////////////
void DrawBitmap(HDC hdc,HBITMAP hbit, int x, int y, int width, int height,BOOL trans){ 
   if(!trans)DrawBitmap(hdc,hbit,x,y,width,height);
   else TransBlt(hdc,x,y,hbit,RGB(255,0,0));
   //TransparentBlt(hdc,x,y,width,height,memDC,0,0,width,height,RGB(0,0,0));
}

void DrawBitmap(HDC hdc,HBITMAP hbit, int x, int y, int width, int height){
   HDC memDC=CreateCompatibleDC(hdc);
   HBITMAP oldbit=(HBITMAP)SelectObject(memDC,hbit);
   BitBlt(hdc,x,y,width,height,memDC,0,0,SRCCOPY);
   //TransparentBlt(hdc,x,y,width,height,memDC,0,0,width,height,RGB(255,0,0));
   SelectObject(memDC,oldbit);
   DeleteDC(memDC);
}

void DrawBitmap(HDC hdc,int x,int y,HBITMAP hBit)
{
	HDC MemDC;
	HBITMAP OldBitmap;
	int bx,by;
	BITMAP bit;

	MemDC=CreateCompatibleDC(hdc);
	OldBitmap=(HBITMAP)SelectObject(MemDC, hBit);

	GetObject(hBit,sizeof(BITMAP),&bit);
	bx=bit.bmWidth;
	by=bit.bmHeight;

	BitBlt(hdc,x,y,bx,by,MemDC,0,0,SRCCOPY);

	SelectObject(MemDC,OldBitmap);
	DeleteDC(MemDC);
}

void TransBlt(HDC hdc, int x, int y, HBITMAP hbitmap, COLORREF clrMask)
{
	BITMAP bm;
	COLORREF cColor;
	HBITMAP bmAndBack, bmAndObject, bmAndMem, bmSave;
	HBITMAP bmBackOld, bmObjectOld, bmMemOld, bmSaveOld;
	HDC		hdcMem, hdcBack, hdcObject, hdcTemp, hdcSave;
	POINT	ptSize;

	hdcTemp = CreateCompatibleDC(hdc);
	SelectObject(hdcTemp, hbitmap);
	GetObject(hbitmap, sizeof(BITMAP), (LPSTR)&bm);
	ptSize.x = bm.bmWidth;
	ptSize.y = bm.bmHeight;
	DPtoLP(hdcTemp, &ptSize,1);

	hdcBack   = CreateCompatibleDC(hdc);
	hdcObject = CreateCompatibleDC(hdc);
	hdcMem    = CreateCompatibleDC(hdc);
	hdcSave   = CreateCompatibleDC(hdc);

	bmAndBack   = CreateBitmap(ptSize.x, ptSize.y, 1, 1, NULL);
	bmAndObject = CreateBitmap(ptSize.x, ptSize.y, 1, 1, NULL);
	bmAndMem    = CreateCompatibleBitmap(hdc, ptSize.x, ptSize.y);
	bmSave      = CreateCompatibleBitmap(hdc, ptSize.x, ptSize.y);

	bmBackOld   = (HBITMAP) SelectObject(hdcBack, bmAndBack);
	bmObjectOld = (HBITMAP) SelectObject(hdcObject, bmAndObject);
	bmMemOld    = (HBITMAP) SelectObject(hdcMem, bmAndMem);
	bmSaveOld   = (HBITMAP) SelectObject(hdcSave, bmSave);

	SetMapMode(hdcTemp, GetMapMode(hdc));

	BitBlt(hdcSave, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0, SRCCOPY);

	cColor = SetBkColor(hdcTemp, clrMask);

	BitBlt(hdcObject, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0, SRCCOPY);

	SetBkColor(hdcTemp, cColor);

	BitBlt(hdcBack, 0, 0, ptSize.x, ptSize.y, hdcObject, 0, 0, NOTSRCCOPY);
	BitBlt(hdcMem , 0, 0, ptSize.x, ptSize.y, hdc      , x, y, SRCCOPY);
	BitBlt(hdcMem , 0, 0, ptSize.x, ptSize.y, hdcObject, 0, 0, SRCAND);
	BitBlt(hdcTemp, 0, 0, ptSize.x, ptSize.y, hdcBack  , 0, 0, SRCAND);
	BitBlt(hdcMem , 0, 0, ptSize.x, ptSize.y, hdcTemp  , 0, 0, SRCPAINT);
	BitBlt(hdc    , x, y, ptSize.x, ptSize.y, hdcMem   , 0, 0, SRCCOPY);
	BitBlt(hdcTemp, 0, 0, ptSize.x, ptSize.y, hdcSave  , 0, 0, SRCCOPY);

	DeleteObject(SelectObject(hdcBack, bmBackOld));
	DeleteObject(SelectObject(hdcObject, bmObjectOld));
	DeleteObject(SelectObject(hdcMem, bmMemOld));
	DeleteObject(SelectObject(hdcSave, bmSaveOld));
	
	DeleteDC(hdcMem);
	DeleteDC(hdcBack);
	DeleteDC(hdcObject);
	DeleteDC(hdcSave);
	DeleteDC(hdcTemp);
}

////////////////////////////////////////////algorithms In Game ///////////////////////////////////

void make_enemies(){
     if(rand()%2==0)
     {
            for(int i=0;i<MAX_ENEMY;i++)
            {
                    if(enemies[i]->show==FALSE)
                    {
                           enemies[i]->x=(rand()%SIZE_BATX+rand()%SIZE_X)/2;
                           enemies[i]->y=(rand()%SIZE_BATY)/5;
                           enemies[i]->life=rand()%2;
                           enemies[i]->show=TRUE;
                           return;
                    }
            }
     }
     return;
}
     
void shoot(int x, int y, BOOL forward,int damage){
     int dy;     
     for(int i=0;i<MAX_BULLET;i++)
     {
             if(bullets[i]->show==FALSE)
             {
                     if(forward==TRUE) dy=-20;
                     else dy=20; 
                     bullets[i]->x=x+10;
                     bullets[i]->y=y+dy;
                     bullets[i]->forward=forward;
                     bullets[i]->show=TRUE;
                     bullets[i]->damage=damage;
                     
                     /*
                     if(sound==TRUE){
                          PlaySound(MAKEINTRESOURCE(IDR_BULLET),g_hinst,SND_RESOURCE|SND_ASYNC);
                     }
                     */
                     return;
             }
     }
     return;
}

void dropItem(int x, int y, int type){
     if(type>NITEMTYPES)return;
     for(int i=0;i<MAX_ITEM;i++)
     {
             if(items[i]->show==FALSE)
             {

                     items[i]->itemtype=type;
                     items[i]->x=x;
                     items[i]->y=y;
                     items[i]->show=TRUE;
                     items[i]->age=7000;
                     return;
             }
     }
     return;
}



void kill_entities()
{
           for(int i=0;i<MAX_ENEMY;i++)
            {
                    if(enemies[i]!=NULL)
                            delete enemies[i];
            }
            for(int i=0;i<MAX_BULLET;i++)
            {
                    if(bullets[i]!=NULL)
                            delete bullets[i];
            }
            for(int i=0;i<MAX_ITEM;i++)
            {
                    if(items[i]!=NULL)
                            delete items[i];
            }
            delete player;
}



int  checkbounce(int x, int y, int size_x, int size_y){
                   int bx,by;  
                   for(int i=0;i<MAX_BULLET;i++)
                   {
                           if(bullets[i]->show)
                           {
                                 bx=bullets[i]->x;
                                 by=bullets[i]->y;
                                 if(x<=bx&&bx<=x+size_x){
                                                           if(by>y&&y<=by&&by<=y+size_y)goto here;                  //미사일이 아래에                                                       
                                                           if(by<=y&&y<=by+SIZE_BMY&&by+SIZE_BMY<=y+size_y)goto here;                 //미사일이 위에 
                                                           continue;
                                                            here: bullets[i]->show=FALSE;
                                                                  return bullets[i]->damage;
                                 }
                                 
                           }
                   }
           return 0;
      }

int  checkbounceItem(int x, int y, int size_x, int size_y){
                   int ix,iy;  
                   for(int i=0;i<MAX_ITEM;i++)
                   {
                           if(items[i]->show)
                           {
                                 ix=items[i]->x;
                                 iy=items[i]->y;
                                 if(x<=ix&&ix<=x+size_x){
                                                           if(iy>y&&y<=iy&&iy<=y+size_y)goto here;                  //아이템이 아래에                                                       
                                                           if(iy<=y&&y<=iy+SIZE_BIY&&iy+SIZE_BIY<=y+size_y)goto here;                 //아이템이 위에 
                                                           continue;
                                                            here: items[i]->show=FALSE;
                                                                  return items[i]->itemtype;
                                 }
                                 
                           }
                   }
           return -1;
      }


/////////////////////////////////////////////소리///////////////////////////////////
void playBGM(int num)
{
     if(!Game.musicOn){
                       StopSound();
                       return;
     }
     char numchar = num+'0';
     char filename[6];
     filename[0]=numchar;
     filename[1]='.';
     filename[2]='m';
     filename[3]='p';
     filename[4]='3';
     filename[5]='\0';
     myPlaySound(filename);
}


char szCommand[256], szReturnStr[256]; 
void myPlaySound(char *filename)
{
     //우선 버퍼를 비워줍니다,
     mciSendString("stop mydev",szReturnStr,sizeof(szReturnStr),NULL);
     mciSendString("close mydev",szReturnStr,sizeof(szReturnStr),NULL);
     
     //filename에 입력했던 오디오파일 출력
     //ex)wsprintf(szCommand,"open %s alias mydev","./Sound/Gee.mp3");
     //이와 같이 경로 잡기
     
     wsprintf(szCommand,"open %s alias mydev",filename);
     mciSendString(szCommand, szReturnStr, sizeof(szReturnStr),NULL);
     mciSendString("play mydev repeat", szReturnStr, sizeof(szReturnStr),NULL);
}

void StopSound()
{
     mciSendString("stop mydev",szReturnStr, sizeof(szReturnStr),NULL);
     mciSendString("close mydev",szReturnStr, sizeof(szReturnStr),NULL);
}     

void mPlaySound(char* a, HINSTANCE g,unsigned int mode){
     if(sound){
               PlaySound(a,g,SND_RESOURCE|SND_ASYNC);
     }
}





/*
void OnTimer()

{

RECT crt;

HDC hdc,hMemDC;

HBITMAP OldBit,;

HPEN hPen,OldPen;

HBRUSH hBrush,OldBrush;

int i,ball;

 

GetClientRect(hWnd,&crt);

hdc=GetDC(hWnd);

 

if (hBit==NULL) {

    hBit=CreateCompatibleBitmap(hdc,crt.right,crt.bottom);

}

hMemDC=CreateCompatibleDC(hdc);

OldBit=(HBITMAP)SelectObject(hMemDC,hBit);

 

FillRect(hMemDC,&crt,GetSysColorBrush(COLOR_WINDOW));

 

hPen=CreatePen(PS_INSIDEFRAME,5,RGB(255,0,0));

OldPen=(HPEN)SelectObject(hMemDC,hPen);

hBrush=CreateSolidBrush(RGB(0,0,255));

OldBrush=(HBRUSH)SelectObject(hMemDC,hBrush);

DeleteObject(SelectObject(hMemDC,OldPen));

DeleteObject(SelectObject(hMemDC,OldBrush));

 

SelectObject(hMemDC,OldBit);

DeleteDC(hMemDC);

ReleaseDC(hWnd,hdc);

InvalidateRect(hWnd,NULL,FALSE);

}

*/

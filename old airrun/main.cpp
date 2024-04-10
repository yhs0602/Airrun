#include "main.h"
//PlaySound(MAKEINTRESOURCE(IDR_BULLET),g_hInst,SND_RESOURCE | SND_ASYNC);

bullet * bullets[MAX_BULLET];
enemy * enemies[MAX_ENEMY];
Player * player;

HWND hWnd;
HWND hButton; 

HINSTANCE g_hinst;

HPEN old;
HPEN whitepen;
HBRUSH bluebrush,whitebrush;

HBITMAP hbititem[NITEMTYPES];
HBITMAP hbitsurround[5];
HBITMAP hbitenemy;
HBITMAP hbitbullet,hbitnuclear;
HBITMAP hbitplayer,hbitexplosion;
//HBITMAP hbitcloud;

int running;
int score;
int surnumtodraw;
int enemynum,bulletnum;
//unsigned int cloud_x,cloud_y
unsigned int count;
BOOL sound;
BOOL stelse;
char scoretext[30];
RECT battlefield={0,0,SIZE_X,SIZE_Y-100};
RECT left={0,SIZE_Y-100,SIZE_BATX,SIZE_BATY};


/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
char szClassName[ ] = "WindowsApp";

int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nFunsterStil)

{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */
    g_hinst=hThisInstance;
    
    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                       /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default color as the background of the window */
    wincl.hbrBackground =(HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           "iris",              /* Title Text */
           SWP_NOSIZE,          /* NOSIZE window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           SIZE_X,                 /* The programs width */
           SIZE_Y,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nFunsterStil);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;


    switch (message)                  /* handle the messages */
    {
        case WM_DESTROY:
            KillTimer(hwnd,1);
            for(int i=0;i<5;i++)
            {
                    DeleteObject(hbitsurround[i]);
            }
            DeleteObject(hbitbullet);
            DeleteObject(hbitenemy);
            DeleteObject(hbitplayer);
            DeleteObject(hbitnuclear);
            DeleteObject(hbitexplosion);
            //DeleteObject(hbitcloud);
            kill_entities();
            DeleteObject(whitepen);
            DeleteObject(bluebrush);
            DeleteObject(whitebrush);
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
            
        case WM_CREATE:
             hWnd=hwnd;
             srand(time(NULL));
             bluebrush=CreateSolidBrush(RGB(0,0,0xff));
             whitebrush=CreateSolidBrush(RGB(0xff,0xff,0xff));
             whitepen=CreatePen(PS_SOLID,2,RGB(0xFF,0xff,0xff));
             //for(int i=0;i<5;i++)
             //{
             //       hbitsurround[i]=LoadBitmap(g_hinst,MAKEINTRESOURCE(IDB_BITSUR1+i));
             //}
             
             //hbitcloud=LoadBitmap(g_hinst,MAKEINTRESOURCE(IDB_BITCLOUD));
             hbitenemy=LoadBitmap(g_hinst,MAKEINTRESOURCE(IDB_BITENEMY));
             hbitbullet=LoadBitmap(g_hinst,MAKEINTRESOURCE(IDB_BITBULLET));
             hbitnuclear=LoadBitmap(g_hinst,MAKEINTRESOURCE(IDB_BITNUCLEAR));
             hbitplayer=LoadBitmap(g_hinst,MAKEINTRESOURCE(IDB_BITPLAYER));
             hbitexplosion=LoadBitmap(g_hinst,MAKEINTRESOURCE(IDB_BITEXPLOSION));;
             if(hButton==NULL){
                     hButton=CreateWindow(TEXT("button"),TEXT("start"),WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,SIZE_X/2-50,SIZE_Y*3/4,100,50,hWnd,(HMENU)IDC_BUTTONSTART,g_hinst,NULL);
             }
             
             for(int i=0;i<MAX_BULLET;i++){
                  bullets[i]=new bullet();
             }
             for(int i=0;i<MAX_ENEMY;i++){
                  enemies[i]=new enemy();
             }
             player = new Player();
             SetTimer(hwnd,1,15,NULL);

             break;
             
        case WM_KEYDOWN:
             switch(wParam)
             {
                 case 'S':
                      
                      start();    /*Running*/
                      return 0;
                 case 'M':
                      sound=!sound;
                      return 0;
                      
                 case VK_LEFT:
                 case VK_RIGHT:
                 case VK_UP:
                 case VK_DOWN:
                      if(running==1)
                      {
                             player->move(wParam);
                             return 0;
                      }
                      break;
                 case VK_SPACE:
                      if(running==1)
                      {
                             player->bshoot =!player->bshoot;
                             return 0;
                      }
                      break;
                 case 'N':
                      if(running==1)
                      {
                             player->nuclear();
                             return 0;
                      }
                      break;
                 case 'Q':
                             stelse=!stelse;
                             return 0;
                      break;
                 case VK_ESCAPE:
                      if(menu())
                      {
                                DestroyWindow(hwnd);
                                return 0;
                      }
                      break;
             }
             if(running!=1)
             {
                      if(running==2)   /*game Over*/
                      {
                             if(hButton==NULL){
                                      hButton=CreateWindow(TEXT("button"),TEXT("start"),WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,250,600,100,50,hWnd,(HMENU)IDC_BUTTONSTART,g_hinst,NULL);
                             }
                             return 0;
                      }
             }
             return 0;
             
        case WM_COMMAND:     
                 switch(LOWORD(wParam))
                 {
                       case IDC_BUTTONSTART:
                            start();
                            DestroyWindow(hButton);
                            hButton=NULL;
                            break;
                       
                 }
                 return 0;
         case WM_TIMER:
              if(running==1){
                     //surnumtodraw++;
                     //if(surnumtodraw>4)surnumtodraw=0;
                     if(count%4==0){
                          InvalidateRect(hwnd,NULL,FALSE);
                     }
                     if(count%5==0){
                           for(int i=0;i<MAX_ENEMY;i++)
                           {
                                   enemies[i]->check();
                           }
                           player->check();

                     }
                     if(count%7==0){
                           for(int i=0;i<MAX_ENEMY;i++)
                           {
                                    enemies[i]->move();
                           }
                           player->work();
                     }
                     
                     if(count%70==0){               
                                    make_enemies();
                                    /*cloud_y++;
                                    cloud_x+=rand()%10;
                                    if(cloud_y>SIZE_BATY)cloud_y=0;
                                    if(cloud_x>SIZE_BATX)cloud_x=0;
                                    */
                     }
                     
                     for(int i=0;i<MAX_BULLET;i++)
                     {
                                   bullets[i]->move();
                     }



                     //if(count%500==0)PlaySound(NULL,NULL,NULL);

                     return 0;
              }
               return 0;
        case WM_PAINT:
               hdc=BeginPaint(hwnd,&ps);
               //DrawBitmap(hbitsurround[surnumtodraw],0,0,600,700);
               old=(HPEN)SelectObject(hdc,whitepen);
               TextOut(hdc,0,SIZE_Y-100,scoretext,30);
               SelectObject(hdc,bluebrush);
               FillRect(hdc,&battlefield,bluebrush);
               FillRect(hdc,&left,whitebrush);
               SelectObject(hdc,old);
               //DrawBitmap(hbitcloud,cloud_x,cloud_y,SIZE_BCX,SIZE_BCY);
               if(running==1)
               {
                     if(stelse==FALSE){
                                   for(int i=0;i<MAX_ENEMY;i++)
                                   {
                                           enemies[i]->draw();
                                   }
                                   player->draw();
                     }
                     for(int i=0;i<MAX_BULLET;i++)
                     {
                             bullets[i]->draw();
                     }

               }else if(running==3){
                     TextOut(hdc,SIZE_X/2-4,(SIZE_Y-100)/2,"game over",9);
               }
               EndPaint(hwnd,&ps);
               return 0;
                 
                                                
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}

int menu(){
    int t=running;
    running=4;
    int end=MessageBox(hWnd, TEXT("종료할까요?"),TEXT("종료"),MB_YESNO|MB_ICONQUESTION);
    if(end==IDYES)
                  return 1;
    running=t; 
    return 0;   
}

void start(){
     running=1;
     score=0;
     surnumtodraw=0;
     enemynum=bulletnum=0;
     //cloud_x=cloud_y=
     count=0;
     sound=FALSE;
     stelse=FALSE;
     for(int i=0;i<MAX_ENEMY;i++)
     {
             if(enemies[i]!=NULL){
                              enemies[i]->show=FALSE;
                              enemies[i]->x=0;
                              enemies[i]->y=0;
                              enemies[i]->life=0;
                              
             }
     }
     for(int i=0;i<MAX_BULLET;i++)
     {
             if(bullets[i]!=NULL){
                             bullets[i]->show=FALSE;
                             bullets[i]->x=0;
                             bullets[i]->y=0;
                             
             }                      
     }
       player->x=100;
       player->y=600;
       player->life=5;
       player->left_nuclear=3;
       player->nucleartimercount=0;
       player->bshoot=TRUE;
       player->bshow=TRUE;
       player->bnuclear=FALSE;
       player->pc=0;
      

     sprintf(scoretext,"score:%d             life:%d \0",score,5);
     return;
}

void DrawBitmap(HBITMAP hbit, int x, int y, int width, int height){
   HDC hdc=GetDC(hWnd);
   HDC memDC=CreateCompatibleDC(hdc);
   HBITMAP oldbit=(HBITMAP)SelectObject(memDC,hbit);
   //BitBlt(hdc,x,y,width,height,memDC,0,0,SRCCOPY);
   TransparentBlt(hdc,x,y,width,height,memDC,0,0,width,height,RGB(0,0,0));
   SelectObject(memDC,oldbit);
   DeleteDC(memDC);
   ReleaseDC(hWnd,hdc);
}

void make_enemies(){
     if(rand()%100==0)
     {
            for(int i=0;i<MAX_ENEMY;i++)
            {
                    if(enemies[i]->show==FALSE)
                    {
                           enemies[i]->x=(rand()%SIZE_BATX+rand()%SIZE_X)/2;
                           enemies[i]->y=(rand()%SIZE_BATY)/5;
                           enemies[i]->life=rand()%10+5;
                           enemies[i]->show=TRUE;
                           return;
                    }
            }
     }
     return;
}
     
void shoot(int x, int y, BOOL forward){
     int dy;
     static int a=0;     
     for(int i=0;i<MAX_BULLET;i++)
     {
             if(bullets[i]->show==FALSE)
             {
                     if(forward==TRUE) dy=-30;
                     else dy=30; 
                     bullets[i]->x=x;
                     bullets[i]->y=y+dy;
                     bullets[i]->forward=forward;
                     bullets[i]->show=TRUE;
                     a++;
                     if(sound==TRUE&&a%4==0){
                          PlaySound(MAKEINTRESOURCE(IDR_BULLET),g_hinst,SND_RESOURCE  /*|SND_ASYNC*/);
                     }
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
            delete player;
}

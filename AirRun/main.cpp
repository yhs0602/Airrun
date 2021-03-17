#include "main.h"
//PlaySound(MAKEINTRESOURCE(IDR_BULLET),g_hInst,SND_RESOURCE | SND_ASYNC);

Bullet * bullets[MAX_BULLET];
Enemy * enemies[MAX_ENEMY];
Item * items[MAX_ITEM];
Player * player;
//World * theworld;

HWND hWnd;
HWND hButton; 
RECT clientrect;
int SIZE_X,SIZE_Y,SIZE_BATX,SIZE_BATY;

HINSTANCE g_hinst;

HPEN old;
HPEN whitepen;
HBRUSH bluebrush,whitebrush;

HBITMAP hbititem[NITEMTYPES];
HBITMAP hbitsurround[5];
HBITMAP hbitenemy;
HBITMAP hbitbullet[MAX_BULLETDAMAGE],hbitnuclear;
HBITMAP hbitplayer,hbitexplosion;

char musics[64][10];
//HBITMAP hbitcloud;

int running;
int score;
int surnumtodraw;
int enemynum,bulletnum;
//unsigned int cloud_x,cloud_y
unsigned int count;
BOOL sound;
BOOL stelse;
char scoretext[128];
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
    SIZE_X= 800;
    SIZE_Y= 900;
    
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
           "AirRun",              /* Title Text */
           WS_OVERLAPPEDWINDOW,          /*  window */
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
    HDC hdc,hMemDC;
    PAINTSTRUCT ps;
    int i=0;
    static HBITMAP doublebuffer=NULL;
    HBITMAP OldBit;
    FILE *setups;
    
    switch (message)                  /* handle the messages */
    {
        case WM_DESTROY:
			StopSound();
            KillTimer(hwnd,1);
            //for(int i=0;i<5;i++)
            //{
            //        DeleteObject(hbitsurround[i]);
            //}
            for(int i=0;i<=NITEMTYPES;i++)
            {
                    DeleteObject(hbititem[i]);
            }
            for(int i=0;i<MAX_BULLETDAMAGE;i++)
            {
                    DeleteObject(hbitbullet[i]);
            }
            
            DeleteObject(hbitbullet);
            DeleteObject(hbitenemy);
            DeleteObject(hbitplayer);
            DeleteObject(hbitnuclear);
            DeleteObject(hbitexplosion);
            //DeleteObject(hbitcloud);
            kill_entities();
            //delete theworld;
            DeleteObject(whitepen);
            DeleteObject(bluebrush);
            DeleteObject(whitebrush);
            
            PostQuitMessage(0);       /* send a WM_QUIT to the message queue */
            break;
            
        case WM_CREATE:
             sound=FALSE;
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
             
			 for(int i=0;i<=NITEMTYPES;i++){
					hbititem[i]=LoadBitmap(g_hinst,MAKEINTRESOURCE(IDB_BITITEM1+i));
			}
			 for(int i=0;i<MAX_BULLETDAMAGE;i++){
					hbitbullet[i]=LoadBitmap(g_hinst,MAKEINTRESOURCE(IDB_BITBULLET1+i));
			}
			
             hbitenemy=LoadBitmap(g_hinst,MAKEINTRESOURCE(IDB_BITENEMY));
             //hbitbullet=LoadBitmap(g_hinst,MAKEINTRESOURCE(IDB_BITBULLET));
             hbitnuclear=LoadBitmap(g_hinst,MAKEINTRESOURCE(IDB_BITNUCLEAR));
             hbitplayer=LoadBitmap(g_hinst,MAKEINTRESOURCE(IDB_BITPLAYER));
             hbitexplosion=LoadBitmap(g_hinst,MAKEINTRESOURCE(IDB_BITEXPLOSION));
             
             setups=fopen("setups.txt","rt");
             for(i=0;i<10;i++){
                               fgets(musics[i],sizeof(musics[i]),setups);
             }
             fclose(setups);
             
             if(hButton==NULL){
                     hButton=CreateWindow(TEXT("button"),TEXT("start"),WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,SIZE_X/2-50,SIZE_Y*3/4,100,50,hWnd,(HMENU)IDC_BUTTONSTART,g_hinst,NULL);
             }
             
             for(int i=0;i<MAX_BULLET;i++){
                  bullets[i]=new Bullet();
             }
             for(int i=0;i<MAX_ITEM;i++){
                  items[i]=new Item(0,0,0);
             }
             for(int i=0;i<MAX_ENEMY;i++){
                  enemies[i]=new Enemy();
             }
             player = new Player();
             //theworld=new World();
             SetTimer(hwnd,1,10,NULL);

             break;
             
        case WM_KEYDOWN:
             switch(wParam)
             {
                 case 'S':
                      start();    /*Running*/
                      return 0;
                 case 'M':
                      sound=!sound;
                      sprintf(scoretext,"score:%d       life:%d 이동:방향키, M:소리 토글 Esc:종료 1:... 2:... 3:... 4:... sound:%s",score,5,sound? "true":"false");
                      if(!sound) StopSound();
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
                             return 0;
                      }
                      break;
                 case 'Q':
                             stelse=!stelse;
                             return 0;
                      break;
                      
                 case '1':
                      if(sound){
                                myPlaySound("1.mp3");
                      }else{
                            StopSound();
                      }
                      break;
                 
                 case '2':
                      if(sound){
                                myPlaySound("2.mp3");
                      }else{
                            StopSound();
                      }
                      break;
                 case '3':
                      if(sound){
                                myPlaySound("3.mp3");
                      }else{
                            StopSound();
                      }
                      break;
                 case '4':
                      if(sound){
                                myPlaySound("4.mp3");
                      }else{
                            StopSound();
                      }
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
                 
         case WM_SIZE:
                   GetClientRect(hwnd,&clientrect);
                   SIZE_X=clientrect.right;
                   SIZE_Y=clientrect.bottom; 
                   battlefield.left=clientrect.left;
                   battlefield.top=clientrect.top;
                   battlefield.right=clientrect.right;
                   battlefield.bottom=clientrect.bottom-100;
                   left.top=battlefield.bottom;
                   left.left=clientrect.left;
                   left.right=clientrect.right;
                   left.bottom=clientrect.bottom;
                   SIZE_BATX=SIZE_X;
                   SIZE_BATY=SIZE_Y-100;

                   return 0; 
         case WM_TIMER:
              count++;
              if(running==1){
                     if(count%2==0){
                     for(int i=0;i<MAX_BULLET;i++)
                          {
                                   bullets[i]->move();
                          }
                          hdc=GetDC(hwnd);
                          if (doublebuffer==NULL) {
                             doublebuffer=CreateCompatibleBitmap(hdc,SIZE_X,SIZE_Y);
                          }
                          hMemDC=CreateCompatibleDC(hdc);
                          OldBit=(HBITMAP)SelectObject(hMemDC,doublebuffer);
                          FillRect(hMemDC,&battlefield,bluebrush);
                          FillRect(hMemDC,&left,whitebrush);
                          TextOut(hMemDC,0,SIZE_Y-100,scoretext,128);
                          if(running==1)
                          {
                                   if(stelse==FALSE){
                                   for(int i=0;i<MAX_ENEMY;i++)
                                   {
                                           enemies[i]->draw(hMemDC);
                                   }
                                   player->draw(hMemDC);
                          }
                          for(int i=0;i<MAX_BULLET;i++)
                          {
                             bullets[i]->draw(hMemDC);
                          }
                          for(int i=0;i<MAX_ITEM;i++)
                          {
							if(items[i]->show)
                             //DrawBitmap(hbititem[items[i]->itemtype],items[i]->x,items[i]->y,SIZE_BIX,SIZE_BIY,TRUE);
                             items[i]->draw(hMemDC);
                          }
					               //for(int i=0;i<MAX_ITEM;i++)
                                   //{
                                   //        theworld->itemlist[i]->draw();
                                   //}
                          }else if(running==3){
                                TextOut(hMemDC,SIZE_X/2-4,(SIZE_Y-100)/2,"game over",9);
                          }
                          SelectObject(hMemDC,OldBit);
                          DeleteDC(hMemDC);
                          ReleaseDC(hWnd,hdc);         
                          InvalidateRect(hwnd,NULL,FALSE);
                     }
                     if(count%4==2){
                           for(int i=0;i<MAX_ENEMY;i++)
                           {
                                   enemies[i]->check();
                           }
                           if(player->check()==3){
                                            start();    /*Running*/
                                            return 0;
                           }
                     }
                     if(count%4==0){               
                           for(int i=0;i<MAX_ENEMY;i++)
                           {
                                          enemies[i]->move();
                           }
                           for(int i=0;i<MAX_ITEM;i++)
                           {
								items[i]->update();
						   }
                           player->work();
                     }
                     
                     if(count%10==0){               
                                    make_enemies();
                     }
                     return 0;
              }
               return 0;
        case WM_PAINT:
		     hdc=BeginPaint(hWnd, &ps);
		     DrawBitmap(hdc,0,0,doublebuffer);
		     EndPaint(hWnd, &ps);
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
     //sound=FALSE;
     stelse=FALSE;
     for(int i=0;i<MAX_ENEMY;i++)
     {
             if(enemies[i]!=NULL){
                              enemies[i]->Init();
             }
     }
     for(int i=0;i<MAX_BULLET;i++)
     {
             if(bullets[i]!=NULL){
                             bullets[i]->Init();
             }                      
     }
       player->Init();

     sprintf(scoretext,"score:%d       life:%d 이동:방향키, M:소리 Q:스텔스 Esc:종료 1:...  2:... 3:... 4:... sound:%s",score,5,sound? "true":"false");
     return;
}

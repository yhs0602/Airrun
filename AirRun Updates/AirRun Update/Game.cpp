

class Game{
      Saver *saver;
      BOOLEAN musicOn;
      HWND hwndMain;
      HBITMAP doublebuffer;
      unsigned long tick;
      int sizeX,sizeY;
      HDC memDC, HDC hdc;
      World *worldObj;
      Player *thePlayer;
      int Game::Size(int x,int y){
          sizeX=x,sizeY=y;
      }
      Game(HWND hwnd){
                hwndMain=hwnd;
                tick=0;
                sizeX=sizeY=400;
                worldObj=new World(this);
                saver= new Saver(this);
                musicOn=0;
                saver.LoadAll();
                thePlayer=new Player();
                
      }
             
};

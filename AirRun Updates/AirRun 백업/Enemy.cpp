#include "main.h"
Enemy::Enemy(){
               x=0;
               y=0;
               life=5;
               show=FALSE;
               explosioncount=0;
}
 
void Enemy::Init(){
               x=0;
               y=0;
               life=5;
               show=FALSE;
               explosioncount=0;
               //world=theworld;
}


void Enemy::move(){
     if(show)
     {
             x+=(rand()%5)-2;
             y+=rand()%5;
             if(x<0)x=0;
             if(y<0)y=0;
             if(x>SIZE_BATX)x=SIZE_BATX;
             if(y>SIZE_BATY)show=FALSE;
             if(rand()%50==0)shoot(x,y,FALSE,1);
             //if(rand()%40==0)shoot(x,y,TRUE);
     }
}

void Enemy::draw(HDC hdc){
     if(show)
     {
             DrawBitmap(hdc,hbitenemy,x,y,20,20,TRUE);
           
     }else if(explosioncount<100)
     {
           DrawBitmap(hdc,hbitexplosion,x,y,20,20,TRUE);
           explosioncount++;
     }
}

  void Enemy::check(){
		int damage;
           if(show)
           {
                   int sx=x-SIZE_BEX,sy=y,ex=x,ey=y+SIZE_BEY,bx,by; 
                   if(damage=checkbounce(x,y,SIZE_BEX,SIZE_BEY)) {
                                        life-=damage;
                                        if(life<1)
                                        {
                                              explosioncount=0;
                                              score+=100;
                                              sprintf(scoretext,"score:%d       life:%d 이동:방향키, M:소리 Q:스텔스 Esc:종료 숫자: 배경음악 sound:%s",score,player->life,sound? "true":"false");
                                              mPlaySound(MAKEINTRESOURCE(IDR_EXPLOSION),g_hinst,SND_RESOURCE);
                                              show=FALSE;
                                              if(rand()%20==0){
													dropItem(x,y,rand()%2);
											 }
											 
                                        }
                                        
                   }
                   
           }
                                 
      }
void Enemy::work(){
     if(show)
     {
             if(rand()%40==0)shoot(x,y,FALSE,1);
             //if(rand()%40==0)shoot(x,y,TRUE);

     }
}

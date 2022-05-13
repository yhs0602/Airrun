#include "main.h"
#define BULLET_VELOCITY 30
void Bullet::move(){
           if(show)
           {
                   if(forward==TRUE)
                   {
                         y-=BULLET_VELOCITY;
                   }else{
                         y+=BULLET_VELOCITY;
                   }
                   if(y>SIZE_BATY-SIZE_BMY||y<0)show=FALSE;
           }
}
      
void Bullet::draw(HDC hdc){
           if(show)
           {
                   DrawBitmap(hdc,hbitbullet[damage-1],x,y,SIZE_BMX, SIZE_BMY,TRUE);
           }
}
      
Bullet::Bullet(){
	Init();                           
}                 

void Bullet::Init(){
                   x=0;
                   y=0;
                   show=FALSE;
                   damage=1;
                   //world=theworld;    
}

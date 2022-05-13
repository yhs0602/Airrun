#include "main.h"
class Item{
      static Item* 
      void Item::update(){
           if(show)
           {
                   if(age>0)
                   {
                         age--;
                   }else{
                         show=FALSE;
                   }
                   y+=5;
                   if(y>SIZE_Y)show=FALSE;    
           }
      }
      void Item::draw(HDC hdc){
           if(show)
           {
                   DrawBitmap(hdc,hbititem[itemtype],x,y,SIZE_BIX,SIZE_BIY,TRUE);
           }
      }
      
      Item::Item(int ax, int ay, int type){
                   this->x=ax;
                   this->y=ay;
                   this->itemtype=type;
                   age=0;
                   show=FALSE;
                   //world=theworld;
      }
      
void Item::OnCollide(Player *p){
	mPlaySound(MAKEINTRESOURCE(IDR_ITEM),g_hinst,SND_RESOURCE);
	switch(itemtype){
		case 0:
			p->life++;
			sprintf(scoretext,"score:%d       life:%d 이동:방향키, M:소리 Q:스텔스 Esc:종료 1:허경영 2.이명박 3.박근혜 4.김정은 sound:%s",score,p->life,sound? "true":"false");
			break;
		case 1:
			p->damagelevel++;
			if(p->damagelevel>MAX_BULLETDAMAGE){
				p->damagelevel=MAX_BULLETDAMAGE;
				p->life++;
			}
			break;
		default:
			break;
	}
	return;
}

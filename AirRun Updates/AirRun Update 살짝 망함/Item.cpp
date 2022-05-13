#include "main.h"
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
			sprintf(scoretext,"score:%d       life:%d �̵�:����Ű, M:�Ҹ� Q:���ڽ� Esc:���� 1:��濵 2.�̸�� 3.�ڱ��� 4.������ sound:%s",score,p->life,sound? "true":"false");
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

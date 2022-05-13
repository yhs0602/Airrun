#include "main.h"
      
Player::Player(){
	Init();
}

void Player::Init(){
       x=SIZE_BATX/2;
       y=SIZE_BATY-100;
       life=5;
       left_nuclear=3;
       nucleartimercount=0;
       bshoot=TRUE;
       bshow=TRUE;
       bnuclear=FALSE;
       pc=0;
       damagelevel=1;
       //world=theworld;
}    
      
void Player::move(int key){
	int Citem;
           switch(key)
           {
                case VK_UP:
                     y-=19;
                     break;
                case VK_DOWN:
                     y+=19;
                     break;
                case VK_RIGHT:
                     x+=19;
                     break;
                case VK_LEFT:
                     x-=19;
                     break;
           }
           if(x<0)x=10;
           if(y<0)y=10;
           if(x>SIZE_BATX)x=SIZE_BATX-10;
           if(y>SIZE_BATY)y=SIZE_BATY-10;
}
             
      int Player::check(){
           pc++;
           if(pc>500)
           {
                    pc=0;
                    bshow=TRUE;
           }
           if(bshow)
           {
				int Citem;
				if(Citem=checkbounceItem(x,y,SIZE_BPX,SIZE_BPY)!=-1)items[Citem]->OnCollide(this);
                   int sx=x-SIZE_BPX,sy=y,ex=x,ey=y+SIZE_BPY,bx,by; 
                   if(checkbounce(x,y,SIZE_BPX,SIZE_BPY)) {
                                        life--;
                                        if(life<1)
                                        {
                                              //DrawBitmap(hbitexplosion,sx,sy,20,20,FALSE);
                                              running=3;
                                              if(MessageBox(hWnd, TEXT("종료할까요?"),TEXT("종료"),MB_YESNO|MB_ICONQUESTION)==IDYES){
                                                                  DestroyWindow(hWnd);
                                              }else{
                                                    return 3;
                                              }
                                              return 1;
                                        }
                                        bshow=FALSE;
                                        left_nuclear=3;
                                                                                      
                                        mPlaySound(MAKEINTRESOURCE(IDR_OUCH),g_hinst,SND_RESOURCE|SND_ASYNC);
                                        sprintf(scoretext,"score:%d       life:%d 이동:방향키, M:소리 Q:스텔스 Esc:종료 1:허경영 2.이명박 3.박근혜 4.김정은 sound:%s",score,life,sound? "true":"false");

                                        return 0;
                   }
                   
           }
                                 
      }
      
      void Player::nuclear(){
           if(left_nuclear>0)
           {
                 nucleartimercount=500;
                 left_nuclear--;
                 if(left_nuclear<0)left_nuclear=0;
                 bnuclear= TRUE;
           }
      }
      
      void Player::draw(HDC hdc){
           DrawBitmap(hdc,hbitplayer,x,y,20,20,TRUE);
      }
      
      void Player::work(){
           if(bnuclear){
                       nucleartimercount--;
                       if(nucleartimercount<0)bnuclear=FALSE;
                       //DrawBitmap(hbitnuclear,x-10,0,20,SIZE_Y,FALSE);
           }
           bshow=TRUE;
           if(bshoot)
           {
                     shoot(x,y,TRUE,damagelevel);
           /* DONE (#1#): 이런 Player가 총도 안쏘고 무적이네 */
           }
      }


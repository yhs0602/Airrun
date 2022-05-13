#include "main.h"
#define MAX_ENTITY 4096
#define MAX_ITEM 256
class World{
      int sizeX,sizeY,sizeZ;
      Player *player;
      Game *game;
      Entity *entityList[MAX_ENTITY];
      Item *itemList[MAX_ITEM];
      int spawnEntityInWorld(Entity entity,int x,int y,int z);
      int onUpdate(unsigned long tick);
      World(Game *g){
                 game=g;
                 player=g->thePlayer();
                 
      }
}




int World::spawnItemInWorld(int x, int y, int type){
/*    if(itemindex<MAX_ITEM && itemlist[itemindex]==NULL){
         itemlist[itemindex]=new Item(x,y,type);
         itemlist[itemindex]->age=7000;
         itemlist[itemindex]->show=TRUE;
         itemindex++;
         
    }
*/    return type;
}

int World::spawnEntityInWorld(int x, int y, int type){
	
    return type;
}

int World::spawnBulletInWorld(int x, int y, int type){
    return type;
}

World::World(){
/*    itemindex=0;
	for(int i=0;i<MAX_BULLET;i++){
            bullets[i]=new Bullet();
    }
    for(int i=0;i<MAX_ENEMY;i++){
            enemies[i]=new Enemy();
    }
    
	player = new Player();
*/}

World::~World(){
/*    itemindex=0;    
    for(int i=0;i<MAX_ITEM;i++){
            if(itemlist[i]!=NULL){
                                  delete itemlist[i];
                                  itemlist[i]=NULL;
            }
    }
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
*/}

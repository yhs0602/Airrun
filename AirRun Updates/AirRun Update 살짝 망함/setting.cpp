#include "main.h"

int LoadSetting(Setting *set)
{
    FILE *init;
    int i;
    init=fopen("res\\init.txt","rt");
    if(init==NULL)
    {
                  MessageBox(hWnd, TEXT("초기화 파일인 \'init.txt\'를 열 수 없습니다!!"),TEXT("FATAL ERROR"),MB_YESNO);
                  return -1;
    }
    for(i=0;i<9;i++)
    {
                     if(fgets((set->musicNames[FILENAMELEN*i]),FILENAMELEN+1,init)==NULL)
                     {
                                                                        MessageBox(hWnd, TEXT("BGM명을 바르게 입력하였는지 확인"),TEXT("FATAL ERROR"),MB_YESNO);
                                                                        return -1;
                     }                                                                      
    }
    if(fgets(set->playerBitName,FILENAMELEN,init)==NULL){
                                                  MessageBox(hWnd, TEXT("사용자 비트맵명을 바르게 입력하였는지 확인"),TEXT("FATAL ERROR"),MB_YESNO);
                                                  return -1;
    }
    if(fgets(set->enemyBitName,FILENAMELEN,init)==NULL){
                                                       MessageBox(hWnd, TEXT("적군 비트맵명을 바르게 입력하였는지 확인"),TEXT("FATAL ERROR"),MB_YESNO);
                                                       return -1;
    }
    if(fgets(set->explosionBitName,FILENAMELEN,init)==NULL){
                                                       MessageBox(hWnd, TEXT("폭발 비트맵명을 바르게 입력하였는지 확인"),TEXT("FATAL ERROR"),MB_YESNO);
                                                       return -1;
    }
    for(i=0;i<10;i++)
    {
                     if(fgets(set->bulletBitNames[FILENAMELEN*i],FILENAMELEN,init)==NULL)
                     {
                                                                        MessageBox(hWnd, TEXT("총알 비트맵명을 바르게 입력하였는지 확인"),TEXT("FATAL ERROR"),MB_YESNO);
                                                                        return -1;
                     }                                                                      
    }
    for(i=0;i<2;i++)
    {
                     if(fgets(set->itemBitNames[FILENAMELEN*i],FILENAMELEN,init)==NULL)
                     {
                                                                        MessageBox(hWnd, TEXT("아이템 비트맵명을 바르게 입력하였는지 확인"),TEXT("FATAL ERROR"),MB_YESNO);
                                                                        return -1;
                     }                                                                      
    }
    
    strcpy(set->initFileName,"res\\init.txt");
    fclose(init);
    MessageBox(hWnd, set->musicNames[0],TEXT("Check"),MB_YESNO); 
    MessageBox(hWnd, set->musicNames[1],TEXT("Check"),MB_YESNO); 
    deleteNewLines(set);
    MessageBox(hWnd, set->bulletBitNames[0],TEXT("Check"),MB_YESNO);
    MessageBox(hWnd, set->itemBitNames[0],TEXT("Check"),MB_YESNO);
    MessageBox(hWnd, set->musicNames[0],TEXT("Check"),MB_YESNO);    
    return 0;
}

//개행이 문제로다 

void deleteNewLines(Setting *set){
     int i;
     for(i=0;i<9;i++)
    {
                     deleteNewLinesSub(set->musicNames[i],TRUE);                                         
    }
    deleteNewLinesSub(set->playerBitName,FALSE);
    deleteNewLinesSub(set->enemyBitName,FALSE);
    deleteNewLinesSub(set->explosionBitName,FALSE);
    for(i=0;i<BULLETLEVELS;i++)
    {
                     deleteNewLinesSub(set->bulletBitNames[i],TRUE);                               
    }
    for(i=0;i<ITEMKINDS;i++)
    {
                     deleteNewLinesSub(set->itemBitNames[i],TRUE);                       
    }
}

void deleteNewLinesSub(char * str,BOOL patch)
{
     int i=0;
     for(;str[i]!='\n';i++);
     str[i]='\0';
     //int len= strlen(str);
     //str[len-(patch?0:1)]='\0';     
}

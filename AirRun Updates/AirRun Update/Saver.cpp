class Saver{
      FILE *worldInputStream,*worldOutputStream;
      FILE *settingInputStream,*settingOutputStream;
      Game *game;
      char worldFileName[64];
      char settingFileName[64];
      //Constructor
      Saver(Game *g,char *worldFileN,char *settingFileN){
                 strncpy(worldFileName,worldFileN,64);
                 strncpy(settingFileName,settingFileN,64);
                 game=g;
      }
      //saves all data to file
      public void SaveAll(){
             SaveWorld();
             SaveSetting();
      }
      //save all world data
      public void SaveWorld(){
             worldOutputStream=fopen(worldFileName,"wb");
             //TODO:save player,entity,item data
             fclose(worldOutputStream);
      }
      //save settings
      public void SaveSetting(){
             settingOutputStream=fopen(settingFileName,"wb");
             //TODO:save settings
             fclose(settingOutputStream);
      }
      //Load all data from file
      public void LoadAll(){
             LoadWorld();
             LoadSetting();
      }
      //Load all world data
      public void LoadWorld(){
             worldInputStream=fopen(worldFileName,"rb");
             //TODO:load world data
             fclose(worldInputStream);
      }
      //Load settings
      public void LoadSetting(){
             settingInputStream=fopen(settingFileName,"rb");
             //TODO:load settings
             fclose(settingInputStream);
      }
      
}
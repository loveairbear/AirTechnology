/*
void playmusic(char file[]){
  p.close();
  p.begin("madplay");
  
  if(strlen(file)>2){
  char* path =(char*)malloc(17 + strlen(file)+1+4); 
  strcpy(path, "/mnt/sda1/Sounds/"); 
  strcat(path, file); 
  strcat(path, ".mp3");
    p.addParameter(path);
    Serial.println(path);
    p.addParameter("-A-8");
    free(path);
    p.run();
  }
  else{
    char song[3];
   char* path =(char*)malloc(16+3+1+4); 
  strcpy(path, "/mnt/sda1/Songs/"); 
   strcat(path, file); 
   strcat(path, ".mp3"); 
   p.addParameter(path);
  Serial.println(path); 
   //p.addParameter("--replay-gain=audiophile"); 
   p.addParameter("-A-23"); 
   
   free(path); 
   p.runAsynchronously(); 

  }
}//end function
*/



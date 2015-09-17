
void playmusic(char file[]){
  p.begin("madplay");
  
  if(strlen(file)>2){
  char* path =(char*)malloc(17 + strlen(file)+1+4); /* make space for the new string (should check the return value ...) */
  strcpy(path, "/mnt/sda1/Sounds/"); /* copy name into the new var, used strncpy to combat buffer overflow*/
  strcat(path, file); /* add the extension */
  strcat(path, ".mp3");
    p.addParameter(path);
    Serial.println(path);
    p.addParameter("-A-8");
    free(path);
    p.run();
  }
  else{
    char song[3];
   char* path =(char*)malloc(16+3+1+4); /* make space for the new string (should check the return value ...) */ 
  strcpy(path, "/mnt/sda1/Songs/"); /* copy name into the new var, used strncpy to combat buffer overflow*/ 
   strcat(path, file); /* add the extension */ 
   strcat(path, ".mp3"); 
   p.addParameter(path);
  Serial.println(path); 
   //p.addParameter("--replay-gain=audiophile"); 
   p.addParameter("-A-23"); 
   
   free(path); 
   p.runAsynchronously(); 

  }
}//end function



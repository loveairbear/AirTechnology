
bool playmusic(char file[]){
          char* w = "madplay /mnt/sda1/Sounds/";
  char* path =(char*)malloc(strlen(w)+strlen(file)+1); /* make space for the new string (should check the return value ...) */
  strcpy(path, w); /* copy name into the new var, used strncpy to combat buffer overflow*/
  strcat(path, file); /* add the extension */
  p.runShellCommand(path);
  free(path);
 return(true);
  
}


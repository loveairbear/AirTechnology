void SDbytes(char path[],int sdarray[]){
  File w=FileSystem.open(path,FILE_READ);
  int x;
  for(int i = 0 ; i < 64; i++){
    x = w.read() << 8; // Extract the MSB of the 16-bit integer
    x |= w.read(); // Append the LSB to the previous MSB
    sdarray[i] = x;
  }//end forloop
  w.close(); // close sd file
}// end function


void drawbitmap(int colorbuffer[],uint8_t mode) {


if(mode == 1){
  for(int i = 0 ; i <= brightness ; i += 5){ //fade in
  int bufferindex = 0;
    for (int y = 7 ; y >= 0 ; y--) { //after the color array is built, they are pushed into this loop where it build the each pixel
      for (int x = 0 ; x < 8 ; x++) {    //and displays according to the color array
        matrix.drawPixel(x, y, colorbuffer[bufferindex]);
        bufferindex++;
      }
    }
    matrix.setBrightness(i);
    matrix.show();
    delay(5);
  }
}//endif mode 1 which fades in
else{

  int bufferindex = 0;
  for (int y = 7 ; y >= 0 ; y--) { //after the color array is built, they are pushed into this loop where it build the each pixel
    for (int x = 0 ; x < 8 ; x++) {    //and displays according to the color array
      matrix.drawPixel(x, y, colorbuffer[bufferindex]);
      bufferindex++;

    }
  }
  matrix.show();

}//end if mode 0 which doesnt fade in (used for bitmap animations)


}


bool fetchNsketch(char* werd,uint8_t mode,uint8_t frames,bool still){
  char* w = ("/mnt/sda1/Dsprites/");
  mqttsig=0;
  
  if(frames!=0){
    while (true){
      for(int i=1 ; i <= frames ; i++){
        char* path =(char*)malloc(strlen(w)+strlen(werd)+3+1); /* make space for the new string (should check the return value ...) */
        char list[2];
        strcpy(path, w); /* copy name into the new var*/
        strcat(path, werd); /* add the extension */
        strcat(path,itoa(i,list,10));/* add the extension */ 
        SDbytes(path,sd);
        free(path);// deallocate memory used for char array
        drawbitmap(sd,mode);
        int firstTime = millis(); // lastTime and firstTime to time infinite loop
        int lastTime = firstTime; 
        while ((lastTime-firstTime)<=350){
          
          if(mqttsig == 1){mqttsig=0;return false;} // common exit flag
          
          if(mode>2){if(sendnrecv(mode)>0){return true;}} // send and receive mode
          
          if(mode==2){
            if(scrollingmusic()> 0){return true;}
            } // scrolling through songs in playmode
          lastTime = millis();
          }//end delay while loop
        } //end forloop
        if(still==true){return true;} // this is if you choose to run the animation once
      }//endwhile
  }//endif

 else{
    char* path =(char*)malloc(strlen(w)+strlen(werd)+1+1); /* make space for the new string (should check the return value ...) */
    strcpy(path, w); /* copy name into the new var*/
    strcat(path, werd); /* add the extension */
    SDbytes(path,sd);
    free(path);// deallocate memory used for char array
    drawbitmap(sd,mode);
    delay(200); // To give the Yun a break so it doesnt straight up die
    return (true); 
    }
return true;
}


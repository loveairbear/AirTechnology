bool cancelpin() {
  if (digitalRead(squarepin) == HIGH) {
    vibrate();
    matrix.fillScreen(0);
    matrix.show();
    playmusic("madplay /mnt/sda1/Sounds/back.mp3");
    return (true);

  }//endif
}//end func



bool button() {


  int counter = 0;
  if (digitalRead(heartpin) == HIGH && digitalRead(squarepin) == LOW) { // enter inbox mode
    
   // digitalWrite(vibratepin,HIGH); // this motor acts to give feedback if the loop is working
    
//    while (digitalRead(heartpin)==HIGH && counter <=255 ){ //This loop acts to count while 
     // counter += 1;
 //   }
    

    //digitalWrite(vibratepin,LOW);
    /*
    if (counter==255){
      SDbytes("/mnt/sda1/AirTech/www/DecodedSprites/clouds",sd);
      drawbitmap(sd);
    }*/
    //else
      client.publish("protobear/sig","heartpressed");
      playmusic("madplay /mnt/sda1/Sounds/rcvd.mp3"); //
      // client.loop(); 
    }
  
  if (digitalRead(circlepin) == HIGH and digitalRead(crosspin) == HIGH) {
    
        while (connection()) { // this loop functions to reply to a received emoticon
          client.loop();
          connection();
          playmusic("madplay /mnt/sda1/Sounds/mode.mp3");
        if (digitalRead(crosspin) == HIGH and digitalRead(circlepin) == LOW) { // to the left
          vibrate();
          client.publish("protobear/sig", "thingsicansend-left");
          playmusic("madplay /mnt/sda1/Sounds/bloop.mp3");
        }
        if (digitalRead(circlepin) == HIGH and digitalRead(crosspin) == LOW) {
          vibrate();
          client.publish("protobear/sig", "thingsicansend-right");
          playmusic("madplay /mnt/sda1/Sounds/bloop.mp3");
        }
        if (digitalRead(heartpin) == HIGH) {
          vibrate();
          vibrate();
          playmusic("madplay /mnt/sda1/Sounds/send.mp3");
          client.publish("protobear/sig", "send");
          
        return (true); // breaks 
        }//end meta-if

        if (cancelpin()){
          return (true); // breaks out of function

        }
    }//end while      
      
    }
  //}                                                                                                   //endif for heartpin
 
  if (digitalRead(heartpin) == HIGH && digitalRead(squarepin) == HIGH) {                              // Heart button and square button (left+right)
    p.runShellCommandAsynchronously("madplay /mnt/sda1/Sounds/storytime.mp3");
      SDbytes("/mnt/sda1/AirTech/www/DecodedSprites/galleyship",sd);
      drawbitmap(sd);
      //delay(3000);
    //   SDbytes("/mnt/sda1/AirTech/www/DecodedSprites/pirateship",sd);
     // drawbitmap(sd);
      
    }//end while loop
  //end heart+square if

  
  cancelpin();//the same as if statement for square pin

  if (digitalRead(crosspin) == HIGH and digitalRead(circlepin) == LOW) {
    vibrate();
    playmusic("madplay /mnt/sda1/Sounds/bloop.mp3");
     SDbytes("/mnt/sda1/AirTech/www/DecodedSprites/wispx1",sd);
      
      drawbitmap(sd);
    return (true);
  }


  if (digitalRead(circlepin) == HIGH and digitalRead(crosspin) == LOW) {
    vibrate();
    playmusic("madplay /mnt/sda1/Sounds/bloop.mp3");
//    hug("/mnt/sda1/AirTech/www/DecodedSprites/circle1");
 //   hug("/mnt/sda1/AirTech/www/DecodedSprites/circle2");
  //  hug("/mnt/sda1/AirTech/www/DecodedSprites/circle3");
    return (true);
  }



  if (digitalRead(crosspin) == HIGH and digitalRead(circlepin) == HIGH) {//entering sendmode
    vibrate();
    playmusic("madplay /mnt/sda1/Sounds/storynory.mp3");

  }//end if
  return (0);
}//end function

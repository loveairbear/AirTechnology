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
    
      client.publish("protobear/sig","heartpressed");
      playmusic("madplay /mnt/sda1/Sounds/rcvd.mp3"); //
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

    }//end while      
      
    }
  //}                                                                                                   //endif for heartpin
 
  if (digitalRead(heartpin) == HIGH && digitalRead(squarepin) == HIGH) {                              // Heart button and square button (left+right)
    p.runShellCommandAsynchronously("madplay /mnt/sda1/Sounds/storytime.mp3");
    }//end while loop
  //end heart+square if

  
  cancelpin();//the same as if statement for square pin

  if (digitalRead(crosspin) == HIGH) {
             vibrate();
          client.publish("protobear/sig", "thingsicansend-left");
          playmusic("madplay /mnt/sda1/Sounds/bloop.mp3");
   /*

    vibrate();
    playmusic("madplay /mnt/sda1/Sounds/bloop.mp3");
    */
    //return (true);
  }


  if (digitalRead(circlepin) == HIGH) {
             vibrate();
          client.publish("protobear/sig", "thingsicansend-right");
          playmusic("madplay /mnt/sda1/Sounds/bloop.mp3");
/*
    vibrate();
    playmusic("madplay /mnt/sda1/Sounds/bloop.mp3");
//    hug("/mnt/sda1/AirTech/www/DecodedSprites/circle1");
 //   hug("/mnt/sda1/AirTech/www/DecodedSprites/circle2");
  //  hug("/mnt/sda1/AirTech/www/DecodedSprites/circle3");
    return (true);*/
  }


  //return (0);
}//end function

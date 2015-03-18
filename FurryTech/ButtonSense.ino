bool cancelpin() {
  if (digitalRead(squarepin) == HIGH && digitalRead(heartpin) == LOW) {
    vibrate();
    playmusic("back.mp3");
    for (int q = brightness ; q >= 0  ; q-=5) {
      matrix.setBrightness(q);
      matrix.show();
      delay(20);
    }
    
    return (true);

  }//endif
  else {
    return false;
  }
}//end func

int last = 0;
int first =0;

bool button() {


   
  if (digitalRead(heartpin) == HIGH && digitalRead(squarepin) == LOW) { // ENTER INBOX MODE
    vibrate();
    client.publish("protobear/sig", "heartp"); // enter inbox mode
    playmusic("rcvd.mp3"); //
    client.loop();
    connection();
    while (true) {
      client.loop();
      connection();
      if (digitalRead(squarepin) == HIGH && digitalRead(heartpin) == LOW) { //CANCEL PIN
        vibrate();
        playmusic("back.mp3");
        for (int q = brightness ; q >= 0  ; q-=5) {
          matrix.setBrightness(q);
          matrix.show();
          delay(30);
        }
        break;
      }//endif
      
      if (digitalRead(crosspin) == HIGH and digitalRead(circlepin) == LOW) { // Scroll through last 10 received messages LEFT
        vibrate();
        client.publish("protobear/sig", "heart-left");
        playmusic("light.mp3");
      }//end if
      
      if (digitalRead(circlepin) == HIGH and digitalRead(crosspin) == LOW) { // Scroll through last 10 received messages RIGHT
        vibrate();
        client.publish("protobear/sig", "heart-right");
        playmusic("light.mp3");
      }//endif
      
      if (digitalRead(heartpin) == HIGH && digitalRead(squarepin) == LOW) { //  ENTER  
        vibrate();
        playmusic("mode.mp3");
        while (true) { // this loop functions to reply to a received emoticon
          client.loop();
          connection();
          if (digitalRead(squarepin) == HIGH && digitalRead(heartpin) == LOW) { //CANCEL PIN
            vibrate();
            playmusic("back.mp3");
            for (int q = brightness ; q >= 0  ; q-=5) {
              matrix.setBrightness(q);
              matrix.show();
              delay(30);
            }
            break;
          }//endif
          if (digitalRead(crosspin) == HIGH and digitalRead(circlepin) == LOW) { // to the left
            vibrate();
            client.publish("protobear/sig", "scroll-left");
            playmusic("bloop.mp3");
            client.loop();
          }//endif
          
          if (digitalRead(circlepin) == HIGH and digitalRead(crosspin) == LOW) {
            vibrate();
            client.publish("protobear/sig", "scroll-right");
            playmusic("bloop.mp3");
            client.loop();
          }//endif
          
          if (digitalRead(heartpin) == HIGH) {
            vibrate();
            vibrate();
            playmusic("send.mp3");
            client.publish("protobear/sig", "scroll-send");
            return (true); // break out of function
          }//end meta-if

        }//end while for send mode

      }//end meta button if


    }//end while loop for receive mode
  }//end if for heart button
                                                                                                   //endif for heartpin

  if(digitalRead(crosspin) == HIGH){
    first = millis();
    while (true){
      if (digitalRead(crosspin) == LOW){
        last = millis();
        break;
      }
    }
    if(last-first > 800){
      vibrate();
      fetchNsketch("360ninja1",1);
      //playmusic("storytime.mp3");
      vibrate();
    }
  } //end hold  if




  cancelpin();//the same as if statement for square pin
  if (digitalRead(circlepin) == HIGH) {

    vibrate();
    playmusic("bloop.mp3");    
    hug("circle1");
    hug("circle2");
    hug("circle3");
    return (true);
  }


  //return (0);
}//end function

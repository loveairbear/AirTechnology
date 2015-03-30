bool cancelpin() {
  if (digitalRead(squarepin) == HIGH && digitalRead(heartpin) == LOW) {
    vibrate();
    playmusic("back");
    for (int q = brightness ; q >= 0  ; q -= 5) {
      matrix.setBrightness(q);
      matrix.show();
      delay(10);
    }
    return (true);

  }//endif
  else {
    return false;
  }
}//end func

int last = 0;
int first = 0;

bool button() {



  if (digitalRead(heartpin) == HIGH && digitalRead(squarepin) == LOW) { // ENTER INBOX MODE
    vibrate();
    client.publish(branch, "heartp"); // enter inbox mode
    playmusic("rcvd"); //
    client.loop();
    connection();
    while (true) { /// ENTER INBOX MODE
      client.loop();
      connection();
      if (digitalRead(squarepin) == HIGH && digitalRead(heartpin) == LOW) { //CANCEL PIN
        vibrate();
        playmusic("back");
        for (int q = brightness ; q >= 0  ; q -= 5) {
          matrix.setBrightness(q);
          matrix.show();
          delay(30);
        }
        break;
      }//endif

      if (digitalRead(crosspin) == HIGH and digitalRead(circlepin) == LOW) { // Scroll through last 10 received messages LEFT
        vibrate();
        client.publish(branch, "heart-left");
        playmusic("light");
      }//end if

      if (digitalRead(circlepin) == HIGH and digitalRead(crosspin) == LOW) { // Scroll through last 10 received messages RIGHT
        vibrate();
        client.publish(branch, "heart-right");
        playmusic("light");
      }//endif

      if (digitalRead(heartpin) == HIGH && digitalRead(squarepin) == LOW) { //  ENTER SEND MODE
        vibrate();
        playmusic("mode");
        while (true) { // this loop functions to reply to a received emoticon
          client.loop();
          connection();
          if (digitalRead(squarepin) == HIGH && digitalRead(heartpin) == LOW) { //CANCEL PIN
            vibrate();
            playmusic("back");
            for (int q = brightness ; q >= 0  ; q -= 5) {
              matrix.setBrightness(q);
              matrix.show();
              delay(30);
            }
            break;
          }//endif
          if (digitalRead(crosspin) == HIGH and digitalRead(circlepin) == LOW) { // to the left
            vibrate();
            client.publish(branch, "scroll-left");
            playmusic("bloop");
            client.loop();
          }//endif

          if (digitalRead(circlepin) == HIGH and digitalRead(crosspin) == LOW) {
            vibrate();
            client.publish(branch, "scroll-right");
            playmusic("bloop");
            client.loop();
          }//endif

          if (digitalRead(heartpin) == HIGH) {
            vibrate();
            vibrate();
            playmusic("send");
            client.publish(branch, "scroll-send");
            return (true); // break out of function
          }//end meta-if

        }//end while for send mode

      }//end meta button if


    }//end while loop for receive mode
  }//end if for heart button
  //endif for heartpin
  /// ENTER PLAYMODE :D ////////
  if (digitalRead(crosspin) == HIGH) {
    first = millis();
    uint8_t index = 0;
    while (true) {
      if (digitalRead(crosspin) == LOW) {
        last = millis();
        break;
      }//endif
    }//endwhile
    
    if (last - first > 800) {
      vibrate();
      playmusic("pickup");
    }//endif
    
    while (true) {
         if(cancelpin()== true){p.close();break;}
         if (digitalRead(crosspin) == true){
              //to the left!
            p.close();
            index = (index-1);
            index = index % soundsize;
            playsongs(char(index));
          delay(500);
        
         }
        if (digitalRead(circlepin) == true){
          //to the right
          
          p.close();
          index = (index+1);
          index = index % soundsize;
          playsongs(char(index));
          delay(500);
        }
        
        else{matrix.fillScreen(0);matrix.show();}
    }
} //end hold  if

/// END PLAYMODE /////////////////


cancelpin();//the same as if statement for square pin
  if (digitalRead(circlepin) == HIGH) {

    vibrate();
    playmusic("bloop");
    hug("circle1");
    hug("circle2");
    hug("circle3");
    return (true);
  }


  //return (0);
}//end function 


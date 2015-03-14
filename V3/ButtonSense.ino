bool cancelpin() {
  if (digitalRead(squarepin) == HIGH && digitalRead(heartpin) == LOW) {
    vibrate();
    matrix.fillScreen(0);
    matrix.show();
    playmusic("back.mp3");
    return (true);

  }//endif
}//end func



bool button() {


  int counter = 0;
  if (digitalRead(heartpin) == HIGH && digitalRead(squarepin) == LOW) { // enter inbox mode
    client.publish("protobear/sig", "heartp"); // enter inbox mode
    playmusic("rcvd.mp3"); //
    while (true) {
      if (digitalRead(crosspin) == HIGH and digitalRead(circlepin) == LOW) { // Scroll through last 10 received messages LEFT
        vibrate();
        client.publish("protobear/sig", "heart-left");
        playmusic("light.mp3");
      }
      if (digitalRead(circlepin) == HIGH and digitalRead(crosspin) == LOW) { // Scroll through last 10 received messages RIGHT
        vibrate();
        client.publish("protobear/sig", "heart-right");
        playmusic("light.mp3");
      }
      if (digitalRead(heartpin) == HIGH && digitalRead(squarepin) == LOW) {
        playmusic("mode.mp3");
        while (true) { // this loop functions to reply to a received emoticon
          client.loop();
          connection();

          if (digitalRead(crosspin) == HIGH and digitalRead(circlepin) == LOW) { // to the left
            vibrate();
            client.publish("protobear/sig", "scroll-left");
            playmusic("light.mp3");
          }
          if (digitalRead(circlepin) == HIGH and digitalRead(crosspin) == LOW) {
            vibrate();
            client.publish("protobear/sig", "scroll-right");
            playmusic("light.mp3");
          }
          if (digitalRead(heartpin) == HIGH) {
            vibrate();
            vibrate();
            playmusic("send.mp3");
            client.publish("protobear/sig", "scroll-send");

            return (true); // breaks
          }//end meta-if

        }//end while

      }//end meta button if


    }
    playmusic("pickup.mp3");
  }


  //}                                                                                                   //endif for heartpin

  if (digitalRead(heartpin) == HIGH && digitalRead(squarepin) == HIGH) {                              // Heart button and square button (left+right)
    //p.runShellCommandAsynchronously("storytime.mp3");
  }//end while loop
  //end heart+square if


  cancelpin();//the same as if statement for square pin

  if (digitalRead(crosspin) == HIGH) {
    vibrate();
    client.publish("protobear/sig", "scroll-left");
    playmusic("bloop.mp3");
    /*

     vibrate();
     playmusic("bloop.mp3");
     */
    //return (true);
  }


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

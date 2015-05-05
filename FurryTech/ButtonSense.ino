bool cancelpin() {
  if (digitalRead(squarepin) == HIGH && digitalRead(heartpin) == LOW) {
    vibrate();
    playmusic("back");
    for (int q = brightness ; q >= 0  ; q -= 5) {
      matrix.setBrightness(q);
      matrix.show();
      delay(10);
    }
    matrix.setBrightness(brightness);
    matrix.fillScreen(0);
    matrix.show();
    return (true);

  }//endif
  else {
    return false;
  }
}//end func

bool scrollingmusic(){
           if (digitalRead(crosspin) == true){
              //to the left!
            p.close();
            index = index-1;
            index = (index % soundsize);
            Serial.println(index);
            playsongs(char(index));
            delay(500);
            return true;
        
         }
        if (digitalRead(circlepin) == true){
          //to the right
          
          p.close();
          index = index+1;
          index = index % soundsize;
          Serial.println(index);
          playsongs(char(index));
          delay(500);
          return true;        
          }
        else{return false;}
}//end func
 bool sendmode(){         
          client.loop();
          connection();
          if(cancelpin()==true){return true;}
          if (digitalRead(crosspin) == HIGH and digitalRead(circlepin) == LOW) { // to the left
            vibrate();
            client.publish(branch, "scroll-left");
            playmusic("bloop");
            client.loop();
            return(false);
          }//endif

          if (digitalRead(circlepin) == HIGH and digitalRead(crosspin) == LOW) { // to the right
            vibrate();
            client.publish(branch, "scroll-right");
            playmusic("bloop");
            client.loop();
            return(false);
          }//endif

          if (digitalRead(heartpin) == HIGH) { // heart button
            vibrate();
            vibrate();
            playmusic("send");
            client.publish(branch, "scroll-send");
            return (true); // break out of function
          }//end meta-if
          else{return false;}
    }//end function
uint8_t sendnrecv(uint8_t mode){
      client.loop();
      connection();
      
      if(cancelpin()==true){mqttsig =1 ;return 1;}//endif

      if (digitalRead(crosspin) == HIGH and digitalRead(circlepin) == LOW ) { // Scroll through last 10 received messages LEFT
        vibrate();
        if(mode==3){
          mqttmsg = "h-l";
          playmusic("light");
          return 3;            
        }
        if(mode==4){
          mqttmsg = "s-r";
          playmusic("bloop");
          return(4);
        }

      }//end if    
      if (digitalRead(circlepin) == HIGH and digitalRead(crosspin) == LOW) { // Scroll through last 10 received messages RIGHT
        vibrate();
        if(mode==3){
        mqttmsg = "h-l";
        playmusic("light");
        return 3;            
        }
        if(mode==4){
        mqttmsg = "s-l";
        playmusic("bloop");
        return(4);            
        }

      }//endif

      if (digitalRead(heartpin) == HIGH && digitalRead(squarepin) == LOW) { //  ENTER SEND MODE
        vibrate();
        if(mode==3){

        playmusic("mode");      
        return 2;            
        }
        if(mode==4){
        vibrate();
        playmusic("send");
        client.publish(branch, "s-snd");
        return (5); // break out of function
            
        }

      }//endif

    }//end function

void latcher(){if (mqttmsg!=NULL){client.publish(branch,mqttmsg);}} // simple function


int last = 0;
int first = 0;

bool button() {
  if (digitalRead(heartpin) == HIGH && digitalRead(squarepin) == LOW) { // ENTER INBOX MODE
    vibrate();
    playmusic("rcvd"); //
    
    connection();
    animode=3; //set animode to inboxmode
    mqttsig=0; // reset mqtt flag signal
    client.publish(branch, "hrtp"); // enter inbox mode
    while (true) { /// ENTER INBOX MODE 
      if(mqttsig==1){return true;} // another exit signal coming from the animation infinite loop
      Serial.println(mqttsig);
      latcher();
      if(sendnrecv(animode)==2){ // enter send mode
        animode=4;
        while (mqttsig==0){
          sendnrecv(animode);
          latcher();
        }
        }
      }//endinfinitewhile
    }//end function
           
  /// ENTER PLAYMODE :D ////////
  if (digitalRead(crosspin) == HIGH) {                                         // This uses millis() to detect for how long a button has been held
    first = millis();
    index = 0;
    while (true) {
      if (digitalRead(crosspin) == LOW) {
        last = millis();
        break;
      }//endif
    }//endwhile
    
    if (last - first > 800) {
      vibrate();
      playmusic("pickup");
      
    while (true) {
         if(cancelpin()== true){p.close();return false;}
        else{matrix.fillScreen(0);matrix.show();}
        scrollingmusic();
        
        while(p.running()){
        if(cancelpin()== true){p.close();return false;}
        scrollingmusic();
        if(index==7){if(fetchNsketch("epicface",2,7)==false){return false;}}
        if(index==9){if(fetchNsketch("dragon",2,17)==false){return false;}}
        if(index==3){if(fetchNsketch("angel",2,12)==false){return false;}}
        if(index==4){if(fetchNsketch("chesth",2,12)==false){return false;}}
        
        else{matrix.fillScreen(0);matrix.show();}
        }
    }//end while
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


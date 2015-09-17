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

uint8_t scrollingmusic(){
         if (digitalRead(crosspin) == true && digitalRead(circlepin) == false){
              //to the left!
            p.close();
            index = index-1;
            index = (index % soundsize);
            char music[3];
            itoa(index,music,10);
            playmusic(music);
            delay(1000);
            return 1;
        
         }
        if (digitalRead(circlepin) == true){
          //to the right
          
          p.close();
          index = index+1;
          index = index % soundsize;
            char music[3];
            itoa(index,music,10);
          playmusic(music);
          delay(1000);
          return 1;        
          }
        else{return 0;}
}//end func
uint8_t sendnrecv(uint8_t mode){
      if(cancelpin()==true){mqttsig=1 ;return 1;}//endif
      if (digitalRead(crosspin) == HIGH and digitalRead(circlepin) == LOW ) { // Scroll through last 10 received messages LEFT
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
      }//end if    
      if (digitalRead(circlepin) == HIGH and digitalRead(crosspin) == LOW) { // Scroll through last 10 received messages RIGHT
        vibrate();
        if(mode==3){
        mqttmsg = "h-r";
        playmusic("light");
        return 3;            
        }
        if(mode==4){
        mqttmsg = "s-r";
        playmusic("bloop");
        return(4);            
        }

      }//endif

      if (digitalRead(heartpin) == HIGH && digitalRead(squarepin) == LOW) { //  ENTER SEND MODE
        vibrate();
        if(mode==3){
        animode=4; // set flag to 4 which is sendmode
        playmusic("mode");      
        return 4; // 4 is sendmode            
        }
        if(mode==4){
        vibrate();
        playmusic("send");
        mqttsig=1;
        refresh();
        client.publish(branch, "s-snd");
        return (5); // break out of function
        }

      }//endif
      else{return 0;}
    }//end function

void latcher(){
 
  if (mqttmsg!=NULL){
    client.publish(branch,mqttmsg);
    mqttmsg=NULL;
    int TimerStart=millis();
    int TimerEnd = 0;
    while(TimerEnd-TimerStart<1000){
      TimerEnd=millis();
      client.loop();
    }// end while
    
  }//endif
  client.loop();
} // endfunction




bool button() {
  int ButtonUp = 0;
  int ButtonDown= 0;
  
  if (digitalRead(heartpin) == HIGH && digitalRead(squarepin) == LOW) { // ENTER INBOX MODE 
    
    /* this part involving millis() is used to determine how long a button is held by entering an infinite loop once the button is pressed
    then once the button is let go the infinite loop exits while capturing the time upon letting the button go, the difference between the variables
    'first' and 'last' yield the time the button was held in milliseconds*/
    
    ButtonUp = millis();
    while (true) {
      client.loop();
      if (digitalRead(heartpin) == LOW) {
        ButtonDown = millis();
        break;
      }//endif
    }//endwhile
    
    if (ButtonUp - ButtonDown > 800) {
      p.begin("python");
      p.addParameter("/mnt/sda1/libpy/vce.py");
      p.runAsynchronously();
      while(p.running()){
        fetchNsketch("muzak",0,2,false);
        if(cancelpin()==true){p.close();return true;}
      }
      return true;
    
    }// end if for holding heart button
    
    else{
      vibrate();
      playmusic("rcvd"); //'
      connection();
      animode=3;//GLOBAL set animode to inbox mode - this flag is called 'animation mode',
      //this flag lets the bitmap drawing function(infinite loop) know what mode the bear is in (ie. play the respective mode sounds)
    
    mqttsig=0; // GLOBAL reset mqtt flag signal - this is default - this flag is a simple exit flag which in retrospect should be named 'exitsig'
    
    bool called = true;// one timer boolean just to make sure a certain command is called once within an infinite loop
    notificationflag = false;// GLOBAL - this flag is solely used for the 'ghost animation' which is the main() loop, it makes the ghost change
    
    // resets the 'ghost animation color'(in  main() loop) this restores default color after being trigger by sms via notification flag
    GhostColor[0] = 0;
    GhostColor[1] = 255;
    GhostColor[2] = 255;
    client.publish(branch, "hrtp"); // enter inbox mode
    ButtonDown=millis();
    while(ButtonUp-ButtonDown<200){
      ButtonUp=millis();
      client.loop();
    }// end while
    
    while(true){//inbox infinite loop
      sendnrecv(animode);// the sendnrecv function either prepares a string which would be used by latcher() which sends mqtt or
      //exit while modifying the animode variable thus changing to send mode (or can exit using mqttsig flag)
      latcher();
      delay(250);
      if(mqttsig==1){return 1;}
      
      if(animode==4){//entersendmode
        while(true){
          sendnrecv(animode);
          latcher();
          if(mqttsig==1){return 1;}
          }//end infinite while loop
        }//endif
      }//end infinite while loop
    }//end else
  }//end if
           
  /// ENTER PLAYMODE :D ////////
  if (digitalRead(crosspin) == HIGH) {                                         // This uses millis() to detect for how long a button has been held
    ButtonDown = millis();
    index = 0;
    while (true) {
      if (digitalRead(crosspin) == LOW) {
        ButtonUp = millis();
        break;
      }//endif
    }//endwhile
    if (ButtonUp - ButtonDown >= 500) {
      vibrate();
      playmusic("pickup");
      while (true) {
      scrollingmusic();
      if(cancelpin()==true){mqttsig=0;return false;}
        while(p.running()){
          scrollingmusic();
          if(cancelpin()==true){p.close();mqttsig=0;return false;}
          if(index==7){fetchNsketch("epicface",2,7,true);}
          if(index==9){fetchNsketch("dragon",2,17,true);}
          if(index==3){fetchNsketch("angel",2,12,true);}
          if(index==4){fetchNsketch("chesth",2,12,true);}   
          else{fetchNsketch("muzak",0,2,true);}
        }
        return true;
        
    }//end while
    }//end if
    else{return false;}
} //end button if

/// END PLAYMODE /////////////////
  if (digitalRead(squarepin) == HIGH) {                                         // This uses millis() to detect for how long a button has been held
    ButtonDown = millis();
    index = 0;
    while (true) {
      if (digitalRead(squarepin) == LOW) {
        ButtonUp = millis();
        break;
      }//endif
    }//endwhile
    
    if (ButtonUp - ButtonDown > 800) { //enter settings mode
      refresh();
      while(true){
        heart(4);
        if(digitalRead(crosspin)==HIGH){
          brightness = brightness - 5 % 255;
          delay(25);
        }
        if(digitalRead(circlepin)==HIGH){
          brightness = brightness + 5 % 255;
          delay(25);
        }
        
        if(cancelpin()==true){return false;}
        }// end infinite loop
      
    }
    else{
    vibrate();
    playmusic("back");
    }//ennd else
  }// end square button ( cancel/ settings(hold)) if
  if (digitalRead(circlepin) == HIGH) {
    delay(1500);
    while(true){
    if(digitalRead(crosspin)==HIGH){
    vibrate();
    playmusic("bloop");
    fetchNsketch("eau1",1,0,false);
    while(true){
      if(cancelpin()){return true;}
      if(digitalRead(heartpin)==HIGH){
        fetchNsketch("eau",0,6,true);
        fetchNsketch("tama",0,6,true);
        fetchNsketch("tama",0,6,true);
        refresh();
        return true;
      }   
    }
    }
    if(digitalRead(circlepin)==HIGH){
    vibrate();
    playmusic("bloop");
    fetchNsketch("appl1",1,0,false);
    while(true){
      if(cancelpin()){return true;}
      if(digitalRead(heartpin)==HIGH){
        fetchNsketch("appl",0,5,true);
        fetchNsketch("tama",0,6,true);
        fetchNsketch("tama",0,6,true);
        refresh();
        return true;
      }   
    }
    }
    }
    return (true);
  }


  //return (0);
}//end function 


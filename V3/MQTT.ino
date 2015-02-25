
boolean connection() {
  if (client.connected()) {
    client.subscribe("protobear/com");
    return (true);
  }
  else{
    for(int i = 0 ; i < 10 ; i++){
      client.
    }
  }
  
  
}//end func



void callback(char* topic, byte* payload, unsigned int length) {
  Serial.println(F("x"));
  Serial.println(int(payload));
  
if( (int(payload) - 48) == 1){
    heart(1);
    connection();  
  }
  if ((int(payload) - 48) == 2)  {
              SDbytes("/mnt/sda1/AirTech/www/DecodedSprites/apple",sd);
      drawbitmap(sd);
  }
  if ((int(payload) - 48) == 3)  {
    heart(3);
    connection();
  }
  if ((int(payload) - 48) == 4)  {
    heart(4);
    connection();
  }
  
  /*
  if ((int(payload) - 48) == 5) {
    hug("/mnt/sda1/AirTech/www/DecodedSprites/circle1");
    hug("/mnt/sda1/AirTech/www/DecodedSprites/circle2");
    hug("/mnt/sda1/AirTech/www/DecodedSprites/circle3");
  }*/
  /*
  if ((int(payload) - 48) == 6){
          SDbytes("/mnt/sda1/AirTech/www/DecodedSprites/apple",sd);
      drawbitmap(sd);
  }
  if ((int(payload) - 48) == 7){
    draw("food");
  }
   if ((int(payload) - 48) == 8){
    draw("fullglass");
  }
  if ((int(payload) - 48) == 9){
    draw("magicbunny");
  }
  if ((int(payload) - 48) == 10){
    draw("ring");
  }
  
 
  if ((int(payload) - 48) == 11){
    draw("galleyship");
  }
  if ((int(payload) - 48) == 12){
    draw("pinetree");
  }
  if ((int(payload) - 48) == 13){
    draw("lollerpop");
  }
  if ((int(payload) - 48) == 14){
    draw("pirateship");
  }
  if ((int(payload) - 48) == 15){
     draw("slimer");
  }
  if ((int(payload) - 48) == 16){
    draw("wispx1");
  }
  if ((int(payload) - 48) == 17){
    draw("skepticskullfy");
  }
*/
  
  else {
    refresh();
    connection();
  }
}







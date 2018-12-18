#include <math.h>

int received_byte, counter, id, id_sender, id_dest, id_concern;
bool start, started;
String msg;
int deci_lat_bat1;
int deci_lat_bat2;
int deci_long_bat1;
int deci_long_bat2;
String type;
float vitesse_met1;
float vitesse_met2;
float vitesse_bat1;
float vitesse_bat2;
float cap_met1;
float cap_met2;
float cap_bat1;
float cap_bat2;
float longitude_bat1;
float longitude_bat2;
float latitude_bat1;
float latitude_bat2;
float tangage_bat1;
float tangage_bat2;
float gite_bat1;
float gite_bat2;
float barre_bat1;
float barre_bat2;
float ecoute_bat1;
float ecoute_bat2;

void setup() {
  // put your setup code here, to run once:
  counter = -2;
  start = false;
  started = false;
  Serial.begin(9600);
}

void loop() {
  //Read the received data
  if (Serial.available() > 0) {
    // read the incoming byte:
    received_byte = Serial.read();
    if (received_byte == 114) { //receive only "r" --> Restart
      counter = -2;
      start = true;
    }
  }
  //Start the simulation when something is received
  //if (Serial.available() > 0 && start == false) {
  //  start = true;
  //}
  if (start == true) {
    if (counter <= 2  && started==false) {
    //if (counter <= 2) {
      if (counter != 0) {
        int key = random(1, 999);
        if (counter < 0) {type = "MC";}
        else {type = "BC";}
        id_sender = counter;
        id_dest = 0;
        id_concern = counter;
        msg = String("__") + key + "&type:" + type + "&id_sender:" + id_sender + "&id_dest:" + id_dest + "&id_concern:" + id_concern + "&" + key + "//";
        Serial.print(msg);
      }
      else{
        longitude_bat1 = -4.613100f;
        longitude_bat2 = -4.613300f;
        latitude_bat1  = 48.430300f;
        latitude_bat2  = 48.430100f;

        vitesse_met1 = 0.0f;
        vitesse_met2 = 0.0f;
        vitesse_bat1 = 0.0f;
        vitesse_bat2 = 0.0f;
        cap_met1 = 160.0f;
        cap_met2 = 175.0f;
        cap_bat1 = 10.0f;
        cap_bat2 = -12.0f;
        
        deci_long_bat1 = 0;
        deci_long_bat2 = 0;
        deci_lat_bat1 = 0;
        deci_lat_bat2 = 0;
        
        tangage_bat1 = 2.0f;
        tangage_bat2 = -3.0f;
        gite_bat1 = -5.0f;
        gite_bat2 = 4.0f;
        barre_bat1 = 10.0f;
        barre_bat2 = -10.0f;
        ecoute_bat1 = 25.0f;
        ecoute_bat2 = 32.0f;
      }
    }
    else {
      started=true;
      message(1);
    }
    delay(1000);
    counter++;
  }
}

void message(int mode) {
  msg = "";

  if(mode==1){
    //Make the random really random
    randomSeed(counter);
    int key = random(1, 999);
    id = random(-2, 3);
    id_sender = id;
    id_dest = 0;
    id_concern = id;
    if (id != 0) {
      if (id > 0) {
        //It is a boat
        type = "B";
        msg = msg + "__" + key + "&type:" + type + "&id_sender:" + id_sender + "&id_dest:" + id_dest + "&id_concern:" + id_concern + "&";
            
        //VITESSE
        if(id==1){
          vitesse_bat1 = vitesse_bat1 + 0.1f;
          msg = msg + "vitesse:" + vitesse_bat1 + "&";
        } else {
          vitesse_bat2 = vitesse_bat2 + 0.1f;
          msg = msg + "vitesse:" + vitesse_bat2 + "&";
        }

        //CAP
        if(id==1){
          cap_bat1 = cap_bat1 + 0.1f;
          msg = msg + "cap:" + cap_bat1 + "&";
        } else {
          cap_bat2 = cap_bat2 + 0.1f;
          msg = msg + "cap:" + cap_bat2 + "&";
        }
        
        //LONGITUDE
        
        if(id==1){
          if (longitude_bat1>10.0f || longitude_bat1<-10.0f){
            deci_long_bat1 = deci_long_bat1 + int(longitude_bat1/10.0f);
            longitude_bat1 = longitude_bat1 - float((deci_long_bat1)*10);
          }
          longitude_bat1 = longitude_bat1 + 0.000005f;
          if (deci_long_bat1 != 0){ msg = msg + "longitude:" + deci_long_bat1 + String(fabs(longitude_bat1),6) + "&";}
          else {msg = msg + "longitude:" + String(longitude_bat1,6) + "&";}
        } else {
          if (longitude_bat2>10.0f || longitude_bat2<-10.0f){
            deci_long_bat2 = deci_long_bat2 + int(longitude_bat2/10.0f);
            longitude_bat2 = longitude_bat2 - float((deci_long_bat2)*10);
          }
          longitude_bat2 = longitude_bat2 + 0.000005f;
          if (deci_long_bat2 != 0){ msg = msg + "longitude:" + deci_long_bat2 + String(fabs(longitude_bat2),6) + "&";}
          else {msg = msg + "longitude:" + String(longitude_bat2,6) + "&";}
        }

        //LATITUDE
        
        if(id==1){
          if (latitude_bat1>10.0f || latitude_bat1<-10.0f){
            deci_lat_bat1 = deci_lat_bat1 + int(latitude_bat1/10.0f);
            latitude_bat1 = latitude_bat1 - float((deci_lat_bat1)*10);
          }
            latitude_bat1 = latitude_bat1 + 0.000005f;
          if (deci_lat_bat1 != 0){ msg = msg + "latitude:" + deci_lat_bat1 + String(fabs(latitude_bat1),6) + "&";}
          else {msg = msg + "latitude:" + String(latitude_bat1,6) + "&";}
        } else {
          if (latitude_bat2>10.0f || latitude_bat2<-10.0f){
            deci_lat_bat2 = deci_lat_bat2 + int(latitude_bat2/10.0f);
            latitude_bat2 = latitude_bat2 - float((deci_lat_bat2)*10);
          }
          latitude_bat2 = latitude_bat2 + 0.000005f;
          if (deci_lat_bat2 != 0){ msg = msg + "latitude:" + deci_lat_bat2 + String(fabs(latitude_bat2),6) + "&";}
          else {msg = msg + "latitude:" + String(latitude_bat2,6) + "&";}
        }

        //TANGAGE
        if(id==1){
          tangage_bat1 = tangage_bat1 + 0.1f;
          msg = msg + "tangage:" + tangage_bat1 + "&";
        } else {
          tangage_bat2 = tangage_bat2 + 0.1f;
          msg = msg + "tangage:" + tangage_bat2 + "&";
        }

        //GITE
        if(id==1){
          gite_bat1 = gite_bat1 + 0.1f;
          msg = msg + "gite:" + gite_bat1 + "&";
        } else {
          gite_bat2 = gite_bat2 + 0.1f;
          msg = msg + "gite:" + gite_bat2 + "&";
        }
        
        //BARRE
        if(id==1){
          barre_bat1 = barre_bat1 + 0.1f;
          msg = msg + "barre:" + barre_bat1 + "&";
        } else {
          barre_bat2 = barre_bat2 + 0.1f;
          msg = msg + "barre:" + barre_bat2 + "&";
        }

        //ECOUTE
        if(id==1){
          ecoute_bat1 = ecoute_bat1 + 0.1f;
          msg = msg + "ecoute:" + ecoute_bat1 + "&";
        } else {
          ecoute_bat2 = ecoute_bat2 + 0.1f;
          msg = msg + "ecoute:" + ecoute_bat2 + "&";
        }
      }
      else if (id < 0) {
        //It is a weather station
        type = "M";
        msg = msg + "__" + key + "&type:" + type + "&id_sender:" + id_sender + "&id_dest:" + id_dest + "&id_concern:" + id_concern + "&";
        
        if(id==1){
          vitesse_met1 = vitesse_met1 + 0.1f;
          msg = msg + "vitesse:" + vitesse_met1 + "&";
        } else {
          vitesse_met2 = vitesse_met2 + 0.1f;
          msg = msg + "vitesse:" + vitesse_met2 + "&";
        }

        if(id==1){
          cap_met2 = cap_met1 + 0.1f;
          msg = msg + "cap:" + cap_met1 + "&";
        } else {
          cap_met2 = cap_met2 + 0.1f;
          msg = msg + "cap:" + cap_met2 + "&";
        }
      }
      msg = msg + key + "//";
      Serial.print(msg);
    }
    //Do nothing, it is the id of the serveur(0)
  }
//  else if (mode==2){
//    int key = random(1, 999);
//    id_sender = 1;
//    id_dest = 0;
//    id_concern = 1;
//    type = "B";
//    msg = msg + "__" + key + "&type:" + type + "&id_sender:" + id_sender + "&id_dest:" + id_dest + "&id_concern:" + id_concern + "&";
//    longitude = longitude + 0.000001;
//    if (longitude>10.0 || longitude<-10.0){
//      deci_long = deci_long + int(longitude/10);
//      longitude = longitude - deci_long*10;
//    }
//    if (deci_long != 0){
//      msg = msg + "longitude:" + deci_long + String(fabs(longitude),6) + "&";
//    }
//    else
//    {
//      msg = msg + "longitude:" + String(longitude,6) + "&";
//    }
//    
//    msg = msg + "longitude:" + String(longitude,6) + "&";
//    
//    latitude = latitude + 0.000001;
//    if (latitude>10.0 || latitude<-10.0){
//      deci_lat = deci_lat + int(latitude/10);
//      latitude = latitude - deci_lat*10;
//    }
//    if (deci_lat != 0){
//      msg = msg + "latitude:" + deci_lat + String(fabs(latitude),6) + "&";
//    }
//    else
//    {
//      msg = msg + "latitude:" + String(latitude,6) + "&";
//    }
//    msg = msg + key + "//";
//    Serial.print(msg);
//  }
}

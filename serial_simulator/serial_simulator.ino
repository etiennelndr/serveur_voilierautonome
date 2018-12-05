#include <math.h>

int received_byte, i, id, id_sender, id_dest, id_concern, deci_lat, deci_long;
String msg, type;
float vitesse, cap, longitude, latitude, tangage, gite, barre, ecoute;
bool start, started;

void setup() {
  // put your setup code here, to run once:
  i = -5;
  deci_long = 0;
  deci_lat = 0;
  start = false;
  started = false;
  vitesse = 0.0;
  cap = 0.0;
  longitude = -4.612900;
  latitude = 48.430100;
  tangage = 0.0;
  gite = 0.0;
  barre = 0.0;
  ecoute = 0.0;
  Serial.begin(9600);
}

void loop() {
  //Read the received data
  if (Serial.available() > 0) {
    // read the incoming byte:
    received_byte = Serial.read();
    if (received_byte == 114) { //receive only "r" --> Restart
      i = -5;
    }
  }
  //Start the simulation when something is received
  if (Serial.available() > 0 && start == false) {
    start = true;
  }
  if (start == true) {
    if (i <= 5  && started==false) {
      if (i != 0) {
        int key = random(1, 999);
        if (i < 0) {
          type = "MC";
        }
        else if (i > 0) {
          type = "BC";
        }
        id_sender = i;
        id_dest = 0;
        id_concern = i;
        msg = String("__") + key + "&type:" + type + "&id_sender:" + id_sender + "&id_dest:" + id_dest + "&id_concern:" + id_concern + "&" + key + "//";
        Serial.print(msg);
      }
    }
    else {
      started=true;
      message(1);
    }
    delay(1000);
    i++;
  }
}

void message(int mode) {
  msg = "";

  if(mode==1){
    //Make the random really random
    randomSeed(i);
    int key = random(1, 999);
    int choice;
    id = random(-5, 5);
    id_sender = id;
    id_dest = 0;
    id_concern = id;
    if (id != 0) {
      if (id > 0) {
        //It is a boat
        type = "B";
        msg = msg + "__" + key + "&type:" + type + "&id_sender:" + id_sender + "&id_dest:" + id_dest + "&id_concern:" + id_concern + "&";
        choice = random(1, 8);
        switch (choice) {
          case 1 :
            vitesse += 0.1;
            msg = msg + "vitesse:" + vitesse + "&";
            break;
          case 2 :
            cap -= 0.1;
            msg = msg + "cap:" + cap + "&";
            break;
          case 3 :
            longitude = longitude + 0.000001;
            if (longitude>10.0 || longitude<-10.0){
              deci_long = deci_long + int(longitude/10);
              longitude = longitude - deci_long*10;
            }
            if (deci_long != 0){
              msg = msg + "longitude:" + deci_long + String(fabs(longitude),6) + "&";
            }
            else
            {
              msg = msg + "longitude:" + String(longitude,6) + "&";
            }
            
            msg = msg + "longitude:" + String(longitude,6) + "&";
            
            latitude = latitude + 0.000001;
            if (latitude>10.0 || latitude<-10.0){
              deci_lat = deci_lat + int(latitude/10);
              latitude = latitude - deci_lat*10;
            }
            if (deci_lat != 0){
              msg = msg + "latitude:" + deci_lat + String(fabs(latitude),6) + "&";
            }
            else
            {
              msg = msg + "latitude:" + String(latitude,6) + "&";
            }
            break;
          case 4 :
            tangage += 0.1;
            msg = msg + "tangage:" + tangage + "&";
            break;
          case 5 :
            gite += 0.1;
            msg = msg + "gite:" + gite + "&";
            break;
          case 6 :
            barre += 0.1;
            msg = msg + "barre:" + barre + "&";
            break;
          case 7 :
            ecoute += 0.1;
            msg = msg + "ecoute:" + ecoute + "&";
            break;
  
        }
      }
      else if (id < 0) {
        //It is a weather station
        type = "M";
        msg = msg + "__" + key + "&type:" + type + "&id_sender:" + id_sender + "&id_dest:" + id_dest + "&id_concern:" + id_concern + "&";
        choice = random(1, 3);
        switch (choice) {
          case 1 :
            vitesse = randomDouble(0.0, 100.0);
            msg = msg + "%svitesse:" + vitesse + "&";
            break;
          case 2 :
            cap = randomDouble(0.0, 100.0);
            msg = msg + "cap:" + cap + "&";
            break;
        }
      }
      msg = msg + key + "//";
      Serial.print(msg);
    }
    //Do nothing, it is the id of the serveur(0)
  }
  else if (mode==2){
    int key = random(1, 999);
    id_sender = 1;
    id_dest = 0;
    id_concern = 1;
    type = "B";
    msg = msg + "__" + key + "&type:" + type + "&id_sender:" + id_sender + "&id_dest:" + id_dest + "&id_concern:" + id_concern + "&";
    longitude = longitude + 0.000001;
    if (longitude>10.0 || longitude<-10.0){
      deci_long = deci_long + int(longitude/10);
      longitude = longitude - deci_long*10;
    }
    if (deci_long != 0){
      msg = msg + "longitude:" + deci_long + String(fabs(longitude),6) + "&";
    }
    else
    {
      msg = msg + "longitude:" + String(longitude,6) + "&";
    }
    
    msg = msg + "longitude:" + String(longitude,6) + "&";
    
    latitude = latitude + 0.000001;
    if (latitude>10.0 || latitude<-10.0){
      deci_lat = deci_lat + int(latitude/10);
      latitude = latitude - deci_lat*10;
    }
    if (deci_lat != 0){
      msg = msg + "latitude:" + deci_lat + String(fabs(latitude),6) + "&";
    }
    else
    {
      msg = msg + "latitude:" + String(latitude,6) + "&";
    }
    msg = msg + key + "//";
    Serial.print(msg);
  }
}

double randomDouble(double minf, double maxf)
{
  return minf + random(1UL << 31) * (maxf - minf) / (1UL << 31);  // use 1ULL<<63 for max double values)
}

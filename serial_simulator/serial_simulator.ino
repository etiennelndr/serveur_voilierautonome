#include <math.h> 

int i,id,id_sender, id_dest, id_concern;
String msg, type;
double vitesse,cap,longitude,latitude,tangage,gite,barre,ecoute;

void setup() {
  // put your setup code here, to run once:
  id=-5;
  Serial.begin(9600);
}

void loop() {
  if(i<=5){
    if (i != 0) {
      if (i < 0) {
        type = "MC";
      }
      else if (i > 0) {
        type = "BC";
      }
      id_sender = i;
      id_dest = 0;
      id_concern = i;
      msg="__255&type:"+ type +"&id_sender:"+ id_sender +"&id_dest:"+ id_dest +"&id_concern:"+ id_concern +"&255//";
      Serial.println(msg);
    }
  }
  else{
    message();
  }
  delay(1000);
  i++;
}

void message() {
  msg="";
  //Make the random really random
  randomSeed(i);
  int key = random(1,999);
  int choice;
  id = random(-5,5);
  id_sender=id;
  id_dest=0;
  id_concern=id;
  if (id != 0) {
    if (id > 0) {
      //It is a boat
      type="B";
      msg=msg+"__"+ key +"&type:"+ type +"&id_sender:"+ id_sender +"&id_dest:"+ id_dest +"&id_concern:"+ id_concern +"&";
      choice = random(1,8);
      switch (choice) {
        case 1 :
          vitesse = randomDouble(0.0,100.0);
          msg = msg + "vitesse:" + vitesse + "&";
          break;
        case 2 :
          cap = randomDouble(0.0,100.0);
          msg = msg + "cap:" + cap + "&";
          break;
        case 3 :
          longitude = randomDouble(0.0,100.0);
          msg = msg + "longitude:" + longitude + "&";
          latitude = randomDouble(0.0,100.0);
          msg = msg + "latitude:" + latitude + "&";
          break;
        case 4 :
          tangage = randomDouble(0.0,100.0);
          msg = msg + "tangage:" + tangage + "&";
          break;
        case 5 :
          gite = randomDouble(0.0,100.0);
          msg = msg + "gite:" + gite + "&";
          break;
        case 6 :
          barre = randomDouble(0.0,100.0);
          msg = msg + "barre:" + barre + "&";
          break;
        case 7 :
          ecoute = randomDouble(0.0,100.0);
          msg = msg + "ecoute:" + ecoute + "&";
          break;
 
      }
    }
    else if (id < 0) {
      //It is a weather station
      type="M";
      msg=msg+"__"+ key +"&type:"+ type +"&id_sender:"+ id_sender +"&id_dest:"+ id_dest +"&id_concern:"+ id_concern +"&";
      choice = random(1,3);
      switch (choice) {
        case 1 :
          vitesse = randomDouble(0.0,100.0);
          msg = msg + "%svitesse:" + vitesse + "&";
          break;
        case 2 :
          cap = randomDouble(0.0,100.0);
          msg=msg+"cap:"+ cap +"&";
          break;
      }
    }
    msg=msg+key+"//";
    Serial.println(msg);
  }
  //Do nothing, it is the id of the serveur(0)
}

double randomDouble(double minf, double maxf)
{
  return minf + random(1UL << 31) * (maxf - minf) / (1UL << 31);  // use 1ULL<<63 for max double values)
}

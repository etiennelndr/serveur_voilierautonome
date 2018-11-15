int i,id,id_sender, id_dest, id_concern;
char* type;
char msg[100];
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
      sprintf(msg,"__255&type:%s&id_sender:%i&id_dest:%i&id_concern:%i&255//",type,id_sender,id_dest,id_concern);
      Serial.println(msg);
    }
    i++;
  }
  else{
    message();
  }
  delay(1000);
}

void message() {
  //Make the random really random
  randomSeed(analogRead(A0));
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
      sprintf(msg,"__%i&type:%s&id_sender:%i&id_dest:%i&id_concern:%i&",key,type,id_sender,id_dest,id_concern);
      choice = random(1,8);
      switch (choice) {
        case 1 :
          vitesse = randomDouble(0.0,100.0);
          sprintf(msg,"%svitesse:%d&",msg,vitesse);
          break;
        case 2 :
          cap = randomDouble(0.0,100.0);
          sprintf(msg,"%scap:%d&",msg,cap);
          break;
        case 3 :
          longitude = randomDouble(0.0,100.0);
          sprintf(msg,"%slongitude:%d&",msg,longitude);
          latitude = randomDouble(0.0,100.0);
          sprintf(msg,"%slatitude:%d&",msg,latitude);
          break;
        case 4 :
          tangage = randomDouble(0.0,100.0);
          sprintf(msg,"%stangage:%d&",msg,tangage);
          break;
        case 5 :
          gite = randomDouble(0.0,100.0);
          sprintf(msg,"%sgite:%d&",msg,gite);
          break;
        case 6 :
          barre = randomDouble(0.0,100.0);
          sprintf(msg,"%sbarre:%d&",msg,barre);
          break;
        case 7 :
          ecoute = randomDouble(0.0,100.0);
          sprintf(msg,"%secoute:%d&",msg,ecoute);
          break;

      }
    }
    else if (id < 0) {
      //It is a weather station
      type="M";
      sprintf(msg,"__%i&type:%s&id_sender:%i&id_dest:%i&id_concern:%i&",key,type,id_sender,id_dest,id_concern);
      choice = random(1,3);
      switch (choice) {
        case 1 :
          vitesse = randomDouble(0.0,100.0);
          sprintf(msg,"%svitesse:%d&",msg,vitesse);
          break;
        case 2 :
          cap = randomDouble(0.0,100.0);
          sprintf(msg,"%scap:%d&",msg,cap);
          break;
      }
    }
    sprintf(msg,"%s%i//",msg,key);
    Serial.println(msg);
  }
  //Do nothing, it is the id of the serveur(0)
}

double randomDouble(double minf, double maxf)
{
  return minf + random(1UL << 31) * (maxf - minf) / (1UL << 31);  // use 1ULL<<63 for max double values)
}

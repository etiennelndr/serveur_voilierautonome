#ifndef BOAT_H
#define BOAT_H


class Message;


/**
 * @brief The Boat class
 */
class Boat {
    public:
        Boat();

        //getters
        float  get_vitesse()        {return vitesse;}
        float  get_cap()            {return cap;}
        float  get_longitude()      {return longitude;}
        float  get_latitude()       {return latitude;}
        float  get_gite()           {return gite;}
        float  get_tangage()        {return tangage;}
        float  get_barre()          {return barre;}
        float  get_ecoute()          {return ecoute;}
        float* get_vitesse_addr()   {return &vitesse;}
        float* get_cap_addr()       {return &cap;}
        float* get_longitude_addr() {return &longitude;}
        float* get_latitude_addr()  {return &latitude;}
        float* get_gite_addr()      {return &gite;}
        float* get_tangage_addr()   {return &tangage;}
        float* get_barre_addr()     {return &barre;}
        float* get_ecoute_addr()     {return &ecoute;}
        int    get_id()             {return id;}

        //setters
        void set_vitesse(float _vitesse)    {vitesse=_vitesse;}
        void set_cap(float _cap)            {cap=_cap;}
        void set_longitude(float _longitude){longitude=_longitude;}
        void set_latitude(float _latitude)  {latitude=_latitude;}
        void set_tangage(float _tangage)    {tangage=_tangage;}
        void set_gite(float _gite)          {gite=_gite;}
        void set_barre(float _barre)        {barre=_barre;}
        void set_ecoute(float _ecoute)        {ecoute=_ecoute;}

        void init(Message m);

    private:
        float vitesse;
        float cap;
        float longitude;
        float latitude;
        float gite;
        float tangage;
        float barre;
        float ecoute;
        int id; //Identifiant du bateau pour la communication des data
};

#endif // BOAT_H

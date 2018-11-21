#ifndef WEATHERSTATION_H
#define WEATHERSTATION_H


class Message;


/**
 * @brief The WeatherStation class
 */
class WeatherStation {
    public:
        WeatherStation(int _id, float _longitude, float _latitude);
        WeatherStation();

        // Getters
        float  get_vitesse();
        float  get_cap();
        float  get_longitude();
        float  get_latitude();
        float* get_vitesse_addr();
        float* get_cap_addr();
        float* get_longitude_addr();
        float* get_latitude_addr();

        // Setters
        void set_vitesse(float _vitesse) ;
        void set_cap(float _cap);
        void set_longitude(float _longitude);
        void set_latitude(float _latitude);

    private:
        int   id;
        float vitesse;
        float cap;
        float latitude;
        float longitude;

};

inline float  WeatherStation::get_vitesse()        { return vitesse; }
inline float  WeatherStation::get_cap()            { return cap; }
inline float  WeatherStation::get_longitude()      { return longitude; }
inline float  WeatherStation::get_latitude()       { return latitude; }
inline float* WeatherStation::get_vitesse_addr()   { return &vitesse; }
inline float* WeatherStation::get_cap_addr()       { return &cap; }
inline float* WeatherStation::get_longitude_addr() { return &longitude; }
inline float* WeatherStation::get_latitude_addr()  { return &latitude; }

//setters
inline void WeatherStation::set_vitesse(float _vitesse)    { vitesse=_vitesse; }
inline void WeatherStation::set_cap(float _cap)            { cap=_cap; }
inline void WeatherStation::set_longitude(float _longitude){ longitude=_longitude; }
inline void WeatherStation::set_latitude(float _latitude)  { latitude=_latitude; }

#endif // WEATHERSTATION_H

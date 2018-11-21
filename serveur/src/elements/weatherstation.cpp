#include "weatherstation.h"

#include "message.h"

/**
 * CONSTRUCTOR
 *
 * @brief WeatherStation::WeatherStation
 */
WeatherStation::WeatherStation(int _id, float _longitude, float _latitude) {
    this->id = _id;
    this->longitude = _longitude;
    this->latitude = _latitude;
}
WeatherStation::WeatherStation() {
    this->id = -1;
    this->longitude = -1.0f;
    this->latitude = -1.0f;
}


#include "weatherstation.h"

#include "message.h"

/**
 * CONSTRUCTOR
 *
 * @brief WeatherStation::WeatherStation
 */
WeatherStation::WeatherStation() {
    // Nothing to do
}

/**
 * METHOD
 *
 * @brief WeatherStation::init : init parameters with a Message object
 * @param m
 */
void WeatherStation::init(Message m) {
    if (m.getIdSender())
        this->id = *m.getIdSender();

    if (m.getVitesse())
        this->vitesse = *m.getVitesse();

    if (m.getCap())
        this->cap = *m.getCap();

    if (m.getLongitude())
        this->longitude = *m.getLongitude();

    if (m.getLatitude())
        this->latitude = *m.getLatitude();
}

#include "boat.h"

#include "message.h"

/**
 * CONSTRUCTOR
 *
 * @brief Boat::Boat
 */
Boat::Boat() {
    // Nothing to do
}

/**
 * METHOD
 *
 * @brief Boat::init : init parameters with a Message object
 * @param m
 */
void Boat::init(Message m) {
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

    if (m.getGite())
        this->gite = *m.getGite();

    if (m.getTangage())
        this->tangage = *m.getTangage();

    if (m.getBarre())
        this->barre = *m.getBarre();

    if (m.getEcoute())
        this->ecoute = *m.getEcoute();
}

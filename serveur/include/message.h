#ifndef MESSAGE_H
#define MESSAGE_H 1

#include <QString>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

class Message {
    public:
        Message();
        ~Message();

        // Encodeur et décodeur pour l'UART et le TCP/IP
        QString encodeData();
        void decodeData(QString msg);

        // Getters
        string* getType();
        int* getIdSender();
        int* getIdDest();
        int* getIdConcern();
        float* getLongitude();
        float* getLatitude();
        float* getCap();
        float* getVitesse();
        float* getGite();
        float* getTangage();
        float* getBarre();
        float* getEcoute();

        // Setters
        void setType(string* t);
        void setIdSender(int* i);
        void setIdDest(int* i);
        void setIdConcern(int* i);
        void setLongitude(float* l);
        void setLatitude(float* l);
        void setCap(float* c);
        void setVitesse(float* v);
        void setGite(float* g);
        void setTangage(float* t);
        void setBarre(float* b);
        void setEcoute(float* e);

        bool getError();

    private:
        // Type (B, M ou S)
        string* type;
        // Id de l'objet qui envoie -> 1, 2, ... pour bateaux, 0 pour serveur,  -1, -2, ... pour stations météos
        int* id_sender;
        // Id de l'objet qui doit recevoir
        int* id_dest;
        // Id de l'objet concerné
        int* id_concern;
        // Position GPS: longitude (du vent ou du bateau)
        float* longitude;
        // Position GPS: latitude (du vent ou du bateau)
        float* latitude;
        // Cap (du vent ou du bateau)
        float* cap;
        // Vitesse (du vent ou du bateau)
        float* vitesse;
        // Gite du bateau
        float* gite;
        // Tangage du bateau
        float* tangage;
        // Barre du bateau
        float* barre;
        // Ecoute du bateau
        float* ecoute;

        // Permet de vérifier si un erreur est apparue lors du décodage d'un message
        bool error;


        // This method is useful to split encoding message
        vector<string> splitMessage(string& data, char delimiter);
        // Used for attribute value assignment
        void assignValueToCorrectAttribute(string& data);
};

inline string* Message::getType() { return type; }
inline int* Message::getIdSender() { return id_sender; }
inline int* Message::getIdDest() { return id_dest; }
inline int* Message::getIdConcern() { return id_concern; }
inline float* Message::getLongitude() { return longitude; }
inline float* Message::getLatitude() { return latitude; }
inline float* Message::getCap() { return cap; }
inline float* Message::getVitesse() { return vitesse; }
inline float* Message::getGite() { return gite; }
inline float* Message::getTangage() { return tangage; }
inline float* Message::getBarre() { return barre; }
inline float* Message::getEcoute() { return ecoute; }
inline bool Message::getError() { return error; }

inline void Message::setType(string* t) { type = t; }
inline void Message::setIdSender(int* i) { id_sender = i; }
inline void Message::setIdDest(int* i) { id_dest = i; }
inline void Message::setIdConcern(int* i) { id_concern = i; }
inline void Message::setLongitude(float* l) { longitude = l; }
inline void Message::setLatitude(float* l) { latitude = l; }
inline void Message::setCap(float* c) { cap = c; }
inline void Message::setVitesse(float* v) { vitesse = v; }
inline void Message::setGite(float* g) { gite = g; }
inline void Message::setTangage(float* t) { tangage = t; }
inline void Message::setBarre(float* b) { barre = b; }
inline void Message::setEcoute(float* e) { ecoute = e; }

#endif // MESSAGE_H

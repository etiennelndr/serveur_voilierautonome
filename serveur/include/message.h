#ifndef MESSAGE_H
#define MESSAGE_H

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

        // Encodeur et décodeur pour l'UART et le TCP/IP
        QString encodeData();
        void decodeData();
        // This method is useful to split encoding message
        vector<string> splitMessage(const string& s, char delimiter);
};

#endif // MESSAGE_H

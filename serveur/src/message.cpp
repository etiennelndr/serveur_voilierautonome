#include "message.h"

// Encodeur et décodeur pour l'UART et le TCP/IP
QString Message::encodeData() {
    // Initialisation de la trame
    string msg = "__&";

    // Type (B, M ou S)
    if (!type) {
        msg += "type_" + *type + "&";
    }
    // Id de l'objet qui envoie -> 1, 2, ... pour bateaux, 0 pour serveur,  -1, -2, ... pour stations météos
    if (!id_sender) {
        msg += "id_sender_" + to_string(*id_sender) + "&";
    }
    // Id de l'objet qui doit recevoir
    if (!id_dest) {
        msg += "id_dest_" + to_string(*id_dest) + "&";
    }
    // Id de l'objet concerné
    if (!id_concern) {
        msg += "id_concern_" + to_string(*id_concern) + "&";
    }
    // Position GPS: longitude (du vent ou du bateau)
    if (!longitude) {
        msg += "longitude_" + to_string(*longitude) + "&";
    }
    // Position GPS: latitude (du vent ou du bateau)
    if (!latitude) {
        msg += "latitude_" + to_string(*latitude) + "&";
    }
    // Cap (du vent ou du bateau)
    if (!cap) {
        msg += "cap_" + to_string(*cap) + "&";
    }
    // Vitesse (du vent ou du bateau)
    if (!vitesse) {
        msg += "vitesse_" + to_string(*vitesse) + "&";
    }
    // Gite du bateau
    if (!gite) {
        msg += "gite_" + to_string(*gite) + "&";
    }
    // Tangage du bateau
    if (!tangage) {
        msg += "tangage_" + to_string(*tangage) + "&";
    }
    // Barre du bateau
    if (!barre) {
        msg += "barre_" + to_string(*barre) + "&";
    }
    // Ecoute du bateau
    if (!ecoute) {
        msg += "ecoute_" + to_string(*ecoute) + "&";
    }

    // Fermeture de la trame
    msg += "__";

    return QString::fromStdString(msg);
}

void Message::decodeData() {

}

vector<string> Message::splitMessage(const string& s, char delimiter) {
   vector<string> tokens;
   string token;
   istringstream tokenStream(s);
   while (getline(tokenStream, token, delimiter)) {
      tokens.push_back(token);
   }
   return tokens;
}

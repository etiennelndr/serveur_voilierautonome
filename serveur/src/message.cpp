#include "message.h"

#include "utils.h"

using std::to_string;
using std::istringstream;

/**
 * CONSTRUCTOR
 *
 * @brief Message::Message : Constructor for Message class
 */
Message::Message() {
    qsrand(uint(QTime::currentTime().msec()));
    error = false;
}

/**
 * DESTRUCTOR
 *
 * @brief Message::~Message : Destructor for Message class
 */
Message::~Message() {
    delete type;
    delete id_sender;
    delete id_dest;
    delete id_concern;
    delete longitude;
    delete latitude;
    delete cap;
    delete vitesse;
    delete gite;
    delete tangage;
    delete barre;
    delete ecoute;
}

/*--------------------------*
 *                          *
 *         METHODS          *
 *                          *
 *--------------------------*/
/**
 * METHOD
 *
 * @brief Message::encodeData : Encodeur pour l'UART et le TCP/IP
 * @return
 */
QString Message::encodeData() {
    // Initialisation de la trame
    string msg = SEPARATOR_DEBUT;
    // Generate a random key and add it to the message
    string key = to_string(qrand() % ((random_high + 1) - random_low) + random_low);
    msg += key;
    // Add a seperator
    msg += "&";

    // Type (B, BC, M, MC ou S)
    if (type) {
        msg += "type" + SEPARATOR + *type + "&";
    }
    // Id de l'objet qui envoie -> 1, 2, ... pour bateaux, 0 pour serveur,  -1, -2, ... pour stations météos
    if (id_sender) {
        msg += "id_sender" + SEPARATOR + to_string(*id_sender) + "&";
    }
    // Id de l'objet qui doit recevoir
    if (id_dest) {
        msg += "id_dest" + SEPARATOR + to_string(*id_dest) + "&";
    }
    // Id de l'objet concerné
    if (id_concern) {
        msg += "id_concern" + SEPARATOR + to_string(*id_concern) + "&";
    }
    // Position GPS: longitude (du vent ou du bateau)
    if (longitude) {
        msg += "longitude" +SEPARATOR + to_string(*longitude) + "&";
    }
    // Position GPS: latitude (du vent ou du bateau)
    if (latitude) {
        msg += "latitude" +SEPARATOR + to_string(*latitude) + "&";
    }
    // Cap (du vent ou du bateau)
    if (cap) {
        msg += "cap" +SEPARATOR + to_string(*cap) + "&";
    }
    // Vitesse (du vent ou du bateau)
    if (vitesse) {
        msg += "vitesse" +SEPARATOR + to_string(*vitesse) + "&";
    }
    // Gite du bateau
    if (gite) {
        msg += "gite" +SEPARATOR + to_string(*gite) + "&";
    }
    // Tangage du bateau
    if (tangage) {
        msg += "tangage" +SEPARATOR + to_string(*tangage) + "&";
    }
    // Barre du bateau
    if (barre) {
        msg += "barre" +SEPARATOR + to_string(*barre) + "&";
    }
    // Ecoute du bateau
    if (ecoute) {
        msg += "ecoute" +SEPARATOR + to_string(*ecoute) + "&";
    }

    // Fermeture de la trame
    msg += key + SEPARATOR_FIN;

    return QString::fromStdString(msg);
}

/**
 * METHOD
 *
 * @brief Message::decodeData : Décodeur pour l'UART et le TCP/IP
 * @param msg
 */
void Message::decodeData(QString msg) {
    // Concert from QString to string
    string data = msg.toStdString();

    // Split the data (for each '&' character we split the data)
    vector<string> splitData = split(data, "&");

    // If we don't have correct symbols at the beginning and the end
    // of the data we MUST return an error
    // Also the message MUST contain an id_sender, an id_concern, an
    // id_dest and a type
    if (verifyMessage(data, splitData[0], splitData[splitData.size()-1])) {
        error = true;
        return;
    }

    // Then assign each value to its attribute
    for (unsigned int i=1; i < splitData.size()-1; i++) {
        assignValueToCorrectAttribute(splitData[i]);
    }
}

/**
 * METHOD
 *
 * @brief Message::verifyMessage : Verify the beginning and the end of the message (separators and key)
 * @param debut
 * @param fin
 * @return
 */
bool Message::verifyMessage(string data, string debut, string fin) {
    return debut.length()                           < 3
        || fin.length()                             < 3
        || debut.substr(0, 2)                       != SEPARATOR_DEBUT
        || fin.substr(fin.length()-2, fin.length()) != SEPARATOR_FIN
        || debut.substr(2, debut.length())          != fin.substr(0, fin.length()-2)
        || data.find("id_sender:")                  == string::npos
        || data.find("id_concern:")                 == string::npos
        || data.find("id_dest:")                    == string::npos
        || data.find("type:")                       == string::npos;
}

/**
 * METHOD
 *
 * @brief Message::assignValueToCorrectAttribute : used for attribute value assignment
 * @param s
 */
void Message::assignValueToCorrectAttribute(string& data) {
    // First of all we need to split the data
    vector<string> dataAndValue = split(data, SEPARATOR);

    if (dataAndValue[0] == "type") {
        type = new string(dataAndValue[1]);
    } else if (dataAndValue[0] == "id_sender") {
        id_sender = new int(stoi(dataAndValue[1]));
    } else if (dataAndValue[0] == "id_dest") {
        id_dest = new int(stoi(dataAndValue[1]));
    } else if (dataAndValue[0] == "id_concern") {
        id_concern = new int(stoi(dataAndValue[1]));
    } else if (dataAndValue[0] == "longitude") {
        longitude = new float(stof(dataAndValue[1]));
    } else if (dataAndValue[0] == "latitude") {
        latitude = new float(stof(dataAndValue[1]));
    } else if (dataAndValue[0] == "cap") {
        cap = new float(stof(dataAndValue[1]));
    } else if (dataAndValue[0] == "vitesse") {
        vitesse = new float(stof(dataAndValue[1]));
    } else if (dataAndValue[0] == "gite") {
        gite = new float(stof(dataAndValue[1]));
    } else if (dataAndValue[0] == "tangage") {
        tangage = new float(stof(dataAndValue[1]));
    } else if (dataAndValue[0] == "barre") {
        barre = new float(stof(dataAndValue[1]));
    } else if (dataAndValue[0] == "ecoute") {
        ecoute = new float(stof(dataAndValue[1]));
    }
}

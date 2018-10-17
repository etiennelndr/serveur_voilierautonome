#include "message.h"

Message::Message() {
    error = false;
}

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

// Encodeur et décodeur pour l'UART et le TCP/IP
QString Message::encodeData() {
    // Initialisation de la trame
    string msg = "__&";

    // Type (B, M ou S)
    if (type) {
        msg += "type" + to_string(SEPARATOR) + *type + "&";
    }
    // Id de l'objet qui envoie -> 1, 2, ... pour bateaux, 0 pour serveur,  -1, -2, ... pour stations météos
    if (id_sender) {
        msg += "id_sender" + to_string(SEPARATOR) + to_string(*id_sender) + "&";
    }
    // Id de l'objet qui doit recevoir
    if (id_dest) {
        msg += "id_dest" + to_string(SEPARATOR) + to_string(*id_dest) + "&";
    }
    // Id de l'objet concerné
    if (id_concern) {
        msg += "id_concern" + to_string(SEPARATOR) + to_string(*id_concern) + "&";
    }
    // Position GPS: longitude (du vent ou du bateau)
    if (longitude) {
        msg += "longitude" + to_string(SEPARATOR) + to_string(*longitude) + "&";
    }
    // Position GPS: latitude (du vent ou du bateau)
    if (latitude) {
        msg += "latitude" + to_string(SEPARATOR) + to_string(*latitude) + "&";
    }
    // Cap (du vent ou du bateau)
    if (cap) {
        msg += "cap" + to_string(SEPARATOR) + to_string(*cap) + "&";
    }
    // Vitesse (du vent ou du bateau)
    if (vitesse) {
        msg += "vitesse" + to_string(SEPARATOR) + to_string(*vitesse) + "&";
    }
    // Gite du bateau
    if (gite) {
        msg += "gite" + to_string(SEPARATOR) + to_string(*gite) + "&";
    }
    // Tangage du bateau
    if (tangage) {
        msg += "tangage" + to_string(SEPARATOR) + to_string(*tangage) + "&";
    }
    // Barre du bateau
    if (barre) {
        msg += "barre" + to_string(SEPARATOR) + to_string(*barre) + "&";
    }
    // Ecoute du bateau
    if (ecoute) {
        msg += "ecoute" + to_string(SEPARATOR) + to_string(*ecoute) + "&";
    }

    // Fermeture de la trame
    msg += "__";

    return QString::fromStdString(msg);
}

void Message::decodeData(QString msg) {
    // Concert from QString to string
    string data = msg.toStdString();

    // Split the data (for each '&' character we split the data)
    vector<string> splitData = splitMessage(data, (char)(*"&"));

    // If we don't have correct symbols at the beginning and the end
    // of the data we MUST return an error
    if (splitData[0] != "__" || splitData[splitData.size()-1] != "__") {
        error = true;
        return;
    }

    // Then assign each value to its attribute
    for (unsigned int i=1; i < splitData.size()-1; i++) {
        assignValueToCorrectAttribute(splitData[i]);
    }
}

/**
 * @brief Message::assignValueToCorrectAttribute : used for attribute value assignment
 * @param s
 */
void Message::assignValueToCorrectAttribute(string& data) {
    // First of all we need to split the data
    vector<string> dataAndValue = splitMessage(data, SEPARATOR);

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

/**
 * @brief Message::splitMessage : this method is useful to split encoding message
 * @param s
 * @param delimiter
 * @return
 */
vector<string> Message::splitMessage(string& data, char delimiter) {
   vector<string> tokens;
   string token;
   istringstream tokenStream(data);
   while (getline(tokenStream, token, delimiter)) {
      tokens.push_back(token);
   }
   return tokens;
}

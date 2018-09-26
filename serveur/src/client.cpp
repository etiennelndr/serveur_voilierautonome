#include "client.h"

ClientTcp::ClientTcp(QString ip) {
	serverPort = 4000; // choix arbitraire (>1024)

	serverIp = ip;
	soc.connectToHost(serverIp, serverPort); // pour se connecter au serveur
}

void ClientTcp::run() {
	QString ligne;
	while(soc.canReadLine()) { 		// tant qu'il y a quelque chose à lire dans la socket
		ligne = soc.readLine();     // on lit une ligne
	}
}
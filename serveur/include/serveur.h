#ifndef SERVEUR_H
#define SERVEUR_H 1


#include <QObject>
#include <QtGui>
#include <QtNetwork>
#include <QString>
#include <iostream>

#include "message.h"

using namespace std;

class ServeurTcp : public QTcpServer {
    Q_OBJECT
    public:
        ServeurTcp(quint16 port);
		~ServeurTcp();
		void envoyerATous(const QString &message);
        void envoyerATousSauf(const QString &message, const QTcpSocket* client);
	private slots:
		void demandeConnexion();
		void donneesRecues();
		void deconnexionClient();
    private:
	    QList<QTcpSocket *> clients;
		quint16 tailleMessage;
};


#endif // !SERVEUR_H

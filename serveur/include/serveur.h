#ifndef SERVEUR_H
#define SERVEUR_H


#include <QObject>
#include <QtGui>
#include <QtNetwork>
#include <QString>
#include <QtConcurrentRun>
#include <iostream>

using namespace std;

class ServeurTcp : public QTcpServer {
    Q_OBJECT
    public:
	    ServeurTcp(int port);
		~ServeurTcp();
		void envoyerATous(const QString &message);
	private slots:
		void demandeConnexion();
		void donneesRecues();
		void deconnexionClient();
    private:
	    QList<QTcpSocket *> clients;
		quint16 tailleMessage;
};


#endif // !SERVEUR_H
Voilier autonome : Serveur
==========================

Introduction
------------

Développement d'un serveur pour la gestion d'un voilier autonome.


Téléchargement du dépôt
-----------------------

```
git clone https://github.com/etiennelndr/serveur_voilierautonome.git
```

Logiciels à télécharger
-----------------------

Afin de pouvoir utiliser correctement cette partie du projet vous devez télécharger **Qt 5.12** ainsi que **QtCreator** 
qui sont disponibles [ici](https://www.qt.io/download).

De plus, afin de pouvoir lancer la simulation vous devez télécharger **Arduino** qui est téléchargeable à cette [adresse](https://www.arduino.cc/en/main/software).


Lancement du serveur
--------------------

Pour lancer le serveur il vous suffit d'exécuter le programme QtCreator et d'ouvrir le fichier **serveur.pro** présent dans
le dépôt GitHub que vous venez de cloner en local. Suite à cela, vous n'avez plus qu'à exécuter QMake, à compiler et à lancer
le programme. N'oubliez pas de **lancer la simulation Arduino** afin de pouvoir recevoir des trames UART.

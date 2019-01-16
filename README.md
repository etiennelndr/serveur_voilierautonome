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


Lancement de la simulation Arduino
----------------------------------
Cette simulation permet d'envoyer des trames UART au serveur. Ces trames permettent de simuler des données venant des
différentes stations météo ou des bateaux.
Afin d'utiliser correctement cette simulation vous devez lancer le logiciel Arduino précédemment téléchargé et ouvrir le code 
**serial_simulator/serial_simulator.ino** présent dans ce dépôt. Suite à cela, vous devez vérifier puis téléverser le code
en vérifiant auparavant que votre carte Arduino est bien branchée et que le bon port COM est utilisé par le logiciel. Après cela,
cliquez sur **Outils > Moniteur série** (Ctrl + Maj + M), tapez la lettre "r" et faites "Entrée". La simulation est démarrée : vous 
pouvez désormais fermer le moniteur série et retourner sur le programme du serveur afin de le lancer.

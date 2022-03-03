# Projet Cours de Réseau
## Julian BARKOUDEH et Camille DOUZET EI2I3 II

### Objectif du projet
L'objectif du projet est d'implémenter une application permettant de gérer des comptes bancaires en utilisant une architecture client-serveur.

### Rappels des différentes fonctionnalités
Chaque client peut avoir un ou plusieurs comptes bancaires (jusqu'à 3 dans notre cas)
Tous les comptes sont déjà crées au préalable.
Vous pouvez consulter la liste des clients et comptes actifs un peu plus bas.
Vous pouvez effectuer 4 types d'opérations :
    1. Faire un **ajout** : Ajouter une somme dans le compte que vous aurez choisi
    2. Faire un **retrait** : Debiter un montant dans le compte voulu
    3. Obtenir le **solde** de votre compte.
    4. Obtenir les 10 dernières **opérations** du client
Le serveur vous renverra les réponses à vos requêtes.

### Comment est organisé le projet ?
Il y a 3 scripts principaux :
- **server.c** : Contient le code utile pour la création des sockets et de la communication avec le protocole TCP
- **client.c** : Contient le code nécessaire pour établir la connexion avec le serveur
- **communication.c** : Fonctions utiles pour le script server.c
- **communication.h** : Structures et Prototypes des fonctions utilisées dans server.c
Il y a aussi un **makefile** pour facilité la compilation du projet

### Comment exécuter le code ?
A mettre a jour !

1. Se placer dans le dossier du projet
2. Faire un `make` dans un premier terminal puis executé la ligne `./a.out`
3. Ouvrir un 2e terminal et executer les deux commandes : 
    - `gcc client.c -o client`
    - `./client`
Normalement la connection s'établie correctement.

### Récapitulatif des clients et comptes existants
- client 1 :
identifiant : julian
mot de passe : 1234
état des comptes :
    - compte 1 : ...
    - compte 2 : ...
    - compte 3 : ...

- client 2 :
identifiant : camille
mot de passe : 1234
état des comptes :
    - compte 1 : ...
    - compte 2 : ...
    - compte 3 : ...

- client 3 :
identifiant : douzet
mot de passe : 1234
état des comptes :
    - compte 1 : ...
    - compte 2 : ...
    - compte 3 : ...

### Les étapes à suivre pour effectuer une action 
A faire
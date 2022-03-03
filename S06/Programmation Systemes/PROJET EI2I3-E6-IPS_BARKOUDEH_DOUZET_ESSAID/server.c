/* PROJET Programmation Système
Julian - Camille - Oumeima 
21/06/2021
*/
// Code Serveur 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <netdb.h>
#include <arpa/inet.h>

struct _client // Structure des coordonnées d'un client 
{
    char ipAddress[40];
    int port;
    char name[40];
} tcpClients[4];

int nbClients; 
int fsmServer;
int deck[13]={0,1,2,3,4,5,6,7,8,9,10,11,12};  
int tableCartes[4][8]; 
char *nomcartes[]=
{"Sebastian Moran", "irene Adler", "inspector Lestrade",
  "inspector Gregson", "inspector Baynes", "inspector Bradstreet",
  "inspector Hopkins", "Sherlock Holmes", "John Watson", "Mycroft Holmes",
  "Mrs. Hudson", "Mary Morstan", "James Moriarty"};
int joueurCourant;
int joueurEchec[4]; //Tableau des "flag" = 1 quand un joueur a échoué dans l'accusation 
void error(const char *msg)
{
    perror(msg);
    exit(1);
}

void melangerDeck()
{
    int i;
    int index1,index2,tmp;

    for (i=0;i<1000;i++)
    {
        index1=rand()%13;
        index2=rand()%13;

        tmp=deck[index1];
        deck[index1]=deck[index2];
        deck[index2]=tmp;
    }
}

void createTable()
{
	// Le joueur 0 possede les cartes d'indice 0,1,2
	// Le joueur 1 possede les cartes d'indice 3,4,5
	// Le joueur 2 possede les cartes d'indice 6,7,8
	// Le joueur 3 possede les cartes d'indice 9,10,11
	// Le coupable est la carte d'indice 12
	int i,j,c;

	for (i=0;i<4;i++)
		for (j=0;j<8;j++)
			tableCartes[i][j]=0;

	for (i=0;i<4;i++) // Parcourir les clients 
	{
		for (j=0;j<3;j++) // Parcourir les cartes 
		{
			c=deck[i*3+j]; // Lecture de la carte du joueur 
			switch (c)
			{
				case 0: // Sebastian Moran
					tableCartes[i][7]++;
					tableCartes[i][2]++;
					break;
				case 1: // Irene Adler
					tableCartes[i][7]++;
					tableCartes[i][1]++;
					tableCartes[i][5]++;
					break;
				case 2: // Inspector Lestrade
					tableCartes[i][3]++;
					tableCartes[i][6]++;
					tableCartes[i][4]++;
					break;
				case 3: // Inspector Gregson
					tableCartes[i][3]++;
					tableCartes[i][2]++;
					tableCartes[i][4]++;
					break;
				case 4: // Inspector Baynes
					tableCartes[i][3]++;
					tableCartes[i][1]++;
					break;
				case 5: // Inspector Bradstreet
					tableCartes[i][3]++;
					tableCartes[i][2]++;
					break;
				case 6: // Inspector Hopkins
					tableCartes[i][3]++;
					tableCartes[i][0]++;
					tableCartes[i][6]++;
					break;
				case 7: // Sherlock Holmes
					tableCartes[i][0]++;
					tableCartes[i][1]++;
					tableCartes[i][2]++;
					break;
				case 8: // John Watson
					tableCartes[i][0]++;
					tableCartes[i][6]++;
					tableCartes[i][2]++;
					break;
				case 9: // Mycroft Holmes
					tableCartes[i][0]++;
					tableCartes[i][1]++;
					tableCartes[i][4]++;
					break;
				case 10: // Mrs. Hudson
					tableCartes[i][0]++;
					tableCartes[i][5]++;
					break;
				case 11: // Mary Morstan
					tableCartes[i][4]++;
					tableCartes[i][5]++;
					break;
				case 12: // James Moriarty
					tableCartes[i][7]++;
					tableCartes[i][1]++;
					break;
			}
		}
	}
}

//Focntion d'affichage des cartes 
void printDeck()
{
  int i,j;

  for (i=0;i<13;i++)
          printf("%d %s\n",deck[i],nomcartes[deck[i]]);

	for (i=0;i<4;i++)
	{
		for (j=0;j<8;j++)
			printf("%2.2d ",tableCartes[i][j]);
		puts("");
	}
}
//Fonction d'affichage des informations d'un client 
void printClients()
{
    int i;

    for (i=0;i<nbClients;i++)
      printf("%d: %s %5.5d %s\n",i,tcpClients[i].ipAddress,
        tcpClients[i].port,
        tcpClients[i].name);
}
//Fonction envoie l'indice d'un client dans le table cartes par son nom 
int findClientByName(char *name) 
{
        int i;

        for (i=0;i<nbClients;i++)
                if (strcmp(tcpClients[i].name,name)==0)
                        return i;
        return -1;
}
// Fonction d'envoie des meessages au client sur le thread créé 
void sendMessageToClient(char *clientip, int clientport,char *mess)
{
    //Création des sockets   
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[256]; // buffer d'envoie 

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    server = gethostbyname(clientip);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(clientport);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
        {
                printf("ERROR connecting\n");
                exit(1);
        }

        sprintf(buffer,"%s\n",mess);
        n = write(sockfd,buffer,strlen(buffer)); //Fonction write permettant d'envoyer le message par les paramètres créés

    close(sockfd); // On ferme le socket 
}
//Fonction envoie le même message à tous les clients 
void broadcastMessage(char *mess)
{
    int i;

    for (i=0;i<nbClients;i++)
            sendMessageToClient(tcpClients[i].ipAddress, tcpClients[i].port, mess);
}

int main(int argc, char *argv[])
{
    //Structure des sockets   
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[256];   // Buffer dees messages recus par les clients 
    struct sockaddr_in serv_addr, cli_addr;
    int n;
	  int i;

    char com;
    char clientIpAddress[256], clientName[256];
    int clientPort;
    int id;
    char reply[256];
    int fin_jeu = 0;

     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0); // creation du socket
     if (sockfd < 0)
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) // dis tout ce qui viens sur mon port, c'est mon port
              error("ERROR on binding");
     listen(sockfd,5);// ouverture et début de l'écoute pour receptionner les messages
     clilen = sizeof(cli_addr);

	printDeck();
	melangerDeck();
	createTable();
	printDeck();
	joueurCourant=0; 

    // Boucle d'initialisation du tableau des structurs clients conetnants tous ses coordonnées 
	for (i=0;i<4;i++)
	{
        	strcpy(tcpClients[i].ipAddress,"localhost");
        	tcpClients[i].port=-1;
        	strcpy(tcpClients[i].name,"-");
	}
    while (1)
    {
     	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
     	if (newsockfd < 0) // Echec de connexion avec le client 
          	error("ERROR on accept");

     	bzero(buffer,256); // Vider le buffer des messages 
     	n = read(newsockfd,buffer,255); // Variable permettant de detecter un problème lors de la reception des messages 
     	if (n < 0)
		    error("ERROR reading from socket");

        printf("Received packet from %s:%d\nData: [%s]\n\n", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port), buffer);
        int Joueur, Coupable, Objet, JoueurSlect;
        // Envoie des messages aux clients 
        if (fsmServer==0)
        {
        	switch (buffer[0])
        	{
            	case 'C':
              	sscanf(buffer,"%c %s %d %s", &com, clientIpAddress, &clientPort, clientName);
              	printf("COM=%c ipAddress=%s port=%d name=%s\n",com, clientIpAddress, clientPort, clientName);

            	   // fsmServer==0 alors j'attends les connexions de tous les joueurs
                strcpy(tcpClients[nbClients].ipAddress,clientIpAddress);
                tcpClients[nbClients].port=clientPort;
                strcpy(tcpClients[nbClients].name,clientName);
                nbClients++;

                printClients();

                // rechercher l'id du joueur qui vient de se connecter
                id=findClientByName(clientName);
                printf("id=%d\n",id);

                // lui envoyer un message personnel pour lui communiquer son id
                sprintf(reply,"I %d",id);
                sendMessageToClient(tcpClients[id].ipAddress, tcpClients[id].port, reply);

        				// Envoyer un message broadcast pour communiquer a tout le monde la liste des joueurs actuellement
         				// connectes
                sprintf(reply,"L %s %s %s %s", tcpClients[0].name, tcpClients[1].name, tcpClients[2].name, tcpClients[3].name);
                broadcastMessage(reply);

                // Si le nombre de joueurs atteint 4, alors on peut lancer le jeu
                if (nbClients==4)
		            {
        					// On envoie ses cartes au joueur 0, ainsi que la ligne qui lui correspond dans tableCartes
                  sprintf(reply, "D %d %d %d", deck[0], deck[1], deck[2]); // Distribution des cartes : Case D 
                  sendMessageToClient(tcpClients[0].ipAddress, tcpClients[0].port, reply); // Envoie du message dans le buffer "replay", avec les paramètres créés
                  // Construire le tableau des cartes
                  for (int i = 0; i < 8; i++) {  
                    sprintf(reply, "V %d %d %d", 0, i, tableCartes[0][i]); // On envoie au client 0  la valeur des cartes  : Case V
                    sendMessageToClient(tcpClients[0].ipAddress, tcpClients[0].port, reply); // Envoie du message dans le buffer "replay", avec les paramètres créés
                  }

        					// On envoie ses cartes au joueur 1, ainsi que la ligne qui lui correspond dans tableCartes
                  sprintf(reply, "D %d %d %d", deck[3], deck[4], deck[5]); // Distribution des cartes : Case D
                  sendMessageToClient(tcpClients[1].ipAddress, tcpClients[1].port, reply);
                  for (int i = 0; i < 8; i++) {
                    sprintf(reply, "V %d %d %d", 1, i, tableCartes[1][i]);// On envoie au client 1  la valeur des cartes  : Case V
                    sendMessageToClient(tcpClients[1].ipAddress, tcpClients[1].port, reply);
                  }

        					// On envoie ses cartes au joueur 2, ainsi que la ligne qui lui correspond dans tableCartes
                  sprintf(reply, "D %d %d %d", deck[6], deck[7], deck[8]);
                  sendMessageToClient(tcpClients[2].ipAddress, tcpClients[2].port, reply);
                  for (int i = 0; i < 8; i++) {
                    sprintf(reply, "V %d %d %d", 2, i, tableCartes[2][i]);
                    sendMessageToClient(tcpClients[2].ipAddress, tcpClients[2].port, reply);
                  }

        					// On envoie ses cartes au joueur 3, ainsi que la ligne qui lui correspond dans tableCartes
                  sprintf(reply, "D %d %d %d", deck[9], deck[10], deck[11]);
                  sendMessageToClient(tcpClients[3].ipAddress, tcpClients[3].port, reply);
                  for (int i = 0; i < 8; i++) {
                    sprintf(reply, "V %d %d %d", 3, i, tableCartes[3][i]);
                    sendMessageToClient(tcpClients[3].ipAddress, tcpClients[3].port, reply);
                  }

        					// On envoie enfin un message a tout le monde pour definir qui est le joueur courant=0
                  sprintf(reply, "M %d", joueurCourant); // Activation du bouton go pour le joueur courant  : case M 
                  broadcastMessage(reply); // Envoie du message à tous les clients 
                  fsmServer=1;
		            }
		            break;
          }
	     }
        // Réception des messages des clients 
      else if (fsmServer==1)
      {
        	switch (buffer[0])
        	{
                case 'G': // Acussation d'un coupable  
                    sscanf(buffer,"G %d %d", &Joueur, &Coupable); // Récuperer le message envoyé par le client  : Numéro de client et le numéro de coupable 
                    printf("pour gagner : %d\n", deck[12]);
                    if (Coupable == deck[12]) { // Le joueur a bien deviné le coupable 
                      sprintf(reply, "W %d %s",Joueur, tcpClients[Joueur].name); // Annoncer le joueur gagnant 
                      broadcastMessage(reply); // Envoie de ce message à tous les clients 
                      fin_jeu = 1; // Le jeu se termine 
                    }
                    else { // Le joueur a échoué 
                      joueurEchec[Joueur] = 1; // Mettre à jour le tableau des joueurs perdants 
                      sprintf(reply,"E"); // Envoyer au joueur qu'il a échoué  : cas E 
                      sendMessageToClient(tcpClients[Joueur].ipAddress, tcpClients[Joueur].port, reply); // Envoie du message 
                    }
                    break;
                case 'O': // Le joueur demande des objets 
                    sscanf(buffer, "O %d %d", &Joueur, &Objet); // Récuperer l'indice de joueur ainsi que l'objet demandé 
                    for(int i = 0; i < 4; i++){ // Parcourir les joueurs sauf le joueur qui a envoyé la demande 
                      if(i != Joueur){ 
                        if(tableCartes[i][Objet] != 0){
                          sprintf(reply, "V %d %d %d != 0", i, Objet, 100); // On envoie la valeur 100 (pour afficher une *) quand on a trouvé l'objet avec un des joueurs d'indice i
                          for(int j = 0; j < 4; j++){
                            if(j != i){
                            sendMessageToClient(tcpClients[j].ipAddress, tcpClients[j].port, reply); // On envoie cette réponse aux joueurs( y compris le demandeur) sauf au joueur d'indice i 
                            }
                          }
                        }
                        else { // L'objet n'a pas été trouvé avec le joueur d'indice i
                          sprintf(reply, "V %d %d %d != 0", i, Objet, 0); //On envoie la valeur 0 à tous les joueurs (y compris le joueur i car cela ne changera rien)
                          broadcastMessage(reply);
                        }
                      }
                    }
                		break;
        		    case 'S': // Le joueur demande des objets à un autre joueur
              			sscanf(buffer,"S %d %d %d", &Joueur, &JoueurSlect, &Objet); // Récuperer le numéro du joueur, le numéro de joueur à demander et l'objet demandé 
                    sprintf(reply, "V %d %d %d", JoueurSlect, Objet, tableCartes[JoueurSlect][Objet]); //On envoie la valeur de l'objet du joueur à demander 
                    broadcastMessage(reply); // On envoie la réponse à tous les joueurs (y compirs le joueur qui a été demandé car cela ne changera pas son tableau)
              			break;
                default:
                    break;
        	}
          // Choisir le joueur pour le prochain tour 
          int i = 0;
          while(i < nbClients){
            i++;
            if (joueurCourant == 3) // Si le joueur 3 a été le joueur courant on reintialise la variable joueurCourant
              joueurCourant = 0;
            else
              joueurCourant++; // On choisit le joueur d'après sinon 
            if(joueurEchec[joueurCourant]!=1){ // On verifit si le joueur "joueurCourant + 1 " n'a pas déjà perdu
              sprintf(reply, "M %d", joueurCourant); 
              broadcastMessage(reply); // Envoie aux joueurs à qui sera le procahain tour  : le joueur avec le même indice que la varabiale "joueurCourant"
              break;
            }
          }
          if(i >= nbClients && joueurEchec[joueurCourant] == 1) { // On vérifie si tous les clients ont déjà perdus .
            sprintf(reply, "W %d %s",nbClients+1,"-");// Aucun joueur a gagné 
            broadcastMessage(reply);                 
            fin_jeu = 1; // On termine le jeu 
          }
        if(fin_jeu){ // Si le jeu a été terminé 
          fsmServer = 0; // Réinitialiser le jeu 
          for( int i = 0; i <nbClients; i++){ 
           bzero((struct _client *) &tcpClients[i], sizeof(tcpClients[i])); // Vider les structures de tous les clients 
          }
          nbClients = 0;
        }
      }
     	close(newsockfd);
    }

     close(sockfd);
     return 0;
}

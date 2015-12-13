/*!
  Documentation
  * \file client.hpp
  *  \brief Ce fichier contient les différentes fonctionnalités du client
   * \author CAMARA Mamadou
   */
#ifndef CLIENT_H
#define CLIENT_H
#include "socket.hpp"

//Data structures
#include "addr_map.hpp"
#include <vector>

//Class
#include "AddrStorage.hpp"
#include "Converter.hpp"
//#include "Datagram.hpp"
#include "Exception.hpp"
#include "File.hpp"
//#include "State.hpp"
//#include "Counter.hpp"
//#include "library.hpp"

#define	MAXLEN	1024

using namespace std;
class  Client
{
 private :
 string config;
 AddrStorage monaddr;
 protected :
  int sock4;
  int sock6;
  char login[MAXLEN];

// functions
//void usage (char *);
//void raler (char *);
  public :
  /*!
    * Constructeur
    */
  Client(string config);
  /*!
    * Destructeur
    */
 ~Client();
/*!
 * serverId :retourne identite des serveurs d'un canal dans la struct sockaddr
 */
 
void  channelId(char * ,const AddrStorage & );
/*!
  * Famille de socket qui a été faites
  */
int mySocket();
 /*!
  * logTo abonnement aux serveurs du canal
  */
  void logTo(const AddrStorage &);
/*!
 * sendTo Envoi des messages au server du canal
 */ 
 void sendTo(const AddrStorage &,char *  );
/*! 
  * recvfrom reçoit et affiche les messages 
  */
void recvFrom(AddrStorage,char *);
AddrStorage  monAdresse();
/*const struct sockaddr_in & addrIn();
const struct sockaddr_in6 & addrIn6();
//string charAdresse();*/
};
typedef enum 
{
    CONNECTER,
    LEAVE,
} ETAT;
typedef struct  canal_comunication
{   
    char * nom ;
    AddrStorage  clients[MAXSOCK];
    AddrStorage serveur;
} CANAL;
#endif


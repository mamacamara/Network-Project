#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include<netinet/in.h>
#include <arpa/inet.h>

#define LG_MESSAGE 256

void raler(char *message)
{
  perror(message);
  exit(-1);
}

int main()
{
  int descripteurSocket, descripteurBind ;
  struct sockaddr_in pointDeRencontreLocal;
  struct sockaddr_in pointDeRencontreDistant;
  socklen_t longueurAdresse;
  char messageEnvoi[LG_MESSAGE];
  int ecrits;
  int retour; 


  descripteurSocket = socket(PF_INET,SOCK_DGRAM,0);
  if (descripteurSocket  < 0)
    raler("Socket non créée");
  printf("Socket créée avec succès ! %d\n", descripteurSocket);
  longueurAdresse = sizeof( struct sockaddr_in);
  memset(&pointDeRencontreLocal,0x00,longueurAdresse);
  pointDeRencontreLocal.sin_family = PF_INET;
  pointDeRencontreLocal.sin_addr.s_addr = htonl(INADDR_ANY);
  pointDeRencontreLocal.sin_port = htons(0);
  descripteurBind = bind(descripteurSocket,(struct sockaddr*)& pointDeRencontreLocal,longueurAdresse);
  if (descripteurBind < 0)
    raler("Bind non fait");
  printf("Socket attachée avec succès ! \n");
  longueurAdresse = sizeof(pointDeRencontreDistant);
  memset(&pointDeRencontreDistant,0x00,longueurAdresse);
  pointDeRencontreDistant.sin_family = PF_INET;
  pointDeRencontreDistant.sin_port   = htons(IPPORT_USERRESERVED);
  inet_aton("198.168.52.2",&pointDeRencontreDistant.sin_addr);
  memset(messageEnvoi,0x00,LG_MESSAGE*sizeof(char));
  sprintf(messageEnvoi,"Hello world  ! \n");
  ecrits = sendto(descripteurSocket,messageEnvoi,strlen(messageEnvoi),0,
      (struct sockaddr *)&pointDeRencontreDistant,longueurAdresse);
  switch (ecrits)
  {
    case -1 : 
      raler("sendto non reussi");
      close(descripteurSocket);
      return 0;
    case 0 :
      fprintf(stderr,"Aucune donnée n'a été envoyée ! \n\n");
      close(descripteurSocket);
      return 0;
    default :
      if (ecrits != strlen(messageEnvoi))
        fprintf(stderr,"Erreur dans l'envoi des données! \n\n");
    else
      printf("Message %s envoyé avec succès (%d octets)\n\n",messageEnvoi,ecrits);
  }
   
  close (descripteurSocket);
  return 0;
}



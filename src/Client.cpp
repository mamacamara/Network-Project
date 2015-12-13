#include "Client.hpp"
#include <string.h>


#define MAXLEN 1024

/*void usage (char *argv0)
  {
  fprintf (stderr, "usage: %s addr [port]\n", argv0) ;
  exit (1) ;
  }

  void raler (char *msg)
  {
  perror (msg) ;
  exit (1) ;
}*/
//Canal de comunication 

Client::Client(string config)
{
    File conf(config);

    int i = 1;
    string line = "end";
    string a,p;
    //ssize_t fr;
  // login = (char*) malloc( 1024);
   cout<<"Your login please?\n";
   fgets(login,MAXLEN,stdin);
    while((line = conf.read(i)) != "end")
    {
        char delim =' ';
        vector<string> v = Converter::split(line,delim);

        if(v.size()==2)
        {
            string a = v[0];
            string p = v[1];

            //Convert
            //hostname->ip
            const char *hostname = Converter::stocs(a);
            struct addrinfo hints, *res;
            struct in_addr tmp;

            memset(&hints, 0, sizeof(hints));
            hints.ai_socktype = SOCK_DGRAM;
            hints.ai_family = AF_INET;

            if(getaddrinfo(hostname, NULL, &hints, &res)!=0)
            {
                throw (Exception("Unable to find this server ("+a+")",__LINE__));
            }

            tmp.s_addr = ((struct sockaddr_in *)(res->ai_addr))->sin_addr.s_addr;

            freeaddrinfo(res);


            a = inet_ntoa(tmp);
            //end
            //convert

            AddrStorage addr(a,p);
            monaddr =addr;
//            State s(DISCONNECT);

            //_server_map[addr] = s;
      }
     else throw (Exception("There is a mistake in server.cfg",__LINE__));

        i++;
    }

    // Create socket listening IPv4
    sock4 = socket(AF_INET, SOCK_DGRAM, 0);

    // Create socket listening IPv6
    sock6 = socket(AF_INET6, SOCK_DGRAM, 0);
    cout<<"mon adresse est "<<monaddr<<"\n";
}
Client::~Client()
{
    close(sock4);
    close(sock6);
 //   free(login);
}
void Client::channelId(char * cnal,const AddrStorage & addr)
{
    int soket  = mySocket();
    /*char  msg[] = "Identité des serveurs sur le canal";
    char *  message = NULL;
    strcpy(message,msg);
    strcat(message,cnal.nom);*/
    struct sockaddr * saddr = addr.sockaddr();
    socklen_t salong = addr.len();
    int longu = strlen(cnal);
   int rq =  sendto(soket, cnal, longu, 0,  saddr, salong);
   if( rq < 0)
       cout<<"Error request from Channel Id\n";
    
}   
/*   {

   struct sockaddr_in *sadr4 = (struct sockaddr_in *) &sadr ;
   struct sockaddr_in6 *sadr6 = (struct sockaddr_in6 *) &sadr ;
   char *padr = NULL ;
   int s, r, family, port = 0 ;
   char buf [MAXLEN] ;
   struct sockaddr_storage sadr ;
   struct sockaddr_in *sadr4 = (struct sockaddr_in *) &sadr ;
   struct sockaddr_in6 *sadr6 = (struct sockaddr_in6 *) &sadr ;
   socklen_t salong ;
   char *padr = NULL ;
   int s, r, family, port = 0, o ;
   char buf [MAXLEN] ;

   memset (&sadr, 0, sizeof sadr) ;

   padr = argv [1] ;
   port = 9000 ;
   padr = argv [1] ;
   port = atoi (argv [2]) ;

   port = htons (port) ;

   if (inet_pton (AF_INET6, padr, & sadr6->sin6_addr) == 1)
   {
   family = PF_INET6 ;
   sadr6->sin6_family = AF_INET6 ;
   sadr6->sin6_port = port ;
   salong = sizeof *sadr6 ;
   }
   else if (inet_pton (AF_INET, padr, & sadr4->sin_addr) == 1)
   {
   family = PF_INET ;
   sadr4->sin_family = AF_INET ;
   sadr4->sin_port = port ;
   salong = sizeof *sadr4 ;
   }
   else
   {
   fprintf (stderr, "%s: adresse '%s' non reconnue\n", argv [0], padr) ;
   exit (1) ;
   }

   s = socket (family, SOCK_DGRAM, 0) ;
   if (s == -1) raler ("socket") ;

   o = 1 ;
   setsockopt (s, SOL_SOCKET, SO_BROADCAST, &o, sizeof o) ;

   while ((r = read (0, buf, MAXLEN)) > 0)
   {
   r = sendto (s, buf, r, 0, (struct sockaddr *) &sadr, salong) ;
   if (r == -1) raler ("sendto") ;
   }
   if (r == -1) raler ("read") ;

   close (s) ;

   exit (0) ;
   }*/
int Client::mySocket()
{
AddrStorage addr = monaddr;
    int res = -1;
    switch(addr.family())
    {
        case AF_INET :
            res = sock4;
            break;
        case AF_INET6 :
            res = sock6;
            break;
        default :
            throw (Exception("Bad family definition.", addr, __LINE__));
            break;
    }
    return res;
}
// Abonne   au serveur du canal
void Client::logTo(const AddrStorage & addr)
{
    int socket = addr.sock();
    if (socket < 0){
        perror("socket non créé pour ce canal");
        exit(-1);
    }
}
// envoi un message au serveur de canal
void Client::sendTo(const  AddrStorage & addr, char * buf)
{   
    int r, socket = mySocket();
    struct sockaddr * saddr = addr.sockaddr();
  // char buf [MAXLEN] ;
    char * buff = new char [MAXLEN];
    buf = new char [MAXLEN];
    socklen_t salong = addr.len();
    cout<<"Message à envoyer ?\n";
    fgets(buff,MAXLEN,stdin);
    cout<<"Message Saisi  "<<buff<<"\n";
    r = sendto(socket, buff, MAXLEN, 0,  saddr, salong) ;
    if(r<0)
        throw (Exception("send_to : Failed", __LINE__));
    strcpy(buf,buff);
    delete [] buff;
        
    
}
void Client::recvFrom(AddrStorage addr, char buf[])
{
    struct sockaddr_storage * sonadr = addr.storage();
    socklen_t salong = addr.len(); 
    int r, af , socket = mySocket();
    void *nadr ;            /* au format network */
    char padr [INET6_ADDRSTRLEN] ;  /* au format presentation */
    char * buffer = (char*)malloc(1024);
    buf = (char*)malloc(1024);
    
    r = recvfrom (socket, buffer, MAXLEN, 0, (struct sockaddr *) &sonadr, &salong) ;
    if(r==-1)
        throw (Exception("send_to : Failed", __LINE__));
    strcpy(buf,buffer);
    free(buffer);
    
    af = ((struct sockaddr *) &sonadr)->sa_family ;
    switch (af)
    {
        case AF_INET :
            nadr = & ((struct sockaddr_in *) &sonadr)->sin_addr ;
            break ;
        case AF_INET6 :
            nadr = & ((struct sockaddr_in6 *) &sonadr)->sin6_addr ;
            break ;
    }
    inet_ntop (af, nadr, padr, sizeof padr) ;
   printf ("%s: Message de  recu  de  %s\n", buf, padr) ;
   
}
AddrStorage Client::monAdresse()
{
    return monaddr;
}









































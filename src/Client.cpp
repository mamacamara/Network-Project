#include "Client.hpp"
#include <string.h>

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
Client::Client(string config)
{
    File conf(config);

    int i = 1;
    string line = "end";
    string a,p;

    while((line = conf.read(i)) != "end")
    {
      char delim = ' ';
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
        State s(DISCONNECT);

        //_server_map[addr] = s;
      }
      else throw (Exception("There is a mistake in server.cfg",__LINE__));

      i++;
    }

    // Create socket listening IPv4
    sock4 = socket(AF_INET, SOCK_DGRAM, 0);

    // Create socket listening IPv6
    sock6 = socket(AF_INET6, SOCK_DGRAM, 0);
  }

 /* void serverId(char* channel,struct sockaddr adr)
  {

    struct sockaddr_in *sadr4 = (struct sockaddr_in *) &sadr ;
    struct sockaddr_in6 *sadr6 = (struct sockaddr_in6 *) &sadr ;
    char *padr = NULL ;
    int s, r, family, port = 0, o ;
    char buf [MAXLEN] ;
    int main (int argc, char *argv [])
    {
      struct sockaddr_storage sadr ;
      struct sockaddr_in *sadr4 = (struct sockaddr_in *) &sadr ;
      struct sockaddr_in6 *sadr6 = (struct sockaddr_in6 *) &sadr ;
      socklen_t salong ;
      char *padr = NULL ;
      int s, r, family, port = 0, o ;
      char buf [MAXLEN] ;

      memset (&sadr, 0, sizeof sadr) ;

      switch (argc)
      {
        case 2 :
          padr = argv [1] ;
          port = 9000 ;
          break ;
        case 3 :
          padr = argv [1] ;
          port = atoi (argv [2]) ;
          break ;
        default :
          usage (argv [0]) ;
      }

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

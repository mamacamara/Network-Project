#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define	MAXLEN	1024

void usage (char *argv0)
{
    fprintf (stderr, "usage: %s addr [port]\n", argv0) ;
    exit (1) ;
}

void raler (char *msg)
{
    perror (msg) ;
    exit (1) ;
}

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
}

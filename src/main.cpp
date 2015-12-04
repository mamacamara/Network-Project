/*
 * Mamadou CAMARA
 * Projet reseau
 * Master 2 CSMI
 */

#include "Channels.hpp"
//#include "Shell.hpp"
#include "Exception.hpp"

int main(int argc, const char* argv[])
{
	string type,port,addr;
	switch(argc)
	{
	case 2 :
		type = argv[1];
		break;
	case 3 :
		type = argv[1];
		port = argv[2];
		break;
	default :
		cout << "Invalid arguments" << endl;
		cout << argv[0] << " server|client [port]" << endl;
		break;
	}

	if(type == "server")
	{
		string config = "server.cfg";
		Channels s(port,config);
	}
	else if(type == "client")
	{   
            string file = "server.cfg";
            Client cl(file);
            AddrStorage sonaddr(file,port);
            char *buff =(char*)malloc(1024);
            cl.sendTo(sonaddr,buff);
            cl.recvFrom(sonaddr,buff);
            free (buff);
	    

	return true;
     }
}

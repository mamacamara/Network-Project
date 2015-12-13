/*
 * Mamadou CAMARA
 * Projet reseau
 * Master 2 CSMI
 */

#include "Channels.hpp"
//#include "Shell.hpp"
#include "Exception.hpp"
using namespace std;

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
	else if(type == "client1")
	{   
            string file = "client1.cfg";
            Client cl(file);
            AddrStorage sonaddr("127.0.0.1","4244");
            char buff[MAXLEN];
            cl.sendTo(sonaddr,buff);
            cl.recvFrom(sonaddr,buff);
       }
	else if(type == "client2")
	{   
            string file = "client2.cfg";
            Client cl(file);
            AddrStorage sonaddr("127.0.0.1","4244");
            char buff[MAXLEN];
            cl.sendTo(sonaddr,buff);
            cl.recvFrom(sonaddr,buff);
        }
return true;
}

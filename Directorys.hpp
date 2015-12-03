#ifndef SERVER_H
#define SERVER_H

#include "Client.hpp"

using namespace std;

class Directorys : public Client
{
 public :
	Directorys(string port, string config);
	~Directorys();

	int sock(const AddrStorage &addr);
	void run();
	
	//Envoi/reception de datagrammes
	void send_to(const Datagram &dg, const AddrStorage &addr);
	void receive(Datagram &dg, AddrStorage *addr, int s);

	

	//Surcouche serveur
	void process(const Datagram &dg, const AddrStorage &addr);
	void update_client_map(const AddrStorage &addr);

	int find_file(const string& file);

	void import(const string &file);

 private :
	int _sockets[MAXSOCK];
	int _n_socks;
	
	bool _run;

	addr_map _client_map;
	library _lib;
};

#endif

#ifndef SERVER_H
#define SERVER_H

#include "Client.hpp"

using namespace std;

class Channels : public Client
{
 public :
	Channels(string port, string config);
	~Channels();

	int sock(const AddrStorage &addr);
        CANAL chnl;
        int actuel;
	void run();
	
	//Envoi/reception de datagrammes
	/*void send_to(const Datagram &dg, const AddrStorage &addr);
	void receive(Datagram &dg, AddrStorage *addr, int s);*/
        void lire_message(AddrStorage * ,char[MAXLEN], int);
        void diffuser_message(CANAL,AddrStorage  ,char[MAXLEN]);


	

	//Surcouche serveur
	/*void process(const Datagram &dg, const AddrStorage &addr);
	void update_client_map(const AddrStorage &addr);

	int find_file(const string& file);

	void import(const string &file);*/
        void nouveaux(const AddrStorage &);

 private :
	int _sockets[MAXSOCK];
	int _n_socks;
	
	bool _run;

	addr_map _client_map;
//	library _lib;

};

#endif

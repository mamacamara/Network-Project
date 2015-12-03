#ifndef SHELL
#define SHELL

#include "socket.hpp"
#include "Client.hpp"

class Shell
{
 public :
	Shell();
	~Shell();

 private :
	void wait_command();

	void fail();
	void close();
	void lire_message(char  cmd);
	void envoyer_a_tous(char cmd);
//	void remove(vector<string> cmd);
//	void library();
//	

	Client *_c;
};


#endif

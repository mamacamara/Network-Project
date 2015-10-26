#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include "shell.h"


/*Shell::Shell()
{
  string file = "server.cfg";
  try
  {
    _c = new Client(file);
  }
  catch(Exception e)
  {
    cout << endl <<  "A fatal error occured : " << endl << e.what() << endl << endl;
    exit(false);
  }
  wait_command();
}*/

/*Shell::~Shell()
{
}

void Shell::wait_command()
{
  cout << "PRAKClient> ";

  string cmd;
  getline(cin,cmd);

  char delim = ' ';
  vector<string> v = Converter::split(cmd, delim);

  string ask = v[0];

  try
  {
    if(ask == "exit") close();
    else if(ask == "dl" || ask == "lire") download(v);
    else if(ask == "ul" || ask == "stocker") upload(v);
    else if(ask == "lib" || ask == "catalogue") library();
    else if(ask == "rm" || ask == "detruire") remove(v);
    else fail();
  }
  catch(Exception e)
  {
    cout << endl <<  "An error occured : " << endl << e.what() << endl << endl;
    AddrStorage addr = e.addr();
    if(addr.pport()!="0") _c->disconnect_req(addr);
  }

  wait_command();
}*/

void close()
{
  printf( "Goodbye ! \n\n") ;
  exit(1);
  return;
}

void fail()
{
  printf ("Command fail\n\n");
  return;
}
void command(char * msg)
{
 printf(" m %s\n ", msg);
 }
void beginChannel(char* channel)
{
 printf(" client  %s\n", channel);
}
int main()
{
char * msg = "salut tout le monde";
char * canal = "m2csmi";
  command(msg);
  beginChannel(canal);
  return 0;

}

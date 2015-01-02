#include <iostream>
#include <list>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <iterator>
#include <stdexcept>

#include "queue.h"
#include "item.h"

using namespace std;

static list<Queue> listQueue;

void tokenizeCmd(const string &str, vector<string> &tokens, const string &delimiters = " ") {
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    string::size_type pos = str.find_first_of(delimiters, lastPos);

    while (string::npos != pos || string::npos != lastPos) {
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        lastPos = str.find_first_not_of(delimiters, pos);
        pos = str.find_first_of(delimiters, lastPos);
    }
}

void processCommand(string strCmd) {
    vector<string> tokens;
    tokenizeCmd(strCmd, tokens);
    
    if (tokens.empty())
      return;

    try {
      if(tokens.at(0) == "list") {
	cout << "All queues [" << listQueue.size() << "]" << endl;
	for(std::list<Queue>::iterator it = listQueue.begin(); it != listQueue.end(); ++it)
	    std::cout << it->GetName() << "\t\tProirity: " << it->GetPriority() << '\n';

      } else if(tokens.at(0) == "add") {
	Queue cA(tokens.at(1));
	if (tokens.size() > 2)
	  cA.SetPriority(std::stoi(tokens.at(2)));
	listQueue.push_back(cA);

      } else if(tokens.at(0) == "remove") {
	for(std::list<Queue>::iterator it = listQueue.begin(); it != listQueue.end(); ++it)
	    if(it->GetName() == tokens.at(1))
	      listQueue.erase(it++);

      } else if(tokens.at(0) == "update") {
	if (tokens.size() < 3)
	  return;

	try {
	  for(std::list<Queue>::iterator it = listQueue.begin(); it != listQueue.end(); ++it)
	      if(it->GetName() == tokens.at(1))
		it->SetPriority(std::stoi(tokens.at(2)));
	} catch (const std::exception &ex) {
	    std::cerr << ex.what() << '\n';
	}
	    
      } else if(tokens.at(0) == "help") {
	  cout << "Available commands:\n"
	       << "\tadd <name> [priority]\n"
	       << "\tremove <name>\n"
	       << "\tupdate <name> <priority>\n"
	       << "\tlist\n";
      } else if(tokens.at(0) == "quit") {
	exit(0);
      }
    } catch (const std::out_of_range &oor) {
      std::cerr << "Too few arguments for " << tokens.at(0) << '\n';
    }
}

void shell() {
    string strCmd;

    cout << "Switch to interactive shell\n";
    cout << "qsh> ";
    while(std::getline(std::cin, strCmd)) {
      processCommand(strCmd);
      cout << "qsh> ";
    }
}

void usage(char *pchProgram) {
    cout << "Usage: " << pchProgram << '\n'
	 << " -h\tShow help\n"
	 << " -d\tDaemonize the server (default)\n"
	 << " -s\tStart interactive shell\n"
	 << " -f\tRun on foreground\n";
}

void initialize() {
  Queue cGeneral("generic");
  cGeneral.SetSystemFlag(true);
  listQueue.push_back(cGeneral);
}

int main(int argc, char **argv) {

    /* Create at least one queue */
    initialize();

    if (argc < 2)
      /*TODO daemon */
      cout << "Starting server\n";
    else
	for(int i=1; i<argc; i++)
	  if (!strcmp(argv[i], "-s"))
	      shell();
	  else if (!strcmp(argv[i], "-s"))
	      exit(0);
	  else
	    usage(argv[0]);

    return 0;
}

//Garrett Jennings //A01491831
//HW4 CMD Shell
//CS3100
#include <sys/wait.h>
#include <iostream>
#include <unistd.h>
#include "func.hpp"
#include <string>
#include <chrono>
#include <ctime>

int main(void)
{
	std::vector<std::string> history;
	auto temp = std::chrono::system_clock::now();	
	std::chrono::duration<double> ptime;
	ptime = temp - temp;
		//forever (until "exit" is entered by the user
	while(true) 
	{
		std::cout <<"[cmd]"; //G-shell i.e. garretts-shell
		std::string cmd;

			//read a line of input from the user
		getline(std::cin, cmd); // at this point, I need to 'tokenize' cmd;
		std::vector<std::string> tokenCmd;
		history.push_back(cmd);
		tokenCmd = tokenize(cmd);
		
			// loads the tokenized vector into an char ** array
			// likely not the most efficient but whatevs
			// we might decide if the input is a builtin command
		if(tokenCmd[0] == "ptime")
		{
			std::cout << ptime.count() << std::endl;
		}
		else if(tokenCmd[0] == "history")
		{
			printHistory(history);
		}
		else if(tokenCmd[0] == "^")
		{
			printHistory(history, tokenCmd);
			std::vector<std::string> histCmd;
			int index = std::stoi(tokenCmd[1]);
			std::cout << index << std::endl;
			histCmd = tokenize(history[index]);
			std::cout << histCmd[0] << std::endl;
			ptime = forkExec(histCmd, ptime);			
		}
		else if (tokenCmd[0] == "exit")
		{
			break;
		}
		else // if the command is not built in we need to search for a program and fork execvp it
		{	
			ptime =	forkExec(tokenCmd, ptime);
		}	
	}
	return 0;
}




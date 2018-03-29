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
#include <cstring>

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
			std::cout << "Time spend executing child processes: " <<  ptime.count() << " seconds" << std::endl;
		}
		else if(tokenCmd[0] == "history")
		{
			printHistory(history);
		}
		else if(tokenCmd[0] == "^")
		{
			std::vector<std::string> histCmd;
			int index = std::stoi(tokenCmd[1]);
			histCmd = tokenize(history[index]);
			ptime = forkExec(histCmd, ptime);			
		}
		else if (tokenCmd[0] == "cd")
		{	
			//change directories
			if (tokenCmd.size() > 1)
			{
				const char* path = strdup(tokenCmd[1].c_str());
				chdir(path);
				delete path;
			}
		}
		else if (tokenCmd[0] == "exit")
		{
			break;
		}
		//we need to check if a pipe was in the command
		else if (check4Pipe(tokenCmd))
		{
			//now I am going to get the index of the pipe, INEFFICIENT because I just checked.
			//but I kinda liked the idea of getting the index after I know it is there.
			//its not production quality but it's not gonna give me bugs so whatever.
			int pipeIndex =  getPipeIndex(tokenCmd);
			//now I am going to split tokenCmd into 2 separate cmds
			std::vector<std::string> tokenCmdL;		//left of pipe
			std::vector<std::string> tokenCmdR;		//right of pipe
			for( int i = 0; i< tokenCmd.size(); i++)
			{
				if( i < pipeIndex)
				{
					tokenCmdL.push_back(tokenCmd[i]);	
				}
				else if( i > pipeIndex)
				{
					tokenCmdR.push_back(tokenCmd[i]);	
				}
			}	
			ptime = pipeForkExec(tokenCmdL, tokenCmdR, ptime);
			
		}
		else // if the command is not built in we need to search for a program and fork execvp it
		{	
			ptime =	forkExec(tokenCmd, ptime);
		}	
	}
	return 0;
}




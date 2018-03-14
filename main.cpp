//Garrett Jennings //A01491831
//HW4 CMD Shell
//CS3100
#include <sys/wait.h>
#include <iostream>
#include <unistd.h>
#include "func.hpp"
#include <string>

int main(void)
{
	std::vector<std::string> history;
		//forever (until "exit" is entered by the user
	while(true) 
	{
		std::cout <<"gash cmd-->"; //G-shell i.e. garretts-shell
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

		}
		else if(tokenCmd[0] == "history")
		{

		}
		else if(tokenCmd[0] == "^")
		{

		}
		else if (tokenCmd[0] == "exit")
		{
			break;
		}
		
		else // if the command is not built in we need to search for a program and fork execvp it
		{	
			int numArgs = tokenCmd.size();
			char** args = new char*[numArgs];
			for(int i = 0; i < numArgs; i++)
			{
				args[i] = (char*) tokenCmd[i].c_str();	
			}
	
	
			if(fork())
			{
				// parent waits for the child to finish
				int status;
				wait(&status);
			}
			else
			{
				//child, executes the user's input as a command
				//char** args = new char*[2];
				//args[0] = (char*) cmd.c_str();
				//args[1] = (char*)NULL;
				
				execvp(args[0], args);
				//note if the command is successfully found the child will never
				//execute the following error message
				//command not found, or similar errors
				std::cerr << args[0] << " did something wrong" << std::endl;
				exit(1);
			}

		}	
	}
	return 0;
}




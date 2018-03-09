//Garrett Jennings
//A01491831
//HW4 CMD Shell
//CS3100
#include <sys/wait.h>
#include <iostream>
#include <unistd.h>
#include "func.hpp"


int main(void)
{
	
	//forever (until "exit" is entered by the user
	while(true) 
	{
		std::cout <<"gash cmd-->"; //G-shell i.e. garretts-shell
		std::string cmd;

		//read a line of input from the user
		getline(std::cin, cmd); // at this point, I need to 'tokenize' cmd;
		//tokenize(cmd);
	
		// we might decide if the input is a builtin command
		// Ill later come back to do a switch statement chain.
		if (cmd == "exit")
		{
			break;
		}
		
		else // if the command is not built in we need to search for a program and fork execvp it
		{	
			
			if(fork())
			{
				// parent waits for the child to finish
				int status;
				wait(&status);
			}
			else
			{
				// child, executes the user's input as a command
				char** args = new char*[2];
				args[0] = (char*) cmd.c_str();
				args[1] = (char*)NULL;

				execvp(args[0], args);
				//note if the command is successfully found the child will never
				//execute the following error message
				// command not found, or similar errors
				std::cerr << args[0] << " did something wrong" << std::endl;
				exit(1);
			}
		}	
	}
	return 0;
}




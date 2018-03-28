#include <iostream>
#include <string>
#include "func.hpp"
#include <chrono>
#include <ctime>
#include <sys/wait.h>
#include <iostream>
#include <unistd.h>
#include <cstring>


std::vector<std::string> tokenize(std::string cmd)
{
	std::vector<std::string> tokenCmd;
	int length = cmd.length();
	std::vector<char> tempCmd;
	bool hasCmd = false;						// this is to allow more than 1 space between commands
	for(int i = 0; i <= length; i++)
	{
		if(cmd[i] == ' '|| i == length)			// the last iteration stores what ever is left in cmd
		{
			if(hasCmd) 							// this will add the command to the vector
			{
				std::string newCmd(tempCmd.begin(), tempCmd.end());
				tokenCmd.push_back(newCmd);
				hasCmd = false;
				tempCmd.clear();
			}
		}
		else
		{
			tempCmd.push_back(cmd[i]);
			hasCmd = true;
		}
	}

	return tokenCmd;
}
void printHistory(std::vector<std::string> history)
{
			for(int i = 0; i < history.size(); i++)
			{
				std::cout << history[i] << std::endl;	
			}
}		
void printHistory(std::vector<std::string> history, std::vector<std::string> tokenCmd)
{
	if (tokenCmd.size() > 1)
			{
				int i = stoi(tokenCmd[1]);
				i--;
				std::cout << history[i] << std::endl;
			}
			else
			{
				std::cout << "Please specify history index like so '^ int' " << std::endl;	
			}
}
std::chrono::duration<double> forkExec(std::vector<std::string> tokenCmd, std::chrono::duration<double> ptime)
{
			auto start = std::chrono::system_clock::now();	
			if(fork())
			{
				// parent waits for the child to finish
				int status;
				wait(&status);
				auto end = std::chrono::system_clock::now();
				std::chrono::duration<double> elapsed_seconds = end - start;
				ptime += elapsed_seconds;
			}
			else
			{
				int numArgs = tokenCmd.size();
				char** args = new char*[numArgs];
				for(int i = 0; i < numArgs; i++)
				{
					args[i] = strdup(tokenCmd[i].c_str());
				}
				//child, executes the user's input as a command
				execvp(args[0], args);
				//note if the command is successfully found the child will never
				//execute the following error message
				//command not found, or similar errors
				std::cerr << args[0] << " did something wrong" << std::endl;
				exit(1);
				delete[] args;
			}
			return ptime;
//			int numArgs = tokenCmd.size();
//			char** args = new char*[numArgs];
//			for(int i = 0; i < numArgs; i++)
//			{
//				args[i] = (char*) tokenCmd[i].c_str();	
//			}
//			auto start = std::chrono::system_clock::now();	
//			if(fork())
//			{
//				// parent waits for the child to finish
//				int status;
//				wait(&status);
//				auto end = std::chrono::system_clock::now();
//				std::chrono::duration<double> elapsed_seconds = end - start;
//				ptime += elapsed_seconds;
//			}
//			else
//			{
//				//child, executes the user's input as a command
//				execvp(args[0], args);
//				//note if the command is successfully found the child will never
//				//execute the following error message
//				//command not found, or similar errors
//				std::cerr << args[0] << " did something wrong" << std::endl;
//				exit(1);
//			}
//
//			delete[] args;
//
//			return ptime;
}


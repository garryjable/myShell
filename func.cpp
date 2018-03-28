#include <iostream>
#include <string>
#include "func.hpp"
#include <chrono>
#include <ctime>
#include <sys/wait.h>
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <errno.h>
#include <error.h>


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
				args[numArgs] = NULL; //// execvp needs a null at the back.
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
}
std::chrono::duration<double> pipeForkExec(std::vector<std::string> tokenCmdL, std::vector<std::string> tokenCmdR,std::chrono::duration<double> ptime)
{
			int p[2];
			pipe(p);
			if(fork()==0)
			{
				// this is the first child
				// 0) read in the source feor this file and print it to the pipe

				// close(p[READ]);
//				dup2(p[WRITE],STDOUT_FILENO);
//
//				char *cat[] = { (char*)"cat", (char*)"encrypt.cpp", (char*)NULL };
//				if (execvp(cat[0], cat) < 0)
//				{
//					error(1, errno, "execvp(cat) failed");
//				}
			}
			
			if(fork()==0)
			{
				// 2nd child
				// 1) read the pipe and send the text
				// through the tr program

				// close(p[WRITE]);
//				dup2(p[READ], STDIN_FILENO);
//
//				char *tr[] = { (char*)"tr", (char*)"a-zA-Z()<>{}[]",
//					(char*)"n-za-mN-ZA-M) (><}{][", (char*)NULL };
//				if (execvp(tr[0], tr) < 0)
//					{
//						error(1, errno, "execvp(tr) failed");
//					}

			}
//			close(p[READ]);
//			close(p[WRITE]);

			int wstatus;
			int kids = 2;
			while (kids >0)
			{
				pid_t kiddo = waitpid(-1, &wstatus, 0);
				std::cout << "Child proc " << kiddo << " exited with status " << wstatus << std::endl;
				kids--;
			}
			std::cout << "all done" << std::endl;
			return ptime;
}
bool check4Pipe(std::vector<std::string> tokenCmd)
{
		bool isPipe = false;
		for (int i = 0; i < tokenCmd.size(); i++)
		{
			if(tokenCmd[i] == "|")
			{
				isPipe = true;
			}
		}
		return isPipe;
}
int getPipeIndex(std::vector<std::string> tokenCmd)
{
		int pipeIndex;
		for (int i = 0; i < tokenCmd.size(); i++)
		{
			if(tokenCmd[i] == "|")
			{
				pipeIndex = i;
			}
		}
		return pipeIndex;
}

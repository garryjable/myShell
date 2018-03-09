#include <string>
#include "func.hpp"


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

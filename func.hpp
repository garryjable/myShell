// this is the header for my function file
#pragma once 
#include <vector>
#include <chrono>
#include <ctime>
#include <sys/wait.h>
#include <iostream>
#include <unistd.h>
const int WRITE = 1;
const int READ = 0;
std::vector<std::string> tokenize(std::string cmd);
void printHistory(std::vector<std::string> history);
void printHistory(std::vector<std::string> history, std::vector<std::string> tokenCmd);
std::chrono::duration<double> forkExec(std::vector<std::string> tokenCmd, std::chrono::duration<double> ptime);
std::chrono::duration<double> pipeForkExec(std::vector<std::string> tokenCmdL, std::vector<std::string> tokenCmdR,std::chrono::duration<double> ptime);
bool check4Pipe(std::vector<std::string> tokenCmd);
int getPipeIndex(std::vector<std::string> tokenCmd);

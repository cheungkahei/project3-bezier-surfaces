//nputfile.bez 0.1 -a 

#include "interpreter.h"
#include "main.cpp"
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>

using namespace std;
using namespace interpreter;

interpreter_t::interpreter_t(const string& command) {
	/* parse the command line */
	this->read(filename, scene);
}


int interpreter_t::read(const string& commandLine){
	std::string token, fileName, flag;
	std::string delimiter = " ";
	std::string identifier = "-";
	int pos = 0;
	float subDiv;
	commandLine = commandLine + " "; //from main
	pos = commandLine.find(delimiter);

	//save filename
	token = commandLine.substr(0, pos);
	fileName = token;
	commandLine.erase(0, pos + 1);

	//check for flag
	if( (commandLine.last == 'a') || (commandLine.last == 'u') ){ //call for last item of string
	  flag = commandLine.last;  
	  int endLn = commandLine.length() - 1;
	  int startDel = commandLine.length() - 3;
	  commandLine.erase(startDel, endLn);
	  pos = commandLine.find(identifier - 2); //bring pos to place before " -" so that subDiv will get the number before '-a'
	}
	else{
	  pos = commandLine.length() - 1; //end of subDiv is the end of the commandLine string
	}

	//assign value to subDiv
	token = commandLine.substr(0, pos);
	std::string tokenStr = token;
	float val = ::atof(tokenStr.c_str());
	subDiv = val;
	commandLine.erase(0, pos + 1);

};


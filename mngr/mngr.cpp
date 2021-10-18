// libstdc++
#include <fstream>
#include <iostream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

// header for lib
#include "mngr.hpp"

using namespace std;
using namespace mngr;

/*
// check if a file exists
bool file_exists(const string &_name_f)
{
	struct stat buffer;
	return (stat(_name_f.c_str(), &buffer) == 0); // get info on file
}

// creates a file
bool create_file(const string &_name, const string &content)
{
	if (file_exists(_name))
	{
		cerr << "File \"" << _name << "\" already exists!";
		return false;
	}
	else
	{

		ofstream _outfile(_name);
		_outfile << content << endl;
		_outfile.close();
	}
}
*/
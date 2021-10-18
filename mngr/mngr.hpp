#pragma once

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

// mngr is a minimalist C++ library oriented towards simplicity.
// It allows incredibly easy file management, for example, including voids such as delete_file(), or create_file().
// It is self contained within one header file.
namespace mngr
{
	// FILE MANAGEMENT

	// Cecks if a specific file exists.
	bool file_exists(const string &_name)
	{
		struct stat buffer;
		return (stat(_name.c_str(), &buffer) == 0); // get info on file
	}

	// Creates a file.
	void create_file(const string &_name, const string &content = "", bool replace = false)
	{
		if (!replace && file_exists(_name))
		{
			cerr << "Attempted to create file \"" << _name << "\", but it already exists. \
			        \nTry passing 3rd argument (replace) in mngr::create_file()"
			     << endl;
			return;
		}
		else
		{
			// Initialise file
			ofstream _outfile;
			_outfile.open(_name, ios::out | ios::app);

			if (_outfile.fail())
				cerr << "File writing failed, perhaps because of lack of permission." << endl;

			// make sure write fails with exception if something is wrong
			_outfile.exceptions(_outfile.exceptions() | ios::failbit | ifstream::badbit);

			// Optional content
			_outfile << content << endl;
			_outfile.close();
		}
	}

	// Deletes a file.
	void delete_file(const string &_name)
	{
		remove(_name.c_str());
	}

	// Appends content to the end of a file.
	void add_to_file(const string &_name, const string &content)
	{
		if (!file_exists(_name))
		{
			cerr << "Attempted to write to file \"" << _name << "\" but it does not exist. \
			        \nmngr::create_file() can be called to create it."
			     << endl;
		}
		else
		{
			ofstream _outfile;
			_outfile.open(_name, ios::out | ios::app);

			if (_outfile.fail())
				cerr << "File writing failed, perhaps because of lack of permission." << endl;

			// make sure write fails with exception if something is wrong
			_outfile.exceptions(_outfile.exceptions() | ios::failbit | ifstream::badbit);

			_outfile << content << std::endl;
			_outfile.close();
		}
	}
}

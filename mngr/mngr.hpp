#pragma once

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <bits/fs_fwd.h>
#include <bits/fs_path.h>
#include <bits/fs_dir.h>
#include <bits/fs_ops.h>

// Support for C++11 and 17 (and 20, evidently)
#ifndef __has_include
static_assert(false, "__has_include not supported");
#else
#if __cplusplus >= 201703L && __has_include(<filesystem>)
#include <filesystem>
namespace fs = std::filesystem;
#elif __has_include(<experimental/filesystem>)
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#endif
#endif

using namespace std;

// mngr is a minimal C++ library oriented towards simplicity.
// It allows incredibly easy file management, for example, including voids such as delete_file(), or create_file().
// It is self contained within one header file.
namespace mngr
{
	// FILE MANAGEMENT

	// Checks if a specific file exists.
	bool file_exists(const string &_name)
	{
		struct stat buffer;
		return (stat(_name.c_str(), &buffer) == 0); // get info on file. == 0? => file exists
	}

	// Checks if a specific directory exists.
	bool folder_exists(const string &_name)
	{
		struct stat info;

		int statRC = stat(_name.c_str(), &info);
		if (statRC != 0)
		{
			if (errno == ENOENT)
			{
				return 0;
			} // something along the path does not exist
			if (errno == ENOTDIR)
			{
				return 0;
			} // something in path prefix is not a dir
			return -1;
		}

		return (info.st_mode & S_IFDIR) ? 1 : 0;
	}

	// Creates a file.
	void create_file(const string &_name, const string &content = "", bool replace = false)
	{
		if (!replace && file_exists(_name))
		{
			// Error long
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

			// File opening failure.
			if (_outfile.fail())
				cerr << "File writing failed, perhaps because of lack of permission." << endl;

			// make sure write fails with exception if something is wrong
			_outfile.exceptions(_outfile.exceptions() | ios::failbit | ifstream::badbit);

			// Optional content. Unrecommended.
			_outfile << content << endl;
			_outfile.close();
		}
	}

	// Deletes a file.
	void delete_file(const string &_name)
	{
		// Self explanative. Convert std::string to const char *
		remove(_name.c_str());
	}

	// Appends content to the end of a file.
	void add_to_file(const string &_name, const string &content)
	{
		if (!file_exists(_name))
		{
			// Error log
			cerr << "Attempted to write to file \"" << _name << "\" but it does not exist. \
			        \nmngr::create_file() can be called to create it."
			     << endl;
		}
		else
		{
			// Initialise file
			ofstream _outfile;
			_outfile.open(_name, ios::out | ios::app);

			// File failure
			if (_outfile.fail())
				cerr << "File writing failed, perhaps because of lack of permission." << endl;

			// make sure write fails with exception if something is wrong
			_outfile.exceptions(_outfile.exceptions() | ios::failbit | ifstream::badbit);

			// Append
			_outfile << content << std::endl;
			_outfile.close();
		}
	}

	// Gives a new path to a file (can be used for renaming the file, evidently).
	void new_path(const string &_name, const string &newpath)
	{
		// Convert parameters from std::string to const char *
		rename(_name.c_str(), newpath.c_str());
	}

	// Deletes a folder.
	void delete_folder(const string &_name)
	{
		fs::remove_all(_name);
	}

	// Creates a folder.
	void create_folder(const string &_name)
	{
		fs::create_directories(_name);
	}
}

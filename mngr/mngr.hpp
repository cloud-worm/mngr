/*

		    [*𝗺𝗻𝗴𝗿;]

	     « Python in C++ » *

   A small, simplicity-oriented utility
   library. Aims to be as explicit as
   possible - each method serves one sole
   purpose that is obvious.

   Basically, the philosophy is that you
   must not be using complex data types
   and templates as instead, exclusively
   call functions that serve a single
   purpose.

   Writing this text is probably pointless,
   since I'm probably the only one that's
   ever going to use this library. But still.

   * I call this "Python in C++" because
   the 'method-driven' approach to C++ that
   this library uses (as I like to call it)
   ressembles Python, slightly.

	Copyright (c) 2021  Cloud Worm
*/

// Guards
#ifndef MNGR
#define MNGR

// Make sure it is exclusively included once!
#pragma once

#include <ios>	     // For streamsize type
#include <limits>	     // numeric_limits<...>
#include <fstream>     // File manipulation
#include <iostream>    // For input(), print() and related
#include <string>	     // Strings
#include <sys/types.h> // Not sure I'm actually using this
#include <sys/stat.h>  // For file_exists()
#include <numbers>     // Gives user access to constants: pi, etc
#include <chrono>	     // Time, etc
#include <thread>	     // Also time, I guess
//#include <unistd.h>    // I don't remember
//#include <stdio.h>     // Probably useful? Not sure.
//#include <cstdarg>    // For va_<...>
//#include <unistd.h>    // I don't remember

/*
At some point I had problems with <filesystem>.
I am a naïve fool, and I thought including the following
four was going to help.

#include <bits/fs_fwd.h>
#include <bits/fs_path.h>
#include <bits/fs_dir.h>
#include <bits/fs_ops.h>
*/

// Support for C++11 up to 17 (and 20, evidently)
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

// Although this is considered unreasonable, we don't want to write
// namespace scopes each time ┐(´ー｀)┌
using namespace std::this_thread;
using namespace std::chrono_literals;
using std::chrono::system_clock;
using namespace std;

// Namespace definition.

namespace mngr
{
	// FILE MANAGEMENT

	bool is_file_empty(const string &_name)
	{
		std::ifstream pFile(_name.c_str());

		return pFile.peek() == std::ifstream::traits_type::eof();
	}

	int count_file_lines(const string &_name)
	{

		string s;
		int sTotal;
		ifstream _in;

		_in.open(_name.c_str());

		while (!_in.eof())
		{
			getline(_in, s);
			sTotal++;
		}

		_in.close();

		return sTotal;
	}

	// Checks if a specific file exists.
	bool file_exists(const string &_name)
	{
		struct stat buffer;
		return (stat(_name.c_str(), &buffer) == 0); // get info on file. == 0? => file exists
	}

	// Checks if a specific directory exists.
	bool folder_exists(const string &_name)
	{
		struct stat buffer;

		int statRC = stat(_name.c_str(), &buffer);
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

		return (buffer.st_mode & S_IFDIR) ? 1 : 0;
	}

	// Creates a file.
	void create_file(const string &_name, bool replace = false)
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

			_outfile.close();
		}
	}

	// Deletes a file.
	void delete_file(const string &_name)
	{
		// Self explanative. Convert std::string to const char *
		remove(_name.c_str());
	}

	// Clears the content of a file.
	void clear_file(const string &_name)
	{
		std::ofstream _outfile;
		_outfile.open(_name, std::ofstream::out | std::ofstream::trunc);
		_outfile.close();
	}

	// Gives a new path to a file (can be used for renaming the file, evidently).
	void new_path(const string &_name, const string &newpath)
	{
		// Convert parameters from std::string to const char *
		rename(_name.c_str(), newpath.c_str());
	}

	// Removes specific line of a file.
	void remove_line(const string &_name, int num_of_lines = -12)
	{
		if (num_of_lines == -12)
		{
			num_of_lines = count_file_lines(_name);
		}
		else if (num_of_lines <= 0 && num_of_lines > count_file_lines(_name))
		{
			cerr << "You did not input a valid line number!"
			     << endl;
		}

		if (!file_exists(_name))
		{
			cerr << "Attempted to write to file \"" << _name << "\" but it does not exist. \
			        \nmngr::create_file() can be called to create it."
			     << endl;
		}
		else
		{
			/*
			std::ifstream in(_name);
			std::ofstream out(_name + ".tmp");
			// some error checking...
			std::string line;
			std::getline(in, line);
			for (std::string tmp; std::getline(in, tmp); line.swap(tmp))
			{
				out << line << '\n';
			}

			// std::string temp_str = _name + ".tmp";
			// const char *_tempfile = temp_str.c_str();

			cout << _name + ".tmp";

			delete_file(_name + ".tmp");
			*/

			ifstream fin(_name.c_str());
			ofstream fout;
			fout.open("temp.txt", ios::out);

			char ch;
			int line = 1;
			while (fin.get(ch))
			{
				if (ch == '\n')
					line++;

				if (line != num_of_lines) // content not to be deleted
					fout << ch;
			}
			fout.close();
			fin.close();
			remove(_name.c_str());
			rename("temp.txt", _name.c_str());
		}
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
			bool rm_lastl = false;

			if (is_file_empty(_name))
			{
				rm_lastl = true;
			}

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

			if (rm_lastl = true)
			{
				remove_line(_name, count_file_lines(_name));
			}
		}
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

	// TIME MANAGEMENT

	// Copyright (c) 2008-2020 Free Software Foundation, Inc., for this function (slightly modified)

	// Sleep for some time (uses time literal suffixes).
	template <typename _Rep, typename _Period>
	void wait(const chrono::duration<_Rep, _Period> &sleeptime = 1s)
	{
		if (sleeptime <= sleeptime.zero())
			return;
		auto _seconds = chrono::duration_cast<chrono::seconds>(sleeptime);
		auto _nanos = chrono::duration_cast<chrono::nanoseconds>(sleeptime - _seconds);

#ifdef _GLIBCXX_USE_NANOSLEEP
		__gthread_time_t __ts =
		    {
			  static_cast<std::time_t>(_seconds.count()),
			  static_cast<long>(_nanos.count())};
		while (::nanosleep(&__ts, &__ts) == -1 && errno == EINTR)
		{
		}
#else
		__sleep_for(_seconds, _nanos);
#endif
	}

	// CONSOLE

	// Prints content to the standard output, adds a new line and flushes the buffer.
	void print(const string &content = "")
	{
		cout << content << endl;
	}

	// Prints content, then waits the given time (uses time literal suffixes).
	template <typename _Rep, typename _Period>
	void print_and_wait(const string &content = "", const chrono::duration<_Rep, _Period> &sleeptime = 1s)
	{
		print(content);
		wait(sleeptime);
	}

	// Waits the given time (uses time literal suffixes), then prints content.
	template <typename _Rep, typename _Period>
	void wait_and_print(const string &content = "", const chrono::duration<_Rep, _Period> &sleeptime = 1s)
	{
		print(content);
		wait(sleeptime);
	}

	// Receives user input from the standard input.
	// By default, the input is a string, and you must specify the type, as a template parameter, if it isn't.
	template <typename T = string>
	T input(const string &prompt)
	{
		T _input;

		cout << prompt;
		cin >> _input;

		return _input;
	}

	// Convert any number into a string.
	string make_string(unsigned input_val)
	{
		return to_string(input_val);
	}

	/*
		// Function allowing the user to press any key to continue.
		void any_key(const string &message = "")
		{
			// cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max());
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			// cin.get();
			getchar();


		} */
}

// End guards
#endif

// End of mngr.hpp

/*

                [*𝗺𝗻𝗴𝗿;]

   A small, simplicity-oriented utility
   library. Aims to be as explicit as
   possible - each method serves one sole
   purpose that is obvious.

   Basically, the philosophy is that you
   must not be using complex data types
   and templates and instead, exclusively
   call functions that serve a single
   purpose.

   mngr's different utilities are defined
   in several namespaces, which include:

     - file
     - folder
     - console
     - time
     - data

   Writing this text is probably pointless,
   since I'm probably the only one that's
   ever going to use this library. But still.

        Copyright (c) 2021  Cloud Worm
*/

// Guards
#ifndef MNGR
#define MNGR 1

// Make sure it is exclusively included once!
#pragma once

#include <sys/stat.h>  // For file_exists()
#include <sys/types.h> // Not sure I'm actually using this

#include <chrono>   // Time, etc
#include <fstream>  // File manipulation
#include <ios>      // For streamsize type
#include <iostream> // For input(), print() and related
#include <limits>   // numeric_limits<...>
#include <numbers>  // Gives user access to constants: pi, etc
#include <string>   // Strings
#include <thread>   // Also time, I guess
//#include <unistd.h>    // I don't remember
//#include <stdio.h>     // Probably useful? Not sure.
//#include <cstdarg>    // For va_<...>
//#include <unistd.h>    // I don't remember

/*
At some point I had problems with <filesystem>.
I am a naïve fool, and I thought including the following
four was going to help.

#include <bits/fs_dir.h>
#include <bits/fs_fwd.h>
#include <bits/fs_ops.h>
#include <bits/fs_path.h>
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

// A simple, all-purpose utility library.
namespace mngr
{

      // FILE

      // Management and uilities relative to specific paths or files.
      namespace file
      {

            /**
             * @brief if a file is empty.
             *
             * @param _name string: path of the file.
             */
            bool is_file_empty(const string &_name)
            {
                  std::ifstream pFile(_name.c_str());

                  return pFile.peek() == std::ifstream::traits_type::eof();
            }

            /**
             * @brief the number of lines in a file.
             *
             * @param _name string: path of the file.
             */
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

            /**
             * @brief if a specific file exists.
             *
             * @param _name string: path of the file.
             */
            bool file_exists(const string &_name)
            {
                  struct stat buffer;
                  return (stat(_name.c_str(), &buffer) ==
                          0); // get info on file. == 0? => file exists
            }

            /**
             * @brief a file.
             *
             * @param _name string: name of the file.
             */
            void create_file(const string &_name, bool replace = false)
            {
                  if (!replace && file_exists(_name))
                  {
                        // Error long
                        cerr << "Attempted to create file \"" << _name
                             << "\", but it already exists. \
                                 \nTry passing 2nd argument (replace) in mngr::create_file()"
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
                              cerr << "File writing failed, perhaps because of lack of permission."
                                   << endl;

                        // make sure write fails with exception if something is wrong
                        _outfile.exceptions(_outfile.exceptions() | ios::failbit |
                                            ifstream::badbit);

                        _outfile.close();
                  }
            }

            /**
             * @brief Deletes a file.
             * 
             * @param _name string: name of the file.
             */
            void delete_file(const string &_name)
            {
                  // Self explanative. Convert std::string to const char *
                  remove(_name.c_str());
            }

            /**
             * @brief Clears the contents of a file.
             * 
             * @param _name string: name of the file.
             */
            void clear_file(const string &_name)
            {
                  std::ofstream _outfile;
                  _outfile.open(_name, std::ofstream::out | std::ofstream::trunc);
                  _outfile.close();
            }

            /**
             * @brief Gives a new path to a file (can be used for renaming the file, evidently).
             * 
             * @param _name string: original path.
             * @param newpath string: new path of the file.
             */
            void new_path(const string &_name, const string &newpath)
            {
                  // Convert parameters from std::string to const char *
                  rename(_name.c_str(), newpath.c_str());
            }

            /**
             * @brief Removes a specific line of a file. By default, it removes the last line of the file.
             * 
             * @param _name string: name of the file.
             * @param line_num integer: line to remove (default: last line of the file).
             */
            void remove_line(const string &_name, int line_num = -12)
            {
                  if (line_num == -12)
                  {
                        line_num = count_file_lines(_name);
                  }
                  else if (line_num <= 0 && line_num > count_file_lines(_name))
                  {
                        cerr << "You did not input a valid line number!" << endl;
                  }

                  if (!file_exists(_name))
                  {
                        cerr << "Attempted to write to file \"" << _name
                             << "\" but it does not exist. \
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

                              if (line != line_num) // content not to be deleted
                                    fout << ch;
                        }
                        fout.close();
                        fin.close();
                        remove(_name.c_str());
                        rename("temp.txt", _name.c_str());
                  }
            }

            /**
             * @brief Replace specific text in a file with a given string.
             * 
             * @param _name string: name of the file.
             * @param _target string: target text to be replaced.
             * @param _replacement string: replacement text.
             */
            void replace_file_text(const string &_name, const string _target, const string _replacement)
            {
                  if (!file_exists(_name))
                  {
                        cerr << "Attempted to write to file \"" << _name
                             << "\" but it does not exist. \
			        \nmngr::create_file() can be called to create it."
                             << endl;
                  }
                  else
                  {

                        /* Give these arguments more meaningful names. */
                        const char *filename = _name.c_str();
                        std::string target = _target;
                        std::string replacement = _replacement;

                        /* Read the whole file into a stringstream. */
                        std::stringstream buffer;
                        std::fstream file(filename, std::fstream::in);
                        for (std::string line; getline(file, line);)
                        {
                              /* Do the replacement while we read the file. */
                              if (line == target)
                              {
                                    buffer << replacement;
                              }
                              else
                              {
                                    buffer << line;
                              }
                              buffer << std::endl;
                        }
                        file.close();

                        /* Write the whole stringstream back to the file */
                        file.open(filename, std::fstream::out);
                        file << buffer.str();
                        file.close();
                  }
            }

            /**
             * @brief Appends content to the end of a file.
             * 
             * @param _name string: name of the file.
             * @param content string: content to append.
             */
            void add_to_file(const string &_name, const string &content)
            {
                  if (!file_exists(_name))
                  {
                        // Error log
                        cerr << "Attempted to write to file \"" << _name
                             << "\" but it does not exist. \
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
                              cerr << "File writing failed, perhaps because of lack of permission."
                                   << endl;

                        // make sure write fails with exception if something is wrong
                        _outfile.exceptions(_outfile.exceptions() | ios::failbit |
                                            ifstream::badbit);

                        // Append
                        _outfile << content /*<< std::endl*/;

                        _outfile.close();

                        /*
                        if (rm_lastl == true)
                        {
                              remove_line(_name, count_file_lines(_name));
                        }
*/
                  }
            }
      } // namespace file

      // Management and utilities relative to directories.
      namespace folder
      {

            /**
             * @brief Deletes a folder.
             * 
             * @param _name string: name of the folder.
             */
            void delete_folder(const string &_name) { fs::remove_all(_name); }

            /**
             * @brief Creates a folder.
             * 
             * @param _name string: name of the folder.
             */
            void create_folder(const string &_name) { fs::create_directories(_name); }

            /**
             * @brief Checks if a specific directory exists.
             * 
             * @param _name string: name of the folder.
             * @return true if the folder exists.
             */
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

      } // namespace folder

      // TIME MANAGEMENT

      // Time management, such as the wait() function to sleep for a given time.
      namespace time
      {

            // Copyright (c) 2008-2020 Free Software Foundation, Inc., for this function
            // (slightly modified)

            /**
             * @brief Sleeps for the given time (uses time literal suffixes: ns, ms, s).
             * 
             * @param sleeptime duration: Amount of time to sleep. Nanoseconds can be passed as a parameter if they are compatible with the compiler (default: 1s).
             */
            template <typename _Rep, typename _Period>
            void wait(const chrono::duration<_Rep, _Period> &sleeptime = 1s)
            {
                  if (sleeptime <= sleeptime.zero())
                        return;
                  auto _seconds = chrono::duration_cast<chrono::seconds>(sleeptime);
                  auto _nanos =
                      chrono::duration_cast<chrono::nanoseconds>(sleeptime - _seconds);

#ifdef _GLIBCXX_USE_NANOSLEEP
                  __gthread_time_t __ts = {static_cast<std::time_t>(_seconds.count()),
                                           static_cast<long>(_nanos.count())};
                  while (::nanosleep(&__ts, &__ts) == -1 && errno == EINTR)
                  {
                  }
#else
                  __sleep_for(_seconds, _nanos);
#endif
            }
      } // namespace time

      // CONSOLE

      // Console utilitities (input & output, amongst others)
      namespace console
      {

            /**
             * @brief Prints content to the standard output, adds a new line and flushes the buffer.
             * 
             * @param content string: string to be printed (default: empty string).
             */
            void print(const string &content = "") { cout << content << endl; }

            /**
             * @brief Prints content, then waits the given time (uses time literal suffixes).
             * 
             * @param content string: string to be printed (default: empty string).
             * @param sleeptime duration: Amount of time to sleep. Nanoseconds can be passed as a parameter if they are compatible with the compiler (default: 1s).
             */
            template <typename _Rep, typename _Period>
            void print_and_wait(const string &content = "",
                                const chrono::duration<_Rep, _Period> &sleeptime = 1s)
            {
                  print(content);
                  wait(sleeptime);
            }

            /**
             * @brief Prints content, then waits the given time (uses time literal suffixes).
             * 
             * @param sleeptime duration: Amount of time to sleep. Nanoseconds can be passed as a parameter if they are compatible with the compiler (default: 1s).
             * @param content string: string to be printed (default: empty string).
             */
            template <typename _Rep, typename _Period>
            void wait_and_print(const chrono::duration<_Rep, _Period> &sleeptime = 1s,
                                const string &content = "")
            {
                  wait(sleeptime);
                  print(content);
            }

            /**
             * @brief Receives user input from the standard input. By default, the input is a string, and you must specify the type, as a template parameter, if it isn't.
             * 
             * @tparam T Type of the input value.
             * @param prompt string: rompt that precedes the input (default: empty string).
             * @return Returns what was input as the type specified as template parameter.
             */
            template <typename T = string>
            T input(const string &prompt = "")
            {
                  T _input;

                  cout << prompt;
                  cin >> _input;

                  return _input;
            }

      } // namespace console

      // DATA

      // Data management and utilities.
      namespace data
      {

            /**
             * @brief Convert any number into a string.
             * 
             * @param input_val unsigned number: input number to convert.
             * @return Returns the input number as a string.
             */
            string s(unsigned input_val)
            {
                  stringstream ss;
                  ss << input_val;
                  return ss.str();
            }

            /**
             * @brief Convert any number into a string.
             * 
             * @param input_val long number: input number to convert.
             * @return Returns the input number as a string.
             */
            string s(long input_val)
            {
                  stringstream ss;
                  ss << input_val;
                  return ss.str();
            }

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
} // namespace mngr

// End guards
#endif

// End of mngr.hpp

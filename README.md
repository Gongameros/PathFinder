# PathFinder

## Install
All you need to install the app is to clone the repository.
It already has pre-compiled builds for Windows and Linux.
Windows has two builds: the main one is g++, and the other is Visual Studio.
If you are a Windows user, I suggest you use the Visual Studio build. It is much faster than the other one.

## About
This program searches for a specified file in a given directory and its subdirectories using multiple threads.
The search process is parallelized to improve efficiency, with a limit of MAX_THREADS concurrent search threads.
It employs atomics and mutexes to ensure thread safety and synchronized access to shared resources.
The findPathToFile function recursively explores the directory tree, spawning threads to search in subdirectories.
If the file is found, the program prints its path to the console and terminates all threads.
The program handles filesystem errors gracefully and prints a message if the file is not found or if the provided directory is invalid.
The initial function initiates the search process by creating a new thread for the findPathToFile function.
The program waits until the search is completed before exiting.


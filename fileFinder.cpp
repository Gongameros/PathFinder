/* This program searches for a specified file in a given directory and its subdirectories using multiple threads.
// The search process is parallelized to improve efficiency, with a limit of MAX_THREADS concurrent search threads.
// It employs atomics and mutexes to ensure thread safety and synchronized access to shared resources.
// The findPathToFile function recursively explores the directory tree, spawning threads to search in subdirectories.
// If the file is found, the program prints its path to the console and terminates all threads.
// The program handles filesystem errors gracefully and prints a message if the file is not found or if the provided directory is invalid.
// The initial function initiates the search process by creating a new thread for the findPathToFile function.
// The program waits until the search is completed before exiting.
*/


#include "fileFinder.h"

const uint8_t MAX_THREADS = 8;
std::atomic<uint8_t> workingThreads(1);
std::atomic<uint8_t> countAddThreads(0);
std::mutex mtxThread;
std::mutex mtxPrint;
std::atomic<bool> stopSearch(false);

void findPathToFile(const std::filesystem::path& directory, const std::string& filename)
{
    try
    {
        for (auto const& dir_entry : std::filesystem::directory_iterator(directory))
        {
            if (stopSearch)
                return;

            if (dir_entry.is_directory())
            {
                std::unique_lock<std::mutex> locker(mtxThread);
                if (workingThreads < MAX_THREADS)
                {
                    ++workingThreads;
                    locker.unlock();
                    std::thread searchThread(findPathToFile, dir_entry.path(), filename);
                    searchThread.detach();
                }

                else
                {
                    ++countAddThreads;
                    locker.unlock();
                    findPathToFile(dir_entry.path(), filename);
                }
            }

            if (dir_entry.is_regular_file() && dir_entry.path().filename() == filename)
            {
                std::unique_lock<std::mutex> ul(mtxPrint);
                std::cout << "Path for current file is: " << dir_entry.path() << std::endl;
                stopSearch = true;
                --workingThreads;
                ul.unlock();
                return;
            }

        }
    }

    catch (std::filesystem::filesystem_error& a){}

    if(workingThreads == MAX_THREADS && countAddThreads > 0)
        --countAddThreads;
    else
        --workingThreads;

    if (workingThreads == 0)
    { 
        stopSearch = true;
        std::cout << "File wasn`t found" << std::endl;
    }
}

void initial(const std::filesystem::path& directory, const std::string& filename)
{
    if (std::filesystem::exists(directory))
    {
        std::thread thFind(findPathToFile, directory, filename);
        thFind.detach();
    }
    else
    {
        std::cout << "Wrong Path!" << std::endl;
        return;
    }
    
    while (!stopSearch) {}
}
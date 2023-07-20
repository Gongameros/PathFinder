#include "fileFinder.h"

int main()
{
    std::string filename;
    std::cout << "Type filename: ";
    std::cin >> filename;
    std::string Path;
    std::cout << "Path from where to start: ";
    std::cin >> Path;
    
    initial(Path, filename);

    return 0;
}


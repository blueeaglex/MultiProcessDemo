#include "Base/os.h"
#include <iostream>

//using namespace boost::process;


int main()
{
    std::cout << "APP Path:" << boost::filesystem::current_path() << std::endl;
}

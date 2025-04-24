
#include <iostream>
#include <filesystem>

using namespace std;

#include "Parser.h"



int main(int argc, char *argv[])
{
    map<string, map<string,funcDescription*>*> mapInterfaces;

    std::string path = "..\\..\\interfaces_obj\\";
    for (const auto & entry : filesystem::directory_iterator(path))
    {   // std::cout <<  << std::endl;

        string iterfaceName = entry.path().string();
        if(Parser(iterfaceName, &mapInterfaces))
        {
            CreateAdapters( &mapInterfaces, "..\\..\\adapters" );
            cout<< "so happy!"<<endl;
        }
    }

    return 0;
}

#include "CacheManagement.hpp"
#include <bits/stdc++.h> 

namespace CacheManagment{
    void operate(int argc, const char** const argv) {
        //Get the second word in the string

        if (strcmp(argv[1], "clear")) {
            CacheManagment::clear();
            return;
        }


         if(strcmp(argv[1], "search")) {
            std::string print = "";
            search(print);
            std::cout << print << std::endl;
            return;
        }

        CacheOperate object(factory(str));
        auto info = std::make_unique<std::string>(object.getInfo());


        if (search(*info)) {
            //delete the i-th row
            //write to the last row
        }

        object.operate();
        //do the operation
        //write
        //add to the cache.txt
    }
}
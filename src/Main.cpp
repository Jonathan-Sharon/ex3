#include "CacheManagement/CacheManagement.h"
#include "CacheOperations/CacheOperations.h"
#include "CacheOperations/CacheOperationFactory.h"

#include <string.h>
#include <filesystem>
#include <iostream>

using namespace Operation;
using namespace std::filesystem;

int main(int argc, char const *argv[]){


    //If there are not enough arguments then return
    //the appropriate error
    if(argc < 3) {
        throw runtime_error("too little argument");
    }

    if(strcmp(argv[1], "cache") == 0){

        if(strcmp(argv[2], "search") == 0){

            std::unique_ptr<CacheOperation> cacheOperation = CacheOperationFactory::CacheOperationFactory(argc - 1, &argv[2]);
            
            CacheManagement cacheManager; 
            cacheManager.search(*cacheOperation);
            return 0;
        }
        if(strcmp(argv[2], "clear") == 0){

            CacheManagement cacheManager; 
            cacheManager.clear();
            return 0;
        }
    }

    auto cacheOperation = CacheOperationFactory::CacheOperationFactory(argc, argv);
    CacheManagement cacheManager; 
    cacheManager.operate(*cacheOperation, argv[argc-1]);

    return 0;

}
#include <string.h>
#include "CacheManagement/CacheManagement.hpp"
#include "CacheOperations/CacheOperations.hpp"
#include "CacheOperations/CacheOperationFactory.hpp"
int main(int argc, char const *argv[]){

    if(argc < 3) {
        throw runtime_error("too little arguments");
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

    std::unique_ptr<CacheOperation> cacheOperation = CacheOperationFactory::CacheOperationFactory(argc, argv);
    CacheManagement cacheManager; 
    cacheManager.operate(*cacheOperation, argv[argc-1]);

    return 0;

}
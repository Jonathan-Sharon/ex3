#pragma once
#include "../CacheOperations/CacheOperations.h"
#include <memory>

namespace CacheOperationFactory
{
    /**
     * @brief factory which creats the appropriate CacheOperation,
     * according to it's argv
     * 
     * @param argc number of arguments
     * @param argv content of the argument
     * @return std::unique_ptr<Operation::CacheOperation> unique pointer
     */
    std::unique_ptr<Operation::CacheOperation> CacheOperationFactory(int argc, const char **argv);
}
#pragma once
#include "../CacheOperations.hpp"
#include <memory>

namespace CacheOperationFactory
{
    std::unique_ptr<CacheOperation> CacheOperationFactory(const int argc, const char **argv);
}
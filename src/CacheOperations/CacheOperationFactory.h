#pragma once
#include "../CacheOperations/CacheOperations.h"
#include <memory>

namespace CacheOperationFactory
{
    std::unique_ptr<Operation::CacheOperation> CacheOperationFactory(int argc, const char **argv);
}
#pragma once
#include "../CacheOperations.hpp"
#include <memory>

namespace Factory
{
    std::unique_ptr<CacheOperation> factory(const int argc, const char **argv);
}
#pragma once
#include "../CacheOperations.hpp"

namespace Factory
{
    CacheOperation *factory(const int argc, const char **argv);
}
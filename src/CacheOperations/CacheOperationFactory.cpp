#include "CacheOperationFactory.h"

#include <stdexcept>
#include <memory>
#include <string.h>
#include <iostream>

using namespace Operation;

namespace CacheOperationFactory
{
    std::unique_ptr<CacheOperation> CacheOperationFactory(int argc, const char **argv)
    {
        if (argc < 4)
        {
            throw std::runtime_error("Too little arguments were given");
        }

        if (strcmp(argv[1], "matrix") == 0)
        {
            if (strcmp(argv[2], "add") == 0 && argc >= 6)
            {
                return std::make_unique<MatrixAddition>(argv[3], argv[4]);
            }

            if (strcmp(argv[2], "multiply") == 0 && argc >= 6)
            {
                return std::make_unique<MatrixMultipication>(argv[3], argv[4]);
            }

            throw std::runtime_error("Unvalid input!");
        }

        if (strcmp(argv[1], "image") == 0)
        {
            if (strcmp(argv[2], "rotate") == 0 && argc >= 5)
            {
                return std::make_unique<BmpRotate>(argv[3]);
            }

            if (strcmp(argv[2], "convert") == 0 && argc >= 5)
            {
                return std::make_unique<BmpConvertToGrayScale>(argv[3]);
            }

            throw std::runtime_error("Unvalid input!");
        }

        if (strcmp(argv[1], "hash") == 0)
        {
            if (strcmp(argv[2], "crc32") == 0 && argc >= 5)
            {
                return std::make_unique<BinaryStringHash>(argv[3]);
            }

            throw std::runtime_error("Unvalid input!");
        }
        throw std::runtime_error("Unvalid input!");
    }
} // namespace CacheOperationFactory

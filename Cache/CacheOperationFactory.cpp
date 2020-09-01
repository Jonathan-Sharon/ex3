#include "CacheOperationFactory.hpp"
#include <stdexcept>
#include "FileReading.hpp"
#include "../CacheOperations.hpp"
#include <memory>
#include <string.h>

namespace CacheOperationFactory
{
    std::unique_ptr<CacheOperation> CacheOperationFactory(const int argc, const char **argv)
    {
        if (argc < 3)
        {
            throw std::runtime_error("Too little arguments were given");
        }

        if (strcmp(argv[0], "matrix"))
        {
            if (strcmp(argv[1], "add") && argc >= 5)
            {
                return std::make_unique<MatrixAddition>(argv[2], argv[3]);
            }

            if (strcmp(argv[1], "multiply") && argc >= 5)
            {
                return std::make_unique<MatrixMultipication>(argv[2], argv[3]);
            }

            throw std::runtime_error("Unvalid input!");
        }

        if (strcmp(argv[0], "image"))
        {
            if (strcmp(argv[1], "rotate") && argc >= 4)
            {
                return std::make_unique<BmpRotate>(argv[2]);
            }

            if (strcmp(argv[1], "convert") && argc >= 4)
            {
                return std::make_unique<BmpConvertToGrayScale>(argv[2]);
            }

            throw std::runtime_error("Unvalid input!");
        }

        if (strcmp(argv[0], "hash"))
        {
            if (strcmp(argv[1], "crc32") && argc >= 4)
            {
                return std::make_unique<BinaryStringHash>(argv[2]);
            }

            throw std::runtime_error("Unvalid input!");
        }
        throw std::runtime_error("Unvalid input!");
    }
} // namespace CacheOperationFactory
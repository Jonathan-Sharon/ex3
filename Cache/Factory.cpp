#include "Factory.hpp"
#include <stdexcept>
#include "FileReading.hpp"
#include "../CacheOperations.hpp"
namespace Factory
{
    std::unique_ptr<CacheOperation> factory(const int argc, const char **argv)
    {
        if (argc < 3)
        {
            throw std::runtime_error("Too little arguments were given");
        }

        if (argv[0] == "matrix")
        {
            if (argv[1] == "add" && argc >= 5)
            {
                return std::make_unique<MatrixAddition>(argv[2], argv[3]);
            }

            if (argv[1] == "multiply" && argc >= 5)
            {
                return std::make_unique<MatrixMultipication>(argv[2], argv[3]);
            }

            throw std::runtime_error("Unvalid input!");
        }

        if (argv[0] == "image")
        {
            if (argv[1] == "rotate" && argc >= 4)
            {
                return std::make_unique<BmpRotate>(argv[2]);
            }

            if (argv[1] == "convert" && argc >= 4)
            {
                return std::make_unique<BmpConvertToGrayScale>(argv[2]);
            }

            throw std::runtime_error("Unvalid input!");
        }

        if (argv[0] == "hash")
        {
            if (argv[1] == "crc32" && argc >= 4)
            {
                return std::make_unique<BinaryStringHash>(argv[2]);
            }

            throw std::runtime_error("Unvalid input!");
        }
        throw std::runtime_error("Unvalid input!");
    }
} // namespace Factory
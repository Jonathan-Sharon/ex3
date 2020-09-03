#include "bmp_tester.hpp"
#include "Bmp.hpp"
#include "../fileReading/file_reading.hpp"
#include <string>

namespace testing
{
    namespace bmp
    {
        void rotate_image(const std::string &imagePath, const std::string &outputPath)
        {
            //Create a Bmp file
            Bmp bmp = Bmp(imagePath);

            //Rotate the Bmp file
            bmp.rotate();

            //write into the output path the new Bmp file
            writeFileContent(outputPath, bmp.bmpWrite());
        }

        void convert_to_grayscale(const std::string &imagePath, const std::string &outputPath)
        {
            //Create a Bmp file
            Bmp bmp = Bmp(imagePath);

            //convert the Bmp file to gray scale
            bmp.convertToGrayScale();

            //write into the output path the new Bmp file
            writeFileContent(outputPath, bmp.bmpWrite());
        }

    } // namespace bmp
} // namespace testing
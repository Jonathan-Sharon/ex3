#include "Bmp.hpp"
#include "../fileReading/file_reading.hpp"
#include <string>
#include <sys/stat.h>
#include <math.h>
#include <string.h>
#include <bits/stdc++.h>

Bmp::Bmp(const std::string &imagePath)
{
    //Check whether the imagePath exists
    if (!isFileExists(imagePath))
    {
        throw std::runtime_error("file path for the image does not exist");
    }

    //Read the file
    std::string fileString = readFileContent(imagePath);

    readBmp(fileString);
}

void Bmp::readBmp(const std::string &fileString)
{

    //The size must be more than 54 bits,
    //in order to be a valid Bmp file
    if (fileString.size() < sizeof(Header) + sizeof(DIBHeader))
    {
        throw std::runtime_error("picture format is invalid");
    }

    //read only the header
    char *headerRead = new char[sizeof(Header) + 1];
    fileString.copy(headerRead, sizeof(Header) + 1);
    header = (Header *)(headerRead);

    //Because we read the Header, now we know the size of the file
    int size = header->size - sizeof(Header);
    char *str = new char[size + 1];

    //Continue reading from the string
    //Read the DIBHeader
    fileString.substr(sizeof(Header)).copy(str, size + 1);
    dibHeader = (DIBHeader *)(str);

    //Check if the file is really a bmp file
    //We can do that now because we know the DIBHeader
    if (!isFileBmpValid())
    {
        throw std::runtime_error("picture format is invalid");
    }

    bool islLessThen8 = dibHeader->bitsPerPixel <= 8 ? true : false;
    uint32_t numberOfColors = dibHeader->numberOfColors == 0 ? pow(2, dibHeader->bitsPerPixel) : dibHeader->numberOfColors;

    //If there are only 8 bits per pixel, read the color palette
    if (islLessThen8)
    {
        for (uint32_t i = 0; i < numberOfColors; ++i)
        {
            colorPaletteArray[i] = (ColorPalette *)(&str[sizeof(DIBHeader) + 4 * i]);
        }
    }

    //continue reading
    matrixRead(fileString.substr(header->pixelArrayOffset, dibHeader->bitmapSize));
}

inline bool Bmp::isFileExists(const std::string &name)
{
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}

void Bmp::matrixRead(const std::string &str)
{

    //create a matrix
    pixelMatrix = new Matrix(static_cast<uint32_t>(dibHeader->bitmapHeight), static_cast<uint32_t>(dibHeader->bitmapWidth));

    //number the paddings
    int padding = 4 - (dibHeader->bitmapWidth * (dibHeader->bitsPerPixel / 8)) % 4;
    if (padding == 4)
    {
        padding = 0;
    }

    for (int i = 0; i < dibHeader->bitmapHeight; ++i)
    {
        for (int j = 0; j < dibHeader->bitmapWidth; ++j)
        {
            uint32_t *value = (uint32_t *)(&str[(i * (dibHeader->bitmapWidth + padding) + j) * (dibHeader->bitsPerPixel / 8)]);

            //get the value of the first 8 bits
            uint32_t newValue = *value % (uint32_t)pow(2, (double)dibHeader->bitsPerPixel);

            //Check the value
            pixelMatrix->setValue(dibHeader->bitmapHeight - i - 1, j, (double)newValue);
        }
    }
}

bool Bmp::isFileBmpValid()
{
    char str[] = "BM";
    //Check if the file starts with "BM"
    if (header->magic[0] != str[0] || header->magic[1] != str[1])
    {
        return false;
    }

    //The constant in the DIBHeader must be equal to 1
    if (dibHeader->constant != 1)
    {
        return false;
    }

    //In our exercise we dont use compression, therefor it must be equal to 0
    if (dibHeader->compression != 0)
    {
        return false;
    }

    //file is valid
    return true;
}

void Bmp::rotate()
{
    //rotate
    *(this->pixelMatrix) = this->pixelMatrix->rotate();
    std::swap(this->dibHeader->bitmapHeight, this->dibHeader->bitmapWidth);
    std::swap(this->dibHeader->horizontalResolution, this->dibHeader->verticalResolution);
}

std::string Bmp::bmpWrite()
{
    std::string fileString = "";

    const char *headerWrite = (char *)(header);
    //write header

    for (unsigned long i = 0; i < sizeof(Header); ++i)
    {
        fileString.push_back(headerWrite[i]);
    }

    //write DIBHeader
    char *dibHeaderWrite = (char *)(dibHeader);

    for (unsigned long i = 0; i < sizeof(DIBHeader); ++i)
    {
        fileString.push_back(dibHeaderWrite[i]);
    }

    uint32_t numberOfColors = dibHeader->numberOfColors == 0 ? pow(2, dibHeader->bitsPerPixel) : dibHeader->numberOfColors;

    //If there are only 8 bits per pixel, read the color palette
    if (dibHeader->bitsPerPixel == 8)
    {
        for (uint32_t i = 0; i < numberOfColors; ++i)
        {
            char *colorPaletteWrite = (char *)(colorPaletteArray[i]);

            for (unsigned long j = 0; j < sizeof(ColorPalette); ++j)
            {
                fileString.push_back(colorPaletteWrite[j]);
            }
        }
    }

    //write from matrix
    fileString += matrixWrite();

    return fileString;
}

std::string Bmp::matrixWrite()
{
    std::string fileString = "";
    //number the paddles

    int padding = 4 - (dibHeader->bitmapWidth * (dibHeader->bitsPerPixel / 8)) % 4;
    if (padding == 4)
    {
        padding = 0;
    }

    for (int i = 0; i < dibHeader->bitmapHeight; ++i)
    {
        for (int j = 0; j < dibHeader->bitmapWidth; ++j)
        {
            //double doubleValue = pixelMatrix->getValue(dibHeader->bitmapHeight - i - 1, j);
            //uint32_t uint32Value = (uint32_t)doubleValue;
            uint32_t uint32Value = (uint32_t)pixelMatrix->getValue(dibHeader->bitmapHeight - i - 1, j);
            uint32_t *value = &uint32Value;

            char *write = (char *)(value);

            for (unsigned long z = 0; z < dibHeader->bitsPerPixel / 8; ++z)
            {
                fileString.push_back(write[z]);
            }
        }

        for (int j = 0; j < padding; ++j)
        {
            fileString.push_back(0);
        }
    }

    return fileString;
}

std::uint8_t Bmp::getBlueColor(int height, int width)
{
    //get blue color
    double value = pixelMatrix->getValue(height, width);
    int newValue = (int)value;
    newValue = newValue << (8 * sizeof(int) - 8);
    newValue = newValue >> (8 * sizeof(int) - 8);
    return newValue;
}

std::uint8_t Bmp::getGreenColor(int height, int width)
{
    //get green color
    double value = pixelMatrix->getValue(height, width);
    int newValue = (int)value;
    newValue = newValue << (8 * sizeof(int) - 16);
    newValue = newValue >> (8 * sizeof(int) - 24);
    return newValue;
}

std::uint8_t Bmp::getRedColor(int height, int width)
{
    //get red color
    double value = pixelMatrix->getValue(height, width);
    int newValue = (int)value;
    newValue = newValue << (8 * sizeof(int) - 24);
    newValue = newValue >> (8 * sizeof(int) - 16);
    return newValue;
}

void Bmp::convertToGrayScale()
{
    if (dibHeader->bitsPerPixel == 8)
    {
        for (int i = 0; i < dibHeader->bitmapHeight; ++i)
        {
            for (int j = 0; j < dibHeader->bitmapWidth; ++j)
            {
                //get the palette index
                int index = pixelMatrix->getValue(i, j);
                //Calculate the gray color
                double grayValue = 0.2126 * colorPaletteArray[index]->r;
                grayValue += 0.7152 * colorPaletteArray[index]->g;
                grayValue += 0.0722 * colorPaletteArray[index]->b;

                //round the result
                int roundValue = (int)(grayValue + 0.5);

                //set the new value
                pixelMatrix->setValue(i, j, roundValue);
            }
        }
    }

    //Create the color platte
    for (int i = 0; i < 256; ++i)
    {
        colorPaletteArray[i] = new ColorPalette();
        colorPaletteArray[i]->a = 0;
        colorPaletteArray[i]->b = i;
        colorPaletteArray[i]->g = i;
        colorPaletteArray[i]->r = i;
    }

    if (dibHeader->bitsPerPixel == 24)
    {
        for (int i = 0; i < dibHeader->bitmapHeight; ++i)
        {
            for (int j = 0; j < dibHeader->bitmapWidth; ++j)
            {
                double grayValue = 0.2126 * getRedColor(i, j);
                grayValue += 0.7152 * getGreenColor(i, j);
                grayValue += 0.0722 * getBlueColor(i, j);
                int roundValue = (int)(grayValue + 0.5);

                pixelMatrix->setValue(i, j, roundValue);
            }
        }
    }

    dibHeader->numberOfColors = 256;
    header->pixelArrayOffset = sizeof(Header) + sizeof(DIBHeader) + dibHeader->numberOfColors * sizeof(ColorPalette);

    //Change bits per pixel to be 8
    dibHeader->bitsPerPixel = 8;
    header->size = sizeof(Header) + sizeof(DIBHeader) + dibHeader->numberOfColors * sizeof(ColorPalette) + dibHeader->bitmapHeight * dibHeader->bitmapWidth * dibHeader->bitsPerPixel;
}
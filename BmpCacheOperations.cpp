#include "CacheOperations.hpp"
#include "Bmp.hpp"
#include "file_reading.hpp"

BmpConvertToGrayScale::BmpConvertToGrayScale(const std::string &imagePath) : m_bmp(imagePath){}

void BmpConvertToGrayScale::operate(const std::string &outputFile){
    
    m_bmp.convertToGrayScale();
    writeFileContent(outputFile, m_bmp.bmpWrite());
}

BmpRotate::BmpRotate(const std::string &imagePath) : m_bmp(imagePath){}

void BmpRotate::operate(const std::string &outputFile){
    
    m_bmp.rotate();
    writeFileContent(outputFile, m_bmp.bmpWrite());
}
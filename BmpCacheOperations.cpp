#include "CacheOperations.hpp"
#include "Bmp.hpp"
#include "file_reading.hpp"

BmpConvertToGrayScale::BmpConvertToGrayScale(const std::string &imagePath) : m_bmp(imagePath){}

std::string BmpConvertToGrayScale::operate(){
    
    m_bmp.convertToGrayScale();
    return m_bmp.bmpWrite();
}

BmpRotate::BmpRotate(const std::string &imagePath) : m_bmp(imagePath){}

std::string BmpRotate::operate(){
    
    m_bmp.rotate();
    return m_bmp.bmpWrite();
}
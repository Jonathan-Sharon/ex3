#include "CacheOperations.hpp"
#include "Bmp.hpp"
#include "file_reading.hpp"
#include "Cache/CacheManagement.hpp"

BmpConvertToGrayScale::BmpConvertToGrayScale(const std::string &imagePath) : m_bmp(imagePath){

    CacheManagement cacheManager;
    BinaryStringHash HashOperation(imagePath);
    
    cacheManager.operate(HashOperation, "cache/tmp");
    m_bmpHash = stoi(readFileContent("cache/tmp"));

    remove("cache/tmp");
}

std::string BmpConvertToGrayScale::operate(){
    
    m_bmp.convertToGrayScale();
    return m_bmp.bmpWrite();
}

BmpRotate::BmpRotate(const std::string &imagePath) : m_bmp(imagePath){

    CacheManagement cacheManager;
    BinaryStringHash HashOperation(imagePath);
    
    cacheManager.operate(HashOperation, "cache/tmp");
    m_bmpHash = stoi(readFileContent("cache/tmp"));

    remove("cache/tmp");
}

std::string BmpRotate::operate(){
    
    m_bmp.rotate();
    return m_bmp.bmpWrite();
}
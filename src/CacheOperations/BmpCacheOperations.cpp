#include "../fileReading/file_reading.h"
#include "../CacheManagement/CacheManagement.h"

using namespace Operation;

BmpConvertToGrayScale::BmpConvertToGrayScale(const std::string &imagePath) : m_bmp(imagePath){

    CacheManagement cacheManager;
    BinaryStringHash HashOperation(imagePath);
    
    cacheManager.operate(HashOperation, "src/bin/cache/tmp.txt");
    m_bmpHash = stoi(readFileContent("src/bin/cache/tmp.txt"));

    remove("src/bin/cache/tmp.txt");
}

const std::string BmpConvertToGrayScale::getInfo(){

    return "image convert " + m_bmpHash;
}

const std::string BmpConvertToGrayScale::operate(){
    
    m_bmp.convertToGrayScale();
    return m_bmp.bmpWrite();
}


BmpRotate::BmpRotate(const std::string &imagePath) : m_bmp(imagePath){

    CacheManagement cacheManager;
    BinaryStringHash HashOperation(imagePath);
    
    cacheManager.operate(HashOperation, "src/bin/cache/tmp");
    m_bmpHash = stoi(readFileContent("src/bin/cache/tmp"));

    remove("src/bin/cache/tmp");
}

const std::string BmpRotate::operate(){
    
    m_bmp.rotate();
    return m_bmp.bmpWrite();
}

const std::string BmpRotate::getInfo(){

    return "image rotate " + m_bmpHash;
}
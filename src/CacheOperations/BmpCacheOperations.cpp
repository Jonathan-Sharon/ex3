#include "../fileReading/file_reading.h"
#include "../CacheManagement/CacheManagement.h"

using namespace Operation;
using namespace CacheManagement;

BmpConvertToGrayScale::BmpConvertToGrayScale(const std::string &imagePath) : m_bmp(imagePath){

    CacheManagement::CacheManagement cacheManager;
    BinaryStringHash HashOperation(imagePath);

    //calculate the hash of the image
    cacheManager.operate(HashOperation, "src/bin/cache/tmp.txt");
    m_bmpHash = stoul(readFileContent("src/bin/cache/tmp.txt"));

    remove("src/bin/cache/tmp.txt");
}

std::string BmpConvertToGrayScale::getInfo() const{

    return "image convert " + to_string(m_bmpHash);
}

std::string BmpConvertToGrayScale::operate(){
    //Do the operation
    m_bmp.convertToGrayScale();
    return m_bmp.bmpWrite();
}


BmpRotate::BmpRotate(const std::string &imagePath) : m_bmp(imagePath){

    CacheManagement::CacheManagement cacheManager;
    BinaryStringHash HashOperation(imagePath);
    
    //get the hash og the image
    cacheManager.operate(HashOperation, "src/bin/cache/tmp.txt");
    m_bmpHash = stoul(readFileContent("src/bin/cache/tmp.txt"));

    remove("src/bin/cache/tmp.txt");
}

std::string BmpRotate::operate(){
    //do the operation
    m_bmp.rotate();
    return m_bmp.bmpWrite();
}

std::string BmpRotate::getInfo() const{
    //get the info about the operation
    return "image rotate " + to_string(m_bmpHash);
}
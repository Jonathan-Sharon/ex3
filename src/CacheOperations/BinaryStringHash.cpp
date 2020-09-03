#include "CacheOperations.h"

#include "../Hash/crc32.c"
#include "../fileReading/file_reading.h"

#include <string>
#include <cstring>
#include <memory>

using namespace Operation;

    BinaryStringHash::BinaryStringHash(const std::string &filePath) :
     m_str(readFileContent(filePath)), m_filePath(filePath) {}


    const std::string BinaryStringHash::operate(){

        auto cstr = std::make_unique<unsigned char[]>(m_str.size() + 1);
        strcpy(reinterpret_cast<char*>(cstr.get()), m_str.c_str());

        //unsigned char* cstr =  new unsigned char[m_str.size() + 1];
	    //strcpy((char *)cstr, m_str.c_str());
        //calculate the hash
        auto hash = calculate_crc32c(0, cstr.get(), m_str.length());
        return to_string(hash);
    }

    const std::string BinaryStringHash::getInfo() const{

        return "hash crc32 " + m_filePath;
    }
    

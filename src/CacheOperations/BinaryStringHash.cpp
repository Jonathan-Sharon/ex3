#include "CacheOperations.hpp"
#include "../Hash/crc32.c"
#include "../fileReading/file_reading.hpp"
#include <string>
#include <cstring>

    BinaryStringHash::BinaryStringHash(const std::string &filePath){

        m_str = readFileContent(filePath);
        m_filePath = filePath;
    }

    std::string BinaryStringHash::operate(){

        unsigned char* cstr =  new unsigned char[m_str.size() + 1];
	    strcpy((char *)cstr, m_str.c_str());
        std::uint32_t hash = calculate_crc32c(0, cstr, m_str.length());

        return to_string(hash);
    }

    std::string BinaryStringHash::getInfo(){

        return "hash crc32 " + m_filePath;
    }
    
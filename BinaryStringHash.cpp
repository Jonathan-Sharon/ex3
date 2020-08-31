#include "CacheOperations.hpp"
#include "crc32.c"
#include "file_reading.hpp"
#include <string>
#include <cstring>

    BinaryStringHash::BinaryStringHash(const std::string &filePath){

        m_str = readFileContent(filePath);
        m_filePath = filePath;
    }

    std::string BinaryStringHash::operate() const{

        unsigned char cstr[m_str.size() + 1];
	    strcpy((char *)cstr, m_str.c_str());
        std::uint32_t hash = calculate_crc32c(0, cstr, m_str.length());

        return to_string(hash);
    }

    std::string BinaryStringHash::getInfo() const{

        return "hash crc32 " + m_filePath;
    }
    

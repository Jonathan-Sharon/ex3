#include "CacheOperations.h"
#include "../Matrix/Matrix.hpp"
#include "../CacheManagement/CacheManagement.hpp"
#include "../fileReading/file_reading.hpp"

using namespace Operation;


MatrixAddition::MatrixAddition(const std::string &matrix1, const std::string &matrix2) : m_matrix1(matrix1), m_matrix2(matrix2){

    CacheManagement cacheManager1;
    CacheManagement cacheManager2;

    BinaryStringHash matrix1HashOperation(matrix1);
    BinaryStringHash matrix2HashOperation(matrix2);
    
    cacheManager1.operate(matrix1HashOperation, "src/bin/cache/tmp.txt");
    m_matrix1Hash = stoi(readFileContent("src/bin/cache/tmp.txt"));

    cacheManager2.operate(matrix2HashOperation, "src/bin/cache/tmp.txt");
    m_matrix2Hash = stoi(readFileContent("src/bin/cache/tmp.txt"));

    remove("src/bin/cache/tmp.txt");
}

const std::string MatrixAddition::operate(){

    return (m_matrix1 + m_matrix2).toString();
}

const std::string MatrixAddition::getInfo(){

    return "matrix add " + to_string(m_matrix1Hash) + " " + to_string(m_matrix2Hash);
}


MatrixMultipication::MatrixMultipication(const std::string &matrix1, const std::string &matrix2) : m_matrix1(matrix1), m_matrix2(matrix2){

    CacheManagement cacheManager1;

    BinaryStringHash matrix1HashOperation(matrix1);
    BinaryStringHash matrix2HashOperation(matrix2);
    
    cacheManager1.operate(matrix1HashOperation, "cache/tmp");
    m_matrix1Hash = stoi(readFileContent("cache/tmp"));

    CacheManagement cacheManager2;
    
    cacheManager2.operate(matrix2HashOperation, "cache/tmp");
    m_matrix2Hash = stoi(readFileContent("cache/tmp"));

    remove("cache/tmp");
}

const std::string MatrixMultipication::operate(){

    return (m_matrix1 * m_matrix2).toString();
}

const std::string MatrixMultipication::getInfo(){

    return "matrix multiply " + to_string(m_matrix1Hash) + " " + to_string(m_matrix2Hash);
}
#include "CacheOperations.h"
#include "../Matrix/Matrix.h"
#include "../CacheManagement/CacheManagement.h"
#include "../fileReading/file_reading.h"

using namespace Operation;
using namespace CacheManagement;


MatrixAddition::MatrixAddition(const std::string &matrix1, const std::string &matrix2) : m_matrix1(matrix1), m_matrix2(matrix2){

    CacheManagement::CacheManagement cacheManager1;

    BinaryStringHash matrix1HashOperation(matrix1);
    BinaryStringHash matrix2HashOperation(matrix2);
    
    cacheManager1.operate(matrix1HashOperation, "src/bin/cache/tmp.txt");
    m_matrix1Hash = stoul(readFileContent("src/bin/cache/tmp.txt"));

    CacheManagement::CacheManagement cacheManager2;

    cacheManager2.operate(matrix2HashOperation, "src/bin/cache/tmp.txt");
    m_matrix2Hash = stoul(readFileContent("src/bin/cache/tmp.txt"));

    remove("src/bin/cache/tmp.txt");
}

const std::string MatrixAddition::operate(){

    return (m_matrix1 + m_matrix2).toString();
}

const std::string MatrixAddition::getInfo() const{

    return "matrix add " + to_string(m_matrix1Hash) + " " + to_string(m_matrix2Hash);
}


MatrixMultipication::MatrixMultipication(const std::string &matrix1, const std::string &matrix2) : m_matrix1(matrix1), m_matrix2(matrix2){

    CacheManagement::CacheManagement cacheManager1;

    BinaryStringHash matrix1HashOperation(matrix1);
    BinaryStringHash matrix2HashOperation(matrix2);
    
    cacheManager1.operate(matrix1HashOperation, "src/bin/cache/tmp.txt");
    m_matrix1Hash = stoul(readFileContent("src/bin/cache/tmp.txt"));

    CacheManagement::CacheManagement cacheManager2;
    
    cacheManager2.operate(matrix2HashOperation, "src/bin/cache/tmp.txt");
    m_matrix2Hash = stoul(readFileContent("src/bin/cache/tmp.txt"));

    remove("src/bin/cache/tmp.txt");
}

const std::string MatrixMultipication::operate(){

    return (m_matrix1 * m_matrix2).toString();
}

const std::string MatrixMultipication::getInfo() const{

    return "matrix multiply " + to_string(m_matrix1Hash) + " " + to_string(m_matrix2Hash);
}
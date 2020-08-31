#include "CacheOperations.hpp"
#include "Matrix.hpp"

MatrixAddition::MatrixAddition(const std::string &matrix1, const std::string &matrix2) : m_matrix1(matrix1), m_matrix2(matrix2){}

void MatrixAddition::operate(const std::string &outputFile){

    (m_matrix1 + m_matrix2).toFile(outputFile);
}


MatrixMultipication::MatrixMultipication(const std::string &matrix1, const std::string &matrix2) : m_matrix1(matrix1), m_matrix2(matrix2){}

void MatrixMultipication::operate(const std::string &outputFile){

    (m_matrix1 * m_matrix2).toFile(outputFile);
}
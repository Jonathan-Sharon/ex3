#include "CacheOperations.hpp"
#include "Matrix.hpp"

MatrixAddition::MatrixAddition(const std::string &matrix1, const std::string &matrix2) : m_matrix1(matrix1), m_matrix2(matrix2){}

std::string MatrixAddition::operate(){

    (m_matrix1 + m_matrix2).toString();
}

std::string MatrixAddition::getInfo(){

    return "matrix add " + to_string(m_matrix1Hash) + " " + to_string(m_matrix2Hash);
}


MatrixMultipication::MatrixMultipication(const std::string &matrix1, const std::string &matrix2) : m_matrix1(matrix1), m_matrix2(matrix2){}

std::string MatrixMultipication::operate(){

    (m_matrix1 * m_matrix2).toString();
}
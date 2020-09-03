#pragma once

#include <string>
#include "../Matrix/Matrix.h"
#include "../Bmp/Bmp.hpp"

namespace Operation {
class CacheOperation
{
public:

    virtual const std::string getInfo() = 0;
    virtual const std::string operate() = 0;
    virtual ~CacheOperation() { };
};

class MatrixAddition : public CacheOperation
{
public:

    MatrixAddition(const std::string &matrix1, const std::string &matrix2);
    virtual const std::string getInfo();
    virtual const std::string operate();

private:
    
    const Matrix m_matrix1;
    const Matrix m_matrix2;
    std::uint32_t m_matrix1Hash;
    std::uint32_t m_matrix2Hash;
};

class MatrixMultipication : public CacheOperation
{
public:

    MatrixMultipication(const std::string &matrix1, const std::string &matrix2);
    virtual const std::string getInfo();
    virtual const std::string operate();

private:
    
    Matrix m_matrix1;
    Matrix m_matrix2;
    std::uint32_t m_matrix1Hash;
    std::uint32_t m_matrix2Hash;
};

class BmpConvertToGrayScale : public CacheOperation
{
public:

    BmpConvertToGrayScale(const std::string &imagePath);
    virtual const std::string getInfo();
    virtual const std::string operate();

private:
    
    Bmp m_bmp;
    std::uint32_t m_bmpHash;  
};

class BmpRotate : public CacheOperation
{
public:

    BmpRotate(const std::string &imagePath);
    virtual const std::string getInfo();
    virtual const std::string operate();

private:
    
    Bmp m_bmp;
    std::uint32_t m_bmpHash;  
};

class BinaryStringHash : public CacheOperation
{
public:

    explicit BinaryStringHash(const std::string &filePath);
    virtual const std::string getInfo();
    virtual const std::string operate();

private:

    const std::string m_str;
    const std::string m_filePath;
};

}// namespace Operation

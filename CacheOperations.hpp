#pragma once
#include <string>
#include "Matrix.hpp"
#include "Bmp.hpp"

class CacheOperation
{
public:

    virtual std::string getInfo() = 0;
    virtual std::string  operate() = 0;
};

class MatrixAddition : public CacheOperation
{
public:

    MatrixAddition(const std::string &matrix1, const std::string &matrix2);
    virtual std::string getInfo();
    virtual std::string operate();

private:
    
    Matrix m_matrix1;
    Matrix m_matrix2;
    std::uint32_t m_matrix1Hash;
    std::uint32_t m_matrix2Hash;
};

class MatrixMultipication : public CacheOperation
{
public:

    MatrixMultipication(const std::string &matrix1, const std::string &matrix2);
    virtual std::string getInfo();
    virtual std::string operate();

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
    virtual std::string getInfo();
    virtual std::string operate();

private:
    
    Bmp m_bmp;
    std::uint32_t m_bmpHash;  
};

class BmpRotate : public CacheOperation
{
public:

    BmpRotate(const std::string &imagePath);
    virtual std::string getInfo();
    virtual std::string operate();

private:
    
    Bmp m_bmp;
    std::uint32_t m_bmpHash;  
};

class BinaryStringHash : public CacheOperation
{
public:

    BinaryStringHash(const std::string &filePath);
    virtual std::string getInfo();
    virtual std::string operate();

private:

    std::string m_str;
    std::string m_filePath;
};



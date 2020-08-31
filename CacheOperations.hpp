#pragma once
#include <string>
#include "Matrix.hpp"
#include "Bmp.hpp"

class CacheOperation
{
public:

    virtual std::string getInfo() = 0;
    virtual void operate(const std::string &outputFile) = 0;
};

class MatrixAddition : public CacheOperation
{
public:

    MatrixAddition(const std::string &matrix1, const std::string &matrix2);
    virtual std::string getInfo();
    virtual void operate(const std::string &outputFile);

private:
    
    Matrix m_matrix1;
    Matrix m_matrix2;
};

class MatrixMultipication : public CacheOperation
{
public:

    MatrixMultipication(const std::string &matrix1, const std::string &matrix2);
    virtual std::string getInfo();
    virtual void operate(const std::string &outputFile);

private:
    
    Matrix m_matrix1;
    Matrix m_matrix2;
};

class BmpConvertToGrayScale : public CacheOperation
{
public:

    BmpConvertToGrayScale(const std::string &imagePath);
    virtual std::string getInfo();
    virtual void operate(const std::string &outputFile);

private:
    
    Bmp m_bmp;  
};

class BmpRotate : public CacheOperation
{
public:

    BmpRotate(const std::string &imagePath);
    virtual std::string getInfo();
    virtual void operate(const std::string &outputFile);

private:
    
    Bmp m_bmp;  
};



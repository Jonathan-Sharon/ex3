#pragma once

#include <string>
#include "../Matrix/Matrix.hpp"
#include "../Bmp/Bmp.h"

namespace Operation {
class CacheOperation
{
public:
    /**
     * @brief Get info about the operation
     * 
     * @return const std::string the info about the operation
     */
    virtual std::string getInfo() const = 0;

    /**
     * @brief the actual operation the object should do
     * 
     * @return const std::string which represents the operation
     */
    virtual std::string operate() = 0;

    /**
     * @brief Destroy the Cache Operation object
     * 
     */
    virtual ~CacheOperation() { };
};

class MatrixAddition : public CacheOperation
{
public:
    /**
     * @brief Construct a new Matrix Addition object
     * 
     * @param matrix1 the first matrix
     * @param matrix2 the second matrix
     */
    explicit MatrixAddition(const std::string &matrix1, const std::string &matrix2);
    virtual std::string getInfo() const;
    virtual std::string operate();

private:
    
    const Matrix m_matrix1;
    const Matrix m_matrix2;
    std::uint32_t m_matrix1Hash;
    std::uint32_t m_matrix2Hash;
};

class MatrixMultipication : public CacheOperation
{
public:
    /**
     * @brief Construct a new Matrix Multipication object
     * 
     * @param matrix1 the first Matrix
     * @param matrix2 the second matrix
     */
    explicit MatrixMultipication(const std::string &matrix1, const std::string &matrix2);
    virtual std::string getInfo() const;
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

    /**
     * @brief Construct a new Bmp Convert To Gray Scale object
     * 
     * @param imagePath the path to the image
     */
    explicit BmpConvertToGrayScale(const std::string &imagePath);
    virtual std::string getInfo() const;
    virtual std::string operate();

private:
    
    Bmp m_bmp;
    std::uint32_t m_bmpHash;  
};

class BmpRotate : public CacheOperation
{
public:

    /**
     * @brief Construct a new Bmp Rotate object
     * 
     * @param imagePath the path to the image
     */
    explicit BmpRotate(const std::string &imagePath);
    virtual std::string getInfo() const;
    virtual std::string operate();

private:
    
    Bmp m_bmp;
    std::uint32_t m_bmpHash;  
};

class BinaryStringHash : public CacheOperation
{
public:

    /**
     * @brief Construct a new Binary String Hash object
     * 
     * @param filePath the path to the file to be hashed
     */
    explicit BinaryStringHash(const std::string &filePath);
    virtual std::string getInfo() const;
    virtual std::string operate();

private:

    const std::string m_str;
    const std::string m_filePath;
};

}// namespace Operation

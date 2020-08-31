
#include "Matrix.h"
#include "ErrorCode.h"
#include "MatrixErrorCode.hpp"
#include "Matrix.hpp"
#include <cstdint>
#include <utility>
#include <string>
#include <fstream>
#include "file_reading.hpp"
#include <algorithm>
#include <iostream>

using namespace std;

Matrix::Matrix(std::uint32_t height, std::uint32_t width)
{
  // create
  auto pmatrix = new PMatrix;
  auto code = matrix_create(pmatrix, height, width);

  // If, for some reason, an error occured, throw an exception
  if (!error_isSuccess(code))
  {
    throw MatrixErrorCode(code);
  }

  // assign
  this->m_matrix = *pmatrix;
}


Matrix::Matrix(const string &filePath){

  string fileContent = readFileContent(filePath);
  std::uint32_t height = count(fileContent.begin(), fileContent.end(), '\n')+1;
  std::uint32_t width = count(fileContent.begin(), fileContent.end(), ',') / height + 1;
  
  // create
  auto pmatrix = new PMatrix;
  auto code = matrix_create(pmatrix, height, width);

  // If, for some reason, an error occured, throw an exception
  if (!error_isSuccess(code))
  {
    throw MatrixErrorCode(code);
  }

  // assign
  this->m_matrix = *pmatrix;

  string::size_type sz = 0;
  
  for(uint32_t i=0; i<height; ++i){

    for(uint32_t j=0; j<width; ++j){

      string::size_type temp;
      while(!isdigit(fileContent[sz])){

        sz ++;
      }
      matrix_setValue(*pmatrix , i, j, stod(fileContent.substr(sz), &temp));

      sz += temp;     
    }
  }
}

Matrix::Matrix(const Matrix &other)
{
  // Copy
  auto pmatrix = new PMatrix;
  auto code = matrix_copy(pmatrix, other.m_matrix);

  // If, for some reason, an error occured, throw an exception
  if (!error_isSuccess(code))
  {
    throw MatrixErrorCode(code);
  }

  // assign
  this->m_matrix = *pmatrix;
}

Matrix &Matrix::operator=(const Matrix &other)
{
  // Copy assignment operator
  // If the this matrix and other equals, return *this
  // Else, delete "this" matrix and create another one
  if (this == &other)
  {
    return *this;
  }

  reset();
  auto pmatrix = new PMatrix;
  this->m_matrix = *pmatrix;
  *this = Matrix(other);
  return *this;
}

Matrix::Matrix(Matrix &&other) noexcept
{
  // move
  m_matrix = std::exchange(other.m_matrix, nullptr);
}

Matrix &Matrix::operator=(Matrix &&other) noexcept
{
  // Move assignment operator
  // If "this" matrix and "other" equals, return *this
  // Else, move "other" to "this"
  if (this == &other)
  {
    return *this;
  }

  reset();
  m_matrix = std::exchange(other.m_matrix, nullptr);
  return *this;
}

Matrix::~Matrix()
{
  // Destructor
  reset();
}

std::uint32_t Matrix::getHeight() const
{
  // returns the height of the matrix.
  std::uint32_t height;
  auto code = matrix_getHeight(m_matrix, &height);

  // If, for some reason, an error occured, throw an exception
  if (!error_isSuccess(code))
  {
    throw MatrixErrorCode(code);
  }

  return height;
}

std::uint32_t Matrix::getWidth() const
{
  // returns the width of the matrix.
  std::uint32_t width;
  auto code = matrix_getWidth(m_matrix, &width);

  // If, for some reason, an error occured, throw an exception
  if (!error_isSuccess(code))
  {
    throw MatrixErrorCode(code);
  }

  return width;
}

double Matrix::getValue(uint32_t rowIndex, uint32_t colIndex) const
{
  // returns the value at [rawIndex, colIndex]
  double value;
  auto code = matrix_getValue(m_matrix, rowIndex, colIndex, &value);

  // If, for some reason, an error occured, throw an exception
  if (!error_isSuccess(code))
  {
    throw MatrixErrorCode(code);
  }
  return value;
}

void Matrix::setValue(uint32_t rowIndex, uint32_t colIndex, double value)
{
  // Sets a value to the matrix.
  auto code = matrix_setValue(m_matrix, rowIndex, colIndex, value);

  // If, for some reason, an error occured, throw an exception
  if (!error_isSuccess(code))
  {
    throw MatrixErrorCode(code);
  }
}

double Matrix::operator()(uint32_t rowIndex, uint32_t colIndex) const
{
  // returns the value at [rawIndex, colIndex]
  return this->getValue(rowIndex, colIndex);
}

Matrix Matrix::operator+(const Matrix &other) const
{
  // Computes the addition of two matrices.
  Matrix result(this->getHeight(), this->getWidth());
  auto code = matrix_add(&result.m_matrix, m_matrix, other.m_matrix);

  // If, for some reason, an error occured, throw an exception
  if (!error_isSuccess(code))
  {
    throw MatrixErrorCode(code);
  }

  return result;
}

Matrix Matrix::operator*(const Matrix &other) const
{
  // Computes the multiplication of two matrices.
  Matrix result(this->getHeight(), other.getWidth());
  auto code = matrix_multiplyMatrices(&result.m_matrix, m_matrix, other.m_matrix);

  // If, for some reason, an error occured, throw an exception
  if (!error_isSuccess(code))
  {
    throw MatrixErrorCode(code);
  }

  return result;
}

void Matrix::operator*(double scalar)
{
  // Multiplies a matrix with a scalar and stores the result in the given
  // matrix.
  auto code = matrix_multiplyWithScalar(m_matrix, scalar);

  // If, for some reason, an error occured, throw an exception
  if (!error_isSuccess(code))
  {
    throw MatrixErrorCode(code);
  }
}

Matrix Matrix::add(const Matrix &other) const
{
  // Computes the addition of two matrices.
  return *this + other;
}

Matrix Matrix::multiplyMatrices(const Matrix &other) const
{
  // Computes the multiplication of two matrices.
  return (*this) * other;
}

void Matrix::multiplyWithScalar(double scalar)
{
  // Multiplies a matrix with a scalar and stores the result in the given
  // matrix.
  (*this) * scalar;
}

void Matrix::reset()
{
  // reset all the values, height and width to 0.
  matrix_destroy(m_matrix);
}

Matrix Matrix::rotate() const
{

  Matrix result(this->getWidth(), this->getHeight());

  //rotate
  for (uint32_t i = 0; i < result.getHeight(); ++i)
  {

    for (uint32_t j = 0; j < result.getWidth(); ++j)
    {

      result.setValue(i, j, (*this)(this->getHeight() - j - 1, i));
    }
  }

  return result;
}

string Matrix::toString(){

  string content;

  for(uint32_t i=0; i < this -> getHeight(); ++i){

    for(uint32_t j=0; j < this -> getWidth() - 1; ++j){

      content.append(to_string(this -> getValue(i,j)) + ", ");
    }

    content.append(to_string(this -> getValue(i, this -> getWidth() -1)) + "\n");
  }

  return content;
}

#include <string>
#include "Matrix.hpp"
#pragma pack(push, 1)

struct Header
{
  char magic[2];
  uint32_t size = 0;
  uint16_t reserved1 = 0;
  uint16_t reserved2 = 0;
  uint32_t pixelArrayOffset = 0;
};

struct DIBHeader
{
  uint32_t size = 0;
  int32_t bitmapWidth = 0;
  int32_t bitmapHeight = 0;
  uint16_t constant = 0;
  uint16_t bitsPerPixel = 0;
  uint32_t compression = 0;
  uint32_t bitmapSize = 0;
  int32_t horizontalResolution = 0;
  int32_t verticalResolution = 0;
  uint32_t numberOfColors = 0;
  uint32_t numberOfImportantColors = 0;
};

struct ColorPalette
{
  uint8_t b = 0;
  uint8_t g = 0;
  uint8_t r = 0;
  uint8_t a = 0;
};

#pragma pack(pop)
class Bmp
{
public:
  /**
 * @brief Construct a new Bmp object
 * 
 * @param imagePath the path to the Bmp file to construct
 */
  Bmp(const std::string &imagePath);

  /**
 * @brief read file to bmp class
 * 
 * @param string the string to be read by the BMP
 */
  void readBmp(const std::string &string);

  /**
   * @brief read the string into the matrix
   * 
   * @param string the string to be read by the Matrix
   */
  void matrixRead(const std::string &string);

  /**
 * @brief write the information in the BMP class into a string
 * 
 * @return std::string  the string which represents the BMP
 */
  std::string bmpWrite();

  /**
 * @brief write the information in the Matrix class into a string
 * 
 * @return std::string  the string which represents the Matrix
 */
  std::string matrixWrite();

  /**
 * @brief checks if the file truly exists in the path
 * 
 * @param imagePath the path to check whether the file exists
 * @return true the file exists
 * @return false the file does not exist
 */
  inline bool isFileExists(const std::string &imagePath);

  /**
   * @brief check if the parameters in the file trult indicates he is a valid BMP file
   * 
   * @return true the Bmp file is valid
   * @return false the Bmp file is not valid
   */
  bool isFileBmpValid();

  /**
 * @brief Get the Blue Color object
 * 
 * @return std::uint8_t represents the Blue color
 */
  std::uint8_t getBlueColor(int, int);

  /**
   * @brief Get the Green Color object
   * 
   * @return std::uint8_t represents the Green color
   */
  std::uint8_t getGreenColor(int, int);

  /**
   * @brief Get the Green Color object
   * 
   * @return std::uint8_t represents the Red color
   */
  std::uint8_t getRedColor(int, int);

  /**
   * @brief rotate the file
   * 
   */
  void rotate();

  /**
   * @brief convert the file to be gray scale
   * 
   */
  void convertToGrayScale();

private:
  //fields
  Header *header;
  DIBHeader *dibHeader;
  ColorPalette *colorPaletteArray[256];
  Matrix *pixelMatrix;
};
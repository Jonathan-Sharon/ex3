#pragma once
#include "../CacheOperations/CacheOperations.h"

#include <string>
#include <vector>
namespace CacheManagement {
class CacheManagement
{
public:
    /**
    * @brief Construct a new Cache Management object
    * 
    */
    CacheManagement();

    /**
     * @brief the method finds out if an operation already happened before.
     * If it did, then take the reuslt. Else, put the result in the cache
     * 
     * @param operation the operation find out if had happened
     * @param outputFile the output file to write to
     */
    void operate(Operation::CacheOperation &operation, const std::string &outputFile);
    void clear();

    /**
     * @brief the function gets a string, and checks if it's in m_fileContent.
     * If it isn't then it return false. If it is, then it prints the appropriate message
     * and return true
     * 
     * @return true if the string appears in m_fileContent
     * @return false if it does not
     */
    void search(const Operation::CacheOperation &operation) const;

private:
    /**
 * @brief gets a string, and delets the line in which equals to that string.
 * 
 */
    void deleteLine(const std::string &);

    /**
     * @brief get a string, and get her values into m_argc and m_argv
     * 
     */
    void takeTheLineValues(const std::string &);

    /**
     * @brief check if the operation is valid
     * 
     * @param argc number of words
     * @param argv the input
     * @return true if the operatino is valid
     * @return false if it isn't
     */
    bool operationIsValid(int argc, const char **const argv) const;

    const std::string m_filePath;
    std::vector<std::string> m_line;
    size_t m_argc;
    std::string m_fileContent;
    uint8_t m_sizeOfCache;
};
} //namespace Cache Management
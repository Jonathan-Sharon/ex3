#pragma once
#include <string>
#include "../CacheOperations.hpp"

class CacheManagement
{
public:
    CacheManagement();
    void operate(CacheOperation &operation, const std::string &outputFile);
    void clear();

    /**
     * @brief the function gets a string, and checks if it's in m_fileContent.
     * If it isn't then it return false. If it is, then it prints the appropriate message
     * and return true
     * 
     * @return true if the string appears in m_fileContent
     * @return false if it does not
     */
    bool search(const CacheOperation &operation, bool print) const;

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

    const std::string m_filePath = "cache.txt";
    std::string m_fileContent;
    char **m_line;
    int m_argc;
    int m_sizeOfCache;
};
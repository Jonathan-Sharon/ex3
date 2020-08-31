#pragma once
#include <string>

class CacheManagement
{
public:
    CacheManagement();
    void operate(int argc, const char **const argv);
    void clear();
    int search(const std::string &) const;

private:
    void deleteLine(int n);
    void createTheLine(int);
    bool operationIsValid(int argc, const char **const argv) const;

    const std::string m_filePath = "cache.txt";
    std::string m_fileContent;
    char **m_line;
    int m_argc;
    int m_sizeOfCache;
};
#pragma once
#include <string>

class CacheManagement
{
public:
    CacheManagement();
    void operate(int argc, const char **const argv);
    void clear();
    int search(std::string &) const;

private:
    void deleteLine(const char *file_name, int n);
    void createTheLine(int);

    std::string m_fileContent;
    char **m_line;
    int m_argc;
    const std::string m_fileName = "cache.txt";
};
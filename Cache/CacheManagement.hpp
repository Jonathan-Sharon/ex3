#pragma once
#include <string>

class CacheManagement
{
public:
    CacheManagement();
    void operate(const std::string &);
    void clear();
    int search(std::string &);

private:
    const std::string searchOutputFileName(int);
    const std::time_t searchTimeStamp(int);
    void deleteLine(const char *file_name, int n);

    std::string m_file;
};
#include "CacheManagement.hpp"
#include "FileReading.hpp"
#include <time.h>
#include <bits/stdc++.h>
#include "../CacheOperations.hpp"
#include <regex>
#include <iostream>

//#include <clock>

//#include <filesystem>

#define CACHE_MAX_SIZE 10

using namespace std::filesystem;

CacheManagement::CacheManagement()
{
    m_fileContent = readFileContent(m_filePath);

    //The first line will contain the size of
    //the cache. If the file is empty then the size of the
    //cache will be equal to 0
    if (m_fileContent.empty())
    {
        m_fileContent.append("0\n");
        m_sizeOfCache = 0;
    }
    else
    {
        std::string firstLine = m_fileContent.substr(0, m_fileContent.find("\n"));
        m_sizeOfCache = stoi(firstLine);
    }
}

void CacheManagement::operate(CacheOperation &operation, const std::string &outputFile)
{
    auto operationInfo = operation.getInfo();
    size_t found = m_fileContent.find(operationInfo);

    if(found != string::npos){

        auto info = m_fileContent.substr(found, m_fileContent.find("\n", found) - found);
        
        takeTheLineValues(info);

        //Copy the file to our needed output file
        copy_file(m_line[m_argc - 1], outputFile);

        //delete the line
        //(afterwards we will create a newer line)
        m_fileContent.replace(found, info.length()+1, "");

        //Create a new row at the end of the file
        m_fileContent.append(info + "\n");
        writeFileContent(m_filePath, m_fileContent);
        return;
    }

    //If we got here, we could not take the operation from the cache
    
    //calculating the operation
    auto result = operation.operate();

    //If the cache size is too big then delete the least used operation,
    //which is in the first line
    if (m_sizeOfCache >= CACHE_MAX_SIZE)
    {
        //delete the first line
        size_t zeroRowEnds = m_fileContent.find("\n");
        size_t firstRowEnds = m_fileContent.find("\n", zeroRowEnds + 1);
        size_t firstCharInFileName = m_fileContent.find_last_of(' ', firstRowEnds)+1;
        
        remove(m_fileContent.substr(firstCharInFileName, firstRowEnds - firstCharInFileName));
        m_fileContent.replace(zeroRowEnds, firstRowEnds - zeroRowEnds, "");

        //update the size of cache
        --m_sizeOfCache;
    }

    ++m_sizeOfCache;
    
    auto newFile = "cache/" + regex_replace(operationInfo, basic_regex(" "), "_");
    writeFileContent(newFile, result);
    writeFileContent(outputFile, result);

    //Create a new row at the end of the file
    m_fileContent.append(operationInfo + " " + newFile + "\n");
    
    //change the size of the cache in the string (m_fileContent)
    m_fileContent.replace(0, m_fileContent.find("\n"), std::to_string(m_sizeOfCache));

    //write m_fileContent to our file
    writeFileContent(m_filePath, m_fileContent);

    return;
}

void CacheManagement::clear()
{
    m_fileContent.clear();
    writeFileContent(m_filePath, m_fileContent);
}

void CacheManagement::search(CacheOperation &operation) const
{
    if(m_fileContent.find(operation.getInfo()) != string::npos){

        std::cout << "result found in cache" << std::endl;
        return;
    }

    std::cout << "The result was not found in cache" << std::endl;
}


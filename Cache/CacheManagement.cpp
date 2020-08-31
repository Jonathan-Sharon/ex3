#include "CacheManagement.hpp"
#include "FileReading.hpp"
#include <time.h>
#include <bits/stdc++.h>
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

void CacheManagement::operate(int argc, const char **const argv)
{
    //Check if the input that has been given is valid
    if (!operationIsValid(argc, argv))
    {
        throw std::runtime_error("invalid input !");
    }

    //If one of the input files does not exist, return the appropiate error
    int numberOfInputFiles = argc - 3;
    for (int i = 0; i < numberOfInputFiles; ++i)
    {
        //check if all the input files exists.
        //there are 2 arguments needed before the first input file
        if (exists(argv[2 + i]))
        {
            throw std::runtime_error("path " + std::string(argv[2 + i]) + " does not exists");
        }
    }

    //Now we know that the argv and argc that we got are valid.
    //What i'll do know is to check if the operation in related to the
    //cache

    //Get the second word in the string
    //If it equals to any of the cache operations,
    //then do them
    if (strcmp(argv[0], "cache"))
    {
        if (strcmp(argv[1], "clear"))
        {
            clear();
            return;
        }

        if (strcmp(argv[1], "search"))
        {
            //Create the operation to be searched
            std::string operatorInformation = "";

            //argv[2] is the type - Matrix/Hash....
            operatorInformation.append(argv[2]);
            operatorInformation.append(" ");
            //argv[3] is the operation itself
            operatorInformation.append(argv[3]);

            //Add the Hashed version of the input files
            for (int i = 4; i < argc; ++i)
            {
                //create the output file
                std::string temporaryFileName = "tmp" + std::to_string(i - 3) + ".txt";
                const char *arguments[] = {"hash", "crc32", argv[i], temporaryFileName.c_str()};

                //do the Hash on the input file,
                //and write it to our temporary file
                operate(3, arguments);
                operatorInformation.append(readFileContent(temporaryFileName));
            }

            search(operatorInformation);
            return;
        }
    }

    //The operation is nor related to cache, so call the factor
    //in order to create operation

    //Call the factory to create a ChaceOperation
    CacheOperate object = factory(argc, argv);
    auto info = std::make_unique<std::string>(object.getInfo());

    //get the line number with the get info in it
    int lineNumber = search(*info);

    //If lineNumber != 0 then we have already done that operation,
    //so just take it from the output file
    if (lineNumber != 0)
    {
        //give value for the m_line and m_argc,
        //Which contains information about the row we found
        createTheLine(lineNumber);

        //get the time in which the operation took place
        time_t OutputFileCreated = (time_t)(atol(m_line[m_argc - 1]));

        //get the time the output file last changed
        path p = m_line[m_argc - 2];
        auto ftime = last_write_time(p);
        std::time_t lastWriteTime = decltype(ftime)::clock::to_time_t(ftime);

        //If that is true, it means that the output file did not change
        //since we have made our operation on it.
        //So, we already have a file with the result we want.
        if (OutputFileCreated >= lastWriteTime - 1)
        {
            //Copy the file to our needed output file
            copy_file(m_line[m_argc - 2], argv[argc - 1]);

            //delete the line
            //(afterwards we will create a newer line)
            deleteLine(lineNumber);

            //Create a new row at the end of the file
            m_fileContent.append(*info + "\n");
            writeFileContent(m_filePath, m_fileContent);
            return;
        }
    }

    //If we got here, we could not take the operation from the cache
    //(because it wasn't there / the output file was modified)
    //write to the output file
    object.operate(argv[argc - 1]);

    //If the cache size is too big then delete the least used operation,
    //which is in the first line
    if (m_sizeOfCache >= CACHE_MAX_SIZE)
    {
        deleteLine(1);
        --m_sizeOfCache;
    }

    //Create a new row at the end of the file
    m_fileContent.append(*info + "\n");
    ++m_sizeOfCache;

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

int CacheManagement::search(const std::string &) const
{
}

void deleteLine(const char *file_name, int n)
{
    // open file in read mode or in mode
    std::ifstream is(file_name);

    // open file in write mode or out mode
    std::ofstream ofs;
    ofs.open("temp.txt", std::ofstream::out);

    // loop getting single characters
    char c;
    int line_no = 1;
    while (is.get(c))
    {
        // if a newline character
        if (c == '\n')
            line_no++;

        // file content not to be deleted
        if (line_no != n)
            ofs << c;
    }

    // closing output file
    ofs.close();

    // closing input file
    is.close();

    // remove the original file
    remove(file_name);

    // rename the file
    rename("temp.txt", file_name);
}

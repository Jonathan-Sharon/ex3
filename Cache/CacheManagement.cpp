#include "CacheManagement.hpp"
#include "FileReading.hpp"
#include <time.h>
#include <bits/stdc++.h>
#include <experimental/filesystem>

#define CACHE_MAX_SIZE 10

using namespace std::experimental::filesystem;

CacheManagement::CacheManagement()
{
    m_fileContent = readFileContent(m_fileName);
}

void CacheManagement::operate(int argc, const char **const argv)
{
    //Get the second word in the string
    //If it equals to any of the cache operations,
    //then so them

    if (strcmp(argv[0], "cache"))
    {
        if (strcmp(argv[1], "clear"))
        {
            clear();
            return;
        }

        if (strcmp(argv[1], "search"))
        {
            std::string print = "";
            search(print);
            std::cout << print << std::endl;
            return;
        }
    }

    //If one of the input files does not exist, return the appropiate error
    int numberOfInputFiles = argc - 3;
    for (int i = 0; i < numberOfInputFiles; ++i)
    {
        //check if the file exists.
        //there are 2 arguments needed before the first input file
        if (exists(argv[2 + i]))
        {
            throw std::runtime_error("path " + std::string(argv[2 + i]) + " does not exists");
        }
    }

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
        time_t OutputFileCreated = (long)(m_line[m_argc - 1]);
        printf("%jd seconds since the epoch began\n", (intmax_t)OutputFileCreated);

        auto ftime = last_write_time(m_line[m_argc - 2]);

        std::time_t cftime = decltype(ftime)::clock::to_time_t(ftime); // assuming system_clock

        if (searchTimeStamp(lineNumber) >)

            copy_file(argv[argc - 1], searchOutputFileName(lineNumber));

        //delete the line
        deleteLine("cache.txt", lineNumber);
    }
    else
    {

        writeFileContent(argv[argc - 1], object.operate());
        //write
        //add to the cache.txt
    }

    std::ifstream myFile(FILE_NAME);

    // new lines will be skipped unless we stop it from happening:
    myFile.unsetf(std::ios_base::skipws);

    // count the newlines with an algorithm specialized for counting:
    unsigned line_count = std::count(
        std::istream_iterator<char>(myFile),
        std::istream_iterator<char>(),
        '\n');

    if (line_count > CACHE_MAX_SIZE)
    {
        deleteLine("cache.txt", 1);
    }

    //std::ofstream myFile;
    myFile.open("cache.txt", std::ios::out | std::ios::app);
    myFile << *info << std::endl;
    myFile.close();
}

void clear()
{
}

int search(const std::string &)
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

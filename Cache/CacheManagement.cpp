#include "CacheManagement.hpp"
#include <bits/stdc++.h>

#define CACHE_MAX_SIZE 10
#define FILE_NAME "cache.txt"

namespace CacheManagement
{
    void operate(int argc, const char **const argv)
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

        //Call the factory to create a ChaceOperation
        CacheOperate object(factory(argc, argv));
        auto info = std::make_unique<std::string>(object.getInfo());

        //get the line number with the get info in it
        int lineNumber = search(*info);

        if (lineNumber != 0)
        {
            //write to the output file
            std::string read = readFileContent(FILE_NAME);
            writeFileContent(argv[argc - 1], read);

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
} // namespace CacheManagement

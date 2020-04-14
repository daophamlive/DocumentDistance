///////////////////////////////////////////////////////////
//  FileReaderIFstream.cpp
//  Implementation of the Class FileReaderIFstream
//  Original author: DAOPHAM
///////////////////////////////////////////////////////////

#include "FileReaderIFstream.h"
#include <fstream>
#include <exception>
#include <iostream>
#include <sstream>

namespace _FileReader
{

FileReaderIFstream::FileReaderIFstream(const std::string &docPath):
    m_docPath(docPath)
{

}


FileReaderIFstream::~FileReaderIFstream()
{}


PTR_STRING_VECTOR FileReaderIFstream::getTextLines()
{
    PTR_STRING_VECTOR fileLines(new STRING_VECTOR());
    try
    {
        std::fstream infile(m_docPath, std::fstream::in );
        std::string line;
        while (std::getline(infile, line))
        {
            if(!line.empty())
                fileLines->push_back(line);
        }
    }
    catch (const std::ifstream::failure& e) {
        std::cout << "Exception opening/reading file "<<m_docPath <<std::endl;
    }

    return  fileLines;
}
}

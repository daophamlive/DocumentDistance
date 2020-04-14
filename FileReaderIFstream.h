///////////////////////////////////////////////////////////
//  FileReaderIFstream.h
//  Implementation of the Class FileReaderIFstream
//  Original author: DAOPHAM
///////////////////////////////////////////////////////////

#if !defined(FILEREADERIFSTTTREAM__INCLUDED_)
#define FILEREADERIFSTTTREAM__INCLUDED_

#include "IFileReader.h"
#include "DefaultDefines.h"
#include <vector>

namespace _FileReader
{
class FileReaderIFstream : public IFileReader
{
public:
    FileReaderIFstream(const std::string &docPath);
	virtual ~FileReaderIFstream();

   PTR_STRING_VECTOR  getTextLines();

private:
    std::string m_docPath;

};
}
#endif // !defined(FILEREADERIFSTTTREAM__INCLUDED_)

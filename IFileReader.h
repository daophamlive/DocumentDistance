///////////////////////////////////////////////////////////
//  IFileReader.h
//  Implementation of the Interface IFileReader
//  Original author: DAOPHAM
///////////////////////////////////////////////////////////

#if !defined(IFILEREADER__INCLUDED_)
#define IFILEREADER__INCLUDED_

#include "DefaultDefines.h"
#include <vector>

namespace _FileReader
{

typedef std::shared_ptr<std::vector<std::string>> PTR_STRING_VECTOR;
typedef std::vector<std::string>                STRING_VECTOR;

class IFileReader
{
public:
    IFileReader() = default;
    virtual ~IFileReader() = default;
    virtual PTR_STRING_VECTOR getTextLines() =0;

};

}
#endif // !defined(IFILEREADER__INCLUDED_)

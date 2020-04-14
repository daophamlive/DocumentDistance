///////////////////////////////////////////////////////////
//  IDistanceCalculator.h
//  Implementation of the Interface IDistanceCalculator
//  Original author: DAOPHAM
///////////////////////////////////////////////////////////

#if !defined(IDISTANCECALCULATOR__INCLUDED_)
#define IDISTANCECALCULATOR__INCLUDED_

#include "DefaultDefines.h"

class IDistanceCalculator
{
public:
    IDistanceCalculator(){};
    virtual ~IDistanceCalculator() = default;
   // virtual  double calcDocsDistance(const std::string & firstDocPath, const std::string & secondDocPath) =0;

};
#endif // !defined(IDISTANCECALCULATOR__INCLUDED_)

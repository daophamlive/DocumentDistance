///////////////////////////////////////////////////////////
//  DistanceCalculatorCosine.h
//  Implementation of the Class DistanceCalculatorCosine
//  Original author: DAOPHAM
///////////////////////////////////////////////////////////

#if !defined(DISTANCECALCULATORCOSINE__INCLUDED_)
#define DISTANCECALCULATORCOSINE__INCLUDED_


#include "IDistanceCalculator.h"
#include "DefaultDefines.h"
#include <map>
#include <vector>
#include <IFileReader.h>
#include <unordered_map>


class DistanceCalculatorCosine : virtual public  IDistanceCalculator
{
private:
    typedef  std::shared_ptr<std::unordered_map<std::string,unsigned int>> PTR_WORD_LIST;
    typedef  std::unordered_map<std::string,unsigned int> WORD_LIST;
    typedef  std::pair<std::string,unsigned int> WORD_LIST_PAIR;

    typedef  std::map<char,bool> VALID_ASCII_LIST;
    typedef  std::pair<char,bool> VALID_ASCII_PAIR;

    static constexpr double M_PI_VALUE = 3.1415926535897;

public:
    DistanceCalculatorCosine();
    DistanceCalculatorCosine(const std::string &filePath);
	virtual ~DistanceCalculatorCosine();

    double calcDocsDistance(const std::string & firstDocPath, const std::string & secondDocPath);
    double getDistance(DistanceCalculatorCosine &distance2);

public:
    _FileReader::PTR_STRING_VECTOR getTextLinesOfFile();
    PTR_WORD_LIST getWordsFrequencies() ;
    unsigned int innerProduct() const;
    unsigned int innerProduct(PTR_WORD_LIST spFrequencies) const;
private:

    double calcVectorAngle(DistanceCalculatorCosine &distance2);
    void updateWordList(PTR_WORD_LIST spWordsList, const std::string &c);

    PTR_WORD_LIST getWordsFrequencies(PTR_WORD_LIST spWordList,const std::string &words, const std::string &delim) ;
    int getDistanceResult(double distanceRadian);
    bool isDelim(const char &ch) const;
    void initReportValues();

private:
    std::string m_delimChars = {32};
    std::string m_debugText;
    std::string m_filePath;
   _FileReader::PTR_STRING_VECTOR m_spFileContent;
    PTR_WORD_LIST m_spFrequencies;

    size_t m_numOfWords;
};
#endif // !defined(DISTANCECALCULATORCOSINE__INCLUDED_)

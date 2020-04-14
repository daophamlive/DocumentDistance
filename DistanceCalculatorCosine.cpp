///////////////////////////////////////////////////////////
//  DistanceCalculatorCosine.cpp
//  Implementation of the Class DistanceCalculatorCosine
//  Original author: DAOPHAM
///////////////////////////////////////////////////////////

#include "DistanceCalculatorCosine.h"
#include "FileReaderIFstream.h"
#include <complex>
#include <iostream>
#include <chrono>
#include <sstream>
#include <algorithm>


using namespace _FileReader;



#define DECLARE_TIMING()  std::chrono::time_point<std::chrono::system_clock> start, end
#define START_TIMING()    start = std::chrono::system_clock::now()
#define STOP_TIMING()     end = std::chrono::system_clock::now()
#define GET_DURATION(count_time)    std::chrono::duration<double> count_time = (end - start)

DistanceCalculatorCosine::DistanceCalculatorCosine(): m_numOfWords(0)
{
}

DistanceCalculatorCosine::DistanceCalculatorCosine(const std::string &filePath):
    m_filePath(filePath)
{
}



DistanceCalculatorCosine::~DistanceCalculatorCosine(){

}


double DistanceCalculatorCosine::getDistance(DistanceCalculatorCosine &distance2)
{
    DECLARE_TIMING();

     START_TIMING();
    double angle(0);
    m_spFrequencies =  getWordsFrequencies();

    angle = calcVectorAngle(distance2);//complexity: O(2n^2), average O(2n)
    STOP_TIMING();
    GET_DURATION(totalTime);


    printf("\nTotal time  %f ", totalTime);
    return angle;
}

/*
 * Inner product between two vectors, where vectors
    are represented as dictionaries of (word,freq) pairs.
    Example: inner_product({"and":3,"of":2,"the":5},
                           {"and":4,"in":1,"of":1,"this":2}) = 14.0

     complexity: O(n^2), average O(n)
*/
unsigned int DistanceCalculatorCosine::innerProduct( DistanceCalculatorCosine::PTR_WORD_LIST spFrequencies) const
{
    unsigned int sum(0);
    if(m_spFrequencies.get() == nullptr || spFrequencies.get() == nullptr)
    {
        return sum;
    }

    PTR_WORD_LIST spSmallerMap = m_spFrequencies;
    PTR_WORD_LIST spLargerMap = spFrequencies;
    if(m_spFrequencies->size() > spFrequencies->size())
    {
        spSmallerMap = spFrequencies;
        spLargerMap = m_spFrequencies;
    }

    for(const auto &element: (*spSmallerMap.get()) ) //O(n)
     {
         const std::string &word = element.first;
         const unsigned int &frequences = element.second;
         auto it = spLargerMap->find(word); //worst case O(n), average O(1)
         if(it != spLargerMap->end()) //O(1)
         {
             sum += (frequences * it->second);
         }
     }

      printf("\nInnerProduct  : D1*D2 = %llu", sum);
     return sum;
}


unsigned int DistanceCalculatorCosine::innerProduct() const
{
    unsigned int sum(0);
    if(m_spFrequencies == nullptr || m_spFrequencies->empty())
    {
        return sum;
    }

    for(const auto &element: (*m_spFrequencies.get()) ) //O(n)
     {
         sum += std::pow(element.second,2);
     }

     printf("innerProduct  : |D|  %llu \n", sum);
    return sum;
}


/*
 * complexity: O(2n^2), average O(2n)
 *  The input is a list of (word,freq) pairs, sorted alphabetically.
    Return the angle between these two vectors.
*/
double DistanceCalculatorCosine::calcVectorAngle(DistanceCalculatorCosine &distance2)
{
    DECLARE_TIMING();

     START_TIMING();
    double res(0);
    if(m_spFrequencies == nullptr || distance2.getWordsFrequencies() == nullptr)
    {
        return 0;
    }

    unsigned int numerator = innerProduct(distance2.getWordsFrequencies());//D1*D2, complexity: O(n^2), average O(n)
    double denominator = std::sqrt( innerProduct()* distance2.innerProduct() ); //|D1| * |D2|, complexity: O(2n^2), average O(2n)

    res = acos(numerator/denominator);
    STOP_TIMING();
    GET_DURATION(angleCalcTime);
    printf("\n\nNumerator  : D1*D2 %llu ", numerator);
    printf("\nDenominator  : |D1| * |D2| = %llu", denominator);
    printf("\nCalculate angle time: %f", angleCalcTime.count());

    return res;
}

/*
 * Parse the given text into words.
    Return dictionary of (word,frequency) pairs for the given file.
    Complexity : O(n^2)
*/
DistanceCalculatorCosine::PTR_WORD_LIST DistanceCalculatorCosine::getWordsFrequencies()
{
    if(m_spFrequencies != nullptr && !m_spFrequencies->empty())
        return m_spFrequencies;

    DECLARE_TIMING();

    m_spFrequencies = std::make_shared<WORD_LIST>();
    initReportValues();
    START_TIMING();
    m_spFileContent = getTextLinesOfFile();
    STOP_TIMING();
    GET_DURATION(readfileTime);

    if(m_spFileContent == nullptr)
    {
        return m_spFrequencies;
    }

    if(m_spFileContent->empty())
    {
        return m_spFrequencies;
    }

    const size_t LINELIST_SIZE = m_spFileContent->size();
    const size_t HALF_LINELIST_SIZE = (LINELIST_SIZE/2 );

    START_TIMING();
    std::string word;
    for(size_t i = 0; i < HALF_LINELIST_SIZE; i++)
    {

        const std::string &line = m_spFileContent->at(i);
        std::istringstream ss(line);

        if(!line.empty())
        {
            getWordsFrequencies(m_spFrequencies,line,m_delimChars);
        }

        size_t j = LINELIST_SIZE - i - 1;
        if(i != j && j > 0)
        {
            const std::string &line1 = m_spFileContent->at(j);
             std::istringstream ss1(line1);
            if(!line1.empty())
            {
               getWordsFrequencies(m_spFrequencies,line1,m_delimChars);
            }
        }
    }
    STOP_TIMING();
    GET_DURATION(frequencies_time);

    printf("\nFile %s;            lines: %llu Num of words: %llu, distince words: %llu", m_filePath.c_str(),m_spFileContent->size(), m_numOfWords, m_spFrequencies->size());
    printf("\nRead file time  : %f ", readfileTime.count());
    printf("\nFrequencies time: %f ", frequencies_time.count());
    return m_spFrequencies;
}

/*
 * O(1)
*/
PTR_STRING_VECTOR DistanceCalculatorCosine::getTextLinesOfFile()
{
    std::shared_ptr<IFileReader> spFileReader(std::make_shared<FileReaderIFstream> (m_filePath));
    PTR_STRING_VECTOR spContent= spFileReader->getTextLines() ;
    return spContent;
}

/*
 *
 * O(n) + O(1) = O(n+1)
 *  complexity: worst case O(n+1), average O(n)
 *
*/
void DistanceCalculatorCosine::updateWordList(DistanceCalculatorCosine::PTR_WORD_LIST spWordList, const std::string &word)
{
    const int DEFAULT_FREQUENCE(1);
    WORD_LIST_PAIR pair(word,DEFAULT_FREQUENCE);


    if(spWordList != nullptr && !word.empty())
    {
        WORD_LIST::iterator it = spWordList->find(word);//worse case O(n)
        if(it == spWordList->end())
        {
            spWordList->insert(std::move(pair));//O(1)
        }
        else
        {
            it->second++;//O(1)
        }
        m_numOfWords++;
    }
}

DistanceCalculatorCosine::PTR_WORD_LIST DistanceCalculatorCosine::getWordsFrequencies(PTR_WORD_LIST spWordList, const std::string &words, const std::string &delim)
{
    if(delim.empty() || words.empty())
    {
        return spWordList;
    }

    std::istringstream ss(words);

    const size_t DELIM_SIZE = delim.size();
    std::string word;

    while(std::getline(ss, word, delim.at(0)))
    {
        if(DELIM_SIZE == 1 && !word.empty())
        {
            updateWordList(spWordList,word);
            m_numOfWords++;
        }
        else
        {
            getWordsFrequencies(spWordList, word, delim.substr(1,DELIM_SIZE -1));
        }
    }

    return spWordList;
}


int DistanceCalculatorCosine::getDistanceResult(double distanceRadian)
{
    int distance(0);
    const double MAX_DIFFERENCE = M_PI_VALUE/2;

    distance = static_cast<int>( (100 * distanceRadian)/MAX_DIFFERENCE );

    return distance;
}

bool DistanceCalculatorCosine::isDelim(const char &ch) const
{
    const size_t size = m_delimChars.size();
    if(size == 0)
        return false;
    const size_t half_size = m_delimChars.size()/2;

    for (size_t i = 0; i <= half_size; ++i)
    {
        if (m_delimChars[i] == ch)
            return true;

        size_t j = size - 1 - i;
        if( (j > 0) && (j != i) && m_delimChars[j] == ch)
            return true;
    }

    return false;
}

void DistanceCalculatorCosine::initReportValues()
{
    m_numOfWords = 0;
}



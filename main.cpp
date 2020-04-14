//Usage:
//    DocumentDistance filename1 filename2
//
// This program computes the "distance" between two text files
// as the angle between their word frequency vectors (in radians).
//
// For each input file, a word-frequency vector is computed as follows:
//    (1) the specified file is read in
//    (2) it is converted into a list of alphanumeric "words"
//        Here a "word" is a sequence of consecutive alphanumeric
//        characters.  Non-alphanumeric characters are treated as blanks.
//        Case is not significant.
//    (3) for each word, its frequency of occurrence is determined
//    (4) the word/frequency lists are sorted into order alphabetically
//
// The "distance" between two vectors is the angle between them.
// If x = (x1, x2, ..., xn) is the first vector (xi = freq of word i)
// and y = (y1, y2, ..., yn) is the second vector,
// then the angle between them is defined as:
//    d(x,y) = arccos(inner_product(x,y) / (norm(x)*norm(y)))
// where:
//    inner_product(x,y) = x1*y1 + x2*y2 + ... xn*yn
//    norm(x) = sqrt(inner_product(x,x))


#include <iostream>
#include <chrono>

#include "DistanceCalculatorCosine.h"




using namespace std;

int main(int argc,const char **argv = nullptr)
{
    if(argc != 3)
    {
        std::cout<< "Usage: DocumentDistance filename_1 filename_2"<<std::endl;
        return 1;
    }

    const char * firstDocPath = argv[1];
    const char * secondDocPath = argv[2];

    std::shared_ptr<DistanceCalculatorCosine> spDistanceCalc1 (new DistanceCalculatorCosine(firstDocPath));
    std::shared_ptr<DistanceCalculatorCosine> spDistanceCalc2 (new DistanceCalculatorCosine(secondDocPath));



    double distance = spDistanceCalc1->getDistance(*spDistanceCalc2.get());

    return 0;
}

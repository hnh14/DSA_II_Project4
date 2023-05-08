#include "monte.hpp"
#include <math.h>

//Calulates P fail rate
double Monte::pFail(int p, int n) {
    return pow((1.0 - (p / 100.0)), n);
}

//Analyzes the sets in a simulations
//Returns the number of bad batches found
int Monte::analyzeSet(int start, int finish, int numSamples) {
    std::ifstream stream;
    int maxBad = 0;
    int minBad = 9999;
    int totalBad = 0;
    int badCount = 0;
    int thisBad;
    bool badFlag = 0;
    std::string temp;

    //Runs through each set and tests samples
    //Prints results
    for(int i = start; i < finish; i++) {
        stream.open("batch-sets/ds" + std::to_string(i) + ".txt");
        stream.clear();
        stream.seekg(0);
        thisBad = 0;
        badFlag = 0;
        for(int j = 0; j < numSamples; j++) {
            stream >> temp;
            if(temp[0] == 'b') {
                thisBad++;
                badFlag = 1;
            }
        }

        if(badFlag == 1)
            badCount++;

        thisBad *= (1000 / numSamples);

        stream.close();
        totalBad += thisBad;
        if(thisBad > maxBad)
            maxBad = thisBad;
        if(thisBad < minBad && thisBad > 0)
            minBad = thisBad;
    }

    std::cout << "\tMax number of bad items in a bad set = " << maxBad << std::endl;
    std::cout << "\tMin number of bad items in a bad set = " << minBad << std::endl;
    std::cout << "\tAvg number of bad items in a bad set = " << totalBad / badCount << std::endl << std::endl;

    return badCount;
}
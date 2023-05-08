#include <iostream>
#include <fstream>
#include <time.h>
#include <string>
#include "monte.hpp"

int main() {
    int input[4][5];

    //Opens input files
    std::ifstream t1("t1.txt");
    std::ifstream t2("t2.txt");
    std::ifstream t3("t3.txt");
    std::ifstream t4("t4.txt");

    //Checks if all files are open
    if(!(t1.is_open() && t2.is_open() && t3.is_open() && t4.is_open())) {
        std::cout << "Could not open file\n";
        return 0;
    }

    //Reads values from file
    for(int i = 0; i < 5; i++) {
        t1 >> input[0][i];
        t2 >> input[1][i];
        t3 >> input[2][i];
        t4 >> input[3][i];
    }

    //Tests input
    // for(int i = 0; i < 4; i++){
    //     for(int j = 0; j < 5; j++) {
    //         std::cout << input[i][j] << ", ";
    //     }
    //     std::cout << "\n";
    // }

    //Creates batch files
    std::ofstream out;
    int lastBatchNum = 1;
    int numBad, badTest;

    //Loops for each test file
    for(int s = 0; s < 4; s++) {
        numBad = input[s][0] * (input[s][2] / 100.0);

        //Loops and creates file for each batch
        for(int batch = lastBatchNum; batch < lastBatchNum + input[s][0]; batch++ ) {
            out.open("batch-sets/ds" + std::to_string(batch) + ".txt");

            //Loops once for each item in batch, writes 'g' or 'b'
            for(int item = 1; item <= input[s][1]; item++) {
                if(numBad > 0) {
                    // std::srand(time(0));
                    badTest = std::rand() % 100;
                    if(badTest < input[s][3]) {
                        out << "b\n";
                        continue;
                    }
                }
                
                out << "g\n";
            }

            numBad--;
            out.close();
        }

        lastBatchNum += input[s][0];
    }

    lastBatchNum = 1;

    //Runs tests and produces output
    for(int i = 0; i < 4; i++) {
        std::cout << "Simulation #" << i + 1 << std::endl
                  << "\tNumber of batches of items: " << input[i][0] << std::endl
                  << "\tNumber of items in each batch: " << input[i][1] << std::endl
                  << "\tPercentage of batches containing bad items: " << input[i][2] << std::endl
                  << "\tPercentage of items that are bad in a bad set: " << input[i][3] << std::endl
                  << "\tItems sampled from each set: " << input[i][4] << std::endl << std::endl;

        std::cout << "Generating data sets:\n"
                  << "\tTotal bad sets = " << input[i][0] * (input[i][2] / 100.0) << std::endl;
        double badCount = Monte::analyzeSet(lastBatchNum, lastBatchNum + input[i][0] - 1, input[i][4]);
        lastBatchNum += input[i][0];

        std::cout << "Analyzing Data Sets\n"
                  << "\tBase = " + std::to_string((100.0 - input[i][3]) / 100.0) << " exponent = " << input[i][4] << std::endl
                  << "\tP(failure) = " << Monte::pFail(input[i][3], input[i][4]) << std::endl
                  << "\tP(good) = " << 1 - Monte::pFail(input[i][3], input[i][4]) << std::endl
                  << "\tPercentage of bad batches detected = " << (badCount / (input[i][0] * input[i][2])) * 10000.0 << "%" << std::endl << std::endl;
    }

    
}
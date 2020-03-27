#include <iostream>
#include <fstream>
#include <chrono>
#include <cmath>

#ifndef SORTER_H
#define SORTER_H

using namespace std;

class Sorter
{
    public:
        /**
        * @param unsigned int TableSize - Size of the vectors which will be sorted
        * @param unsigned int AlreadySorted - Percentage of sorted elements before sorting (0<=x<=1)
        * if x = 0 every element is random
        * if x = 1 table is sorted and reversed
        */
        Sorter(int TableSize, float AlreadySorted);


        /**
        *  @brief Destructor which delete every dynamic table
        */
        ~Sorter(){for (int i = 0; i<100; i++){ delete [] _Tables[i];  delete [] _TablesCopy[i];} delete [] _Tables; delete [] _TablesCopy;}

        /**
        * @brief [PL] Sortowanie szybkie
        * @return Return sorting time in ms
        */
        int TestQuicksort();

        /**
        * @brief [PL] Sortowanie przez scalanie
        * @return Return sorting time in ms
        */
        int TestMergeSort();

        /**
        * @brief [PL] Sortowanie przez kopcowanie
        * @return Return sorting time in ms
        */
        int TestHeapsort();

        /**
        * @brief Make the test and save results to the file
        */
        void TestAndSave();

    private:
        int ** _Tables    = new int * [100];
        int ** _TablesCopy = new int * [100];
        int _Elements;
        float _AlreadySorted;
};

#endif

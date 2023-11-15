#include <iostream>
#include <bits/stdc++.h>
#include <ctime>
#include <vector>
#include <chrono>

using namespace std;

// Implementation modified from https://www.geeksforgeeks.org/insertion-sort/
// Function to sort an array using
// insertion sort
void insertionSort(vector<int> *arr, int l, int r)
{
    int i, key, j;
    for (i = l; i <= r; i++) {
        key = arr->at(i);
        j = i - 1;

        // Move elements of arr[0..i-1],
        // that are greater than key,
        // to one position ahead of their
        // current position
        while (j >= l && arr->at(j) > key) {
            arr->at(j + 1) = arr->at(j);
            j = j - 1;
        }
        arr->at(j + 1) = key;
    }
}


// Implementation modified from https://www.geeksforgeeks.org/merge-sort/
// Merges two subarrays of array[].
// First subarray is arr[begin..mid]
// Second subarray is arr[mid+1..end]
void merge(vector<int> *array, int const left, int const mid,
           int const right)
{
    int const subArrayOne = mid - left + 1;
    int const subArrayTwo = right - mid;

    // Create temp arrays
    auto *leftArray = new int[subArrayOne],
            *rightArray = new int[subArrayTwo];

    // Copy data to temp arrays leftArray[] and rightArray[]
    for (auto i = 0; i < subArrayOne; i++) {
        leftArray[i] = array->at(left + i);
    }
    for (auto j = 0; j < subArrayTwo; j++)
        rightArray[j] = array->at(mid + 1 + j);

    auto indexOfSubArrayOne = 0, indexOfSubArrayTwo = 0;
    int indexOfMergedArray = left;

    // Merge the temp arrays back into array[left..right]
    while (indexOfSubArrayOne < subArrayOne
           && indexOfSubArrayTwo < subArrayTwo) {
        if (leftArray[indexOfSubArrayOne]
            <= rightArray[indexOfSubArrayTwo]) {
            array->at(indexOfMergedArray) = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }
        else {
            array->at(indexOfMergedArray) = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }

    // Copy the remaining elements of
    // left[], if there are any
    while (indexOfSubArrayOne < subArrayOne) {
        array->at(indexOfMergedArray) = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }

    // Copy the remaining elements of
    // right[], if there are any
    while (indexOfSubArrayTwo < subArrayTwo) {
        array->at(indexOfMergedArray) = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
    delete[] leftArray;
    delete[] rightArray;
}

// begin is for left index and end is right index
// of the sub-array of arr to be sorted
void timSort(vector<int> *array, int const begin, int const end, int const k)
{
    if (begin >= end)
        return;

    if (end - begin <= k){
        insertionSort(array, begin, end);
    }
    else{
        int mid = begin + (end - begin) / 2;
        timSort(array, begin, mid, k);
        timSort(array, mid + 1, end, k);
        merge(array, begin, mid, end);
    }
}



int main() {
    vector<int> arr;

    vector<int> sizes = {100, 200, 300, 400, 500, 600, 700};
    vector<int> constants = {10, 20, 30, 40, 50, 60};
    
    vector<vector<double>> timResults;

    for(int size : sizes){
        vector<double> sizeResults = {(double)size};
        for(int constant : constants){
            vector<int> constResults = {};
            for(int j = 0; j < 200; j++){
                for(int i = 0; i < size; i++){
                    arr.push_back(rand()%100);
                }

                vector<int> copy1 = arr;


                chrono::steady_clock::time_point start_time = chrono::steady_clock::now();
                timSort(&copy1, 0, copy1.size() - 1, constant);
                chrono::steady_clock::time_point end_time = chrono::steady_clock::now();
                chrono::steady_clock::duration tot_time = end_time - start_time;
                constResults.push_back(chrono::duration_cast<chrono::microseconds>(tot_time).count());

                arr.clear();
            }
        double average = 0;
        for(int value : constResults){
            average += value;
        }
        average /= constResults.size();
        sizeResults.push_back(average);
        }
        timResults.push_back(sizeResults);
    }

    for(auto i : timResults){
        for(int result : i){
            std::cout << result << ',';
        }
        std::cout << std::endl;
    }





    return 0;
}

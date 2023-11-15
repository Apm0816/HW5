#include <iostream>
#include <bits/stdc++.h>
#include <ctime>
#include <vector>
#include <chrono>

using namespace std;

// Implementation taken from https://www.geeksforgeeks.org/insertion-sort/
// Function to sort an array using
// insertion sort
void insertionSort(vector<int> *arr, int n)
{
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr->at(i);
        j = i - 1;

        // Move elements of arr[0..i-1],
        // that are greater than key,
        // to one position ahead of their
        // current position
        while (j >= 0 && arr->at(j) > key) {
            arr->at(j + 1) = arr->at(j);
            j = j - 1;
        }
        arr->at(j + 1) = key;
    }
}


// Implementation taken from https://www.geeksforgeeks.org/merge-sort/
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
void mergeSort(vector<int> *array, int const begin, int const end)
{
    if (begin >= end)
        return;

    int mid = begin + (end - begin) / 2;
    mergeSort(array, begin, mid);
    mergeSort(array, mid + 1, end);
    merge(array, begin, mid, end);
}



int main() {
    vector<int> arr;

    vector<int> sizes = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    
    vector<vector<int>> insertionResults;
    vector<vector<int>> mergeResults;
    
    for(int size : sizes){
        vector<int> sizeResults = {size};
        vector<int> size2Results = {size};
        for(int j = 0; j < 20; j++){
            for(int i = 0; i < size; i++){
                arr.push_back(rand()%100);
            }

            vector<int> copy1 = arr;
            vector<int> copy2 = arr;

            chrono::steady_clock::time_point start_time = chrono::steady_clock::now();
            insertionSort(&copy1, copy1.size());
            chrono::steady_clock::time_point end_time = chrono::steady_clock::now();
            chrono::steady_clock::duration tot_time = end_time - start_time;
            sizeResults.push_back(chrono::duration_cast<chrono::microseconds>(tot_time).count());

            
            start_time = chrono::steady_clock::now();
            mergeSort(&copy2, 0, copy2.size() - 1);
            end_time = chrono::steady_clock::now();
            tot_time = end_time - start_time;
            size2Results.push_back(chrono::duration_cast<chrono::microseconds>(tot_time).count());

            arr.clear();
        }
        insertionResults.push_back(sizeResults);
        mergeResults.push_back(size2Results);
    }

    for(auto i : insertionResults){
        for(int result : i){
            std::cout << result << ',';
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

    for(auto i : mergeResults){
        for(int result : i){
            std::cout << result << ',';
        }
        std::cout << std::endl;
    }


    return 0;
}

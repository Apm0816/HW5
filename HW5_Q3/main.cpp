#include <iostream>
#include <map>
#include <unordered_set>
#include <cstdlib>
#include <cmath>
#include <chrono>
#include <vector>

using namespace std;

int main() {
    vector<int> output_tree;
    vector<int> output_hash;
    for(int i = 3; i < 8; i++){
        std::multimap<int, int> tree;
        std::unordered_multiset<int> hash;

        chrono::steady_clock::time_point start_time = chrono::steady_clock::now();
        for(int j = 0; j < pow(10, i); j++){
            tree.insert({rand(), j});
        }
        chrono::steady_clock::time_point end_time = chrono::steady_clock::now();
        chrono::steady_clock::duration tot_time = end_time - start_time;
        output_tree.push_back(chrono::duration_cast<chrono::milliseconds>(tot_time).count());

        start_time = chrono::steady_clock::now();
        for(int j = 0; j < pow(10, i); j++){
            hash.insert(rand());
        }
        end_time = chrono::steady_clock::now();
        tot_time = end_time - start_time;
        output_hash.push_back(chrono::duration_cast<chrono::milliseconds>(tot_time).count());
    }

    for(int i : output_tree) {
        std::cout << i << ',';
    }
    std::cout << std::endl;
    for(int i : output_hash){
        std::cout << i << ',';
    }
}

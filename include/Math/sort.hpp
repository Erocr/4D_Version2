#ifndef QUICKSORT
#define QUICKSORT
#include <vector>
#include <utility>
#include <math.h>
#include <iostream>
using namespace std;

template<typename T>
int find_max_pow_10(const vector<pair<int, T>>& elements);

template<typename T>
vector<T> quicksort(vector<pair<int, T>>& not_sorted);

template<typename T>
vector<T> radixsort(vector<pair<int, T>> &not_sorted, int max_pow_10);

template<typename T>
void draw_vector_pairs(vector<pair<int, T>> to_draw);

#endif QUICKSORT
//
//  Fonctions.cpp
//  Labos ASD1 2018
//
//  Created by Olivier Cuisenaire on 16.12.16.
//  Copyright © 2016 Olivier Cuisenaire. All rights reserved.
//
//	Stéphane Teixeira Carvalho, Diego Villagrasa, Robin Müller
//

#include "Fonctions.h"
#include <cstdlib>
#include <ctime>

using namespace std;

size_t chercherPosition(const vector<int>& v, int val) {
    for(size_t i = 0; i < v.size(); ++i) {
        if(v.at(i) == val)
            return i;
    }
    return -1;
}

unsigned trier(vector<int>& v) {
    if(v.empty()) return 0;

    unsigned nbIterations = 0;
    for(int a : v) {
        auto j = v.begin();
        auto k = j++;
        for(; j != v.end(); k = j++ ) {
            ++nbIterations;
            if (*k > *j)
                swap(*k, *j);
        }
    }

    return nbIterations;
}

unsigned chercherSiContient(const vector<int>& v, int val) {
    auto first = v.begin();
    auto last = v.end();

    unsigned nbIterations = 0;
    while( first != last ) {
        ++nbIterations;

        auto mid = first + ( last - first ) / 2;
        if(*mid == val) {
            return nbIterations;
        } else if(*mid < val) {
            first = mid+1;
        } else {
            last = mid;
        }
    }
    return nbIterations;
}

unsigned long long f( unsigned n ) {

    if( n == 0 ) return 1;

    return f(n-1) + f(n-1) + f(n-1);
}

unsigned g(vector<int>& v) {
    unsigned nbIterations = 0;
    for(size_t i = 0; i < v.size(); ++i) {
        for(size_t j = v.size() - 1; j > 0; j /= 2 ) {
            ++nbIterations;
            v.at(i) += v.at(j);
        }
    }
    return nbIterations;
}

vector<int> random( size_t N , int maxVal ) {

    vector<int> v;
    for(size_t i = 0; i < N; ++i) {
        v.push_back(1+rand()%maxVal);
    }

    return v;
}

vector<int> random2( size_t N , int maxVal ) {

    vector<int> v;
    for(size_t i = 0; i < N; ++i) {
        v.insert(v.begin(),1+rand()%maxVal);
    }

    return v;
}

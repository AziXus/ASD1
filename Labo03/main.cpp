//
//  main.cpp
//

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <random>
#include "CountingSort.h"

using namespace std;
using namespace asd1;

// Fonction principale

#include <chrono>

using namespace chrono;

void testSort1(unsigned exposantMax, unsigned base, unsigned valMin = 1, unsigned valMax = 100, unsigned nbTests = 30) {
    cout << "******* valeur " << valMin << "-" << valMax << ", n change *******\n";

    std::mt19937_64 gen(0);
    high_resolution_clock::time_point t1, t2;
    std::uniform_int_distribution<unsigned> alea(valMin, valMax);

    for (unsigned m = 1 ; m <= exposantMax ; m++) {
        long temps1 = 0;
        long temps2 = 0;
        //long temps3 = 0;
        //long temps4 = 0;

        unsigned n = (unsigned)(pow(base, m) + 0.5); //Arrondi avec +0.5
        cout << "\nn = " << n << " = " << base << "^" << m << endl;

        vector<unsigned> v(n);
        vector<unsigned> w(n);

        for (unsigned j = 1 ; j <= nbTests ; ++j) {
            generate(v.begin(), v.end(), [&]() { return alea(gen); });

            t1 = high_resolution_clock::now();
            CountingSort(v.begin(), v.end(), w.begin(), [](unsigned val) { return val; }, alea.max());
            t2 = high_resolution_clock::now();
            temps1 += duration_cast<nanoseconds>(t2 - t1).count();

            t1 = high_resolution_clock::now();
            RadixSort(v);
            t2 = high_resolution_clock::now();
            temps2 += duration_cast<nanoseconds>(t2 - t1).count();
        }

        cout << "Temps d'execution pour CoutingSort : " << temps1 / nbTests << " ns" << endl;
        cout << "Temps d'execution pour RadixSort   : " << temps2 / nbTests << " ns" << endl;
    }
}

void testSort2(unsigned exposantMax, unsigned base, size_t n = 100000, unsigned nbTests = 30) {

    cout << "******* n = " << n << ", valeur max change *******\n";
    vector<unsigned> v(n);
    vector<unsigned> w(n);

    std::mt19937_64 gen(0);
    high_resolution_clock::time_point t1, t2;

    for (unsigned m = 1 ; m <= exposantMax ; m++) {
        long temps1 = 0;
        long temps2 = 0;
        //long temps3 = 0;
        //long temps4 = 0;

        unsigned k = (unsigned)(pow(base, m) + 0.5); //Arrondi avec +0.5
        std::uniform_int_distribution<unsigned> alea(0, k);

        cout << "\nvaleur max = " << k << " = " << base << "^" << m << endl;

        for (unsigned j = 1 ; j <= nbTests ; ++j) {
            //On génére un vecteur puis on créer une copie pour le tri radix
            generate(v.begin(), v.end(), [&]() { return alea(gen); });

            t1 = high_resolution_clock::now();
            CountingSort(v.begin(), v.end(), w.begin(), [](unsigned val) { return val; }, alea.max());
            t2 = high_resolution_clock::now();
            temps1 += duration_cast<nanoseconds>(t2 - t1).count();

            t1 = high_resolution_clock::now();
            RadixSort(v);
            t2 = high_resolution_clock::now();
            temps2 += duration_cast<nanoseconds>(t2 - t1).count();
        }

        cout << "Temps d'execution pour CoutingSort : " << setw(10) << temps1 / nbTests << " ns" << endl;
        cout << "Temps d'execution pour RadixSort   : " << setw(10) << temps2 / nbTests << " ns" << endl;
    }

    cout << "**************************************************";
}

void testSort3(unsigned exposantMax, unsigned base, unsigned valMin = 1, unsigned valMax = 100, unsigned nbTests = 30) {
    cout << "******* valeur " << valMin << "-" << valMax << ", n change *******\n";

    std::mt19937_64 gen(0);
    high_resolution_clock::time_point t1, t2;
    std::uniform_int_distribution<unsigned> alea(valMin, valMax);

    for (unsigned m = 1 ; m <= exposantMax ; m++) {
        long temps1 = 0;
        long temps2 = 0;
        //long temps3 = 0;
        //long temps4 = 0;

        unsigned n = (unsigned)(pow(base, m) + 0.5); //Arrondi avec +0.5
        cout << "\nn = " << n << " = " << base << "^" << m << endl;

        vector<unsigned> v(n);

        for (unsigned j = 1 ; j <= nbTests ; ++j) {
            generate(v.begin(), v.end(), [&]() { return alea(gen); });

            t1 = high_resolution_clock::now();
            selectionSort(v.begin(), v.end());
            t2 = high_resolution_clock::now();
            temps1 += duration_cast<nanoseconds>(t2 - t1).count();
        }

        cout << "Temps d'execution pour le tri par selection : " << temps1 / nbTests << " ns" << endl;
    }
}

void testSort4(unsigned exposantMax, unsigned base, size_t n = 100000, unsigned nbTests = 30) {

    cout << "******* n = " << n << ", valeur max change *******\n";
    vector<unsigned> v(n);
    vector<unsigned> w(n);

    std::mt19937_64 gen(0);
    high_resolution_clock::time_point t1, t2;

    for (unsigned m = 1 ; m <= exposantMax ; m++) {
        long temps1 = 0;
        long temps2 = 0;
        //long temps3 = 0;
        //long temps4 = 0;

        unsigned k = (unsigned)(pow(base, m) + 0.5); //Arrondi avec +0.5
        std::uniform_int_distribution<unsigned> alea(0, k);

        cout << "\nvaleur max = " << k << " = " << base << "^" << m << endl;

        for (unsigned j = 1 ; j <= nbTests ; ++j) {
            //On génére un vecteur puis on créer une copie pour le tri radix
            generate(v.begin(), v.end(), [&]() { return alea(gen); });

            t1 = high_resolution_clock::now();
            selectionSort(v.begin(), v.end());
            t2 = high_resolution_clock::now();
            temps1 += duration_cast<nanoseconds>(t2 - t1).count();
        }

        cout << "Temps d'execution pour tri par selection : " << setw(10) << temps1 / nbTests << " ns" << endl;
    }

    cout << "**************************************************";
}

int main() {
    const unsigned EXPOSANT_MAX = 6;
    const unsigned BASE = 10;

    testSort1(EXPOSANT_MAX, BASE);
    cout << endl;
    testSort2(EXPOSANT_MAX + 2, BASE);
    cout << endl;
    testSort3(EXPOSANT_MAX, BASE);
    cout << endl;
    testSort4(EXPOSANT_MAX, BASE);

    return EXIT_SUCCESS;
}

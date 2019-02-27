//
//  Labo1.cpp
//  Labos ASD1 2018
//
//  Created by Olivier Cuisenaire on 16.12.16.
//  Copyright © 2016 Olivier Cuisenaire. All rights reserved.
//
//	/* NOMS DES ETUDIANTS ICI */
//

#include <stdlib.h>
#include <vector>
#include <random>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <chrono>

void testChercherPosition(int nbTests);
void testTrier(int nbValeurs, int base, int nbTests);
void testChercherSiContient(int nbValeurs, int base, int nbTests);
void testG(int nbValeurs, int base, int nbTests);

using namespace std;

/**
 * 1. Recherche la position d'une valeur dans un vector.
 *
 * Pour la complexité, on considère le nombre d'itérations.
 * Tester pour diverses valeurs de val, présentes ou non dans le vector.
 *
 * @param v vector dans lequel on cherche
 * @param val valeur à chercher
 * @return la position de la valeur dans le vector si trouvé, -1 sinon
 */
size_t chercherPosition( const vector<int>& v , int val ) {
    for(size_t i = 0; i < v.size(); ++i) {
        if(v.at(i) == val)
            return i;
    }
    return -1;
}


/**ME
 * 2. Trie un vector.
 *
 * Pour la complexité, on considère le nombre de comparaisons (>)
 *
 * @param v vector à trier
 */
void trier( vector<int>& v ) {
    if(v.empty()) return;

    for(int a : v) {
        auto j = v.begin();
        auto k = j++;
        for(; j != v.end(); k = j++ )
            if(*k > *j )
                swap(*k, *j);
    }
}

//Identique à trier en retournant le nombre d'itérations
unsigned trier2( vector<int>& v ) {
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

/**ME
 * 3. Retourne true si la valeur est contenue dans le vector.
 *
 * Pour la complexité, on considère le nombre d'itérations.
 * v doit être trié en entrée !
 * Tester pour diverses valeurs de val, présentes ou non dans le vecteur.
 *
 * @param v vector trié dans lequel on cherche
 * @param val valeur à chercher
 * Retourne true si la valeur est contenue dans le vector, false sinon.
 */
bool chercherSiContient( const vector<int>& v , int val ) {
    auto first = v.begin();
    auto last = v.end();

    while( first != last ) {
        auto mid = first + ( last - first ) / 2;
        if(*mid == val) {
            return true;
        } else if(*mid < val) {
            first = mid+1;
        } else {
            last = mid;
        }
    }
    return false;
}

//Idem a chercherSiContient mais avec le nombre d'itérations en retour
unsigned chercherSiContient2( const vector<int>& v , int val ) {
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

/**
 * 4. Pour la complexité, on considère le nombre d'additions
 *
 * @param n
 * @return
 */
unsigned long long f( unsigned n ) {

    if( n == 0 ) return 1;

    return f(n-1) + f(n-1) + f(n-1);
}

/**ME
 * 5. Pour la complexité, on considère le nombre d'additions (+=)
 *
 * @param v
 */
void g( vector<int>& v ) {
    for(size_t i = 0; i < v.size(); ++i) {
        for(size_t j = v.size() - 1; j > 0; j /= 2 ) {
            v.at(i) += v.at(j);
        }
    }
}

//Fonction identique à g mais retourne le nombre d'itérations
unsigned g2( vector<int>& v ) {
    unsigned nbIterations = 0;
    for(size_t i = 0; i < v.size(); ++i) {
        for(size_t j = v.size() - 1; j > 0; j /= 2 ) {
            ++nbIterations;
            v.at(i) += v.at(j);
        }
    }
    return nbIterations;
}

/**
 * 6. Pour la complexité, on considère les opérations push_back()
 *
 * Evaluer le temps d'exécution
 *
 * @param N nombre de données à générer
 * @param maxVal valeur maximale des données
 * @return vector rempli de N valeurs aléatoires.
 */
vector<int> random( size_t N , int maxVal ) {

    vector<int> v;
    for(size_t i = 0; i < N; ++i) {
        v.push_back(1+rand()%maxVal);
    }

    return v;
}

/**
 * 7. Pour la complexité, on considère les opérations insert()
 *
 * Evaluer le temps d'exécution
 *
 * @param N nombre de données à générer
 * @param maxVal valeur maximale des données
 * @return vector rempli de N valeurs aléatoires.
 */
vector<int> random2( size_t N , int maxVal ) {

    vector<int> v;
    for(size_t i = 0; i < N; ++i) {
        v.insert(v.begin(),1+rand()%maxVal);
    }

    return v;
}

vector<int> generateVector(size_t size) {
    vector<int> v(size);

    for (int i = 0; i < size; ++i) {
        v[i] = i;
    }

    random_shuffle(v.begin(), v.end(), [](int i) {
        return rand()%i;
    });

    return v;
}

int main() {
    const int NB_TESTS = 1000;

    //initialisation du générateur aléatoire
    srand (time(NULL));

    //testChercherPosition(NB_TESTS);
    testTrier(8, 2, NB_TESTS);

    cout << "\n--------------\n";

    testChercherSiContient(10, 2, 100000);

    cout << "\n--------------\n";

    testG(8, 2, NB_TESTS);
}

void testChercherPosition(int nbTests) {
    cout << fixed << setprecision(2);

    cout << "Fonction : chercherPosition()\n";
    for (int i = 1; i <= 6; ++i) {
        vector<int> v = generateVector((size_t)pow(10, i));
        double averageIterations = 0.;

        cout << "Iterations pour n = " << v.size() << endl;
        for (int j = 1; j <= nbTests; ++j) {
            size_t posVal = chercherPosition(v, rand() % v.size());

            if (posVal != -1) {
                averageIterations += (double)(posVal + 1) / nbTests;
            } else {
                averageIterations += (double)v.size() / nbTests;
            }
        }

        cout << "---------------\nAverage: " << averageIterations << endl << endl;
    }
}

void testTrier(int nbValeurs, int base, int nbTests) {
    cout << fixed << setprecision(2);

    cout << "Fonction : trier()\n";
    for (int i = 1; i <= nbValeurs; ++i) {
        vector<int> v = generateVector((size_t)pow(base, i));
        double averageIterations = 0.;

        cout << "Iterations pour n = " << v.size() << " (" << base << "^" << i  << ") : ";
        for (int j = 1; j <= nbTests; ++j) {
            unsigned nbIterations = trier2(v);

            averageIterations += (double)nbIterations / nbTests;
        }

        cout << averageIterations << endl;
    }
}

void testChercherSiContient(int nbValeurs, int base, int nbTests) {
    cout << fixed << setprecision(2);

    cout << "Fonction : chercherSiContient2()\n";
    for (int i = 1; i <= nbValeurs; ++i) {
        vector<int> v = generateVector((size_t)pow(base, i));
        sort(v.begin(), v.end());

        double averageIterations = 0.;
        cout << "Iterations pour n = " << v.size() << " (" << base << "^" << i  << ") : ";
        for (int j = 1; j <= nbTests; ++j) {
            unsigned nbIterations = chercherSiContient2(v, rand() % v.size());

            averageIterations += (double)nbIterations / nbTests;
        }

        cout << averageIterations << endl;
    }
}

void testG(int nbValeurs, int base, int nbTests) {
    cout << fixed << setprecision(2);

    cout << "Fct : g()\n";
    for (int i = 1; i <= nbValeurs; ++i) {
        vector<int> v = generateVector((size_t)pow(base, i));

        double averageIterations = 0.;
        cout << "Iterations pour n = " << v.size() << " (" << base << "^" << i  << ") : ";
        for (int j = 1; j <= nbTests; ++j) {
            unsigned nbIterations = g2(v);

            averageIterations += (double)nbIterations / nbTests;
        }

        cout << averageIterations << endl;
    }
}
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

#include "Test.h"

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


/**
 * 2. Trie un vector.
 *
 * Pour la complexité, on considère le nombre de comparaisons (>)
 *
 * @param v vector à trier
 */
void trier(vector<int>& v) {
    if(v.empty()) return;

    for(int a : v) {
        auto j = v.begin();
        auto k = j++;
        for(; j != v.end(); k = j++ )
            if(*k > *j )
                swap(*k, *j);
    }
}

/**
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
bool chercherSiContient(const vector<int>& v, int val) {
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

/**
 * 5. Pour la complexité, on considère le nombre d'additions (+=)
 *
 * @param v
 */
void g(vector<int>& v) {
    for(size_t i = 0; i < v.size(); ++i) {
        for(size_t j = v.size() - 1; j > 0; j /= 2 ) {
            v.at(i) += v.at(j);
        }
    }
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

int main() {
    const int NB_TESTS = 1000;

    //initialisation du générateur aléatoire
    srand (time(NULL));

    testTrier(8, 2);

    cout << endl;
    testChercherSiContient(14, 2, NB_TESTS);

    cout << endl;
    testG(8, 2);
}
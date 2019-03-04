#include "Test.h"

#include <random>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <algorithm>


using namespace std;



vector<int> generateVector(size_t size) {
    vector<int> v(size);

    for (int i = 0; i < size; ++i) {
        v[i] = i;
    }

    random_shuffle(v.begin(), v.end());

    return v;
}

//Identique à trier2 en retournant le nombre d'itérations
unsigned trier2(vector<int>& v) {
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

//Idem a chercherSiContient2 mais avec le nombre d'itérations en retour
unsigned chercherSiContient2(const vector<int>& v, int val) {
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

//Fonction identique à g2 mais retourne le nombre d'itérations
unsigned g2(vector<int>& v) {
    unsigned nbIterations = 0;
    for(size_t i = 0; i < v.size(); ++i) {
        for(size_t j = v.size() - 1; j > 0; j /= 2 ) {
            ++nbIterations;
            v.at(i) += v.at(j);
        }
    }
    return nbIterations;
}

void testTrier(int nbValeurs, int base) {
    cout << fixed << setprecision(2);

    cout << "Fonction : trier()\n";
    for (int i = 1; i <= nbValeurs; ++i) {
        vector<int> v = generateVector((size_t)pow(base, i));

        cout << "Iterations pour n = " << v.size() << " (" << base << "^" << i  << ") : " << trier2(v) << endl;
    }
}

void testChercherSiContient(int nbValeurs, int base, int nbTests) {
    cout << fixed << setprecision(2);

    cout << "Fonction : chercherSiContient()\n";
    for (int i = 1; i <= nbValeurs; ++i) {
        vector<int> v = generateVector((size_t)pow(base, i));
        sort(v.begin(), v.end());

        double averageIterations = 0.;
        cout << "Iterations pour n = " << v.size() << " (" << base << "^" << i  << ") : ";

        //Calcul la moyenne pour nbTests valeurs
        for (int j = 1; j <= nbTests; ++j) {
            //La valeur recherché à 1 chance sur 10 de ne pas être dans le vecteur.
            unsigned nbIterations = chercherSiContient2(v, rand() % (v.size() + v.size() / 10));

            averageIterations += (double)nbIterations / nbTests;
        }

        cout << averageIterations << endl;
    }
}

void testG(int nbValeurs, int base) {
    cout << fixed << setprecision(2);

    cout << "Fonction : g()\n";
    for (int i = 1; i <= nbValeurs; ++i) {
        vector<int> v = generateVector((size_t)pow(base, i));

        cout << "Iterations pour n = " << v.size() << " (" << base << "^" << i  << ") : " << g2(v) << endl;
    }
}



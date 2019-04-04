/**
 \file main.cpp
 \author Stéphane Teixeira Carvalho, Diego Villagrasa, Robin Müller
 \date 04 Avril 2019
 Labo 3 : Mettre en place un programme permettant de tester les différents tris 
          demandés pour le laboratoire(selection sort, quick sort, counting sort, radix sort).
          La comparaison se fera avec le temps d'éxecution des 4 tris.
 */

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;
using namespace chrono;

// selectionSort
//
// Effectue le tri par sélection des éléments entre begin
// et end (non inclus).
template < typename RandomAccessIterator >
void selectionSort( RandomAccessIterator begin,
                    RandomAccessIterator end )
{
    //end - 1 car end non-inclus
    for(auto i = begin; i < end - 1; i++)
    {
        RandomAccessIterator imin = i;
        for(auto j = i + 1; j < end; j++)
        {
            if(*j < *imin)
            {
                imin = j;
            }
        }
        swap(*i, *imin);
    }
}

// selectPivot(begin,end)
//
// choisit un pivot pour le tri rapide parmi le tableau
// entre begin et end (non inclus). Calcule la médiane
// entre le premier, le dernier et l'élément central.
// retourne un iterateur du même type que begin et end
// pointant sur la valeur choisie.

template < typename RandomAccessIterator >
RandomAccessIterator selectPivot( const RandomAccessIterator begin,
                                  const RandomAccessIterator end )
{
    RandomAccessIterator p1 = begin;
    RandomAccessIterator p2 = begin + ( end-begin ) / 2;
    RandomAccessIterator p3 = end-1;

    if(*p1 < *p2) {
        if( *p2 < *p3 ) return p2;
        else if(*p1 < *p3) return p3;
        return p1;
    } else {
        if( *p1 < *p3 ) return p1;
        else if(*p2 < *p3) return p3;
        return p2;
    }
}

// partition
// S'occupe de partitionner les elements du vecteur
// En faisant un swap des element qui ne sont pas à leur place.
template < typename RandomAccessIterator >
RandomAccessIterator partition ( const RandomAccessIterator begin,
                                 const RandomAccessIterator end )
{
    RandomAccessIterator i = begin-1;
    RandomAccessIterator k = (end - 1);

    while(true){
        do
        {
            i++;
        } while (*i < *(end - 1));

        do
        {
            k--;
        } while (k > begin && *(end - 1) < *k);

        if(i >= k)
            break;

        iter_swap(i, k);
    }

    iter_swap(i, end - 1);
    return i;
}

// quickSort
//
// Effectue le tri rapide des éléments entre begin
// et end (non inclus). Doit appeler selectPivot(...)
// pour le choix du pivot, et display() après chaque
// partition

template < typename RandomAccessIterator >
void quickSort( RandomAccessIterator begin,
                RandomAccessIterator end )
{
    if(end - 1 <= begin)
        return;

    RandomAccessIterator pivot = selectPivot(begin, end);
    iter_swap(pivot, end - 1);
    RandomAccessIterator i = partition(begin, end);

    quickSort(begin, i);
    quickSort(i+1, end);
}

/**
 Tri comptage générique

 https://en.wikipedia.org/wiki/Counting_sort

 @param first  [first,last] est la plage d'éléments d'un tableau à trier.
 @param last   [first,last] est la plage d'éléments d'un tableau à trier.
 @param output début du tableau où écrire le résultat. Doit être différent
               du tableau d'entrée
 @param key fonction prenant un élément en entrée et retourant sa position
            dans le tableau de comptage
 @param max_key valeur maximale pouvant être retournée par key(...). Si -1,
                la fonction calcule cette valeur en parcourant le tableau une
                fois de plus
 */
template<typename RandomAccessIterator, typename Fn>
void CountingSort(RandomAccessIterator first,
                  RandomAccessIterator last,
                  RandomAccessIterator output,
                  Fn key,
                  size_t max_key = -1)
{
    //Si on a le max_key vaut -1, on parcours le tableau et calcul la valeur la plus grande
    if (max_key == (size_t)-1) {
        max_key = 0;
        for (auto it = first; it != last; ++it) {
              if (key(*it) > max_key)
                  max_key = key(*it);
        }
    }

    vector<int> count(max_key + 1);

    //On stocke le nombre de valeurs de 0 à max_key - 1
    for (auto it = first; it != last; ++it)
        ++count[key(*it)];

    //On ajoute la somme précédente à chaque somme afin d'obtenir un index
    for (size_t i = 1; i < count.size(); ++i)
        count[i] += count[i - 1];

    //On commence par la fin pour garder la stabilité
    for (auto it = prev(last); it != prev(first); --it) {
        output[count[key(*it)] - 1] = *it;
        --count[key(*it)];
    }
}

/**
 Tri par base d'entiers non signés sur 32 bits mis en oeuvre en appelant
 4 fois le tri comptage en triant successivement par groupe de 8 bits.

 https://en.wikipedia.org/wiki/Radix_sort

 @param v vecteur à trier, modifié par cette fonction
 */
void RadixSort(vector<unsigned int>& v)
{
    vector<unsigned int> temp(v.size());

    //On trie des bits de poids faible aux bits de poids fort en les sélectionnant grâce à un masque
    for (int i = 0 ; i < numeric_limits<unsigned int>::digits / 8 ; ++i) {
        CountingSort(v.begin(), v.end(), temp.begin(), [&] (unsigned x) {return (unsigned char)(x >> (8 * i) & 0xFF);}, 255); //On garde les 8 * i bits
        v = temp;
    }
}

/**
 * Test les différents tris en mesurant le temps d'exécution pour un vecteur de taille variable et une val min et max fixe
 * @param exposantMax Puissance maximal à atteindre
 * @param base base à utiliser pour la taille du vecteur
 * @param valMin plus petite valeur à stocker dans le vecteur
 * @param valMax plus grande valeur à stocker dans le vecteur
 * @param nbTests nombre de tests à effectuer pour calculer la moyenne du temps d'exécution de chaque tri
 */
void testSort1(unsigned exposantMax, unsigned base, unsigned valMin = 1, unsigned valMax = 100, unsigned nbTests = 70) {
    //Type repris de codecheck
    mt19937_64 gen(0);
    high_resolution_clock::time_point t1, t2;
    //Fonction reprise de codecheck
    uniform_int_distribution<unsigned> alea(valMin, valMax);

    cout << "******* n change, k = [" << alea.min() << ", " << alea.max() << "] *******";

    for (unsigned m = 1 ; m <= exposantMax ; m++) {
        long temps1 = 0;
        long temps2 = 0;
        long temps3 = 0;
        long temps4 = 0;

        unsigned n = (unsigned)(pow(base, m) + 0.5); //Arrondi avec +0.5
        cout << "\nn = " << n << " = " << base << "^" << m << endl;

        vector<unsigned> v(n);
        vector<unsigned> v2(n);
        vector<unsigned> v3(n);
        vector<unsigned> out(n);

        for (unsigned j = 1 ; j <= nbTests ; ++j) {
            generate(v.begin(), v.end(), [&]() { return alea(gen); });
            v2 = v;
            v3 = v;

            //Selection sort desactivé pour ne pas prendre trop de temps
            //t1 = high_resolution_clock::now();
            //selectionSort(v2.begin(), v2.end());
            //t2 = high_resolution_clock::now();
            //temps1 += duration_cast<nanoseconds>(t2 - t1).count();

            t1 = high_resolution_clock::now();
            quickSort(v3.begin(), v3.end());
            t2 = high_resolution_clock::now();
            temps2 += duration_cast<nanoseconds>(t2 - t1).count();

            t1 = high_resolution_clock::now();
            CountingSort(v.begin(), v.end(), out.begin(), [](unsigned val) { return val; }, alea.max());
            t2 = high_resolution_clock::now();
            temps3 += duration_cast<nanoseconds>(t2 - t1).count();

            t1 = high_resolution_clock::now();
            RadixSort(v);
            t2 = high_resolution_clock::now();
            temps4 += duration_cast<nanoseconds>(t2 - t1).count();
        }

        cout << "Temps d'execution pour selectionSort : " << temps1 / nbTests << " ns" << endl;
        cout << "Temps d'execution pour quickSort     : " << temps2 / nbTests << " ns" << endl;
        cout << "Temps d'execution pour CoutingSort   : " << temps3 / nbTests << " ns" << endl;
        cout << "Temps d'execution pour RadixSort     : " << temps4 / nbTests << " ns" << endl;
    }
}

/**
 * Test les différents tris en mesurant le temps d'exécution pour un vecteur de taille fixe avec une valeur max variable
 * @param exposantMax Puissance maximal à atteindre
 * @param base base à utiliser pour le calcul de la valeur max
 * @param valMin plus petite valeur à stocker dans le vecteur
 * @param n taille du vecteur à utiliser
 * @param nbTests nombre de tests à effectuer pour calculer la moyenne du temps d'exécution de chaque tri
 */
void testSort2(unsigned exposantMax, unsigned base, unsigned valMin = 1, size_t n = 100000, unsigned nbTests = 70) {
    cout << "******* n = " << n << ", k change *******";
    vector<unsigned> v(n);
    vector<unsigned> v2(n);
    vector<unsigned> v3(n);
    vector<unsigned> out(n);
    //Type repris de codecheck
    mt19937_64 gen(0);
    high_resolution_clock::time_point t1, t2;

    for (unsigned m = 1 ; m <= exposantMax ; m++) {
        long temps1 = 0;
        long temps2 = 0;
        long temps3 = 0;
        long temps4 = 0;

        unsigned k = (unsigned)(pow(base, m) + 0.5); //Arrondi avec +0.5
        //Fonction reprise de codecheck
        uniform_int_distribution<unsigned> alea(valMin, k);

        cout << "\nk = [" << alea.min() << ", " << alea.max() << "]" << endl;

        for (unsigned j = 1 ; j <= nbTests ; ++j) {
            //On génére un vecteur puis on créer des copies pour les différents tris
            generate(v.begin(), v.end(), [&]() { return alea(gen); });
            v2 = v;
            v3 = v;
            
            //Selection sort desactivé pour ne pas prendre trop de temps
            //t1 = high_resolution_clock::now();
            //selectionSort(v2.begin(), v2.end());
            //t2 = high_resolution_clock::now();
            //temps1 += duration_cast<nanoseconds>(t2 - t1).count();

            t1 = high_resolution_clock::now();
            quickSort(v3.begin(), v3.end());
            t2 = high_resolution_clock::now();
            temps2 += duration_cast<nanoseconds>(t2 - t1).count();

            t1 = high_resolution_clock::now();
            CountingSort(v.begin(), v.end(), out.begin(), [](unsigned val) { return val; }, alea.max());
            t2 = high_resolution_clock::now();
            temps3 += duration_cast<nanoseconds>(t2 - t1).count();

            t1 = high_resolution_clock::now();
            RadixSort(v);
            t2 = high_resolution_clock::now();
            temps4 += duration_cast<nanoseconds>(t2 - t1).count();
        }

        cout << "Temps d'execution pour selectionSort : " << temps1 / nbTests << " ns" << endl;
        cout << "Temps d'execution pour quickSort     : " << temps2 / nbTests << " ns" << endl;
        cout << "Temps d'execution pour CoutingSort   : " << temps3 / nbTests << " ns" << endl;
        cout << "Temps d'execution pour RadixSort     : " << temps4 / nbTests << " ns" << endl;
    }

    cout << "**************************************************";
}

int main() {
    const unsigned EXPOSANT_MAX_SORT1 = 6;
    const unsigned EXPOSANT_MAX_SORT2 = 8;
    const unsigned BASE = 10;

    cout << "n = taille vecteur, k = [val min, val max]\n";

    testSort1(EXPOSANT_MAX_SORT1, BASE);
    cout << endl;
    testSort2(EXPOSANT_MAX_SORT2, BASE);

    return EXIT_SUCCESS;
}

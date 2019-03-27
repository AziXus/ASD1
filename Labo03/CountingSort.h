//
//  CountingSort.h
//

#ifndef CountingSort_h
#define CountingSort_h

#include <vector>
#include <iostream>
#include <algorithm>
#include <type_traits>

using namespace std;

namespace asd1 {
    
    template < typename RandomAccessIterator >
    void display( const RandomAccessIterator begin,
                 const RandomAccessIterator it1,
                 const RandomAccessIterator it2,
                 const RandomAccessIterator end )
    {
        for(auto it = begin; it<it1; ++it) cout << " " << *it << " ";
        if(it1<end) cout << "[" << *it1 << "]";
        for(auto it = it1+1; it<it2; ++it) cout << " " << *it << " ";
        if(it2<end && it1!=it2) cout << "[" << *it2 << "]";
        for(auto it = it2+1; it<end; ++it) cout << " " << *it << " ";
        cout << endl;
    }
    
    // selectionSort
    //
    // Effectue le tri par sélection des éléments entre begin
    // et end (non inclus). Doit appeler display() après chaque
    // échange.
    //
    // A COMPLETER
    template < typename RandomAccessIterator >
    void selectionSort( RandomAccessIterator begin,
                       RandomAccessIterator end )
    {
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
           //display(begin,i,imin,end);
        }
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
        if (max_key == (size_t)-1) {
            //max_key = key(*std::max_element(first, last, [&] (RandomAccessIterator lhs, RandomAccessIterator rhs) { return key(*lhs) < key(*rhs);}));
            max_key = last - first;
        }

        std::vector<int> count(max_key + 1);

        //On stocke le nombre de valeurs de 0 à max_key - 1
        for (auto it = first; it != last; ++it)
            ++count[key(*it)];

        //On ajoute la somme précédente à chaque somme
        for (size_t i = 1; i < count.size(); ++i)
            count[i] += count[i - 1];

        //On commence par la fin pour garder la stabilité
        for (auto it = std::prev(last); it != std::prev(first); --it) {
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
    void RadixSort(std::vector<unsigned int>& v)
    {
        std::vector<unsigned int> temp(v.size());

//        for (int i = 0 ; i < std::numeric_limits<unsigned int>::digits / 8 ; ++i) {
//            CountingSort(v.begin(), v.end(), temp.begin(), [&] (unsigned x) {return (unsigned char)(x >> (8 * i) & 0xFF);}, 255); //On garde les 8 * i bits
//            v = temp;
//        }

        //On trie des bits de poids faible aux bits de poids fort
        CountingSort(v.begin(),    v.end(),    temp.begin(), [] (unsigned x) {return (unsigned char)(x       & 0xFF);}, 255); //On garde les 8 premiers bits
        CountingSort(temp.begin(), temp.end(), v.begin(),    [] (unsigned x) {return (unsigned char)(x >> 8  & 0xFF);}, 255); //On garde les 8 bits suivants
        CountingSort(v.begin(),    v.end(),    temp.begin(), [] (unsigned x) {return (unsigned char)(x >> 16 & 0xFF);}, 255); //On garde les 8 bits suivant
        CountingSort(temp.begin(), temp.end(), v.begin(),    [] (unsigned x) {return (unsigned char)(x >> 24 & 0xFF);}, 255); //On garde les 8 derniers bits
    }
}

#endif /* CountingSort_h */

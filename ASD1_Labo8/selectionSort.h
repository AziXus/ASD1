/**
 \file selectionSort.h
 \author Stéphane Teixeira Carvalho, Diego Villagrasa, Robin Müller
 \date 20 Mai 2019
 Labo 8 : Mettre en place une fonction permettant de d'effectuer un tri par séléction sur une
          liste doublement chainée.
          Le minimum trouvé est mis en place avec un appel à la fonction splice au lieu d'un swap.
          Le code doit passer le codecheck donné.
 */

#ifndef selectionsort_h
#define selectionsort_h

#include "listUtils.h"

template <class T>
void selectionSort(std::list<T>& L) {
    auto j = L.begin();

    //Parcours la liste et s'arrête au dernier élément comme il est déjà au bonne endroit.
    while (j != prev(L.end())) {
        auto iMin = j;
        //Recherche le plus petit élément et le stocke dans iMin
        for (auto i = next(j); i != L.end(); ++i) {
            if (*i < *iMin)
                iMin = i;
        }

        //Déplace iMin à l'emplacement j en décalant j.
        L.splice(j, L, iMin);
        std::cout << L << std::endl;
        j = next(iMin);
    }
}

#endif
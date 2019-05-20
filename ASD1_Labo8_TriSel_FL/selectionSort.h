/**
 \file fizzy.cpp
 \author Stéphane Teixeira Carvalho, Diego Villagrasa, Robin Müller
 \date 20 Mai 2019
 Labo 8 : Mettre en place une fonction permettant de d'effectuer un tri par séléction sur une
          liste simplement chainée.
          Le minimum trouvé est mis en place avec un appel à la fonction splice_after.
          Le code doit passer le codecheck donné.
 */
#ifndef selectionsort_h
#define selectionsort_h

#include "forwardListUtils.h"

template <class T>
void selectionSort(std::forward_list<T>& L) {
   using namespace std;
   if(L.empty())
      return;
   /*for (auto i = L.before_begin(); next(next(i)) != L.end(); i++) {
      auto prevI = i;
      auto pMin = i;

      for (auto j = next(i); j != L.end(); j++)
      {
         if(*j < *(next(pMin))){
            pMin = prevI;
         }
           
         prevI = j;
      }

      L.splice_after(i, L, pMin);
      cout << L << endl;
   }*/
   //Comme on affecte la valeur next de j à j et que ensuite on affetce à i le next de j.
   //Il faut vérifier que next next de j ne soit pas la fin du tableau
   for(auto j = L.before_begin(); next(next(j)) != L.end(); j = next(j))
   {
      auto iMin = j;
      //Parcourt du tableau pour trouver la valeur minimale contenue
      for(auto i = next(j); next(i) != L.end(); i = next(i))
      {
         if(*next(i) < *next(iMin)) 
            iMin = i;
         
      }
      L.splice_after(j, L, iMin);     
      cout << L << endl;
   }
}

#endif
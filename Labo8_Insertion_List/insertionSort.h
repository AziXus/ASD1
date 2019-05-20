/**
 \file fizzy.cpp
 \author Stéphane Teixeira Carvalho, Diego Villagrasa, Robin Müller
 \date 20 Mai 2019
 Labo 8 : Mettre en place une fonction permettant de d'effectuer dun tri par insertion sur une
          liste doublement chainée.
          Le code doit passer le codecheck donné.
 */
#ifndef insertionsort_h
#define insertionsort_h

#include "listUtils.h"

/**
 * Tri par insertion pour une liste doublement chainée
 * @param L Liste à mettre en ordre
 */
template <class T>
void insertionSort(std::list<T>& L) {
  using namespace std;
  //si la liste est vide on ne fait rien
  if(L.empty()) return;
  auto k = next(L.begin());
  while(k != L.end())
  {
      auto i = k;
      //pour utiliser la valeur précédente de i on utilise la fonction prev
      while(i != L.begin() && *k < *prev(i))
      { 
          //on met dans i la valeur du pointeur précédent
          i = prev(i);
      }
      //on met la prochaine valeur de k dans une variable t
      auto t = next(k);
      //on échange de place i et k
      L.splice(i, L, k);
      //on met à k la valeur enregistrée dans t
      k = t;
      cout << L << endl;
  }
}

#endif // insertionsort_h
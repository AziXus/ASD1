/**
 \file fizzy.cpp
 \author Stéphane Teixeira Carvalho, Diego Villagrasa, Robin Müller
 \date 20 Mai 2019
 Labo 8 : Mettre en place un programme permettant de d'ajouter des valeurs dans des forward List
          selon leur multiples.
          Les multiples de 3 mais pas 5 vont dans la liste F, les multiples de 5 mais pas 3 vont dans la liste B et
          les multiples de 3 et de 5 vont dans la liste FB.
          Le code doit passer le codecheck donné
 */
#include "fizzy.h"
#include <cassert>
#include <iostream>

using std::forward_list;


//Vous pouvez ajouter des fonctions annexes si nécessaire

void fizzBuzz(std::forward_list<int>& L,
              std::forward_list<int>& F,
              std::forward_list<int>& B,
              std::forward_list<int>& FB)
{
  assert(F.empty() and B.empty() and FB.empty());
  //Mise en place des différents itérateur pour parcourir les listes
  auto fPlace = F.before_begin();
  auto fbPlace = FB.before_begin();
  auto bPlace = B.before_begin();
  
  for(auto i = L.before_begin(); next(i) != L.end();)
  {
      //Comme on utilise une forward list il faut vérifier la valeur de l'itérateur après l'actuel
      //d'ou l'utilisation de la fonction next
     if(*next(i) % 15 == 0)
     {
         //On va enlever la valeur de i de la forward list L pour l'ajouter dans FB
         FB.splice_after(fbPlace, L, i);
         //Comme on a ajouté une valeur à FB on incrémente son itérateur
         fbPlace++;
     }
     else if(*next(i) % 3 == 0)
     {
         F.splice_after(fPlace, L, i);
         //Comme on a ajouté une valeur à F on incrémente son itérateur
         fPlace++;
     }
     else if(*next(i) % 5 == 0)
     {
         B.splice_after(bPlace, L, i);
         //Comme on a ajouté une valeur à B on incrémente son itérateur
         bPlace++;
     }
     else{
         //si aucune action n'est fait on incrémente l'itérateur
         i++;
     }
  }
}


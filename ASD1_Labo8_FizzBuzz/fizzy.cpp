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
  auto fPlace = F.before_begin();
  auto fbPlace = FB.before_begin();
  auto bPlace = B.before_begin();
  
  for(auto i = L.before_begin(); next(i) != L.end();)
  {
     if(*next(i) % 3 == 0 && *next(i) % 5 == 0)
     {
         FB.splice_after(fbPlace, L, i);
         fbPlace++;
     }
     else if(*next(i) % 3 == 0)
     {
         F.splice_after(fPlace, L, i);
         fPlace++;
     }
     else if(*next(i) % 5 == 0)
     {
         B.splice_after(bPlace, L, i);
         bPlace++;
     }
     else{i++;}
  }
}
/*
 ---------------------Ancienne version--------------------------------------
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
  auto place = L.before_begin();
  bool incrementation = false;
  for(auto i = L.begin(); i != L.end();)
  {
     incrementation = false;
     if(*i % 3 == 0 && *i % 5 == 0)
     {
         i++;
         incrementation = true;
         FB.splice_after(FB.before_begin(), L, place);
     }
     else if(*i % 3 == 0)
     {
         i++;
         incrementation = true;
         F.splice_after(F.before_begin(), L, place);
     }
     else if(*i % 5 == 0)
     {
         i++;
         incrementation = true;
         B.splice_after(B.before_begin(), L, place);
     }
     if(!incrementation)
     {
         i++;
         place++;
     }
  }
  FB.reverse();
  F.reverse();
  B.reverse();
} 
 */


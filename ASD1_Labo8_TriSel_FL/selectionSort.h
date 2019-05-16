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
   /*
   j ← L.début()
   tant que j != L.fin()
   iMin ← j
   i ← suivant(j)
   tant que i != L.fin()
   si *i < *iMin
   iMin ← i
   i ← suivant(i)
   échanger *iMin,*j
   j ← suivant(j)
   */
   auto j = L.before_begin();
   //next(next(j)) mais c'est pas beau
   while(next(j) != L.end())
   {
      auto iMin = j;
      auto i = next(j);
      while(next(i) != L.end())
      {
         if(*next(i) < *next(iMin)) 
            iMin = i;
         i = next(i);
      }
      L.splice_after(j, L, iMin);
      j = next(j);
      cout << L << endl;
   }
}

#endif
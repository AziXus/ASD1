#ifndef selectionsort_h
#define selectionsort_h

#include "forwardListUtils.h"

template <class T>
void selectionSort(std::forward_list<T>& L) {
   using namespace std;
   if(L.empty())
      return;
   for (auto i = L.before_begin(); next(next(i)) != L.end(); i++) {
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
   }
}

#endif
#ifndef listutils_h
#define listutils_h
#include <list>
#include <iostream>

template <class T>
std::ostream& operator<< (std::ostream& os, std::list<T> L) {
  for(const T& el : L)
    os << el << " ";
  return os;
}

template <typename T> std::list<T> readList() {
  using namespace std;
  
  list<T> L;
  int i;
  while(cin >> i)
    L.push_back(i);
  return L;
}

#endif//listutils_h
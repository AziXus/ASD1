#ifndef forwardlistutils_h
#define forwardlistutils_h

#include <forward_list>
#include <iostream>

template <class T>
std::ostream& operator<< (std::ostream& os, std::forward_list<T> L) {
  for(const T& el : L)
    os << el << " ";
  return os;
}

template <typename T> std::forward_list<T> readForwardList() {
  using namespace std;
  
  forward_list<T> L;
  auto p = L.before_begin();
  int i;
  
  while(cin >> i) {
    L.insert_after(p,i);
    ++p;
  };
  return L;
}

#endif // forwardlistutils_h
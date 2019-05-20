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
    std::list<T> L;
    int i;
    while(std::cin >> i)
        L.push_back(i);
    return L;
}

#endif // listutils_h
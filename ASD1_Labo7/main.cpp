//  main.cpp
//  ArrayDeque
//
//  Created by Olivier Cuisenaire on 02.11.18.
//  Copyright © 2018 Olivier Cuisenaire. All rights reserved.
//

#include <iostream>
#include <string>

#include "Spy.h"
#include "ArrayDeque.h"

using namespace std;

template<typename T> string name() { return "Unknown type"; }
template<> string name<int>() { return "int"; }
template<> string name<Movable>() { return "Movable"; }
template<> string name<Unmovable>() { return "Unmovable"; }

template <typename T> void testAPI() {
  cout << "Test API(" << name<T>() << ")" << endl;
  
  ArrayDeque<T> dq(10);
  
  cout << " size " << dq.size() << endl;
  cout << " capacity " << dq.capacity() << endl;
  cout << " empty " << boolalpha << dq.empty() << endl;
  { T t(0); dq.push_back(t); }   cout << endl;
  dq.push_back(1); cout << endl;
  cout << " back " << dq.back() << endl;
  { T t(2); dq.back() = t; }   cout << endl;
  dq.back() = 3;   cout << endl;
  { T t(4); dq.push_front(t); } cout << endl;
  dq.push_front(4); cout << endl;
  cout << " front " << dq.front() << endl;
  dq.front() = 5; cout << endl;
  cout << " at(0) " << dq.at(0) << endl;
  { T t(6); dq.at(0) = t; } cout << endl;
  dq.at(0) = 7; cout << endl;
  dq.pop_front(); cout << endl;
  dq.pop_back(); cout << endl;
}

template <typename T> void testConstAPI()
{
  cout << "Test const API(" << name<T>() << ")" << endl;
  
  ArrayDeque<T> dq(10);
  dq.push_back(1);
  
  const ArrayDeque<T> cdq = dq;
  cout << " size " << cdq.size() << endl;
  cout << " capacity " << cdq.capacity() << endl;
  cout << " empty " << boolalpha << cdq.empty() << endl;
  cout << " front " << cdq.front() << endl;
  cout << " back " << cdq.back() << endl;
  cout << " at(0) " << cdq.at(0) << endl;
  cout << endl;
}

template <typename T>
void fillDeque(ArrayDeque<T>& dq, size_t n)
{
  size_t cap = dq.capacity();
  for(int i = 0; i < n; ++i) {
    if(i%2)
      dq.push_front(i);
    else
      dq.push_back(i);
    
    if(cap != dq.capacity()) {
      cout << " capacity changed: " << cap << " -> " << dq.capacity() << endl;
      cap = dq.capacity();
    }
  }
}

template <typename T>
void displayDeque(ArrayDeque<T>& dq) {
  cout << " Using " << dq.size() << "/" << dq.capacity() << endl;
  cout << " Content: ";
  for( size_t i = 0; i < dq.size(); ++i ) {
    cout << dq.at(i) << " ";
  }
  cout << endl;
}

template <typename T>
void emptyDequeFromFront(ArrayDeque<T>& dq)
{
  cout << " Using " << dq.size() << "/" << dq.capacity() << endl;
  cout << " Empty from front: ";
  while(not dq.empty()) {
    cout << dq.front() << " ";
    dq.pop_front();
  }
  cout << endl;
}

template <typename T>
void emptyDequeFromBack(ArrayDeque<T>& dq)
{
  cout << " Using " << dq.size() << "/" << dq.capacity() << endl;
  cout << " Empty from back: ";
  
  while(not dq.empty()) {
    cout << dq.back() << " ";
    dq.pop_back();
  }
  cout << endl;
}

template <typename T>
void testConstantCapacity() {
  cout << endl << "Test constant capacity(" << name<T>() << ")" << endl;
  
  ArrayDeque<T> dq(20);
  fillDeque(dq, 12);
  displayDeque(dq);
  emptyDequeFromFront(dq);
  fillDeque(dq, 12);
  displayDeque(dq);
  emptyDequeFromBack(dq);
}

template <typename T>
void testVariableCapacity() {
  cout << endl << "Test variable capacity(" << name<T>() << ")" << endl;
  
  ArrayDeque<T> dq;
  fillDeque(dq,7);
  displayDeque(dq);
  emptyDequeFromFront(dq);
  fillDeque(dq,17);
  displayDeque(dq);
  emptyDequeFromBack(dq);
}

template <typename T>
void runAllTests() {
  testAPI<T>();      cout << endl;
  testConstAPI<T>(); cout << endl;
  testConstantCapacity<T>(); cout << endl;
  testVariableCapacity<T>(); cout << endl;
}

template <typename T>
void testExceptionGarantees() {
  cout << endl << "Test exception garantees(" << name<T>() << ")" << endl;

  Spy::constructorBombValue = -42;
  
  ArrayDeque<T> dq(10);
  fillDeque(dq, 7);
  displayDeque(dq);
  Spy::verbose = true;
  
  cout << endl;
  
  try {
    T bomb(Spy::constructorBombValue);
    dq.push_back(bomb);
  } catch(...) {
    displayDeque(dq);
  }
  
  cout << endl;
  
  try {
    T bomb(Spy::constructorBombValue);
    dq.push_front(bomb);
  } catch(...) {
    displayDeque(dq);
  }
  
  cout << endl;
  
  try {
    Spy::constructorBombValue = 2;
    ArrayDeque<T> copy = dq;
  } catch(...) {
    displayDeque(dq);
  }
  
  cout << endl;
  
  Spy::constructorBombValue = -42;
  Spy::verbose = false;
  
  {
    ArrayDeque<T> copy(9);
    fillDeque(copy, 5);
    displayDeque(copy);
    
    Spy::verbose = true;
    
    try {
      Spy::constructorBombValue = 4;
      copy = dq;
    } catch (...) {
      displayDeque(copy);
      displayDeque(dq);
    }
    cout << endl;
  }
  
  try {
    Spy::constructorBombValue = 4;
    for(int i = 10; i < 15; ++i)
      dq.push_back(i);
    cout << "Success !\n";
  } catch(...) {
    cout << "Boom !\n";
  }
  displayDeque(dq);
  cout << endl;
}

int main() {
  
  int testNr;
  cin >> testNr;
  
  switch(testNr) {
    case 0:
      runAllTests<int>();
      break;
    case 1:
      Spy::verbose = true;
      runAllTests<Unmovable>();
      break;
    case 2:
      Spy::verbose = true;
      runAllTests<Movable>();
      break;
    case 3:
      testExceptionGarantees<Unmovable>();
      break;
    case 4:
      testExceptionGarantees<Movable>();
      break;
    default:
      cout << "No such test number\n";
  }
}
#include <iostream>
#include "ArrayDeque.h"

using namespace std;

void testAPI() {
    cout << "Test API" << endl;

    ArrayDeque<int> dq(10);

    cout << " size " << dq.size() << endl;
    cout << " capacity " << dq.capacity() << endl;
    cout << " empty " << boolalpha << dq.empty() << endl;
    dq.push_back(0);
    cout << " back " << dq.back() << endl;
    dq.back() = 1;
    dq.push_front(0);
    cout << " front " << dq.front() << endl;
    dq.front() = 2;
    dq.pop_front();
    dq.pop_back();
}

void testConstAPI()
{
    cout << endl << "Test const API" << endl;

    ArrayDeque<int> dq(10);
    dq.push_back(0);

    const ArrayDeque<int> cdq = dq;
    cout << " size " << cdq.size() << endl;
    cout << " capacity " << cdq.capacity() << endl;
    cout << " empty " << boolalpha << cdq.empty() << endl;
    cout << " front " << cdq.front() << endl;
    cout << " back " << cdq.back() << endl;
}

void fillDeque(ArrayDeque<int>& dq, size_t n)
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

void emptyDequeFromFront(ArrayDeque<int>& dq)
{
    cout << " Using " << dq.size() << "/" << dq.capacity() << endl;
    cout << " Empty from front: ";
    while(not dq.empty()) {
        cout << dq.front() << " ";
        dq.pop_front();
    }
    cout << endl;
}

void emptyDequeFromBack(ArrayDeque<int>& dq)
{
    cout << " Using " << dq.size() << "/" << dq.capacity() << endl;
    cout << " Empty from back: ";

    while(not dq.empty()) {
        cout << dq.back() << " ";
        dq.pop_back();
    }
    cout << endl;
}

void testConstantCapacity() {
    cout << endl << "Test constant capacity" << endl;

    ArrayDeque<int> dq(20);
    fillDeque(dq, 12);
    emptyDequeFromFront(dq);
    fillDeque(dq, 12);
    emptyDequeFromBack(dq);
}

void testVariableCapacity() {
    cout << endl << "Test variable capacity" << endl;

    ArrayDeque<int> dq;
    fillDeque(dq,7);
    emptyDequeFromFront(dq);
    fillDeque(dq,17);
    emptyDequeFromBack(dq);
}

int main() {
    testAPI();
    testConstAPI();
    testConstantCapacity();
    testVariableCapacity();
}
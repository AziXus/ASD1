//
//  main.cpp
//

#define TEST_NR 10

#include <iostream>
#include "StackList.h"

using namespace std;
using namespace asd1;


// Classe utilisée pour teste les garanties fortes
class Boom {
    friend ostream& operator<< (ostream&, const Boom&);
private:
    int i;
public:
    static bool explosive;
    Boom(int _i) : i(_i) {}
    Boom(const Boom& other) {
        if(explosive)
            throw "Boom !";
        i = other.i;
    }
};
bool Boom::explosive = false;
ostream& operator<< ( ostream& os, const Boom& b) {
    os << b.i;
    return os;
}


// Classe utilisée pour tester les garanties faibles
class TimeBomb {
    friend ostream& operator<< (ostream&, const TimeBomb&);
private:
    int i;
public:
    static int timer;
    TimeBomb(int _i) : i(_i) { cout << "C "; }
    TimeBomb(const TimeBomb& other) {
        if(--timer <= 0)
            throw "Boom !";
        i = other.i;
        cout << "CC ";
    }
    ~TimeBomb() { cout << "D "; }
};
int TimeBomb::timer = 1000;
ostream& operator<< ( ostream& os, const TimeBomb& b) {
    os << b.i;
    return os;
}

#if TEST_NR > 1
// Fonction d'aide pour afficher une pile et la vider
template<typename T>
void printAndEmptyStack(const string& name, StackList<T>& s) {
    cout << name << " = ";
    while( not s.empty() ) {
        cout << s.top() << " ";
        s.pop();
    }
    cout << "\n";
}
#endif

int main() {

#if TEST_NR > 0
    {
        cout << "T1 - constructeur par défaut et fonction empty() \n";
        StackList<int> s;
        cout << "empty() : " << boolalpha << s.empty() << "\n\n";
    }
#endif

#if TEST_NR > 1
    {
        cout << "T2 - push, pop, top \n";
        StackList<int> s;
        for(int i = 0; i < 5; ++i)
            s.push(i*i);
        s.top() = 42;

        printAndEmptyStack("s",s);
        cout << "\n";
    }
#endif

#if TEST_NR > 2
    {
        cout << "T3 - exceptions \n";
        StackList<int> s;
        try {
            s.pop();
            cout << "erreur - pas d'exception levée";
        }
        catch(StackEmptyException) {
            cout << "succes";
        }
        catch(...) {
            cout << "erreur - pas la bonne exception";
        }
        cout << "\n\n";
    }
#endif

#if TEST_NR > 3
    {
        cout << "T4 - exceptions \n";
        StackList<int> s;
        try {
            s.top();
            cout << "erreur - pas d'exception levée";
        }
        catch(StackEmptyException) {
            cout << "succes";
        }
        catch(...) {
            cout << "erreur - pas la bonne exception";
        }
        cout << "\n\n";
    }
#endif

#if TEST_NR > 4
    {
       cout << "T5 - copie par constructeur \n";
        StackList<int> s1;
        for(int i = 0; i < 5; ++i)
            s1.push(i*i);
        StackList<int> s2 = s1;
        printAndEmptyStack("s1", s1);
        printAndEmptyStack("s2", s2);
        cout << "\n";
    }
#endif

#if TEST_NR > 5
    {
        cout << "T6 - copie par operateur = \n";
        StackList<int> s1;
        for(int i = 0; i < 5; ++i)
            s1.push(i*i);

        StackList<int> s2;
        for(int i = 0; i < 5; ++i)
            s2.push(-i);
        s2 = s1;

        printAndEmptyStack("s1", s1);
        printAndEmptyStack("s2", s2);
        cout << "\n\n";
    }
#endif


#if TEST_NR > 6
    {
        cout << "T7 - const correctness \n";
        StackList<int> s1;
        for(int i = 0; i < 5; ++i)
            s1.push(i*i);

        const auto s2 = s1;
        cout << s2.top() << " " << s2.empty();

        cout << "\n\n";
    }
#endif

#if TEST_NR > 7
    {
        cout << "T8 - strong garantee push \n";
        Boom::explosive = false;
        StackList<Boom> s;
        for(int i = 0; i < 5; ++i)
            s.push(i*i);

        try {
            Boom::explosive = true;
            s.push(42);
        } catch(...) {
            printAndEmptyStack("s",s);
        }
        cout << "\n";
    }
#endif

#if TEST_NR > 8
    {
        cout << "T9 - strong garantee copy \n";
        Boom::explosive = false;
        StackList<Boom> s1;
        for(int i = 0; i < 5; ++i)
            s1.push(i*i);

        StackList<Boom> s2;
        for(int i = 0; i < 4; ++i)
            s2.push(i*2);

        try {
            Boom::explosive = true;
            s2 = s1;
        } catch(...) {
            printAndEmptyStack("s1", s1);
            printAndEmptyStack("s2", s2);
        }
        cout << "\n";
    }
#endif


#if TEST_NR > 9
    {
        cout << "T10 - weak garantee copy constructor \n";
        TimeBomb::timer = 100;
        StackList<TimeBomb> s1;
        for(int i = 0; i < 5; ++i)
            s1.push(i*i);
        cout << endl;

        try {
            TimeBomb::timer = 3;
            StackList<TimeBomb> s2 = s1;
        } catch(...) {
        }
        cout << endl;
    }
    cout << endl << endl;
#endif

#if TEST_NR > 9
    {
        cout << "T10 - weak garantee operator= \n";
        TimeBomb::timer = 100;
        StackList<TimeBomb> s1;
        for(int i = 0; i < 5; ++i)
            s1.push(i*i);
        cout << endl;

        {
            StackList<TimeBomb> s2;
            s2.push(1);
            cout << endl;

            try {
                TimeBomb::timer = 3;
                s2 = s1;
            } catch(...) {
            }
            cout << endl;
        }
        cout << endl;
    }
    cout << endl;

#endif


}

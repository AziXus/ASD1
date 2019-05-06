#include "Mouchard.h"

using namespace std;

int main1() {

    Int a;              //DC    puis D(5)
    Int b(5);           //IC(5) puis D(5)
    Int c = b;          //CC(5) puis D(-1)
    Int d = move(c);    //MC(5) puis D(-2)

    a = b;              //C=(5)
    b = move(d);        //M=(5)

    return 0;
}

int main2() {
    Int* a = new Int();              //D(5)
    Int* b = new Int(5);           //D(5)
    Int* c = new Int(*b);          //D(-1)
    Int* d = new Int(move(*c));    //D(-2)

    *a = *b;
    *b = move(*d);

    delete d;
    delete c;
    delete b;
    delete a;

    return 0;
}

int main3() {
    Int* p = (Int*)::operator new(4 * sizeof(Int));

    new(p) Int();
    new(p + 1) Int(5);
    new(p + 2) Int(p[1]);
    new(p + 3) Int(move(p[2]));

    p[0] = p[1];
    p[1] = move(p[3]);

    p[3].~Int();
    p[2].~Int();
    p[1].~Int();
    p[0].~Int();

    ::operator delete(p);

    return 0;
}

#include "Mouchard.h"
#include "Pile.h"

#include <iostream>
using namespace std;

int main() {

    cout << "Test constructeur \n";
    Pile<Int> pile1(6);
    cout << endl << endl;

    cout << "Test empiler \n";
    for(int i = 0; i < 4; ++i)
        pile1.empiler(Int(i));
    cout << endl << endl;

    cout << "Contenu pile \n";
    cout << pile1 << endl << endl;
    {
        cout << "Test constructeur de copie \n";
        Pile<Int> pile2 = pile1;
        cout << endl << endl;

        cout << "Contenu pile copiée\n";
        cout << pile2 << endl << endl;

        cout << "Test destructeur \n";
    } // test destruction de pile2
    cout << endl << endl;

    cout << "Tests sommet et depiler \n";
    for(int i = 0; i < 2; ++i) {
        cout << pile1.sommet() << " ";
        pile1.depiler();
    }
    cout << endl << endl;

    cout << "Contenu pile dépilée\n";
    cout << pile1 << endl << endl;  // test contenu pile

    cout << "Test destructeur 2\n";
} // test destruction de pile2
#include "Spy.h"
#include <stdexcept>

using std::cout;

bool Spy::verbose = false;
int Spy::constructorBombValue = -4242;
int Spy::affectationBombValue = -2424;

Spy::Spy() : _i(-42) {
    if(verbose) cout << "DC ";
}

Spy::Spy(int i) : _i(i) {
    if(verbose) cout << "IC(" << _i << ") ";
}

Spy::Spy(const Spy& I) : _i(I._i) {
    if(_i == constructorBombValue) throw std::exception();
    if(verbose) cout << "CC(" << _i << ") ";
}

Spy::Spy(Spy&& I) {
    _i = I._i;
    if(verbose) cout << "MC(" << _i << ") ";
    I._i = 42;
}

Spy::~Spy() {
    if(verbose) cout << "D(" << _i << ") ";
}

Spy& Spy::operator=(const Spy& I) {
    if(I._i == affectationBombValue) throw std::exception();
    _i = I._i;
    if(verbose) cout << "=C(" << _i << ") ";
    return *this;
}

Spy& Spy::operator=(Spy&& I) {
    _i = I._i;
    if(verbose) cout << "=M(" << _i << ") ";
    I._i = 43;
    return *this;
}

using std::ostream;

ostream& operator<<(ostream& os, const Spy& I) {
    os << I._i;
    return os;
}

ostream& operator<<(ostream& os, const Movable& m) {
    os << m.spy;
    return os;
}

ostream& operator<<(ostream& os, const Unmovable& m) {
    os << m.spy;
    return os;
}
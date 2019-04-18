#include "Mouchard.h"
#include <iostream>

using namespace std;

Int::Int() : data(0) {
    if(checkConstruction == OK) {
        cerr << "Erreur: vous essayez de construire un objet déjà construit. \n";
    }
    checkConstruction = OK;
    cout << "DC ";
}

Int::~Int() {
    if(checkConstruction != OK)
        cerr << "Erreur: vous essayez de détruire un objet non construit. \n";
    checkConstruction = 0;
    cout << "D(" << data << ") " ;
}

Int::Int(int d) : data(d) {
    if(checkConstruction == OK) {
        cerr << "Erreur: vous essayez de construire un objet déjà construit. \n";
    }
    checkConstruction = OK;
    cout << "IC(" << data << ") ";
}

Int::Int(const Int& other) : data(other.data) {
    if(checkConstruction == OK) {
        cerr << "Erreur: vous essayez de construire un objet déjà construit. \n";
    }
    checkConstruction = OK;
    cout << "CC(" << data << ") ";
}

Int::Int(Int&& other) : data(other.data) {
    if(checkConstruction == OK) {
        cerr << "Erreur: vous essayez de construire un objet déjà construit. \n";
    }
    checkConstruction = OK;
    other.data = -1;
    cout << "MC(" << data << ") ";
}

Int& Int::operator= (const Int& other) {
    if(checkConstruction != OK) {
        cerr << "Erreur: vous essayez d'assigner dans un objet non construit. \n";
    }
    data = other.data;
    cout << "C=(" << data << ") ";
    return *this;
}

Int& Int::operator= (Int&& other) {
    if(checkConstruction != OK) {
        cerr << "Erreur: vous essayez d'assigner dans un objet non construit. \n";
    }
    data = other.data;
    other.data = -2;
    cout << "M=(" << data << ") ";
    return *this;
}

ostream& operator<<( ostream& os, const Int& i) {
    if(i.checkConstruction != Int::OK) {
        cerr << "Erreur: vous essayez d'afficher un objet non construit. \n";
    }
    os << i.data;
    return os;
}

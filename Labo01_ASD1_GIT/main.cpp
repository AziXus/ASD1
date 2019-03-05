//
//  main.cpp
//  Labos ASD1 2018
//
//  Created by Olivier Cuisenaire on 16.12.16.
//  Copyright © 2016 Olivier Cuisenaire. All rights reserved.
//
//	Stéphane Teixeira Carvalho, Diego Villagrasa, Robin Müller
//

#include "Tests.h"
#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

int main() {
    const int NB_TESTS = 1000;

    //initialisation du générateur aléatoire
    srand (time(NULL));

    cout << setprecision(2) << fixed;
    //Test de la fonction chercherPos jusqu'à 2 puissance 7
    cout << "chercherPos()" << endl;
    chercherPos(7, 2, NB_TESTS);

    cout << endl;
    cout << "random()" << endl;
    //Test de la fonction push_Back avec une valeur maximale de 1000 jusqu'à 2 puissance 10 de taille de vecteur
    pushBack(10, 2, 1000, NB_TESTS);

    testTrier(2, 8);

    cout << endl;
    testChercherSiContient(2, 14, NB_TESTS);

    cout << endl;
    testG(2, 8);

    return EXIT_SUCCESS;
}
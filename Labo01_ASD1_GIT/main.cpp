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
    const int NB_APPELS_FONCTION = 100000;

    //initialisation du générateur aléatoire
    srand (time(NULL));
    cout << setprecision(2) << fixed;

    cout << "chercherPos()" << endl;
    //Test de la fonction chercherPos jusqu'à 2 puissance 7
    testChercherPos(7, 2, NB_APPELS_FONCTION);
    cout << endl;

    //Test de la fonction trier jusqu'à 2 puissance 8
    cout << "trier()" << endl;
    testTrier(2, 8);
    cout << endl;

    //Test de la fonction chercherPos jusqu'à 2 puissance 14 en calculant
    //une moyenne sur 1000 appels par puissance
    cout << "chercherSiContient()" << endl;
    testChercherSiContient(2, 14, NB_APPELS_FONCTION);
    cout << endl;

    //Test de la fonction chercherPos jusqu'à 2 puissance 8
    cout << "g()" << endl;
    testG(2, 8);
    cout << endl;

    testF(6);
    cout << endl;

    //Test de la fonction random avec une valeur maximale de 1000 jusqu'à 2 puissance 10 de taille de vecteur
    cout << "random()" << endl;
    testRandom(10, 2, 1000, NB_APPELS_FONCTION);
    cout << endl;

    //Test random2 avec une incrementation de *2 16x
    cout << "random2()" << endl;
    testRandom2(10, 2, 1000, NB_APPELS_FONCTION);

    return EXIT_SUCCESS;
}
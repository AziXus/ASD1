//
//  Tests.cpp
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
#include <cmath>
#include <algorithm>
#include <chrono>

#include "Fonctions.h"

using namespace std;
using namespace chrono;

vector<int> remplissageVecteur(size_t taille)
{
    vector<int> v(taille);
    for(size_t i = 0; i < taille; i++)
    {
        v[i] = i;
    }
    random_shuffle(v.begin(),v.end());
    return v;
}

void testTrier(int base, int nbValeurs) {
    cout << fixed << setprecision(2);

    cout << "Fonction : trier()\n";
    for (int i = 1; i <= nbValeurs; ++i) {
        vector<int> v = remplissageVecteur((size_t)pow(base, i));

        cout << "Iterations pour n = " << v.size() << " (" << base << "^" << i  << ") : " << trier(v) << endl;
    }
}

void testChercherSiContient(int base, int nbValeurs, int nbTests) {
    cout << fixed << setprecision(2);

    cout << "Fonction : chercherSiContient()\n";
    for (int i = 1; i <= nbValeurs; ++i) {
        vector<int> v = remplissageVecteur((size_t)pow(base, i));
        sort(v.begin(), v.end());

        double averageIterations = 0.;
        cout << "Iterations pour n = " << v.size() << " (" << base << "^" << i  << ") : ";

        //Calcul la moyenne pour nbTests valeurs
        for (int j = 1; j <= nbTests; ++j) {
            //La valeur recherché à 1 chance sur 10 de ne pas être dans le vecteur.
            unsigned nbIterations = chercherSiContient(v, rand() % (v.size() + v.size() / 10));

            averageIterations += (double)nbIterations / nbTests;
        }

        cout << averageIterations << endl;
    }
}

void testG(int base, int nbValeurs) {
    cout << fixed << setprecision(2);

    cout << "Fonction : g()\n";
    for (int i = 1; i <= nbValeurs; ++i) {
        vector<int> v = remplissageVecteur((size_t)pow(base, i));

        cout << "Iterations pour n = " << v.size() << " (" << base << "^" << i  << ") : " << g(v) << endl;
    }
}

void chercherPos(int exposant, int base, int nb_test)
{
    double moyenne;
    //boucle parcourant jusqu'à l'exposant défini en paramètre
    for(int i = 1; i <= exposant; i++)
    {
        //création d'un vecteur de taille
        vector<int> v = remplissageVecteur((unsigned)(pow(base, i) + 0.5));
        moyenne = 0;
        cout << "Taille vecteur : " << v.size() << " | " << base << " puissance "<< i << endl;
        //boucle permettant d'avoir une moyenne du nombre d'itéartions après un nombre de test(nb_test)
        for(int j = 1; j <= nb_test; j++)
        {
            size_t nbIteration = chercherPosition(v, rand()%v.size());
            //test pour savoir si chercherPostion a trouvé une valeur ou non si ce n'est pas le cas nbIteration = -1
            if(nbIteration == (size_t)-1)
            {
                //
                moyenne += (double)v.size()/nb_test;
            }
            else
            {
                //nbIteration + 1 car chercherPosition commence à 0 et cela est déjà une iteration
                moyenne += (double)(nbIteration+1)/(double)nb_test;
            }
        }
        cout << "moyenne      : " << moyenne << endl;
    }
}
void pushBack(int exposant, int base, int maxVal, int nb_test)
{
    for(int i = 1; i <= exposant; i++)
    {
        double temps = 0.;
        vector<int> v;
        unsigned tailleVecteur = pow(base, i) + 0.5;
        for(int j = 1; j <= nb_test; j++)
        {
            //prendre le moment du commencement
            high_resolution_clock::time_point t1 = high_resolution_clock::now();
            //Lancment de la focntion random
            v = random(tailleVecteur, maxVal);
            //prendre le moment d’arrivée
            high_resolution_clock::time_point t2 = high_resolution_clock::now();
            //calcul du temps, ici en nanosecondes
            temps += duration_cast<nanoseconds>( t2 - t1 ).count();
        }
        cout << "Taille vecteur : " << v.size() << " | nb Iteration : " << v.size() << endl;
        //moyenne de temps on prend le temps total de tout les tests divisé par le nombre de tests totals
        cout << "Temps execution : " << temps/nb_test << " nanosecondes" << endl;
    }
}

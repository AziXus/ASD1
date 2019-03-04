//
//  Labo1.cpp
//  Labos ASD1 2018
//
//  Created by Olivier Cuisenaire on 16.12.16.
//  Copyright © 2016 Olivier Cuisenaire. All rights reserved.
//
//	/* NOMS DES ETUDIANTS ICI */
//

#include <stdlib.h>
#include <vector>
#include <random>
#include <ctime>
#include <iostream>
#include <chrono>

#include "Test.h"

using namespace std;
using namespace chrono;

/**
 * 1. Recherche la position d'une valeur dans un vector.
 *
 * Pour la complexité, on considère le nombre d'itérations.
 * Tester pour diverses valeurs de val, présentes ou non dans le vector.
 *
 * @param v vector dans lequel on cherche
 * @param val valeur à chercher
 * @return la position de la valeur dans le vector si trouvé, -1 sinon
 */
size_t chercherPosition( const vector<int>& v , int val ) {
    for(size_t i = 0; i < v.size(); ++i) {
        if(v.at(i) == val)
            return i;
    }
    return -1;
}


/**
 * 2. Trie un vector.
 *
 * Pour la complexité, on considère le nombre de comparaisons (>)
 *
 * @param v vector à trier
 */
void trier(vector<int>& v) {
    if(v.empty()) return;

    for(int a : v) {
        auto j = v.begin();
        auto k = j++;
        for(; j != v.end(); k = j++ )
            if(*k > *j )
                swap(*k, *j);
    }
}

/**
 * 3. Retourne true si la valeur est contenue dans le vector.
 *
 * Pour la complexité, on considère le nombre d'itérations.
 * v doit être trié en entrée !
 * Tester pour diverses valeurs de val, présentes ou non dans le vecteur.
 *
 * @param v vector trié dans lequel on cherche
 * @param val valeur à chercher
 * Retourne true si la valeur est contenue dans le vector, false sinon.
 */
bool chercherSiContient(const vector<int>& v, int val) {
    auto first = v.begin();
    auto last = v.end();

    while( first != last ) {
        auto mid = first + ( last - first ) / 2;
        if(*mid == val) {
            return true;
        } else if(*mid < val) {
            first = mid+1;
        } else {
            last = mid;
        }
    }
    return false;
}

/**
 * 4. Pour la complexité, on considère le nombre d'additions
 *
 * @param n
 * @return
 */
unsigned long long f( unsigned n ) {

    if( n == 0 ) return 1;

    return f(n-1) + f(n-1) + f(n-1);
}

/**
 * 5. Pour la complexité, on considère le nombre d'additions (+=)
 *
 * @param v
 */
void g(vector<int>& v) {
    for(size_t i = 0; i < v.size(); ++i) {
        for(size_t j = v.size() - 1; j > 0; j /= 2 ) {
            v.at(i) += v.at(j);
        }
    }
}

/**
 * 6. Pour la complexité, on considère les opérations push_back()
 *
 * Evaluer le temps d'exécution
 *
 * @param N nombre de données à générer
 * @param maxVal valeur maximale des données
 * @return vector rempli de N valeurs aléatoires.
 */
vector<int> random( size_t N , int maxVal ) {

    vector<int> v;
    for(size_t i = 0; i < N; ++i) {
        v.push_back(1+rand()%maxVal);
    }

    return v;
}

/**
 * 7. Pour la complexité, on considère les opérations insert()
 *
 * Evaluer le temps d'exécution
 *
 * @param N nombre de données à générer
 * @param maxVal valeur maximale des données
 * @return vector rempli de N valeurs aléatoires.
 */
vector<int> random2( size_t N , int maxVal ) {

    vector<int> v;
    for(size_t i = 0; i < N; ++i) {
        v.insert(v.begin(),1+rand()%maxVal);
    }

    return v;
}

/**
 * Fonction permettant de tester la fonction chercherPostion
 * @param exposant entier indiquant l'exposant jusq'au quel tester la fonction
 * @param base entier indiquant la base avec laquelle tester la fonction
 * @param nb_test nombre de test à effectuer par exposant 
 */
void chercherPos(int exposant, int base, int nb_test);

/**
 * Fonction permettant de tester la fonction random
 * @param exposant entier indiquant l'exposant jusq'au quel tester la fonction
 * @param base entier inqiuant la base avec laquel tester la fonction
 * @param maxVal entier indiquant la valeur maximale pouvant être ajouter au vecteur
 * @param nb_test nombre de test à effectuer par exposant 
 */
void pushBack(int exposant, int base, int maxVal, int nb_test);

/**
 * Fonction permettant de remplir le vecteur avec un nombre défini de valeur
 * La fonction utilise un random_shuffle pour mélanger les valeurs à l'intérieur du vecteur 
 * @param nbValeur nombre de valeurs à ajouter au vecteur
 * @return un vecteur rempli de nbValeur et mélangé
 */
std::vector<int> remplissageVecteur(std::size_t nbValeur);

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
    //Test de la focntion push_Back avec une valeur maximale de 1000 jusqu'à 2 puissance 10 de taille de vecteur
    pushBack(10, 2, 1000, NB_TESTS);

    testTrier(8, 2);

    cout << endl;
    testChercherSiContient(14, 2, NB_TESTS);

    cout << endl;
    testG(8, 2);
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
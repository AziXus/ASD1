//
//  Tests.h
//  Labos ASD1 2018
//
//  Created by Olivier Cuisenaire on 16.12.16.
//  Copyright © 2016 Olivier Cuisenaire. All rights reserved.
//
//	Stéphane Teixeira Carvalho, Diego Villagrasa, Robin Müller
//

#ifndef TESTS_H
#define TESTS_H

#include <vector>

/**
 * Fonction permettant de remplir le vecteur avec un nombre défini de valeur
 * La fonction utilise un random_shuffle pour mélanger les valeurs à l'intérieur du vecteur
 * @param nbValeur nombre de valeurs à ajouter au vecteur
 * @return un vecteur rempli de nbValeur et mélangé
 */
std::vector<int> remplissageVecteur(std::size_t taille);

/**
 * Fonction permettant de tester la fonction chercherPostion
 * @param exposant entier indiquant l'exposant jusq'au quel tester la fonction
 * @param base entier indiquant la base avec laquelle tester la fonction
 * @param nb_test nombre de test à effectuer par exposant
 */
void testChercherPos(int exposant, int base, int nb_test);

/**
 * Fonction utilisé pour tester la fonction trier(). Les valeurs sont des puissances de base jusqu'à
 * nbValeurs.
 * @param base à utiliser pour les puissances
 * @param nbValeurs puissance maximale
 */
void testTrier(int base, int nbValeurs);

/**
 * Fonction utilisé pour tester la fonction chercherSiContient(). Les valeurs sont des puissances
 * de base jusqu'à nbValeurs.
 * @param base à utiliser pour les puissances
 * @param nbValeurs puissance maximale
 * @param nbTests nombre de tests à effectuer pour chaque puissance
 */
void testChercherSiContient(int base, int nbValeurs, int nbTests);


/**
 * Fonction utilisé pour tester la fonction g(). Les valeurs sont des puissances de base jusqu'à
 * nbValeurs.
 * @param base à utiliser pour les puissances
 * @param nbValeurs puissance maximale
 */
void testG(int base, int nbValeurs);

/**
 * Fonction utilisé pour tester la fonction f().
 * @param nbValeurs nombres de valeurs à tester
 */
void testF(int nbValeurs);

/**
 * Fonction permettant de tester la fonction random
 * @param exposant entier indiquant l'exposant jusq'au quel tester la fonction
 * @param base entier indiquant la base avec laquel tester la fonction
 * @param maxVal entier indiquant la valeur maximale pouvant être ajouter au vecteur
 * @param nbTests nombre de test à effectuer par exposant
 */
void testRandom(int exposant, int base, int maxVal, int nbTests);

/**
 * Fonction utilisé pour tester la fonction random2(). Les valeurs sont multipliée par le multiplicateur * nbTests
 * @param exposant entier indiquant l'exposant jusq'au quel tester la fonction
 * @param base entier indiquant la base avec laquel tester la fonction
 * @param maxVal Valeur maximale à inserer dans le vecteur
 * @param nbTests nombre de test à effectuer par exposant
 */
void testRandom2(int exposant, int base, int maxVal, int nbTests);

#endif //TESTS_H
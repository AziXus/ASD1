//
//  Fonctions.h
//  Labos ASD1 2018
//
//  Created by Olivier Cuisenaire on 16.12.16.
//  Copyright © 2016 Olivier Cuisenaire. All rights reserved.
//
//	Stéphane Teixeira Carvalho, Diego Villagrasa, Robin Müller
//

#ifndef FONCTIONS_H
#define FONCTIONS_H

#include <vector>

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
std::size_t chercherPosition( const std::vector<int>& v , int val );

/**
 * 2. Trie un vector.
 *
 * Pour la complexité, on considère le nombre de comparaisons (>)
 * La fonction a été modifiée afin de retourner le nombre de comparaisons.
 *
 * @param v vector à trier
 * @return le nombre d'itérations (= au nombre de comparaisons)
 */
unsigned trier(std::vector<int>& v);

/**
 * 3. Retourne true si la valeur est contenue dans le vector.
 *
 * Pour la complexité, on considère le nombre d'itérations.
 * v doit être trié en entrée !
 * Tester pour diverses valeurs de val, présentes ou non dans le vecteur.
 * La fonction a été modifiée afin de retourner le nombre d'itérations.
 *
 * @param v vector trié dans lequel on cherche
 * @param val valeur à chercher
 * @return le nombre d'itérations effectué par la fonction
 */
unsigned chercherSiContient(const std::vector<int>& v, int val);


/**
 * 4. Pour la complexité, on considère le nombre d'additions
 * La fonction a été modifiée en ajoutant un paramètre comptant le nombre d'additions (+=)
 * @param n
 * @param counter compte le nombre d'additions
 * @return
 */
unsigned long long f( unsigned n, unsigned& counter );

/**
 * 5. Pour la complexité, on considère le nombre d'additions (+=)
 * La fonction a été modifiée afin de retourner le nombre d'additions (+=)
 * @param v
 * @return le nombre d'additions (+=) effectué par la fonction
 */
unsigned g(std::vector<int>& v);


/**
 * 6. Pour la complexité, on considère les opérations push_back()
 *
 * Evaluer le temps d'exécution
 *
 * @param N nombre de données à générer
 * @param maxVal valeur maximale des données
 * @return vector rempli de N valeurs aléatoires.
 */
std::vector<int> random( std::size_t N , int maxVal );


/**
 * 7. Pour la complexité, on considère les opérations insert()
 *
 * Evaluer le temps d'exécution
 *
 * @param N nombre de données à générer
 * @param maxVal valeur maximale des données
 * @return vector rempli de N valeurs aléatoires.
 */
std::vector<int> random2( std::size_t N , int maxVal );
#endif //FONCTIONS_H

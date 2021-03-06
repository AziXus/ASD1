/**
 \file main.cpp
 \author Stéphane Teixeira Carvalho, Diego Villagrasa, Robin Müller
 \date 19 Mars 2019
 Labo 2 :Mettre en place un algorithme récursif permettant de trouver toutes les solutions
         du "Puzzle impossible" (https://ocuisenaire.github.io/ASD1-Labs/puzzle/).
         Les fichiers pieces.cpp et pieces.h sont requis.
         Les solutions sont affichées dès qu'elles sont trouvées.
         Une rotation complète de tout le puzzle est considéré comme une solution différente.
 */

#include <iostream>
#include <string>
#include <algorithm>
#include "pieces.h"

using namespace std;

//Enum des côtés d'une pièce
enum COTES {HAUT, DROIT, BAS, GAUCHE};

const unsigned short MAX_ROTATIONS = 3; // Nombre de rotations max d'une pièce
const unsigned short PAIR_OFFSET = 1;   // Offset de chaque paire d'attachment dans AttachementType

/**
 * @brief Verifie si deux pièces sont compatible
 *
 * @param lhs première pièce
 * @param lCote côté a comparer de la première pièce
 * @param rhs deuxième pièce
 * @param rCote côté a comparer de la deuxième pièce
 * @return true si les pièces sont compatibles, false sinon
 */
bool verifierPieces(const Piece& lhs, COTES lCote, const Piece& rhs, COTES rCote){
   //Si l'attachment est pair, on ajoute l'offset et on regarde si l'attachement est le même que
   //la pièce de droite (FILLE_HAUT = 0, FILLE_BAS = 1 et donc FILLE_HAUT + 1 est égal FILLE_BAS)
   if (lhs[lCote] % 2 == 0)
     return lhs[lCote] + PAIR_OFFSET == rhs[rCote];
   //Si l'attachment est impair, on soustrait l'offset
   return lhs[lCote] - PAIR_OFFSET == rhs[rCote];
}

/**
 * @brief Effectue une rotation vers la gauche de la pièce
 * @param piece piece en référence à tourner
 */
void tournerPiece(Piece& piece) {
    //On shift a gauche pour simuler une rotation de la pièce
    rotate(piece.begin(), piece.begin() + 1, piece.end());
}

/**
 * @brief Affiche l'id et l'orientation d'une pièce desirée
 *        A partir de la variable globale PIECES
 *
 * @param piece pièce à afficher
 */
void afficherPiece(Piece& piece){
   Pieces def = PIECES;
   for(auto i = def.begin(); i != def.end(); i++) {
      for(size_t j = 0; j <= MAX_ROTATIONS; j++) {
         //on fait tourner la pièce jusqu'à retrouver son orientation de base dans PIECES
         if(piece == *i) {
            //distance + 1 car le vecteur def commence à 0
            cout << distance(def.begin(), i)+1;
            cout << (char) ((int) 'a' + j) << " ";
            return;
         }
         tournerPiece(*i);
      }
   }
}

/**
 * @brief Affiche un vecteur de Piece (Pieces)
 *
 * @param pieces vecteur en référence de Piece
 */
void afficherPieces(Pieces& pieces){
   for (Piece p: pieces)
      afficherPiece(p);
   cout << endl;
}

/**
 * @brief Verifie si une pièce est compatible et peut donc être posée
 *
 * @param used Pièces utilisées
 * @param piece Piece restante à poser
 * @return true Si la pièce peut être posée, false sinon
 */
bool estCompatible(Pieces& used, Piece& piece){
    bool compatibleGauche = true,
         compatibleHaut   = true;

    //Si on a un arrosoir inverse qui est en bas et qu'on est sur la ligne 1 ou la ligne 2, on aura une incompatibilté plus tard
    //On déclare la pièce invalide afin de réduire le nombre d'appels de la recursive (300 appels en moins)
    if (piece[COTES::BAS] == ARROSOIR_INVERSE && used.size() <= 5)
        return false;

    //Si la pièce n'est pas sur la première colonne, on vérifie que la pièce de gauche est compatible
    if (used.size() % 3 != 0) {
        compatibleGauche = verifierPieces(used.back(), COTES::DROIT, piece, COTES::GAUCHE);
    }

    //On vérifie que la pièce soit compatible avec le pièce du dessus.
    if (used.size() >= 3) {
        compatibleHaut = verifierPieces(used.at(used.size() - 3), COTES::BAS, piece, COTES::HAUT);
    }
    return compatibleGauche && compatibleHaut;
}

/**
 * @brief Fonction récursive permettant de poser les pièces pour obtenir les solutions du jeu
 * @param used pieces utilisées
 * @param disponibles pièces diponibles à poser
 */
void poserPiece(Pieces& used, Pieces& disponibles){
   //Si la dernière Piece à été posée, afficher les pièces utilisées
   //et return pour arrêter la recursion et tester les autres solutions
   if(disponibles.empty()){
      afficherPieces(used);
      return;
   }
   //On test chaque pièces disponibles
   for(auto i = disponibles.begin(); i != disponibles.end(); i++) {
      //On tourne chaque pièces
      for(size_t j = 0; j <= MAX_ROTATIONS; j++) {
         if(estCompatible(used, *i)) {
            used.push_back(*i);
            disponibles.erase(i);
            poserPiece(used, disponibles);
            //Si ça ne marche pas on remet comme avant
            disponibles.insert(i, used.back());
            used.pop_back();
         }
         //on tourne la pièce pour voir si elle est compatible après une rotation
         tournerPiece(*i);
      }
   }
}

int main(){
   Pieces base = PIECES;
   Pieces used;

   cout << "******** SOLUTIONS *******" << endl;
   poserPiece(used, base);

   return EXIT_SUCCESS;
}
#include <iostream>
#include <string>
#include <algorithm>
#include "pieces.h"

using namespace std;

//Enum des cotes d'une piece
enum COTES {HAUT, DROIT, BAS, GAUCHE};

const unsigned short MAX_ROTATIONS = 3;   // Nombre de rotations max d'une pièce
const unsigned short MAX_PAIR = 7;        // Id de AttachementType qui fait encore partit d'une paire
const unsigned short PAIR_OFFSET = 1;     // Offset de chaque paire dans AttachementType


/**
 * @brief Verifie si deux pièces sont compatible
 *
 * @param lhs première pièce
 * @param lSide côté a comparer de la première pièce
 * @param rhs deuxième pièce
 * @param rSide côté a comparer de la deuxième pièce
 * @return true si les pièces sont compatibles
 * @return false si les pièces ne sont pas compatibles
 */
bool verifierPieces(const Piece& lhs, COTES lSide, const Piece& rhs, COTES rSide){
   //Si le coté n'a pas de paire
   if(rhs[rSide] > MAX_PAIR)
      return false;
   //Si c'est la partie gauche de la paire
   if (lhs[lSide] % 2 == 0)
     return lhs[lSide] + PAIR_OFFSET == rhs[rSide];
   //La droite
   return lhs[lSide] - PAIR_OFFSET == rhs[rSide];
}

/**
 * @brief Affiche l'id et l'orientation d'une pièce
 *        A partir de la variable globale PIECES
 *
 * @param piece pièce à afficher
 */
void afficherPiece(Piece& piece){
   Pieces def = PIECES;
   for(auto i = def.begin(); i != def.end(); i++) {
      for(size_t j = 0; j <= MAX_ROTATIONS; j++) {
         if(piece == *i) {
            cout << distance(def.begin(), i)+1;
            cout << (char) ((int) 'a' + j) << " ";
            return;
         }
         rotate(i->begin(), i->begin() + 1, i->end());
      }
   }
}

/**
 * @brief Affiche un vecteur de Piece (Pieces)
 *
 * @param pieces vecteur de Piece
 */
void afficherPieces(Pieces& pieces){
   for(auto i = pieces.begin(); i != pieces.end(); i++)
      afficherPiece(*i);
   cout << endl;
}

/**
 * @brief Verifie si une pièce peut être posée
 *
 * @param used Pièces utilisées
 * @param piece Piece à poser
 * @return true Si la pièce peut être posée
 * @return false Si la pièce ne peut pas être posée
 */
bool estCompatible(Pieces& used, Piece& piece){
   /*return used.size() == 0 ||
         (used.size() < 3 && verifierPieces(used.back(), COTES::DROITE, piece, COTES::GAUCHE)) ||
         (used.size() >= 3 && used.size() % 3 == 0 && verifierPieces(used.at(used.size()-3), COTES::BAS, piece, COTES::HAUT)) ||
         (used.size() >= 3 && used.size() % 3 != 0 && verifierPieces(used.at(used.size()-3), COTES::BAS, piece, COTES::HAUT) && verifierPieces(used.back(), COTES::DROITE, piece, COTES::GAUCHE));*/
    bool compatibleGauche = true,
            compatibleHaut   = true;

    //Si la pièce n'est pas sur la première colonne, on vérifie que la pièce de gauche est compatible
    if (used.size() % 3 != 0) {
        compatibleGauche = verifierPieces(used.back(), COTES::DROIT, piece, COTES::GAUCHE);
    }

    //On vérifie que la pièce soit compatible avec le pièce du dessus.
    if (used.size() >= 3) {
        compatibleHaut = verifierPieces(used.at(used.size() - 3), COTES::BAS, piece, COTES::HAUT);
    }

    return compatibleGauche and compatibleHaut;
}
int ntm = 0;
void poserPiece(Pieces& used, Pieces& disponibles){
    ntm++;
   //Si la dernière Piece à été posée, afficher les pièces utilisées
   //et return pour tester les autres solutions
   if(disponibles.size() == 0){
      afficherPieces(used);
      return;
   }
   //On teste chaque pièces disponibles
   for(auto i = disponibles.begin(); i != disponibles.end(); i++) {
      //On tourne chaque pièces
      for(size_t j = 0; j <= MAX_ROTATIONS; j++) {
         if(estCompatible(used, *i)){
            used.push_back(*i);
            disponibles.erase(i);
            poserPiece(used, disponibles);
            //Ca marche pas on remet comme avant
            disponibles.insert(i, used.back());
            used.pop_back();
         }
         //On shift a gauche pour simuler une rotation de la pièce (comme le site)
         rotate(i->begin(), i->begin() + 1, i->end()); 
      }
   }
}

int main(){
   Pieces base = PIECES;
   Pieces used;
   cout << "******** SOLUTIONS *******" << endl;
   poserPiece(used, base);
   cout << ntm;
   return EXIT_SUCCESS;
}
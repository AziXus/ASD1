#include <iostream>
#include <string>
#include <algorithm>
#include "pieces.h"

using namespace std;

//Enum des côtés d'une pièce
enum COTES {HAUT, DROIT, BAS, GAUCHE};

const unsigned short MAX_ROTATIONS = 3;   // Nombre de rotations max d'une pièce
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
   //Si la partie gauche à une paire
   if (lhs[lSide] % 2 == 0)
     return lhs[lSide] + PAIR_OFFSET == rhs[rSide];
   //Sinon il ne reste plus que la dorite à verifier
   return lhs[lSide] - PAIR_OFFSET == rhs[rSide];
}

/**
 * @brief Effectue une rotation vers la gauche des attachments de la pièce
 * @param piece piece en référence à tourner
 */
void tournerPiece(Piece& piece) {
    //On shift a gauche pour simuler une rotation de la pièce (comme le site)
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
         if(piece == *i) {
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
 * @param pieces vecteur de Piece
 */
void afficherPieces(Pieces& pieces){
   for (Piece p: pieces)
      afficherPiece(p);
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
    return compatibleGauche && compatibleHaut;
}
/**
 * Fonction récursive permettant de poser les pièces pour obtenir les solutions du jeu
 * @param used 
 * @param disponibles
 */
void poserPiece(Pieces& used, Pieces& disponibles){
   //Si la dernière Piece à été posée, afficher les pièces utilisées
   //et return pour tester les autres solutions
   if(disponibles.empty()){
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
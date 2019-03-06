#include <iostream>
#include <string>
#include <algorithm>
#include "pieces.h"

using namespace std;

//Enum des cotes d'une piece
enum SIDES {HAUT, DROITE, BAS, GAUCHE};

const short MAX_ROTATIONS = 3;

bool estCompatible(const Piece& lhs, SIDES lSide, const Piece& rhs, SIDES rSide){
   if(rhs[rSide] > 7)
      return false;
   if (lhs[lSide] % 2 == 0) {
     return lhs[lSide] + 1 == rhs[rSide];
   }
   return lhs[lSide] - 1 == rhs[rSide];
}


bool afficherPiece(Piece piece){
   Pieces def = PIECES;
   for(auto i = def.begin(); i != def.end(); i++)
   {
      for(size_t j = 0; j <= MAX_ROTATIONS; j++)
      {
         if(piece == *i){
            cout << distance(def.begin(), i)+1;
            cout << (char) ((int) 'a' + j) << " ";
            return true;
         }
         rotate(i->begin(), i->begin() + 1, i->end());
      }
   }
   return false;
}

void afficherPieces(Pieces pieces){ 
   for(auto i = pieces.begin(); i != pieces.end(); i++)
   {
      afficherPiece(*i);
   }
   cout << endl;
}


bool poserPiece(Pieces& used, Pieces& disponibles){
   //On fake qu'on a pas trouvé mais on print quand meme l'ordre
   //Comme ca il calcul les autres solutions
   if(disponibles.size() == 0){
      afficherPieces(used);
      return false;
   }
   for(auto i = disponibles.begin(); i != disponibles.end(); i++)
   {
      for(size_t j = 0; j <= MAX_ROTATIONS; j++)
      {
         if(used.size() == 0 || 
         (used.size() < 3 && estCompatible(used.back(), SIDES::DROITE, *i, SIDES::GAUCHE) || 
         (used.size() >= 3 && used.size() % 3 == 0 && estCompatible(used.at(used.size()-3), SIDES::BAS, *i, SIDES::HAUT)) ||
         (used.size() >= 3 && used.size() % 3 != 0 && estCompatible(used.at(used.size()-3), SIDES::BAS, *i, SIDES::HAUT) && estCompatible(used.back(), SIDES::DROITE, *i, SIDES::GAUCHE)))){

            used.push_back(*i);
            disponibles.erase(i);
            //On pose la piece suivante
            if(poserPiece(used, disponibles)){
               if(used.size() == 0){
                  afficherPiece(used.front());
                  cout << endl;
               }
               else{
                  afficherPiece(used.front());
                  used.erase(used.begin());
               return true;
               }  
            }
            //Ca marche pas on remet comme avant
            disponibles.insert(i, used.back());
            used.pop_back();
         }
         //On shift a gauche (comme le site)
         rotate(i->begin(), i->begin() + 1, i->end()); 
      }
   }
   //On a pas de suite
   return false;
}

int main(){
   Pieces base = PIECES;
   Pieces used;
   cout << "*** SOLUTIONS ***" << endl;
   poserPiece(used, base);
   return 0;
}
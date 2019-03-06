#include <iostream>
#include <string>
#include <algorithm>
#include "pieces.h"

using namespace std;

enum SIDES {HAUT, DROITE, BAS, GAUCHE};
const short MAX_ROTATIONS = 4;

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
      for(size_t j = 0; j < MAX_ROTATIONS; j++)
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
   if(disponibles.size() == 0){
      afficherPieces(used);
      return false;
   }
   //1-2-3
   if(used.size() < 3){
      for(auto i = disponibles.begin(); i != disponibles.end(); i++)
      {
         for(size_t j = 0; j < MAX_ROTATIONS; j++)
         {
            if(used.size() == 0 || estCompatible(used.back(), SIDES::DROITE, *i, SIDES::GAUCHE)){
               used.push_back(*i);
               disponibles.erase(i);
               int uS = used.size();
               int dS = disponibles.size();
               bool rep = poserPiece(used, disponibles);
               if(rep){
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
               disponibles.insert(i, used.back());
               used.pop_back();
            }
            rotate(i->begin(), i->begin() + 1, i->end()); 
         }
      }
   }
   else if(used.size() % 3 == 0){
      for(auto i = disponibles.begin(); i != disponibles.end(); i++)
      {
         for(size_t j = 0; j < MAX_ROTATIONS; j++)
         {
            if(estCompatible(used.at(used.size()-3), SIDES::BAS, *i, SIDES::HAUT)){
               used.push_back(*i);
               disponibles.erase(i);
               if(poserPiece(used, disponibles)){
                  afficherPiece(used.front());
                  used.erase(used.begin());
                  return true;
               }
               disponibles.insert(i, used.back());
               used.pop_back();
            }
            rotate(i->begin(), i->begin() + 1, i->end()); 
         }
      }
   }
   else{
      for(auto i = disponibles.begin(); i != disponibles.end(); i++)
      {
         for(size_t j = 0; j < MAX_ROTATIONS; j++)
         {
            if(estCompatible(used.at(used.size()-3), SIDES::BAS, *i, SIDES::HAUT) && estCompatible(used.back(), SIDES::DROITE, *i, SIDES::GAUCHE)){
               used.push_back(*i);
               disponibles.erase(i);
               if(poserPiece(used, disponibles)){
                  afficherPiece(used.front());
                  used.erase(used.begin());
                  return true;
               }
               disponibles.insert(i, used.back());
               used.pop_back();
            }
            rotate(i->begin(), i->begin() + 1, i->end()); 
         }
      }
   }
   return false;
}

int main(){
   Pieces base = PIECES;
   Pieces used;
   cout << "*** SOLUTIONS ***" << endl;
   poserPiece(used, base);
   return 0;
}
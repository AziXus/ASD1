#include <cstdlib>
#include <string>
#include <algorithm>
#include <vector>
#include "pieces.h"

using namespace std;

void tournerPiece(Piece piece)
{
    rotate(piece.begin(),piece.end(),piece.end());
}

bool estCompatible(Piece piece1, Piece piece2)
{
    for(auto i = piece1.begin(); i < piece1.end();i++)
    {
        for(auto j = piece2.begin(); j < piece2.end();j++)
        {
            if(i%2 == 0)
            {
                if(*i == *j - 1)
                {
                  return true;
                }   
            }
            else
            {
                if(*i - 1 == *j)
                {
                  return true;
                } 
            }
        }
    }
    return false;
}

string poserPiece(Piece piece, int orientation, Pieces piecesDisponible)
{
    if(piecesDisponible.size() == 0)
    {
        return char('A' + orientation);
    }
    else{
        for(int i = 0; i < piecesDisponible.size(); i++)
        {
            if(estCompatible(piecesDisponible.at(i), piece))
            {
                for(int k = 0; i < k; i++)
                {
                    estCompatible(piecesDisponible.at(i).at(1), piece.at(3));
                }
            }
            else
            {
                
            }
        }
    }
}


int main() {
    

    return EXIT_SUCCESS;
}


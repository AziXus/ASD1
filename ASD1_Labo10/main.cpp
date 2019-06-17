
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <queue>
#include <algorithm>
#include <unordered_set>

using namespace std;

const char EMPLACEMENT_VIDE = '0';
const uint8_t NB_COLONNES = 3;
const uint8_t NB_LIGNES = 3;
const string ETAT_CIBLE = "012345678";
enum Deplacement {HAUT, BAS, DROITE, GAUCHE};

struct Sommet {
    string etat;
    string chemin;
};

Sommet ajoutVoisin(const Sommet& noeud, size_t pos, Deplacement deplacement){
    Sommet nouveauNoeud;
    nouveauNoeud.etat = noeud.etat;
    switch(deplacement){
        //nouveauNoeud.etat[pos - NB_COLONNES] nous donne la case situé au dessus de la case 0 avec laquelle on peut échanger de place
        case HAUT   : swap(nouveauNoeud.etat[pos], nouveauNoeud.etat[pos - NB_COLONNES]);
                      nouveauNoeud.chemin = noeud.chemin + to_string(pos - NB_COLONNES);
                      break;
        //nouveauNoeud.etat[pos + NB_COLONNES] nous donne la case situé en dessous de la case 0 avec laquelle on peut échanger de place
        case BAS    : swap(nouveauNoeud.etat[pos], nouveauNoeud.etat[pos + NB_COLONNES]);
                      nouveauNoeud.chemin = noeud.chemin + to_string(pos + NB_COLONNES);
                      break;
        //nouveauNoeud.etat[pos + 1] nous donne la case situé juste à droite de la case 0
        case DROITE : swap(nouveauNoeud.etat[pos], nouveauNoeud.etat[pos + 1]);
                      nouveauNoeud.chemin = noeud.chemin + to_string(pos + 1);
                      break;
        //nouveauNoeud.etat[pos - 1] nous donne la case situé juste à gauche de la case 0
        case GAUCHE : swap(nouveauNoeud.etat[pos], nouveauNoeud.etat[pos - 1]);
                      nouveauNoeud.chemin = noeud.chemin + to_string(pos - 1);
                      break;
        default     : cout << "Deplacement inconnu" << endl;
    }
    return nouveauNoeud;
}

vector<Sommet> trouverVoisins(const Sommet& noeud) {
    vector<Sommet> etatsVoisin;

    //On trouve l'emplacement du 0 dans la chaîne
    size_t pos = noeud.etat.find(EMPLACEMENT_VIDE);

    //Recherche des mouvements possible
    //Possibilité de mouvement vers le haut si on est pas sur la première ligne(pos plus loin que la 3ème case)
    if (pos >= NB_COLONNES) {     
        etatsVoisin.push_back(ajoutVoisin(noeud, pos, HAUT));
    }

    //Possibilté de mouvement vers le bas donc est pas sur la dernière ligne plus petit que 6
    if (pos < (NB_COLONNES - 1) * NB_LIGNES) {
        etatsVoisin.push_back(ajoutVoisin(noeud, pos, BAS));
    }

    //Possibilté de mouvement vers la droite si la pos est dans la colonne 0 ou 1(pos % NB_COLONNES)
    if (pos % NB_COLONNES <= 1) {
        etatsVoisin.push_back(ajoutVoisin(noeud, pos, DROITE));
    }

    //Possibilté de mouvement vers la gauche si la pos est dans la colonne 1 ou 2(pos % NB_COLONNES)
    if (pos % NB_COLONNES >= 1) {
        etatsVoisin.push_back(ajoutVoisin(noeud, pos, GAUCHE));
    }

    return etatsVoisin;
}

bool BFS(const string& sommet, string& chemin) {
    chemin = "";

    if (sommet == ETAT_CIBLE)
        return true;

    Sommet noeudDepart = {.etat = sommet, .chemin = ""};

    queue<Sommet> q;
    q.push(noeudDepart);

    //Stocke les parents dans un ordered_set pour avoir une recherche de complexité constante
    unordered_set<string> parents;

    while (!q.empty()) {
        auto parent = q.front();
        q.pop();

        parents.insert(parent.etat);

        auto voisins = trouverVoisins(parent);

        for (const auto& voisin : voisins) {
            if (voisin.etat == ETAT_CIBLE) {
                chemin = voisin.chemin;
                return true;
            }

            if (parents.find(voisin.etat) != parents.end())
                continue;

            q.push(voisin);
        }
    }

    return false;
}


int main() {
    string source, chemin;
    
    cout << "Etat du taquin : ";
    getline(cin, source);

    //Ajouter fonction de vérification et de nettoyage de la saisie (espace)
    //On enlève les eventuelles espaces
    source.erase(remove_if(source.begin(), source.end(), ::isspace), source.end());

    if (BFS(source, chemin)) {
        cout << "Le chemin suivant a ete trouve : ";
        for (char c : chemin)
            cout << c << " ";
    } else {
        cout << "Aucun chemin n'a ete trouve" << endl;
    }

    return EXIT_SUCCESS;
}


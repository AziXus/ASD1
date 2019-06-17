
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

struct Sommet {
    string etat;
    string chemin;
};

vector<Sommet> trouverVoisins(const Sommet& noeud) {
    vector<Sommet> etatsVoisin;

    //On trouve l'emplacement du 0
    size_t pos = noeud.etat.find(EMPLACEMENT_VIDE);

    //Recherche les mouvements possible
    //Haut donc si on est pas sur la première ligne
    if (pos >= NB_COLONNES) {
        Sommet nouveauNoeud;
        nouveauNoeud.etat = noeud.etat;
        swap(nouveauNoeud.etat[pos], nouveauNoeud.etat[pos - NB_COLONNES]);
        nouveauNoeud.chemin = noeud.chemin + to_string(pos - NB_COLONNES);
        etatsVoisin.push_back(nouveauNoeud);
    }

    //Bas donc est pas sur la dernière ligne
    if (pos < (NB_COLONNES - 1) * NB_LIGNES) {
        Sommet nouveauNoeud;
        nouveauNoeud.etat = noeud.etat;
        swap(nouveauNoeud.etat[pos], nouveauNoeud.etat[pos + NB_COLONNES]);
        nouveauNoeud.chemin = noeud.chemin + to_string(pos + NB_COLONNES);
        etatsVoisin.push_back(nouveauNoeud);
    }

    //Droite
    if (pos % NB_COLONNES <= 1) {
        Sommet nouveauNoeud;
        nouveauNoeud.etat = noeud.etat;
        swap(nouveauNoeud.etat[pos], nouveauNoeud.etat[pos + 1]);
        nouveauNoeud.chemin = noeud.chemin + to_string(pos + 1);
        etatsVoisin.push_back(nouveauNoeud);
    }

    //Gauche
    if (pos % NB_COLONNES >= 1) {
        Sommet nouveauNoeud;
        nouveauNoeud.etat = noeud.etat;
        swap(nouveauNoeud.etat[pos], nouveauNoeud.etat[pos - 1]);
        nouveauNoeud.chemin = noeud.chemin + to_string(pos - 1);
        etatsVoisin.push_back(nouveauNoeud);
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

//        parents[parent.etat] = true;
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
        cout << "Aucun chemin n'a été trouvé" << endl;
    }

    return EXIT_SUCCESS;
}


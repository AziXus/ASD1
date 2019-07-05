
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <queue>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>

using namespace std;

const string EMPLACEMENT_VIDE = "XX";
const uint8_t NB_COLONNES = 4;
const uint8_t NB_LIGNES = 4;
const string ETAT_CIBLE = "XX010203040506070809101112131415";
//const string ETAT_CIBLE = "XX0102030405060708";
//const string ETAT_CIBLE = "012345678";

struct Sommet {
    string etat;
    string chemin;
};

const Sommet CIBLE = {.etat = ETAT_CIBLE, .chemin = ""};

enum Move {UP, DOWN, LEFT, RIGHT};

//string deplacer(string etat, Move action) {
//    swap_ranges()
//}

//vector<Sommet> trouverVoisins(const Sommet& noeud) {
//    vector<Sommet> etatsVoisin;
//
//    //On trouve l'emplacement du 0
//    size_t pos = noeud.etat.find(EMPLACEMENT_VIDE);
//
//    //Recherche les mouvements possible
//    //Haut donc si on est pas sur la première ligne
//    if (pos >= NB_COLONNES) {
//        Sommet nouveauNoeud;
//        nouveauNoeud.etat = noeud.etat;
//        swap(nouveauNoeud.etat[pos], nouveauNoeud.etat[pos - NB_COLONNES]);
//        nouveauNoeud.chemin = noeud.chemin + to_string(pos - NB_COLONNES);
//        etatsVoisin.push_back(nouveauNoeud);
//    }
//
//    //Bas donc est pas sur la dernière ligne
//    if (pos < (NB_COLONNES - 1) * NB_LIGNES) {
//        Sommet nouveauNoeud;
//        nouveauNoeud.etat = noeud.etat;
//        swap(nouveauNoeud.etat[pos], nouveauNoeud.etat[pos + NB_COLONNES]);
//        nouveauNoeud.chemin = noeud.chemin + to_string(pos + NB_COLONNES);
//        etatsVoisin.push_back(nouveauNoeud);
//    }
//
//    //Droite
//    if (pos % NB_COLONNES <= 1) {
//        Sommet nouveauNoeud;
//        nouveauNoeud.etat = noeud.etat;
//        swap(nouveauNoeud.etat[pos], nouveauNoeud.etat[pos + 1]);
//        nouveauNoeud.chemin = noeud.chemin + to_string(pos + 1);
//        etatsVoisin.push_back(nouveauNoeud);
//    }
//
//    //Gauche
//    if (pos % NB_COLONNES >= 1) {
//        Sommet nouveauNoeud;
//        nouveauNoeud.etat = noeud.etat;
//        swap(nouveauNoeud.etat[pos], nouveauNoeud.etat[pos - 1]);
//        nouveauNoeud.chemin = noeud.chemin + to_string(pos - 1);
//        etatsVoisin.push_back(nouveauNoeud);
//    }
//
//    return etatsVoisin;
//}
vector<Sommet> trouverVoisins(const Sommet& noeud) {
    vector<Sommet> etatsVoisin;

    //On trouve l'emplacement du 0
    size_t pos = noeud.etat.find(EMPLACEMENT_VIDE);

    //Recherche les mouvements possible
    //Haut donc si on est pas sur la première ligne
//    if (pos >= 6) {
    if (pos >= 8) {
        Sommet nouveauNoeud;
        nouveauNoeud.etat = noeud.etat;
        swap(nouveauNoeud.etat[pos], nouveauNoeud.etat[pos - 6]);
        swap(nouveauNoeud.etat[pos + 1], nouveauNoeud.etat[pos - 5]);
        if (pos / 2 - NB_COLONNES >= 10)
            nouveauNoeud.chemin = noeud.chemin + to_string(pos / 2 - NB_COLONNES);
        else
            nouveauNoeud.chemin = noeud.chemin + to_string(0) + to_string(pos / 2 - NB_COLONNES);
        etatsVoisin.push_back(nouveauNoeud);
    }

    //Bas donc est pas sur la dernière ligne
//    if (pos <= 11) {
    if (pos <= 23) {
        Sommet nouveauNoeud;
        nouveauNoeud.etat = noeud.etat;
        swap(nouveauNoeud.etat[pos], nouveauNoeud.etat[pos + 6]);
        swap(nouveauNoeud.etat[pos + 1], nouveauNoeud.etat[pos + 7]);
        if (pos / 2 + NB_COLONNES >= 10)
            nouveauNoeud.chemin = noeud.chemin + to_string(pos / 2 + NB_COLONNES);
        else
            nouveauNoeud.chemin = noeud.chemin + to_string(0) + to_string(pos / 2 + NB_COLONNES);
        etatsVoisin.push_back(nouveauNoeud);
    }

    //Droite
//    if (pos % 6 <= 3) {
    if (pos % 8 <= 5) {
        Sommet nouveauNoeud;
        nouveauNoeud.etat = noeud.etat;
        swap(nouveauNoeud.etat[pos], nouveauNoeud.etat[pos + 2]);
        swap(nouveauNoeud.etat[pos + 1], nouveauNoeud.etat[pos + 3]);
        if (pos / 2 + 1 >= 10)
            nouveauNoeud.chemin = noeud.chemin + to_string(pos / 2 + 1);
        else
            nouveauNoeud.chemin = noeud.chemin + to_string(0) + to_string(pos / 2 + 1);
        etatsVoisin.push_back(nouveauNoeud);
    }

    //Gauche
//    if (pos % 6 >= 2) {
    if (pos % 8 >= 2) {
        Sommet nouveauNoeud;
        nouveauNoeud.etat = noeud.etat;
        swap(nouveauNoeud.etat[pos], nouveauNoeud.etat[pos - 2]);
        swap(nouveauNoeud.etat[pos + 1], nouveauNoeud.etat[pos - 1]);
        if (pos / 2 - 1 >= 10)
            nouveauNoeud.chemin = noeud.chemin + to_string(pos / 2 - 1);
        else
            nouveauNoeud.chemin = noeud.chemin + to_string(0) + to_string(pos / 2 - 1);
        etatsVoisin.push_back(nouveauNoeud);
    }


    return etatsVoisin;
}

string trouverPosition(const string& etat, size_t pos) {
    return etat.substr(pos * 2, 2);
//    return etat.substr(pos * 1, 1);
}

//Calcul valeur de l'état en fonction du nombre d'éléments au mauvaise endroit
int misplaced(const string& etat, const string& cible) {
    int dist = 0;

    for (int i = 0; i < NB_COLONNES * NB_LIGNES; ++i) {
        if (trouverPosition(etat, i) != EMPLACEMENT_VIDE) {
            int index = stoi(trouverPosition(cible, stoi(trouverPosition(etat, 1))));

            if (index != i)
                dist++;
        }
    }

    return dist;
}

//Calcul valeur de l'état en fonction de la distance de manhattan
int manhattan(const string& etat, const string& cible) {
    int dist = 0;

    for (int i = 0; i < NB_LIGNES; ++i) {
        for (int j = 0 ; j < NB_COLONNES; ++j) {
            int pos = i * NB_COLONNES + j;
            auto p = trouverPosition(etat, pos);
            if (p != EMPLACEMENT_VIDE)
                dist += abs(i - stoi(trouverPosition(etat, pos)) / 4) + abs(j - stoi(trouverPosition(etat, pos)) % 4);
        }
//        string val = trouverPosition(etat, i);
//        if (val != EMPLACEMENT_VIDE) {
//            int index = stoi(trouverPosition(cible, stoi(val)));
//            int xf = index / 4;
//            int yf = index % 4;
//            int xa = i / 4;
//            int ya = i % 4;
//
//            sum += abs(xf - xa) + abs(yf - ya);
//        }
    }

    return dist;
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
//        cout << parent.etat << endl;
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

using key = pair<int, Sommet>;

//template <typename T>
struct manhattanCompare {
    bool operator()(const key& s1, const key& s2) {
        return s1.first > s2.first;
    }
};


bool AStar(const string& sommet, string& chemin) {
    chemin = "";
    int n = 0;
    if (sommet == ETAT_CIBLE)
        return true;

    Sommet noeudDepart = {.etat = sommet, .chemin = ""};

    priority_queue<key, vector<key>, manhattanCompare> q;
//    queue<Sommet> q;
    q.push(key(0, noeudDepart));

    //Stocke les parents dans un ordered_set pour avoir une recherche de complexité constante
//    unordered_set<string> parents;
    map<string, uint8_t> parents;

    while (!q.empty()) {
        int flag = 0;

        auto courant = q.top().second;
        q.pop();

        if (parents.find(courant.etat) == parents.end())
            parents.insert(make_pair(courant.etat, courant.chemin.size() / 2));

        if (parents[courant.etat] >= courant.chemin.size() / 2)
            parents[courant.etat] = courant.chemin.size() / 2;
        else
            flag = 1;

        if (courant.etat == "XX010203040506070809101112131415" or courant.etat == CIBLE.etat or courant.etat == ETAT_CIBLE) {
            chemin = courant.chemin;
            return true;
        }

        if (!flag) {
            auto voisins = trouverVoisins(courant);

            for (const auto& voisin : voisins) {
                q.push(make_pair(manhattan(voisin.etat, CIBLE.etat) * 1.1 + voisin.chemin.size() / 2, voisin));
            }
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

    if (AStar(source, chemin)) {
        cout << "Le chemin suivant a été trouvé : ";
        for (int i = 0; i < chemin.size(); i += 2)
            cout << chemin.substr(i, 2) << " ";
        cout << endl;
    } else {
        cout << "Aucun chemin n'a été trouvé" << endl;
    }

    if (BFS(source, chemin)) {
        cout << "Le chemin suivant a été trouvé : ";
        for (int i = 0; i < chemin.size(); i += 2)
            cout << chemin.substr(i, 2) << " ";
        cout << endl;
    } else {
        cout << "Aucun chemin n'a été trouvé" << endl;
    }

    return EXIT_SUCCESS;
}

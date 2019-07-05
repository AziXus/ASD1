/**
\file main.cpp
\author Stéphane Teixeira Carvalho, Diego Villagrasa, Robin Müller
\date 17 Juin 2019
Labo 10 : Création d'un programme permettant de générer la séquence la plus courte pour résoudre un taquin 3x3.
La solution donnera tout les déplacements à effectuer avec la case vide(0). Les cases sont notées de 0 à 8.

Afin de trouver la solution la plus courte d'un taquin 4x4, il serait nécessaire de modifier l'algorithme
de parcours en utilisant une priority_queue. Il faudrait également ajouter une méthode permettant d'évaluer
le coût d'un état pour arriver jusqu'à l'état cible. De cette façon, on traite toujours en premier le
l'état avec le coût le plus faible (donc le plus prometteur). L'utilisation d'un parcours IDA* est nécessaire.
*/

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
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

/**
 * Déplace le noeud passé en paramètres vers une postion voisin donné
 * @param noeud sommet de type constant étant le noeud à deplacer
 * @param pos size_t indiqaunt la postion du noeud dans le taquin
 * @param deplacement variable de type Deplacement permettant d'indiquer au noeud vers quelle voisin se déplacer
 * @return le nouvelle position du sommet dans le taquin
 */
Sommet deplacementVoisin(const Sommet& noeud, size_t pos, Deplacement deplacement){
    Sommet nouveauNoeud;
    nouveauNoeud.etat = noeud.etat;
    switch(deplacement){
        //nouveauNoeud.etat[pos - NB_COLONNES] nous donne la case située au dessus de la case 0 avec laquelle on peut échanger de place
        case HAUT   : swap(nouveauNoeud.etat[pos], nouveauNoeud.etat[pos - NB_COLONNES]);
                      nouveauNoeud.chemin = noeud.chemin + to_string(pos - NB_COLONNES);
                      break;
        //nouveauNoeud.etat[pos + NB_COLONNES] nous donne la case située en dessous de la case 0 avec laquelle on peut échanger de place
        case BAS    : swap(nouveauNoeud.etat[pos], nouveauNoeud.etat[pos + NB_COLONNES]);
                      nouveauNoeud.chemin = noeud.chemin + to_string(pos + NB_COLONNES);
                      break;
        //nouveauNoeud.etat[pos + 1] nous donne la case située juste à droite de la case 0
        case DROITE : swap(nouveauNoeud.etat[pos], nouveauNoeud.etat[pos + 1]);
                      nouveauNoeud.chemin = noeud.chemin + to_string(pos + 1);
                      break;
        //nouveauNoeud.etat[pos - 1] nous donne la case située juste à gauche de la case 0
        case GAUCHE : swap(nouveauNoeud.etat[pos], nouveauNoeud.etat[pos - 1]);
                      nouveauNoeud.chemin = noeud.chemin + to_string(pos - 1);
                      break;
        default     : cout << "Deplacement inconnu" << endl;
    }
    return nouveauNoeud;
}

/**
 * Permet de trouver les voisins d'un noeud
 * @param noeud variable de type Sommet étant le noeud auquel il faut trouver les voisins
 * @return un vecteur de Sommets contenant les différents voisins du sommet
 */
vector<Sommet> trouverVoisins(const Sommet& noeud) {
    vector<Sommet> etatsVoisin;

    //On trouve l'emplacement du 0 dans la chaîne
    size_t pos = noeud.etat.find(EMPLACEMENT_VIDE);

    //Recherche des mouvements possible
    //Possibilité de mouvement vers le haut si on est pas sur la première ligne(pos plus loin que la 3ème case)
    if (pos >= NB_COLONNES) {     
        etatsVoisin.push_back(deplacementVoisin(noeud, pos, HAUT));
    }

    //Possibilté de mouvement vers le bas donc est pas sur la dernière ligne plus petit que 6
    if (pos < (NB_COLONNES - 1) * NB_LIGNES) {
        etatsVoisin.push_back(deplacementVoisin(noeud, pos, BAS));
    }

    //Possibilté de mouvement vers la droite si la pos est dans la colonne 0 ou 1(pos % NB_COLONNES)
    if (pos % NB_COLONNES <= 1) {
        etatsVoisin.push_back(deplacementVoisin(noeud, pos, DROITE));
    }

    //Possibilté de mouvement vers la gauche si la pos est dans la colonne 1 ou 2(pos % NB_COLONNES)
    if (pos % NB_COLONNES >= 1) {
        etatsVoisin.push_back(deplacementVoisin(noeud, pos, GAUCHE));
    }

    return etatsVoisin;
}

/**
 * Permet le parcours en largeur d'un graphe en donnant son sommet
 * @param sommet string contenant le sommet à partir duquel démarrer le parcours
 * @param chemin string contenant le chemin parcouru dans le graphe(contient les déplacements de la case 0)
 * @return vrai si le parcours à atteint l'état 012345678, faux sinon
 */
bool BFS(const string& sommet, string& chemin) {
    chemin = "";
    //Si le sommet est déjà l'état cible on ne fait rien
    if (sommet == ETAT_CIBLE)
        return true;

    Sommet noeudDepart = {.etat = sommet, .chemin = ""};

    queue<Sommet> q;
    q.push(noeudDepart);

    //Stocke les parents dans un unordered_set pour avoir une recherche de complexité constante
    unordered_set<string> parents;

    while (!q.empty()) {
        auto parent = q.front();
        q.pop();

        parents.insert(parent.etat);
        
        auto voisins = trouverVoisins(parent);

        for (const auto& voisin : voisins) {
            //Si on trouve l'état cible on sort de la fonction
            if (voisin.etat == ETAT_CIBLE) {
                chemin = voisin.chemin;
                return true;
            }
            //Si l'état du taquin est déjà un parent on ne l'ajoute pas
            if (parents.find(voisin.etat) != parents.end())
                continue;

            q.push(voisin);
        }
    }

    return false;
}


int main() {
    string source, chemin;
    bool entreeValide;

    do {
        cout << "Etat du taquin : ";
        getline(cin, source);
        //On enlève les eventuelles espaces
        source.erase(remove_if(source.begin(), source.end(), ::isspace), source.end());
        entreeValide = (source.length() == 9 ? true : false);
        if(!entreeValide) {
            cin.clear();
            cout << "Entree invalide. La chaine doit contenir au minimum 9 caracteres " << endl;
        }
    } while (!entreeValide);    


    if (BFS(source, chemin)) {
        cout << "Le chemin suivant a ete trouve : ";
        for (char c : chemin)
            cout << c << " ";
    } else {
        cout << "Aucun chemin n'a ete trouve" << endl;
    }

    return EXIT_SUCCESS;
}

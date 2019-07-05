/*
 -----------------------------------------------------------------------------------
 Laboratoire : <nn>
 Fichier     : Graphe.cpp
 Auteur(s)   : Robin Müller
 Date        : 17.06.2019

 But         : <à compléter>

 Remarque(s) : <à compléter>

 Compilateur : MinGW-g++ 6.3.0
 -----------------------------------------------------------------------------------
 */
#ifndef ASD1_LABO10_TEST_GRAPHE_H
#define ASD1_LABO10_TEST_GRAPHE_H
#include <cstdlib>
#include <cstdint>
#include <queue>
#include <iostream>
#include <map>
#include <array>

#include "Sommet.h"

const size_t N = 4;
using namespace std;
class Graphe {
private:
    using Sommet2 = Sommet<N>;

    const uint8_t VIDE = 0;
    std::array<uint8_t, N*N> source;
    std::array<uint8_t, N*N> cible;

    //calculation of manhattan distance heuristic
    int manhattan (Sommet2 s) {
        int acc = 0;
        for (int i=0; i<16; i++) {
            if (s.etat[i] != VIDE) {
                int index = cible[s.etat[i]];
                int xf = index/4;
                int yf = index%4;
                int xa = i/4;
                int ya = i%4;
                acc+= abs(xf-xa) + abs(yf-ya);
            }
        }
        return acc;
    }

    struct f{
        bool operator()(const pair<int,Sommet2>& a, pair<int,Sommet2>& b){
            return a.first>b.first;
        }
    };
public:
    Graphe(const std::array<uint8_t, N*N>& s, const std::array<uint8_t, N*N>& c) : source(s), cible(c) {

    }

    bool greedy_Manhattan(){
        //initialize nodes start and end
//        Sommet2(const std::array<T, N*N>& e, const std::string& c, size_t p)
        Sommet2 start(source, "", 0);
        Sommet2 end(cible, "", 0);

        std::priority_queue<std::pair<int, Sommet2>, vector<pair<int, Sommet2>>, f> pq;
        map<string,int> setx;

        pq.push (make_pair(0,start));
        int flag;
        while (!pq.empty()) {
            flag = 0;
            Sommet2 current_node = pq.top().second;
            pq.pop();
            //check if current node was already visited
            if(setx.find(current_node.toString())==setx.end())
                setx.insert(make_pair(current_node.toString(),current_node.profondeur));
            //if was visited but is a better solution
            if(setx[current_node.toString()]>=current_node.profondeur){
                setx[current_node.toString()]=current_node.profondeur;
            }
                //if was already visited and its not optimal node
            else{
                flag=1;
            }
            //check if found objective
            if(current_node.etat == cible) {
                for (int i = 0; i < current_node.chemin.size(); i += 2)
                    cout << current_node.chemin.substr(i, 2) << " ";
                cout << endl;
                printf("Depth: %zu\n",current_node.profondeur);
                return true;
            }
            if(!flag){
                vector<Sommet2> dsc = current_node.findChildren();
                for (int i=0; i<(int)dsc.size();i++) {
                    pq.push(make_pair(manhattan(dsc[i]) * 1.1 + dsc[i].profondeur, dsc[i]));
                }
            }
        }
        return false;
    }
};


#endif //ASD1_LABO10_TEST_GRAPHE_H

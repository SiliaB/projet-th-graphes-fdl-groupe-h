//
// Created by morga on 20/04/2020.
//

#ifndef PROJET2_GRAPHE_H
#define PROJET2_GRAPHE_H


#include <iostream>
#include <vector>
#include <string>
#include "Sommet.h"
#include "Arete.h"
#include <list>

class Graphe {
private:
    bool m_estOriente;
    std::vector<Sommet*> m_sommets;
    std::vector<Arete*> m_aretes;
    std::vector <int> predecesseurs;
public:
    Graphe(std::string cheminFichierGraphe);
    ~Graphe();
    void afficher() const;
    std::vector<int> BFS(int numero_s0) ;
    std::vector<int> DFS(int numero_s0) ;
    void TrierCroissant (std::vector <int> &tableau);
    int tempsDeTrajet(std::vector <Arete*> parcours);
   void applicationTrajet (int depart, int arrivee);



};


#endif //PROJET2_GRAPHE_H
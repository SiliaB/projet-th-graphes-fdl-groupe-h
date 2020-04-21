#include "Graphe.h"
#include "Arete.h"
#include <fstream>
#include <queue>
#include <list>
#include <stack>
#include <algorithm>


Graphe::Graphe(std::string cheminFichierGraphe) {
    std::ifstream ifs{cheminFichierGraphe};
    if(!ifs) {
        throw std::runtime_error("Impossible d'ouvrir " + cheminFichierGraphe);
    }
    ifs >> m_estOriente;
    if(ifs.fail()) {
        throw std::runtime_error("Problème de lecture de l'orientation du graphe.");
    }
    int ordre;
    ifs >> ordre;
    if(ifs.fail()) {
        throw std::runtime_error("Problème de lecture de l'ordre du graphe.");
    }
    int taille;
    ifs >> taille;
    if(ifs.fail()) {
        throw std::runtime_error("Problème de lecture de la taille du graphe.");
    }
    int num,capacite;
    for (int i;i<ordre;i++)
    {
        ifs >> num >> capacite;
        m_sommets.push_back(new Sommet(num,capacite));
    }

    int num1, num2, poids, temps;
    for(int i=0; i<taille; ++i) {
        ifs >> num1 >> num2 >> poids >> temps;
        m_aretes.push_back(new Arete(num1, num2, poids,temps));


    }
        if (ifs.fail()) {
            throw std::runtime_error("Problème de lecture d'un.e arc/arête.");
        }


        m_sommets[num1]->addSuccesseur(m_sommets[num2]);
        if (!m_estOriente && num1 < num2) {
            m_sommets[num2]->addSuccesseur(m_sommets[num1]);
        }
    }



Graphe::~Graphe() {
    for(auto addrSommet : m_sommets) {
        delete addrSommet;
    }
    for(auto addrArete : m_aretes) {
        delete addrArete;
    }
}

void Graphe::afficher() const {
    std::cout << std::endl << "Graphe ";
    std::cout << (m_estOriente ? "orienté" : "non orienté") << std::endl;
    std::cout << "Ordre : " << m_sommets.size() << std::endl;
    std::cout << "Liste d'adjacences : " << std::endl;
    for(auto addrSommet : m_sommets) {
        addrSommet->afficher();
        std::cout << std::endl;
    }
    std::cout << "Liste sommet :"<< std::endl;
    for (const auto& pz: m_sommets)
    {
        std::cout << pz->getNumero()<< ", capacite : "<<pz->getCapacite() << std::endl;
    }
    std::cout << "Liste des aretes :" <<std::endl;
    for (const auto& pz: m_aretes)
    {
        std::cout  << pz->getDepart() <<"---"<< pz->getArrive()<<", poids : "<<pz->getPoids() <<", temps de trajet : "<<pz->getTemps()<< std::endl;
    }


}

// Algo parcoursBFS(s0)
std::vector<int> Graphe::BFS(int numero_s0)  {
    // 1. Tous les sommets sont blancs (non découverts)
    std::vector<int> couleurs((int) m_sommets.size(), 0);
    // 2. Créer une file vide
    std::queue<const Sommet*> file;
    std::vector<int> predecesseurs((int) m_sommets.size(), -1);
    // 3. Enfiler s0 ; s0 devient gris
    file.push(m_sommets[numero_s0]);
    couleurs[numero_s0] = 1; // 0 = blanc, 1 = gris, 2 = noir
    const Sommet* s;
    // 4. Tant que la file n’est pas vide :
    while(!file.empty()) {
        // 4.1 Défiler le prochain sommet s de la file (Traitement éventuel sur s)
        s = file.front();
        file.pop();
        // 4.2 Pour chaque successeur s’ blanc (non découvert) de s :
        for(auto succ : s->getSuccesseurs()) {
            if(couleurs[succ->getNumero()] == 0) { // blanc
                // 4.2.1 Enfiler s’; s’ devient gris
                file.push(succ);
                couleurs[succ->getNumero()] = 1; // gris
                // 4.2.2 Noter que s est le prédécesseur de s’
                predecesseurs[succ->getNumero()] = s->getNumero();
            }
        }
        // 4.3 s devient noir (exploré)
        couleurs[s->getNumero()] = 2;
    }
    return predecesseurs;
}


// Algo parcoursDFS(s0)


// Algo parcoursDFS(s0)
std::vector<int> Graphe::DFS(int numero_s0) {
    // 1. Tous les sommets sont blancs (non découverts)
    std::vector<int> couleurs((int) m_sommets.size(), 0);
    // 2. Créer une file vide
    std::stack<const Sommet*> pile;
    std::vector<int> predecesseurs((int) m_sommets.size(), -1);
    // 3. Enfiler s0 ; s0 devient gris
    pile.push(m_sommets[numero_s0]);
    couleurs[numero_s0] = 1; // 0 = blanc, 1 = gris, 2 = noir
    const Sommet* s;
    // 4. Tant que la pile n’est pas vide :
    while(!pile.empty()) {
        // 4.1 Défiler le prochain sommet s de la pile (Traitement éventuel sur s)
        s = pile.top();
        pile.pop();
        // 4.2 Pour chaque successeur s’ blanc (non découvert) de s :
        for(auto succ : s->getSuccesseurs()) {
            if(couleurs[succ->getNumero()] == 0) { // blanc
                // 4.2.1 Enfiler s’; s’ devient gris
                pile.push(succ);
                couleurs[succ->getNumero()] = 1; // gris
                // 4.2.2 Noter que s est le prédécesseur de s’
                predecesseurs[succ->getNumero()] = s->getNumero();
            }
        }
        // 4.3 s devient noir (exploré)
        couleurs[s->getNumero()] = 2;
    }
    return predecesseurs;
}
void Graphe::TrierCroissant (std::vector <int> &tableau)
{
    for(int i; i<tableau.size();i++)
    {
        if (tableau[i]>tableau[i+1])
        {
            int a =tableau[i];
            tableau[i]=tableau[i+1];
            tableau[i+1]=a;

        }
    }
}

int Graphe:: tempsDeTrajet(std::vector <Arete*> parcours)
{
    int tempstotal;
    for(const auto& pz: parcours)
    {
        tempstotal+=pz->getTemps();
    }
    return tempstotal;
}

void Graphe:: applicationTrajet (int depart, int arrivee)
{
    std::cout<<"Veuillez saisir votre point de depart."<< std::endl;
    std::cin>> depart;
    std::cout <<"Veuillez saisir votre destination."<<std::endl;
    std::cin>> arrivee;
    while (!m_sommets[arrivee]) {
        // 1. Tous les sommets sont blancs (non découverts)
        std::vector<int> couleurs((int) m_sommets.size(), 0);
        // 2. Créer une file vide
        std::queue<const Sommet *> file;
        std::vector<int> predecesseurs((int) m_sommets.size(), -1);
        // 3. Enfiler s0 ; s0 devient gris
        file.push(m_sommets[depart]);
        couleurs[depart] = 1; // 0 = blanc, 1 = gris, 2 = noir
        const Sommet *s;
        // 4. Tant que la file n’est pas vide :
        while (!file.empty()) {
            // 4.1 Défiler le prochain sommet s de la file (Traitement éventuel sur s)
            s = file.front();
            file.pop();
            // 4.2 Pour chaque successeur s’ blanc (non découvert) de s :
            for (auto succ : s->getSuccesseurs()) {
                if (couleurs[succ->getNumero()] == 0) { // blanc
                    // 4.2.1 Enfiler s’; s’ devient gris
                    file.push(succ);
                    couleurs[succ->getNumero()] = 1; // gris
                    // 4.2.2 Noter que s est le prédécesseur de s’
                    predecesseurs[succ->getNumero()] = s->getNumero();
                }
            }
            // 4.3 s devient noir (exploré)
            couleurs[s->getNumero()] = 2;
        }
    }



}
/*
void Graphe::fonctionConnexe() {

    std::cout << "composante connexe :"<< " "<< m_sommets[0]->getNumero();
    //while (ComposanteConnexe.size() != m_sommets.size()) {
    std::vector <int> ComposanteConnexe;
    std::vector<int> couleurs((int) m_sommets.size(), 0);
    std::stack<const Sommet *> pile;
    std::vector<int> predecesseurs((int) m_sommets.size(), -1);
    pile.push(m_sommets[0]);
    couleurs[m_sommets[0]->getNumero()] = 1; // 0 = blanc, 1 = gris, 2 = noir
    const Sommet *s;
    while (!pile.empty()) {
        s = pile.top();
        pile.pop();
        for (auto succ : s->getSuccesseurs()) {
            if (couleurs[succ->getNumero()] == 0) {
                pile.push(succ);
                ComposanteConnexe.push_back(succ->getNumero());
                couleurs[succ->getNumero()] = 1;
                TrierCroissant(ComposanteConnexe);
                for(const auto& pz: ComposanteConnexe)
                {
                    std::cout << "  "<< pz->getNumero() << "  " ;
                }




            }

        }
    }
    // }
}


int Graphe:: trouver(int x)
{
    while (predecesseurs[x] != x)
        x = predecesseurs[x];
    return x;
}
void Graphe ::unir (int x, int y){
    int px=trouver(x);
    int py= trouver(y);
    predecesseurs[px] = py;
}
void Graphe:: Kruskal (){
    int mst_weigth =0;
    int mst_arete=0;
    int mst_ni=0;
    for (int i;i<20;i++)
    {
        predecesseurs.push_back(i);
    }
    std::sort(m_aretes.begin(),m_aretes.end());
    while ((mst_arete < m_sommets.size()-1)||(mst_ni < m_aretes.size())){

        //int depart = m_aretes[mst_ni].second.first;
       // int arrive = m_aretes[mst_ni].second.second;
        //int poids= m_aretes [mst_ni].first;

        //if(trouver(depart) != trouver(arrive)) {
          //  unir (depart,arrive);
            //mst_weigth += poids;
            //std::cout<<depart<<" "<<arrive<<" "<<poids<< std::endl;
            mst_arete ++;

        }

        mst_ni ++;

    }
    std::cout<<" le poids de la MST est " << mst_weigth<< std::endl;
}
*/
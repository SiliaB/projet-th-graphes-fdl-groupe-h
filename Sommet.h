#ifndef TP2_TG_SOMMET_H
#define TP2_TG_SOMMET_H

#include <iostream>
#include <vector>


class Sommet {
private:
    int m_numero;
    int capacite;
    std::vector<const Sommet*> m_successeurs;
    std::string nom;

public:
    Sommet(int num,int capacite);
    Sommet(int num);
    int getNumero() const;
    std::string getNom() const;
    int getCapacite() const;
    int setNumero(int newNumero);
    void addSuccesseur(const Sommet* succ);
    const std::vector<const Sommet*>& getSuccesseurs() const;
    void afficher() const;
};


#endif //TP2_TG_SOMMET_H
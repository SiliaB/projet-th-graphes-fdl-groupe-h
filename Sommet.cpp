#include "Sommet.h"

Sommet::Sommet(int num,int capacite) : m_numero{num},capacite{capacite} {}
Sommet::Sommet(int num) : m_numero{num},capacite{capacite},nom{nom} {}

void Sommet::addSuccesseur(const Sommet* succ) {
    m_successeurs.push_back(succ);
}

const std::vector<const Sommet*>& Sommet::getSuccesseurs() const {
    return m_successeurs;
}

int Sommet::getNumero() const {
    return m_numero;
}
std::string Sommet::getNom() const {
    return nom;
}
int Sommet::getCapacite() const {
    return capacite;
}

int Sommet::setNumero(int newNumero) {
    return m_numero=newNumero;
}

void Sommet::afficher() const {
    std::cout << "   Sommet " << m_numero << " : ";
    for(auto addrSommet : m_successeurs) {
        std::cout << addrSommet->getNumero() << " ";
    }
}
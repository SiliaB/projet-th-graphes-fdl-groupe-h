//
// Created by morga on 20/04/2020.
//
#include "Arete.h"

Arete::Arete(int depart, int arrive, int poids, int temps): depart{depart},arrive{arrive},m_poids{poids},temps{temps}{};

int Arete:: getDepart() const {return depart;};
int Arete::getArrive() const {return arrive;};
int Arete::getPoids() const {return m_poids;};
int Arete::getTemps() const {return temps;};
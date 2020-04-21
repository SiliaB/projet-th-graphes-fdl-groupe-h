//
// Created by morga on 20/04/2020.
//

#ifndef PROJET2_ARETE_H
#define PROJET2_ARETE_H

class Arete {

private :
    int m_poids;
    int depart;
    int arrive;
    int temps;
public:
    Arete (int depart, int arrive, int poids, int temps);
    int getDepart() const;
    int getArrive() const;
    int getPoids() const;
    int getTemps() const ;

};

#endif //PROJET2_ARETE_H
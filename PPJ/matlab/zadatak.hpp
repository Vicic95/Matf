#ifndef ZADATAK_HPP
#define ZADATAK_HPP

#include <iostream>
#include <vector>

class Matrica{
private:
    std::vector<std::vector<int>> m_matrica;
public:
    Matrica();
    Matrica(std::vector<std::vector<int>> m);
    void stampaj();
    void dodaj_vrstu(std::vector<int>& vektor);
    void velicina();
    
    std::vector<std::vector<int>> getMatrica();
    friend Matrica* sabiranje(const Matrica& m1,const Matrica& m2);
    friend Matrica* mnozenje(const Matrica& m1,const Matrica& m2);

};

#endif

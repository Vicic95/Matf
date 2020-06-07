#ifndef POLINOM_HPP
#define POLINOM_HPP

#include <vector>
#include <iostream>
#include <cmath>

class Polinom{

private:
    std::vector<float> koeficijenti;
    
public:
    Polinom(){}
    
    Polinom(std::vector<float> koef);
    
    void dodaj(float c);
    void ispisi();
    
    const std::vector<float>& getKoef();
    int stepen() const;
    friend Polinom* saberi(const Polinom& p1,const Polinom& p2);
    friend Polinom* oduzmi(const Polinom& p1,const Polinom& p2);
    friend Polinom* pomnozi(const Polinom& p1,const Polinom& p2);
    friend Polinom* uminus(const Polinom& p1);
    
    bool jednak(const Polinom& p1);
    
    void izvod();
    void integral(float c);

    float vrednost(float c);
};
#endif

#ifndef ZADATAK_HPP
#define ZADATAK_HPP

#include <iostream>
#include <set>

class Kutija{
private:
    std::set<double> m_kutija;
    std::set<double> m_kutija_2;
    bool m_ima_podskup;
    bool m_ima_podskup2;
    unsigned m_zapremina;
    
public:

    Kutija();
    Kutija(double c);
    Kutija(int c);
    void stampaj();
    void dodaj(int c);
    void dodaj(double c);
    bool puna();
    bool prazna();
    void zapremina(int c);
    void dodaj_skup(const Kutija& k1);
    friend Kutija* razlika(const Kutija& k1,const Kutija& k2);
};

#endif

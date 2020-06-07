#ifndef ZADATAK_HPP
#define ZADATAK_HPP

#include <iostream>
#include <set>
#include <algorithm>

class Skup{
    private:
        std::set<int> m_set;
        
    public:
        Skup();
        Skup(int pocetak, int kraj);
        Skup(std::set<int>& s);
        
        void dodaj(int c);
        
        void stampaj();

        friend Skup* unija(const Skup& s1,const Skup& s2);
        friend Skup* presek(const Skup& s1,const Skup& s2);
        friend Skup* razlika(const Skup& s1,const Skup& s2);
        
        bool sadrzi(int broj);
        bool podskup(const Skup& s1);

        int velicina();
};

#endif

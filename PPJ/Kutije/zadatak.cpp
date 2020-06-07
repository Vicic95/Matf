#include "zadatak.hpp"

Kutija::Kutija(){
    
}
Kutija::Kutija(double c){
    m_kutija.insert(c);
}
Kutija::Kutija(int c){
    m_kutija.insert(c);
}
void Kutija::stampaj() {
    std::cout << "[ ";
    for(std::set<double>::iterator i = m_kutija.begin();i!=m_kutija.cend();i++){
        std::cout << *i << " ";
    }
    std::cout << "]" << std::endl;
    
}

void Kutija::dodaj(int c){
    if(puna())
        std::cout << " Kutija je puna " << std::endl;
    else
        m_kutija.insert(c);
}
void Kutija::dodaj(double c){
    if(puna())
        std::cout << " Kutija je puna " << std::endl;
    else{
        m_kutija.insert(c);
    }
}
bool Kutija::puna(){
    if(m_zapremina == m_kutija.size())
        return true;
    else if((m_kutija.size() == (m_zapremina - 1)) && m_ima_podskup)
        return true;
    else
        return false;
}
bool Kutija::prazna(){
    if(m_kutija.size() == 0)
        return true;
    else
        return false;
}
void Kutija::zapremina(int c){
    m_zapremina = c;
}
void Kutija::dodaj_skup(const Kutija& k1) {
    if(m_ima_podskup){
        std::cerr << "Vec ima podskup" << std::endl;
        exit(EXIT_FAILURE);
    }
    if(m_zapremina <= k1.m_zapremina)
        std::cerr << "Kutija mora biti strogo manje zapremine od one u koju se ubacuje" << std::endl;
		exit(EXIT_FAILURE);
        
    m_ima_podskup = true;
	m_kutija_2 = k1.m_kutija;
}

Kutija* razlika(const Kutija& k1,const Kutija& k2) {
    k1.m_ima_podskup = false;
    k1.m_kutija_2.clear();

    return k1;
}

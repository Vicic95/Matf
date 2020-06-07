#include "zadatak.hpp"

Skup::Skup() {
}
Skup::Skup(int pocetak,int kraj) {

    for(int i = pocetak; i<=kraj; i++){
        m_set.insert(i);
    }
}
Skup::Skup(std::set<int>& s): m_set(s) {
}
void Skup::dodaj(int c) {
    m_set.insert(c);
}

void Skup::stampaj() {
    std::cout << "{";
    for(std::set<int>::iterator i = m_set.begin(); i != m_set.cend(); i++) {
        if(i!= m_set.cbegin())
            std::cout << ",";
    
        std::cout << *i;
    }
    std::cout << "}" << std::endl;
    
}
Skup* unija(const Skup& s1,const Skup& s2) {
    std::set<int> rezultat;
    std::set_union(s1.m_set.cbegin(),s1.m_set.cend(),
                          s2.m_set.cbegin(),s2.m_set.cend(),
                          std::inserter(rezultat,rezultat.begin()));
    return new Skup(rezultat);
}
Skup* presek(const Skup& s1,const Skup& s2) {
    std::set<int> rezultat;
    std::set_intersection(s1.m_set.cbegin(),s1.m_set.cend(),
                          s2.m_set.cbegin(),s2.m_set.cend(),
                          std::inserter(rezultat,rezultat.begin()));
    return new Skup(rezultat);
}
Skup* razlika(const Skup& s1,const Skup& s2) {
    std::set<int> rezultat;
    std::set_difference(s1.m_set.cbegin(),s1.m_set.cend(),
                          s2.m_set.cbegin(),s2.m_set.cend(),
                          std::inserter(rezultat,rezultat.begin()));
    return new Skup(rezultat);
}
bool Skup::sadrzi(int broj){
    auto it = m_set.find(broj);
    if(it != m_set.end())
        return true;
    return false;
}
bool Skup::podskup(const Skup& s1) {
   	for(const auto& e: m_set){
        auto it = s1.m_set.find(e);
        if(it == s1.m_set.end())
            return false;
	}
	
	return true;

}
int Skup::velicina() {
    return m_set.size();
}

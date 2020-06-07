#include "zadatak.hpp"

Matrica::Matrica() {
}

Matrica::Matrica(std::vector<std::vector<int>> m){
	m_matrica = m;
}

void Matrica::stampaj(){
    if(m_matrica.size() == 1){
        std::cout << m_matrica[0].size();
        std::cout << "[";
        for(unsigned i=0; i<m_matrica[0].size(); i++){
            std::cout<<m_matrica[0][i];
            if(i!=(m_matrica[0].size()-1))
                std::cout << ",";
        }
        std::cout << "]" << std::endl;
    }
    else{
        std::cout << "[";
        for(unsigned i=0; i<m_matrica.size();i++){
            std::cout << "[";
            for(unsigned j=0;j<m_matrica[i].size();j++){
                std::cout << m_matrica[i][j];
                if(j!=(m_matrica[i].size()-1))
                    std::cout << ",";
            }
                std::cout << "]";
                if(i!=(m_matrica.size()-1))
                    std::cout << ",";
        }
        std::cout << "]" <<std::endl;
    
    }
}

void Matrica::dodaj_vrstu(std::vector<int>& vektor){
        m_matrica.push_back(vektor);
}
void Matrica::velicina(){
    std::cout<<  m_matrica.size() << "x" << m_matrica[0].size() << std::endl;
}
std::vector<std::vector<int>> Matrica::getMatrica(){
    return m_matrica;
    
}
Matrica* sabiranje(const Matrica& m1, const Matrica& m2){
   std::vector<std::vector<int>> nova;
    for (unsigned i=0; i<m1.m_matrica.size(); i++){
    
        std::vector<int> vrsta;
		for (unsigned j=0; j<m1.m_matrica[i].size(); j++){
			vrsta.push_back(m1.m_matrica[i][j] + m2.m_matrica[i][j]);
		}
		nova.push_back(vrsta);
	}
	Matrica* rezultat = new Matrica(nova);
	return rezultat;
}

Matrica* mnozenje(const Matrica& m1, const Matrica& m2){
    std::vector<std::vector<int>> nova;
    for (unsigned i=0; i<m1.m_matrica.size(); i++){
    
        std::vector<int> vrsta;
		for (unsigned j=0; j<m1.m_matrica[i].size(); j++){
			vrsta.push_back(m1.m_matrica[i][j] * m2.m_matrica[i][j]);
		}
		nova.push_back(vrsta);
	}
	Matrica* rezultat = new Matrica(nova);
	return rezultat;

}

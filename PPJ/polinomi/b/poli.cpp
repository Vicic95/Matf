#include "poli.hpp"

Polinom::Polinom(std::vector<float> koef){
    koeficijenti = koef;
}
    
void Polinom::dodaj(float c){
    koeficijenti.push_back(c);
}
void Polinom::ispisi(){
    for(unsigned i=0; i<koeficijenti.size(); i++){
        if(koeficijenti[i] == 0)
            continue;
        if(i!=0 && koeficijenti[i] > 0){
            std::cout << '+';
        }
        if(koeficijenti[i] != 1 || koeficijenti[i] != -1)
            std::cout << koeficijenti[i];
        if(i>0)
            std::cout << 'x';
        if(i>1)
            std::cout << '^' << i;
    }
    if(koeficijenti.size() == 1 && koeficijenti[0] == 0)
        std::cout << 0;
    
    std::cout << std::endl;
}
const std::vector<float>& Polinom::getKoef(){
    return koeficijenti;
}
int Polinom::stepen() const {
    return koeficijenti.size();
}
Polinom* saberi(const Polinom& p1,const Polinom& p2){
    int stepen = std::max(p1.stepen(),p2.stepen());
    std::vector<float> r_koeficijenti(stepen);
    
    for(int i = 0; i<stepen; i++){
        if(i>p1.stepen()){
            r_koeficijenti[i]=0;
        }
        else
            r_koeficijenti[i] = p1.koeficijenti[i];
        if(i<p2.stepen())
            r_koeficijenti[i] += p2.koeficijenti[i];
    }
    Polinom* rezultat = new Polinom(r_koeficijenti);
    
    return rezultat;
}
Polinom* oduzmi(const Polinom& p1,const Polinom& p2){
    int stepen = std::max(p1.stepen(),p2.stepen());
    std::vector<float> r_koeficijenti(stepen);
    
    for(int i = 0; i<stepen; i++){
        if(i>p1.stepen()){
            r_koeficijenti[i]=0;
        }
        else
            r_koeficijenti[i] = p1.koeficijenti[i];
        if(i<p2.stepen())
            r_koeficijenti[i] -= p2.koeficijenti[i];
    }
    Polinom* rezultat = new Polinom(r_koeficijenti);
    return rezultat;
}
Polinom* pomnozi(const Polinom& p1,const Polinom& p2){
    int stepen = std::max(p1.stepen(),p2.stepen());
    std::vector<float> r_koeficijenti(stepen);
    
    for(int i = 0; i<stepen; i++){
        if(i>p1.stepen()){
            r_koeficijenti[i]=0;
        }
        else
            r_koeficijenti[i] = p1.koeficijenti[i];
        if(i<p2.stepen())
            r_koeficijenti[i] *= p2.koeficijenti[i];
    }
    Polinom* rezultat = new Polinom(r_koeficijenti);
    return rezultat;
}
Polinom* uminus(const Polinom& p1){
    std::vector<float> r_koeficijenti(p1.stepen());
    
    for(int i = 0; i<p1.stepen(); i++){
        r_koeficijenti[i] = (-1)*p1.koeficijenti[i];
    }
    Polinom* rezultat = new Polinom(r_koeficijenti);
    return rezultat;
    
}
    

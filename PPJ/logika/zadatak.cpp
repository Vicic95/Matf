#include "zadatak.hpp"

Formula::Formula() {
}
Formula::Formula(Logic v) {
    m_formula = v;
}
Logic Formula::and_f(const Formula& f) const {
    if(m_formula==true_v && f.m_formula==true_v)
        return true_v;
    else if(m_formula==false_v || f.m_formula==false_v)
        return false_v;
    else
        return undef_v;
}
Logic Formula::or_f(const Formula& f) const {
    if(m_formula == true_v || f.m_formula == true_v)
        return true_v;
    else if(m_formula == false_v && f.m_formula == false_v)    
        return false_v;
    else
        return undef_v;
}
Logic Formula::impl(const Formula& f) const {
    if(m_formula == false_v && f.m_formula == true_v)
        return true_v;
    else if(m_formula == true_v && f.m_formula == true_v)
        return true_v;
    else if(m_formula == false_v && f.m_formula == false_v)
        return true_v;
    else if(m_formula == true_v && f.m_formula == false_v)
        return false_v;
    else
        return undef_v;
}
Logic Formula::ekv(const Formula& f) const {
    if(m_formula == true_v && f.m_formula == true_v)
        return true_v;
    else if(m_formula == false_v && f.m_formula == false_v)
        return true_v;
    else if(m_formula == true_v && f.m_formula == false_v)
        return false_v;
    else if(m_formula == false_v && f.m_formula == true_v)
        return false_v;
    else
        return undef_v;
}
Logic Formula::negacija() const {
    if(m_formula == true_v)
        return false_v;
    else if(m_formula == false_v)
        return true_v;
    else
        return undef_v;
}
std::string Formula::str() {
    if(m_formula == true_v)
        return "True";
    else if(m_formula == false_v)
        return "False";
    else
        return "Undef";
}
Logic Formula::val() {
    return m_formula;
}
    

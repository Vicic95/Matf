#ifndef FORUMLA_HPP
#define FORMULA_HPP

#include <iostream>
#define Logic int
#define true_v (1)
#define false_v (0)
#define undef_v (-1)

class Formula{
    private:
        Logic m_formula;
        
    public:
        Formula();
        Formula(Logic v);
        Logic and_f(const Formula& f) const;
        Logic or_f(const Formula& f) const;
        Logic impl(const Formula& f) const;
        Logic ekv(const Formula& f) const;
        Logic negacija() const;
        std::string str();
        Logic val();
    
};

#endif

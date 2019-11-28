#include "expressionUnaire.hh"

ExpressionUnaire::ExpressionUnaire(ExpressionPtr exp, OperateurUnaire op):
    _exp(exp), _op(op) {

}

double ExpressionUnaire::calculer(const Contexte& contexte) const {
    double exp = _exp->calculer(contexte);
    switch (_op) {
        case OperateurUnaire::neg: return -exp;
        default: return 0;
    }
}
#include "expressionUnaire.hh"

ExpressionUnaire::ExpressionUnaire(ExpressionPtr exp, OperateurUnaire op):
    _exp(exp), _op(op) {

}

int ExpressionUnaire::calculer(const Contexte& contexte) const {
    int exp = _exp->calculer(contexte);
    switch (_op) {
        case OperateurUnaire::neg: return -exp;
        default: return 0;
    }
}
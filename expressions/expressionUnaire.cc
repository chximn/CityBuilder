#include "expressionUnaire.hh"

ExpressionUnaire::ExpressionUnaire(ExpressionPtr exp, OperateurUnaire op):
    _exp(exp), _op(op) {

}

int ExpressionUnaire::calculer(const Contexte& contexte) const {
    int exp = _exp->calculer(contexte);
    switch (_op) {
        case OperateurUnaire::neg: return -exp;
        case OperateurUnaire::non: return !exp;
        default: return 0;
    }
}

int ExpressionOccupied::calculer(const Contexte& contexte) const {
	if (_house->test(_city, contexte)) return 1;
	else return 0;
}

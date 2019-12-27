#include "expressionBinaire.hh"


ExpressionBinaire::ExpressionBinaire(ExpressionPtr gauche, ExpressionPtr droite, OperateurBinaire op):
    _gauche(gauche), _droite(droite), _op(op) {

}

int ExpressionBinaire::calculer(const Contexte& contexte) const {
    int gauche = _gauche->calculer(contexte), droite = _droite->calculer(contexte);
    switch (_op) {
        case OperateurBinaire::plus:      return gauche + droite;
        case OperateurBinaire::moins:     return gauche - droite;
        case OperateurBinaire::divise:    if (droite == 0) error::report("Division par zéro est interdite");
		                                  return gauche / droite;
        case OperateurBinaire::multiplie: return gauche * droite;
        case OperateurBinaire::equ:       return gauche == droite;
        case OperateurBinaire::inf:       return gauche < droite;
        case OperateurBinaire::sup:       return gauche > droite;
        case OperateurBinaire::inf_equ:   return gauche <= droite;
        case OperateurBinaire::sup_equ:   return gauche >= droite;
        case OperateurBinaire::et:        return gauche && droite;
        case OperateurBinaire::ou:        return gauche || droite;
        default: return 0;
    }
}

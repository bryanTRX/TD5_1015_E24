#pragma once

#include "Personnage.hpp"

class Vilain : public virtual Personnage
{
public:
    // Constructeurs -----------------------------------------------------------------------------------------------------

    Vilain(const string& nom, const string& jeu, const string& objectif) : Personnage(nom, jeu), objectif_(objectif) {}

    // Méthodes ----------------------------------------------------------------------------------------------------------

    const string& getObjectif() const { return objectif_; }

    void afficher(ostream& os, Couleur couleur) const override
    {
        Personnage::afficher(os, couleur);
        os << couleurToString(couleur) << "Objectif : " << objectif_ << "\033[0m" << endl;
    }

private:
    string objectif_;
};

ostream& operator<<(ostream& os, const Vilain& vilain)
{
    vilain.afficher(os, Couleur::Rouge);
    return os;
}
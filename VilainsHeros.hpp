#pragma once

#include "Vilains.hpp"
#include "Heros.hpp"

class VilainHeros : public Vilain, public Heros
{
public:
    // Constructeurs -----------------------------------------------------------------------------------------------------

    VilainHeros(const Vilain& vilain, const Heros& heros) 
        : Personnage(vilain.getNom() + " - " + heros.getNom(), vilain.getJeu() + " - " + heros.getJeu()), 
        Vilain(vilain), 
        Heros(heros), 
        mission_(vilain.getObjectif() + " dans le monde de " + heros.getJeu()) {}

    // Méthodes ----------------------------------------------------------------------------------------------------------

    const string& getMission() const { return mission_; }

    void afficher(ostream& os, Couleur couleur) const override 
    {
        Personnage::afficher(os, couleur);
        os << couleurToString(couleur) << "Objectif : " << Vilain::getObjectif() << endl;
        os << "Ennemi : " << Heros::getEnnemi() << "\nAlliés : " << endl;
        for (const auto& i : Heros::getAllies()) 
        {
            os << "\t" << i << endl;
        }
        os << "Mission spéciale : " << mission_ << "\033[0m" << endl;
    }

private:
    string mission_;
};

ostream& operator<<(ostream& os, const VilainHeros& vilainHero)
{
    vilainHero.afficher(os, Couleur::Mauve);
    return os;
}
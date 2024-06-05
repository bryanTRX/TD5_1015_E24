#pragma once
#include "Personnage.hpp"
#include <string>
#include <iostream>
using namespace std;

class Vilain : public virtual Personnage
{
public:
	// Vilain() = default;  // Non nécessaire.
	
	//Vilain(const string& nom, const string& jeu, const string& objectif)  // Non nécessaire si on construit toujour en lisant du istream.
	//	: Personnage(nom, jeu), objectif_(objectif) {}

	Vilain(istream& fichier) : Personnage(fichier), objectif_(lireString(fichier)) {}

	void afficher(ostream& os) const override {
		Personnage::afficher(os);
		afficherSpecificites(os);
	}
	void afficherSpecificites(ostream& os) const {  // Pourrait être protected.
		os << "Objectif : " << objectif_ << "\n";
	}
	void changerCouleur(ostream& os, int couleur) const override {
		Personnage::changerCouleur(os, couleur^2);
	}

	// Getter nécessaire pour la construction du VilainHero (puisque généralement les attributs sont private et non protected):
	const string& getObjectif() const { return objectif_; }

private:
	string objectif_;
};

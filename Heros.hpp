#pragma once
#include "Personnage.hpp"
#include "lireVectorDuFichier.hpp"
#include <iostream>
#include <string>
#include <vector>
#include "cppitertools/range.hpp"
using namespace std;
using namespace iter;

class Heros : public virtual Personnage
{
public:
	Heros() = default;  // Non nécessaire dans le TD4, pourrait servir dans le TD5.
		
	Heros(const string& nom, const string& jeu, const string& ennemi)  // Non nécessaire si on construit toujour en lisant du istream (TD4).
		: Personnage(nom, jeu), ennemi_(ennemi) {}
	
	Heros(istream& fichier) : Personnage(fichier), ennemi_(lireString(fichier)), allies_(lireVectorDuFichier<string>(fichier)) {}
	
	void afficher(ostream& os) const override {
		Personnage::afficher(os);
		afficherSpecificites(os);
	}
	void afficherSpecificites(ostream& os) const {  // Pourrait être protected.
		os << "Ennemi : " << ennemi_ << "\n";
		os << "Alliés :\n";
		for (auto&& allie : allies_)
			os << "\t" << allie << "\n";
	}
	void changerCouleur(ostream& os, int couleur) const override {
		Personnage::changerCouleur(os, couleur^1);  // Pas demandé directement dans l'énoncé, mais c'est bon d'avoir des couleurs différentes pour les différentes classes, tant qu'à avoir une méthode vituelle pour ça...
	}

	// Les getters sont non nécessaires:
	//const string& getEnnemi() const { return ennemi_; }
	//const vector<string>& getAllies() const { return allies_; }

private:
	string ennemi_;
	vector<string> allies_;
};

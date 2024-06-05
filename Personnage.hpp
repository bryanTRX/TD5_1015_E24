#pragma once
#include "Affichable.hpp"
#include "lectureBinaire.hpp"
#include <iostream>
#include <string>
using namespace std;

class Personnage : public Affichable
{
public:
	Personnage() = default;  // Non nécessaire dans le TD4, pourrait servir dans le TD5.

	Personnage(string nom, string jeu) : nom_(nom), parutionJeu_(jeu) {}  // Nécessaire pour la construction du VilainHero.
	
	Personnage(istream& fichier) : nom_(lireString(fichier)), parutionJeu_(lireString(fichier)) {}

	void afficher(ostream& os) const override {
		os << "Nom : " << nom_ << "\n";
		os << "Jeu de parution : " << parutionJeu_ << endl;
	}

	void changerCouleur(ostream& os, int couleur) const override {
		static const string rouge = "\033[91m";
		static const string vert  = "\033[92m";
		static const string jaune = "\033[93m";
		static const string bleu  = "\033[94m";
		static const string couleurStandard  = "\033[0m";

		switch (couleur) {
			case 0: os << jaune; break;
			case 1: os << vert; break;
			case 2: os << rouge; break;
			case 3: os << bleu; break;
			default: os << couleurStandard; break;
		}
	}

	// Les getters sont nécessaires pour la construction du VilainHero (puisque généralement les attributs sont private et non protected):
	const string& getNom() const { return nom_; }
	const string& getParutionJeu() const { return parutionJeu_; }

private:
	string nom_;
	string parutionJeu_;
};

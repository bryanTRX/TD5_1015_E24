#pragma once
#include <iostream>
using namespace std;

class Affichable
{
public:
	virtual ~Affichable() = default;  // Important!  Toute classe polymorphe doit avoir un destructeur virtuel, sinon la destruction par la classe de base est "undefined behavior".
	virtual void afficher(ostream&) const = 0;
	virtual void changerCouleur(ostream&, int laCouleur) const = 0;
};

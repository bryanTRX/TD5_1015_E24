#pragma once
#include "lectureBinaire.hpp"
#include <iostream>
#include <vector>
#include <string>
#include "cppitertools/range.hpp"
using namespace std;
using namespace iter;

template <typename T>
T lireObjetDuFichier(istream& fichier) { return T(fichier); }
// Spécialisation de template (vu en classe pour le cas de 'hash') pour type string.
template <>
string lireObjetDuFichier<string>(istream& fichier) { return lireString(fichier); }

template <typename T>
vector<T> lireVectorDuFichier(istream& fichier)
{
	vector<T> elements;
	for ([[maybe_unused]] size_t i : range(lireUintTailleVariable(fichier)))
		elements.push_back(lireObjetDuFichier<T>(fichier));  // Sans le problème de vouloir supporter aussi string ici, on aurait pu faire directement T(fichier) .
	return elements;
}

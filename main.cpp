﻿// Programme contenant le projet du TD5.
// file		main.cpp
// author	Iliass Khider et Bryan Alexandre Tavares
// date		4 mai 2024
// Créé le	10 mai 2024

#include "Heros.hpp"
#include "lireVectorDuFichier.hpp"
#include "lectureBinaire.hpp"
#include "ListeLiee.hpp"
#include <fstream>
#include <sstream>
#include <cassert>
#include <vector>
#include <functional>
#include <memory>
#include <set>
#include "cppitertools/range.hpp"
#include "bibliotheque_cours.hpp"

using namespace std;
using namespace iter;

ifstream ouvrirFichierBinaire(const string& nomFichier)
{
    ifstream fichier(nomFichier, ios::binary);
    fichier.exceptions(ios::failbit);
    return fichier;
}

void testsPourCouvertureLectureBinaire()
{
    istringstream iss("\xA0\x12\xA1\x21\x43\xA2\x98\xBA\xDC\xFE");
    assert(lireUintTailleVariable(iss) == 0x12);
    assert(lireUintTailleVariable(iss) == 0x4321);
    assert(lireUintTailleVariable(iss) == 0xFEDCBA98);
}

// Trait de separation
static const string trait = "\n═════════════════════════════════════════════════════════════════════════";

// Permet d'avoir une référence non-const à un objet temporaire.
template <typename T> T& temporaireModifiable(T&& objet) { return objet; }

template <typename T>
vector<T> lireVectorDuFichier(const string& nomFichier)
{
    return lireVectorDuFichier<T>(temporaireModifiable(ouvrirFichierBinaire(nomFichier)));
}

template <typename T>
typename ListeLiee<T>::iterator trouverParNom(ListeLiee<T>& liste, const string& nom)
{
    typename ListeLiee<T>::iterator fin = liste.end();
    for (typename ListeLiee<T>::iterator pos = liste.begin(); pos != fin; pos.avancer()) {
        if ((*pos).getNom() == nom)
            return pos;
    }
    return fin;
}

int main()
{
#pragma region "Bibliothèque du cours"
    // Permet sous Windows les "ANSI escape code" pour changer de couleur
    // https://en.wikipedia.org/wiki/ANSI_escape_code ; les consoles Linux/Mac
    // les supportent normalement par défaut.
    bibliotheque_cours::activerCouleursAnsi();
#pragma endregion

    testsPourCouvertureLectureBinaire();

    // ------------------------------------------------------------ Affichage de notre liste apres avoir tester notre iterator ------------------------------------------------------------

    const string traitHeros = "\n\033[32m══════════════════════════════ Modification de notre listeHeros ══════════════════════════════════\033[0m";
    cout << traitHeros << endl;

    // Transférez les héros du vecteur heros dans une ListeLiee.
    vector<Heros> heros = lireVectorDuFichier<Heros>("heros.bin");
    ListeLiee<Heros> listeHeros;
    for (auto& hero : heros)
    {
        listeHeros.push_back(hero);
    }

    // Créez un itérateur sur la liste liée à la position du héros Alucard.
    auto itAlucard = trouverParNom(listeHeros, "Alucard");

    // Servir de l'itérateur créé précédemment pour trouver l'héroine Aya Brea.
    auto itAyaBrea = itAlucard;
    for (; itAyaBrea != listeHeros.end(); itAyaBrea.avancer())
    {
        if ((*itAyaBrea).getNom() == "Aya Brea")
        {
            break;
        }
    }

    // Ajouter un hero bidon à la liste avant Aya Brea en vous servant de l'itérateur.
    Heros heroBidon("Guardian", "Destiny 2", "The Witness");
    listeHeros.insert(itAyaBrea, heroBidon);

    // Assurer que la taille de la liste est correcte après l'ajout.
    assert(listeHeros.size() == heros.size() + 1);

    // Reculez notre itérateur jusqu'au héros Mario et effacez-le en utilisant l'itérateur.
    auto itMario = trouverParNom(listeHeros, "Mario");
    for (; itMario != listeHeros.begin(); itMario.reculer())
    {
        if ((*itMario).getNom() == "Mario")
        {
            break;
        }
    }

    // Affichez le héros suivant dans la liste (devrait être "Naked Snake/John").
    auto itSuivantMario = itMario;
    itSuivantMario.avancer();
    listeHeros.erase(itMario);

    // Assurer que la taille de la liste est correcte après le retrait.
    assert(listeHeros.size() == heros.size());

    // Effacez le premier élément de la liste.
    listeHeros.erase(listeHeros.begin());

    // Afficher liste de héros en utilisant un itérateur.
    for (auto it = listeHeros.begin(); it != listeHeros.end(); it.avancer())
    {
        (*it).changerCouleur(cout, 2);
        (*it).afficher(cout);
        (*it).changerCouleur(cout, 4);
        cout << trait << endl;
    }

    // ------------------------------------------------------------ Affichage de notre liste utilisant la boucle for ------------------------------------------------------------

    const string traitFor = "\n\033[32m══════════════════════════════ Même affichage mais avec la boucle for ══════════════════════════════════\033[0m";
    cout << traitFor << endl;

    // Refaite le même affichage mais en utilisant une simple boucle "for" sur intervalle.
    for (const auto& h : listeHeros)
    {
        h.changerCouleur(cout, 2);
        h.afficher(cout);
        h.changerCouleur(cout, 4);
        cout << trait << endl;
    }

    // ------------------------------------------------------------ Affichage de notre liste en ordre alphabétique ------------------------------------------------------------

    const string traitAlphabetique = "\n\033[32m══════════════════════════════ Affichage des Héros en ordre alphabétique ══════════════════════════════════ ";
    cout << traitAlphabetique << endl;

    // Utilisez un conteneur pour avoir les héros en ordre alphabétique.
    set<Heros, function<bool(const Heros&, const Heros&)>> setHeros([](const Heros& a, const Heros& b) { return a.getNom() < b.getNom(); });

    for (const auto& h : listeHeros)
    {
        setHeros.insert(h);
    }

    // Afficher les héros triés par ordre alphabétique
    for (const auto& h : setHeros)
    {
        h.changerCouleur(cout, 2);
        h.afficher(cout);
        h.changerCouleur(cout, 4);
        cout << trait << endl;
    }
}

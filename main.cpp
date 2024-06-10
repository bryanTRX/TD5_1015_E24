// Programme contenant le projet du TD5.
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
#include <string>
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

    // ------------------------------------------------------------ Affichage de notre listeHeros apres avoir tester notre iterator ------------------------------------------------------------

    const string traitHeros = "\n\033[32m══════════════════════════════ Modification de notre listeHeros ══════════════════════════════════\033[0m";
    cout << traitHeros << endl;

    // Transfer des héros du vecteur heros dans une ListeLiee.
    vector<Heros> heros = lireVectorDuFichier<Heros>("heros.bin");
    ListeLiee<Heros> listeHeros;
    for (auto& hero : heros)
    {
        listeHeros.push_back(hero);
    }

    // Création d'un itérateur sur la liste liée à la position du héros Alucard.
    auto itAlucard = trouverParNom(listeHeros, "Alucard");

    // Utilisation de l'itérateur créé précédemment pour trouver l'héroine Aya Brea.
    auto itAyaBrea = itAlucard;
    for (; itAyaBrea != listeHeros.end(); itAyaBrea.avancer())
    {
        if ((*itAyaBrea).getNom() == "Aya Brea")
        {
            break;
        }
    }

    // Ajout d'un hero bidon à la liste avant Aya Brea en vous servant de l'itérateur.
    Heros heroBidon("Guardian", "Destiny 2", "The Witness");
    listeHeros.insert(itAyaBrea, heroBidon);

    //Verification que la taille de la liste est correcte après l'ajout.
    assert(listeHeros.size() == heros.size() + 1);

    // Recul de l'itérateur jusqu'au héros Mario et effacement de celui ci en utilisant l'itérateur.
    auto itMario = trouverParNom(listeHeros, "Mario");
    for (; itMario != listeHeros.begin(); itMario.reculer())
    {
        if ((*itMario).getNom() == "Mario")
        {
            break;
        }
    }

    // Affichage du héros suivant dans la liste (devrait être "Naked Snake/John").
    auto itSuivantMario = itMario;
    itSuivantMario.avancer();
    listeHeros.erase(itMario);

    // Verification que  la taille de la liste est correcte après le retrait.
    assert(listeHeros.size() == heros.size());

    // Effacement du premier élément de la liste.
    listeHeros.erase(listeHeros.begin());

    // Affichage de notre liste de héros en utilisant un itérateur.
    for (auto it = listeHeros.begin(); it != listeHeros.end(); it.avancer())
    {
        if ((*it).getNom() == "Naked Snake/John")
        {
            (*it).changerCouleur(cout, 3);  // Couleur différente pour Naked Snake/John
        }
            

        else
        {
            (*it).changerCouleur(cout, 2);
        }
            
        (*it).afficher(cout);
        (*it).changerCouleur(cout, 4);
        cout << trait << endl;
    }

    // ------------------------------------------------------------ Affichage de notre liste utilisant la boucle for ------------------------------------------------------------

    const string traitFor = "\n\033[32m══════════════════════════════ Même affichage mais avec la boucle for ══════════════════════════════════\033[0m";
    cout << traitFor << endl;

    // Refaire le même affichage mais en utilisant une simple boucle "for" sur intervalle.
    for (const auto& h : listeHeros)
    {
        if (h.getNom() == "Naked Snake/John")
        {
            h.changerCouleur(cout, 3);
        }
            
        else
        {
            h.changerCouleur(cout, 2);
        }
            
        h.afficher(cout);
        h.changerCouleur(cout, 4);
        cout << trait << endl;
    }

    // ------------------------------------------------------------ Affichage de notre liste en ordre alphabétique ------------------------------------------------------------

    const string traitAlphabetique = "\n\033[32m══════════════════════════════ Affichage des Héros en ordre alphabétique ══════════════════════════════════ ";
    cout << traitAlphabetique << endl;

    // Utilisation d'un conteneur pour avoir les héros en ordre alphabétique.
    set<Heros, function<bool(const Heros&, const Heros&)>> setHeros([](const Heros& a, const Heros& b) { return a.getNom() < b.getNom(); });

    for (const auto& h : listeHeros)
    {
        setHeros.insert(h);
    }

    // Affichage des héros triés par ordre alphabétique
    for (const auto& h : setHeros)
    {
        h.changerCouleur(cout, 2);
        h.afficher(cout);
        h.changerCouleur(cout, 4);
        cout << trait << endl;
    }

    // ------------------------------------------------------------ Affichage de notre liste en ordre alphabétique ------------------------------------------------------------

    const string traitDeRecherche = "\n\033[32m══════════════════════════════ Affichage d'un héros rechercher ══════════════════════════════════ ";
    cout << traitDeRecherche << endl;

    // 2.2 Affichage d'un des héros trouvé par son nom dans le set
    // Recherche d'un héros par nom dans le set
    auto itTrouve = setHeros.find(Heros("Alucard", "", ""));
    if (itTrouve != setHeros.end())
    {
        itTrouve->changerCouleur(cout, 2);
        itTrouve->afficher(cout);
        itTrouve->changerCouleur(cout, 4);
        cout << trait << endl;
    }

    // La complexité moyenne de cette recherche est O(log n) car std::set est généralement implémenté
    // comme un arbre binaire de recherche équilibré. 

    // 2.3 Explication de la recherche la plus rapide
    // Lors d’une recherche d’un héros par le nom, le conteneur set permet la recherche la plus rapide
    // comparé à la liste liée utilisée en 1. Ceci est dû au fait que la recherche dans un std::set a une
    // complexité moyenne de O(log n) grâce à sa structure d’arbre binaire de recherche équilibré, tandis que
    // la recherche dans une liste liée a une complexité moyenne de O(n) car il faut potentiellement parcourir
    // chaque élément de la liste.

    return 0;
}
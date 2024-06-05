#include "Personnage.hpp"
#include "Vilain.hpp"
#include "Heros.hpp"
#include "VilainHeros.hpp"
#include "lireVectorDuFichier.hpp"
#include "lectureBinaire.hpp"
#include "ListeLiee.hpp"
#include <fstream>
#include <sstream>
#include <cassert>
#include <vector>
#include <functional>
#include <memory>
#include "set"
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

// versReferenceAffichable permet d'avoir une référence à l'affichable, que le paramètre soit un unique_ptr ou une référence. 
// On aurait pu faire un template plus générique pour const/non const, et même utiliser un concept, mais ce n'est pas nécessaire pour que ça fonctionne.
// lireFichier aurait aussi pu retourner un vector de unique_ptr pour ne pas avoir besoin de versReferenceAffichable pour supporter à la fois les références et les unique_ptr.
const Affichable& versReferenceAffichable(const Affichable& p) { return p; }
template <typename T>
const Affichable& versReferenceAffichable(const unique_ptr<T>& p) { return *p; }

// Trait de separation
static const string trait = "\n═════════════════════════════════════════════════════════════════════════";

// On ne demande pas particulièrement la surcharge de << dans ce TD.
template <typename T>
void afficherAffichables(const vector<T>& affichables)
{
    static const string separateurElements = "\033[33m" + trait + "\033[0m\n";
    for (auto&& a : affichables) {
        cout << separateurElements;
        auto& x = versReferenceAffichable(a);
        x.changerCouleur(cout, 0);
        x.afficher(cout);
    }
}

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

    // Servez-vous de l'itérateur créé précédemment pour trouver l'héroine Aya Brea.
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

    // Assurez-vous que la taille de la liste est correcte après l'ajout.
    assert(listeHeros.size() == heros.size() + 1);

    // Reculez votre itérateur jusqu'au héros Mario et effacez-le en utilisant l'itérateur.
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

    // Assurez-vous que la taille de la liste est correcte après le retrait.
    assert(listeHeros.size() == heros.size());

    // Effacez le premier élément de la liste.
    listeHeros.erase(listeHeros.begin());

    // Affichez votre liste de héros en utilisant un itérateur.
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
    for (const auto& hero : listeHeros) 
    {
        hero.changerCouleur(cout, 2);
        hero.afficher(cout);
        hero.changerCouleur(cout, 4);
        cout << trait << endl;
    }

    // ------------------------------------------------------------ Affichage de notre liste en ordre alphabétique ------------------------------------------------------------

    const string traitAlphabetique = "\n\033[32m══════════════════════════════ Affichage des Héros en ordre alphabétique ══════════════════════════════════ ";
    cout << traitAlphabetique << endl;

    // Utilisez un conteneur pour avoir les héros en ordre alphabétique.
    set<Heros, function<bool(const Heros&, const Heros&)>> setHeros([](const Heros& a, const Heros& b) { return a.getNom() < b.getNom(); });

    for (const auto& heros : listeHeros)
    {
        setHeros.insert(heros);
    }

    // Afficher les héros triés par ordre alphabétique
    for (const auto& hero : setHeros) 
    {
        hero.changerCouleur(cout, 2);
        hero.afficher(cout);
        hero.changerCouleur(cout, 4);
        cout << trait << endl;
    }
}

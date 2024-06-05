#pragma once

#include <string>

using namespace std;

enum Couleur
{
    Rouge,
    Bleu,
    Mauve,
    Blanc,
};

string couleurToString(Couleur couleur)
{
    switch (couleur)
    {
        case Couleur::Rouge: return "\033[31m";
        case Couleur::Bleu:  return "\033[34m";
        case Couleur::Mauve: return "\033[35m";
        case Couleur::Blanc: return "\033[0m";
        default: return "\033[0m";
    }
}

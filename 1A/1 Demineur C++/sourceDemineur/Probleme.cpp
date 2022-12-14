/**
 * @file Probleme.cpp
 * Projet Demineur
 * @author Nils Mittelhockamp et Louis Masson
 * @version 3 23/12/2021
 * @brief Definition des fonctions permettant de creer un probleme
 */
#include "Probleme.h"

void CreationProbleme(Case** plateau, unsigned int nbLignes, unsigned int nbColonnes, unsigned int nbMines) {
    unsigned int positionMine;
    cout << " " << nbMines << " ";
    //On âppelle la fonction autant de fois que l'on veut de mines
    for (unsigned int i = 0; i < nbMines; ++i)
    {
        positionMine = GenerationMine(plateau, nbLignes, nbColonnes);
        cout << positionMine;
        //On ajoute un espace après la position de la bombe hormis pour la dernière bombe
        if (i != (nbMines - 1)) 
            cout << " ";
        else
            cout << endl;
    }
}
unsigned int GenerationMine(Case** plateau, unsigned int nbLignes, unsigned int nbColonnes) {
    unsigned int numligne;
    unsigned int numcolonne;

    //On génère des indices aléatoire compris dans les dimensions
    numligne = rand() % nbLignes;
    numcolonne = rand() % nbColonnes;

    //On recommence tant que la case est une mine
    while (plateau[numligne][numcolonne].c == MINE)
    {
        numligne = rand() % nbLignes;
        numcolonne = rand() % nbColonnes;
    }

    //On ajoute la mine et on calcule sa position
    plateau[numligne][numcolonne].c = MINE;
    unsigned int positionMine = (numcolonne + (nbColonnes * numligne));
    return positionMine;
}
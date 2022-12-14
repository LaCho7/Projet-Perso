/**
 * @file Commande.cpp
 * Projet Demineur
 * @author Nils Mittelhockamp et Louis Masson
 * @version 3 23/12/2021
 * @brief Definitions des fonctions principales
 */

#include "Commande.h"

void Commande() {
    unsigned int commande, nbLignes, nbColonnes, nbMines;
    cin >> commande >> nbLignes >> nbColonnes; //Recuperation des informations relatives à toutes les commandes

    Case** plateau = CreationPlateau(nbLignes, nbColonnes);
    Partie partie = EN_COURS;

    if (commande == 1)  //Creation d'un probleme
    {
        cin >> nbMines;
        AffichageDimensions(nbLignes, nbColonnes);
        CreationProbleme(plateau, nbLignes, nbColonnes, nbMines);
    }

    else if (commande == 2) //Creation d'une grille
    {
        AffichageDimensions(nbLignes, nbColonnes);
        cin >> nbMines;
        CreationGrille(plateau, nbLignes, nbColonnes, nbMines);
        partie = HistoriqueCoups(plateau, nbLignes, nbColonnes);
        AffichagePlateau(plateau, nbLignes, nbColonnes, partie);
    }

    else if (commande == 3) //Verification de la victoire
    {
        cin >> nbMines;
        CreationGrille(plateau, nbLignes, nbColonnes, nbMines);
        partie = HistoriqueCoups(plateau, nbLignes, nbColonnes);

        //Affiche l'état de la partie après l'historique de coups
        if (partie == GAGNEE)
            cout << "game won";
        else
            cout << "game not won";
    }

    else if (commande == 4) //Verification de la defaite
    {
        cin >> nbMines;
        CreationGrille(plateau, nbLignes, nbColonnes, nbMines);
        partie = HistoriqueCoups(plateau, nbLignes, nbColonnes);

        //Affiche l'état de la partie après l'historique de coups
        if (partie == PERDUE)
            cout << "game lost";
        else
            cout << "game not lost";
    }

    else if (commande == 5) //Creation d'un nouveau coup
    {
        RecuperationGrille(plateau, nbLignes, nbColonnes);
        CreationCoup(plateau, nbLignes, nbColonnes);
    }

    //On rend la mémoire
    for (unsigned int i = 0; i < nbLignes; ++i) {
        delete[] plateau[i];
    }
    delete[] plateau; 
}

Case** CreationPlateau(unsigned int nbLignes, unsigned int nbColonnes)
{
    //Création d'un plateau dynamique à deux dimensions representant le plateau de jeu
    Case** plateau = new Case * [nbLignes];

    for (unsigned int i = 0; i < nbColonnes; ++i) {
        plateau[i] = new Case[nbColonnes];
    }

    InitialiserPlateau(plateau, nbLignes, nbColonnes);

    return plateau;
}

void InitialiserPlateau(Case** plateau, unsigned int nbLignes, unsigned int nbColonnes) {
    //On parcourt toutes les cases du plateau afin de les initialiser à vide
    for (unsigned int i = 0; i < nbLignes; ++i)
    {
        for (unsigned int j = 0; j < nbColonnes; ++j)
        {
            plateau[i][j].c = RIEN;
        }
    }
}
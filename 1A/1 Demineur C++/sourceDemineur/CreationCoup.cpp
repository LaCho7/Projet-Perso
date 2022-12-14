/**
 * @file CreationCoup.cpp
 * Projet Demineur
 * @author Nils Mittelhockamp et Louis Masson
 * @version 3 23/12/2021
 * @brief Definitions des fonctions relatives � la creation d'un coup
 */

#include "CreationCoup.h"

void CreationCoup(Case** plateau, unsigned int nbLignes, unsigned int nbColonnes) {

    unsigned int ligneAleatoire, colonneAleatoire;
    bool continuer = true;
    while (continuer == true)
    {
        unsigned int r = rand() % 2; //On choisit un chiffre al�atoire entre 0 et 1 nous permettant de choisir si on d�couvre ou on marque une case
        if (r == 0) //On choisit de marquer une case
        {
            ligneAleatoire = rand() % nbLignes; //On choisit un indice al�atoire pour les lignes
            colonneAleatoire = rand() % nbColonnes; //On choisit un indice al�atoire pour les colonnes

            //Si la case n'est ni marqu�e, ni d�couverte
            if (plateau[ligneAleatoire][colonneAleatoire].decouverte == false && plateau[ligneAleatoire][colonneAleatoire].marquee == false)
            {
                plateau[ligneAleatoire][colonneAleatoire].decouverte = true;
                cout << "D" << colonneAleatoire + (nbColonnes * (ligneAleatoire)); //On affiche le coup
                continuer = false;
            }
        }

        else
        {
            ligneAleatoire = rand() % nbLignes; //On choisit un indice al�atoire pour les lignes
            colonneAleatoire = rand() % nbColonnes; //On choisit un indice al�atoire pour les colonnes
            if (plateau[ligneAleatoire][colonneAleatoire].decouverte == false && plateau[ligneAleatoire][colonneAleatoire].marquee == false)
            {
                plateau[ligneAleatoire][colonneAleatoire].marquee = true;
                cout << "M" << colonneAleatoire + (nbColonnes * (ligneAleatoire)); //On affiche le coup
                continuer = false;
            }
        }
    }
}
void RecuperationGrille(Case** plateau, unsigned int nbLignes, unsigned int nbColonnes)
{
    unsigned int position = 0, nbEspace = 0;
    char c[2];

    while (position < nbLignes * nbColonnes) //On continue tant que l'on n'a pas trouv� toutes les cases
    {

        cin.ignore(1, '\n');   //On ignore les retours � la ligne
        cin >> c[0]; //On recup�re la grille caract�re par carct�re    

        //On calcule les indices � l'aide de la position
        unsigned int indiceLigne = (position - (position % nbColonnes)) / nbColonnes;
        unsigned int indiceColonne = position % nbColonnes;

        if (c[0] == '.')
        {
            //On enregistre la case, on incr�mente la position et passe le nombre d'espaces � 0
            plateau[indiceLigne][indiceColonne].decouverte = false;
            plateau[indiceLigne][indiceColonne].c = RIEN;
            position = position + 1;
            nbEspace = 0;
        }

        else if (c[0] == 'x' || isdigit(c[0]))
        {
            //On enregistre la case, on incr�mente la position et passe le nombre d'espaces � 0
            plateau[indiceLigne][indiceColonne].c = DANGER;
            plateau[indiceLigne][indiceColonne].decouverte = true; //Ici, "d�couverte" correspond � jouer
            plateau[indiceLigne][indiceColonne].marquee = false;
            position = position + 1;
            nbEspace = 0;
        }

        else if (c[0] == '|')
        {
            //Quand un caract�re | est trouv�, on incremente le nombre d'espaces afin de v�rifer si plusieurs espaces se suivent
            nbEspace = nbEspace + 1;
        }

        if (nbEspace % 2 == 0 && nbEspace != 0) //Si deux espaces se suivent, on enregistre une case vide
        {
            plateau[indiceLigne][indiceColonne].c = RIEN;
            plateau[indiceLigne][indiceColonne].decouverte = true;
            plateau[indiceLigne][indiceColonne].marquee = false;
            position = position + 1;
            nbEspace = nbEspace - 1;
        }

        if (c[0] == '_') //On remet le nombre d'espace � 0 � chaque fin de ligne
        {
            nbEspace = 0;
        }
    }
}
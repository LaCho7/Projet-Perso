/**
 * @file Grille.cpp
 * Projet Demineur
 * @author Nils Mittelhockamp et Louis Masson
 * @version 3 23/12/2021
 * @brief Definitions de divers fonctions relatives � l'execution du d�mineur
 */
#include "Grille.h"
#include <cmath>

void CreationGrille(Case** plateau, unsigned int nbLignes, unsigned int nbColonnes, unsigned int nbMines) {
    unsigned int positionBombe;

    //Ajoute une mine � une position donn�e
    for (unsigned int i = 0; i < nbMines; ++i)
    {
        cin >> positionBombe;
        AjouteMine(plateau, nbColonnes, positionBombe);
    }
    //Recherche les cases adjacentes � des mines
    MinesVoisines(plateau, nbLignes, nbColonnes);
}
void AjouteMine(Case** plateau, unsigned int nbColonnes, unsigned int positionMine)
{
    plateau[(positionMine - (positionMine % nbColonnes)) / nbColonnes][positionMine % nbColonnes].c = MINE;
}
void MinesVoisines(Case** plateau, unsigned int nbLignes, unsigned int nbColonnes)
{
    /*Quadruple boucle qui permet de v�rifier les 9 cases ajacentes � une case
    * On soustrait une valaure � un indice pour obtenir une case adjacente */
    for (int i = 0; i < nbLignes; i++) //Indice ligne
    {
        for (int j = 0; j < nbColonnes; j++) //Indice colonne
        {
            for (int k = -1; k <= 1; k++) //Valeur � soustraire � l'indice colonne pour obtenir une case voisine
            {
                for (int l = -1; l <= 1; l++) //Valeur � soustraire � l'indice ligne pour obtenir une case voisine
                {
                    if ((i - l) >= 0 && (j - k) >= 0 && (i - l) < (int)(nbLignes) && (j - k) < (int)nbColonnes) //On verifie que la case existe (indices >= 0 et indices < aux dimensions du plateau)
                    {
                        if (plateau[i - l][j - k].c == MINE && plateau[i][j].c != MINE) //Si une case voisine est une mine
                        {
                            plateau[i][j].c = DANGER;
                            plateau[i][j].nbMinesVoisines = plateau[i][j].nbMinesVoisines + 1;
                        }
                    }
                }
            }
        }
    }
}
Partie HistoriqueCoups(Case** plateau, unsigned int nbLignes, unsigned int nbColonnes)
{
    char coup[LGCOUP];
    unsigned int nbCoups, position, indiceLigne, indiceColonne;
    Partie partie = EN_COURS;
    cin >> nbCoups;

    for (unsigned int i = 0; i < nbCoups && partie == EN_COURS; ++i)
    {
        cin >> coup;
        if (coup[0] == 'D')
        {
            //On r�cup�re la position entr�e
            position = 0;
            for (unsigned int j = 1; j <= strlen(coup) - 1; j++)
            {
                /*
                * La position est �gal � la somme des produits des chiffres de la position et de leurs poids
                * On caste un caract�re en entier non-sign�, que l'on multiplit par son poids (10 puissance sa position dans le coup)
                * On additionne ce produit au resultat pr�cedent pour obtenir la position finale */
                position = ((unsigned int)coup[j] - 48) * ((unsigned int)pow(10, (strlen(coup) - 1 - j))) + position;
            }
            //On calcule les indices avec la position
            indiceLigne = (position - (position % nbColonnes)) / nbColonnes;
            indiceColonne = position % nbColonnes;

            //Si la case est une bombe, la partie est perdue
            if (plateau[indiceLigne][indiceColonne].c == MINE)
            {
                partie = PERDUE;
                plateau[indiceLigne][indiceColonne].decouverte = true;
            }

            else
            {
                plateau[indiceLigne][indiceColonne].decouverte = true;
                //On appelle une fonction pour d�couvrir les cases adjacentes
                CaseVoisines(plateau, position, nbLignes, nbColonnes); 
            }
        }

        else if (coup[0] == 'M')
        {
            //On r�cup�re la position entr�e
            position = 0;
            for (unsigned int j = 1; j <= strlen(coup) - 1; j++)
            {
                /*
                * La position est �gal � la somme des produits des chiffres de la position et de leurs poids
                * On caste un caract�re en entier non-sign�, que l'on multiplit par son poids (10 puissance sa position dans le coup)
                * On additionne ce produit au resultat pr�cedent pour obtenir la position finale */
                position = ((unsigned int)coup[j] - 48) * ((unsigned int)pow(10, (strlen(coup) - 1 - j))) + position;
            }
            //On calcule les indices avec la position
            indiceLigne = (position - (position % nbColonnes)) / nbColonnes;
            indiceColonne = position % nbColonnes;

            plateau[indiceLigne][indiceColonne].marquee = true;

            //Si la case marqu�e est une bombe, on verifie si la case est une bombe
            if (plateau[indiceLigne][indiceColonne].c == MINE)
            {
                partie = PartieGagnee(plateau, nbLignes, nbColonnes);
            }

            else
            {
                partie = PERDUE;
            }
        }
    }
    return partie;
}
void CaseVoisines(Case** plateau, unsigned int position, unsigned int nbLignes, unsigned int nbColonnes)
{
    bool continuer = true; //Si la recherche doit continuer

    //On r�cup�re les indices de la case � l'aide de la position
    unsigned int i = (position - (position % nbColonnes)) / nbColonnes; //Indice ligne
    unsigned int j = position % nbColonnes; //Indice colonne
    unsigned int p = 0;

    while (continuer == true)
    {
        continuer = false;
        if (plateau[i][j].c == RIEN)
        {
            for (int k = -1; k <= 1; k++) //Valeur � soustraire � l'indice ligne pour obtenir une case voisine
            {
                for (int l = -1; l <= 1; l++) //Valeur � soustraire � l'indice colonne pour obtenir une case voisine
                {
                    //On calcule les nouveaux indices, qui sont �gales � la position moins la variable
                    int nIndiceLigne = i - l;
                    int nIndiceColonne = j - k;

                    if ((nIndiceLigne) >= 0 && (nIndiceColonne) >= 0 && (unsigned int)(nIndiceLigne) < nbLignes && (unsigned int)(nIndiceColonne) < nbColonnes) //On verifie que la case existe dans le plateau 
                    {
                        //Si une mine se cache parmis les case adjacentes � cette case
                        if (plateau[nIndiceLigne][nIndiceColonne].c == DANGER)
                        {
                            plateau[nIndiceLigne][nIndiceColonne].decouverte = true;
                        }

                        //Si la case est vide et n'est pas d�couverte
                        else if (plateau[nIndiceLigne][nIndiceColonne].c == RIEN && plateau[nIndiceLigne][nIndiceColonne].decouverte == false)
                        {
                            plateau[nIndiceLigne][nIndiceColonne].decouverte = true;
                            continuer = true; //On continue la d�couverte des cases adjacentes
                            p = (nIndiceColonne)+(nbColonnes * (nIndiceLigne)); //On calcule la position de la case adjacente vide
                            CaseVoisines(plateau, p, nbLignes, nbColonnes); //La fonction s'appelle elle-meme mais cette fois-ci avec la position de la nouvelle case vide d�couverte
                        }
                    }
                }
            }
        }
    }
}
Partie PartieGagnee(const Case* const* plateau, unsigned int nbLignes, unsigned int nbColonnes)
{
    Partie partie = GAGNEE;

    //On parcourt le plateau � la recherche d'une mine pas d�couverte
    for (unsigned int i = 0; i < nbLignes; i++) //Indice ligne
    {
        for (unsigned int j = 0; j < nbColonnes; j++) //Indice colonne
        {
            if (plateau[i][j].c == MINE && plateau[i][j].marquee == false)
                partie = EN_COURS;
        }
    }
    return partie;
}

//Fonction exclusive pour la commande 2.
void AffichagePlateau(const Case* const* plateau, unsigned int nbLignes, unsigned int nbColonnes, Partie partie) {
    cout << endl;
    for (unsigned int i = 0; i < nbLignes; ++i)
    {
        AffichageLigne(nbColonnes); //Affiche une ligne de s�paration

        for (unsigned int j = 0; j < nbColonnes; ++j)
        {
            //Si une case n'est pas une mine, d�couverte et n'est pas marqu�e
            if (plateau[i][j].decouverte == true && plateau[i][j].marquee == false && plateau[i][j].c != MINE)
            {
                //On affiche le nombre de bombes voisines
                if (plateau[i][j].c == DANGER)
                {
                    cout << "| " << plateau[i][j].nbMinesVoisines << " ";
                }
                else
                    cout << "| " << " " << " ";
            }
            
            //Si la partie n'est pas perdue et n'est pas gagn�e et que la case est marqu�e
            else if (plateau[i][j].marquee == true && partie != PERDUE && partie != GAGNEE) 
            {
                cout << "| " << "x" << " ";
            }

            //Si la partie est perdue, que la case est marqu�e et que la case n'est pas une bombe
            else if (plateau[i][j].marquee == true && partie == PERDUE && plateau[i][j].c != MINE) 
            {
                cout << "| " << "x" << " ";
            }

            //Si la partie est perdue ou gagnee et que la case est une mine
            else if (plateau[i][j].c == MINE && (partie == PERDUE || partie == GAGNEE)) 
            {
                cout << "| " << "m" << " ";
            }

            //Si la case n'est pas d�couverte
            else if (plateau[i][j].decouverte == false)
            {
                cout << "| " << "." << " ";
            }
        }
        cout << "|" << endl;
    }
    AffichageLigne(nbColonnes);
}
void AffichageLigne(unsigned int nbColonnes)
{
    //Affiche une ligne de s�paration
    for (unsigned int i = 0; i < nbColonnes; ++i) {
        cout << " ___";
    }
    cout << endl;
}
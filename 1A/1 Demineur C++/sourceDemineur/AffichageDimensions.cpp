/**
 * @file AffichageDimensions.cpp
 * Projet Demineur
 * @author Nils Mittelhockamp et Louis Masson
 * @version 3 23/12/2021
 * @brief Definition de la fonction affichant les dimensions d'un plateau
 */
#pragma once
#include "AffichageDimensions.h"

void AffichageDimensions(unsigned int nbLignes, unsigned int nbColonnes)
{
    cout << nbLignes << " " << nbColonnes;
}
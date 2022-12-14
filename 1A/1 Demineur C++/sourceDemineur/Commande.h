/**
 * @file Commande.h
 * Projet Demineur
 * @author Nils Mittelhockamp et Louis Masson
 * @version 3 23/12/2021
 * @brief Declaration des fonctions principales
 */

#pragma once

#include "Probleme.h"
#include "Grille.h"
#include "CreationCoup.h"
#include "AffichageDimensions.h"

/**
    * @brief Récupère la commande de l'utilisateur, les dimensions du plateau et appelle la fonction approriée
 */
void Commande();

/**
    * @brief Crée un plateau de jeu composés de cases
    * @param[in] Nombre de lignes du plateau
    * @param[in] Nombre de colonnes du plateau
    * @return Le plateau crée
*/
Case** CreationPlateau(unsigned int nbLignes, unsigned int nbColonnes);

/**
    * @brief Initialise un plateau avec des cases vides
    * @param[in-out] Le plateau à initialiser
    * @param[in] Nombre de lignes du plateau
    * @param[in] Nombres de colonnes du plateau
*/
void InitialiserPlateau(Case** plateau, unsigned int nbLignes, unsigned int nbColonnes);

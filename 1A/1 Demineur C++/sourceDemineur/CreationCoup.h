/**
 * @file CreationCoup.h
 * Projet Demineur
 * @author Nils Mittelhockamp et Louis Masson
 * @version 3 23/12/2021
 * @brief Decalartion des fonctions relatives à la creation d'un coup
 */

#pragma once
#include "Case.h"

/**
    * @brief Crée un coup depuis un plateau
    * @param[in-out] Le plateau
    * @param[in] Nombres de lignes du plateau
    * @param[in] Nombres de colonnes du plateau
*/
void CreationCoup(Case** plateau, unsigned int nbLignes, unsigned int nbColonnes);

/**
    * @brief Récupère une grille
    * @param[in-out] Le plateau dans lequelle on enregistre la grille
    * @param[in] Nombres de lignes du plateau
    * @param[in] Nombres de colonnes du plateau
*/
void RecuperationGrille(Case** plateau, unsigned int nbLignes, unsigned int nbColonnes);

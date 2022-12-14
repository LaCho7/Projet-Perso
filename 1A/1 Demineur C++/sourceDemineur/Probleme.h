/**
 * @file Probleme.h
 * Projet Demineur
 * @author Nils Mittelhockamp et Louis Masson
 * @version 3 23/12/2021
 * @brief Declarations des fonctions permettant de creer un probleme
 */
#pragma once

#include "Case.h"

/**
    * @brief Crée et affiche un probleme généré aléatoirement à partir d'un plateau
    * @param[in-out] Le plateau auquel ajouter le problème
    * @param[in] Nombre de lignes du plateau
    * @param[in] Nombres de colonnes du plateau
    * @param[in] Nombres de mines à ajouter
*/
void CreationProbleme(Case** plateau, unsigned int nbLignes, unsigned int nbColonnes, unsigned int nbMines);

/**
    * @brief Génère une mine aléatoirement sur une case libre d'un plateau
    * @param[in-out] Le plateau à modifier
    * @param[in] Nombre de lignes du plateau
    * @param[in] Nombres de colonnes du plateau
    * @return La position de la mine
*/
unsigned int GenerationMine(Case** plateau, unsigned int nbLignes, unsigned int nbColonnes);

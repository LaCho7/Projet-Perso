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
    * @brief Cr�e et affiche un probleme g�n�r� al�atoirement � partir d'un plateau
    * @param[in-out] Le plateau auquel ajouter le probl�me
    * @param[in] Nombre de lignes du plateau
    * @param[in] Nombres de colonnes du plateau
    * @param[in] Nombres de mines � ajouter
*/
void CreationProbleme(Case** plateau, unsigned int nbLignes, unsigned int nbColonnes, unsigned int nbMines);

/**
    * @brief G�n�re une mine al�atoirement sur une case libre d'un plateau
    * @param[in-out] Le plateau � modifier
    * @param[in] Nombre de lignes du plateau
    * @param[in] Nombres de colonnes du plateau
    * @return La position de la mine
*/
unsigned int GenerationMine(Case** plateau, unsigned int nbLignes, unsigned int nbColonnes);

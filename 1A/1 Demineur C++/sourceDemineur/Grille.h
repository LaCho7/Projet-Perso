/**
 * @file Grille.h
 * Projet Demineur
 * @author Nils Mittelhockamp et Louis Masson
 * @version 3 23/12/2021
 * @brief Declaration de divers fonctions relatives � l'execution du d�mineur
 */

#pragma once

#include "Case.h"

/**
    * @brief Cr�e une grille � partir d'un probl�me et d'un historique de coups
    * @param[in-out] Le plateau � modifier
    * @param[in] Nombre de lignes du plateau
    * @param[in] Nombres de colonnes du plateau
    * @param[in] Nombres de mines
*/
void CreationGrille(Case** plateau, unsigned int nbLignes, unsigned int nbColonnes, unsigned int nbMines);

/**
    * @brief Ajoute une mine � une position donn�e
    * @param[in-out] Le plateau � modifier
    * @param[in] Nombres de colonnes du plateau
    * @param[in] Position de la mine � ajouter
*/
void AjouteMine(Case** plateau, unsigned int nbColonnes, unsigned int positionMine);

/**
    * @brief V�rifie pour chaque case si les cases adjacentes comportent des mines
    * @param[in-out] Le plateau � v�rifier et � modifier
    * @param[in] Nombres de lignes du plateau
    * @param[in] Nombres de colonnes du plateau
*/
void MinesVoisines(Case** plateau, unsigned int nbLignes, unsigned int nbColonnes);

/**
    * @brief R�cup�re un historique de coups, modifie le plateau et renvoi l'�tat de la partie
    * @param[in-out] Le plateau
    * @param[in] Nombres de lignes du plateau
    * @param[in] Nombres de colonnes du plateau
    * @return La partie
*/
Partie HistoriqueCoups(Case** plateau, unsigned int nbLignes, unsigned int nbColonnes);

/**
    * @brief Fonction r�cursive qui d�couvre les cases vides adjacentes � une case
    * @param[in-out] Le plateau
    * @param[in] La position de la case
    * @param[in] Nombres de lignes du plateau
    * @param[in] Nombres de colonnes du plateau
*/
void CaseVoisines(Case** plateau, unsigned int positionCase, unsigned int nbLignes, unsigned int nbColonnes);

/**
    * @brief Verifie si la partie est gagn�e
    * @param[in] Le plateau
    * @param[in] Nombres de lignes du plateau
    * @param[in] Nombres de colonnes du plateau
    * @return L'etat de la partie
*/
Partie PartieGagnee(const Case* const* plateau, unsigned int nbLignes, unsigned int nbColonnes);

//Fonction exclusive pour la commande 2

/**
    * @brief Affiche un plateau
    * @param[in] Le plateau
    * @param[in] Nombres de lignes du plateau
    * @param[in] Nombres de colonnes du plateau
*/
void AffichagePlateau(const Case* const * plateau, unsigned int nbLignes, unsigned int nbColonnes, Partie partie);
/**
    * @brief Affiche une ligne de s�paration entre les lignes du plateau
    * @param[in] Nombres de colonnes du plateau
*/
void AffichageLigne(unsigned int nbColonnes);
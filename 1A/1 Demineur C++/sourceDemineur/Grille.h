/**
 * @file Grille.h
 * Projet Demineur
 * @author Nils Mittelhockamp et Louis Masson
 * @version 3 23/12/2021
 * @brief Declaration de divers fonctions relatives à l'execution du démineur
 */

#pragma once

#include "Case.h"

/**
    * @brief Crée une grille à partir d'un problème et d'un historique de coups
    * @param[in-out] Le plateau à modifier
    * @param[in] Nombre de lignes du plateau
    * @param[in] Nombres de colonnes du plateau
    * @param[in] Nombres de mines
*/
void CreationGrille(Case** plateau, unsigned int nbLignes, unsigned int nbColonnes, unsigned int nbMines);

/**
    * @brief Ajoute une mine à une position donnée
    * @param[in-out] Le plateau à modifier
    * @param[in] Nombres de colonnes du plateau
    * @param[in] Position de la mine à ajouter
*/
void AjouteMine(Case** plateau, unsigned int nbColonnes, unsigned int positionMine);

/**
    * @brief Vérifie pour chaque case si les cases adjacentes comportent des mines
    * @param[in-out] Le plateau à vérifier et à modifier
    * @param[in] Nombres de lignes du plateau
    * @param[in] Nombres de colonnes du plateau
*/
void MinesVoisines(Case** plateau, unsigned int nbLignes, unsigned int nbColonnes);

/**
    * @brief Récupère un historique de coups, modifie le plateau et renvoi l'état de la partie
    * @param[in-out] Le plateau
    * @param[in] Nombres de lignes du plateau
    * @param[in] Nombres de colonnes du plateau
    * @return La partie
*/
Partie HistoriqueCoups(Case** plateau, unsigned int nbLignes, unsigned int nbColonnes);

/**
    * @brief Fonction récursive qui découvre les cases vides adjacentes à une case
    * @param[in-out] Le plateau
    * @param[in] La position de la case
    * @param[in] Nombres de lignes du plateau
    * @param[in] Nombres de colonnes du plateau
*/
void CaseVoisines(Case** plateau, unsigned int positionCase, unsigned int nbLignes, unsigned int nbColonnes);

/**
    * @brief Verifie si la partie est gagnée
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
    * @brief Affiche une ligne de séparation entre les lignes du plateau
    * @param[in] Nombres de colonnes du plateau
*/
void AffichageLigne(unsigned int nbColonnes);
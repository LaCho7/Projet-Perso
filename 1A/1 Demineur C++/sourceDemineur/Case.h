/**
 * @file Case.h
 * Projet Demineur
 * @author Nils Mittelhockamp et Louis Masson
 * @version 3 23/12/2021
 * @brief Declaration de la structure case et des types enumeres
 */

#pragma once

#include <iostream>

using namespace std;

//Type d'une case: vide, mine voisine ou minée
enum typeCase { RIEN = 0, DANGER = 1, MINE = 2 };

//Type de partie: perdue, gagnee ou en cours
enum Partie { PERDUE = 0, GAGNEE = 1, EN_COURS = 2 };

//Longueur maximum d'un coup
const unsigned int LGCOUP = 5;

//Structure d'une case
struct Case
{
    bool decouverte = false; //Case découverte ?  
    bool marquee = false; //Case marquée ?
    typeCase c = RIEN; //Type de la case
    unsigned int nbMinesVoisines = 0; //Nombre de mines avoisinantes
};

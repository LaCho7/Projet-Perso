/**
 * @file Demineur.cpp
 * Projet Demineur
 * @author Nils Mittelhockamp et Louis Masson
 * @version 3 23/12/2021
 * @brief Main du projet
 */

#include <iostream>

using namespace std;

#include "Commande.h"

int main() {
    srand(time(NULL));
    //Appel de la fonction principale
    Commande();
    return 0;
}
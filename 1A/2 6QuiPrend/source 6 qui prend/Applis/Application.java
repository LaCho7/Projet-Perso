package Applis;

import JeuCarte.Partie;
import JeuCarte.Joueur;

/**
* Programme permettant de jouer � une partie de 6 qui prend
* @author Louis Masson et Nils Mittelhockamp
*/

public class Application {

	/***
	 * Le programme principal permettant de jouer une partie de 6 qui prend
	 * @param args Arguments de la fonction principal
	 */
	public static void main(String[] args) {
		//Cr�er une nouvelle partie
		Partie partie = new Partie();
		//Affiche les joueurs de la partie
		System.out.println(partie.joueursParties());

		for(int i=0; i<Joueur.getNbcartes();++i)
		{
			//Effectue un tour
			partie.prochainTour();
			//Affiche les cartes jou�es durant ce tour
			System.out.print(partie.cartesJouees());
			//Affiche le terrain de jeu
			System.out.print(partie.getTerrain().toString());
			//Affiche les points rammass�es durant ce tour par les joueurs
			System.out.print(partie.afficherPointsRamasses());
		}
		
		//Affiche le r�sultat de la partie
		System.out.print(partie.scores());
	}

}

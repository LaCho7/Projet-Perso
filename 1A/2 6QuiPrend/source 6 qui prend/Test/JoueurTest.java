package Test;

import static org.junit.Assert.assertEquals;

import org.junit.jupiter.api.Test;

import JeuCarte.Joueur;
import JeuCarte.Terrain;

/***
 * Classe vérifiant le fonctionnement de la classe Joueur
 * @author Nils
 *
 */
class JoueurTest {

	@Test
	void main() {
		
		Joueur joueur = new Joueur("Louis");
		Terrain t = new Terrain();
		joueur.initialiserMain(t);
		//On vérifie que le joueur a bien reçu le bon nombre de cartes
		assertEquals(joueur.getMain().size(),Joueur.getNbcartes());
		//On vérifie que les cartes ont bien été piochées du deck
		assertEquals(t.getDeck().size(), Terrain.getNBCARTES()-5-Joueur.getNbcartes());
		
		
		/*On teste la méthode aCetteCarte
		 * la méthode doit retourner true 10 fois
		 */
		int cartes=0;
		for (int i=1; i<Terrain.getNBCARTES();++i)
		{
			if(joueur.aCetteCarte(i))
				++cartes;
		}
		//La variable cartes doit avoir été incrémenté 10 fois
		assertEquals(cartes, Joueur.getNbcartes());
	}
}

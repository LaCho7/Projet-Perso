package Test;

import static org.junit.Assert.assertEquals;

import org.junit.jupiter.api.Test;

import JeuCarte.Joueur;
import JeuCarte.Terrain;

/***
 * Classe v�rifiant le fonctionnement de la classe Joueur
 * @author Nils
 *
 */
class JoueurTest {

	@Test
	void main() {
		
		Joueur joueur = new Joueur("Louis");
		Terrain t = new Terrain();
		joueur.initialiserMain(t);
		//On v�rifie que le joueur a bien re�u le bon nombre de cartes
		assertEquals(joueur.getMain().size(),Joueur.getNbcartes());
		//On v�rifie que les cartes ont bien �t� pioch�es du deck
		assertEquals(t.getDeck().size(), Terrain.getNBCARTES()-5-Joueur.getNbcartes());
		
		
		/*On teste la m�thode aCetteCarte
		 * la m�thode doit retourner true 10 fois
		 */
		int cartes=0;
		for (int i=1; i<Terrain.getNBCARTES();++i)
		{
			if(joueur.aCetteCarte(i))
				++cartes;
		}
		//La variable cartes doit avoir �t� incr�ment� 10 fois
		assertEquals(cartes, Joueur.getNbcartes());
	}
}

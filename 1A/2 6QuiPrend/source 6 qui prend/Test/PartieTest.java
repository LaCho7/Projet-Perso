package Test;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

import JeuCarte.Partie;

/***
 * Permet de tester le fonctionnement de la classe partie
 * @author Nils
 *
 */
class PartieTest {

	private final int NBJOUEURS=4;
	@Test
	void nbJoueurs() {
		Partie p = new Partie();	
		//Vérifie qu'une partie comporte bien le nombre de joueurs donné dans le fichier de configuration
		//après création
		assertEquals(p.getNbJoueurs(),NBJOUEURS);
			
		//Aucun joueur doit ramasser de tetes de boeufs au début de la partie
		assertEquals("Aucun joueur ne ramasse de tête de boeufs."+System.getProperty("line.separator"),p.afficherPointsRamasses());
	}
}

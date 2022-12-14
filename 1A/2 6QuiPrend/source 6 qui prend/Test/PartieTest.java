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
		//V�rifie qu'une partie comporte bien le nombre de joueurs donn� dans le fichier de configuration
		//apr�s cr�ation
		assertEquals(p.getNbJoueurs(),NBJOUEURS);
			
		//Aucun joueur doit ramasser de tetes de boeufs au d�but de la partie
		assertEquals("Aucun joueur ne ramasse de t�te de boeufs."+System.getProperty("line.separator"),p.afficherPointsRamasses());
	}
}

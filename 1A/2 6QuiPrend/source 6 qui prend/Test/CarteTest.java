package Test;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

import JeuCarte.Carte;

/***
 * Permet de tester le fonctionnement de la classe carte
 * @author Nils
 *
 */
class CarteTest {

	@Test
	void main() {
		Carte c1 = new Carte(3);
		Carte c2= new Carte(55);
		Carte c3 = new Carte(10);
		Carte c4 = new Carte(22);
		Carte c5 = new Carte(65);
		
		//Verifie la valeur attribuée des tetes de boeufs
		assertEquals(1, c1.getTetesBoeufs());
		assertEquals(7, c2.getTetesBoeufs());
		assertEquals(3, c3.getTetesBoeufs());
		assertEquals(5, c4.getTetesBoeufs());
		assertEquals(2, c5.getTetesBoeufs());

	}
}

package Test;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;
import JeuCarte.Terrain;

/***
 * Permet de tester le fonctionnement de la classe terrain
 * @author Nils
 *
 */
class TerrainTest {
	@Test
	void piocher() {
		Terrain t = new Terrain();
		
		//On souhaite vérifier qu'aucun point ait été attribué
		assertEquals(t.getPointsDuTour().size(),0);
		
		for(int i=0;i<Terrain.getNBCARTES()-5;++i)
		{
			t.piocher();
		} 
		//Vérifie que le deck a bien été vidée et donc que les cartes peuvent bien etre piochées
		assertEquals(t.getDeck().size(),0);
		
	}
}

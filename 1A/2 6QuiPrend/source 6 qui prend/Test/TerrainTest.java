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
		
		//On souhaite v�rifier qu'aucun point ait �t� attribu�
		assertEquals(t.getPointsDuTour().size(),0);
		
		for(int i=0;i<Terrain.getNBCARTES()-5;++i)
		{
			t.piocher();
		} 
		//V�rifie que le deck a bien �t� vid�e et donc que les cartes peuvent bien etre pioch�es
		assertEquals(t.getDeck().size(),0);
		
	}
}

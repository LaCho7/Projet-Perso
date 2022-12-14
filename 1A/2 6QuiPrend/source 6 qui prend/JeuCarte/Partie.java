package JeuCarte;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.Scanner;

/**
 * La classe Partie permet de creer une partie
 * Elle contient un terrain, 
 * une ArrayList de joueurs,
 * une ArrayList de cartes representant les cartes jouées à chaque tour,
 * le nombre de joueurs
 * @author Louis Masson et Nils Mittelhockamp
 */
public class Partie {
	//le terrain de la partie
	private Terrain terrain = new Terrain();
	//les joueurs de la partie
	private ArrayList<Joueur> joueurs= new ArrayList<Joueur>();
	//les cartes jouees à chaque tour
	private ArrayList<Carte> cartesJouees = new ArrayList<Carte>();
	int nbJoueurs;
	
	/***
	 * Constructeur de partie
	 */
	public Partie() {
		//Recupere les differents joueurs depuis le fichier de configuration
		this.recuperationJoueurs(); 
		for(Joueur j : joueurs)
			//Initialise la main de chaque joueur à partir d'un terrain
			j.initialiserMain(this.terrain);
	}
		
	/***
	 * Recupere les differents joueurs depuis le fichier de configuration
	 * et les sauvegardes dans l'ArrayList de joueurs
	 */
	public void recuperationJoueurs()
		{	
		    FileReader fichierConfig;
		    
		    //essai d'ouvrir le fichier de configuartion
			try {
				fichierConfig = new FileReader("config.txt");
				Scanner flux = new Scanner(fichierConfig);
			    while (flux.hasNext())
			    {
			    	//crée et ajoute un nouveau joueur
			    	joueurs.add(new Joueur(flux.nextLine())); 
			    	++nbJoueurs;
			    }
			    flux.close();
			    
			//si l'ouverture du fichier echoue    
			} catch (FileNotFoundException e) {
				e.printStackTrace();
			}
		}
	
	/***
	 * Permet de jouer un tour
	 */
	public void prochainTour() {
		terrain.getPointsDuTour().clear(); //On supprime les points accumulés au tour précedent
		cartesJouees.clear(); //On vide l'ArrayList des cartes jouées
		
		for(Joueur j : joueurs) 
		{
			//Chaque joueur joue une carte et l'ajoute aux cartes jouees
			cartesJouees.add(j.joue(terrain)); 
			cartesJouees.get(cartesJouees.size()-1).setJoueur(j);
		}
		//On trie les cartes jouées et on les ajoutent au terrain
		trierCartesJouees();
		terrain.ajouterCarteTerrain(cartesJouees);
		
	}
	
	/***
	 * Renvoi une chaine de caractère correpsondant à l'affichage des cartes jouées 
	 * @return s les cartes jouées sous forme de chaine de caractères
	 */
	public String cartesJouees() {
		StringBuilder s = new StringBuilder();
		s.append("Les cartes ");
		for (int i=0; i<cartesJouees.size(); ++i){
			//Affichage spécifique pour la dernière carte
			if (i==cartesJouees.size()-1)
				s.append(cartesJouees.get(cartesJouees.size()-1).getNumero()+" ("+cartesJouees.get(cartesJouees.size()-1).getJoueur().getNomJoueur()+") ont été posées."+System.getProperty("line.separator"));
			else
			{
				s.append(cartesJouees.get(i).getNumero()+" ("+cartesJouees.get(i).getJoueur().getNomJoueur()+")");
				if (i==cartesJouees.size()-2)
					s.append(" et ");
				else
					s.append(", ");
			}				
		}
		
		return s.toString();
	}

	/***
	 * Renvoi une chaine de caractère correpsondant à l'affichage des joueurs de la partie 
	 * @return s les joueurs de la partie sous forme de chaine de caractères
	 */
	public String joueursParties() {
		StringBuilder s = new StringBuilder();
		s.append("Les "+nbJoueurs+" joueurs sont ");
		for (int i=0; i<nbJoueurs;++i)
		{	if(i<nbJoueurs-2)
				s.append(joueurs.get(i).getNomJoueur()+", ");
			else if(i==nbJoueurs-2)
				s.append(joueurs.get(i).getNomJoueur()+" ");		
			else
				s.append("et "+joueurs.get(i).getNomJoueur()+". ");
		}
		s.append("Merci de jouer à 6 qui prend !");
		return s.toString();
	}

	/***
	 * Renvoi une chaine de caractère correpsondant à l'affichage des scores de la partie
	 * @return s les scores final sous forme de chaine de caractères
	 */
	public String scores() {
		trierScores();
		StringBuilder s = new StringBuilder();
		s.append("** Score final"+System.getProperty("line.separator"));
		for (Joueur j: joueurs)
		{
			s.append(j.getNomJoueur()+" a ramassé "+j.getTetesBoeufs()+ " tête de boeufs"+System.getProperty("line.separator"));
		}
		
		return s.toString();
		
	}

	/***
	 * Trie les scores de la partie
	 */
	private void trierScores() {
		Joueur j;
		//Double boucle pour parcourir l'ArrayList de joueurs et comparer ses valeurs
		for (int i=0;i<joueurs.size();++i)
		{
			for(int k=1;k<joueurs.size()-i;++k)
			{
				if(joueurs.get(k).getTetesBoeufs()<joueurs.get(k-1).getTetesBoeufs())
				{
					j=joueurs.get(k);
					joueurs.set(k, joueurs.get(k-1));
					joueurs.set(k-1, j);				
				}
				
				//En cas d'égalité des têtes de boeufs, trie par ordre alphabétique
				else if (joueurs.get(k).getTetesBoeufs()==joueurs.get(k-1).getTetesBoeufs() 
						&& ((joueurs.get(k).getNomJoueur().compareTo(joueurs.get(k-1).getNomJoueur())<0)))
				{
					j=joueurs.get(k);
					joueurs.set(k, joueurs.get(k-1));
					joueurs.set(k-1, j);
				}
			}
		}
		
	}

	/***
	 * Trie les cartes jouées
	 */
	private void trierCartesJouees()
	{
		Carte tmp;
		//Double boucle pour parcourir l'ArrayList de cartes et comparer les cartes jouees
		for (int j=0;j<cartesJouees.size();++j)
		{
			for(int i=1;i<cartesJouees.size()-j;++i)
			{
				//Si une carte superieur possède un indice inferieur
				if(cartesJouees.get(i).getNumero()<cartesJouees.get(i-1).getNumero())
				{
					tmp=cartesJouees.get(i);
					cartesJouees.set(i, cartesJouees.get(i-1));
					cartesJouees.set(i-1, tmp);				
				}
			}
		}
	}

	/***
	 * Renvoi le terrain
	 * @return terrain le terrain de la partie
	 */
	public Terrain getTerrain() {
		return terrain;
	}

	/***
	 * Renvoi le nombre de joueurs, seulement utilsié dans les tests
	 * @return nbJoueurs Le nombre de joueurs de la partie
	 */
	public int getNbJoueurs() {
		return nbJoueurs;
	}
	
	/***
	 * Renvoi un String qui correspond à l'affichage attendu pour afficher les points ramassés durant un tour
	 * @return s Le String correspondant
	 */
	public String afficherPointsRamasses() {
		StringBuilder s = new StringBuilder();
		
		//Si aucun joueur n'a ramassé de têtes de boeufs
		if(terrain.getPointsDuTour().size()==0)
			s.append("Aucun joueur ne ramasse de tête de boeufs."+System.getProperty("line.separator"));
		else
		{
			//pour chaque joueur present dans la HashMap
	        for(Joueur j: terrain.getPointsDuTour().keySet()){
	        	s.append(j.getNomJoueur()+" a ramassé "+terrain.getPointsDuTour().get(j)+" tête de boeufs"+System.getProperty("line.separator"));
	        }
		}

		return s.toString();
	}
}

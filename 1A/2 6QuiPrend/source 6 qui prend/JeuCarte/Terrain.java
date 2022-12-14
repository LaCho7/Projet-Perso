package JeuCarte;

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.InputMismatchException;
import java.util.Scanner;

/**
 * La classe Terrain permet de creer un terrain de jeu correspondant au 6 qui prend
 * Elle contient le nombre de cartes par partie
 * le nombre de series
 * le nombre de cartes maximum par serie
 * une ArrayList de cartes correspondant au deck de la partie
 * un tableau d'ArrayList de Carte representant les différentes series
 * et une HashMap utilisant les joueurs comme clés comportant les têtes de boeufs accumulées durant le dernier tour
 * @author Louis Masson et Nils Mittelhockamp
 */
public class Terrain {

	private static final int NBCARTES=105;
	private static final int NBSERIES=4;
	private static final int NBCARTESERIES=5;
	private ArrayList<Carte> deck= new ArrayList<Carte>();
	private ArrayList<Carte>[] series = new ArrayList[NBSERIES];
	private HashMap<Joueur, Integer> pointsDuTour = new HashMap<Joueur, Integer>();

	/***
	 * Constructeur d'un terrain, 
	 * on crée le deck et on initialise chaque serie avant de les trier
	 */
	public Terrain() { 
		creationDeck();	
		for (int i=0; i<NBSERIES;++i)
		{
			series[i]=new ArrayList<Carte>();
			series[i].add(deck.get(deck.size() -1));
			deck.remove(deck.size() -1 );
		}
		trierSeries();
	}

	/***
	 * Initialise un deck
	 */
	private void creationDeck() {
		//Le deck doit etre vide
		assert(deck.size()==0);
		//Ajoute les cartes du jeu au deck
		for(int i=1; i<NBCARTES;i++) {
			deck.add(new Carte(i));
		}
		//Melange le deck
		Collections.shuffle(deck); 
	}

	/***
	 * Permet de piocher une carte du deck
	 * @return La carte piochée
	 */
	public Carte piocher() {
		//Le deck doit contenir des cartes
		assert(deck.size()>0);
		Carte c=deck.get(deck.size()-1);
		deck.remove(deck.size()-1); //supprime la carte piochée du deck
		return c;
	}

	/***
	 * Verifie si une carte donnée peut être ajoutée sur les series du terrain	
	 * @param c La carte à ajouter
	 * @return Une valeure booléenne qui indique si la carte peut etre ajoutée 
	 */
	private boolean carteEmpilable(Carte c) {

		for(int i=0; i<NBSERIES;++i) 
		{
			//verifie pour chaque serie si la carte peut etre empilée
			if (series[i].get(series[i].size()-1).getNumero()<c.getNumero())
				return true;
		}

		return false;
	}

	/***
	 * Permet à un joueur de choisir une serie à ramasser
	 * @return tmp La serie à ramasser
	 */
	private int choisirSerie() {
		Scanner scan = new Scanner(System.in);
		int tmp=0;
		System.out.print("Saisissez votre choix : ");
		do {
			//Essai de récuperer l'entrée du joueur
			try {
				tmp=scan.nextInt();
				if(tmp>NBSERIES || tmp<1)
					System.out.print("Ce n'est pas une série valide, saisissez votre choix : ");

				//En cas d'erreur
			} catch(InputMismatchException e) {
				System.out.print("Ce n'est pas une série valide, saisissez votre choix : ");
				scan.nextLine();
			}
		}while(tmp>NBSERIES || tmp<1);

		return tmp;
	}

	/***
	 * Trie les series entre elles par rapport à leur carte la plus grande
	 * 
	 */
	private void trierSeries()
	{	

		Carte tmp;
		//Double boucle permettant de trier les series par rapport à leur carte la plus grande

		for (int j=0;j<NBSERIES;++j)
		{
			for(int i=1;i<NBSERIES-j;++i)
			{
				if(series[i].get(0).getNumero()<series[i-1].get(0).getNumero())
				{
					tmp=series[i].get(0);
					series[i].set(0, series[i-1].get(0));
					series[i-1].set(0, tmp);				
				}
			}
		}

	}

	/***
	 * Ajoute les cartes jouées par les joueurs au terrain
	 * @param cartesJouees Une ArrayList de cartes comportant les cartes jouées
	 */
	public void ajouterCarteTerrain(ArrayList<Carte> cartesJouees) {

		//Tableau comportant les différences entre une carte et chaque série
		int[] differencesSeries = new int[NBSERIES]; 
		int teteBoeufs=0;
		int indiceSerie;	

		for(int i=0;i<cartesJouees.size();i++) {
			teteBoeufs=0; //On réinitialise les têtes de boeufs à 0
			//Verifie que la carte est ajoutable au terrain
			if (!carteEmpilable(cartesJouees.get(i)))
			{
				System.out.println(cartesVontEtrePosees(cartesJouees));			
				//Si la carte n'est pas jouable, on demande au joueur de la carte de ramasser une série 
				System.out.println("Pour poser la carte "+cartesJouees.get(i).getNumero()+", "+
						cartesJouees.get(i).getJoueur().getNomJoueur()+" doit choisir la série qu'il va ramasser.");
				System.out.print(toString());
				//Apppelle la fonction pour choisir une serie
				int numeroSerie = choisirSerie();

				//On compte les tetes de boeufs de la serie
				for(int k=0;k<series[numeroSerie-1].size();k++){
					teteBoeufs+= series[numeroSerie-1].get(k).getTetesBoeufs();
				}
				//On ajoute les tetes de boeufs au joueur
				cartesJouees.get(i).getJoueur().ajoutTetesBoeuf(teteBoeufs);
				pointsDuTour.put(cartesJouees.get(i).getJoueur(), teteBoeufs);
				//cartesJouees.get(i).getJoueur().afficherRamasserSerie(teteBoeufs);

				//On reinitialise la serie
				series[numeroSerie-1].clear();
				series[numeroSerie-1].add(cartesJouees.get(i));
			}

			else
			{
				for (int j=0; j<NBSERIES;++j)
				{
					//On calcule la différence entre la carte et les différentes series
					differencesSeries[j]= cartesJouees.get(i).getNumero() - series[j].get(series[j].size()-1).getNumero();
				}

				//On récupere l'indice de la serie la plus proche de la carte
				indiceSerie=serieLaPlusProche(differencesSeries);

				//On vérifie si la serie la lpus proche est déjà pleine
				if(series[indiceSerie].size()==NBCARTESERIES) {

					//Si oui, on calcule les têtes de boeufs de la série
					for(int l=0;l<NBCARTESERIES;++l) 
					{
						teteBoeufs+= series[indiceSerie].get(l).getTetesBoeufs();
					}
					//On lui ajoute ces têtes de boeufs et on réinitialise la série
					cartesJouees.get(i).getJoueur().ajoutTetesBoeuf(teteBoeufs);
					pointsDuTour.put(cartesJouees.get(i).getJoueur(), teteBoeufs);
					//cartesJouees.get(i).getJoueur().afficherRamasserSerie(teteBoeufs);
					series[indiceSerie].clear();	

				}

				//On ajoute la carte jouée
				series[indiceSerie].add(cartesJouees.get(i));
			}			
		}
	}

	/***
	 * Renvoi une chaine de caractère correpsondant à l'affichage des cartes allant être jouées 
	 * @param cartesJouees Les cartes jouées durant le tour
	 * @return s les cartes jouées sous forme de chaine de caractères
	 */
	private String cartesVontEtrePosees(ArrayList<Carte> cartesJouees) {
		StringBuilder s = new StringBuilder();
		s.append("Les cartes ");
		for (int i=0; i<cartesJouees.size(); ++i){
			//Affichage spécifique pour la dernière carte
			if (i==cartesJouees.size()-1)
				s.append(cartesJouees.get(cartesJouees.size()-1).getNumero()+" ("+cartesJouees.get(cartesJouees.size()-1).getJoueur().getNomJoueur()+") vont être posées.");
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
	 * Calcule la série la plus proche d'une carte
	 * @param differencesSeries Un tableau comportant la différence entre la carte et chaque série
	 * @return indiceMinimum L'indice de la serie la plus proche de cette carte est jouable 
	 * (carte la plus grande de la serie inferieure à la carte jouée)
	 */
	private int serieLaPlusProche(int[] differencesSeries){

		//Cette différence sera forcement mise à jour étant donné que la plus grande carte du jeu est 105
		int differenceMinimum=NBCARTES+1;
		int indiceMinimum=0;
		for (int i=0; i<NBSERIES;++i)
		{
			if (differencesSeries[i]>0 && differencesSeries[i]<differenceMinimum)
			{
				indiceMinimum=i;
				differenceMinimum=differencesSeries[i];
			}	
		}

		return indiceMinimum;
	}

	/***
	 * Renvoi l'affichage demandée des cartes d'une serie
	 * @param serie La serie à afficher
	 * @return s Un String contenant les données à afficher
	 */
	private String cartesSerie(ArrayList<Carte> serie) {
        StringBuilder s = new StringBuilder();
        for(int i=0; i<serie.size();++i) 
        {
            s.append(serie.get(i).getNumero());
            if(serie.get(i).getTetesBoeufs()>1) 
                s.append(" ("+ serie.get(i).getTetesBoeufs()+")");

            if(i<serie.size()-1)
                s.append(", ");

        }
        return s.toString();
    }

	/***
	 * Renvoi l'affichage demandée d'un terrain
	 * @return s Un String contenant les données à afficher 
	 */
	@Override
	public String toString() {

		StringBuilder s = new StringBuilder();
		for(int i=1;i<=NBSERIES;i++) {
			s.append("- série n° "+i+" : ");
			s.append(cartesSerie(series[i-1])+System.getProperty("line.separator"));
		}
		return s.toString();
	}

	/***
	 * Renvoi le nombre de cartes dans le jeu
	 * @return NBCARTES Le nombre de cartes maximum
	 */
	public static int getNBCARTES() {
		return NBCARTES;
	}

	/***
	 * Renvoi le deck du terrain, seulement utilisé pour la classe de tests
	 * @return deck L'ArrayList comportant les cartes du deck
	 */
	public ArrayList<Carte> getDeck() {

		return deck;
	}
	
	/***
	 * Renvoi la HashMap comportant les têtes de boeufs accumulés durant le dernier tour pour chaque joueur en ayant ramassé
	 * @return pointsDuTour La Hashmap
	 */
	public HashMap<Joueur, Integer> getPointsDuTour() {
		return pointsDuTour;
	}

}

package JeuCarte;

import java.util.ArrayList;
import java.util.InputMismatchException;
import java.util.Scanner;

/**
 * La classe Joueur permet de créer un joueur
 * Elle contient son nom, 
 * son nombre de tetes de boeufs,
 * le nombre maximum de cartes par joueur 
 * et une ArrayList de Carte representant sa main
 * @author Louis Masson et Nils Mittelhockamp
 */

public class Joueur {
	private String nomJoueur;
	private int nbTetesBoeufs;
	private static final int NBCARTESJOUEUR=10;
	//ArrayList de cartes representant la main d'un joueur
	private ArrayList<Carte> main = new ArrayList<Carte>();
	
	/***
	 * Constructeur d'un joueur, on initialise son nom à null et ses points à 0
	 */
	public Joueur(String nomJoueur)
	{
		this.nomJoueur=nomJoueur;
		nbTetesBoeufs=0;
	}
	
	/***
	 * Permet d'obtenir le nom d'un Joueur
	 * @return nomJoueur le nom du joueur en question sous forme de String
	 */
	public String getNomJoueur() {
		return nomJoueur;
	}
	
	/***
	 * Permet d'obtenir le nombre de têtes de boeufs d'un joueur
	 * @return le nombre de têtes de boeufs d'un joueur
	 */
    public int getTetesBoeufs() {
        return this.nbTetesBoeufs;
    }
    
    /***
     * Permet d'obtenir le nombre maximum de cartes qu'un joueur peut avoir en main
     * @return La constante correspondante
     */
	public static int getNbcartes() {
		return NBCARTESJOUEUR;
	}
	
	/***
	 * Ajoute des têtes de boeufs à un joueur
	 * @param p Le nombre de têtes de boeufs à ajouter
	 */
	public void ajoutTetesBoeuf(int p) {
		nbTetesBoeufs+=p;	
	}
	
	/***
	 * Permet d'initialiser la main d'un Joueur à partir d'un terrain
	 * @param t Le terrain pour lequel il faut piocher dans le paquet (deck)
	 */
	public void initialiserMain(Terrain t)
	{
		for (int i=0 ; i<NBCARTESJOUEUR;i++)
		{
			main.add(t.piocher()); //On prend la carte du dessus du deck, on l'attribue au joueur
								   //et on supprime la carte du deck
		}
		
		trierMain(); //On trie la main du joueur
	}
	
	/***
	 * Trie la main d'un joueur
	 */
	private void trierMain()
	{
		Carte tmp;
		for (int j=0;j<main.size();++j)
		{
			for(int i=1;i<main.size()-j;++i)
			{
				if(main.get(i).getNumero()<main.get(i-1).getNumero()) //Si une carte supérieur possède un indice inferieur
				{
					tmp=main.get(i);
					main.set(i, main.get(i-1));
					main.set(i-1, tmp);				
				}
			}
		}

	}
		
	/***
	 * Supprime une carte donnée dans la main d'un joueur
	 * @param c La carte à supprimer
	 */
	private void supprimerCarte(Carte c)
	{
		for (int i=0;i<main.size();++i) //Parcourt la main
		{
			if (main.get(i).getNumero()==c.getNumero())
				main.remove(i);
		}		
	}
	
	/***
	 * Vérifie si un joueur a une carte donnée dans sa main
	 * @param numero Le numero de la carte à chercher
	 * @return Une valeure booléene correspondant à si le joueur a cette carte ou non
	 */
	public boolean aCetteCarte(int numero) {
		for(Carte c : main) 
			if(c.getNumero()==numero) 
				return true;
		
		return false;
	}
			
	/***
	 * Permet à un joueur de jouer
	 * @param terrain Le terrain sur lequel jouer
	 * @return c La carte jouée
	 */
	public Carte joue(Terrain terrain) {
				
		System.out.println("A "+this.getNomJoueur()+" de jouer.");
		util.Console.pause();
		//Affiche le terrain et les cartes du joueur
		System.out.print(terrain);
		System.out.println(cartes());
		

		System.out.print("Saisissez votre choix : ");		
		Scanner scanner = new Scanner(System.in);				

        int numeroCarte=0;
        
        do {
        	//Essai de récupérer les choix du joueur
            try {
            	numeroCarte=scanner.nextInt();
            	//vérifie que le jour possède bien la carte jouée
            	if (!this.aCetteCarte(numeroCarte))
            	{
            		System.out.print("Vous n'avez pas cette carte, saisissez votre choix : ");
            	}

            } catch(InputMismatchException e) {
                System.out.print("Vous n'avez pas cette carte, saisissez votre choix : ");
                scanner.nextLine();
            }
        //Appel une fonction qui vérifie que le joueur a bien cette carte
        }while(!this.aCetteCarte(numeroCarte));
        
        util.Console.clearScreen();
		
        //Supprime la carte jouée par le joueur
		Carte c = new Carte(numeroCarte);
		this.supprimerCarte(c);
		
		return c;
		
	}
	
	/***
	 * Renvoi une chaine de caractères correspondant à l'affichage attendu pour les cartes d'un joueur
	 * @return s La chaine de caractères
	 */
	public String cartes()
    {
        StringBuilder s = new StringBuilder();
        s.append("- Vos cartes : ");
        for (int i=0; i<main.size(); ++i)
        {
            s.append(main.get(i).getNumero());
            if (main.get(i).getTetesBoeufs()>1)
                s.append(" ("+main.get(i).getTetesBoeufs()+")");
            if (i<main.size()-1)
                s.append(", ");
        }

        return s.toString();
    }
	
	/***
	 * Renvoi la main d'un joueur, est utilisé seulement pour la classe de tests
	 * @return main La main du joueur
	 */
	public ArrayList<Carte> getMain()
	{
		return main;
	}
}


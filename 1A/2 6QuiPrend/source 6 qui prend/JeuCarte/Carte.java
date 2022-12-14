package JeuCarte;

/**
 * La classe Carte permet de creer des cartes correspondant au 6 qui prend
 * Elle contient le num�ro d'une carte
 * son nombre de tetes de boeufs
 * et la ref�rence du joueur qui l'a poss�de
 * @author Louis Masson et Nils Mittelhockamp
 */
public class Carte {
	private int numero=0;
    private int teteBoeufs=0;
    private Joueur j;
 
    /**
     * Construit une carte � partir d'un num�ro
     * @param numero Le num�ro de la carte
     */   
    public Carte(int numero) {
    	//Verifie que le num�ro pass� est bien valide
    	assert(numero>0 && numero<Terrain.getNBCARTES());
        this.numero=numero;
        //Initialise le nombre de t�tes de boeufs de la carte
        this.initialiserTeteBoeufs();
        j=null;
    }
    
    /***
     * Renvoi la r�ference du joueur d'une carte
     * @return j Le joueur poss�dent la carte
     */
    public Joueur getJoueur() {
          return this.j;
      }
    
    /***
     * Attribut un joueur � une carte
     * @param j Le joueur de la carte
     */
    public void setJoueur(Joueur j) {
          this.j=j;
      }
    
    /***
     * Renvoi les t�tes de boeufs d'une carte
     * @return teteBoeufs Le nombre de t�tes de boeufs d'une carte
     */
    public int getTetesBoeufs() {
          return teteBoeufs;
      }

    /***
     * Initialise le nombre de t�tes de boeufs d'une carte
     */
    private void initialiserTeteBoeufs()
    {
    	//Initialise � l'aide du num�ro de la carte
    	int b;
		 if (numero%5==0 && numero%10!=0) { //Carte se terminant par un 5
			 if (numero==55) //Si le num�ro est �gal � 55 ?
				 b=7;
             else
            	 b=2; }
         else if(numero%10==0) //Si la carte se terminant par un 0
        	 b=3;
         else if(numero%11==0) //Si la carte poss�de deux chiffres �gaux
        	 b=5;
         else
        	 b=1;
		 
		 this.teteBoeufs=b;

    }
    
    /***
     * Renvoi le num�ro d'une carte
     * @return numero Le num�ro de la carte
     */
    public int getNumero() {
		return numero;
	}
}

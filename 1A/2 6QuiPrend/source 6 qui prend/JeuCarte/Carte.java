package JeuCarte;

/**
 * La classe Carte permet de creer des cartes correspondant au 6 qui prend
 * Elle contient le numéro d'une carte
 * son nombre de tetes de boeufs
 * et la reférence du joueur qui l'a possède
 * @author Louis Masson et Nils Mittelhockamp
 */
public class Carte {
	private int numero=0;
    private int teteBoeufs=0;
    private Joueur j;
 
    /**
     * Construit une carte à partir d'un numéro
     * @param numero Le numéro de la carte
     */   
    public Carte(int numero) {
    	//Verifie que le numéro passé est bien valide
    	assert(numero>0 && numero<Terrain.getNBCARTES());
        this.numero=numero;
        //Initialise le nombre de têtes de boeufs de la carte
        this.initialiserTeteBoeufs();
        j=null;
    }
    
    /***
     * Renvoi la réference du joueur d'une carte
     * @return j Le joueur possédent la carte
     */
    public Joueur getJoueur() {
          return this.j;
      }
    
    /***
     * Attribut un joueur à une carte
     * @param j Le joueur de la carte
     */
    public void setJoueur(Joueur j) {
          this.j=j;
      }
    
    /***
     * Renvoi les têtes de boeufs d'une carte
     * @return teteBoeufs Le nombre de têtes de boeufs d'une carte
     */
    public int getTetesBoeufs() {
          return teteBoeufs;
      }

    /***
     * Initialise le nombre de têtes de boeufs d'une carte
     */
    private void initialiserTeteBoeufs()
    {
    	//Initialise à l'aide du numéro de la carte
    	int b;
		 if (numero%5==0 && numero%10!=0) { //Carte se terminant par un 5
			 if (numero==55) //Si le numéro est égal à 55 ?
				 b=7;
             else
            	 b=2; }
         else if(numero%10==0) //Si la carte se terminant par un 0
        	 b=3;
         else if(numero%11==0) //Si la carte possède deux chiffres égaux
        	 b=5;
         else
        	 b=1;
		 
		 this.teteBoeufs=b;

    }
    
    /***
     * Renvoi le numéro d'une carte
     * @return numero Le numéro de la carte
     */
    public int getNumero() {
		return numero;
	}
}

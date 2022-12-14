//source.c Godin 101, Masson 103, 9/10/2021
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#pragma warning (disable : 4996)

#define maxTournois 10
#define nbMatchTournoi 127 
#define nbJoueusesTournoi 128 
#define longueurMot 30 

typedef struct {
	char nom[longueurMot + 1];
	unsigned int points;
}Joueuse;

typedef struct {
	unsigned int idxGagnante;
	unsigned int idxPerdante;
}Match;

typedef struct {
	char nom[longueurMot + 1];
	int date;
	Match dataMatch[nbMatchTournoi];
}Tournoi;

typedef struct {
	Tournoi dataTournois[maxTournois];
	Joueuse dataJoueuse[maxTournois * nbJoueusesTournoi];
	unsigned int nbTournois;
	unsigned int idxJ;
	unsigned int idxT;
}TournoiWTA;

//prototypage des fonctions utilisees et documentation

/*
* demande le nombre de tournoi avec lequel on travaille
* [in] tableau de type tournoiWTA
*/
void definir_nombre_tournois(TournoiWTA* ins);

/*
* regarde si le tournoi recherché existe
* [in] tableau de type tournoiWTA
* [in] tableau de type char
* [in] entier
* [retour] entier
*/
int ExistanceTournoi(const TournoiWTA* ins, const char ville[], const int date);

/*
* enregistre un tournoi spécifié
* [in] tableau de type tournoiWTA
*/
void enregistrement_tournoi(TournoiWTA* ins);

/*
* inscrit ou retrouve l'index d'une joueuse
* [in] tableau de type tournoiWTA
* [in] tableau de type char (nom de la joueuse)
* [retour] entier (index joueuse)
*/
int referenceID(TournoiWTA* ins, char joueuse[]);

/*
* Ajoute des points aux joueuses dans le tournoi
* [in] tableau de type tournoiWTA
*/
void attributionpoints(TournoiWTA* ins);

/*
* Affiche un tournoi spécifié
* [in] tableau de type tournoiWTA
*/
void affichage_matchs_tournoi(const TournoiWTA* ins);

/*
* Affiche les matchs d'une joueuse
* [in] tableau de type tournoiWTA
*/
void afficher_matchs_joueuse(const TournoiWTA*);

/*
* Affiche le score de chaque joueuse dans un tournoi donné
* [in] tableau de type tournoiWTA
*/
void affichage_joueuses_tournoi(TournoiWTA* ins);

/*
* Affiche le cumul de points de chaque joueuse
* [in] tableau de type tournoiWTA
*/
void afficher_classement(TournoiWTA* ins);

void definir_nombre_tournois(TournoiWTA* ins) {
	int x;
	scanf("%d", &x);
	if ((x >= 1) && (x <= 10)) { //on verifie si il y a bien un tournoi compris entre 1 et 10 compris on ne pourra pas enregistrer moins de 1 tournoi et pas plus de 10
		ins->nbTournois = x; //écrit le nombre de tournoi dans la structure tournoiWTA
	}
}

int ExistanceTournoi(const TournoiWTA* ins, const char ville[], const int date) {

	for (int i = 0; i < ins->idxT; ++i) {
		if ((strcmp(ins->dataTournois[i].nom, ville) == 0) && (ins->dataTournois[i].date == date)) {
			return i; //renvoi le tournois ayant le même nom / date que celui demandé sinon renvoi -1
		}
	}
	printf("tournoi inconnu");
	return -1;
}

void enregistrement_tournoi(TournoiWTA* ins) {
	char ville[longueurMot + 1];
	int date;
	scanf("%s", ville);
	scanf("%d", &date);
	strcpy(ins->dataTournois[ins->idxT].nom, ville);
	ins->dataTournois[ins->idxT].date = date;

	char joueuseGagne[longueurMot + 1];
	char joueusePerd[longueurMot + 1];

	for (int countMatchs = 0; countMatchs < nbMatchTournoi; ++countMatchs) {
		scanf("%s", joueuseGagne);//Lorsqu'on enregistre, la premiere joueuse (a gauche) est toujours gagnate
		scanf("%s", joueusePerd);//A l'invere, la deuxieme joueuse (a droite) est toujours perdante 

		ins->dataTournois[ins->idxT].dataMatch[countMatchs].idxGagnante = referenceID(ins, joueuseGagne);//on recupere son index
		ins->dataTournois[ins->idxT].dataMatch[countMatchs].idxPerdante = referenceID(ins, joueusePerd);//on recupere son index
	}
	attributionpoints(ins);//on leur attributs leurs points
	ins->idxT += 1;
}

void attributionpoints(TournoiWTA* ins) {
	for (int i = 0; i < nbMatchTournoi; ++i) {//boucle sur tous les matchs pour ajouter des points aux perdants
		if (i >= 0 && i < 64) ins->dataJoueuse[ins->dataTournois[ins->idxT].dataMatch[i].idxPerdante].points += 10;
		else if (i >= 64 && i < 96) {
			ins->dataJoueuse[ins->dataTournois[ins->idxT].dataMatch[i].idxPerdante].points += 45;
		}
		else if (i >= 96 && i < 112) {
			ins->dataJoueuse[ins->dataTournois[ins->idxT].dataMatch[i].idxPerdante].points += 90;
		}
		else if (i >= 112 && i < 120) {
			ins->dataJoueuse[ins->dataTournois[ins->idxT].dataMatch[i].idxPerdante].points += 180;
		}
		else if (i >= 120 && i < 124) {
			ins->dataJoueuse[ins->dataTournois[ins->idxT].dataMatch[i].idxPerdante].points += 360;
		}
		else if (i >= 124 && i < 126) {
			ins->dataJoueuse[ins->dataTournois[ins->idxT].dataMatch[i].idxPerdante].points += 720;
		}
		if (i == 126) {
			ins->dataJoueuse[ins->dataTournois[ins->idxT].dataMatch[i].idxGagnante].points += 2000;//ajout des points a la gagnante
			ins->dataJoueuse[ins->dataTournois[ins->idxT].dataMatch[i].idxPerdante].points += 1200;
		}
	}
}

int referenceID(TournoiWTA* ins, char joueuse[]) {
	for (int i = 0; i < ins->idxJ; ++i) { //pour toutes les joueuses déjà inscrite
		if (strcmp(ins->dataJoueuse[i].nom, joueuse) == 0) {
			return i; //test qui renvoi i si joueuse est dans le tableau
		}
	}
	strcpy(ins->dataJoueuse[ins->idxJ].nom, joueuse); //si le nom n'est pas dans le tableau, alors on le met dedans
	ins->dataJoueuse[ins->idxJ].points = 0; //initialisation des points des nouvelles joueuses à 0
	ins->idxJ += 1;

	return ins->idxJ - 1; //renvoi l'index de notre joueuse
}

void affichage_matchs_tournoi(const TournoiWTA* ins) {
	char ville[longueurMot + 1];
	int date;
	scanf("%s", ville);
	scanf("%d", &date);
	int t = ExistanceTournoi(ins, ville, date);
	if (t == -1) {
		return;
	}
	printf("%s %d\n", ins->dataTournois[t].nom, ins->dataTournois[t].date);//ecriture du nom du tournoi et de sa date
	for (int j = 0; j < nbMatchTournoi; ++j) {
		if (j == 0) printf("64emes de finale\n");
		else if (j == 64) {
			printf("32emes de finale\n");
		}
		else if (j == 96) {
			printf("16emes de finale\n");
		}
		else if (j == 112) {
			printf("8emes de finale\n");
		}
		else if (j == 120) {
			printf("quarts de finale\n");
		}
		else if (j == 124) {
			printf("demi-finales\n");
		}
		else if (j == 126) {
			printf("finale\n");
		}
		printf("%s ", ins->dataJoueuse[ins->dataTournois[t].dataMatch[j].idxGagnante].nom);//affichage de la gagnante
		printf("%s\n", ins->dataJoueuse[ins->dataTournois[t].dataMatch[j].idxPerdante].nom);//affichage de la perdante
	}
}

void afficher_matchs_joueuse(const TournoiWTA* ins) {
	char ville[longueurMot + 1];
	int date, i;
	scanf("%s", ville);
	scanf("%d", &date);
	int t = ExistanceTournoi(ins, ville, date);
	if (t == -1) {
		return;
	}
	char joueuse[longueurMot + 1];
	scanf("%s", joueuse);
	for (int i = 0; i < ins->idxJ; ++i) {
		if (strcmp(joueuse, ins->dataJoueuse[i].nom) == 0) {//on regarde si le nom de la joueuse est presente dans un tournoi.
			for (int j = 0; j < nbMatchTournoi; ++j) {
				if ((i == ins->dataTournois[t].dataMatch[j].idxGagnante) || (i == ins->dataTournois[t].dataMatch[j].idxPerdante)) { //on affiche ses matchs
					printf("%s ", ins->dataJoueuse[ins->dataTournois[t].dataMatch[j].idxGagnante].nom);
					printf("%s\n", ins->dataJoueuse[ins->dataTournois[t].dataMatch[j].idxPerdante].nom);
				}
			}
		}
	}
}

void affichage_joueuses_tournoi(TournoiWTA* ins) {
	char ville[longueurMot + 1];
	int date, i, Retenu1, Retenu2, points[nbJoueusesTournoi], Joueuses[nbJoueusesTournoi];
	int notrejoueuse = 0; //remplace par i 
	scanf("%s", ville);
	scanf("%d", &date);
	int t = ExistanceTournoi(ins, ville, date);
	if (t == -100) {
		return;
	}
	printf("%s %d\n", ins->dataTournois[t].nom, ins->dataTournois[t].date);
	for (i = 0; i < 64; i++) { //dans les 64 premiers matchs les perdantes ont 10 points
		Joueuses[notrejoueuse] = ins->dataTournois[t].dataMatch[i].idxPerdante;
		points[notrejoueuse] = 10;
		notrejoueuse++;
	}
	for (; i < 96; i++) { //dans les 32 prochains matchs les perdantes ont 45 points (64 + 32 = 96)
		Joueuses[notrejoueuse] = ins->dataTournois[t].dataMatch[i].idxPerdante;
		points[notrejoueuse] = 45;
		notrejoueuse++;
	}
	for (; i < 112; i++) { //dans les 16 prochains matchs les perdantes ont 90 points
		Joueuses[notrejoueuse] = ins->dataTournois[t].dataMatch[i].idxPerdante;
		points[notrejoueuse] = 90;
		notrejoueuse++;
	}
	for (; i < 120; i++) { //dans les 8 prochains matchs les perdantes ont 180 points
		Joueuses[notrejoueuse] = ins->dataTournois[t].dataMatch[i].idxPerdante;
		points[notrejoueuse] = 180;
		notrejoueuse++;
	}
	for (; i < 124; i++) { //dans les 4 prochains matchs les perdantes ont 360 points
		Joueuses[notrejoueuse] = ins->dataTournois[t].dataMatch[i].idxPerdante;
		points[notrejoueuse] = 360;
		notrejoueuse++;
	}
	for (; i < 126; i++) { //dans les 2 prochains matchs les perdantes ont 720 points
		Joueuses[notrejoueuse] = ins->dataTournois[t].dataMatch[i].idxPerdante;
		points[notrejoueuse] = 720;
		notrejoueuse++;
	}
	Joueuses[notrejoueuse] = ins->dataTournois[t].dataMatch[i].idxPerdante;
	points[notrejoueuse] = 1200; //la perdante de la finale à 1200 points
	notrejoueuse++;
	Joueuses[notrejoueuse] = ins->dataTournois[t].dataMatch[i].idxGagnante;
	points[notrejoueuse] = 2000; //la gagnante du tournoi à 2000 points
	for (int i = 1; i < nbJoueusesTournoi; ++i)
		if (strcmp(ins->dataJoueuse[Joueuses[i - 1]].nom, ins->dataJoueuse[Joueuses[i]].nom) > 0) {
			Retenu1 = Joueuses[i - 1];
			Retenu2 = points[i - 1];
			Joueuses[i - 1] = Joueuses[i];
			points[i - 1] = points[i];
			Joueuses[i] = Retenu1;
			points[i] = Retenu2;
			i = 0;
		}
	for (int i = 0; i < nbJoueusesTournoi; ++i)
		printf("%s %d\n", ins->dataJoueuse[Joueuses[i]].nom, points[i]);
}

void afficher_classement(TournoiWTA* ins) {
	if (ins->nbTournois == 0) printf("pas de classement");
	int tab[maxTournois * nbJoueusesTournoi];
	int i, h, idxGagnante, idxPerdante;
	unsigned int onRetient, j, elemTableau, Valsuperieur;
	for (j = 0; j < ins->idxJ; ++j)
		tab[j] = j;
	for (j = 0; j < ins->idxJ; ++j) {
		Valsuperieur = j;
		for (elemTableau = j; elemTableau < ins->idxJ; ++elemTableau) {
			if (ins->dataJoueuse[tab[Valsuperieur]].points < ins->dataJoueuse[tab[elemTableau]].points) { //si les joueuses ne sont pas trie par leur point de façon decroissante
				Valsuperieur = elemTableau;
			}
			if (ins->dataJoueuse[tab[Valsuperieur]].points == ins->dataJoueuse[tab[elemTableau]].points) {
				if (strcmp(ins->dataJoueuse[tab[elemTableau]].nom, ins->dataJoueuse[tab[Valsuperieur]].nom) < 1) { // si deux joueuses ont le meme nombre de points mais ne sont pas trie en ordre alphabetque
					Valsuperieur = elemTableau;
				}
			}
		}//trieur
		onRetient = tab[j];
		tab[j] = tab[Valsuperieur];
		tab[Valsuperieur] = onRetient;
	}
	for (i = 0; i < ins->idxJ; ++i)
		printf("%s %d\n", ins->dataJoueuse[tab[i]].nom, ins->dataJoueuse[tab[i]].points);//affichage des joueuses par ordre de point décroissant puis alphabétique dans tous les tournois
}

int main() {
	char mot[30];
	TournoiWTA ins; //creation du tournoi generale du nom de ins
	ins.idxJ = 0; //mise en valeur des indices des joueuses
	ins.nbTournois = 0; //mise en valeur du nombre de tournoi
	ins.idxT = 0; //mise en valeur de l'indice des tournois
	while (1) {
		scanf("%s", mot);
		if (strcmp(mot, "exit") == 0) exit(0); //si le mot exit est tape, alors le programme s'arrete
		else if (strcmp(mot, "definir_nombre_tournois") == 0) {//si le mot definir_nombre_tournois est tape, alors la fonction de definition du nombre de tournoi s'execute
			definir_nombre_tournois(&ins);
		}
		else if (strcmp(mot, "enregistrement_tournoi") == 0) {//si le mot enregistrement_tournoi est tape, alors la fonction d'enregistrement tournoi s'execute
			enregistrement_tournoi(&ins);
		}
		else if (strcmp(mot, "affichage_matchs_tournoi") == 0) {//si le mot affichage_matchs_tournoi est tape, alors on affiche les matchs et leurs deroulement
			affichage_matchs_tournoi(&ins);
		}
		else if (strcmp(mot, "afficher_matchs_joueuse") == 0) {//si le mot afficher_matchs_joueuse est tape, alors on affiche tous les matchs d'une joueuse lors d'un tournoi
			afficher_matchs_joueuse(&ins);
		}
		else if (strcmp(mot, "affichage_joueuses_tournoi") == 0) {//si le mot affichage_joueuses_tournoi est tape, alors un classement de point sera affiché par ordre alphabetique
			affichage_joueuses_tournoi(&ins);
		}
		else if (strcmp(mot, "afficher_classement") == 0) {//si le mot afficher_classement est tape, alors on affiche les points par ordre décroissant et leurs noms par ordre alphabétique si leurs points sont egaux
			afficher_classement(&ins);
		}
	}
	system("pause"); return 0;
}
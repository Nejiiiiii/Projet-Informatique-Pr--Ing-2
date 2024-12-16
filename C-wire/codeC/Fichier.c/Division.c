#include <stdio.h>
#include <stdlib.h>

// Fonction pour remplacer les caractères '-' par '0' dans une chaîne
void RemplacerTiretParZero(char *ligne){
    //Boucle pour parcourir la ligne
    for( int i=0; ligne[i]!='\0'; i++){
        //Condition si on tombe sur un caractère '-' on le change par '0'
        if (ligne[i]=='-'){
            ligne[i]='0';
        }
    }
}
//Fonction pour compter le nombre de lignes dans un fichier
int CompterLignes(FILE *entree){
    int n=0; //n pour le nombre de ligne
    char ligne[2000]; //Chaîne pour chaque ligne
    //Boucle pour parcourir toutes les lignes jusqu'à la fin du fichier et incrémenter n de 1 à chaque fois
    while (fgets(ligne, sizeof(ligne), entree)!=NULL){
        n=n+1;
    }
    rewind(entree);//Retour au début du fichier
    return n;
}

//Fonction pour diviser le fichier CSV en 9 parties
void DivisionCSV(char *argv[]) {
    char ligne[2000]; //Chaîne pour récupérer chaque ligne
    int nbFichier=1; //Numéro du fichier en sortie
    FILE *entree=fopen(argv[1], "r"); //Ouverture du fichier d'entrée en mode lecture
    //Condition si l'ouverture du fichier d'entrée échoue
    if (entree==NULL){  fichier d'entrée\n");
        exit(1);  
    }
    //Appel de CompterLignes(entree) pour compter le nombre total de lignes dans le fichier
    int totalLignes=CompterLignes(entree);
    //Condition si le fichier d'entrée est vide
    if (totalLignes<=1){
        printf("Le fichier est vide ou ne contient pas assez de données.\n");
        fclose(entree);
        exit(1);
    }
    fgets(ligne, sizeof(ligne), entree); //Appel de fgets pour lire et ignorer l'en-tête
    //Pour calculer le nombre de lignes par fichier sachant qu'on souhaite crée 9 fichier de sortie en excluant l'entete
    int lignesParFichier=(totalLignes-1+8)/9;
    FILE *sortie=NULL; //Initialisation du fichier de sortie
    int nbligne=0;// Nombre de lignes écrites dans le fichier courant
    //Boucle pour parcourir toutes les lignes jusqu'à la fin du fichier
    while (fgets(ligne, sizeof(ligne), entree)!=NULL){
        RemplacerTiretParZero(ligne); //Pour remplacer les tirets par des zéros
        //Condition si on a atteint le nombre de ligne max par fichier et si on est au premier au fichier de sortie  
        if(nbligne%lignesParFichier==0){
            //Condition si le fichier de sortie actuel n'est pas fermé
            if(sortie!=NULL){
                fclose(sortie); //On ferme le fichier de sortie actuel
            }
            char SortieNom[50]; //Chaîne pour le nom du fichier de sortie
            snprintf(SortieNom, 50, "C-wire/tmp/%s_%d.csv", "Data", nbFichier); //Pour créer le nom du fichier de sortie en fonction du numéro du fichier de sortie
            sortie=fopen(SortieNom, "w"); //Ouverture du fichier de sortie
            //Condition si l'ouverture du fichier de sortie échoue
            if(sortie==NULL){
                printf("Erreur lors de l'ouverture du fichier de sortie\n");
                fclose(entree); //Fermeture du fichier d'entrée
                exit(1);
            }
            nbFichier=nbFichier+1; //On incrémente de 1 le nombre de fichier
        }
        fputs(ligne, sortie); //On insére la ligne dans le fichier de sortie actuel
        nbligne=nbligne+1; //On incrémente de 1 le nombre de lignes
    }
    //Condition si le dernier fichier de sortie n'est pas fermé
    if (sortie!=NULL) {
        fclose(sortie); //Fermeture du dernier fichier de sortie
    }
    fclose(entree); //Fermeture du fichier d'entrée
}


int main(int argc, char *argv[]){
    //Condition si le nombre d'arguments n'est pas respecté
    if (argc != 2) {
        printf("Erreur : problème d'arguments\n");
        exit(1);
    }
    //Appel de la fonction de division du fichier d'entrée en 9 fichiers
    DivisionCSV(argv);
    return 0;
}




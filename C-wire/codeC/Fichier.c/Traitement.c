#include <stdio.h>
#include <stdlib.h>
#include "AVL.h"

//Fonction de traitement de fichier csv
pAVL TraitementFichier(char *argv[], int n, pAVL a, int *h, int station, int consommateur, int idcentrale1){
    int idcentrale; //Valeur pour l identifiant de la centrale
    int idhvb; //Valeur pour l identifiant de la station hvb
    int idhva;//Valeur pour l identifiant de la station hva
    int idlv;//Valeur pour l identifiant du poste lv
    int capa; //Valeur pour la capacité de la station
    int conso; //Valeur pour la consommation des clients
    int idcomp; //Valeur pour l identifiant de l'entreprise
    int idindiv;//Valeur pour l identifiant du particulier
    FILE *entree=fopen(argv[n], "r"); //Ouverture fichier .csv d entrée en mode lecture, l'ouverture du fichier d'entrée a déjà été vérifié dans le main
    //Boucle de lexture du fichier csv ligne par ligne, en récupérant chaques valeurs et insertion dans l'AVL en fonction du traitement
    while (fscanf(entree, "%d;%d;%d;%d;%d;%d;%d;%d",&idcentrale,  &idhvb ,&idhva, &idlv, &idcomp, &idindiv, &capa, &conso)==8){
        //Condition si la lecture des lignes du fichier d'entrée échoue
        if (ferror(entree)){
            printf("Erreur : problème lecture fichier csv\n");
            exit(1);
        }
        //Condition si on effectue un traitement en fonction d'un id de centrale
        if(idcentrale1!=0){
            //Condition si on effectue un traitement en fonction de la station hvb
            if(station==1){
                //Condition pour récupérer les données des lignes correspondantes
                if(idcentrale==idcentrale1 && idhvb!=0 && idhva==0){
                    a=insertionAVLID(a, idhvb , capa, conso, h);
                }
            }
            else{
              //Condition si on effectue un traitement en fonction de la station hva
              if(station==2){
                  //Condition pour récupérer les données des lignes correspondantes
                  if(idcentrale==idcentrale1 && idhva!=0 && idlv==0){
                      a=insertionAVLID(a, idhva , capa, conso, h);
                  }
              }
              else{
                //Condition si on effectue un traitement en fonction de la station lv
                if(station==3){
                    //Condition si on effectue un traitement en fonction du consommateur entreprise
                    if(consommateur==1){
                        //Condition pour récupérer les données des lignes de capacité
                        if(idcentrale==idcentrale1 && idlv!=0 && idcomp==0 && idindiv==0){
                            a=insertionAVLID(a, idlv , capa, conso, h);
                        }
                        else{
                            //Condition pour récupérer les données des lignes de consommation
                            if(idcentrale==idcentrale1 && idlv!=0 && idcomp!=0 && idindiv==0){
                                a=insertionAVLID(a, idlv ,capa , conso, h);
                            }
                        }
                    }
                    else{
                      //Condition si on effectue un traitement en fonction du consommateur particulier
                      if(consommateur==2){
                          //Condition pour récupérer les données des lignes de capacité
                          if(idcentrale==idcentrale1 && idlv!=0 && idcomp==0 && idindiv==0){
                              a=insertionAVLID(a, idlv , capa, conso, h);
                          }
                          else{
                              //Condition pour récupérer les données des lignes de consommation
                              if(idcentrale==idcentrale1 &&  idlv!=0 && idcomp==0 && idindiv!=0){
                                  a=insertionAVLID(a, idlv ,capa , conso, h);
                              }
                          }
                      }
                      else{
                        //Condition si on effectue un traitement en fonction de tout les consommateurs
                        if(consommateur==3){
                            //Condition pour récupérer les données des lignes correspondantes
                            if(idcentrale==idcentrale1 &&  idlv!=0){
                                a=insertionAVLID(a, idlv , capa, conso, h);
                            }
                        }
                      }
                    }
                }
              }
            }
        }
        //Condition si on n'effectue pas un traitement en fonction d'un id de centrale
        else{
            //Condition si on effectue un traitement en fonction de la station hvb
            if(station==1){
                //Condition pour récupérer les données des lignes correspondantes
                if(idhvb!=0 && idhva==0){
                    a=insertionAVLID(a, idhvb , capa, conso, h);
                }
            }
            else{
              //Condition si on effectue un traitement en fonction de la station hva
              if(station==2){
                  //Condition pour récupérer les données des lignes correspondantes
                  if(idhva!=0 && idlv==0){
                      a=insertionAVLID(a, idhva , capa, conso, h);
                  }
              }
              else{
                //Condition si on effectue un traitement en fonction de la station lv
                if(station==3){
                    //Condition si on effectue un traitement en fonction du consommateur entreprise
                    if(consommateur==1){
                        //Condition pour récupérer les données des lignes de capacité
                        if(idlv!=0 && idcomp==0 && idindiv==0){
                            a=insertionAVLID(a, idlv , capa, conso, h);
                        }
                        else{
                            //Condition pour récupérer les données des lignes de consommation
                            if(idlv!=0 && idcomp!=0 && idindiv==0){
                                a=insertionAVLID(a, idlv ,capa , conso, h);
                            }
                        }
                    }
                    else{
                      //Condition si on effectue un traitement en fonction du consommateur particulier
                      if(consommateur==2){
                          //Condition pour récupérer les données des lignes de capacité
                          if(idlv!=0 && idcomp==0 && idindiv==0){
                              a=insertionAVLID(a, idlv , capa, conso, h);
                          }
                          else{
                              //Condition pour récupérer les données des lignes de consommation
                              if(idlv!=0 && idcomp==0 && idindiv!=0){
                                  a=insertionAVLID(a, idlv ,capa , conso, h);
                              }
                          }
                      }
                      else{
                        //Condition si on effectue un traitement en fonction de tout les consommateurs
                        if(consommateur==3){
                            //Condition pour récupérer les données des lignes de consommation
                            if(idlv!=0){
                                a=insertionAVLID(a, idlv , capa, conso, h);
                            }
                        }
                      }
                    }
                }
              }
            }
        }
    }
    fclose(entree);//Fermeture du fichier .csv d entree 
    return a;
}

//Fonction d écritures des valeurs de l'AVL dans le fichier de sortie
void EcrireSortie(FILE* sortie, pAVL a){
    if (a!=NULL) {
        EcrireSortie(sortie, a->gauche);
        fprintf(sortie, "%d;%d;%d\n", a->s.id,  a->s.capa, a->s.conso); //Pour remplir une ligne du fichier de sortie
        EcrireSortie(sortie, a->droit);
        }
}

int main(int argc, char *argv[]){
    pAVL a=NULL; //Initialisation de l'AVL
    int h1=0; //Initialisation de la hauteur de l'AVL
    int station;// valeur pour connaitre la station à traiter =1 pour hvb, =2 pour hva, =3 pour lv
    int consommateur; //valeur pour connaitre le consommateur à traiter =1 pour comp, =2 pour indiv, =3 pour all
    int idcentrale; //s'il est renseigné valeur pour trier selon une centrale
    //Condition pour vérifier que le nombre d'arguments est correct sinon erreur
    if (argc!=13) { // 9 fichiers CSV + 1 argument station + 1 argument consommateur + 1 argument idcentrale
        printf("Erreur : problème d'arguments\n");
        exit(1);
    }
    station=atoi(argv[10]); //Récupération de la valeur de la station depuis les arguments
    consommateur=atoi(argv[11]); //Récupération de la valeur de consommateur depuis les arguments
    idcentrale=atoi(argv[12]); //Récupération de la valeur d'id de centrale depuis les arguments
    //Traitement des 9 fichiers .csv et remplissage de l'AVL en fonction des id de stations
    for(int i=1; i<10; i++){
        //Condition si l'ouverture du fichier d'entrée échoue
        if (fopen(argv[i], "r")==NULL){
            printf("Erreur lors de l'ouverture du fichier d'entrée");
            exit(1);
        }
        //Appel de TraitementFichier() pour remplir l'AVL en fonction du fichier à traiter, de l'id de station de traiter, du consommateur à traiter et de l'id centrale à traiter (si =0 pas à traiter en fonction de l'id de centrale
        a=TraitementFichier( argv, i, a, &h1, station,consommateur, idcentrale );
    }
    //Ouverture du fichier de sortie 
    FILE *sortie=fopen("C-wire/tmp/Output.csv", "w");
    //Condition si l'ouverture du fichier de sortie échoue
    if (sortie==NULL){
        printf("Erreur lors de l'ouverture du fichier de sortie");
        libererAVL(a); //Fonction pour libérer l AVL
        exit(1);
    }
    //Remplissage du fichier de sortie avec les données de l'AVL
    EcrireSortie(sortie, a);
    fclose(sortie); //Fermeture du fichier de sortie
    libererAVL(a); //Fonction pour libérer l AVL
    return 0;
}


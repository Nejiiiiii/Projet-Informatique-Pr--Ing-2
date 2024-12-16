#include <stdio.h>
#include <stdlib.h>

//Definition de la structure Station
typedef struct Station{
    int id;//contient l'id de la station
    int capa;//contient la capacité de la station
    int conso;//contient la somme des consommations des consommateurs de la station
} Station;

//Definition de la structure AVL
typedef struct AVL{
    Station s;
    struct AVL*droit;
    struct AVL*gauche;
    int e;
}AVL;

//Definition du pointeur AVL
typedef struct AVL *pAVL;

//Fonction qui retourne le max entre deux valeurs
int max(int a, int b){
    if(a>=b){
        return a;
    }
    else{
        if(a<b){
            return b;
        }
        else{
            exit(0);
        }
    }
}

//Fonction qui retourne le min entre deux valeurs
int min(int a, int b){
    if(a>=b){
        return b;
    }
    else{
        if(a<b){
            return a;
        }
        else{
            exit(0);
        }
    }
}

//Fonction qui retourne le min entre trois valeurs
int minbis(int a, int b, int c){
    int k;
    k=min(a,b);
    k=min(k,c);
    return k;
}

//Fonction qui retourne le max entre trois valeurs
int maxbis(int a, int b, int c){
    int k;
    k=max(a,b);
    k=max(k,c);
    return k;
}

//Fonction de creation AVL
pAVL creerAVL(int id ,int capa,int conso){
    pAVL p;
    p=malloc(sizeof(AVL));
    if(p==NULL){
       printf("Erreur : allocation AVL\n");
       exit(1);
    }
    else{
       p->s.id=id;
       p->s.capa=capa;
       p->s.conso=conso;
       p->droit=NULL;
       p->gauche=NULL;
       p->e=0;
    }
    return p;
}

//Fonction RotationGauche AVL
pAVL RotationGauche(pAVL a){
    if (a==NULL || a->droit==NULL) {
        printf("Erreur : rotation gauche impossible. a ou a->droit est NULL.\n");
        exit(1);
    }
    pAVL pivot=NULL;
    int eq_a, eq_p;
    pivot=a->droit;
    a->droit=pivot->gauche;
    pivot->gauche=a;
    eq_a=a->e;
    eq_p=pivot->e;
    a->e=eq_a-max(eq_p,0)-1;
    pivot->e=minbis(eq_a-2,eq_a+eq_p-2,eq_p-1);
    a=pivot;
    return a;
}

//Fonction RotationDroite AVL
pAVL RotationDroite(pAVL a){
    if (a==NULL || a->gauche==NULL) {
        printf("Erreur : rotation droite impossible. a ou a->gauche est NULL.\n");
        exit(1);
    }
    pAVL pivot=NULL;
    int eq_a, eq_p;
    pivot=a->gauche;
    a->gauche=pivot->droit;
    pivot->droit=a;
    eq_a=a->e;
    eq_p=pivot->e;
    a->e=eq_a-min(eq_p,0)+1;
    pivot->e=maxbis(eq_a+2,eq_a+eq_p+2,eq_p+1);
    a=pivot;
    return a;
}

//Fonction DoubleRotationDroite AVL
pAVL DoubleRotationDroite(pAVL a){
    a->gauche=RotationGauche(a->gauche);
    return RotationDroite(a);
}

//Fonction DoubleRotationGauche AVL
pAVL DoubleRotationGauche(pAVL a){
    a->droit=RotationDroite(a->droit);
    return RotationGauche(a);
}

//Fonction d equilibrage AVL
pAVL equilibrageAVL(pAVL a){
    if (a==NULL) {
        printf("Erreur : tentative d'équilibrage sur un nœud NULL.\n");
        exit(1);
    }
    if(a->e>=2){
        if (a->droit==NULL) {
            printf("Erreur : nœud droit manquant pour une rotation gauche.\n");
            exit(1);
        }
        if(a->droit->e>=0){
            return RotationGauche(a);
        }
        else{
            return DoubleRotationGauche(a);    
        }
    }
    else{
        if(a->e<=-2){
            if (a->gauche==NULL) {
                printf("Erreur : nœud gauche manquant pour une rotation droite.\n");
                exit(1);
            }
            if(a->gauche->e<=0){
                return RotationDroite(a);
            }
            else{
                return DoubleRotationDroite(a);    
            }
        }
    }
    return a;
}

//Fonction d'insertion de l'AVL en fonction de l id
pAVL insertionAVLID(pAVL a,int id ,int capa,int conso, int *h){
    pAVL p=NULL;
    if(a==NULL){
        *h=1;
        p=creerAVL(id, capa, conso);
        return p;
    }
    else{
        //Condition pour faire la somme des consommations des consommateurs
        if(a->s.id==id){
           a->s.conso=a->s.conso+conso; 
	   a->s.capa=a->s.capa+capa;
	   *h=0;
        }
        else{
           if(a->s.id>id){
              a->gauche=insertionAVLID(a->gauche, id , capa , conso , h);
              *h=-*h;
           }
           else{
              if(a->s.id<id){
                 a->droit=insertionAVLID(a->droit, id , capa , conso , h);
              }
              else{
                 *h=0;
                 return a;
              }
           }
        }
     }
     if(*h!=0){
        a->e=a->e+*h;
        a=equilibrageAVL(a);
        if(a->e==0){
            *h=0;
        }
        else{
           *h=1;
        }
    }
    return a;
}

//Fonction de liberation d AVL
void libererAVL(pAVL a){
    if (a==NULL){
        return;
    }
    libererAVL(a->gauche);
    libererAVL(a->droit);
    free(a);
}


#ifndef H_A
#define H_A
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
int max(int a, int b);
//Fonction qui retourne le min entre deux valeurs
int min(int a, int b);
//Fonction qui retourne le min entre trois valeurs
int minbis(int a, int b, int c);
//Fonction qui retourne le max entre trois valeurs
int maxbis(int a, int b, int c);
//Fonction de creation AVL
pAVL creerAVL(int id , int capa, int conso);
//Fonction RotationGauche AVL
pAVL RotationGauche(pAVL a);
//Fonction RotationDroite AVL
pAVL RotationDroite(pAVL a);
//Fonction DoubleRotationDroite AVL
pAVL DoubleRotationDroite(pAVL a);
//Fonction DoubleRotationGauche AVL
pAVL DoubleRotationGauche(pAVL a);
//Fonction d equilibrage AVL
pAVL equilibrageAVL(pAVL a);
//Fonction d'insertion de l'AVL en fonction de l id
pAVL insertionAVLID(pAVL a,int id ,int capa,int conso, int *h);
//Fonction de liberation d AVL
void libererAVL(pAVL a);
#endif


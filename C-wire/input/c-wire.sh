#!/bin/bash

#Fonction pour afficher le message d'aide
function afficher_aide() {
    echo ""
    echo "Commande à saisir:"
    echo "./<Chemin c-wire.sh> <type de station à traiter> <type de consommateur à traiter> <facultatif: Identifiant de centrale (nombre entier)>"
    echo ""
    echo "Stations disponibles:"
    echo "-hvb"
    echo "-hva"
    echo "-lv"
    echo ""
    echo "Consommateurs disponibles:"
    echo "-comp"
    echo "-indiv"
    echo "-all"
    echo ""
    echo "Exemples de saisies de commande:"
    echo "./C-wire/c-wire.sh hvb comp"
    echo "./C-wire/c-wire.sh lv all 1"
    echo ""
    echo "Attention commandes impossibles:"
    echo "./<Chemin c-wire.sh> hvb all"
    echo "./<Chemin c-wire.sh> hva all"
    echo "./<Chemin c-wire.sh> hva indiv"
    echo "./<Chemin c-wire.sh> hvb indiv"
    echo ""
}

#Pour parcourir les arguments
for ((i=1; i<5; i++)); do
    #Condition si un argument ="-h"
    if [ "${!i}" = "-h"  ]; then
        afficher_aide #afficher aide
        exit 1
    fi
done

#Condition si le nombre d'arguments est incorrect, supérieur à 3 ou inférieur à 2
if [ "$#" -lt 2 ] || [ "$#" -gt 3 ]; then
    #Condition si le nombre d'arguments inférieur à 2, pas assez d'arguments
    if [ "$#" -lt 2 ]; then
        echo "Erreur : Pas assez d'arguments"
    #sinon trop d'arguments
    else
        echo "Erreur : Trop d'arguments"
    fi
    afficher_aide #afficher aide
    exit 1
fi

#Condition si l'argument 1 du code shell fournit est incorrect ( différent de hvb et hva et lv) erreur
if [[ "$1" != "hvb" && "$1" != "hva" && "$1" != "lv" ]]; then
    echo "Erreur : Type de station non valide ($1)"
    afficher_aide #Affichage de l'aide
    exit 1
fi

#Condition si l'argument 2 du code shell fournit est incorrect ( différent de comp et indiv et all) erreur
if [[ "$2" != "comp" && "$2" != "indiv" && "$2" != "all" ]]; then
    echo "Erreur : Type de consommateur non valide ($2)"
    afficher_aide #Affichage de l'aide
    exit 1
fi

#Condition si on cherche à réaliser un traitement impossible, une combinaison interdite, erreur (traitement hvb_indiv, hva_indiv, hvb_all et hva_all impossible)
if [[ ("$1" = "hvb" || "$1" = "hva") && ("$2" = "all" || "$2" = "indiv") ]]; then
    echo "Erreur : Combinaison station/consommateur impossible ($1 / $2)"
    afficher_aide #Affichage de l'aide
    exit 1
fi

#Condition si l'argument 3 du script shell n'est pas fournis, on l'initialise à 0 et il ne sera pas pris en compte dans la suite
if [ -z "$3" ]; then
    set -- "$1" "$2" 0 "${@:4}"  #Initialisation de l'argument 3 = 0
#sinon si l'argument 3 du script shell est fournis
else
    #Condition si l'argument 3 du script shell est un caractère et non un entier erreur
    if ! [[ "$3" =~ ^[0-9]+$ ]]; then
        echo ""
        echo "Erreur : L'identifiant de la centrale doit être un entier."
        echo ""
        afficher_aide #Affichage de l'aide
        exit 1
    fi
    #Condition si l'argument 3 du script shell est supérieur à 5 ou inférieur à 1 erreur
    if [ "$3" -lt 0 ] || [ "$3" -gt 5 ]; then
        echo ""
        echo "Erreur : Id centrale incorrect, il n'existe que 5 centrales (0 à 5)."
        echo ""
        afficher_aide #Affichage de l'aide
        exit 1
    fi
fi

#Condition si les dossiers codeC, gnuplot, input n'existent pas erreur
if [ ! -d C-wire/codeC ] || [ ! -d C-wire/gnuplot ] || [ ! -d C-wire/input ] ; then
    #Condition si le dossier gnuplot n'existe pas erreur, dossier gnuplot manquant
    if [ ! -d C-wire/gnuplot ]; then
    	echo ""
    	echo "Erreur : dossier gnuplot manquant"
    	echo ""
    #Condition si le dossier codeC n'existe pas erreur, dossier codeC manquant
    elif [ ! -d C-wire/codeC ]; then
    	echo ""
    	echo "Erreur : dossier codeC manquant"
    	echo ""
    #Condition si le dossier input n'existe pas erreur, dossier input manquant
    elif [ ! -d C-wire/input ]; then
    	echo ""
    	echo "Erreur : dossier input manquant"
    	echo ""
    fi
    exit 1
fi

#Condition si le fichier code gnuplot lv_all_minmax.gp n'existe pas erreur
if [ ! -f C-wire/gnuplot/lv_all_minmax.gp ]; then
    echo ""
    echo "Erreur : lv_all_minmax.gp manquant"
    echo ""
    exit 1
fi

#Condition si le dossier Fichier.c et Fichier.h n'existent pas erreur
if [ ! -d C-wire/codeC/Fichier.c ] || [ ! -d C-wire/codeC/Fichier.h ] ; then
    #Condition si le dossier Fichier.c n'existe pas erreur, dossier Fichier.c manquant
    if [ ! -d C-wire/codeC/Fichier.c ]; then
    	echo ""
    	echo "Erreur : dossier Fichier.c manquant"
    	echo ""
    #Condition si le dossier Fichier.h n'existe pas erreur, dossier Fichier.h manquant
    elif [ ! -d C-wire/codeC/Fichier.h ]; then
    	echo ""
    	echo "Erreur : dossier Fichier.h manquant"
    	echo ""
    fi
    exit 1
fi

#Condition si les fichiers des codes .c et codes .h n'existent pas erreur
if [ ! -f C-wire/codeC/Fichier.c/AVL.c ] || [ ! -f C-wire/codeC/Fichier.c/Division.c ] || [ ! -f C-wire/codeC/Fichier.c/Traitement.c ] || [ ! -f C-wire/codeC/Fichier.h/AVL.h ] ; then
    #Condition si le fichier AVL.c n'existe pas erreur, fichier AVL.c manquant
    if [ ! -f C-wire/codeC/Fichier.c/AVL.c ]; then
    	echo ""
    	echo "Erreur : fichier programme AVL.c manquant"
    	echo ""
    #Condition si le fichier Division.c n'existe pas erreur, fichier Division.c manquant
    elif [ ! -f C-wire/codeC/Fichier.c/Division.c  ]; then
    	echo ""
    	echo "Erreur : fichier programme Division.c manquant"
    	echo ""
    #Condition si le fichier Traitement.c n'existe pas erreur, fichier Traitement.c manquant
    elif [ ! -f C-wire/codeC/Fichier.c/Traitement.c ]; then
    	echo ""
    	echo "Erreur : fichier programme Traitement.c manquant"
    	echo ""
    #Condition si le fichier AVL.h n'existe pas erreur, fichier AVL.h manquant
    elif [ ! -f C-wire/codeC/Fichier.h/AVL.h ]; then
    	echo ""
    	echo "Erreur : fichier programme AVL.h manquant"
    	echo ""
    fi
    exit 1
fi



#Condition si le dossier tmp n'existe pas création du dossier, si il existe on le vide de ses données avant execution des traitements
if [ ! -d C-wire/tmp ]; then
    mkdir C-wire/tmp #Pour crée le fichier tmp s'il n'existe pas
else
    rm -rf C-wire/tmp/* #Pour vider le fichier tmp s'il existe 
fi

#Condition si le dossier graphs n'existe pas, creation du dossier graphs
if [ ! -d C-wire/graphs ]; then
    mkdir C-wire/graphs #commande création du fichier graphs
fi

#Pour récupérer la liste de tout les fichiers .csv dans le dossier input
csv_files=(C-wire/input/*.csv)
#Création d'un tableau pour stocker les fichiers csv
existing_csv_files=()
#Pour parcourir la liste des fichiers .csv et les ajouter au tableau
for file in "${csv_files[@]}"; do
    if [ -f "$file" ]; then
        existing_csv_files+=("$file")
    fi
done

#Condition s'il n'existe aucun fichier .csv dans le dossier input erreur
if [ ${#existing_csv_files[@]} -eq 0 ]; then
    echo ""
    echo "Erreur : Aucun fichier CSV trouvé dans le dossier 'input'."
    echo ""
    exit 1
#Condition s'il existe plus d'un fichier .csv dans le dossier input erreur
elif [ ${#existing_csv_files[@]} -gt 1 ]; then
    echo ""
    echo "Erreur : Plusieurs fichiers CSV trouvés dans le dossier 'input' :"
    #Parcourt du tableau
    for file in "${existing_csv_files[@]}"; do
        echo "  - $file" #affichage des fichiers un par un
    done
    echo ""
    exit 1
fi

#Condition si les fichiers des programmes compilés n'existent pas, la compilation est faite si le Makefile existe, sinon erreur
if [ ! -f C-wire/codeC/Division ] || [ ! -f C-wire/codeC/Traitement ]; then
    #Condition si le fichier Makefile n'existe pas erreur
    if [ ! -f C-wire/codeC/Makefile ]; then
    	echo ""
    	echo "Erreur : fichier Makefile manquant"
    	echo ""
    	exit 1
    fi
    make -C C-wire/codeC #Lancement de la commande de compilation
    #Condition pour vérifier que la compilation n'a pas échoué, vérifie si la commande s'est exécutée avec succès, récupére le code retour de la commande (=0 si la commande s'est exécutée avec succès)
    if [ $? -ne 0 ]; then
        echo "Erreur : La compilation a échoué."
        exit 1
    fi
fi

#Traitement en fonction des arguments station, consommateur, id centrale
#Lancement du chronometre
start_time=$(date +%s)
echo "Traitement en cours"
#Utilisaton d'un progc pour diviser le fichier csv en plusieurs parties pour une meilleure gestion mémoire
C-wire/codeC/Division ${existing_csv_files[0]}
#Condition pour vérifier que l'exécution du code C n'a pas échoué, vérifie si le code s'est exécutée avec succès, récupére le code retour du code (=0 si le code s'est exécutée avec succès sinon =1)
if [ $? -ne 0 ]; then
   echo "Erreur : Le traitement a échoué."
   exit 1
fi
#Utilisaton du code pour trier les fichiers csv en fonction des arguments
if [ "${1}" = "hvb"  ] && [ "${2}" = "comp"  ] ; then #Traitement hvb_comp
   C-wire/codeC/Traitement C-wire/tmp/Data_{1..9}.csv 1 1 $3 #appel du code C en fonction des argument dans l'ordre : argument 1 à 9 = "C-wire/tmp/Data_{1..9}.csv" pour les fichiers à traiter, argument 10="1" pour préciser la station hvb, argument 11="1" pour préciser le consommateur comp, argument 12="$3" pour préciser le numéro de centrale si =0 non pris en compte
   #Condition pour vérifier que l'exécution du code C n'a pas échoué, vérifie si le code s'est exécutée avec succès, récupére le code retour du code (=0 si le code s'est exécutée avec succès sinon =1)
    if [ $? -ne 0 ]; then
        echo "Erreur : Le traitement a échoué."
        exit 1
    fi
elif [ "${1}" = "hva"  ] && [ "${2}" = "comp"  ] ; then #Traitement hva_comp
   C-wire/codeC/Traitement C-wire/tmp/Data_{1..9}.csv 2 1 $3 #appel du code C en fonction des argument dans l'ordre :argument 1 à 9 = "C-wire/tmp/Data_{1..9}.csv" pour les fichiers à traiter, argument 10="2" pour préciser la station hva, argument 11="1" pour préciser le consommateur comp, argument 12="$3" pour préciser le numéro de centrale si =0 non pris en compte
   #Condition pour vérifier que l'exécution du code C n'a pas échoué, vérifie si le code s'est exécutée avec succès, récupére le code retour du code (=0 si le code s'est exécutée avec succès sinon =1)
    if [ $? -ne 0 ]; then
        echo "Erreur : Le traitement a échoué."
        exit 1
    fi
elif [ "${1}" = "lv"  ] && [ "${2}" = "comp"  ] ; then #Traitement lv_comp
   C-wire/codeC/Traitement C-wire/tmp/Data_{1..9}.csv 3 1 $3 #appel du code C en fonction des argument dans l'ordre : argument 1 à 9 = "C-wire/tmp/Data_{1..9}.csv" pour les fichiers à traiter, argument 10="3" pour préciser la station lv, argument 11="1" pour préciser le consommateur comp, argument 12="$3" pour préciser le numéro de centrale si =0 non pris en compte
   #Condition pour vérifier que l'exécution du code C n'a pas échoué, vérifie si le code s'est exécutée avec succès, récupére le code retour du code (=0 si le code s'est exécutée avec succès sinon =1)
    if [ $? -ne 0 ]; then
        echo "Erreur : Le traitement a échoué."
        exit 1
    fi
elif [ "${1}" = "lv"  ] && [ "${2}" = "indiv"  ] ; then #Traitement lv_indiv
   C-wire/codeC/Traitement C-wire/tmp/Data_{1..9}.csv 3 2 $3 #appel du code C en fonction des argument dans l'ordre : argument 1 à 9 = "C-wire/tmp/Data_{1..9}.csv" pour les fichiers à traiter, argument 10="3" pour préciser la station lv, argument 11="2" pour préciser le consommateur indiv, argument 12="$3" pour préciser le numéro de centrale si =0 non pris en compte
   #Condition pour vérifier que l'exécution du code C n'a pas échoué, vérifie si le code s'est exécutée avec succès, récupére le code retour du code (=0 si le code s'est exécutée avec succès sinon =1)
    if [ $? -ne 0 ]; then
        echo "Erreur : Le traitement a échoué."
        exit 1
    fi
elif [ "${1}" = "lv"  ] && [ "${2}" = "all"  ] ; then #Traitement lv_all
   C-wire/codeC/Traitement C-wire/tmp/Data_{1..9}.csv 3 3 $3 #appel du code C en fonction des argument dans l'ordre : dans argument 1 à 9 = "C-wire/tmp/Data_{1..9}.csv" pour les fichiers à traiter, argument 10="3" pour préciser la station lv, argument 11="3" pour préciser le consommateur all, argument 12="$3" pour préciser le numéro de centrale si =0 non pris en compte
   #Condition pour vérifier que l'exécution du code C n'a pas échoué, vérifie si le code s'est exécutée avec succès, récupére le code retour du code (=0 si le code s'est exécutée avec succès sinon =1)
    if [ $? -ne 0 ]; then
        echo "Erreur : Le traitement a échoué."
        exit 1
    fi
fi
#Création du fichier final avec le fichier temporaire Output.csv et condition si le traitement est fait en fonction d'un numéro centrale et crée le nom de fichier en fonction d'un numéro centrale 
if [ $3 = 0  ] ; then
   #Si le numéro de centrale n'est pas renseigné 
   echo "ID Station ${1}:Capacité:Consommation ${2}" > C-wire/"${1}"_"${2}".csv #Pour insérer l'entête
   awk -F";" -v OFS=":" '{print $1, $2, $3}' C-wire/tmp/Output.csv | sort -t":" -k2,2n >> C-wire/"${1}"_"${2}".csv #Pour effectuer le tri
   #Condition dans le cas où on réalise le traitement lv_all
   if [ "${1}" = "lv"  ] && [ "${2}" = "all"  ] ; then
      #Création d'un nouveau fichier lv_all_minmax et trie des 10 plus grandes valeurs de Capcité et les 10 plus petites dans l'ordre croissant et création d'un graphique
      sort -t";" -k3,3n C-wire/tmp/Output.csv | (head -n 10; tail -n 10) > C-wire/tmp/Output2.csv #Trie en fonction de la consommation et récupére les 10 postes avec le plus de consommation et les 10 avec le moins
      echo "ID Station ${1}:Capacité:Consommation ${2}:Quantité d’énergie consommée en trop" > C-wire/"${1}"_"${2}"_minmax.csv #Pour insérer l'entête
      awk -F";" '{print $0 ";" $3 - $2}' C-wire/tmp/Output2.csv | sort -t";" -k4,4nr | awk -F";" '{OFS=":"; $4=$3 - $2; print $0}' >> C-wire/"${1}"_"${2}"_minmax.csv #Trie pour la quantité absolue d’énergie consommée en trop
      #Lancement du code gnuplot pour crée le graphique 
      gnuplot -persist -e "load 'C-wire/gnuplot/${1}_${2}_minmax.gp'"
      #Affichage du graphique crée 
      xdg-open C-wire/graphs/"${1}"_"${2}"_minmax.png
   fi
else
   #Si le numéro de centrale est renseigné = changement nom fichier en précisant le numéro de la centrale
   echo "ID Station ${1}:Capacité:Consommation ${2}" > C-wire/"${1}"_"${2}"_"${3}".csv #Pour insérer l'entête
   awk -F";" -v OFS=":" '{print $1, $2, $3}' C-wire/tmp/Output.csv | sort -t":" -k2,2n >> C-wire/"${1}"_"${2}"_"${3}".csv #Pour effectuer le tri
fi
#Fin du chronometre
end_time=$(date +%s)
duration=$((end_time - start_time))
#Affichage de la durée total du traitement
echo "Durée totale du traitement: $duration secondes"

#Pour vider le fichier tmp à la fin du programme shell
rm -rf C-wire/tmp/*











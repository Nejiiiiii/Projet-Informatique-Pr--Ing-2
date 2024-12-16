reset

#Police et taille écriture
set terminal pngcairo enhanced font "Arial,12" size 1200,1000 

#Fichier de sortie
set output 'C-wire/graphs/lv_all_minmax.png'

#Fichier à traiter
set datafile separator ":"
datafile = 'C-wire/lv_all_minmax.csv'

#légende
set title 'lv all minmax : Production des stations et consommation des consommateurs '
set xlabel 'ID Stations'
set ylabel 'Capacité (kWh)'
set xtics rotate by -90

#échelle
set yrange [0:*]

#Désactiver l'affichage en notation scientifique
set format y "%.0f"

#Mettre la légende des barres à l'extérieur du graphique
set key outside

#Style des barres
set style data histograms
set style histogram rowstacked
set style fill solid 1.0 border -1
set boxwidth 0.75

#Tracé des barres empilées
plot datafile every ::1 using 2 lc rgb "#4CBB17" ti "Capacité", '' every ::1 using (($4 >= 0) ? $4 : 0):xtic(1) lc rgb "#ff0000" ti "Energie consommée en trop"

set output






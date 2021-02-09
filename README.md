# Spedition
A program for finding shortest route between cities. 
User needs to provide a file with definied connections between cities, for example:

Szczecin Poznan 220
Szczecin Koszalin 110
Poznan Bytom 300
Poznan Lodz 130
Lodz Katowice 170
Bytom Katowice 15
Bytom Wroclaw 180

Via console user selects starting city, and the program using Dijkstra algorithm
will find shortest path from selected city to all other cities:

Poznan -> Bytom: 300
Poznan -> Lodz -> Katowice: 300
Poznan -> Szczecin -> Koszalin: 330
Poznan -> Lodz: 130
Poznan -> Szczecin: 220
Poznan -> Bytom -> Wroclaw: 480

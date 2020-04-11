# Projet 2i006  
### Partie A

**Exercice 1**

netlist.c netlist.h visunetlist.c visunetlist.h (avec utilisation de SVGwriter.c SVGwriter.h)

Le Makefile créé un executable VisuNetlist qui permet de tracer une instance dans un fichier html.  
Usage : ./VisuNetlist [chemin de l'instance] [longueur] [largeur]  
Avec longueur et largeur les dimensions x et y du graphique en pixels.

**Exercice 2 - Algorithme naïf de recherche des intersections :**

intersection.c intersection.h

**Exercice 3 - Algorithme recherche des intersections par balayage et comparaison des performances :**

balayage.c balayage.h

### Partie B

**Exercice 5
La fonction creer_graphe (graphe.c) créée le graphe associé à un fichier int.
Elle prend un paramètre la netlist associée au fichier int et le nom du fichier int. Le graphe est créée en 3 étapes : les sommets, les arretes de conflits, puis les arretes de continuité. Il a été choisit de ne stocker que les arretes de conflits dans le tableau d’arretes de la structure graphe.


**Exercice 6
via_naif.c, pas de modification de l’énnoncé



*Exercice 7
via_cycle.c

La fonction detecte cycle impair ne renvoie -1 si aucun cycle impair n’est trouvé et l’indice du sommet où un cycle impair est détecté sinon.
Ceci a permit d’éviter d’avoir un tableau_peres erroné dans le cas où il y a un cycle pair imbriqué dans un cycle pair, on perdait alors trace d’un élément du cycle.
En faisant de cette manière, le tableau des peres n’est remplit uniquement si un cycle impair est trouvé, et ceci lors de la dérecursification.



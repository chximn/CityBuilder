# 1. Algorithmes des graphes
	Pour tester les algorithmes, on utilise les instructions graphes ajoutés au langage du CityBuilder:
	A*, Dijkstra, Kruskal, Tarjan, Welsh-Powell

## 1.1 Plus Court Chemin:
	pour trouver le plus court chemin, on fait appel à l'instruction "PCC",
	qui appliquera l'algorithme de A* et celle de Dijkstra,
	et affichera le plus court chemin dans le flux de sortie standard (std::cout)
	ainsi que le temps pris par les deux algorithmes
	on trouve dans le fichier pcc.txt,
	un exemple montrant comment tester l'implementation de ces algorithmes

## 1.2. Arbre Couvrante Minimale:
	pour chercher l'arbre couvrante minimale en utilisant l'algorithme de Kruskal,
	on fait appel à l'instruction "Kruskal",
	qui supprimera les arrete qui font pas partie de l'arbre couvrante minimale
	on trouve dans le fichier kruskal.txt,
	un exemple montrant comment tester l'implementation de l'algorithme de kruskal

## 1.3. Composants Fortement Connexes:
	pour trouver les composants fortement connexes dans le graphe,
	on fait appel à l'instruction "Tarjan", qui appliquera l'algorithme de Tarjan
	et colorera les maisons du meme composant fortement connexe par la meme couleur
	on trouve dans le fichier tarjan.txt,
	un exemple montrant comment tester l'implementation de l'algorithme de Tarjan

## 1.4. K-Coloration:
	pour encadrer le nombre chromatique du graphe, en utilisant l'algorithme de Welsh-Powell,
	on fait appel à l'instruction "Welsh-Powell",
	qui colorera les maisons et affichera l'encadrement du nombre chromatique
	on trouve dans le fichier welsh_powell.txt,
	un exemple montrant comment tester l'implementation de l'algorithme de Welsh-Powell

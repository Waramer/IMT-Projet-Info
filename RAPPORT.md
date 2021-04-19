# Projet Asteroids - D�tection de Collisions
Le projet choisi et de cr�er un jeu d'ast�ro�ds analogue � l'original Asteroids(1979).

## Collaborateurs
Quentin Delezenne
Cl�ment Kieffer
Louis Delacour
Hugo Vanhille

## Retour sur le d�roulement du projet
Le projet a �t� r�alis� sur l'IDE Visual Studio 2019, cod� en C++. Le travail a �t� partag� sir Github et tous les membres de l'�quipe ont eu acc�s � ce d�p�t distant afin de pouvoir travailler dessus.
Tous les membres ont utitlis�s les outils git et github incorpor�s � VS2019 pour la gestion des versions. Il y avait une branche principale pour le rencu du travail, une branche Dev pour la version Work In Progress et enfin, chaque personne avait sa propre branche afin de travailler sans g�ner les autres et afin d'avoir une sauvegarde en ligne de son travail.
La m�thode qui a �t� utilis�e est la suivante : 2 personnes ne travaillent pas sur le m�me fichier, lorsqu'une personne � fini son travail sur sa branche personnelle, elle checkout sur Dev, Pull afin de se mettre � jour, pui fusionne sa branche dans Dev en r�solvant les conflits et en lan�ant le programme au moins une fois pour v�rifier son int�grit�.
Cette m�thode est inspir�e du GitFlow.

## Objectifs
Le premier objectif a �t� de g�n�rer une enveloppe convexe � parti de multiple point, chose qui a �t� faite avec les ast�roides. Les d�tection de collision ont ensuite �t� r�alis�s entre les ast�roides et les autres objects du jeu (joueur et tirs).
Enfin il a �t� question de mettre cela en forme et de cr�er le jeu � proprement parler, avec ses menus, options, l'impl�mentation d'un mod�le arbitraire de difficult� et un peu de design visuel et audio.

## Description du code
### Dans le main
Le main contient actuellement le code pour g�n�rer un �cran, qui est la base du programme.
### Classe Point
Repr�sente un point en 2D, avec des m�thodes classiques � propos des coordonn�es, une fonction pour d�tecter si deux points sont supperpos�s et une fonction pour retourner l'angle (en degr�s) du vecteur entre deux points.
### Classe Asteroid
Repr�sente un ast�roid � partir d'un esemble de points et d'attributs g�om�triques. S'y trouve aussi les attributs et m�thodes utilis�s pour le d�placement d'un asteroid, la cr�ation de son enveloppe et la d�tection d'un point dans son enveloppe.
### Classe Tir
Classe qui repr�snete un tir � partir de coordonn�es et qui contient le n�cessaire � son mouvement.
### Classe Joueur
Repr�sente un joueur avec les donn�es relatives � un joueur.
### Classe OptionMenu
Repr�sente une ligne de menu, s�lectionnable avec le clavier et qui am�ne vers d'autre �cran.
### Classe Jeu
La classe jeu comprend la majorit� des algorithmes n�cessaire au bon d�roulement du jeu. On y trouve notamment les m�thodes de collisions entre asteroids, joueur et tirs. Le principe de base et que le jeu avant de trame en trame grace � une m�thode d'"avancement". Ensuite des m�thodes "rendu" affiche tous les �l�ments graphiques.
### Classe Ecran
Cette classe g�n�re un �cran du jeu, il g�re les diff�rents �crans et appelle la classe jeu afin de lancer une partie.

## Divers
En cas de soucis avec la biblioth�que Raylib, nous avons utilis� ce guide :
https://github.com/raysan5/raylib/wiki/Create-Visual-Studio-2019-Project?fbclid=IwAR0bYCk1tebgWyAz46kFeC1OHeDOgAmbQe1RciptH8lFvHH349vEQqWsxXM
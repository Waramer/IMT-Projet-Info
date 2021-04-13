# Projet Asteroids - Détection de Collisions
Le projet choisi et de créer un jeu d'astéroïds analogue à l'original Asteroids(1979). La détection de collision sera alors utilisée pour détecter si un astéroïd touhera le vaisseau ou quand un tir touche un astéroïd pour le détruire. Nous codons en C++ avec Virtual Studio 2019.

## Collaborateurs
Quentin Delezenne
Clément Kieffer
Louis Delacour
Hugo Vanhille

## Decription du programme
Le programme démarre sur un menu d'acceuil dans lequel il est possible d'aller vers : une partie, la page des plus hauts score atteints (pas de sauvegarde), la page des paramètres (plein écran (non fonctionnel car empêche la sortie du jeu), difficulté (fonctionnel), et musique (fonctionnel)). Le dernier choix possible est celui de quitter le jeu (non fonctionnel pour une raison inconnue, pour quitter le jeu il faut fermer la console).
Je principe du jeu est de rester en vie le plus longtemps sans entrer en collision avec un astéroid. Pour cela il suffit de les esquiver avec les flèches directionnelles ou de les détruire en pointant la souris dans la direction voulue et le cas échéant de tirer avec le bouton gauche de la souris.

## Description du code
### Dans le main
Le main contient actuellement le code pour générer un écran, qui est la base du programme.
### Classe Point
Représente un point en 2D, avec des méthodes classiques à propos des coordonnées, une fonction pour détecter si deux points sont supperposés et une fonction pour retourner l'angle (en degrés) du vecteur entre deux points.
### Classe Asteroid
Représente un astéroid à partir d'un esemble de points et d'attributs géométriques. S'y trouve aussi les attributs et méthodes utilisés pour le déplacement d'un asteroid, la création de son enveloppe et la détection d'un point dans son enveloppe.
### Classe Tir
Classe qui représnete un tir à partir de coordonnées et qui contient le nécessaire à son mouvement.
### Classe Joueur
Représente un joueur avec les données relatives à un joueur.
### Classe OptionMenu
Représente une ligne de menu, sélectionnable avec le clavier et qui amène vers d'autre écran.
### Classe Jeu
La classe jeu comprend la majorité des algorithmes nécessaire au bon déroulement du jeu. On y trouve notamment les méthodes de collisions entre asteroids, joueur et tirs. Le principe de base et que le jeu avant de trame en trame grace à une méthode d'"avancement". Ensuite des méthodes "rendu" affiche tous les éléments graphiques.
### Classe Ecran
Cette classe génère un écran du jeu, il gère les différents écrans et appelle la classe jeu afin de lancer une partie.

## Divers
En cas de soucis avec la bibliothèque Raylib, nous avons utilisé ce guide :
https://github.com/raysan5/raylib/wiki/Create-Visual-Studio-2019-Project?fbclid=IwAR0bYCk1tebgWyAz46kFeC1OHeDOgAmbQe1RciptH8lFvHH349vEQqWsxXM

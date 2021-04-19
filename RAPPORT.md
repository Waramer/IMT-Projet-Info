# Projet Asteroids - Détection de Collisions
Le projet choisi et de créer un jeu d'astéroïds analogue à l'original Asteroids(1979).

## Collaborateurs
Quentin Delezenne
Clément Kieffer
Louis Delacour
Hugo Vanhille

## Retour sur le déroulement du projet
Le projet a été réalisé sur l'IDE Visual Studio 2019, codé en C++. Le travail a été partagé sir Github et tous les membres de l'équipe ont eu accès à ce dépôt distant afin de pouvoir travailler dessus.
Tous les membres ont utitlisés les outils git et github incorporés à VS2019 pour la gestion des versions. Il y avait une branche principale pour le rencu du travail, une branche Dev pour la version Work In Progress et enfin, chaque personne avait sa propre branche afin de travailler sans gêner les autres et afin d'avoir une sauvegarde en ligne de son travail.
La méthode qui a été utilisée est la suivante : 2 personnes ne travaillent pas sur le même fichier, lorsqu'une personne à fini son travail sur sa branche personnelle, elle checkout sur Dev, Pull afin de se mettre à jour, pui fusionne sa branche dans Dev en résolvant les conflits et en lançant le programme au moins une fois pour vérifier son intégrité.
Cette méthode est inspirée du GitFlow.

## Objectifs
Le premier objectif a été de générer une enveloppe convexe à parti de multiple point, chose qui a été faite avec les astéroides. Les détection de collision ont ensuite été réalisés entre les astéroides et les autres objects du jeu (joueur et tirs).
Enfin il a été question de mettre cela en forme et de créer le jeu à proprement parler, avec ses menus, options, l'implémentation d'un modèle arbitraire de difficulté et un peu de design visuel et audio.

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
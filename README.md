# Projet Asteroids - Détection de Collisions
Le projet choisi et de créer un jeu d'astéroïds analogue à l'original Asteroids(1979). La détection de collision sera alors utilisée pour détecter si un astéroïd touhera le vaisseau ou quand un tir touche un astéroïd pour le détruire. Nous codons en C++ avec Virtual Studio 2019.

## Collaborateurs
Quentin Delezenne
Clément Kieffer
Louis Delacour
Hugo Vanhille

## Decription du code

### Dans le main

Le main contient actuellement le code pour montrer les résultat des algorithmes relatifs à l'enveloppe ( donc aux classes Asteroid et Point ) ainsi qu'un test d'un première fenêtre utilisant la bibliothèque Raylib.

### Asteroid, Point et l'enveloppe

Point est une classe simple qui représente un point dans l'espace avec des coordonnées X et Y. Plusieurs méthodes relatives à la position d'un point par rapport à un autre sont aussi implémentées pour être utilisées ailleurs.

Asteroid est une classe qui représnete un astéroïd grâce à un vecteur de Points. Plusieurs méthode ont été créées afin de construire une méthode finale permettant de définir l'attribut d'enveloppe d'un asteroid.

### Raylib et les fenêtres
Pas de classes créées pour le moment à cette fin, tout se trouve encore dans les branches des collaborateurs travillant dessus.

### Divers

En cas de soucis avec la bibliothèque Raylib, nous avons utilisé ce guide :
https://github.com/raysan5/raylib/wiki/Create-Visual-Studio-2019-Project?fbclid=IwAR0bYCk1tebgWyAz46kFeC1OHeDOgAmbQe1RciptH8lFvHH349vEQqWsxXM

#include <iostream>
#include <raylib.h>
#include "Asteroid.h"
#include "Ecran.h"
#include <ctime>
#include <cstdlib>
#define _USE_MATH_DEFINES
#include <cmath>
#include "optionMenu.h"
#include "Jeu.h"
#include "Joueur.h"

using namespace std;

Ecran::Ecran()

{}
    void Ecran::affiche() {

        
        const int screenWidth = 800;
        const int screenHeight = 450;
        int selection = 0;

        //initialisation de la fenêtre
        SetConfigFlags(FLAG_WINDOW_RESIZABLE);
        InitWindow(screenWidth, screenHeight, "Asteroids");
        // ToggleFullscreen();
        SetTargetFPS(60);

        MaximizeWindow();

        //définition des variables
        double x = GetScreenWidth();
        double y = GetScreenHeight();
        Vector2 pointeur = { x * 0.5, y * 0.5 };


        Color color = BLACK;
        const char* s0 = "ASTEROIDS";
        int tailleS0 = MeasureText(s0, 120);

        //options de l'ecran d'accueil
        OptionMenu option1("START GAME", true);
        OptionMenu option2("HIGHSCORES", false);
        OptionMenu option3("SETTINGS", false);
        OptionMenu option4("EXIT GAME", false);
        OptionMenu options[4] = { option1, option2, option3, option4 };
        Color tabcolors[4] = { options[0].getColor(), options[1].getColor(), options[2].getColor(), options[3].getColor() };
        int res = 0;

        //début de la fenêtre
        while (!WindowShouldClose())
        {
            /*
                -------------------------------------------------------------------------Ecran d'accueil --------------------------------------------------------------------------------------------------
            */
            while (res == 0) {
                BeginDrawing();

                ClearBackground(color);

                //déplacement entre les différents menus avec les touches up et down
                if (IsKeyPressed(KEY_DOWN) && selection < 3) {
                    tabcolors[selection] = WHITE;
                    options[selection].setSelection(false);

                    tabcolors[selection + 1] = RED;
                    options[selection + 1].setSelection(true);

                    selection++;
                }

                if (IsKeyPressed(KEY_UP) && selection > 0) {
                    tabcolors[selection] = WHITE;
                    options[selection].setSelection(false);

                    tabcolors[selection - 1] = RED;
                    options[selection - 1].setSelection(true);
                    selection--;
                }


                //changer l'ecran selon le menu activé
                if (IsKeyPressed(KEY_ENTER)) {
                    if (selection == 0) {
                        // Lancer le jeu
                        res = 1;
                    }
                    else if (selection == 1) {
                        // Ouvrir la page Highscores
                    }
                    else if (selection == 2) {
                        // Ouvrir la page Settings
                    }
                    else if (selection == 3) {
                        // Quitter le jeu
                        break;

                    }
                }

                //position des menus sur l'ecran
                DrawText(("%c", s0), x / 2 - tailleS0 / 2, 100, 120, WHITE);
                DrawText(option1.getString(), option1.getPosition(x), y * 0.35, 40, tabcolors[0]);
                DrawText(option2.getString(), option2.getPosition(x), y * 0.35 + y * 0.1, 40, tabcolors[1]);
                DrawText(option3.getString(), option3.getPosition(x), y * 0.35 + y * 0.2, 40, tabcolors[2]);
                DrawText(option4.getString(), option4.getPosition(x), y * 0.35 + y * 0.3, 40, tabcolors[3]);
                EndDrawing();
            }

            /*
                -------------------------------------------------------------------------Ecran de Jeu --------------------------------------------------------------------------------------------------            
            */

            Jeu jeu;
            Joueur joueur;

            while (res == 1) {

                //affiachage du haut de l'ecran

                EnableCursor();

                BeginDrawing();
                ClearBackground(BLACK);
                int test = MeasureText("Asteroids", 30);
                DrawText("Asteroids", GetScreenWidth() * 0.5 - (test * 0.5), GetScreenHeight() * 0.05, 50, WHITE);
                DrawText("Press P for pause", GetScreenWidth() * 0.85 - (test * 0.5), GetScreenHeight() * 0.05, 30, WHITE);
                DrawLine(0, GetScreenHeight() * 0.1, GetScreenWidth(), GetScreenHeight() * 0.1, WHITE);
                EndDrawing();

                float angle = GetGestureDragAngle();
                double pi = 3.1415;
                int sourisx = GetMouseX();
                int sourisy = GetMouseY();


                //calculs pour que le pointeur suive la souris 
                if (sourisx == pointeur.x) {
                    if (sourisy < pointeur.y) {
                        angle = 360;
                    }
                    else if (sourisy > pointeur.y) {
                        angle = 180;
                    }
                    else angle = 180;
                }
                else {
                    if (sourisx > pointeur.x) {
                        angle = 360 - (90 - 180 / pi * atan((float)(pointeur.y - sourisy) / (float)(pointeur.x - sourisx)));
                    }
                    else if (sourisx < pointeur.x) {
                        angle = 360 - (270 - 180 / pi * atan((float)(pointeur.y - sourisy) / (float)(pointeur.x - sourisx)));
                    }
                    else
                        angle = 0;
                }

                //afficher le pointeur
                jeu.collisionCurseur(pointeur.x,pointeur.y,angle);
                DrawPolyLines(pointeur, 3, 20, angle, WHITE);
                

                //déplacer le pointeur quand on appuye sur le pavé directionnel
                if (IsKeyDown(265) && ((int)pointeur.y == (int)(y * 0.1) || (int)(pointeur.y - 1) == (int)(y * 0.1))) pointeur.y = y;
                else if (IsKeyDown(265))pointeur.y -= 2;

                if (IsKeyDown(262) && pointeur.x == x)pointeur.x = 0;
                else if (IsKeyDown(262))pointeur.x += 2;

                if (IsKeyDown(263) && pointeur.x == 0)pointeur.x = x;
                else if (IsKeyDown(263))pointeur.x -= 2;

                if (IsKeyDown(264) && ((int)pointeur.y == y || (int)(pointeur.y + 1 == y))) {
                    pointeur.y = y * 0.1;
                }
                else if (IsKeyDown(264))pointeur.y += 2;

                if (IsKeyDown(KEY_P)) {
                    res = 0;
                }
                
                // affichage des asteroids
                //jeu.avancement();
                jeu.renduAsteroids();
                
                
            }

        }

        CloseWindow();
    }
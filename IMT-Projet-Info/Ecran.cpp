#include <iostream>
#include <raylib.h>
#include "Asteroid.h"
#include "Ecran.h"
#include <ctime>
#include <cstdlib>
#define _USE_MATH_DEFINES
#include <cmath>
#include "optionMenu.h"

using namespace std;

Ecran::Ecran()

{}
    void Ecran::affiche() {

        
        const int screenWidth = 800;
        const int screenHeight = 450;
        int selection = 0;
        int selection2 = 0;


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

        OptionMenu option5("RESUME", true);
        OptionMenu option6("SETTINGS", false);
        OptionMenu option7("MAIN SCREEN", false);
        OptionMenu pause[3] = {option5, option6, option7};
        Color pausecolors[3] = { pause[0].getColor(), pause[1].getColor(), pause[2].getColor()};

        //début de la fenêtre
        while (!WindowShouldClose())
        {
            /*
                -------------------------------------------------------------------------Ecran d'accueil --------------------------------------------------------------------------------------------------
            */
            if (res == 0) {
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


            else if (res == 1) {

                //affiachage du haut de l'ecran
                EnableCursor();
                BeginDrawing();
                ClearBackground(BLACK);
                int test = MeasureText("ASTEROID", 50);
                DrawText("ASTEROID", GetScreenWidth() * 0.5 - (test * 0.5), GetScreenHeight() * 0.05, 50, WHITE);
                DrawText("Press P for pause", GetScreenWidth() * 0.85 - (test * 0.5), GetScreenHeight() * 0.05, 30, WHITE);

                DrawLine(0, GetScreenHeight() * 0.1, GetScreenWidth(), GetScreenHeight() * 0.1, WHITE);
                


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


                //déplacer le pointeur quand on appuye sur le pavé directionnel
                cout << (int)y * 0.1 << "\n";
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
                    EndDrawing();
                    res = 2;
                }




                //afficher le pointeur
                bool element = false;
                int a, b, c, d;
                DrawPolyLines(pointeur, 3, 20, angle, WHITE);


                //afficher les tirs
                a = pointeur.x;
                b = pointeur.y;
                c = sourisx - pointeur.x + 1;
                d = sourisy - pointeur.y + 1;
                int time;
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    DrawCircle(a, b, 3, WHITE);
                    element = true;
                    time = GetTime();

                }
                if (element && GetTime()-time > 10) {
                    
                    DrawCircle(c, d, 3, WHITE);
                    c ++;
                    d++;
                    time = GetTime();

                }
                EndDrawing();
            }

            /*
                -------------------------------------------------------------------------Ecran de Pause --------------------------------------------------------------------------------------------------
            */


            else if (res == 2) {

            BeginDrawing();

            //déplacement entre les différents menus avec les touches up et down
            if (IsKeyPressed(KEY_DOWN) && selection2 < 2) {
                pausecolors[selection2] = WHITE;
                pause[selection2].setSelection(false);

                pausecolors[selection2 + 1] = RED;
                pause[selection2 + 1].setSelection(true);

                selection2++;
            }

            if (IsKeyPressed(KEY_UP) && selection2 > 0) {
                pausecolors[selection2] = WHITE;
                pause[selection2].setSelection(false);

                pausecolors[selection2 - 1] = RED;
                pause[selection2 - 1].setSelection(true);
                selection2--;
            }


            //changer l'ecran selon le menu activé
            if (IsKeyPressed(KEY_ENTER)) {

                if (selection2 == 0) {
                    // Lancer le jeu
                    res = 1;
                }
                else if (selection2 == 1) {
                    // Ouvrir la page Settings
                }
                else if (selection2 == 2) {
                    // Ouvrir le menu
                    pointeur.x = x * 0.5;
                    pointeur.y = y * 0.5;
                    res = 0;
                }
            }

            //position des menus sur l'ecran
            DrawText(option5.getString(), option5.getPosition(x), y * 0.35, 40, pausecolors[0]);
            DrawText(option6.getString(), option6.getPosition(x), y * 0.35 + y * 0.1, 40, pausecolors[1]);
            DrawText(option7.getString(), option7.getPosition(x), y * 0.35 + y * 0.2, 40, pausecolors[2]);
            EndDrawing();

            }
            
        }

        CloseWindow();
    }




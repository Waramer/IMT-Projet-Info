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

using namespace std;

Ecran::Ecran()

{}
    void Ecran::affiche() {

        
        const int screenWidth = 800;
        const int screenHeight = 450;
        int selection = 0;
        int difficultyLevel = 0;
        int fullScreen = 0;
        int musicON = 0;
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

        //Titre de l'écran d'accueil
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

        //Titre de l'écran de réglages
        const char* s1 = "SETTINGS";
        int tailleS1 = MeasureText(s1, 120);

        //options de l'écran de réglages
        OptionMenu optionSettings1("FULL SCREEN : ", true);
        OptionMenu optionSettings2("DIFFICULTY : ", false);
        OptionMenu optionSettings3("MUSIC : ", false);
        OptionMenu optionSettings4("RETURN TO MENU", false);
        OptionMenu optionsSettings[4] = { optionSettings1, optionSettings2, optionSettings3, optionSettings4 };
        Color tabColorsSettings[4] = { optionsSettings[0].getColor(),optionsSettings[1].getColor() ,optionsSettings[2].getColor(),optionsSettings[3].getColor() };

        // Titre de l'écran des scores
        const char* s2 = "HIGHSCORES";
        int tailleS2 = MeasureText(s2, 120);

        const char* s3 = "PRESS ENTER TO RETURN TO MENU";
        int tailleS3 = MeasureText(s3, 40);


        // Tableau des scores trié

        int scoresTab[15] = {5500, 4256, 4214, 4053, 3501, 2798, 2435, 1789, 1456, 1234,880,756,526,128,42};
        char* scoresTabChar[15];



        // choix options
        const char* displayTab[2] = { "OFF","ON" };
        const char* difficultyTab[3] = { "EASY","NORMAL", "HARD" };
        const char* musicTab[2] = { "ON","OFF" };
        int selectionSettings = 0;
        int selectionDisplay = fullScreen;
        int selectionDifficulty = difficultyLevel;
        int selectionMusic= musicON;

        


        OptionMenu option5("RESUME", true);
        OptionMenu option6("SETTINGS", false);
        OptionMenu option7("MAIN SCREEN", false);
        OptionMenu pause[3] = {option5, option6, option7};
        Color pausecolors[3] = { pause[0].getColor(), pause[1].getColor(), pause[2].getColor()};

        //initialisation des sons musique
        InitAudioDevice();
        Sound sound = LoadSound("audio_menu.wav");
        Sound sound2 = LoadSound("audio_jeu.mp3");
        Sound sound3 = LoadSound("tir.wav");
        Sound sound4 = LoadSound("explosion.wav");
        Sound sound5 = LoadSound("game_over.mp3");


        //PlaySoundMulti(sound3);
        //PlaySoundMulti(sound4);
        //PlaySoundMulti(sound5);


        PlaySoundMulti(sound);

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
                        StopSoundMulti();
                        PlaySoundMulti(sound2);
                    }
                    else if (selection == 1) {
                        // Ouvrir la page Highscores
                        res = 3;
                    }
                    else if (selection == 2) {
                        // Ouvrir la page Settings
                        res = 4;
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

            Jeu j;

            while (res == 1) {


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

                j.avancement(pointeur.x,pointeur.y,angle);

                if (j.collisionCurseur(pointeur.x, pointeur.y, angle) == true) {
                    StopSoundMulti();
                    PlaySoundMulti(sound5);
                }



                /*
                -------------------------------------------------------------------------Ecran de Pause --------------------------------------------------------------------------------------------------
                */

                while (res == 2) {

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
                            StopSoundMulti();
                            PlaySoundMulti(sound);
                        }
                    }

                    //position des menus sur l'ecran
                    DrawText(option5.getString(), option5.getPosition(x), y * 0.35, 40, pausecolors[0]);
                    DrawText(option6.getString(), option6.getPosition(x), y * 0.35 + y * 0.1, 40, pausecolors[1]);
                    DrawText(option7.getString(), option7.getPosition(x), y * 0.35 + y * 0.2, 40, pausecolors[2]);
                    EndDrawing();

                }


                EndDrawing();
            }

            


            /*
                ------------------------------------------------------------------------- Ecran de Highscores ----------------------------------------------------------------------------------------------
            */

            while (res == 3) {
                // Page Highscores
                BeginDrawing();
                ClearBackground(color);

                DrawText(("%c", s2), x / 2 - tailleS2 / 2, 100, 120, WHITE);
                for (int i = 0; i < 5;i++) {
                    DrawText(TextFormat("#%d : %d", i + 1, scoresTab[i]), x / 4, 300+100*i, 40, GRAY);
                }
                for (int i = 5; i < 10;i++) {
                    DrawText(TextFormat("#%d : %d", i + 1, scoresTab[i]), x / 2, 300 + 100 * (i-5), 40, GRAY);
                }
                for (int i = 10; i < 15;i++) {
                    DrawText(TextFormat("#%d : %d", i + 1, scoresTab[i]), 3*x / 4, 300 + 100 * (i - 10), 40, GRAY);
                }

                DrawText(("c", s3), x / 2 - tailleS3 / 2, y - 150, 40, RED);
                if (IsKeyPressed(KEY_ENTER)) {
                    res = 0;
                }
            
                EndDrawing();
            }

            /*
                ------------------------------------------------------------------------- Ecran de Settings ------------------------------------------------------------------------------------------------
            */

            while (res == 4) {

                BeginDrawing();
                ClearBackground(color);

                //déplacement entre les différents menus avec les touches up et down
                if (IsKeyPressed(KEY_DOWN) && selectionSettings < 3) {
                    tabColorsSettings[selectionSettings] = WHITE;
                    optionsSettings[selectionSettings].setSelection(false);

                    tabColorsSettings[selectionSettings + 1] = RED;
                    optionsSettings[selectionSettings + 1].setSelection(true);

                    selectionSettings++;
                }

                if (IsKeyPressed(KEY_UP) && selectionSettings > 0) {
                    tabColorsSettings[selectionSettings] = WHITE;
                    optionsSettings[selectionSettings].setSelection(false);

                    tabColorsSettings[selectionSettings - 1] = RED;
                    optionsSettings[selectionSettings - 1].setSelection(true);
                    selectionSettings--;
                }

                switch(selectionSettings){
                case 0:
                    //DISPLAY
                    if (IsKeyPressed(KEY_RIGHT) && selectionDisplay < 1) {
                        selectionDisplay++;
                    }

                    if (IsKeyPressed(KEY_LEFT) && selectionDisplay > 0) {
                        selectionDisplay--;
                    }
                    if (selectionDisplay == 0) {
                        if (IsKeyPressed(KEY_ENTER) && fullScreen == 1) {
                            ToggleFullscreen();
                            fullScreen = selectionDisplay;
                        }
                    }
                    else {
                        if (IsKeyPressed(KEY_ENTER) && fullScreen == 0) {
                            ToggleFullscreen();
                            fullScreen = selectionDisplay;
                        }
                    }
                
                    break;
                case 1:
                    // Difficulty
                    if (IsKeyPressed(KEY_RIGHT) && selectionDifficulty < 2) {
                        selectionDifficulty++;
                    }

                    if (IsKeyPressed(KEY_LEFT) && selectionDifficulty > 0) {
                        selectionDifficulty--;
                    }
                    if (IsKeyPressed(KEY_ENTER)) {
                        difficultyLevel = selectionDifficulty;
                    }
                    break;
                case 2:
                    // Music
                    if (IsKeyPressed(KEY_RIGHT) && selectionMusic < 1) {
                        selectionMusic++;
                    }

                    if (IsKeyPressed(KEY_LEFT) && selectionMusic > 0) {
                        selectionMusic--;
                    }
                    if (IsKeyPressed(KEY_ENTER)) {
                        musicON = selectionMusic;
                        if(musicON%2==1)
                            StopSoundMulti();
                        else
                            PlaySoundMulti(sound2);

                    }
                    break;
                case 3:
                    if (IsKeyPressed(KEY_ENTER)) {
                        selectionDisplay = fullScreen;
                        selectionDifficulty = difficultyLevel;
                        selectionMusic = musicON;
                        res = 0;
                    }
                    break;
                default:
                    break;
                }

                //position des menus sur l'ecran
                DrawText(("%c", s1), x / 2 - tailleS1 / 2, 100, 120, WHITE);
                DrawText(optionSettings1.getString(), optionSettings1.getPosition(x), y * 0.35, 40, tabColorsSettings[0]);
                DrawText(displayTab[selectionDisplay], optionSettings1.getPosition(x) + MeasureText(optionSettings1.getString(),40), y * 0.35, 40, GRAY);
                DrawText(optionSettings2.getString(), optionSettings2.getPosition(x), y * 0.35 + y * 0.1, 40, tabColorsSettings[1]);
                DrawText(difficultyTab[selectionDifficulty], optionSettings2.getPosition(x) +  MeasureText(optionSettings2.getString(), 40), y * 0.35 + y * 0.1, 40, GRAY);
                DrawText(optionSettings3.getString(), optionSettings3.getPosition(x), y * 0.35 + y * 0.2, 40, tabColorsSettings[2]);
                DrawText(musicTab[selectionMusic], optionSettings3.getPosition(x) +  MeasureText(optionSettings3.getString(), 40), y * 0.35 + y * 0.2, 40, GRAY);
                DrawText(optionSettings4.getString(), optionSettings4.getPosition(x), y * 0.35 + y * 0.3, 40, tabColorsSettings[3]);
                EndDrawing();

            }

        }
        //Arret des sons
        UnloadSound(sound);
        UnloadSound(sound2);
        UnloadSound(sound3);
        UnloadSound(sound4);
        UnloadSound(sound5);
        CloseAudioDevice();

        CloseWindow();
    }




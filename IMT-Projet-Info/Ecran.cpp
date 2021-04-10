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
        int difficultyLevel = 0;
        int fullScreen = 0;
        int musicON = 0;
        int selection2 = 0;
        int selectionGameOver = 0;


        Joueur joueur;
        
        


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
        int screenOptionsSizes[2] = { MeasureText("FULL SCREEN : OFF", 40), MeasureText("FULL SCREEN : ON", 40) };
        OptionMenu optionSettings2("DIFFICULTY : ", false);
        int difficultyOptionsSizes[3] = { MeasureText("DIFFICULTY : EASY", 40), MeasureText("DIFFICULTY : MEDIUM", 40), MeasureText("DIFFICULTY : HARD", 40) };
        OptionMenu optionSettings3("MUSIC : ", false);
        int musicOptionsSizes[2] = { MeasureText("MUSIC : ON", 40), MeasureText("MUSIC : OFF", 40) };
        OptionMenu optionSettings4("MAIN SCREEN", false);
        OptionMenu optionsSettings[4] = { optionSettings1, optionSettings2, optionSettings3, optionSettings4 };
        Color tabColorsSettings[4] = { optionsSettings[0].getColor(),optionsSettings[1].getColor() ,optionsSettings[2].getColor(),optionsSettings[3].getColor() };

        // Titre de l'écran des scores
        const char* s2 = "HIGHSCORES";
        int tailleS2 = MeasureText(s2, 120);

        const char* s3 = "PRESS ENTER TO RETURN TO MENU";
        int tailleS3 = MeasureText(s3, 40);


        // Tableau des scores trié

        int scoresTabEasy[5] = {};
        int scoresTabMedium[5] = {};
        int scoresTabHard[5] = {};
        //int highscore = scoresTab[0];
        //char* scoresTabChar[15];

        // Menu Game Over

        const char* s4 = "GAME OVER";
        int tailleS4 = MeasureText(s4, 200);

        const char* s5 = "YOUR SCORE : ";
        int tailleS5 = MeasureText(s5, 75);

        const char* s6 = "HIGHSCORE : ";
        int tailleS6 = MeasureText(s5, 75);


        OptionMenu optionGameOver1("RESTART GAME", true);
        OptionMenu optionGameOver2("MAIN SCREEN", false);
        OptionMenu optionsGameOver[2] = { optionGameOver1, optionGameOver2 };
        Color tabColorsGameOver[2] = { optionsGameOver[0].getColor(), optionsGameOver[1].getColor() };

        // choix options
        const char* displayTab[2] = { "OFF","ON" };
        const char* difficultyTab[3] = { "EASY","MEDIUM", "HARD" };
        const char* musicTab[2] = { "ON","OFF" };
        int selectionSettings = 0;
        int selectionDisplay = fullScreen;
        int selectionDifficulty = difficultyLevel;
        int selectionMusic= musicON;

        


        OptionMenu option5("RESUME GAME", true);
        OptionMenu option6("MAIN SCREEN", false);
        OptionMenu pause[2] = {option5, option6};
        Color pausecolors[2] = { pause[0].getColor(), pause[1].getColor()};

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
                        pointeur.x = x * 0.5;
                        pointeur.y = y * 0.5;
                        StopSoundMulti();
                        if (musicON != 1) {
                            PlaySoundMulti(sound2);
                        }
                        
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
                        StopSoundMulti();
                        break;

                    }
                }

                //position des menus sur l'ecran
                DrawText(("%c", s0), x / 2 - tailleS0 / 2, 100, 120, WHITE);
                for (int i = 0; i < 4;i++) {
                    DrawText(options[i].getString(), options[i].getPosition(x), y * 0.35 + i*y*0.1, 40, tabcolors[i]);
                }
                
                EndDrawing();
            }

            /*
                -------------------------------------------------------------------------Ecran de Jeu --------------------------------------------------------------------------------------------------            
            */        

            Jeu j(difficultyLevel, joueur);
            int score = 0;

            while (res == 1) {

                switch (difficultyLevel) {
                case 0:
                    score = j.j_joueur.getScoreEasy();
                    break;

                case 1:
                    score = j.j_joueur.getScoreMedium();
                    break;
                case 2:
                    score = j.j_joueur.getScoreHard();
                    break;
                default:
                    break;
                }
                
                //affichage du haut de l'ecran
                EnableCursor();
                BeginDrawing();
                ClearBackground(BLACK);
                int test = MeasureText("ASTEROID", 75);
                DrawText("ASTEROID", x * 0.5 - (test * 0.5), y * 0.015, 75, WHITE);
                DrawText("PRESS P FOR PAUSE", x * 0.85 - (test * 0.5), y * 0.03, 40, WHITE);
                DrawText(TextFormat("SCORE : %d", score), x * 0.05, y * 0.03, 40, WHITE);
                DrawLine(0, y * 0.1, x, y * 0.1, WHITE);

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
                else if (IsKeyDown(265))pointeur.y -= 3;

                if (IsKeyDown(262) && pointeur.x == x)pointeur.x = 0;
                else if (IsKeyDown(262))pointeur.x += 3;

                if (IsKeyDown(263) && pointeur.x == 0)pointeur.x = x;
                else if (IsKeyDown(263))pointeur.x -= 3;

                if (IsKeyDown(264) && ((int)pointeur.y == y || (int)(pointeur.y + 1 == y))) {
                    pointeur.y = y * 0.1;
                }
                else if (IsKeyDown(264))pointeur.y += 3;

                //afficher le pointeur
                bool element = false;
                int a, b, c, d;
                DrawPolyLines(pointeur, 3, 20, angle, WHITE);

                j.avancement(pointeur.x,pointeur.y,angle);

                if (j.collisionCurseur(pointeur.x, pointeur.y, angle) == true) {
                    int tmp = 0;
                    int newScoresTab[5] = {};

                    switch (difficultyLevel) {
                    case 0:
                        for (int i = 0; i < 5;i++) {
                            if (score >= scoresTabEasy[i] && tmp == 0) {
                                newScoresTab[i] = score;
                                tmp += 1;
                                for (int k = i; k < 4;k++) {
                                    newScoresTab[k + 1] = scoresTabEasy[k];
                                }
                            }
                            else if (score < scoresTabEasy[i]) {
                                newScoresTab[i] = scoresTabEasy[i];
                            }
                        }
                        for (int i = 0; i < 5;i++) {
                            scoresTabEasy[i] = newScoresTab[i];
                        }
                        
                        break;

                    case 1:
                        for (int i = 0; i < 5;i++) {
                            if (score >= scoresTabMedium[i] && tmp == 0) {
                                newScoresTab[i] = score;
                                tmp += 1;
                                for (int k = i; k < 4;k++) {
                                    newScoresTab[k + 1] = scoresTabMedium[k];
                                }
                            }
                            else if (score < scoresTabMedium[i]) {
                                newScoresTab[i] = scoresTabMedium[i];
                            }
                        }
                        for (int i = 0; i < 5;i++) {
                            scoresTabMedium[i] = newScoresTab[i];
                        }

                        break;
                    case 2:
                        for (int i = 0; i < 5;i++) {
                            if (score >= scoresTabHard[i] && tmp == 0) {
                                newScoresTab[i] = score;
                                tmp += 1;
                                for (int k = i; k < 4;k++) {
                                    newScoresTab[k + 1] = scoresTabHard[k];
                                }
                            }
                            else if (score < scoresTabHard[i]) {
                                newScoresTab[i] = scoresTabHard[i];
                            }
                        }
                        for (int i = 0; i < 5;i++) {
                            scoresTabHard[i] = newScoresTab[i];
                        }
                        break;
                    default:
                        break;
                    }
                    
                    
                    
                    StopSoundMulti();
                    PlaySoundMulti(sound5);
                    res = 5;
                }

                if (IsKeyDown(KEY_P)) {
                    EndDrawing();
                    res = 2;
                }

               

                /*
                -------------------------------------------------------------------------Ecran de Pause --------------------------------------------------------------------------------------------------
                */

                while (res == 2) {

                    ClearBackground(BLACK);
                    BeginDrawing();
                    int test = MeasureText("ASTEROID", 75);
                    int test2 = MeasureText("GAME PAUSED", 100);
                    DrawText("ASTEROID", x * 0.5 - (test * 0.5), y * 0.015, 75, WHITE);
                    DrawText("GAME PAUSED", x * 0.5 - (test2 * 0.5), y * 0.3, 100, WHITE);
                    DrawText(TextFormat("SCORE : %d", score), x * 0.05, y * 0.03, 40, WHITE);
                    DrawLine(0, y * 0.1, x, y * 0.1, WHITE);
                    

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
                            // Ouvrir le menu
                            pointeur.x = x * 0.5;
                            pointeur.y = y * 0.5;
                            res = 0;
                            StopSoundMulti();
                            if (musicON != 1) {
                                PlaySoundMulti(sound);
                            }
                            
                        }
                    }

                    //position des menus sur l'ecran
                    DrawText(option5.getString(), option5.getPosition(x), y * 0.5, 40, pausecolors[0]);
                    DrawText(option6.getString(), option6.getPosition(x), y * 0.5 + y * 0.1, 40, pausecolors[1]);
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

                DrawText("EASY : ", x / 4, 300, 40, WHITE);
                for (int i = 0; i < 5;i++) {
                    DrawText(TextFormat("#%d : %d", i + 1, scoresTabEasy[i]), x / 4, 400+100*i, 40, GRAY);
                }

                DrawText("MEDIUM : ", x / 2, 300, 40, WHITE);
                for (int i = 0; i < 5;i++) {
                    DrawText(TextFormat("#%d : %d", i + 1, scoresTabMedium[i]), x / 2, 400 + 100 *i, 40, GRAY);
                }

                DrawText("HARD : ", 3*x / 4, 300, 40, WHITE);
                for (int i = 0; i < 5;i++) {
                    DrawText(TextFormat("#%d : %d", i + 1, scoresTabHard[i]), 3*x / 4, 400 + 100 *i, 40, GRAY);
                }

                DrawText(("c", s3), x / 2 - tailleS3 / 2, y - 100, 40, RED);
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
                    
                
                    break;
                case 1:
                    // Difficulty
                    if (IsKeyPressed(KEY_RIGHT) && selectionDifficulty < 2) {
                        selectionDifficulty++;
                    }

                    if (IsKeyPressed(KEY_LEFT) && selectionDifficulty > 0) {
                        selectionDifficulty--;
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
                    
                    break;
                case 3:
                    if (IsKeyPressed(KEY_ENTER)) {
                        // Application de l'affichage
                        if (selectionDisplay == 0 && fullScreen == 1) {
                            ToggleFullscreen();
                            fullScreen = selectionDisplay;
                            
                        }
                        else if (selectionDisplay == 1 && fullScreen == 0) {
                                ToggleFullscreen();
                                fullScreen = selectionDisplay;
                            
                        }

                        // Application de la difficulté
                        difficultyLevel = selectionDifficulty;

                        // Application du réglage de la musique
                        musicON = selectionMusic;
                        if (musicON  == 1)
                            StopSoundMulti();
                        else if(GetSoundsPlaying() == 0)
                            PlaySoundMulti(sound);

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
                
                DrawText(optionsSettings[0].getString(), x/2 - screenOptionsSizes[selectionDisplay]/2, y * 0.35, 40, tabColorsSettings[0]);
                DrawText(optionsSettings[1].getString(), x / 2 -difficultyOptionsSizes[selectionDifficulty] / 2, y * 0.35 + y * 0.1 * 1, 40, tabColorsSettings[1]);
                DrawText(optionsSettings[2].getString(), x / 2 - musicOptionsSizes[selectionMusic] / 2, y * 0.35 + y * 0.1 * 2, 40, tabColorsSettings[2]);
                DrawText(optionsSettings[3].getString(), optionsSettings[3].getPosition(x), y * 0.35 + y * 0.1 * 3, 40, tabColorsSettings[3]);

                DrawText(displayTab[selectionDisplay], x / 2 - screenOptionsSizes[selectionDisplay] / 2 + MeasureText(optionSettings1.getString(),40), y * 0.35, 40, GRAY);
                DrawText(difficultyTab[selectionDifficulty], x/2 - difficultyOptionsSizes[selectionDifficulty] / 2 +  MeasureText(optionSettings2.getString(), 40), y * 0.35 + y * 0.1, 40, GRAY);
                DrawText(musicTab[selectionMusic], x / 2 - musicOptionsSizes[selectionMusic] / 2 +  MeasureText(optionSettings3.getString(), 40), y * 0.35 + y * 0.2, 40, GRAY);
                EndDrawing();

            }

            /*
                ------------------------------------------------------------------------- Ecran de Game Over ------------------------------------------------------------------------------------------------
            */

            while (res == 5) {
                BeginDrawing();
                ClearBackground(BLACK);
                if (IsKeyPressed(KEY_DOWN) && selectionGameOver < 1) {
                    tabColorsGameOver[selectionGameOver] = WHITE;
                    optionsGameOver[selectionGameOver].setSelection(false);

                    tabColorsGameOver[selectionGameOver + 1] = RED;
                    optionsGameOver[selectionGameOver + 1].setSelection(true);

                    selectionGameOver++;
                }

                if (IsKeyPressed(KEY_UP) && selectionGameOver > 0) {
                    tabColorsGameOver[selectionGameOver] = WHITE;
                    optionsGameOver[selectionGameOver].setSelection(false);

                    tabColorsGameOver[selectionGameOver - 1] = RED;
                    optionsGameOver[selectionGameOver - 1].setSelection(true);
                    selectionGameOver--;
                }

                if (IsKeyPressed(KEY_ENTER)) {
                    if (selectionGameOver == 0) {
                        res = 1;
                        pointeur.x = x * 0.5;
                        pointeur.y = y * 0.5;
                        StopSoundMulti();
                        PlaySoundMulti(sound2);
                    }
                    else {
                        res = 0;
                        StopSoundMulti();
                        if (musicON != 1) {
                            PlaySoundMulti(sound);
                        }
                        
                    }
                }

                DrawText(("%c", s4), x / 2 - tailleS4 / 2, 100, 200, RED);

                switch (difficultyLevel) {
                case 0:
                    DrawText(TextFormat("SCORE : %d", j.j_joueur.getScoreEasy()), x / 2 - tailleS5 / 2, 350, 75, GRAY);
                    DrawText(TextFormat("HIGHSCORE : %d", scoresTabEasy[0]), x / 2 - tailleS6 / 2, 450, 75, GRAY);
                    break;

                case 1:
                    DrawText(TextFormat("SCORE : %d", j.j_joueur.getScoreMedium()), x / 2 - tailleS5 / 2, 350, 75, GRAY);
                    DrawText(TextFormat("HIGHSCORE : %d", scoresTabMedium[0]), x / 2 - tailleS6 / 2, 450, 75, GRAY);
                    break;
                case 2:
                    DrawText(TextFormat("SCORE : %d", j.j_joueur.getScoreHard()), x / 2 - tailleS5 / 2, 350, 75, GRAY);
                    DrawText(TextFormat("HIGHSCORE : %d", scoresTabHard[0]), x / 2 - tailleS6 / 2, 450, 75, GRAY);
                    break;
                default:
                    break;
                }
               
                for (int i = 0;i < 2;i++) {
                    DrawText(optionsGameOver[i].getString(), optionsGameOver[i].getPosition(x), y * 0.6+y*i*0.1, 40, tabColorsGameOver[i]);
                }
                
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



